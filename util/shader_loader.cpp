#include "../include/util/shader_loader.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <stdexcept>

namespace Dolly {
    std::string ShaderLoader::readFile(std::string path)
    {
	std::cout << "Reading Shader File " << path << std::endl;
	std::ifstream shader_file(path);
	std::string shader_str;

	shader_file.seekg(0, std::ios::end);
	shader_str.reserve(shader_file.tellg()); // Allocate string upfront
	shader_file.seekg(0, std::ios::beg);

	shader_str.assign((std::istreambuf_iterator<char>(shader_file)),
			   std::istreambuf_iterator<char>());

	return shader_str;
    }

    ShaderLoader::ShaderLoader(std::string vs, std::string fs)
    {
	loadVertexShader(vs);
	loadFragmentShader(fs);
	compileShaders();
    }

    void ShaderLoader::loadVertexShader(std::string path)
    {
	const char* shader_str = readFile(path).c_str();
	GLint len = strlen(shader_str);
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &shader_str, &len);
    }

    void ShaderLoader::loadFragmentShader(std::string path)
    {
	const char* shader_str = readFile(path).c_str();
	GLint len = strlen(shader_str);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &shader_str, &len);
    }

    void ShaderLoader::compileShaders()
    {
	if (vertexShader == 0) {
	    throw std::runtime_error("Vertex Shader is NULL!");
	}
	if (fragmentShader == 0) {
	    throw std::runtime_error("Fragment Shader is NULL!");
	}
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);
	shader_program = glCreateProgram();
	glAttachShader(shader_program, fragmentShader);
	glAttachShader(shader_program, vertexShader);
	glLinkProgram(shader_program);
    }

    GLuint ShaderLoader::shaderProgram()
    {
	if (shader_program == 0) {
	    throw std::runtime_error("Shader program is NULL!");
	}
	return shader_program;
    }
}
