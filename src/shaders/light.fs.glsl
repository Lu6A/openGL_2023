// #version 330 core

// in vec2 vTextCoord;
// in vec3 vVertexNormalVS;
// out vec4 fFragColor;

// uniform sampler2D uTexture;
// uniform vec3 uLightDirection;
// uniform vec3 uSpecularLightColor;
// uniform float uSpecularLightIntensity;
// uniform float uSpecularShininess;
// uniform vec3 uCameraPosition;

// void main()
// {
//     vec2 fCorrectCoords = vec2(vTextCoord.x, 1 - vTextCoord.y);
//     vec4 color = texture(uTexture, fCorrectCoords);

//     vec3 normal = normalize(vVertexNormalVS);
//     vec3 lightDirection = normalize(uLightDirection);
//     vec3 viewDirection = normalize(uCameraPosition - gl_FragCoord.xyz);

//     vec3 reflectionDirection = reflect(-lightDirection, normal);
//     float specularFactor = pow(max(dot(reflectionDirection, viewDirection), 0.0), uSpecularShininess);
//     vec3 specularColor = uSpecularLightColor * uSpecularLightIntensity;
//     vec3 finalColor = color.rgb + specularColor * specularFactor;

//     fFragColor = vec4(finalColor, color.a);
// }



#version 330 core


//sorties   VS=view space
in vec3 vVertexPositionVS;
in vec3 vVertexNormalVS;
in vec2 vTextCoord;

// uniform int uNumLights;  // Nombre de lumières
// uniform vec3 uLightPos[MAX_LIGHTS];  // Tableau de positions des lumières
// uniform vec3 uLightIntensity[MAX_LIGHTS];  // Tableau d'intensités des lumières

uniform vec3 uLightPos1;
uniform vec3 uLightPos2;
uniform vec3 uLightDir;

uniform vec3 uLightIntensity1;
uniform vec3 uLightIntensity2;
uniform vec3 uLightIntensity3;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform sampler2D uTexture;

out vec4 fFragColor;

vec3 blinnPhong(vec3 light_pos, vec3 light_intensity) {
    vec3 result = vec3(0.0);

        float d = distance(vVertexPositionVS, light_pos);
        vec3 Li = light_intensity / (d * d);
        vec3 N = vVertexNormalVS;
        vec3 w0 = normalize(-vVertexPositionVS);
        vec3 wi = normalize(light_pos - vVertexPositionVS);
        vec3 halfVector = normalize(w0 + wi);

        result += Li * (uKd * dot(wi, N) + uKs * pow(dot(halfVector, N), uShininess));
    

    return result;
}

vec3 blinnPhong_dir(vec3 light_dir, vec3 light_intensity){
    vec3 Li = light_intensity;
    vec3 N = vVertexNormalVS;
    vec3 w0 = normalize(-vVertexPositionVS);
    vec3 wi = normalize(light_dir);
    vec3 halfVector = (w0+wi)/2.f;

    
    return Li * ( uKd * dot(wi,N) + uKs * pow(dot(halfVector, N), uShininess));
    
}

void main() {
    vec2 fCorrectCoords = vec2(vTextCoord.x, 1-vTextCoord.y);

    vec3 lights = blinnPhong(uLightPos1, uLightIntensity1)+ blinnPhong(uLightPos2, uLightIntensity2) + blinnPhong_dir(uLightDir, uLightIntensity3);
    vec3 color_texture = texture(uTexture, fCorrectCoords).rgb;

    

    fFragColor = vec4( color_texture * lights , 1.0) ;

    
}