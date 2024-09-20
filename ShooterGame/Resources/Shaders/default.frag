
#version 330 core
out vec4 FragColor;
  
// in vec3 ourColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec3 viewPos;

#define NR_POINT_LIGHTS 3

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
    // generate point lighting using input texture as ambient
     
//    vec3 lightPos = vec3(-8.0f, 15.0f, 15.0f);
vec3 lightPos = light[i].position;

//    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 lightColor = light[i].diffuse;
    vec3 specColor = lightColor;
    vec3 objectColor = texture(ourTexture, TexCoord).rgb;
    // ambient
    vec3 ambient = 0.1 * objectColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    // adjust the diffuse for toon
//    float stepSize = 0.3 * sin( time) + 0.5   ;
//    float stepSize = 0.33;
//
//    for (float i = 0.0; i < 1.0; i += stepSize)
//	{
//		if (diff > i && diff < i + stepSize)
//		{
//			diff = i;
//			break;
//		}
//     }

//if(diff > 0.66)
//diff=1;
//else if(diff > 0.33)
//diff=0.66;
//else
//diff=0.33;

    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.3;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);

//   for (float i = 0.0; i < 1.0; i += stepSize)
//	{
//		if (spec > i && spec < i + stepSize)
//		{
//			spec = i;
//			break;
//		}
//     }
//    
//    if(spec > 0.66)
//spec=1;
//else if(spec > 0.33)
//spec=0.66;
//else
//spec=0.33;

    vec3 specular = specularStrength * spec * specColor;  
        
    vec3 result = (ambient + diffuse + specular) * objectColor;

    // matrix colour 
//    result = vec3(pow(result.x, 7.0 / 5.0), result.y, pow(result.z, 8.0 / 5.0));

    return vec4(result, 1.0);
}


void main()
{
vec4 color = vec4(0,0,0,1);
    //FragColor = texture(ourTexture, TexCoord);
//    FragColor = calculatePointLight(0);
        for(int i = 0; i < NR_POINT_LIGHTS; i++)
        color += calculatePointLight(i); //, norm, FragPos, viewDir

        FragColor = normalize( color);
    
    //FragColor = vec4(FragPos,1);
    //FragColor = calculatePointLight(0);
}
