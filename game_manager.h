#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "entity.h"

typedef enum {
RUNNING,
LOADING,
PAUSED,
END
} GameState;

typedef struct {
GameState state;
entity_s** entities;
} Game;

Game* get_game();

void pause_game(Game* game);

void resume_game(Game* game);

void start_game(Game* game);

void exit_game(Game* game);

#endif