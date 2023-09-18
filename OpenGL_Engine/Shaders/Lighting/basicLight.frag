#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;

    sampler2D  diffuse; // base texture map
    sampler2D specular;      
    sampler2D emission; 
    float emissionBrightness;
    float shininess;
}; 
uniform Material material;


struct DirectionalLight {
    vec3 direction;

    vec3 ambient; // not a whole lot going on here really
    vec3 diffuse; // base colour
    vec3 specular; // reflection colour

};
uniform DirectionalLight dirLight;

#define NR_POINT_LIGHTS 4

struct PointLight {
    vec3 position;

    vec3 ambient; // not a whole lot going on here really
    vec3 diffuse; // base colour
    vec3 specular; // reflection colour

    float constant;
    float linear;
    float quadratic;
};
uniform PointLight pointLight[NR_POINT_LIGHTS];

struct SpotLight {
    vec3 position;
    vec3 direction;

    vec3 ambient; // not a whole lot going on here really
    vec3 diffuse; // base colour
    vec3 specular; // reflection colour

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
};
uniform SpotLight spotLight;

in vec3 FragPos;  
in vec3 Normal; 
in vec2 TexCoords;
  
uniform vec3 viewPos;

vec4 calculateSpotLight()
{
    vec4 final = vec4(0);
    vec3 lightDir = normalize(spotLight.position - FragPos);
    
    // check if lighting is inside the spotlight cone
    float theta = dot(lightDir, normalize(-spotLight.direction)); 
    
    if(theta > spotLight.cutOff) // remember that we're working with angles as cosines instead of degrees so a '>' is used.
    {    
        // ambient
        vec3 ambient = spotLight.ambient * texture(material.diffuse, TexCoords).rgb;
        
        // diffuse 
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = spotLight.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
        
        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = spotLight.specular * spec * texture(material.specular, TexCoords).rgb;  
        
        // attenuation
        float distance    = length(spotLight.position - FragPos);
        float attenuation = 1.0 / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));    

        // ambient  *= attenuation; // remove attenuation from ambient, as otherwise at large distances the light would be darker inside than outside the spotlight due the ambient term in the else branch
        diffuse   *= attenuation;
        specular *= attenuation;   
            
        vec3 result = ambient + diffuse + specular;
        final = vec4(result, 1.0);
        return final;
    }
    else 
    {
        // else, use ambient light so scene isn't completely dark outside the spotspotLight.
        final = vec4(spotLight.ambient * texture(material.diffuse, TexCoords).rgb, 1.0);
        return final;
    }
}
vec4 calculatePointLight(int i)
{
    // ambient
    vec3 ambient = pointLight[i].ambient * texture(material.diffuse, TexCoords).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(pointLight[i].position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = pointLight[i].diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = pointLight[i].specular * spec * texture(material.specular, TexCoords).rgb;  
    
    // attenuation
    float distance    = length(pointLight[i].position - FragPos);
    float attenuation = 1.0 / (pointLight[i].constant + pointLight[i].linear * distance + pointLight[i].quadratic * (distance * distance));    

    ambient  *= attenuation;  
    diffuse   *= attenuation;
    specular *= attenuation;   
        
    vec3 result = ambient + diffuse + specular;
    vec4 colour = vec4(result, 1.0);
    return colour;
}


vec4 calculateDirLight()
{
// ambient
    vec3 ambient = dirLight.ambient * vec3(texture(material.diffuse, TexCoords));
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    //  vec3 lightDir = normalize(dirLight.position - FragPos); // original
    vec3 lightDir = normalize(-dirLight.direction);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = dirLight.diffuse * diff * vec3(texture(material.diffuse, TexCoords));  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = dirLight.specular * (spec * vec3(texture(material.specular, TexCoords)));  

    // emission
    vec3 emission = vec3(texture(material.emission, TexCoords));
    emission = emission * material.emissionBrightness;
        
    vec3 result = ambient + diffuse + specular + emission;
    vec4 colour = vec4(result, 1.0);
    return colour;
}

void main()
{
vec4 total = vec4(0);

    //total = calculateDirLight();

    for(int i = 0; i < NR_POINT_LIGHTS; i++)
    {
        total += calculatePointLight(i);
    }
    //total += calculateSpotLight();
    FragColor = total;
} 