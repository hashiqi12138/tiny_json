//
// Created by liujie52 on 2021/1/9.
//

#ifndef
TINY_JSON_JSON_HASH_MAP_H
#define
TINY_JSON_JSON_HASH_MAP_H

typedef struct _JSON_OBJECT {
    char* key,
    JSON_VALUE* value
} JSON_OBJECT;

union JSON_VALUE {
    char* ,
    int ,
    double ,
    float ,
    JSON_OBJECT
};

#endif //TINY_JSON_JSON_HASH_MAP_H
