#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include "log.h"
#include "types.h"

void check_shader_error(unsigned int shader);

u32 create_shader(GLenum type, const char *source);
u32 create_shader_from_file(GLenum type, const char *filename);
u32 create_linked_shader_program(u32 vertex, u32 fragment);
