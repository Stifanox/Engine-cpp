#version 330 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aColor;

out vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = projection * view * model * aPos;
   color = aColor;
};