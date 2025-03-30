#!/usr/bin/env python3
'''
This script reads in a grammar file and emits templates for a parser and and
AST. It does not attempt to actually generate the code. If this is run in the
actual source tree, it will destroy all edits.
'''

import re
import time
import os
import sys

tokens = []
non_terminals = []
terminals = []
keywords = []
translate = []
srules = {}
grules = {}
rule_name = ""
grammar = []

def convert(str):

    s = "TOK"
    for c in str:
        if c == '!': s += "_BANG"
        elif c == '@': s += "_AT"
        elif c == '#': s += "_HASH"
        elif c == '$': s += "_DOLLAR"
        elif c == '%': s += "_PERCENT"
        elif c == '^': s += "_CARAT"
        elif c == '&': s += "_AMPERSAND"
        elif c == '*': s += "_STAR"
        elif c == '(': s += "_OPAREN"
        elif c == ')': s += "_CPAREN"
        elif c == '-': s += "_MINUS"
        elif c == '=': s += "_EQUAL"
        elif c == '+': s += "_PLUS"
        elif c == '[': s += "_OSBRACE"
        elif c == ']': s += "_CSBRACE"
        elif c == '{': s += "_OCBRACE"
        elif c == '}': s += "_CCBRACE"
        elif c == '\\': s += "_BSLASH"
        elif c == ':': s += "_COLON"
        elif c == ';': s += "_SEMICOLON"
        elif c == '\'': s += "_SQUOTE"
        elif c == '\"': s += "_DQUOTE"
        elif c == ',': s += "_COMMA"
        elif c == '<': s += "_OPBRACE"
        elif c == '.': s += "_DOT"
        elif c == '>': s += "_CPBRACE"
        elif c == '/': s += "_SLASH"
        elif c == '?': s += "_QUESTION"
        elif c == '~': s += "_TILDE"
    return s

def get_srule(fp, name):
    srules[name] = []
    for line in fp:
        line = line.strip()
        if line[0] == ':' or line[0] == '|':
            srules[name].append(line[1:].strip())
        elif line[0] == ';':
            break

def get_grule(fp, name):
    non_terminals.append(name)
    grules[name] = []
    for line in fp:
        line = line.strip()
        if line[0] == ':' or line[0] == '|':
            grules[name].append("    %s"%(line))
            res = re.findall(r"\'([^\']+)\'|\"([^\"]+)\"", line)
            for mat in res:
                if len(mat[0]) != 0:
                    tmp = mat[0]
                elif len(mat[1]) != 0:
                    tmp = mat[1]

                if not tmp in terminals:
                    terminals.append(tmp)

                if re.match(r"[a-z_]+", tmp):
                    if not tmp in keywords:
                        keywords.append(tmp)
                    s = "TOK_%s"%(tmp.upper())
                else:
                    s = convert(tmp)

                if not s in tokens:
                    tokens.append(s)
                    translate.append("(type == %s)? \"%s\" :"%(s, tmp))

            res = re.findall(r"([A-Z_]+)", line)
            for mat in res:
                if mat != "_":
                    s = "TOK_"+mat
                    if not s in tokens:
                        tokens.append(s)
                        translate.append("(type == %s)? \"%s\" :"%(s, mat))

        elif line[0] == ';':
            grules[name].append("    ;\n")
            break

def gen_lists(fname):

    with open(fname, "r") as fp:
        for line in fp :
            line = line.strip()
            if len(line) > 0 and line[0] != '#' :
                grammar.append(line)
                if re.match(r"[A-Z_]+", line):
                    get_srule(fp, line)
                elif re.match(r"[a-z_]+", line):
                    get_grule(fp, line)
                else:
                    print("unknown line ignored: ", line.strip())

    #terminals.sort()
    #non_terminals.sort()
    #tokens.sort()

