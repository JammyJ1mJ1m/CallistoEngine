#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixAmount;
uniform vec3 newCol;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	vec4 Col = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixAmount);
//	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixAmount);
//	if(Col.w < 1)
//	{
//		Col.w ==0;
//	}
	if(Col.w == 0)
	{
		discard;
	}
	FragColor = Col * vec4(newCol,0);
}