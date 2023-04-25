#pragma once

#include <cglm/cglm.h>

#include "types.h"
#include "model.h"

static Mesh sprite_mesh;

struct Sprite {
	u32 texture;
	vec2 position;
	vec2 size;
};
