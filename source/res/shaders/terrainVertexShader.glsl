#version 130

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

out vec2 pass_textureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;


void restricted_inverse(mat4 src, out mat4 dst)
{
    mat3 m = transpose(mat3(src));
    vec3 v = vec3(src[3]);
    dst = mat4(m);
    dst[3] = vec4(-m*v,1.0);
}

void main(void){

    vec4 worldPosition = transformationMatrix * vec4(position,1.0f);

    gl_Position =  projectionMatrix * viewMatrix * worldPosition;
    pass_textureCoords = textureCoords;

    surfaceNormal = (transformationMatrix * vec4(normal,0.0f)).xyz;
    toLightVector = lightPosition - worldPosition.xyz;
    mat4 realViewMatrix;
    restricted_inverse(viewMatrix,realViewMatrix);
    toCameraVector = ((realViewMatrix) * vec4(0.0,0.0,0.0,1.0)).xyz - worldPosition.xyz;

}