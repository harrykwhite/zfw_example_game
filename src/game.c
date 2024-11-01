#include "game.h"

#include <string.h>
#include <math.h>

#include "zfw_rendering.h"

void on_game_init(void *const user_ptr, zfw_user_func_data_t *const zfw_data)
{
    game_t *game = user_ptr;

    zfw_data->view_state->scale = 3.0f;

    // Reset the game struct in case this is a game restart.
    memset(game, 0, sizeof(*game));

    init_player(&game->player, zfw_data);
}

void on_game_tick(void *const user_ptr, zfw_user_func_data_t *const zfw_data, const int zfw_frame_tick_count, const double zfw_frame_time_interval_accum)
{
    game_t *game = user_ptr;

    // Handle fullscreen toggling.
    if (zfw_is_key_pressed(ZFW_KEY_CODE__F, zfw_data->input_state, zfw_data->input_state_last))
    {
        *zfw_data->window_fullscreen = !*zfw_data->window_fullscreen;
    }

    // Handle restarting.
    if (zfw_is_key_pressed(ZFW_KEY_CODE__R, zfw_data->input_state, zfw_data->input_state_last))
    {
        *zfw_data->restart = ZFW_TRUE;
    }

    update_player(&game->player, zfw_data);
}

void on_window_resize(void *const user_ptr, zfw_user_func_data_t *const zfw_data)
{
}
