//
// Created by liujie52 on 2020/9/30.
//

/**
 *
{
  "a": 1,
  "b": "string"
}
 *
 */

#include "tokenizer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


TOKEN* parseStringToTokens (char* json_string) {
    int index = 0;
    int *curPointerIndex = &index;

    TOKEN* root = create_link_list();
    TOKEN *temp;

    printf("json_string = %s\n", json_string);
    while (*curPointerIndex < strlen(json_string)) {

        char character = json_string[*curPointerIndex];

        if (isSpace(json_string, *curPointerIndex)) {
            *curPointerIndex = *curPointerIndex + 1;
            continue;
        }

        if (character == '{') {
            temp = malloc(sizeof (TOKEN));
            PARSE_VALUE_RESULT result = parseBeginObject(json_string, curPointerIndex, temp);
            if (result != SUCCESS) {
                exit(result);
            }
            push_to_list(root, temp);
            temp = NULL;
            continue;
        }

        if (character == '}') {
            temp = malloc(sizeof (TOKEN));
            PARSE_VALUE_RESULT result = parseEndObject(json_string, curPointerIndex, temp);
            if (result != SUCCESS) {
                exit(result);
            }
            push_to_list(root, temp);
            temp = NULL;
            continue;
        }

        if (character == '[') {
            temp = malloc(sizeof (TOKEN));
            PARSE_VALUE_RESULT result = parseBeginArray(json_string, curPointerIndex, temp);
            if (result != SUCCESS) {
                exit(result);
            }
            push_to_list(root, temp);
            temp = NULL;
            continue;
        }

        if (character == ']') {
            temp = malloc(sizeof (TOKEN));
            PARSE_VALUE_RESULT result = parseEndArray(json_string, curPointerIndex, temp);
            if (result != SUCCESS) {
                exit(result);
            }
            push_to_list(root, temp);
            temp = NULL;
            continue;
        }

        if (character == ':') {
            temp = malloc(sizeof (TOKEN));
            PARSE_VALUE_RESULT result = parseSepColon(json_string, curPointerIndex, temp);
            if (result != SUCCESS) {
                exit(result);
            }
            push_to_list(root, temp);
            temp = NULL;
            continue;
        }

        if (character == ',') {
            temp = malloc(sizeof (TOKEN));
            PARSE_VALUE_RESULT result = parseSepComma(json_string, curPointerIndex, temp);
            if (result != SUCCESS) {
                exit(result);
            }
            push_to_list(root, temp);
            temp = NULL;
            continue;
        }

        if (character == '"') {
            temp = malloc(sizeof (TOKEN));
            PARSE_VALUE_RESULT result = parseStringValue(json_string, curPointerIndex, temp);
            if (result != SUCCESS) {
                exit(result);
            }
            push_to_list(root, temp);
            temp = NULL;
            continue;
        }

        if (isNum(json_string, *curPointerIndex)) {
            temp = malloc(sizeof (TOKEN));
            PARSE_VALUE_RESULT result = parseNumberValue(json_string, curPointerIndex, temp);
            if (result != SUCCESS) {
                exit(result);
            }
            push_to_list(root, temp);
            temp = NULL;
            continue;
        }

        if (character == 'f' || character == 't') {
            temp = malloc(sizeof (TOKEN));
            PARSE_VALUE_RESULT result = parseBoolValue(json_string, curPointerIndex, temp);
            if (result != SUCCESS) {
                exit(result);
            }
            push_to_list(root, temp);
            temp = NULL;
            continue;
        }

        if (character == 'n') {
            temp = malloc(sizeof (TOKEN));
            PARSE_VALUE_RESULT result = parseNullValue(json_string, curPointerIndex, temp);
            if (result != SUCCESS) {
                exit(result);
            }
            push_to_list(root, temp);
            temp = NULL;
            continue;
        }

    }

    return root;
};


PARSE_VALUE_RESULT parseBeginObject(const char* json_string, int* curPointerIndex, TOKEN* token) {
    token->start_index = *curPointerIndex;
    token->end_index = *curPointerIndex;
    token->token_type = BEGIN_OBJECT;
    token->next = NULL;
    *curPointerIndex = *curPointerIndex + 1;
    get_token_value(json_string, token);
    return SUCCESS;
}

PARSE_VALUE_RESULT parseEndObject(const char* json_string, int* curPointerIndex, TOKEN* token) {
    token->start_index = *curPointerIndex;
    token->end_index = *curPointerIndex;
    token->token_type = END_OBJECT;
    token->next = NULL;
    *curPointerIndex = *curPointerIndex + 1;
    get_token_value(json_string, token);
    return SUCCESS;
}

PARSE_VALUE_RESULT parseBeginArray(const char* json_string, int* curPointerIndex, TOKEN* token) {
    token->start_index = *curPointerIndex;
    token->end_index = *curPointerIndex;
    token->token_type = BEGIN_ARRAY;
    token->next = NULL;
    *curPointerIndex = *curPointerIndex + 1;
    get_token_value(json_string, token);
    return SUCCESS;
}

