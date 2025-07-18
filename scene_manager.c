#include "scene_manager.h"
#include "ui_manager.h"
#include "json_parser.h"
#include <string.h>


void load_scene_name(Scene_Name scene_name, Game* game){
    switch (scene_name)
    {
    case START_MENU:
        load_scene("start_scene",game);
        break;
    case MAIN_GAME:
        load_scene("main_scene",game);
        setup_grid_entities(game);
        break;
    default:
        break;
    }
}

//Free any lingering entity data
//Then clear entity list
void clear_scene(Game* game){
    free_entities(game);
    clear_list(game->entities);
}

void load_scene(char* name, Game* game){
    clear_scene(game);

    SceneManager* manager  = game->scene_manager;
    list_t* scenes = manager->scenes;

    for(int i = 0; i<scenes->capacity; i++){
        if(scenes->data[i] != NULL){
            Scene* scene = (Scene*)scenes->data[i];
            if(strcmp(scene->name, name) == 0){
                list_t* scene_objects = scene->objects;
                load_scene_objects(scene, scene_objects, game);
                return;
            }
        }
    }

    printf("Could Not Find Scene Named: %s in Scene List", name);
    return;
}

void load_scene_objects(Scene* scene, list_t* scene_objects, Game* game){
    
    list_t* json_elements = NULL;
    JsonObj* json_obj = NULL;
    
    //Load Buttons
    list_t* buttons = json_list_get(scene_objects,"buttons");
    if(buttons != NULL){
        for(int i = 0; i<buttons->capacity; i++){
            if(buttons->data[i] != NULL){
                //Button JSON
                json_obj = (JsonObj*)buttons->data[i];

                //Button JSON List
                json_elements = (list_t*)json_obj->value;

                char* name = (char*)json_obj_get(json_elements,"name")->value;
                int* x = (int*)json_obj_get(json_elements,"x")->value;
                int* y = (int*)json_obj_get(json_elements,"y")->value;
                int* width = (int*)json_obj_get(json_elements,"width")->value;
                int* height = (int*)json_obj_get(json_elements,"height")->value;
                char* text = (char*)json_obj_get(json_elements,"text")->value;
                char* font = (char*)json_obj_get(json_elements,"font")->value;
                FONT f = parse_font(font);
                char* function = (char*)json_obj_get(json_elements,"function")->value;
                OnClick func = parse_button_function(function);
                void* data = json_obj_get(json_elements,"data")->value;
                int* active = (int*)json_obj_get(json_elements,"active")->value;

                add_button_to_scene(name, *x, *y, *width, *height, text, f, func, game, data, *active);
            }
        }
    }

    //Load Text Panels
    list_t* text_panels = json_list_get(scene_objects,"text_panels");
    if(text_panels != NULL){
        for(int i = 0; i<text_panels->capacity; i++){
            if(text_panels->data[i] != NULL){
                //Text Panel JSON
                json_obj = (JsonObj*)text_panels->data[i];

                //Tex Panel JSON List
                json_elements = (list_t*)json_obj->value;

                char* name = (char*)json_obj_get(json_elements,"name")->value;
                int* x = (int*)json_obj_get(json_elements,"x")->value;
                int* y = (int*)json_obj_get(json_elements,"y")->value;
                int* width = (int*)json_obj_get(json_elements,"width")->value;
                int* height = (int*)json_obj_get(json_elements,"height")->value;
                char* text = (char*)json_obj_get(json_elements,"text")->value;
                char* font = (char*)json_obj_get(json_elements,"font")->value;
                FONT f = parse_font(font);
                int* active = (int*)json_obj_get(json_elements,"active")->value;

                add_text_panel_to_scene(name, *x, *y, *width, *height, text, f, game, *active);
            }
        }
    }
}

void load_scene_manifest(char* filepath, SceneManager* manager){
    list_t* manifest = read_json_into_objects(filepath);
    if(manifest == NULL){
        printf("Failed to read JSON.\n");
        return;
    }
    //print_json(manifest);
    read_scene_manifest(manifest, manager);
}

