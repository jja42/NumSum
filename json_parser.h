#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "list.h"
#include <stdio.h>

typedef struct {
char* key;
char* value;
} JsonObj;

//Read our manifest file which details the scenes we'll have in the game and their filepaths
list_t* read_json_manifest(char* filepath);

//Read our scene json into a char* buffer
char* read_json_into_buffer(char* filename);

//Read from our buffer and make objects that we can get data from. Refer to JsonObj
void read_buffer_into_objects();

//Returns the number of chars in the file. 
long get_filesize(FILE* file);

#endif