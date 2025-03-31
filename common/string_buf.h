#ifndef _STRING_BUF_H_
#define _STRING_BUF_H_

#include <stddef.h>

typedef struct _string_buf_t_ {
    char* buffer;
    size_t len;
    size_t cap;
} string_buf_t;

string_buf_t* create_string_buf(const char* str);
string_buf_t* create_string_buf_fmt(const char* fmt, ...);
void destroy_string_buf(string_buf_t* buf);
void append_string_buf(string_buf_t* buf, const char* str);
void append_string_buf_fmt(string_buf_t* buf, const char* fmt, ...);
void append_string_buf_char(string_buf_t* buf, int ch);
const char* raw_string_buf(string_buf_t* buf);
int len_string_buf(string_buf_t* buf);
int comp_string_buf(string_buf_t* buf1, string_buf_t* buf2);

void strip_quotes(string_buf_t* buf);
void strip_space(string_buf_t* buf);

#endif /* _STRING_BUF_H_ */
