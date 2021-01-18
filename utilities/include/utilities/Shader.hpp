#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>


/// @class Shader
/// @brief Handle boilerplate for compiling a shader.
template<int ShaderType>
class Shader
{
    // SFINAE: Ensure ShaderType is one of two possible values at compile-time.
    typedef std::integral_constant<int, ShaderType> ShaderTypeHelper;
    static_assert(ShaderTypeHelper::value == GL_FRAGMENT_SHADER
               || ShaderTypeHelper::value == GL_VERTEX_SHADER);
// Data members.
private:
    std::string mFile;
    unsigned int mId;

// Construction and destruction.
public:
    Shader(const std::string &shaderFile)
        : mFile{shaderFile},
          mId{glCreateShader(ShaderTypeHelper::value)}
    {
    }

    ~Shader()
    {
        glDeleteShader(mId);
    }

// Member functions.
public:
    /// @fn    getId
    /// @brief Get OpenGL-generated identifier for this shader.
    constexpr unsigned int getId() const noexcept
    {
        return mId;
    }

    /// @fn    compile
    /// @brief Read source GLSL file into heap and compile it.
    bool compile() const
    {
        std::vector<char> shaderSource;
        std::ifstream sourceStream{mFile};

        std::copy(
            std::istreambuf_iterator<char>{sourceStream},
            std::istreambuf_iterator<char>{},
            std::back_inserter(shaderSource));
        shaderSource.emplace_back('\0');

        const char *shaderSourceBytestring = shaderSource.data();

        glShaderSource(mId, 1, &shaderSourceBytestring, nullptr);
        glCompileShader(mId);

        int compileSuccess;
        glGetShaderiv(mId, GL_COMPILE_STATUS, &compileSuccess);

        return static_cast<bool>(compileSuccess);
    }

};

using VertexShader = Shader<GL_VERTEX_SHADER>;
using FragmentShader = Shader<GL_FRAGMENT_SHADER>;
