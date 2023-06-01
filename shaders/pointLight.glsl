#version 330

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoords;

out vec4 fFragColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightPos_vs;
uniform vec3 uLightIntensity;

vec3 blinnPhong() {
  vec3 w0 = normalize(-vPosition);
  vec3 w1 = normalize(uLightPos_vs - vPosition);
  float d = distance(vPosition, uLightPos_vs);
  return (uLightIntensity / (d * d)) * (uKd * dot(w1, vNormal) + (uKs * pow(dot((w0 + w1) / 2, vNormal), uShininess)));
}

void main() {
  fFragColor = vec4(blinnPhong(), 1);
}
