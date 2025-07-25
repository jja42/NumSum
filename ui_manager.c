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

void add_button_to_scene(char* name, TextPanel* t, OnClick click_function, Game* game, int active)
{    
    Button* button = init_button(t, click_function);

    entity_s* ent = init_entity(BUTTON, button, active, name);

    add_entity(game, ent);
}

void add_text_panel_to_scene(char* name, int x, int y, int w, int h, char* text, FONT font_name, Game* game, int active, Color border_color){

    TextPanel* text_panel = init_text_panel(x, y, w, h, text, font_name, game, border_color);

    entity_s* ent = init_entity(TEXTPANEL, text_panel, active, name);

    add_entity(game, ent);
}

void ui_render_text_panel(SDL_Renderer* ren, void* text_panel_data){
    TextPanel* text_panel = (TextPanel*)text_panel_data;
    render_text_panel(ren, text_panel);
}

void ui_render_button(SDL_Renderer* ren, void* button_data){
    Button* button = (Button*)button_data;
    render_text_panel(ren, button->panel);
}

void ui_click_button(entity_s* entity, Game* game){
    Button* button = (Button*) entity->data;
    button->on_click(game);
}

bool ui_check_click(entity_s* entity, int mouseX, int mouseY){
    
    if(!entity->interactible){
        return false;
    }
    
    TextPanel* panel = ui_get_panel(entity);
    
    //check x bounds
    if(mouseX <= panel->x_pos + panel->width && mouseX >= panel->x_pos){
    //check y bounds
        if(mouseY <= panel->y_pos + panel->height && mouseY >= panel->y_pos){
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
        return start_button_func;
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
    if(strcmp(function,"GRID3") == 0){
        return init_grid_3;
    }
    if(strcmp(function,"GRID4") == 0){
        return init_grid_4;
    }
    if(strcmp(function,"GRID5") == 0){
        return init_grid_5;
    }
    if(strcmp(function,"GRID6") == 0){
        return init_grid_6;
    }
    if(strcmp(function,"GRID7") == 0){
        return init_grid_7;
    }
    if(strcmp(function,"GRID8") == 0){
        return init_grid_8;
    }
    printf("Could not find matching Function for: %s\n", function);
    return NULL;
}

void ui_change_panel_border(TextPanel* t, Color color){
    t->border_color = color;
}

Color ui_get_color(char* color){
    if(strcmp(color,"BLUE") == 0){
        return BLUE;
    }
    if(strcmp(color,"GREEN") == 0){
        return GREEN;
    }
    if(strcmp(color,"GOLD") == 0){
        return GOLD;
    }
    if(strcmp(color,"RED") == 0){
       return RED;
    }
}


void add_grid_entity_to_scene(int x, int y, TextPanel* panel, Num* num, Game* game){

    GridEntity* g_ent = init_grid_entity(panel, x, y, num);

    entity_s* ent = init_entity(GRIDENTITY, g_ent, 1, "Grid Cell");

    add_entity(game, ent);
}

void ui_render_grid_entity(SDL_Renderer* ren, void* grid_entity_data){
    GridEntity* g_ent = (GridEntity*)grid_entity_data;
    render_text_panel(ren, g_ent->panel);
}

void ui_click_grid_entity(entity_s* entity, Game* game){
    grid_entity_click(game, entity);
}

TextPanel* ui_get_panel(entity_s* ent){
    switch (ent->type)
    {
    case TEXTPANEL:
        return (TextPanel*)ent->data;
        break;
    case BUTTON:
        Button* button = (Button*) ent->data;
        return button->panel;
        break;
    case GRIDENTITY:
        GridEntity* g_ent = (GridEntity*)ent->data;
        return g_ent->panel;
        break;
    default:
        break;
    }
    return NULL;
}

void ui_update_panel_text(TextPanel* text_panel, char* text, FONT font_name, Game* game){

    TTF_Font* font = get_font(font_name, game->ui_manager);
    SDL_Renderer* ren = game->renderer;

    //Create Text Surface and Texture
    SDL_Color black = {0, 0, 0};
    SDL_Surface* text_surface = TTF_RenderText_Blended_Wrapped(font, text, black,0);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(ren, text_surface);

    //Get these for centering
    int text_width = text_surface->w;
    int text_height = text_surface->h;

    //FREE
    SDL_FreeSurface(text_surface);

    //Also free old ref
    SDL_DestroyTexture(text_panel->text_texture);

    //Create a rect
    SDL_Rect text_rect = {
    text_panel->x_pos + (text_panel->width - text_width) / 2,
    text_panel->y_pos + (text_panel->height - text_height) / 2,
    text_width,
    text_height};

    //Assign our text refs here for rendering later
    text_panel->text_texture = text_texture;
    text_panel->text_rect = text_rect;
}