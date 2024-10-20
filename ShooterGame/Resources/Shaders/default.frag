
#version 330 core
out vec4 FragColor;
  
// in vec3 ourColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D diffuseTex;
uniform sampler2D emissionTex;
uniform sampler2D specularMap;
uniform vec3 viewPos;

#define NR_POINT_LIGHTS 99

struct Light {
    vec3 position;  
//  
//    vec3 ambient;
    vec3 diffuse;
//    vec3 specular;
//	
//    float constant;
//    float linear;
//    float quadratic;
}; 
//
uniform Light light[NR_POINT_LIGHTS];
uniform float time;

vec4 calculatePointLight(int i)
{

vec3 lightPos = light[i].position;

    vec3 lightColor = light[i].diffuse;
    vec3 specColor = lightColor;
    vec3 objectColor = texture(diffuseTex, TexCoord).rgb;
    // ambient
    vec3 ambient = 0.1 * objectColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);


    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.99;
    float specularPower = 256;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(norm, halfwayDir), 0.0), specularPower);



    vec3 specular = specularStrength * spec * specColor * texture(specularMap, TexCoord).rgb;  
        
    vec3 result = (ambient + diffuse + specular) * objectColor;

    return vec4(result, 1.0);
}


void main()
{
   vec4 color = vec4(0,0,0,1);

    // Calculate lighting from all point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        color += calculatePointLight(i);

    // Sample the emission texture
    vec3 emission = texture(emissionTex, TexCoord).rgb;
    color = normalize(color)*2;
    // Add emission to the final color
    vec4 result = color;
    result = result + vec4(emission,1);
    FragColor =  vec4(color.rgb + (emission * 3), 1.0);

}
