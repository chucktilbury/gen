/**
 * @file string_buf.c
 *
 * @brief
 *
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @version 0.1
 * @date 2025-03-25
 * @copyright Copyright (c) 2025
 */
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "alloc.h"
#include "string_buf.h"

string_buf_t* create_string_buf(const char* str) {

    string_buf_t* ptr = _ALLOC_TYPE(string_buf_t);
    ptr->len = 0;
    ptr->cap = 1 << 3;
    ptr->buffer = _ALLOC_ARRAY(char, ptr->cap);

    if(str != NULL)
        append_string_buf(ptr, str);

    return ptr;
}

string_buf_t* create_string_buf_fmt(const char* fmt, ...) {

    va_list args;

    va_start(args, fmt);
    size_t len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    char* str = _ALLOC(len+1);

    va_start(args, fmt);
    vsprintf(str, fmt, args);
    va_end(args);

    string_buf_t* buf = create_string_buf(str);
    _FREE(str);

    return buf;
}

void destroy_string_buf(string_buf_t* buf) {

    if(buf != NULL) {
        if(buf->buffer != NULL)
            _FREE(buf->buffer);

        _FREE(buf);
    }
}

void append_string_buf(string_buf_t* buf, const char* str) {

    size_t len = strlen(str);

    if(buf->len + len >= buf->cap) {
        while(buf->len + len >= buf->cap)
            buf->cap <<= 1;
        buf->buffer = _REALLOC_ARRAY(buf->buffer, char, buf->cap);
    }

    memcpy(&buf->buffer[buf->len], str, len+1);
    buf->len += len;
}

void append_string_buf_fmt(string_buf_t* buf, const char* fmt, ...) {

    va_list args;

    va_start(args, fmt);
    size_t len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    char* str = _ALLOC(len+1);

    va_start(args, fmt);
    vsprintf(str, fmt, args);
    va_end(args);

    append_string_buf(buf, str);
    _FREE(str);
}

void append_string_buf_char(string_buf_t* buf, int ch) {

    if(buf->len+2 >= buf->cap) {
        buf->cap <<= 1;
        buf->buffer = _REALLOC_ARRAY(buf->buffer, char, buf->cap);
    }

    buf->buffer[buf->len] = (char)ch;
    buf->len++;
    buf->buffer[buf->len] = '\0';
}

const char* raw_string_buf(string_buf_t* buf) {

    return buf->buffer;
}

int len_string_buf(string_buf_t* buf) {

    return (int)buf->len;
}

int comp_string_buf(string_buf_t* buf1, string_buf_t* buf2) {

    return strcmp(buf1->buffer, buf2->buffer);
}

void strip_quotes(string_buf_t* buf) {

    if(buf->buffer[0] == '\'' || buf->buffer[0] == '\"') {
        memmove(&buf->buffer[0], &buf->buffer[1], buf->len+1);
        buf->len -= 2;
        if(buf->buffer[buf->len] == '\'' || buf->buffer[buf->len] == '\"')
            buf->buffer[buf->len] = '\0';

    }

    buf->len = strlen(buf->buffer);
}

void strip_space(string_buf_t* buf) {

    int idx = 0;

    while(isspace(buf->buffer[idx]) && buf->buffer[idx] != '\0')
        idx++;

    if(buf->buffer[idx] != '\0') {
        int len = strlen(&buf->buffer[idx]);
        memmove(&buf->buffer[0], &buf->buffer[idx], len+1);

        len--;
        while(isspace(buf->buffer[len]) && len >= 0) {
            buf->buffer[len] = '\0';
            len--;
        }
    }

    buf->len = strlen(buf->buffer);
}

#if 0
int main(void) {

    string_buf_t* ptr = create_string_buf("'   this isi the string   \"");

    strip_quotes(ptr);
    strip_space(ptr);

    printf("\"%s\"\n", ptr->buffer);

    append_string_buf_fmt(ptr, " carp: %d and %s", 24, "another string");

    printf("\"%s\"\n", ptr->buffer);

    return 0;
}
#endif
