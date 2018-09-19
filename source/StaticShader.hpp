#include "ShaderProgram.hpp"

class StaticShader : public ShaderProgram{
    
    protected:

    GLuint loc_transformationMatrix;

    void bindAttributes () override;
    void getAllUniformLocations () override;

    public:

    StaticShader();
    void loadTransformationMatrix( glm::mat4 matrix );

};