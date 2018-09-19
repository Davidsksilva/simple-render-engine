#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>

glm::mat4 createRotationMatrix( glm::vec3 rotation ){

    // Create a 4x4 indentity matrix
    glm::mat4 rotXMatrix = glm::mat4(1.0f);

    // Create RotationMatrix on X axis
    rotXMatrix[1][1] = glm::cos(rotation.x);
    rotXMatrix[1][2] = - glm::sin(rotation.x);
    rotXMatrix[2][1] = glm::sin(rotation.x);
    rotXMatrix[2][2] = glm::cos(rotation.x);

    // Create a 4x4 indentity matrix
    glm::mat4 rotYMatrix = glm::mat4(1.0f);

    // Create Rotation Matrix on Y axis
    rotYMatrix[0][0] = glm::cos(rotation.y);
    rotYMatrix[0][2] = glm::sin(rotation.y);
    rotYMatrix[2][0] = - glm::sin(rotation.y);
    rotYMatrix[2][2] = glm::cos(rotation.y);

    // Create a 4x4 indentity matrix
    glm::mat4 rotZMatrix = glm::mat4(1.0f);

    // Create Rotation Matrix on Z axis

    rotZMatrix[0][0] = glm::cos(rotation.z);
    rotZMatrix[0][1] = - glm::sin(rotation.z);
    rotZMatrix[1][0] = glm::sin(rotation.z);
    rotZMatrix[1][1] = glm::cos(rotation.z);

    return rotZMatrix * rotYMatrix * rotXMatrix;
}

glm::mat4 createTransformationMatrix( glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale ){

    glm::mat4 ScaleMatrix = glm::scale(scale);
    glm::mat4 TranslationMatrix = glm::translate(translation);
    glm::mat4 RotationMatrix = createRotationMatrix(rotation);

    return TranslationMatrix * RotationMatrix * ScaleMatrix;
    
}

