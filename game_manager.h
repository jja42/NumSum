#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

typedef enum {
RUNNING,
LOADING,
PAUSED,
VICTORY,
LOSS,
END
} GameState;

typedef struct {
GameState state;

} Game;


#endif