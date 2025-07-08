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

//Wrapper for the two following functions. Consolidated into one neat function
list_t* read_json_into_objects(char* filename);

//Read from our json file into a buffer 
char* read_json_into_buffer(char* filename);

//Read from our buffer and make objects that we can get data from. Refer to JsonObj
list_t* read_buffer_into_objects(char* buffer);

//Finds the starting index of the next string in the buffer
int find_next_string(char* buffer, int index);

//return the string given a starting index
char* parse_string(char* buffer, int index);

//return the index of the next delimiter
int find_next_value(char* buffer, int index);

//Get the obj type of the json value
ObjType get_value_type(char* buffer, int index);

//Returns the number of chars in the file. 
long get_filesize(FILE* file);

#endif