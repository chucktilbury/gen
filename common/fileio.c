
#include <string.h>
#include <errno.h>

#include "mem.h"
#include "errors.h"
#include "fileio.h"

static file_info_t* file_stack = NULL;
static file_info_t* end_file = NULL;

void open_file(const char* fname) {

    FILE* fp = fopen(fname, "r");
    if(fp == NULL)
        FATAL("cannot open input file: %s: %s", fname, strerror(errno));

    file_info_t* ptr = _ALLOC_TYPE(file_info_t);
    ptr->fp = fp;
    ptr->name = _COPY_STRING(fname);
    ptr->col_no = 1;
    ptr->line_no = 1;

    if(file_stack != NULL)
        ptr->next = file_stack;
    file_stack = ptr;

    advance_char();
}

int get_char(void) {

    int ch = EOF;

    if(file_stack != NULL)
        ch = file_stack->ch;

    return ch;
}

int advance_char(void) {

    if(file_stack != NULL) {
        int ch = fgetc(file_stack->fp);
        if(ch == EOF) {
            fclose(file_stack->fp);
            file_info_t* old = file_stack;
            file_stack = file_stack->next;
            // this allows something useful to be retuned by the getters
            // after the last of the input has been scanned.
            if(file_stack == NULL)
                end_file = old;
            else {
                _FREE(old->name);
                _FREE(old);
            }
            return get_char();
        }
        else if(ch == '\n') {
            file_stack->col_no = 1;
            file_stack->line_no++;
        }
        else
            file_stack->col_no++;

        file_stack->ch = ch;
        return ch;

    }
    else
        return EOF;
}

int get_line_no(void) {

    if(file_stack != NULL)
        return file_stack->line_no;
    else if(end_file != NULL)
        return end_file->line_no;
    else
        return -1; // no file has ever been open
}

int get_col_no(void) {

    if(file_stack != NULL)
        return file_stack->col_no;
    else if(end_file != NULL)
        return end_file->col_no;
    else
        return -1;
}

const char* get_fname(void) {

    if(file_stack != NULL)
        return file_stack->name;
    else if(end_file != NULL)
        return end_file->name;
    else
        return NULL;
}

