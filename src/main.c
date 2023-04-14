#include <stdio.h>
#include <unistd.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "ngin.h"

int main() {
	GLFWwindow *window = ngin_init(800, 600);
	if (window == NULL) {
		ngin_destroy();
		return -1;
	}

	u32 vertex_shader = create_shader_from_file(GL_VERTEX_SHADER, "assets/vertex.glsl");
	u32 fragment_shader = create_shader_from_file(GL_FRAGMENT_SHADER, "assets/frag.glsl");
	u32 shader_program = create_linked_shader_program(vertex_shader, fragment_shader);

	f32 vertices[] = {
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f
	};
	u32 indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	BufferSchema schema = {
		.num = 2,
		.attributes = (Attribute[]){
			{ GL_FLOAT, 3, true },
			{ GL_FLOAT, 3, true }
		}
	};

	Shape model = create_model(vertices, sizeof(vertices), indices, sizeof(indices)/sizeof(u32));
	apply_buffer_schema(schema);
	glBindVertexArray(0); // unbind VAO

	// i32 added_color_location = glGetUniformLocation(shader_program, "added_color");
	while (!glfwWindowShouldClose(window)) {
		glClearColor(.2f, .3f, .3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shader_program);
		draw_model(model);

		ngin_end_frame(window);
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glDeleteProgram(shader_program);

	ngin_destroy();

	return 0;
}
