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

#define NR_SPOT_LIGHTS 4

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
uniform SpotLight spotLight[NR_SPOT_LIGHTS];

in vec3 FragPos;  
in vec3 Normal; 
in vec2 TexCoords;
  
uniform vec3 viewPos;

vec4 calculateEmission(int i)
{
    vec3 emission = vec3(texture(material.emission, TexCoords));
    emission = emission * material.emissionBrightness;
    return vec4(emission,0);
}


vec4 calculateSpotLight(int i)
{
    vec4 final = vec4(0);
    vec3 lightDir = normalize(spotLight[i].position - FragPos);
    
    // check if lighting is inside the spotlight cone
    float theta = dot(lightDir, normalize(-spotLight[i].direction)); 
    
    if(theta > spotLight[i].cutOff) // remember that we're working with angles as cosines instead of degrees so a '>' is used.
    {    
        // ambient
        vec3 ambient = spotLight[i].ambient * texture(material.diffuse, TexCoords).rgb;
        
        // diffuse 
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = spotLight[i].diffuse * diff * texture(material.diffuse, TexCoords).rgb * 2;  
        
        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = spotLight[i].specular * spec * texture(material.specular, TexCoords).rgb;  
        
        // attenuation
        float distance    = length(spotLight[i].position - FragPos);
        float attenuation = 1.0 / (spotLight[i].constant + spotLight[i].linear * distance + spotLight[i].quadratic * (distance * distance));    

        // ambient  *= attenuation; // remove attenuation from ambient, as otherwise at large distances the light would be darker inside than outside the spotlight due the ambient term in the else branch
        diffuse   *= attenuation;
        specular *= attenuation;
            
            // emission
        vec3 emission = vec3(texture(material.emission, TexCoords));
        emission = emission * material.emissionBrightness;

        vec3 result = ambient + diffuse + specular ;//+ emission;
        final = vec4(result, 1.0);
        return final;
    }
    else 
    {
        // else, use ambient light so scene isn't completely dark outside the spotspotLight.
        final = vec4(spotLight[i].ambient * texture(material.diffuse, TexCoords).rgb, 1.0);
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
        
   // emission
    vec3 emission = vec3(texture(material.emission, TexCoords));
    emission = emission * material.emissionBrightness;
        
    vec3 result = ambient + diffuse + specular;// + emission;
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
        
    vec3 result = ambient + diffuse + specular ;
    vec4 colour = vec4(result, 1.0);
    return colour;
}

void main()
{
vec4 total = vec4(0);

    total = calculateDirLight();

    for(int i = 0; i < NR_POINT_LIGHTS; i++)
    {
        total += calculatePointLight(i);
    }

    for(int i = 0; i < NR_SPOT_LIGHTS; i++)
    {
        total += calculateSpotLight(i);
    }

    // draw the emission last as it is a "light" output so other lights shouldnt intefer with it
    total += calculateEmission(0);
    //total += calculateSpotLight(0) * 3;
    FragColor = total;
} 