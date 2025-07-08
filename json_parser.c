#include "json_parser.h"

list_t* read_json_manifest(char* filepath){
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

    //Read JSON File to get data
    //Realizing the other part of this will need to be finished first, rip.

    //Set up A list. WIP
    list_t* manifest_list = new_list(2);
    return manifest_list;
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