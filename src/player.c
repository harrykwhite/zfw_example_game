#include "player.h"

void init_player(player_t *const player, zfw_user_func_data_t *const zfw_data)
{
    player->sb_slot_key = zfw_take_render_layer_sprite_batch_slot(ZFW_SPRITE_BATCH_GROUP_ID__VIEW, 0, 0, zfw_data->sprite_batch_groups, zfw_data->main_mem_arena);
}

void update_player(player_t *const player, tilemap_t *const tilemap, zfw_user_func_data_t *const zfw_data)
{
    const zfw_vec_2d_i_t move_axis = {
        zfw_is_key_down(ZFW_KEY_CODE__D, zfw_data->input_state) - zfw_is_key_down(ZFW_KEY_CODE__A, zfw_data->input_state),
        zfw_is_key_down(ZFW_KEY_CODE__S, zfw_data->input_state) - zfw_is_key_down(ZFW_KEY_CODE__W, zfw_data->input_state)
    };

    player->pos.x += move_axis.x;
    player->pos.y += move_axis.y;

    const zfw_rect_t src_rect = {0, 0, 16, 16};
    zfw_write_to_render_layer_sprite_batch_slot(player->sb_slot_key, player->pos, 0.0f, zfw_create_vec_2d(1.0f, 1.0f), zfw_create_vec_2d(0.5f, 0.5f), &src_rect, &zfw_k_color_white, zfw_data->sprite_batch_groups, zfw_data->user_tex_data);
}
