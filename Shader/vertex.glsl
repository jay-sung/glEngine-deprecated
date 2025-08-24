#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 aNormal;

out vec3 vColor;
out vec2 vUV;
out vec3 vNormal;
out vec3 vFragPos;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

void main()
{
    vColor = aColor;
    vUV = aUV;
    vNormal = mat3(transpose(inverse(uModel))) * aNormal;
    vFragPos = vec3(uModel * vec4(aPos, 1.0));

    gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);
}