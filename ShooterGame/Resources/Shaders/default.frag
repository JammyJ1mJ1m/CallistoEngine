
#version 330 core
out vec4 FragColor;
  
// in vec3 ourColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec3 viewPos;



vec4 calculatePointLight(int i)
{
    // generate point lighting using input texture as ambient
     
    vec3 lightPos = vec3(-8.0f, 15.0f, 15.0f);
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 specColor = vec3(1.0, 0.0, 1.0);
    vec3 objectColor = texture(ourTexture, TexCoord).rgb;
    // ambient
    vec3 ambient = 0.1 * objectColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.3;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
    
    vec3 specular = specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + diffuse + specular) * objectColor;
    return vec4(result, 1.0);
}


void main()
{

    //FragColor = texture(ourTexture, TexCoord);
    FragColor = calculatePointLight(0);
    
    //FragColor = vec4(FragPos,1);
    //FragColor = calculatePointLight(0);
}
