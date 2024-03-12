//#version 330 core
//layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aNormal;
//layout (location = 2) in vec2 aTexCoords;
//
//out vec2 TexCoords;
//
//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;
//
//void main()
//{
//    TexCoords = aTexCoords;    
//    gl_Position = projection * view * model * vec4(aPos, 1.0);
//}



#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 transform;
void main()
{
    // gl_Position = vec4(aPos, 1.0);
    gl_Position = transform * vec4(aPos, 1.0f);
    ourColor = aColor;
    TexCoord = aTexCoord;
}