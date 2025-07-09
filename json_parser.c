#include "json_parser.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

list_t* read_json_into_objects(char* filename){
    char* buffer = read_json_into_buffer(filename);
    list_t* objs = read_buffer_into_objects(buffer);
    free(buffer);
    return objs;
}

char* read_json_into_buffer(char* filepath){
    //Open File
    FILE *file;
    file = fopen(filepath,"r");

    //Check File
    if (file == NULL) {
        printf("File at %s could not be opened.\n", filepath);
        return NULL;
    }

    //Get Size
    long size = get_filesize(file);

    //Allocate a Buffer to Check
    char* buffer = malloc(sizeof(char) * (size + 1));

    //Error handling
    if (buffer == NULL)
    {
        printf("Failed to allocate buffer for file at %s",filepath);
        fclose(file);
        return NULL;
    }

    //Read into the buffer
    fread(buffer, sizeof(char), size, file);

    //Close File
    fclose(file);
    return buffer;
}

list_t* read_buffer_into_objects(char* buffer){
    size_t length = strlen(buffer);
    
    //Check Length
    if (length == 0) {
    printf("Empty buffer. Not valid JSON.\n");
    return NULL;
    }

    //Check Proper JSON formatting
    if(buffer[0] != '{'){
        printf("Invalid JSON formatting. Must begin with '{'.\n");
        return NULL;
    }

    if(buffer[length-1] != '}'){
        printf("Invalid JSON formatting. Must end with '}'.\n");
        return NULL;
    }

    int curr_index = 0;
    list_t* object_list = new_list(0);
    if(object_list == NULL){
        printf("Failed to Create Object List.\n");
        return NULL;
    }

    while (curr_index < length)
    {
        //Start identifying Key:Value Pairs
        curr_index = find_next_string(buffer, curr_index);
        
        if(curr_index == -1){
            printf("Invalid JSON formatting. Keys must begin with \".\n");
            free_list(object_list);
            return NULL;
        }
        
        //get our key string
        char* key = parse_string(buffer, &curr_index);
        if(key == NULL){
            printf("Could not parse string for key at index %d.\n", curr_index);
            free_list(object_list);
            return NULL;
        }

        //get our delimiter index to get our value
        curr_index = find_next_value(buffer, curr_index);
        
        if(curr_index == -1){
            printf("Invalid JSON formatting. Values must be proceeded by ':' .\n");
            free(key);
            free_list(object_list);
            return NULL;
        }

        //move past the delimiter
        curr_index++;

        //skip whitespace
        while (isspace(buffer[curr_index])) curr_index++;

        //get the type of object we're working with
        ObjType type = get_value_type(buffer, curr_index);

        if(type == NONE){
            printf("Invalid JSON formatting. Values must be proceeded by ':' .\n");
            free(key);
            free_list(object_list);
            return NULL;
        }

        //Get our value
        void* value = get_value(buffer, &curr_index, type);

        if(value == NULL){
            printf("Failed to obtain value.");
            free(key);
            free_list(object_list);
            return NULL;
        }

        //create a json object for our data
        JsonObj* obj = init_json_object(key, value, type);

        //Handle Malloc Error
        if(obj == NULL){
            printf("Failed to allocate JsonObj.\n");
            free(key);
            free(value);
            free_list(object_list);
            return NULL;
        }

        list_add(object_list, obj);

        curr_index = get_next_obj_index(buffer,curr_index);
        if(curr_index == -1){
            break;
        }
        curr_index++;
    }
    
    return object_list;
}

int find_next_string(char* buffer, int index){
    //Loop through buffer and look for "
    for(int i = index; buffer[i] != '\0'; i++){
        if(buffer[i] == '"'){
            return i;
        }
    }
    printf("ERROR: No String Found.");
    return -1;
}

int find_next_value(char* buffer, int index){
    //Iterate through the buffer and look for delimiter :
    for(int i = index; buffer[i] != '\0'; i++){
        if(buffer[i] == ':'){
            return i;
        }
    }
    printf("ERROR: No Delimiter Found.");
    return -1;
}

ObjType get_value_type(char* buffer, int index){
    switch (buffer[index])
    {
    case '\"':
        return STRING;
    case '{':
        return JSON;
    case '[':
        return ARRAY;
    default:
        if(isdigit(buffer[index])){
            return INT;
        }
        if(strncmp(buffer + index, "true", 4) == 0 || strncmp(buffer + index, "false", 5) == 0){
            return BOOL;
        }
        return NONE;
    }
}

void* get_value(char* buffer, int* index, ObjType type){
    switch (type)
    {
    case STRING:
        return parse_string(buffer, index);
        break;
    case INT:
        return parse_int(buffer,index);
    case BOOL:
        return parse_bool(buffer, index);
    case ARRAY:
        return parse_array(buffer, index);
    case JSON:
        return parse_json(buffer, index);
    default:
        break;
    }
}

