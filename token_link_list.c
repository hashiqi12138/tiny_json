//
// Created by liujie52 on 2020/12/21.
//

#include <stdio.h>
#include <string.h>
#include "token_link_list.h"

TOKEN* create_link_list() {
    TOKEN * token = malloc(sizeof(TOKEN));
    token->next = NULL;
    if (token == NULL) {
        exit(EXIT_FAILURE);
    }
    return token;
}

OPERATION_RESULT push_to_list(TOKEN* root, TOKEN* to_insert) {
    OPERATION_RESULT result;
    TOKEN * temp;
    result.status = 1;
    result.msg = "success";
    temp = root;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = to_insert;
    temp = NULL;
    return result;
}

OPERATION_RESULT pop_from_list(TOKEN* root) {
    OPERATION_RESULT result;
    TOKEN * temp;
    TOKEN * parent;
    if (root->next == NULL) {
        result.msg = "Cannot pop from an empty list";
        result.status = 0;
        return result;
    }
    parent = NULL;
    temp = root;
    while (temp->next != NULL) {
        parent = temp;
        temp = temp->next;
    }
    parent->next = NULL;
    free(temp->value);
    temp->value = NULL;
    free(temp);
    result.status = 1;
    result.msg = "success";
    return result;
}

OPERATION_RESULT free_token_list(TOKEN* root) {
    while (root->next != NULL) {
        pop_from_list(root);
    }
    free(root);
};

void to_string(TOKEN* root) {
    TOKEN * temp;
    temp = root->next;
    while (temp != NULL) {
        printf("token type is [ %s ], start index [ %d ], end index [ %d ], value is [ %s ]\n",
               get_token_type_name(temp->token_type), temp->start_index, temp->end_index, temp->value);
        temp = temp->next;
    }
};


char* get_token_type_name(TOKEN_TYPE type) {
    switch (type) {
        case BEGIN_OBJECT:
            return "{";
        case END_OBJECT:
            return "}";
        case BEGIN_ARRAY:
            return "[";
        case END_ARRAY:
            return "]";
        case Null:
            return "null";
        case NUMBER:
            return "number";
        case STRING:
            return "string";
        case BOOLEAN:
            return "bool";
        case SEP_COMMA:
            return ",";
        case SEP_COLON:
            return ":";
        default:
            return "unknown";
    }
}

void get_token_value (const char* json_string, TOKEN* token) {
    token->value = NULL;
    int index = 0;
    int length = token->end_index - token->start_index + 1;
    token->value = malloc(length);
    while (index < length) {
        token->value[index] = json_string[index + token->start_index];
        index ++;
    }
}

