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

void add_button_to_scene(char* button_name, int x, int y, int w, int h, char* text, FONT font_name, void (*click_function)(Button* self), Game* game)
{
    TTF_Font* font = get_font(font_name, game->ui_manager);
    
    Button* testbutton = init_button(button_name, x, y, w, h, text, font, click_function, game->renderer);

    entity_s* ent = init_entity(BUTTON, testbutton);

    add_entity(game, ent);
}

void ui_render_button(SDL_Renderer* ren, void* button_data){
    Button* button = (Button*)button_data;
    render_button(ren, button);
}

void ui_click_button(entity_s* entity, int mouseX, int mouseY){
    Button* button = (Button*) entity->data;
    //check x bounds
    if(mouseX <= button->x_pos + button->width && mouseX >= button->x_pos){
    //check y bounds
        if(mouseY <= button->y_pos + button->height && mouseY >= button->y_pos){
        //if within bounds, call on_click
            button->on_click(button);
        }
    }
}