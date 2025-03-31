/**
 *
 * @file tokens.c
 *
 * @brief Token queue implementation.
 * This file was generated on Mon Mar 31 11:23:05 2025.
 *
 */


#include <stdio.h>
#include <strings.h>

#include "tokens.h"
#include "scanner.h"
#include "queue.h"
#include "fileio.h"
#include "alloc.h"

queue_t* token_queue = NULL;

void init_token_queue(const char* fname) {

    if(token_queue == NULL)
        token_queue = _ALLOC_TYPE(queue_t);

    open_file(fname);
    yylex();
}

void* post_token_queue(void) {

    return (void*)token_queue->crnt;
}

void reset_token_queue(void* post) {

    token_queue->crnt = (queue_element_t*)post;
}

void consume_token_queue(void) {

    queue_element_t* next;
    for(queue_element_t* elem = token_queue->head; elem != token_queue->crnt; elem = next) {
        next = elem->next;
        destroy_token(elem->data);
        _FREE(elem);
    }
}

void add_token_queue(token_t* tok) {

    add_queue(token_queue, (void*)tok);
}

token_t* create_token(const char* str, token_type_t type) {

    token_t* tok = _ALLOC_TYPE(token_t);
    tok->type = type;
    tok->raw = create_string_buf(str);
    tok->line_no = get_line_no();
    tok->col_no = get_col_no();
    tok->fname = create_string_buf(get_file_name());

    return tok;
}

void destroy_token(token_t* tok) {

    if(tok != NULL) {
        if(tok->raw != NULL)
            destroy_string_buf(tok->raw);
        if(tok->fname != NULL)
            destroy_string_buf(tok->fname);

        _FREE(tok);
    }
}

token_t* get_token(void) {

    if(token_queue != NULL) {
        return peek_queue(token_queue);
    }
    else
        return NULL;
}

token_t* advance_token(void) {

    token_t* tok = advance_queue(token_queue);
    if(tok == NULL) {
        tok = get_token();
        if(tok->type != TOK_END_OF_INPUT) {
            if(yylex() == 0)
                add_token_queue(create_token("end of input", TOK_END_OF_INPUT));

            token_queue->crnt = token_queue->tail;
            tok = get_token();
        }
    }

    return tok;
}

const char* token_type_to_str(token_type_t type) {

    return (type == TOK_START)? "start" :
        (type == TOK_IMPORT)? "import" :
        (type == TOK_AS)? "as" :
        (type == TOK_IDENTIFIER)? "IDENTIFIER" :
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

        (type == TOK_END_OF_INPUT)? "END OF INPUT" :
        (type == TOK_END_OF_FILE)? "END OF FILE" :
        (type == TOK_ERROR)? "ERROR" : "UNKNOWN";
}

