#include "ui_manager.h"
#include "stdio.h"

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
    ui->fonts = new_list(10);
    return ui;
}