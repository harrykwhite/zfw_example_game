#include "world.h"

void init_world(world_t *const world, zfw_user_func_data_t *const zfw_data)
{
    init_tilemap(&world->tilemap, 80, 45, zfw_data);

    init_player(&world->player, zfw_data);
    world->player.pos = zfw_create_vec_2d(world->tilemap.width * TILE_SIZE * 0.5f, world->tilemap.height * TILE_SIZE * 0.5f);
}

void update_world(world_t *const world, zfw_user_func_data_t *const zfw_data)
{
    update_player(&world->player, &world->tilemap, zfw_data);
}
