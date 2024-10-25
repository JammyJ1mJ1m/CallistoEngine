#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D bloomBlur; // Blurred bright areas
uniform sampler2D scene;        // Original scene


//uniform sampler2D albedo;       // blurred 
//uniform sampler2D raw_image;    // unblurred

uniform float bloomIntensity = 3; // How intense the bloom effect should be

void main()
{
//    vec3 original = texture(scene, TexCoords).rgb;
//    vec3 bloom = texture(bloomBlur, TexCoords).rgb;
////    FragColor = vec4(original + bloom * bloomIntensity, 1.0); // Add bloom to the original scene
//    FragColor = vec4(bloom,1);

    vec4 col = texture(bloomBlur, TexCoords);
    float lum = (col.r + col.g + col.b) / 3;
    
    vec4 bloom = col * lum;
    vec4 raw = texture(scene, TexCoords);
    FragColor = raw + bloom ;
}
