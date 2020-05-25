#version 330 core
out vec4 FragColor;  

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoord;
  
uniform vec4 leftColor;
uniform vec4 rightColor;


void main()
{
    FragColor =  mix(vec4(leftColor),vec4(rightColor),TexCoord.x);
} 