def gen_ast():

    with open("ast/ast.h", "w") as fp:
        fp.write("/**\n *\n")
        fp.write(" * @file ast.h\n *\n")
        fp.write(" * @brief AST traverse public interface.\n")
        fp.write(" * This file was generated on %s.\n"%(time.asctime()))
        fp.write(" *\n */\n")
        fp.write("\n#ifndef _AST_H_\n#define _AST_H_\n\n")

        fp.write("typedef enum {\n")
        for str in grules:
            fp.write("    AST_%s,\n"%(str.upper()))
        fp.write("} ast_node_type_t;\n\n")

        fp.write("typedef struct _ast_node_ {\n")
        fp.write("    ast_node_type_t type;\n")
        fp.write("} ast_node_t;\n\n")

        for str in grules:
            fp.write("/**\n")
            fp.write(" * %s\n"%(str))
            for s in grules[str]:
                fp.write(" * %s\n"%(s))
            fp.write(" */\n")
            fp.write("typedef struct _ast_%s_t_ {\n"%(str))
            fp.write("    ast_node_t node;\n\n")
            fp.write("} ast_%s_t;\n\n"%(str))

        for str in grules:
            fp.write("void traverse_%s(ast_%s_t* node);\n"%(str, str))

        fp.write("\nast_node_t* create_ast_node(ast_node_type_t type);\n")
        fp.write("void traverse_ast(ast_%s_t* node);\n\n"%(non_terminals[0]))
        fp.write("\n#endif /* _AST_H_ */\n\n")

    with open("ast/ast.c", "w") as fp:
            fp.write("/**\n *\n")
            fp.write(" * @file %s.c\n *\n"%(str))
            fp.write(" * @brief AST implementation.\n")
            fp.write(" * This file was generated on %s.\n"%(time.asctime()))
            fp.write(" *\n */\n")
            fp.write("#include <stddef.h>\n\n")

            fp.write("#include \"ast.h\"\n\n")
            fp.write("static size_t node_size(ast_node_type_t type) {\n\n")
            fp.write("    return\n")
            for str in grules:
                fp.write("    (type == AST_%s)? sizeof(ast_%s_t) : \n"%(str.upper(), str))
            fp.write("    (size_t)-1; // error if we reach here\n")
            fp.write("}\n\n")
            fp.write("ast_node_t* create_ast_node(ast_node_type_t type) {\n\n")
            fp.write("    ast_node_t* node = _ALLOC(node_size(type));\n")
            fp.write("    node->type = type;\n")
            fp.write("    return node;\n")
            fp.write("}\n\n")
            fp.write("void traverse_ast(ast_%s_t* node) {\n\n"%(non_terminals[0]))
            fp.write("    traverse_%s(node);\n"%(non_terminals[0]))
            fp.write("}\n\n")

    for str in grules:
        with open("ast/%s.c"%(str), "w") as fp:
            fp.write("/**\n *\n")
            fp.write(" * @file %s.c\n *\n"%(str))
            fp.write(" * @brief Traverse AST for node %s.\n"%(str))
            fp.write(" * This file was generated on %s.\n"%(time.asctime()))
            fp.write(" *\n */\n")
            fp.write("#include \"ast.h\"\n")
            fp.write("#include \"trace.h\"\n\n")
            fp.write("/**\n")
            fp.write(" * %s\n"%(str))
            for s in grules[str]:
                fp.write(" * %s\n"%(s))
            fp.write(" */\n")
            fp.write("void traverse_%s(ast_%s_t* node) {\n\n"%(str, str))
            fp.write("    ENTER;\n")
            fp.write("    RETURN();\n")
            fp.write("}\n\n")

