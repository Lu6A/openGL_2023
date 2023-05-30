#version 330 core

//Atributs
layout (location = 0) in vec3 aVertexPosition;
layout (location = 1) in vec3 aVertexNormal;
layout (location = 2) in vec2 aTextCoord;

//matrices uniformes et de transformation
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

//sorties   VS=view space
out vec3 vVertexPositionVS;
out vec3 vVertexNormalVS;
out vec2 vTextCoord;

void main ()
{
	//Coordonnées homogènes
	vec4 vertexPosition = vec4(aVertexPosition, 1);
	vec4 vertexNormal = vec4(aVertexNormal, 1);

	//Valeurs de sortie
	vVertexPositionVS = vec3(uMVMatrix * vertexPosition);
    vVertexNormalVS = vec3(uNormalMatrix * vertexNormal);
    vTextCoord = aTextCoord;

    //Position projetée
    gl_Position = uMVPMatrix * vertexPosition;
}




