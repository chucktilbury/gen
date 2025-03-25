/**
 * @file trace.h
 *
 * @brief
 *
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @version 0.1
 * @date 2025-03-24
 * @copyright Copyright (c) 2025
 */
#ifndef _TRACE_
#define _TRACE_

#include <stdio.h>
#include <stdlib.h>

extern int trace_depth;

#define TRACE(...) \
    do { \
        fprintf(stdout, "%*sTRACE: ", trace_depth, ""); \
        fprintf(stdout, __VA_ARGS__); \
        fprintf(stdout, "\n"); \
    } while(0)

#define ENTER \
    do { \
        fprintf(stdout, "%*sENTER: %s: %s: %d", trace_depth, "", __FILE__, __FUNC__, __LINE__); \
        trace_depth+=2; \
    } while(0)

#define RETURN(...) \
    do { \
        trace_depth-=2; \
        fprintf(stdout, "%*sRETURN(%s) %s", trace_depth, "", #__VA_ARGS__, __FUNC__); \
        return(__VA_ARGS__); \
    } while(0)

#define SEPARATOR printf("------------------------\n");

#define ASSERT(expr, ...)                                                                                 \
    do {                                                                                                  \
        if(!(expr)) {                                                                                     \
            fprintf(stderr, "%s: %s: %d: assertion failed: (%s): ", __FILE__, __func__, __LINE__, #expr); \
            fprintf(stderr, __VA_ARGS__);                                                                 \
            fputc('\n', stderr);                                                                          \
            abort();                                                                                      \
        }                                                                                                 \
    } while(0)

#define FATAL(...)                                                                  \
    do {                                                                            \
        fprintf(stderr, "fatal error: %s: %s: %d: ", __FILE__, __func__, __LINE__); \
        fprintf(stderr, __VA_ARGS__);                                               \
        fputc('\n', stderr);                                                        \
        exit(1);                                                                    \
    } while(0)

#endif /* _TRACE_ */
