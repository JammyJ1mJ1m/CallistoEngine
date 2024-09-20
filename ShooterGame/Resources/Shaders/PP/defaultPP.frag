#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    vec3 color = texture(screenTexture, TexCoords).rgb;

    color = vec3(color.x, color.y, color.z);
   

    FragColor = vec4(color, 1.0);
}