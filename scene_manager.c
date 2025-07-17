#include "scene_manager.h"
#include "ui_manager.h"
#include "json_parser.h"

void load_scene_name(Scene_Name scene_name, Game* game){
    switch (scene_name)
    {
    case START_MENU:
        load_scene("start_scene",game);
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
    JsonObj* json_obj = NULL;
    list_t* json = NULL;
    list_t* elements = NULL;
    JsonObj* obj = NULL;
    
    //Load Buttons
    json_obj = json_list_get(scene_objects,"buttons");
    list_t* buttons = (list_t*)json_obj->value;
    for(int i = 0; i<buttons->capacity; i++){
        if(buttons->data[i] != NULL){
            //Button JSON
            json_obj = (JsonObj*)buttons->data[i];

            //Button JSON List
            json = (list_t*)json_obj->value;

            char* name = (char*)json_list_get(json,"name")->value;
            int* x = (int*)json_list_get(json,"x")->value;
            int* y = (int*)json_list_get(json,"y")->value;
            int* width = (int*)json_list_get(json,"width")->value;
            int* height = (int*)json_list_get(json,"height")->value;
            char* text = (char*)json_list_get(json,"text")->value;
            char* font = (char*)json_list_get(json,"font")->value;
            FONT f = parse_font(font);
            char* function = (char*)json_list_get(json,"function")->value;
            OnClick func = parse_button_function(function);
            void* data = json_list_get(json,"data")->value;

            add_button_to_scene(name, *x, *y, *width, *height, text, f, func, game, data);
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
                    
                    JsonObj* object = json_list_get(json_elements,"name");
                    scene->name = strdup((char*)object->value);
                    object = json_list_get(json_elements,"file");
                    scene_path = (char*)object->value;
                }
            scene->objects = read_json_into_objects(scene_path);
            list_add(manager->scenes,scene);
            }
        }
    }
}