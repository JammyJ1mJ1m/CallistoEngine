#version 330 core
in vec3 fColor;
out vec4 color;

void main()
{
    color = vec4(fColor, 1);   
    //color = vec4(1, 0, 0, 1);
}