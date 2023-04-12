#include <sys/times.h>
#include <time.h>
#include "grammar/grammar_populator/constructor.h"
#include "compiler/symbol_table/constructor/symbol_table_constructor.h"
#include "parser.h"
#include "lexer_constructor.h"
#include "ast.h"
#include "compiler/symbol_table/constructor/symbol_table_constructor.h"
#include "compiler/semantic_analyzer/semantic_analyzer.h"
#include "compiler/code_generator/code_generator.h"

char *state_to_token_path = "files/lexer_files/mini_id_to_token_type.txt";
char *edges_path = "files/lexer_files/mini_edges.txt";
char *ac_retract_path = "files/lexer_files/mini_accept_retract_other.txt";
char *state_to_error = "files/lexer_files/state_to_error.txt";

static void driver(char *src, char *asm_file);

static void handle_ast_compression_info_request(char *src);

static void handle_code_generation_request(char *src, char *asm_file);

static void handle_error_reporting_and_time_request(char *src);

static void handle_parser_request(char *src);

static void handle_array_printing(char *src);

static void handle_ast_request(char *src);

static void handle_print_symbol_table(char *src);

static void handle_lexer_request(char *src);

static void handle_activation_record_printing(char *src);

static void print_menu();

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Execution Syntax ./compiler testcase.txt code.asm");
        exit(-1);
    }
    char *src = argv[1];
    char *asm_out = argv[2];
    driver(src, asm_out);
    return 0;
}

static void driver(char *src, char *asm_file) {
    while (true) {
        print_menu();
        int choice;
        puts("Enter your choice, 0 for exit");
        scanf("%d", &choice);
        switch (choice) {
            case 0: {
                exit(0);
            }
            case 1: {
                handle_lexer_request(src);
                continue;
            }
            case 2: {
                handle_parser_request(src);
                continue;
            }
            case 3: {
                handle_ast_request(src);
                continue;
            }
            case 4: {
                handle_ast_compression_info_request(src);
                continue;
            }
            case 5: {
                handle_print_symbol_table(src);
                continue;
            }
            case 6: {
                handle_activation_record_printing(src);
                continue;
            }
            case 7: {
                handle_array_printing(src);
            }
            case 8: {
                handle_error_reporting_and_time_request(src);
                continue;
            }
            case 9: {
                handle_code_generation_request(src, asm_file);
                continue;
            }
            default: {
                puts("Invalid Request. Retry");
                continue;
            }
        }
    }
}

static void print_menu() {
    puts("0. To exit from the loop");

    puts("1. Lexer: For printing the token list generated by the lexer (on the console)");

    puts("2. Parser: For parsing to verify the syntactic correctness of the input source code and to produce parse tree (On Console)");

    puts("3. AST: For printing the Abstract Syntax Tree in appropriate format. Also specify the traversal order at the beginning. (On Console)");

    puts("4. Memory: For displaying the amount of allocated memory and number of nodes to each of parse tree and abstract syntax tree for the test case used."
         " The format should be as per the example given below");

    puts("5. Symbol Table: For printing the Symbol Table");

    puts("6. Activation record size (fixed, excluding system related):");

    puts("7. Static and dynamic arrays: For printing the type expressions and width of array variables in a "
         "line for a test case for the following information.");

    puts("8. Errors reporting and total compiling time:");

    puts("9. Code generation:");
}

static void handle_lexer_request(char *src) {
    const Grammar *g = get_initialized_grammar("/Users/wint/code/compiler/files/grammar_files/mini_productions.txt");
    Parser *parser = get_initialized_parser(g);
    Lexer *lexer = get_initialized_lexer_for_parser(parser, src, state_to_token_path, edges_path,
                                                    ac_retract_path,
                                                    state_to_token_path, state_to_error, 1024);
    parser->lexer = lexer;
    set_string_to_token_type_map_for_lexer(lexer, parser->grammar->string_to_terminal_map);
    initialize_parser_symbol_table(parser);
    grant_symbol_table_to_lexer(parser->lexer, parser->symbol_table);
    run_lexer_independently_on_and_print_to(lexer, stdout);
}

static void handle_parser_request(char *src) {
    const Grammar *g = get_initialized_grammar("/Users/wint/code/compiler/files/grammar_files/mini_productions.txt");
    Parser *parser = get_initialized_parser(g);
    Lexer *lexer = get_initialized_lexer_for_parser(parser, src, state_to_token_path, edges_path,
                                                    ac_retract_path,
                                                    state_to_token_path, state_to_error, 1024);
    parser->lexer = lexer;
    set_string_to_token_type_map_for_lexer(lexer, parser->grammar->string_to_terminal_map);
    initialize_parser_symbol_table(parser);
    grant_symbol_table_to_lexer(parser->lexer, parser->symbol_table);
    ParseTree *parse_tree = construct_parse_tree(parser);
    print_parse_tree(parser, parse_tree, stdout);
}

