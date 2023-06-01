#version 330

struct DirectionalLight {
  vec3 direction;
  vec3 intensity;
};

#define DIRECTIONAL_LIGHTS_COUNT 2

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoords;

out vec4 fFragColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform DirectionalLight uDirectionalLights[DIRECTIONAL_LIGHTS_COUNT];

vec3 blinnPhong(vec3 direction, vec3 intensity) {
  vec3 w0 = normalize(-vPosition);
  vec3 w1 = normalize(direction);
  return intensity * (uKd * dot(w1, vNormal) + (uKs * pow(dot((w0 + w1) / 2, vNormal), uShininess)));
}

vec3 addColor(vec3 color1, vec3 color2) {
  return vec3(max(color1.x, color2.x), max(color1.y, color2.y), max(color1.z, color2.z));
}

void main() {
  vec3 color = vec3(0.f, 0.f, 0.f);

  for(int i = 0; i < DIRECTIONAL_LIGHTS_COUNT; i++) {
    vec3 pingpong = blinnPhong(uDirectionalLights[i].direction, uDirectionalLights[i].intensity);
    color = addColor(color, pingpong);
  }

  fFragColor = vec4(color, 1);
}
