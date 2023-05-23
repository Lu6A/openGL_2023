#version 330 core

// Variables d'entrées
in vec3 vVertexPosition;
in vec3 vVertexNormal;
//in vec2 vVertexTexCoords;

// Variables de sorties 
out vec3 fFragColor;

//uniform sampler2D uTexture;

void main()
{
    fFragColor = normalize(vVertexNormal);
    //fFragColor = vec3(1,0,0); // pour tester si on a des vertex
}