list_t* load_scene_file(char* filepath){
    list_t* scene = read_json_into_objects(filepath);

    if(scene == NULL){
        printf("Failed to read JSON.\n");
        return NULL;
    }

    return scene;
}


void free_scenes(SceneManager* manager){
    for(int i = 0; i<manager->scenes->capacity; i++){
        if(manager->scenes->data[i] != NULL){
            free_scene(manager->scenes->data[i]);
        }
    }
    free_list(manager->scenes);
    free(manager);
}

void free_scene(Scene* scene){
    free(scene->name);
    for(int i = 0; i<scene->objects->capacity; i++){
        if(scene->objects->data[i] != NULL){
            free_json(scene->objects->data[i]);
        }
    }
    free_list(scene->objects);
    free(scene);
}

SceneManager* init_scene_management(){
    SceneManager* manager = malloc(sizeof(SceneManager));
    //Handle Malloc Error
    if(manager == NULL){
         printf("Failed to allocate Scene Manager.\n");
         return NULL;
    }

    manager->scenes = new_list(1);

    return manager;
}

void read_scene_manifest(list_t* manifest, SceneManager* manager){
    for(int i = 0; i<manifest->capacity; i++){
        if(manifest->data[i] != NULL){
            //Key = Scenes
            //Value = Array
            JsonObj* array = (JsonObj*) manifest->data[i];
            list_t* array_elements = (list_t*)array->value;

            char* scene_path = NULL;

            for(int i = 0; i <array_elements->capacity; i++){
                Scene* scene = malloc(sizeof(Scene));
                
                //Handle Malloc Error
                if(scene == NULL){
                    printf("Failed to allocate Scene.\n");
                    return;
                }
                
                if(array_elements->data[i] == NULL){
                    free(scene);
                    continue;
                }

                else{
                    //Nested JSON
                    //name : Name
                    //file : Filepath
                    JsonObj* json = (JsonObj*)array_elements->data[i];
                    list_t* json_elements = (list_t*)json->value;
                    
                    JsonObj* object = json_obj_get(json_elements,"name");
                    scene->name = strdup((char*)object->value);
                    object = json_obj_get(json_elements,"file");
                    scene_path = (char*)object->value;
                }
            scene->objects = read_json_into_objects(scene_path);
            list_add(manager->scenes,scene);
            }
        }
    }
}

void setup_grid_entities(Game* game){
    //For Centering
    int cellSize = 45;
    int gridSize = game->grid->size * cellSize;
    int startX = (800 - gridSize) / 2;
    startX -= 15;
    int startY = (600 - gridSize) / 2;

    //Make Buttons for each Grid Cell
    for(int i = 0; i<game->grid->size; i++){
        list_t* columns = (list_t*)game->grid->rows->data[i];
        for(int j = 0; j<game->grid->size; j++){
            //Get Num
            Num* n = (Num*)columns->data[j];
            char* name = "Grid Cell";
            //Convert Value to Text
            char text[4];
            SDL_itoa(n->value,text,10);
            //Set Number Position
            n->x = j;
            n->y = i;
            //Button Data
            void* data = n;
            //Position
            int x  = startX + (j * 50);
            int y = startY + (i * 50);
            add_button_to_scene(name, x, y, 45, 45, text, ARIAL, grid_entity_button_func, game, data, 1);
        }
    }

    //Put Sums on Top and Side
    for(int r = 0; r<game->grid->sums_r->count; r++){
        int x = startX - 75; 
        int y = startY + (r * 55);
        
        //Get Num
        Num* n = (Num*)game->grid->sums_r->data[r];
        char* name = "Row Sum";

        //Convert Value to Text
        char text[4];
        SDL_itoa(n->value,text,10);

        add_text_panel_to_scene(name,x,y,35,35,text,ARIAL,game,1);
    }

    for(int c = 0; c<game->grid->sums_c->count; c++){
        int x = startX + (c * 55); 
        int y = startY - 75 ;
        
        //Get Num
        Num* n = (Num*)game->grid->sums_c->data[c];
        char* name = "Column Sum";

        //Convert Value to Text
        char text[4];
        SDL_itoa(n->value,text,10);

        add_text_panel_to_scene(name,x,y,35,35,text,ARIAL,game,1);
    }
}