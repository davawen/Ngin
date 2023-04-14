#pragma once

#include "types.h"

typedef struct {
	u32 vertex_buffer;
	u32 vertices_size;

	u32 index_buffer;
	u32 num_indices;

	u32 vertex_array;
} Shape;

/// Creates a shape with a vertex buffer, index buffer and array object  
/// 
/// You need to set the shape of the vertex array after this using `BufferSchema`
Shape create_model(void *vertices, u32 vertices_size, u32 *indices, u32 num_indices);

/// Draws the given model
///
/// WARNING: The model's vertex array stays bound after this call
void draw_model(Shape model);
