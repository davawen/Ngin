#version 330 core
out vec4 FragColor;

uniform sampler2D tex;

in vec4 vertex_color;
in vec2 tex_coord;

void main() {
	// FragColor = vec4(1.0, 0.5, 0.2, 1.0);
	FragColor = texture(tex, tex_coord);
	// FragColor = vertex_color;
}
