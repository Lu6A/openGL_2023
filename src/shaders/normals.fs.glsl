#version 330 core

//in vec3 vVertexNormalVS;
//in vec2 vTextCoord;
out vec4 fFragColor;

//uniform sampler2D uTexture;

void main()
{
    vec3 color = vec3(0.66f, 0.09f, 0.09f);
    fFragColor = vec4(color.xyz, 1.f);
}

