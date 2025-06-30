#ifndef ENTITY_H
#define ENTITY_H

typedef enum {
BUTTON,
NUMBER,
GROUP
} Entity_Type;


//Will Hold Data Eventually
//Container Type to Loop through for Game Manager
typedef struct{
Entity_Type type;
void* data;
} entity_s;

#endif