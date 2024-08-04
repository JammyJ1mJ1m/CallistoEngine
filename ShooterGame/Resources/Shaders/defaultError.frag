

//#version 330 core
//out vec4 FragColor;
//  
//in vec3 ourColor;
//in vec2 TexCoord;
//
//uniform sampler2D ourTexture;
//
//void main()
//{
//    FragColor = texture(ourTexture, TexCoord);
//}





#version 330 core
out vec4 FragColor;
  
// in vec3 ourColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D ourTexture;

uniform float fTime;



vec4 calculatePointLight(int i)
{
    // generate point lighting using input texture as ambient

    vec3 objectColor = texture(ourTexture, TexCoord).xyz;
  
    //vec3 result =  (objectColor * 2) + sin(fTime) + 0.5;
    //return vec4(result, 1.0);

    // Increase the brightness factor
float brightnessFactor = 1.2; // Adjust this value to increase or decrease brightness

// Pulsation amplitude and speed
float pulsationAmplitude = 0.5; 
float pulsationSpeed = 1.0; 
float pulsation = sin(fTime * pulsationSpeed) * pulsationAmplitude;

vec3 result = (objectColor * brightnessFactor) + pulsation;
    return vec4(result, 1.0);

}


void main()
{
    FragColor = calculatePointLight(0);
}
