#ifndef JSON_PARSER_H
#define JSON_PARSER_H

typedef struct {
char* key;
char* value;
} JsonObj;

char* read_json_into_buffer();

void read_buffer_into_objects();

#endif