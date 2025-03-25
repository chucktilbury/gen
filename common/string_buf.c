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
#include <string.h>
#include <stdarg.h>

#include "mem.h"
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
    size_t len = vsnsprintf(NULL, 0, fmt, args);
    va_end(args);

    const char* str = _ALLOC(len+1);

    va_start(args, fmt);
    size_t len = vsprintf(str, fmt, args);
    va_end(args);

    string_buf_t* buf = create_string_buf(str);
    _FREE(str);

    return buf;
}

void append_string_buf(string_buf_t* buf, const char* str) {

    size_t len = strlen(str);

    if(buf->len + len >= buf->cap) {
        while(buf->len + len >= buf->cap)
            buf->cap <<= 1;
        buf->buffer = _REALLOC_TYPE(buf->buffer, char, buf->cap);
    }

    memcpy(&buf->buffer[buf->len], str, len+1);
    buf->len += len;
}

void append_string_buf_fmt(string_buf_t* buf, const char* fmt, ...) {

    va_list args;

    va_start(args, fmt);
    size_t len = vsnsprintf(NULL, 0, fmt, args);
    va_end(args);

    const char* str = _ALLOC(len+1);

    va_start(args, fmt);
    size_t len = vsprintf(str, fmt, args);
    va_end(args);

    append_string_buf(buf, str);
    _FREE(str);
}

void append_string_buf_char(string_buf_t* buf, int ch) {

    if(buf->len+2 >= buf->cap) {
        buf->cap <<= 1;
        buf->buffer = _REALLOC_TYPE(buf->buffer, char, buf->cap);
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

