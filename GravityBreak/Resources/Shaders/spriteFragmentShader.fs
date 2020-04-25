#version 330 core
out vec4 FragColor;  

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoord;
  
uniform sampler2D sprite;
uniform vec4 colour;


void main()
{
    FragColor = texture(sprite, TexCoord).rgba *vec4(colour);
} 