#version 450

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec3 texCoord;

uniform mat4 ProjectionView;
uniform mat4 Model;

void main()
{
    texCoord = vec3(aTexCoord,1);
    vec4 pos = ProjectionView * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}