//
// Created by liujie52 on 2020/9/30.
//

#ifndef TINY_JSON_TOKENIZER_H
#define TINY_JSON_TOKENIZER_H

#include "token_link_list.h"

typedef enum{
    SUCCESS,     //成功
    SYN_TAX_ERR,  // 未知字符
    NOT_VALID_STRING_VALUE, // 不合规的字符串
    NOT_VALID_BOOL_VALUE,   // 不合规的布尔值
    NOT_VALID_NULL_VALUE,   // 不合规的 null 值
    NOT_VALID_NUMBER_VALUE,   // 不合规的 null 值
    NO_MATCHING_OBJECT_START_TAG,  // 对象没有匹配的起始符
    NO_MATCHING_OBJECT_END_TAG,  // 对象没有匹配的结束符
    NO_MATCHING_ARRAY_START_TAG,  // 数组没有匹配的起始符
    NO_MATCHING_ARRAY_END_TAG,   // 数组没有匹配的结束符
    NO_SEP_COLON_IN_KEY_PAIR,    // 键值对中间没有冒号
    NO_SEP_COMMA_BETWEEN_KEY_PAIR  // 没有逗号
} PARSE_VALUE_RESULT;



TOKEN* parseStringToTokens(char* json_string);

PARSE_VALUE_RESULT parseBeginObject(const char* json_string, int* curPointerIndex, TOKEN* token);

PARSE_VALUE_RESULT parseEndObject(const char* json_string, int* curPointerIndex, TOKEN* token);

PARSE_VALUE_RESULT parseBeginArray(const char* json_string, int* curPointerIndex, TOKEN* token);

PARSE_VALUE_RESULT parseEndArray(const char* json_string, int* curPointerIndex, TOKEN* token);

PARSE_VALUE_RESULT parseSepComma(const char* json_string, int* curPointerIndex, TOKEN* token);

PARSE_VALUE_RESULT parseSepColon(const char* json_string, int* curPointerIndex, TOKEN* token);

PARSE_VALUE_RESULT parseBoolValue(const char* json_string, int* curPointerIndex, TOKEN* token);

PARSE_VALUE_RESULT parseStringValue(char* json_string, int* curPointerIndex, TOKEN* token);

PARSE_VALUE_RESULT parseNullValue(const char* json_string, int* curPointerIndex, TOKEN* token);

PARSE_VALUE_RESULT parseNumberValue(char* json_string, int* curPointerIndex, TOKEN* token);

int isEscapeChar(const char* json_string, int index);

int isSpace(const char* json_string, int index);

int isNum(const char* json_string, int index);

#endif //TINY_JSON_TOKENIZER_H
