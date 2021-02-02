//
// Created by liujie52 on 2020/12/21.
//

#ifndef TINY_JSON_TOKEN_LINK_LIST_H
#define TINY_JSON_TOKEN_LINK_LIST_H
#include <stdlib.h>

typedef enum{
    BEGIN_OBJECT, //  {
    END_OBJECT,   //   }
    BEGIN_ARRAY,  //  [
    END_ARRAY,    //  ]
    Null,         //  null
    NUMBER,       //  数字
    STRING,       //  字符串
    BOOLEAN,      //  true/false
    SEP_COLON,    //  :
    SEP_COMMA,    //  ,
    END_DOCUMENT
} TOKEN_TYPE;

typedef struct {
    int status;
    char* msg;
} OPERATION_RESULT;

typedef struct _token{
    TOKEN_TYPE token_type;
    int start_index;
    int end_index;
    struct _token* next;
    char* value;
} TOKEN;

TOKEN* create_link_list();

OPERATION_RESULT push_to_list(TOKEN* root, TOKEN* to_insert);

OPERATION_RESULT pop_from_list(TOKEN* root);

OPERATION_RESULT free_token_list(TOKEN* root);

void to_string(TOKEN* root);

char* get_token_type_name(TOKEN_TYPE);

void get_token_value (const char* json_string, TOKEN* token);


#endif //TINY_JSON_TOKEN_LINK_LIST_H
