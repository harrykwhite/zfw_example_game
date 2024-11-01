#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <zfw_game.h>
#include <zfw_rendering.h>
#include <zfw_common_math.h>

typedef struct
{
    zfw_vec_2d_t pos;
    zfw_sprite_batch_slot_key_t sb_slot_key;
} player_t;

void init_player(player_t *const player, zfw_user_func_data_t *const zfw_data);
void update_player(player_t *const player, zfw_user_func_data_t *const zfw_data);

#endif
