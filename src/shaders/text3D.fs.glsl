#version 330 core

in vec2 vTextCoord;
out vec4 fFragColor;

uniform sampler2D uTexture;

void main()
{
    vec2 fCorrectCoords = vec2(vTextCoord.x, 1-vTextCoord.y);
    vec4 color = texture(uTexture, fCorrectCoords);
    fFragColor = vec4(color.xyz, 1.f);
}   
