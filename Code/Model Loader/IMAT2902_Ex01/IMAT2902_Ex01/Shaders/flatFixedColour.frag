#version 410

vec3 colour = vec3 (100.0, 1.0, 0.0);

out vec4 frag_colour;

void main() {
	frag_colour = vec4 (colour, 1.0);
}
