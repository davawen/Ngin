#version 330 core
out vec4 FragColor;

in vec4 vertex_color;

void main() {
	// FragColor = vec4(1.0, 0.5, 0.2, 1.0);
	FragColor = vertex_color;
}
