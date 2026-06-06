#version 330

in float height;

out vec4 fragColor;

uniform float u_maxHeight;

void main() {
    float t = clamp(height / u_maxHeight, 0.0, 1.0);

    vec3 baseColor = vec3(0.05, 0.6, 0.01);
    vec3 tipColor  = vec3(0.2, 0.8, 0.1);

    fragColor = vec4(mix(baseColor, tipColor, t), 1.0);
}
