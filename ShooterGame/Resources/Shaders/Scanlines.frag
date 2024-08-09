#version 330 core
out vec4 FragColor;
  
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform float time; 


vec4 Scanlines()
{
    vec2 resolution = vec2(1024.0, 1024.0); 
    float lineThickness = 0.9 ;
    float lineDistance = 15.0;
    int numLines = 50;
    
    float lineSeparation = resolution.y / numLines; 

    float linePattern = mod(gl_FragCoord.y, lineSeparation);

    float lineIntensity = smoothstep(lineThickness, lineThickness + lineDistance, linePattern);

    vec4 texColor = texture(ourTexture, TexCoord);

    // I need to remember how to handle sin wave stuff
    float Amp = 1.0;
    float Freq = 1.0;
    float PhaseShift = 1.0;
    float yOffset = 2.0;
    float shiftedVal = Amp * sin(Freq * time + PhaseShift ) + yOffset;
    vec4 scanlineColor = vec4(0.0, 0.7, 1.0, 0.2 * lineIntensity * shiftedVal);


    return mix(texColor, scanlineColor, scanlineColor.a);
}

void main()
{
    FragColor = Scanlines();
}