def gen_parse():

    with open("parser/parser.h", "w") as fp:
        fp.write("/**\n *\n")
        fp.write(" * @file parser.h\n *\n")
        fp.write(" * @brief Parse grammar public interface.\n")
        fp.write(" * This file was generated on %s.\n"%(time.asctime()))
        fp.write(" *\n */\n")
        fp.write("#ifndef _PARSER_H_\n#define _PARSER_H_\n\n")

        fp.write("#include \"ast.h\"\n")
        fp.write("#include \"parser_prototypes.h\"\n\n")

        fp.write("typedef enum {\n")
        fp.write("    STATE_START = 0,\n")
        fp.write("    STATE_MATCH = 1000,\n")
        fp.write("    STATE_NO_MATCH = 1010,\n")
        fp.write("    STATE_ERROR = 1020,\n")
        fp.write("} parser_state_t;\n")

        fp.write("typedef struct {\n")
        fp.write("    int mode;\n")
        fp.write("} parser_state_t;\n\n")
        #fp.write("void recover_error(void);\n")

        fp.write("#define STATE \\ \n")
        fp.write("    do { \\ \n")
        fp.write("        TRACE(\"STATE: %d\", state); \\ \n")
        fp.write("    } while(0)\n\n")

        fp.write("ast_%s_t* parse(void);\n\n"%(non_terminals[0]))

        fp.write("#endif /* _PARSER_H_ */\n\n")

    with open("parser/parser_prototypes.h", "w") as fp:
        fp.write("/**\n *\n")
        fp.write(" * @file parser_prototypes.h\n *\n")
        fp.write(" * @brief Internal prototypes for parser.\n")
        fp.write(" * This file was generated on %s.\n"%(time.asctime()))
        fp.write(" *\n */\n")
        fp.write("#ifndef _PARSER_PROTOTYPES_H_\n#define _PARSER_PROTOTYPES_H_\n\n")
        fp.write("#include \"parser.h\"\n")
        fp.write("#include \"ast.h\"\n\n")
        for str in grules:
            fp.write("ast_%s_t* parse_%s(void);\n"%(str, str))
        fp.write("\n#endif /* _PARSER_PROTOTYPES_H_ */\n\n")

    with open("parser/parser.c", "w") as fp:
        fp.write("/**\n *\n")
        fp.write(" * @file parser.c\n *\n")
        fp.write(" * @brief Parser external interface implementation.\n")
        fp.write(" * This file was generated on %s.\n"%(time.asctime()))
        fp.write(" *\n */\n")
        fp.write("#include \"ast.h\"\n")
        fp.write("#include \"parser_prototypes.h\"\n\n")
        #fp.write("#include \"trace.h\"\n\n")
        #fp.write("void recover_error(void) {\n\n")
        #fp.write("}\n\n")
        fp.write("ast_%s_t* parse(void) {\n\n"%(non_terminals[0]))
        #fp.write("    parser_state_t* pstate = _ALLOC_DS(parser_state_t);\n")
        #fp.write("    pstate->mode = 0;\n")
        fp.write("    ast_%s_t* %s = parse_%s();\n"%(non_terminals[0], non_terminals[0], non_terminals[0]))
        fp.write("    return %s;\n"%(non_terminals[0]))
        fp.write("}\n\n")

    for str in grules:
        with open("parser/%s.c"%(str), "w") as fp:
            fp.write("/**\n *\n")
            fp.write(" * @file %s.c\n *\n"%(str))
            fp.write(" * @brief Parse grammar production %s.\n"%(str))
            fp.write(" * This file was generated on %s.\n"%(time.asctime()))
            fp.write(" *\n */\n")
            #fp.write("#include \"common.h\"\n")
            fp.write("#include \"tokens.h\"\n")
            fp.write("#include \"trace.h\"\n")
            fp.write("#include \"parser.h\"\n\n")
            fp.write("/**\n")
            fp.write(" * %s\n"%(str))
            for s in grules[str]:
                fp.write(" * %s\n"%(s))
            fp.write(" */\n")
            fp.write("ast_%s_t* parse_%s(void) {\n\n"%(str, str))
            #fp.write("    ASSERT(pstate != NULL);\n")
            fp.write("    ENTER;\n\n")
            fp.write("    ast_%s_t* node = NULL;\n"%(str))
            fp.write("    int state = STATE_START;\n")
            fp.write("    bool finished = false;\n")
            fp.write("    void* post = post_token_queue();\n\n")
            fp.write("    while(!finished) {\n")
            fp.write("        switch(state) {\n")
            fp.write("            case STATE_START:\n")
            fp.write("                // initial state\n")
            fp.write("                STATE;\n")
            fp.write("                break;\n\n")
            fp.write("            case STATE_MATCH:\n")
            fp.write("                // production recognized\n")
            fp.write("                STATE;\n")
            fp.write("                node = (ast_%s_t*)create_ast_node(AST_%s);\n"%(str, str.upper()))
            fp.write("                finished = true;\n")
            fp.write("                break;\n\n")
            fp.write("            case STATE_NO_MATCH:\n")
            fp.write("                // not a match, not an error\n")
            fp.write("                STATE;\n")
            fp.write("                reset_token_queue(post);\n")
            fp.write("                finished = true;\n")
            fp.write("                break;\n\n")
            fp.write("            case STATE_ERROR:\n")
            fp.write("                // error found\n")
            fp.write("                STATE;\n")
            fp.write("                recover_error();\n")
            fp.write("                finished = true;\n")
            fp.write("                break;\n\n")
            fp.write("            default:\n")
            fp.write("                FATAL(\"unknown state: %d\", state);\n")
            fp.write("        }\n")
            fp.write("    }\n\n")
            fp.write("    RETURN(node);\n")
            fp.write("}\n\n")

