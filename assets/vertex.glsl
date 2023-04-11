#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_color;

out vec4 vertex_color;

void main() {
	gl_Position = vec4(a_pos, 1.0);
	vertex_color = vec4(a_color, 1.0);
};