JsonObj* init_json_object(char* key, void* value, ObjType type){
    JsonObj* obj = malloc(sizeof(JsonObj));
    obj->key = key;
    obj->value = value;
    obj->type = type;
    return obj;
}

char* parse_string(char* buffer, int* start_index){
    //Match our opening " with a closing "
    int string_end = find_next_string(buffer, *start_index +1);
    //Exclude the ending quotation mark
    int length = string_end - *start_index - 1;

    //Allocate a string to hold the value
    char* string = malloc(sizeof(char) * (length + 1));

    //Error handling
    if (string == NULL)
    {
        printf("Failed to allocate string.\n");
        return NULL;
    }

    //Copy from the buffer into our string
    //Excludes the starting quotation mark
    memcpy(string,buffer + *start_index + 1,length);

    //Add a terminator
    string[length] = '\0';
    
    //Update Index
    //increment position by "string" (moves us past second ")
    *start_index += length + 2;

    return string;
}

int* parse_int(char* buffer, int* index){
    //Allocate an int
    int* i = malloc(sizeof(int));
    if(i == NULL){
        printf("Failed to allocate int.\n");
        return NULL;
    }

    //get end of int
    int end_index = get_next_obj_index(buffer, *index) - 1;

    int length = end_index - *index;

    //allocate a string
    char* str = malloc(sizeof(char) * length + 1);

    if (str == NULL) {
        printf("Failed to allocate for int conversion.\n");
        free(i);
        return NULL;
    }

    //copy from buffer into string
    memcpy(str, buffer + *index, length);

    str[length] = '\0';

    //convert string value into int
    *i = atoi(str);

    free(str);

    //update index
    *index = end_index;

    return i;
}

bool* parse_bool(char* buffer, int* index){
    bool* b = malloc(sizeof(bool));
    if(b == NULL){
        printf("Failed to allocate bool.\n");
        return NULL;
    }
    if(strncmp(buffer + *index, "true", 4) == 0){
        *b = true;
        *index += 4;
        return b;
    } 
    if(strncmp(buffer + *index, "false", 5) == 0){
        *b = false;
        *index += 5;
        return b;
    }
    return NULL;
}

list_t* parse_array(char* buffer, int* index){
    //get index of ]
    int end_index  = get_array_end(buffer, *index) - 1;
    if(end_index == -1){
        printf("Invalid JSON format. Missing matching array bracket.");
        return NULL;
    }

    int length = end_index - *index;
    //malloc a substring
    char* sub_buffer = malloc(sizeof(char) * (length + 1));

    if (sub_buffer == NULL) {
        printf("Failed to allocate for array parsing.\n");
        return NULL;
    }

    memcpy(sub_buffer,buffer + *index + 1,length);
    sub_buffer[length] = '\0';

    //recursion
    list_t* array_elements = read_buffer_into_objects(sub_buffer);
    
    free(sub_buffer);

    *index = end_index + 1;

    return array_elements;
}

list_t* parse_json(char* buffer, int* index){
    //get index of }
    int end_index  = get_json_end(buffer, *index) - 1;
    if(end_index == -1){
        printf("Invalid JSON format. Missing matching closing brace.");
        return NULL;
    }
    int length = end_index - *index;
    //malloc a substring
    char* sub_buffer = malloc(sizeof(char) * (length + 1));

    if (sub_buffer == NULL) {
        printf("Failed to allocate for object parsing.\n");
        return NULL;
    }

    memcpy(sub_buffer,buffer + *index + 1,length);
    sub_buffer[length] = '\0';

    //recursion
    list_t* object_elements = read_buffer_into_objects(sub_buffer);
    
    free(sub_buffer);

    *index = end_index + 1;

    return object_elements;
}

long get_filesize(FILE *file){
//Use fseek to get to the end of the file
fseek(file, 0, SEEK_END);

//ftell gives us the last index
long filesize = ftell(file);

//undo our seeking by returning the internal position index to the start
rewind(file);

return filesize;
}

int get_next_obj_index(char* buffer,int index){
    //Iterate through the buffer and look for delimiter ,
    for(int i = index; buffer[i] != '\0'; i++){
        if(buffer[i] == ','){
            return i;
        }
    }
    return -1;
}

int get_array_end(char* buffer, int index){
    //Iterate through the buffer and look for delimiter ]
    for(int i = index; buffer[i] != '\0'; i++){
        if(buffer[i] == ']'){
            return i;
        }
    }
    return -1;
}

int get_json_end(char* buffer, int index){
    //Iterate through the buffer and look for delimiter }
    for(int i = index; buffer[i] != '\0'; i++){
        if(buffer[i] == '}'){
            return i;
        }
    }
    return strlen(buffer);
}