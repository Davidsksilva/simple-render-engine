#include "ShaderProgram.hpp"

class StaticShader : public ShaderProgram{
    
    protected:

    void bindAttributes () override;

    public:

    StaticShader();

};