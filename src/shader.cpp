#include<core/shader.hpp>

Shader::Shader(const std::string& shaderPath) {
    composedShader = parseShader(shaderPath);
    uId = createShader(composedShader);
}

Shader::~Shader() {
    glDeleteProgram(uId);
}

void Shader::enable() {
    glUseProgram(uId);
}

void Shader::disable() {
    glUseProgram(0);
}

ComposedShader Shader::parseShader(const std::string& filePath) {
    std::ifstream stream(filePath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1, MESH = 2
    };

    std::string line;
    std::stringstream ss[3];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#!") != std::string::npos) {
            if (line.find("vertex shader") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment shader") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            } else if (line.find("mesh shader") != std::string::npos) {
                type = ShaderType::MESH;
            }
        } else {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str(), ss[2].str() };
}

unsigned int Shader::createShader(ComposedShader composedShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, composedShader.VertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, composedShader.FragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(sizeof(char) * length);
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader: " << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}