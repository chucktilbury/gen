#ifndef _FILEIO_H_
#define _FILEIO_H_

#include <stdio.h>

typedef struct _file_info_t_ {
    const char* name;
    FILE* fp;
    size_t line_no;
    size_t col_no;
    struct _file_info_t_* next;
} file_info_t;

void open_file(const char* fname);
int get_char(void);
int get_line_no(void);
int get_col_no(void);
const char* get_fname(void);

#endif /* _FILEIO_H_ */
