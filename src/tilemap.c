#include "tilemap.h"

#include <assert.h>
#include <zfw_common_mem.h>

zfw_bool_t init_tilemap(tilemap_t *const tilemap, const int width, const int height, zfw_user_func_data_t *const zfw_data)
{
    assert(width > 0 && height > 0);
    assert(zfw_data);

    tilemap->width = width;
    tilemap->height = height;

    // Allocate memory for tilemap tile types and sprite batch slot keys.
    tilemap->types = zfw_mem_arena_alloc(zfw_data->main_mem_arena, sizeof(*tilemap->types) * width * height);

    if (!tilemap->types)
    {
        return ZFW_FALSE;
    }

    memset(tilemap->types, 0, sizeof(*tilemap->types) * width * height);

    tilemap->slot_keys = zfw_mem_arena_alloc(zfw_data->main_mem_arena, sizeof(*tilemap->slot_keys) * width * height);

    if (!tilemap->slot_keys)
    {
        return ZFW_FALSE;
    }

    memset(tilemap->slot_keys, 0, sizeof(*tilemap->slot_keys) * width * height);

    // Take all the sprite batch slot keys needed for the tilemap.
    zfw_take_multiple_render_layer_sprite_batch_slots(tilemap->slot_keys, width * height, ZFW_SPRITE_BATCH_GROUP_ID__VIEW, 0, 0, zfw_data->sprite_batch_groups, zfw_data->main_mem_arena);

    // Set tile types.
    for (int ty = tilemap->height / 2; ty < tilemap->height; ++ty)
    {
        for (int tx = 0; tx < tilemap->width; ++tx)
        {
            update_tilemap_tile_type_and_display(tilemap, tx, ty, TILE_TYPE_ID__DIRT, zfw_data);
        }
    }

    return ZFW_TRUE;
}

void update_tilemap_tile_type_and_display(tilemap_t *const tilemap, const int tx, const int ty, const tile_type_id_t tile_type, const zfw_user_func_data_t *const zfw_data)
{
    assert(tilemap);
    assert(tx >= 0 && ty >= 0 && tx < tilemap->width && ty < tilemap->height);

    const int ti = (ty * tilemap->width) + tx;

    const tile_type_id_t tile_type_last = tilemap->types[ti];

    if (tile_type == tile_type_last)
    {
        return;
    }

    tilemap->types[ti] = tile_type;

    if (tile_type)
    {
        // The type is not 0, meaning that something has to be drawn here.
        const zfw_vec_2d_t pos = zfw_create_vec_2d(tx * TILE_SIZE, ty * TILE_SIZE);

        zfw_rect_t src_rect;
        zfw_init_rect(&src_rect, 16, 0, 8, 8);
        //zfw_init_rect(&src_rect, 24, 0, 8, 8);

        zfw_write_to_render_layer_sprite_batch_slot(tilemap->slot_keys[ti], pos, 0.0f, zfw_create_vec_2d(1.0f, 1.0f), zfw_create_vec_2d(0.0f, 0.0f), &src_rect, &zfw_k_color_white, zfw_data->sprite_batch_groups, zfw_data->user_tex_data);
    }
    else
    {
        // The type is 0, so clear the sprite batch slot (draw nothing at this tile position).
        zfw_clear_render_layer_sprite_batch_slot(tilemap->slot_keys[ti], zfw_data->sprite_batch_groups);
    }
}