static void handle_ast_request(char *src) {
    const Grammar *g = get_initialized_grammar("/Users/wint/code/compiler/files/grammar_files/mini_productions.txt");
    Parser *parser = get_initialized_parser(g);
    Lexer *lexer = get_initialized_lexer_for_parser(parser, src, state_to_token_path, edges_path,
                                                    ac_retract_path,
                                                    state_to_token_path, state_to_error, 1024);
    parser->lexer = lexer;
    set_string_to_token_type_map_for_lexer(lexer, parser->grammar->string_to_terminal_map);
    initialize_parser_symbol_table(parser);
    grant_symbol_table_to_lexer(parser->lexer, parser->symbol_table);
    ParseTree *parse_tree = construct_parse_tree(parser);
    ProgramNode *program_node_root = parse_tree->got_syntax_error ? NULL : parse_tree->program_node;
    if (program_node_root != NULL) {
        construct_symbol_table(program_node_root);
        perform_semantic_analysis(program_node_root, program_node_root->global_symbol_table);
        puts("***************************Printing AST: Traversal Order: Preorder***************************");
        print_ast_node((const ASTNode *) program_node_root, 0);
    } else {
        puts("Failed to construct AST due to Syntax Errors");
    }
}

static void handle_ast_compression_info_request(char *src) {
    const Grammar *g = get_initialized_grammar("/Users/wint/code/compiler/files/grammar_files/mini_productions.txt");
    Parser *parser = get_initialized_parser(g);
    int buffer_size = 1024;
    Lexer *lexer = get_initialized_lexer_for_parser(parser, src, state_to_token_path, edges_path,
                                                    ac_retract_path,
                                                    state_to_token_path, state_to_error, buffer_size);
    parser->lexer = lexer;
    set_string_to_token_type_map_for_lexer(lexer, parser->grammar->string_to_terminal_map);
    initialize_parser_symbol_table(parser);
    // print_symbol_table(interface->symbol_table);
    grant_symbol_table_to_lexer(parser->lexer, parser->symbol_table);
    get_parse_tree(parser);
    printf("Parse Tree Number of Nodes = %d, Allocated Memory = %d\n", parse_tree_number_of_nodes,
           parse_tree_allocated_memory);
    printf("AST Number of Nodes = %d, Allocated Memory = %d\n", ast_number_of_nodes,
           ast_allocated_memory);
    double compression_percentage =
            ((double) (parse_tree_allocated_memory - ast_allocated_memory)) / ((double) (parse_tree_allocated_memory));
    compression_percentage = compression_percentage * 100;
    printf("Compression Percentage = %lf\n", compression_percentage);
}

static void handle_print_symbol_table(char *src) {
    const Grammar *g = get_initialized_grammar("/Users/wint/code/compiler/files/grammar_files/mini_productions.txt");
    Parser *parser = get_initialized_parser(g);
    Lexer *lexer = get_initialized_lexer_for_parser(parser, src, state_to_token_path, edges_path,
                                                    ac_retract_path,
                                                    state_to_token_path, state_to_error, 1024);
    parser->lexer = lexer;
    set_string_to_token_type_map_for_lexer(lexer, parser->grammar->string_to_terminal_map);
    initialize_parser_symbol_table(parser);
    grant_symbol_table_to_lexer(parser->lexer, parser->symbol_table);
    ParseTree *parse_tree = construct_parse_tree(parser);
    ProgramNode *program_node_root = parse_tree->got_syntax_error ? NULL : parse_tree->program_node;
    if (program_node_root != NULL) {
        construct_symbol_table(program_node_root);
        perform_semantic_analysis(program_node_root, program_node_root->global_symbol_table);
        puts("*************************** Printing Symbol Table***************************");
        print_symbol_table_as_required(program_node_root->global_symbol_table);
    } else {
        puts("Failed to construct AST due to Syntax Errors");
    }
}

