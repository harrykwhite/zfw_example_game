#include "player.h"

#if 0
static inline zfw_rect_t make_rect(const int x, const int y, const int w, const int h)
{
    const zfw_rect_t rect = {x, y, w, h};
    return rect;
}
#endif

const float k_move_spd = 1.5f;

static zfw_bool_t get_tile_collision(const zfw_rect_f_t *const collider, const tilemap_t *const tilemap)
{
    for (int ty = 0; ty < tilemap->height; ++ty)
    {
        for (int tx = 0; tx < tilemap->width; ++tx)
        {
            if (!tilemap->types[(ty * tilemap->width) + tx])
            {
                // There is no tile here.
                continue;
            }

            const zfw_rect_f_t tile_collider = {tx * TILE_SIZE, ty * TILE_SIZE, TILE_SIZE, TILE_SIZE};

            if (zfw_do_rect_fs_collide(collider, &tile_collider))
            {
                return ZFW_TRUE;
            }
        }
    }

    return ZFW_FALSE;
}

static void handle_tilemap_collisions(player_t *const player, const tilemap_t *const tilemap)
{
    const zfw_rect_f_t player_hor_collider = {player->pos.x - 8.0f + player->vel.x, player->pos.y - 8.0f, 16.0f, 16.0f};

    if (get_tile_collision(&player_hor_collider, tilemap))
    {
        player->vel.x = 0.0f;
    }

    const zfw_rect_f_t player_ver_collider = {player->pos.x - 8.0f, player->pos.y - 8.0f + player->vel.y, 16.0f, 16.0f};

    if (get_tile_collision(&player_ver_collider, tilemap))
    {
        player->vel.y = 0.0f;
    }

    if (player->vel.x && player->vel.y)
    {
        const zfw_rect_f_t player_diag_collider = {player->pos.x - 8.0f + player->vel.x, player->pos.y - 8.0f + player->vel.y, 16.0f, 16.0f};

        if (get_tile_collision(&player_diag_collider, tilemap))
        {
            player->vel.x = 0.0f;
        }
    }
}

void init_player(player_t *const player, zfw_user_func_data_t *const zfw_data)
{
    player->sb_slot_key = zfw_take_render_layer_sprite_batch_slot(ZFW_SPRITE_BATCH_GROUP_ID__VIEW, 1, 0, zfw_data->sprite_batch_groups, zfw_data->main_mem_arena);
}

void update_player(player_t *const player, const tilemap_t *const tilemap, zfw_user_func_data_t *const zfw_data)
{
    const zfw_vec_2d_i_t move_axis = {
        zfw_is_key_down(ZFW_KEY_CODE__D, zfw_data->input_state) - zfw_is_key_down(ZFW_KEY_CODE__A, zfw_data->input_state),
        zfw_is_key_down(ZFW_KEY_CODE__S, zfw_data->input_state) - zfw_is_key_down(ZFW_KEY_CODE__W, zfw_data->input_state)
    };

    player->vel.x = move_axis.x;
    player->vel.y = move_axis.y;

    handle_tilemap_collisions(player, tilemap);

    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;

    const zfw_rect_t src_rect = {0, 0, 16, 16};
    zfw_write_to_render_layer_sprite_batch_slot(player->sb_slot_key, player->pos, 0.0f, zfw_create_vec_2d(1.0f, 1.0f), zfw_create_vec_2d(0.5f, 0.5f), &src_rect, &zfw_k_color_white, zfw_data->sprite_batch_groups, zfw_data->user_tex_data);
}
