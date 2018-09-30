#version 400 core

in vec2 pass_textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;

out vec4 out_Color;

uniform sampler2D textureSampler;
uniform vec3 lightColor;
uniform float lightIntensity;

uniform float specularIntensity;
uniform float specularPower;

void main(void){

    vec4 AmbientColor = vec4(lightColor * lightIntensity,1.0f);

    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitLightVector = normalize(toLightVector);

    float diffuseFactor = dot(unitNormal, unitLightVector);
    float brightness = max(diffuseFactor, 0.02);
    vec3 diffuse = brightness * lightColor;

    vec3 unitVectorToCamera = normalize(toCameraVector);
    vec3 lightDirection = -unitLightVector;
    vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

    float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
    specularFactor = max(specularFactor, 0.1 );
    float dampedFactor = pow(specularFactor, specularPower);
    vec3 finalSpecular = dampedFactor * specularIntensity * lightColor;
    

    out_Color = vec4(diffuse, 1.0) * texture(textureSampler, pass_textureCoords) + vec4(finalSpecular,1.0) + AmbientColor;
}