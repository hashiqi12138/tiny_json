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
    printf("test tokenizer >>> \n");
    char* json = "{\"a\":1,\"b\":\"string\",\"c\": [{\"c\" : false}]}";
    TOKEN * token = parseStringToTokens(json);
    to_string(token);
    free_token_list(token);
    getchar();
}