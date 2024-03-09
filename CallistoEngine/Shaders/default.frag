#version 330 core
out vec4 FragColor;
//
//in vec2 TexCoords;
//
//uniform sampler2D texture_diffuse1;
//uniform sampler2D texture_emission1;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} 
//void main()
//{    
//    vec4 final = vec4(0);
//
//        vec3 diffuse = texture(texture_diffuse1, TexCoords).rgb ;  
//
//        vec3 emission = vec3(texture(texture_emission1, TexCoords));
//        emission = emission * 1.0f;
//
//        vec3 result = diffuse + emission ;//+ emission;
//        final = vec4(result, 1.0);
//        FragColor = final;
//
//
//    //FragColor = texture(texture_diffuse1, TexCoords)+ texture(texture_emission1,TexCoords);
//}