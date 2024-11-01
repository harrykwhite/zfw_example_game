#include <zfw_game.h>
#include "game.h"

int main()
{
    game_t game;

    zfw_user_game_run_info_t zfw_game_run_info = { 0 };

    zfw_game_run_info.init_window_size = zfw_create_vec_2d_i(1280, 720);
    zfw_game_run_info.init_window_title = "Example Game";
    zfw_game_run_info.window_resizable = ZFW_TRUE;

    zfw_game_run_info.on_init_func = on_game_init;
    zfw_game_run_info.on_tick_func = on_game_tick;
    zfw_game_run_info.on_window_resize_func = on_window_resize;

    zfw_game_run_info.user_ptr = &game;

    return !zfw_run_game(&zfw_game_run_info);
}
