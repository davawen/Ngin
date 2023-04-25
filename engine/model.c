#include "model.h"

Mesh create_mesh(void *vertices, u32 vertices_size, u32 *indices, u32 num_indices) {
	Mesh mesh;
	glGenBuffers(1, &mesh.vertex_buffer);
	mesh.vertices_size = vertices_size;

	glGenBuffers(1, &mesh.index_buffer);
	mesh.num_indices = num_indices;

	glGenVertexArrays(1, &mesh.vertex_array);

	glBindVertexArray(mesh.vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * sizeof(u32), indices, GL_STATIC_DRAW);

	return mesh;
}

void draw_mesh(Mesh mesh) {
	glBindVertexArray(mesh.vertex_array);
	glDrawElements(GL_TRIANGLES, mesh.num_indices, GL_UNSIGNED_INT, NULL);
}
