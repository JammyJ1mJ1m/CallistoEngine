#version 330 core

out vec4 FragColor; // Output color

in vec2 TexCoords; // Input texture coordinates

uniform sampler2D texture1; // Texture sampler

void main()
{
    FragColor = texture(texture1, TexCoords); // Sample the texture
}