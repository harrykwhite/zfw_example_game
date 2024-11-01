#ifndef __GAME_H__
#define __GAME_H__

#include <zfw_game.h>
#include <zfw_common_bits.h>
#include <zfw_rendering.h>
#include "player.h"

typedef enum
{
    FONT_ID__EB_GARAMOND_18,
    FONT_ID__EB_GARAMOND_24,
    FONT_ID__EB_GARAMOND_36
} font_id_t;

typedef struct
{
    player_t player;
    tilemap_t tilemap;
} game_t;

void on_game_init(void *const user_ptr, zfw_user_func_data_t *const zfw_data);
void on_game_tick(void *const user_ptr, zfw_user_func_data_t *const zfw_data, const int zfw_frame_tick_count, const double zfw_frame_time_interval_accum);
void on_window_resize(void *const user_ptr, zfw_user_func_data_t *const zfw_data);

#endif
