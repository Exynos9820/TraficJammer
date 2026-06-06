#version 330

in vec3 vertexPosition;
out float height;
uniform mat4 mvp;
uniform float u_time;

void main() {
    vec3 pos = vertexPosition;
    height = pos.z;  // 0 at base, 1 at tip
    pos.z = 0.0;

    float sway = sin(u_time * 2.0 + pos.x * 0.05) * 2.0 * height;
    pos.x += sway;

    gl_Position = mvp * vec4(pos, 1.0);
}
