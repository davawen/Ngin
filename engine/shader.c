#include "shader.h"

void check_shader_error(unsigned int shader) {
	int success;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char info[512];
		glGetShaderInfoLog(shader, 512, NULL, info);
		LOG("error: failed to compile shader:\n%s\n", info);
	}
}

u32 create_shader(GLenum type, const char *source) {
	u32 shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	check_shader_error(shader);

	return shader;
}

u32 create_shader_from_file(GLenum type, const char *filename) {
	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		LOG("error: could not open file %s\n", filename);
		goto cleanup;
	}
	fseek(f, 0, SEEK_END);
	i32 len = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	char *source = malloc(len + 1);
	if (source == NULL) {
		LOG("error: failed to allocate memory\n");
		goto cleanup;
	}
	fread(source, 1, len, f);
	source[len] = '\0'; // fread does not set null terminator

	u32 shader = create_shader(type, source);

cleanup:
	fclose(f);
	free(source);

	return shader;
}

u32 create_linked_shader_program(u32 vertex, u32 fragment) {
	u32 shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex);
	glAttachShader(shader_program, fragment);
	glLinkProgram(shader_program);

	int success;
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if(!success) {
		char info[512];
		glGetProgramInfoLog(shader_program, 512, NULL, info);
		LOG("error: failed to link shader program:\n%s\n", info);
	}

	return shader_program;
}