def gen_scanner():

    with open("scanner/tokens.h", "w") as fp:
        fp.write("/**\n *\n")
        fp.write(" * @file token_defs.h\n *\n")
        fp.write(" * @brief Token definitions public interface.\n")
        fp.write(" * This file was generated on %s.\n"%(time.asctime()))
        fp.write(" *\n */\n")
        fp.write("#ifndef _TOKEN_DEFS_H_\n")
        fp.write("#define _TOKEN_DEFS_H_\n\n")

        fp.write("#include <stdint.h>\n\n")

        fp.write("typedef enum {\n")
        for item in tokens:
            fp.write("    %s,\n"%(item))

        fp.write("\n    TOK_END_OF_INPUT,\n")
        fp.write("    TOK_END_OF_FILE,\n")
        fp.write("    TOK_ERROR,\n")
        fp.write("} token_type_t;\n\n")

        fp.write("typedef struct _token_t_ {\n")
        fp.write("    token_type_t type;\n")
        fp.write("    const char* raw;\n")
        fp.write("    const char* fname;\n")
        fp.write("    int line_no;\n")
        fp.write("    int col_no;\n")
        fp.write("    union {\n")
        fp.write("        int64_t count;\n")
        fp.write("        double real;\n")
        fp.write("        unsigned char boolean;\n")
        fp.write("        const char* text;\n")
        fp.write("        void* other;\n")
        fp.write("    } value;\n")
        fp.write("    struct _token_t_* next;\n")
        fp.write("} token_t;\n\n")

        fp.write("void init_token_queue(const char* fname);\n")
        fp.write("void* post_token_queue(void);\n")
        fp.write("void reset_token_queue(void* post);\n")
        fp.write("void consume_token_queue(void);\n\n")

        fp.write("token_t* create_token(const char* str, token_type_t type);\n")
        fp.write("token_t* get_token(void);\n")
        fp.write("token_t* advance_token(void);\n")
        fp.write("const char* token_type_to_str(token_type_t type);\n\n")

        fp.write("#endif /* _TOKEN_DEFS_H_ */\n\n")

    with open("scanner/tokens.c", "w") as fp:
        fp.write("/**\n *\n")
        fp.write(" * @file token_defs.c\n *\n")
        fp.write(" * @brief Token definition implementation.\n")
        fp.write(" * This file was generated on %s.\n"%(time.asctime()))
        fp.write(" *\n */\n")
        fp.write("#include <stdio.h>\n")
        fp.write("#include <strings.h>\n\n")
        fp.write("#include \"tokens.h\"\n")

        fp.write("const char* token_type_to_str(token_type_t type) {\n\n")
        fp.write("    return ")
        fp.write("%s\n"%(translate[0]))
        for item in translate[1:]:
            fp.write("        %s\n"%(item))
        fp.write("        \"UNKNOWN\";\n")
        fp.write("}\n\n")

def generate() :

    if not os.path.isdir('ast'):
        os.mkdir('ast')
    if not os.path.isdir('parser'):
        os.mkdir('parser')
    if not os.path.isdir('scanner'):
        os.mkdir('scanner')

    gen_ast()
    gen_parse()
    gen_scanner()


if __name__ == '__main__':

    # print("Before you run this, know that it will destroy the parser")
    # print("and all of the manual changes that were made to it.")
    # exit(1)

    if(len(sys.argv) < 2) :
        sys.stderr.write("%s: file name required\n"%(sys.argv[0]))
        exit(1)

    gen_lists(sys.argv[1])

    count = 0
    with open("non-terminals.txt", "w") as fp:
        for item in non_terminals:
            fp.write("%s\n"%(item))
            count += 1
    print("non-terminals:", count)

    count = 0
    with open("terminals.txt", "w") as fp:
        for item in terminals:
            fp.write("%s\n"%(item))
            count += 1

    print("terminals:", count)

    count = 0
    with open("keywords.txt", "w") as fp:
        for item in keywords:
            fp.write("%s\n"%(item))
            count += 1

    print("keywords:", count)

    count = 0
    with open("tokens.txt", "w") as fp:
        for item in tokens:
            fp.write("%s\n"%(item))
            count += 1

    print("tokens:", count)

    count = 0
    with open("srules.txt", "w") as fp:
        for item in srules:
            fp.write("%s\n    "%(item))
            t = ""
            l = len(srules[item])
            for i, x in enumerate(srules[item]):
                fp.write("%s"%(x))
                if i+1 < l:
                    fp.write("|")
            count += 1
            fp.write("\n")

    print("srules:", count)

    generate()
