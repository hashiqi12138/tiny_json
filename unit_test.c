//
// Created by liujie on 2020/6/1.
//
#include "token_link_list.h"
#include "tokenizer.h"
#include <stdio.h>

void test_token_link_list() {
    TOKEN * root = create_link_list();
    TOKEN token_first, token_second;
    token_first.next = NULL;
    token_first.token_type = BEGIN_ARRAY;
    token_first.start_index = 1;
    token_first.end_index = 2;

    token_second.next = NULL;
    token_second.token_type = END_ARRAY;
    token_second.start_index = 5;
    token_second.end_index = 6;

    push_to_list(root, &token_first);
    push_to_list(root, &token_second);

    to_string(root);

    getchar();
}

void test_tokenizer() {
//    printf("test tokenizer >>> \n");
//    char* json = "{\"a\":1,\"b\":\"string\",\"c\": [{\"c\" : false, \"d\": null}]}";
//    TOKEN * token = parseStringToTokens(json);
//    to_string(token);
//    free_token_list(token);
//    getchar();
//
//    printf("test tokenizer simple json >>> \n");
//    char* json_simple = "{  }";
//    TOKEN * token_simple = parseStringToTokens(json_simple);
//    to_string(token_simple);
//    free_token_list(token_simple);
//    getchar();

    printf("test tokenizer complex json >>> \n");
    char* json_complex = "{\"errno\":0,\"tk\":\"258cdafa18b96daa17ec7546665354656346654\",\"isFavorite\":false}";
    TOKEN * token_complex = parseStringToTokens("{\"errno\":0,\"tk44444444456415645465465455\":\"258cdafa1fdaf8b96daa1\",\"isFavorite\":false}");
    to_string(token_complex);
    free_token_list(token_complex);
    getchar();
}