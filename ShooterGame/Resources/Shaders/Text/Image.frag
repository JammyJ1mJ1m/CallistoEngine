#version 330 core

out vec4 FragColor; // Output color

in vec2 TexCoords; // Input texture coordinates

uniform sampler2D texture1; // Texture sampler
uniform vec4 color;

void main()
{
     FragColor = texture(texture1, TexCoords) * color; // Sample the texture
    //FragColor = vec4(1,0,0,1);
}