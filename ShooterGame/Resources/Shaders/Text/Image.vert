#version 330 core

layout(location = 0) in vec3 aPos; 
layout(location = 1) in vec2 aTexCoord; 

out vec2 TexCoords; 

uniform mat4 projection;
uniform vec3 translation; 
void main()
{
    gl_Position = projection * vec4(aPos + translation, 1.0); 
    TexCoords = aTexCoord; 
}