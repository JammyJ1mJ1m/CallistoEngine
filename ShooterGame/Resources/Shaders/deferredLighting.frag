#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;    // 0
uniform sampler2D gNormal;      // 1
uniform sampler2D gAlbedoSpec;  // 2
uniform sampler2D gEmission;    // 3

struct Light {
    vec3 Position;
    vec3 Color;
    float Linear;
    float Quadratic;
};
const int NR_LIGHTS = 1;
uniform Light lights[NR_LIGHTS];

uniform vec3 viewPos;

uniform int outputMode;

void main()
{             
    // Retrieve data from G-buffer
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = normalize(texture(gNormal, TexCoords).rgb);
    vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;
    vec3 Emission = texture(gEmission, TexCoords).rgb;

    // Ambient
    vec3 lighting = Diffuse * 0.1; 
    vec3 viewDir = normalize(viewPos - FragPos);

    for (int i = 0; i < NR_LIGHTS; ++i) 
    {
        vec3 lightDir = normalize(lights[i].Position - FragPos);

        // Diffuse
        float diff = max(dot(Normal, lightDir), 0.0);
        vec3 diffuse = diff * Diffuse * lights[i].Color;

        // Specular
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(Normal, halfwayDir), 0.0), 64.0); // Adjust shininess as needed
        vec3 specular = spec * vec3(1,0,0) ;

        // Attenuation
        float distance = length(lights[i].Position - FragPos);
        float attenuation = 1.0 / (1.0 + lights[i].Linear * distance + lights[i].Quadratic * (distance * distance));
        diffuse *= attenuation;
        // specular *= attenuation; // disable to exaggerate col

        lighting +=  specular ;
    }
    



switch(outputMode)
{   case 0: FragColor = vec4(lighting, 1.0); break;
    case 1: FragColor = vec4(FragPos, 1.0); break;
    case 2: FragColor = vec4(Normal, 1.0); break;
    case 3: FragColor = vec4(TexCoords,0.0, 1.0); break;
    case 4: FragColor = vec4(Diffuse, 1.0); break;
    case 5: FragColor = vec4(Emission, 1.0) ; break;
}

}
