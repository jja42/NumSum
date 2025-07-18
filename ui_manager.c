#include "ui_manager.h"
#include "game_manager.h"

void free_ui(UI* ui){
    //loop through fonts
    for(int i = 0; i< ui->fonts->capacity; i++){
        if(ui->fonts->data[i] == NULL){
            continue;
        }
        //Explicit Cast
        TTF_Font *font = (TTF_Font*)ui->fonts->data[i];
        //FREE THE FONTS
        TTF_CloseFont(font);
    }
    free_list(ui->fonts);
    free(ui);
}

TTF_Font* get_font(FONT font, UI* ui){
    switch (font)
    {
    case ARIAL:
        return (TTF_Font*)ui->fonts->data[0];
        break;
    
    default:
        break;
    }
}

void add_font(TTF_Font* font, UI* ui){
    list_add(ui->fonts, font);
}

UI* init_ui(){
    UI* ui = malloc(sizeof(UI));
    //Handle Malloc Error
    if(ui == NULL){
         printf("Failed to allocate UI Manager.\n");
         return NULL;
    }
    ui->fonts = new_list(10);
    return ui;
}

void add_button_to_scene(char* button_name, int x, int y, int w, int h, char* text, FONT font_name, OnClick click_function, Game* game, void* data, int active)
{
    TTF_Font* font = get_font(font_name, game->ui_manager);
    
    Button* button = init_button(button_name, x, y, w, h, text, font, click_function, game->renderer, data);

    entity_s* ent = init_entity(BUTTON, button, active, button_name);

    add_entity(game, ent);
}

void add_text_panel_to_scene(char* name, int x, int y, int w, int h, char* text, FONT font_name, Game* game, int active){
    TTF_Font* font = get_font(font_name, game->ui_manager);

    TextPanel* text_panel = init_text_panel(name, x, y, w, h, text, font, game->renderer);

    entity_s* ent = init_entity(TEXTPANEL, text_panel, active, name);

    add_entity(game, ent);
}

void ui_render_text_panel(SDL_Renderer* ren, void* text_panel_data){
    TextPanel* text_panel = (TextPanel*)text_panel_data;
    render_text_panel(ren, text_panel);
}

void ui_render_button(SDL_Renderer* ren, void* button_data){
    Button* button = (Button*)button_data;
    render_button(ren, button);
}

void ui_click_button(entity_s* entity, Game* game){
    Button* button = (Button*) entity->data;
    button->on_click(game, button->data);
}

bool ui_check_button(entity_s* entity, int mouseX, int mouseY){
    Button* button = (Button*) entity->data;

    if(!button->interactible){
        return false;
    }
    
    //check x bounds
    if(mouseX <= button->x_pos + button->width && mouseX >= button->x_pos){
    //check y bounds
        if(mouseY <= button->y_pos + button->height && mouseY >= button->y_pos){
            //if within bounds, return true
            return true;
        }
    }

    return false;
}

FONT parse_font(char* font){
    if(strcmp(font, "ARIAL") == 0){
        return ARIAL;
    }
    printf("Could not find matching FONT for:  %s\n", font);
    return ARIAL;
}

OnClick parse_button_function(char* function){
    if(strcmp(function,"MAIN") == 0){
        return main_scene_button_func;
    }
    if(strcmp(function,"INFO") == 0){
        return open_info_button_func;
    }
    if(strcmp(function,"EXIT") == 0){
        return exit_button_func;
    }
    if(strcmp(function,"START") == 0){
        return start_menu_button_func;
    }
    if(strcmp(function,"CLOSE_INFO") == 0){
        return close_info_button_func;
    }
    if(strcmp(function,"MARK") == 0){
        return mark_button_func;
    }
    if(strcmp(function,"ERASE") == 0){
        return erase_button_func;
    }
    printf("Could not find matching Function for: %s\n", function);
    return NULL;
}

void ui_change_button_border(entity_s* ent, char* color){
    Button* b = (Button*)ent->data;
    if(strcmp(color,"blue") == 0){
        b->border_color = BLUE;
    }
    if(strcmp(color,"green") == 0){
        b->border_color = GREEN;
    }
    if(strcmp(color,"gold") == 0){
        b->border_color = GOLD;
    }
    if(strcmp(color,"red") == 0){
        b->border_color = RED;
    }
}