PARSE_VALUE_RESULT parseEndArray(const char* json_string, int* curPointerIndex, TOKEN* token) {
    token->start_index = *curPointerIndex;
    token->end_index = *curPointerIndex;
    token->token_type = END_ARRAY;
    token->next = NULL;
    *curPointerIndex = *curPointerIndex + 1;
    get_token_value(json_string, token);
    return SUCCESS;
}

PARSE_VALUE_RESULT parseSepComma(const char* json_string, int* curPointerIndex, TOKEN* token) {
    token->start_index = *curPointerIndex;
    token->end_index = *curPointerIndex;
    token->token_type = SEP_COMMA;
    token->next = NULL;
    *curPointerIndex = *curPointerIndex + 1;
    get_token_value(json_string, token);
    return SUCCESS;
}

PARSE_VALUE_RESULT parseSepColon(const char* json_string, int* curPointerIndex, TOKEN* token) {
    token->start_index = *curPointerIndex;
    token->end_index = *curPointerIndex;
    token->token_type = SEP_COLON;
    token->next = NULL;
    *curPointerIndex = *curPointerIndex + 1;
    get_token_value(json_string, token);
    return SUCCESS;
}

PARSE_VALUE_RESULT parseBoolValue(const char* json_string, int* curPointerIndex, TOKEN* token) {
    token->token_type = BOOLEAN;
    token->start_index = *curPointerIndex;
    char character = json_string[*curPointerIndex];
    char* true_value = "true";
    char* false_value = "false";

    char* val;
    if (character == 't') { val = true_value; }
    else { val = false_value; }
    for (int index = 0; index < strlen(val) - 1; index ++) {
        if (val[index] != json_string[*curPointerIndex]) {
            printf("NOT_VALID_BOOL_VALUE");
            return NOT_VALID_BOOL_VALUE;
        }
        *curPointerIndex = *curPointerIndex + 1;
    }
    token->end_index = *curPointerIndex;
    *curPointerIndex = *curPointerIndex + 1;
    get_token_value(json_string, token);
    return SUCCESS;
}

PARSE_VALUE_RESULT parseStringValue(char* json_string, int* curPointerIndex, TOKEN* token) {
    token->token_type = STRING;
    token->start_index = *curPointerIndex;
    do {
        if (*curPointerIndex >= strlen(json_string)) {
            printf("NOT_VALID_STRING_VALUE");
            return NOT_VALID_STRING_VALUE;
        }
        *curPointerIndex = *curPointerIndex + 1;
    } while (json_string[*curPointerIndex] != '"');
    token->end_index = *curPointerIndex;
    *curPointerIndex = *curPointerIndex + 1;
    get_token_value(json_string, token);
    return SUCCESS;
}

PARSE_VALUE_RESULT parseNullValue(const char* json_string, int* curPointerIndex, TOKEN* token) {
    token->token_type = Null;
    token->start_index = *curPointerIndex;
    char* null_val = "null";
    for (int index = 0; index < strlen(null_val) - 1; index ++) {
        if (null_val[index] != json_string[*curPointerIndex]) {
            printf("NOT_VALID_NULL_VALUE");
            return NOT_VALID_NULL_VALUE;
        }
        *curPointerIndex = *curPointerIndex + 1;
    }
    token->end_index = *curPointerIndex;
    *curPointerIndex = *curPointerIndex + 1;
    get_token_value(json_string, token);
    return SUCCESS;
}

PARSE_VALUE_RESULT parseNumberValue(char* json_string, int* curPointerIndex, TOKEN* token) {
    token->token_type = NUMBER;
    token->start_index = *curPointerIndex;
    do {
        if (*curPointerIndex >= strlen(json_string)) {
            printf("NOT_VALID_NUMBER_VALUE");
            return NOT_VALID_NUMBER_VALUE;
        }
        *curPointerIndex = *curPointerIndex + 1;
    } while (json_string[*curPointerIndex] == '0'
            || json_string[*curPointerIndex] == '1'
            || json_string[*curPointerIndex] == '2'
            || json_string[*curPointerIndex] == '3'
            || json_string[*curPointerIndex] == '4'
            || json_string[*curPointerIndex] == '5'
            || json_string[*curPointerIndex] == '6'
            || json_string[*curPointerIndex] == '7'
            || json_string[*curPointerIndex] == '8'
            || json_string[*curPointerIndex] == '9'
            || json_string[*curPointerIndex] == '.');
    token->end_index = *curPointerIndex - 1;
    get_token_value(json_string, token);
    return SUCCESS;
}


int isEscapeChar(const char* json_string, int index) {
    char c = json_string[index];
    if (c == '\\') {
        return 1;
    }
    return 0;
}

int isSpace(const char* json_string, int index) {
    char c = json_string[index];
    if (c == '\t')
        return 1;
    if (c == '\n')
        return 1;
    if (c == '\r')
        return 1;
    if (c == '\0')
        return 1;
    if (c == ' ')
        return 1;
    return 0;
}

int isNum(const char* json_string, int index) {
    char c = json_string[index];
    if (c == '0'
    || c == '1'
    || c == '2'
    || c == '3'
    || c == '4'
    || c == '5'
    || c == '6'
    || c == '7'
    || c == '8'
    || c == '9'
    || c == '.') {
        return 1;
    } else {
        return 0;
    }
};