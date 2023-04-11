#include "model.h"

Shape create_model(void *vertices, u32 vertices_size, u32 *indices, u32 num_indices) {
	Shape model;
	glGenBuffers(1, &model.vertex_buffer);
	model.vertices_size = vertices_size;

	glGenBuffers(1, &model.index_buffer);
	model.num_indices = num_indices;

	glGenVertexArrays(1, &model.vertex_array);

	glBindVertexArray(model.vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, model.vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * sizeof(u32), indices, GL_STATIC_DRAW);

	return model;
}

void draw_model(Shape model) {
	glBindVertexArray(model.vertex_array);
	glDrawElements(GL_TRIANGLES, model.num_indices, GL_UNSIGNED_INT, NULL);
}
