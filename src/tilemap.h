#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include <zfw_game.h>
#include <zfw_rendering.h>

#define TILE_SIZE 8

typedef enum
{
    TILE_TYPE_ID__NONE,
    TILE_TYPE_ID__DIRT,
    TILE_TYPE_ID__STONE
} tile_type_id_t;

typedef struct
{
    int width, height;
    tile_type_id_t *types;
    zfw_sprite_batch_slot_key_t *slot_keys;
} tilemap_t;

zfw_bool_t init_tilemap(tilemap_t *const tilemap, const int width, const int height, zfw_user_func_data_t *const zfw_data);
void update_tilemap_tile_type_and_display(tilemap_t *const tilemap, const int tx, const int ty, const tile_type_id_t tile_type, const zfw_user_func_data_t *const zfw_data);

#endif
