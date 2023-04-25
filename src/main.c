#include <stdio.h>
#include <unistd.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>

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
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};

	u32 indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	BufferSchema schema = {
		.num = 3,
		.attributes = (Attribute[]){
			{ GL_FLOAT, 3, true },
			{ GL_FLOAT, 3, true },
			{ GL_FLOAT, 2, true }
		}
	};

	Mesh model = create_mesh(vertices, sizeof(vertices), indices, sizeof(indices)/sizeof(u32));
	apply_buffer_schema(schema);
	glBindVertexArray(0); // unbind VAO

	stbi_set_flip_vertically_on_load(true);
	int width, height, channels;
	u8 *texture_data = stbi_load("assets/image.png", &width, &height, &channels, 3);
	if (!texture_data) {
		LOG("error: couldn't load image\n");
		return -1;
	}

	u32 texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texture_data);

	glUseProgram(shader_program);
	glUniform1i(glGetUniformLocation(shader_program, "tex"), 0);

	u32 transformLocation = glGetUniformLocation(shader_program, "transform");

	// i32 added_color_location = glGetUniformLocation(shader_program, "added_color");
	while (!glfwWindowShouldClose(window)) {
		glClearColor(.2f, .3f, .3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shader_program);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		mat4 transform = GLM_MAT4_IDENTITY_INIT;
		glm_rotate(transform, glfwGetTime(), (vec3){0, 0, 1});

		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, (float *)transform);
		draw_mesh(model);

		ngin_end_frame(window);
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glDeleteProgram(shader_program);

	ngin_destroy();

	return 0;
}