static void handle_activation_record_printing(char *src) {
    const Grammar *g = get_initialized_grammar("/Users/wint/code/compiler/files/grammar_files/mini_productions.txt");
    Parser *parser = get_initialized_parser(g);
    Lexer *lexer = get_initialized_lexer_for_parser(parser, src, state_to_token_path, edges_path,
                                                    ac_retract_path,
                                                    state_to_token_path, state_to_error, 1024);
    parser->lexer = lexer;
    set_string_to_token_type_map_for_lexer(lexer, parser->grammar->string_to_terminal_map);
    initialize_parser_symbol_table(parser);
    grant_symbol_table_to_lexer(parser->lexer, parser->symbol_table);
    ParseTree *parse_tree = construct_parse_tree(parser);
    ProgramNode *program_node_root = parse_tree->got_syntax_error ? NULL : parse_tree->program_node;
    if (program_node_root != NULL) {
        construct_symbol_table(program_node_root);
        perform_semantic_analysis(program_node_root, program_node_root->global_symbol_table);
        puts("*************************** Printing Activation Record Sizes***************************");
        SymbolTable *global_symbol_table = program_node_root->global_symbol_table;
        for (int i = 0; i < global_symbol_table->capacity; ++i) {
            SymbolTableEntry *symbol_table_entry = global_symbol_table->records[i];
            if (symbol_table_entry == NULL) continue;
            SymbolTable *module_symbol_table = symbol_table_entry->type_descriptor.function_type.symbol_table;
            printf("%s:%d\n", symbol_table_entry->name, module_symbol_table->total_data_size);
        }
    } else {
        puts("Failed to construct AST due to Syntax Errors");
    }
    puts("");
}

static void handle_array_printing(char *src) {
    const Grammar *g = get_initialized_grammar("/Users/wint/code/compiler/files/grammar_files/mini_productions.txt");
    Parser *parser = get_initialized_parser(g);
    Lexer *lexer = get_initialized_lexer_for_parser(parser, src, state_to_token_path, edges_path,
                                                    ac_retract_path,
                                                    state_to_token_path, state_to_error, 1024);
    parser->lexer = lexer;
    set_string_to_token_type_map_for_lexer(lexer, parser->grammar->string_to_terminal_map);
    initialize_parser_symbol_table(parser);
    grant_symbol_table_to_lexer(parser->lexer, parser->symbol_table);
    ParseTree *parse_tree = construct_parse_tree(parser);
    ProgramNode *program_node_root = parse_tree->got_syntax_error ? NULL : parse_tree->program_node;
    if (program_node_root != NULL) {
        construct_symbol_table(program_node_root);
        perform_semantic_analysis(program_node_root, program_node_root->global_symbol_table);
        puts("*************************** Printing Arrays ***************************");
        print_array_variable_entry(program_node_root->global_symbol_table);
    } else {
        puts("Failed to construct AST due to Syntax Errors");
    }
    puts("");
}

static void handle_error_reporting_and_time_request(char *src) {
    clock_t begin = clock();
    const Grammar *g = get_initialized_grammar("/Users/wint/code/compiler/files/grammar_files/mini_productions.txt");
    Parser *parser = get_initialized_parser(g);
    Lexer *lexer = get_initialized_lexer_for_parser(parser, src, state_to_token_path, edges_path,
                                                    ac_retract_path,
                                                    state_to_token_path, state_to_error, 1024);
    parser->lexer = lexer;
    set_string_to_token_type_map_for_lexer(lexer, parser->grammar->string_to_terminal_map);
    initialize_parser_symbol_table(parser);
    grant_symbol_table_to_lexer(parser->lexer, parser->symbol_table);
    ParseTree *parse_tree = construct_parse_tree(parser);
    ProgramNode *program_node_root = parse_tree->got_syntax_error ? NULL : parse_tree->program_node;
    if (program_node_root != NULL) {
        construct_symbol_table(program_node_root);
        perform_semantic_analysis(program_node_root, program_node_root->global_symbol_table);
    } else {
        puts("Failed to construct AST due to Syntax Errors");
    }
    clock_t end = clock();
    size_t ticks = end - begin;
    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("CPU Time executed to compile the program (System dependent) =  %f seconds and %zu ticks\n",
           time_spent, ticks);
    puts("");
}

static void handle_code_generation_request(char *src, char *asm_file) {
    const Grammar *g = get_initialized_grammar("/Users/wint/code/compiler/files/grammar_files/mini_productions.txt");
    Parser *parser = get_initialized_parser(g);
    Lexer *lexer = get_initialized_lexer_for_parser(parser, src, state_to_token_path, edges_path,
                                                    ac_retract_path,
                                                    state_to_token_path, state_to_error, 1024);
    parser->lexer = lexer;
    set_string_to_token_type_map_for_lexer(lexer, parser->grammar->string_to_terminal_map);
    initialize_parser_symbol_table(parser);
    grant_symbol_table_to_lexer(parser->lexer, parser->symbol_table);
    ParseTree *parse_tree = construct_parse_tree(parser);
    ProgramNode *program_node_root = parse_tree->got_syntax_error ? NULL : parse_tree->program_node;
    if (program_node_root != NULL) {
        construct_symbol_table(program_node_root);
        perform_semantic_analysis(program_node_root, program_node_root->global_symbol_table);
        if (!GOT_SEMANTIC_ERROR_GLOBAL) {
            generate_code_from(program_node_root, asm_file);
        } else {
            puts("Failed to generate code due to Semantic Errors");
        }
    } else {
        puts("Failed to construct AST/AssemblyCode due to Syntax Errors");
    }
}