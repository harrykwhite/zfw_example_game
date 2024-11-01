#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <zfw_game.h>
#include <zfw_rendering.h>
#include <zfw_common_math.h>
#include "tilemap.h"

typedef struct
{
    zfw_vec_2d_t pos;
    zfw_vec_2d_t vel;
    zfw_sprite_batch_slot_key_t sb_slot_key;
    zfw_bool_t jumping;
} player_t;

void init_player(player_t *const player, zfw_user_func_data_t *const zfw_data);
void update_player(player_t *const player, const tilemap_t *const tilemap, zfw_user_func_data_t *const zfw_data);

#endif
