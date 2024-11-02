#ifndef __TEX_SRC_RECTS_H__
#define __TEX_SRC_RECTS_H__

#include <zfw_common_math.h>

typedef enum
{
    TEX_SRC_RECT_ID__PLAYER,
    TEX_SRC_RECT_ID__DIRT_TILE,
    TEX_SRC_RECT_ID__STONE_TILE,

    TEX_SRC_RECT_COUNT
} tex_src_rect_id_t;

extern const zfw_rect_t k_tex_src_rects[TEX_SRC_RECT_COUNT];

#endif
