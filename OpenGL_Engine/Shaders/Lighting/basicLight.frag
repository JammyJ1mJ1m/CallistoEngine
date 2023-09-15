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

struct Light {
    vec3 position;

    vec3 ambient; // not a whole lot going on here really
    vec3 diffuse; // base colour
    vec3 specular; // reflection colour
};

in vec3 FragPos;  
in vec3 Normal; 
in vec2 TexCoords;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, TexCoords)));  

    // emission
    vec3 emission = vec3(texture(material.emission, TexCoords));
    emission = emission * material.emissionBrightness;
        
    vec3 result = ambient + diffuse + specular + emission;
    FragColor = vec4(result, 1.0);
} 