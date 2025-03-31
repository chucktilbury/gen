/**
 *
 * @file token_defs.h
 *
 * @brief Token definitions public interface.
 * This file was generated on Sun Mar 30 23:32:20 2025.
 *
 */
#ifndef _TOKEN_DEFS_H_
#define _TOKEN_DEFS_H_

#include <stdint.h>

typedef enum {
    TOK_START = 256,
    TOK_IMPORT = 257,
    TOK_AS = 258,
    TOK_IDENT = 259,
    TOK_INCLUDE = 260,
    TOK_PRIVATE = 261,
    TOK_PUBLIC = 262,
    TOK_PROTECTED = 263,
    TOK_FLOAT = 264,
    TOK_INTEGER = 265,
    TOK_STRING = 266,
    TOK_BOOLEAN = 267,
    TOK_NOTHING = 268,
    TOK_LIST = 269,
    TOK_DICT = 270,
    TOK_LITERAL_STRING = 271,
    TOK_LITERAL_FLOAT = 272,
    TOK_LITERAL_INTEGER = 273,
    TOK_LITERAL_BOOL = 274,
    TOK_OPAREN = 275,
    TOK_COMMA = 276,
    TOK_CPAREN = 277,
    TOK_CONST = 278,
    TOK_EQUAL = 279,
    TOK_COLON = 280,
    TOK_OSBRACE = 281,
    TOK_CSBRACE = 282,
    TOK_DOT = 283,
    TOK_CREATE = 284,
    TOK_DESTROY = 285,
    TOK_OR_OPER = 286,
    TOK_AND_OPER = 287,
    TOK_EQU_OPER = 288,
    TOK_NEQU_OPER = 289,
    TOK_LT_OPER = 290,
    TOK_GT_OPER = 291,
    TOK_LTE_OPER = 292,
    TOK_GTE_OPER = 293,
    TOK_PLUS = 294,
    TOK_MINUS = 295,
    TOK_STAR = 296,
    TOK_SLASH = 297,
    TOK_PERCENT = 298,
    TOK_NOT_OPER = 299,
    TOK_NAMESPACE = 300,
    TOK_OCBRACE = 301,
    TOK_CCBRACE = 302,
    TOK_CLASS = 303,
    TOK_PLUS_EQUAL = 304,
    TOK_MINUS_EQUAL = 305,
    TOK_STAR_EQUAL = 306,
    TOK_SLASH_EQUAL = 307,
    TOK_PERCENT_EQUAL = 308,
    TOK_INLINE = 309,
    TOK_BREAK = 310,
    TOK_CONTINUE = 311,
    TOK_YIELD = 312,
    TOK_TYPE = 313,
    TOK_RETURN = 314,
    TOK_RAISE = 315,
    TOK_TRACE = 316,
    TOK_PRINT = 317,
    TOK_EXIT = 318,
    TOK_WHILE = 319,
    TOK_DO = 320,
    TOK_FOR = 321,
    TOK_IF = 322,
    TOK_ELSE = 323,
    TOK_TRY = 324,
    TOK_EXCEPT = 325,
    TOK_FINAL = 326,
    TOK_COMMENT = 327,

    TOK_END_OF_INPUT = 328,
    TOK_END_OF_FILE = 329,
    TOK_ERROR = 330,
} token_type_t;


typedef struct _token_t_ {
    token_type_t type;
    const char* raw;
    const char* fname;
    int line_no;
    int col_no;
    union {
        int64_t count;
        double real;
        unsigned char boolean;
        const char* text;
        void* other;
    } value;
    struct _token_t_* next;
} token_t;

void init_token_queue(const char* fname);
void* post_token_queue(void);
void reset_token_queue(void* post);
void consume_token_queue(void);
void add_token_queue(token_t* tok);

token_t* create_token(const char* str, token_type_t type);
token_t* get_token(void);
token_t* advance_token(void);
const char* token_type_to_str(token_type_t type);

#endif /* _TOKEN_DEFS_H_ */

