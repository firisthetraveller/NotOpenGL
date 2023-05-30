#version 330

in vec3 vPosition_vs;
in vec3 vNormal;

out vec4 fFragColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

vec3 blinnPhong() {
  vec3 w0 = normalize(-vPosition_vs);
  vec3 w1 = normalize(uLightDir_vs);
  return uLightIntensity * (uKd * dot(w1, vNormal) + (uKs * pow(dot((w0 + w1) / 2, vNormal), uShininess)));
}

void main() {
  fFragColor = vec4(blinnPhong(), 1);
}
