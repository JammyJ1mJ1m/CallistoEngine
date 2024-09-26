#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    vec3 color = texture(screenTexture, TexCoords).rgb;

    color = vec3(pow(color.x, 7.0 / 5.0), color.y, pow(color.z, 8.0 / 5.0));
   
   if(color == vec3(0,0,0))
   {
   color = vec3(1,0,0);
   }
    FragColor = vec4(color, 1.0);
}