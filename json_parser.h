#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "list.h"
#include <stdio.h>

typedef enum {
INT,
STRING,
ARRAY,
BOOL,
JSON,
NONE
} ObjType;

typedef struct {
char* key;
ObjType type;
void* value;
} JsonObj;

//Read our manifest file which details the scenes we'll have in the game and their filepaths
list_t* read_json_manifest(char* filepath);

//Read from our json into a buffer and make objects that we can get data from. Refer to JsonObj
list_t* read_json_into_objects(char* filename);

//Returns the number of chars in the file. 
long get_filesize(FILE* file);

#endif