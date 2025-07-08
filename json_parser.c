#include "json_parser.h"
#include <string.h>

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

    while (curr_index < length)
    {
        //Start identifying Key:Value Pairs
        int key_index = find_next_string(buffer, curr_index);
        
        if(key_index == -1){
            printf("Invalid JSON formatting. Keys must begin with \".\n");
            return NULL;
        }
        
        //get our key string
        char* key = parse_string(buffer, key_index);
        if(key == NULL){
            printf("Could not parse string for key at index %d.\n", key_index);
            return NULL;
        }

        //increment position
        curr_index = key_index + strlen(key) + 1;
        //get our delimiter index to get our value
        int val_index = find_next_value(buffer, curr_index);
        
        if(val_index == -1){
            printf("Invalid JSON formatting. Values must be proceeded by ':' .\n");
            free(key);
            return NULL;
        }

        curr_index = val_index + 1;
        
        //Skip Whitespace
        while (isspace(buffer[curr_index])) curr_index++;

        //get the type of object we're working with
        ObjType type = get_value_type(buffer, curr_index);

        if(type == NULL){
            printf("Invalid JSON formatting. Values must be proceeded by ':' .\n");
            free(key);
            return NULL;
        }
 
    }

    free(buffer);
    return NULL;
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

char* parse_string(char* buffer, int start_index){
    //Match our opening " with a closing "
    int string_end = find_next_string(buffer, start_index +1);
    //Exclude the ending quotation mark
    int length = string_end - start_index - 1;

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
    memcpy(string,buffer + start_index + 1,length);
    //Add a terminator
    string[length] = '\0';
    return string;
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

long get_filesize(FILE *file){
//Use fseek to get to the end of the file
fseek(file, 0, SEEK_END);

//ftell gives us the last index
long filesize = ftell(file);

//undo our seeking by returning the internal position index to the start
rewind(file);

return filesize;
}