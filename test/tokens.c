/**
 *
 * @file token_defs.c
 *
 * @brief Token definition implementation.
 * This file was generated on Sun Mar 30 23:32:20 2025.
 *
 */


#include <stdio.h>
#include <strings.h>

#include "fileio.h"
#include "tokens.h"

void init_token_queue(const char* fname) {
}

void* post_token_queue(void) {
}

void reset_token_queue(void* post) {
}

void consume_token_queue(void) {
}

void add_token_queue(token_t* tok) {
//printf("add token queue\n");
}

token_t* create_token(const char* str, token_type_t type) {
printf("%d:%d: create token: \"%s\" %s\n", get_line_no(), get_col_no(), str, token_type_to_str(type));
}

token_t* get_token(void) {
}

token_t* advance_token(void) {
}

const char* token_type_to_str(token_type_t type) {

    return (type == TOK_START)? "start" :
        (type == TOK_IMPORT)? "import" :
        (type == TOK_AS)? "as" :
        (type == TOK_IDENT)? "IDENT" :
        (type == TOK_INCLUDE)? "include" :
        (type == TOK_PRIVATE)? "private" :
        (type == TOK_PUBLIC)? "public" :
        (type == TOK_PROTECTED)? "protected" :
        (type == TOK_FLOAT)? "float" :
        (type == TOK_INTEGER)? "integer" :
        (type == TOK_STRING)? "string" :
        (type == TOK_BOOLEAN)? "boolean" :
        (type == TOK_NOTHING)? "nothing" :
        (type == TOK_LIST)? "list" :
        (type == TOK_DICT)? "dict" :
        (type == TOK_LITERAL_STRING)? "LITERAL_STRING" :
        (type == TOK_LITERAL_FLOAT)? "LITERAL_FLOAT" :
        (type == TOK_LITERAL_INTEGER)? "LITERAL_INTEGER" :
        (type == TOK_LITERAL_BOOL)? "LITERAL_BOOL" :
        (type == TOK_OPAREN)? "(" :
        (type == TOK_COMMA)? "," :
        (type == TOK_CPAREN)? ")" :
        (type == TOK_CONST)? "const" :
        (type == TOK_EQUAL)? "=" :
        (type == TOK_COLON)? ":" :
        (type == TOK_OSBRACE)? "[" :
        (type == TOK_CSBRACE)? "]" :
        (type == TOK_DOT)? "." :
        (type == TOK_CREATE)? "create" :
        (type == TOK_DESTROY)? "destroy" :
        (type == TOK_OR_OPER)? "OR_OPER" :
        (type == TOK_AND_OPER)? "AND_OPER" :
        (type == TOK_EQU_OPER)? "EQU_OPER" :
        (type == TOK_NEQU_OPER)? "NEQU_OPER" :
        (type == TOK_LT_OPER)? "LT_OPER" :
        (type == TOK_GT_OPER)? "GT_OPER" :
        (type == TOK_LTE_OPER)? "LTE_OPER" :
        (type == TOK_GTE_OPER)? "GTE_OPER" :
        (type == TOK_PLUS)? "+" :
        (type == TOK_MINUS)? "-" :
        (type == TOK_STAR)? "*" :
        (type == TOK_SLASH)? "/" :
        (type == TOK_PERCENT)? "%" :
        (type == TOK_NOT_OPER)? "NOT_OPER" :
        (type == TOK_NAMESPACE)? "namespace" :
        (type == TOK_OCBRACE)? "{" :
        (type == TOK_CCBRACE)? "}" :
        (type == TOK_CLASS)? "class" :
        (type == TOK_PLUS_EQUAL)? "+=" :
        (type == TOK_MINUS_EQUAL)? "-=" :
        (type == TOK_STAR_EQUAL)? "*=" :
        (type == TOK_SLASH_EQUAL)? "/=" :
        (type == TOK_PERCENT_EQUAL)? "%=" :
        (type == TOK_INLINE)? "INLINE" :
        (type == TOK_BREAK)? "break" :
        (type == TOK_CONTINUE)? "continue" :
        (type == TOK_YIELD)? "yield" :
        (type == TOK_TYPE)? "type" :
        (type == TOK_RETURN)? "return" :
        (type == TOK_RAISE)? "raise" :
        (type == TOK_TRACE)? "trace" :
        (type == TOK_PRINT)? "print" :
        (type == TOK_EXIT)? "exit" :
        (type == TOK_WHILE)? "while" :
        (type == TOK_DO)? "do" :
        (type == TOK_FOR)? "for" :
        (type == TOK_IF)? "if" :
        (type == TOK_ELSE)? "else" :
        (type == TOK_TRY)? "try" :
        (type == TOK_EXCEPT)? "except" :
        (type == TOK_FINAL)? "final" :
        (type == TOK_COMMENT)? "COMMENT" :
        "UNKNOWN";
}

