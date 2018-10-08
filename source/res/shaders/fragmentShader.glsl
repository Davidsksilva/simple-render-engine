#version 130

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

    float DiffuseFactor = dot(unitNormal, unitLightVector);

    vec4 DiffuseColor = vec4(0,0,0,0);
    vec4 SpecularColor = vec4(0,0,0,0);

    if ( DiffuseFactor > 0 ){

        DiffuseColor = vec4(lightColor,1.0f) * lightIntensity * DiffuseFactor;
        float brightness = max(DiffuseFactor, 0.2);
        vec3 diffuse = brightness * lightColor;

        vec3 unitVectorToCamera = normalize(toCameraVector);
        vec3 lightDirection = -unitLightVector;
        vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

        float SpecularFactor = dot(reflectedLightDirection, unitVectorToCamera);

        if( SpecularFactor > 0 ){
            SpecularFactor = pow(SpecularFactor, specularPower);
            SpecularColor = vec4(SpecularFactor * specularIntensity * lightColor,1.0f);
        }
    }

    out_Color = texture(textureSampler, pass_textureCoords) * (AmbientColor + DiffuseColor + SpecularColor);
}