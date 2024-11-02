#include "player.h"

#include "tex_src_rects.h"
#include "world.h"

#define MOVE_SPD 1.5f
#define JUMP_FORCE 5.0f

static inline zfw_rect_f_t get_collider(player_t *const player, const zfw_vec_2d_t offs)
{
    const zfw_vec_2d_t top_left = zfw_create_vec_2d(
        player->pos.x - (k_tex_src_rects[TEX_SRC_RECT_ID__PLAYER].w / 2.0),
        player->pos.y - (k_tex_src_rects[TEX_SRC_RECT_ID__PLAYER].h / 2.0)
    );

    const zfw_rect_f_t collider = {top_left.x + offs.x, top_left.y + offs.y, k_tex_src_rects[TEX_SRC_RECT_ID__PLAYER].w, k_tex_src_rects[TEX_SRC_RECT_ID__PLAYER].h};

    return collider;
}

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
    const zfw_rect_f_t player_hor_collider = get_collider(player, zfw_create_vec_2d(player->vel.x, 0.0f));

    if (get_tile_collision(&player_hor_collider, tilemap))
    {
        player->vel.x = 0.0f;
    }

    const zfw_rect_f_t player_ver_collider = get_collider(player, zfw_create_vec_2d(0.0f, player->vel.y));

    if (get_tile_collision(&player_ver_collider, tilemap))
    {
        player->vel.y = 0.0f;
    }

    // Check for a diagonal collision only if neither an exclusively horizontal nor an exclusively vertical collision was found.
    if (player->vel.x && player->vel.y)
    {
        const zfw_rect_f_t player_diag_collider = get_collider(player, zfw_create_vec_2d(player->vel.x, player->vel.y));

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
    const int move_axis = zfw_is_key_down(ZFW_KEY_CODE__D, zfw_data->input_state) - zfw_is_key_down(ZFW_KEY_CODE__A, zfw_data->input_state);

    player->vel.x = move_axis * MOVE_SPD;
    player->vel.y += WORLD_GRAV;

    // Handle jump activation.
    if (zfw_is_key_pressed(ZFW_KEY_CODE__SPACE, zfw_data->input_state, zfw_data->input_state_last))
    {
        // Only jump if there is a tile below.
        const zfw_rect_f_t ground_collider = get_collider(player, zfw_create_vec_2d(0.0f, 1.0f));

        if (get_tile_collision(&ground_collider, tilemap))
        {
            player->vel.y = -JUMP_FORCE;
            player->jumping = ZFW_TRUE;
        }
    }

    handle_tilemap_collisions(player, tilemap);

    if (player->vel.y >= 0.0f)
    {
        // We are no longer ascending, so any jump that was active is active no more.
        player->jumping = ZFW_FALSE;
    }
    else
    {
        // If the jump key is released while still jumping, stop ascending.
        if (player->jumping && zfw_is_key_released(ZFW_KEY_CODE__SPACE, zfw_data->input_state, zfw_data->input_state_last))
        {
            player->vel.y = 0.0f;
            player->jumping = ZFW_FALSE;
        }
    }

    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;

    // Update our render data.
    zfw_write_to_render_layer_sprite_batch_slot(
        player->sb_slot_key,
        player->pos, 0.0f,
        zfw_create_vec_2d(1.0f, 1.0f),
        zfw_create_vec_2d(0.5f, 0.5f),
        &k_tex_src_rects[TEX_SRC_RECT_ID__PLAYER],
        &zfw_k_color_white,
        zfw_data->sprite_batch_groups,
        zfw_data->user_tex_data
    );
}
