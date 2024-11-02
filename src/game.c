#include "game.h"

#include <string.h>
#include <math.h>

#include "zfw_rendering.h"
#include "tex_src_rects.h"

/*
    Checks (through assertion) whether the sizes of all the tile texture source rectangles are equal to the specified tile size.
*/
static void check_tile_tex_src_rect_sizes()
{
    for (int i = 1; i < TILE_TYPE_COUNT; ++i)
    {
        const zfw_rect_t *src_rect = &k_tex_src_rects[get_tile_type_tex_src_rect_id((tile_type_id_t)i)];
        assert(src_rect->w == TILE_SIZE && src_rect->h == TILE_SIZE);
    }
}

void on_game_init(void *const user_ptr, zfw_user_func_data_t *const zfw_data)
{
    game_t *const game = user_ptr;

    // Reset the game struct in case this is a game restart.
    memset(game, 0, sizeof(*game));

    // NOTE: Might be a good idea to move this check into main().
#ifdef DEBUG
    check_tile_tex_src_rect_sizes();
#endif

    zfw_data->view_state->scale = 2.0f;

    init_world(&game->world, zfw_data);
}

void on_game_tick(void *const user_ptr, zfw_user_func_data_t *const zfw_data, const int zfw_frame_tick_count, const double zfw_frame_time_interval_accum)
{
    game_t *const game = user_ptr;

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

    update_world(&game->world, zfw_data);
}

void on_window_resize(void *const user_ptr, zfw_user_func_data_t *const zfw_data)
{
}
