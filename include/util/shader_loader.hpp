#ifndef UTIL_SHADER_LOADER_HPP
#define UTIL_SHADER_LOADER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

namespace Dolly {
    class ShaderLoader {
    private:
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shader_program;
	std::string readFile(std::string path);
    public:
	ShaderLoader(): vertexShader(0), fragmentShader(0), shader_program(0) {}
	ShaderLoader(std::string vs, std::string fs);
	void loadVertexShader(std::string path);
	void loadFragmentShader(std::string path);
	void compileShaders();
	GLuint shaderProgram();
    };
}

#endif /* UTIL_SHADER_LOADER_HPP */
