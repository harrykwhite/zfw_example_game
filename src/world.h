#ifndef __WORLD_H__
#define __WORLD_H__

#include "player.h"
#include "tilemap.h"

#define WORLD_GRAV 0.35f

typedef struct
{
    tilemap_t tilemap;
    player_t player;
} world_t;

void init_world(world_t *const world, zfw_user_func_data_t *const zfw_data);
void update_world(world_t *const world, zfw_user_func_data_t *const zfw_data);

#endif
