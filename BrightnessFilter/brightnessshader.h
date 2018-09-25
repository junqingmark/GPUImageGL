#pragma once
#include <string>

std::string createBrightnessFilterVertexShader()
{
	std::string str = "";
	str = str + "#version 330 core\n"
		+ "layout (location = 0) in vec3 position;\n"
		+ "layout (location = 1) in vec2 inputTextureCoordinate;\n"
		+ "\n"
		+ "out vec2 textureCoordinate;\n"
		+ "\n"
		+ "void main()\n"
		+ "{\n"
		+ "		gl_Position = vec4(position, 1.0);\n"
		+ "		textureCoordinate = inputTextureCoordinate;\n"
		+ "}\n";

	return str;
}

std::string createBrightnessFilterFragmentShader()
{
	std::string str = "";
	str = str + "#version 330 core\n"
		+ "in vec2 textureCoordinate;\n"
		+ "out vec4 FragColor;\n"
		+ "uniform sampler2D inputImageTexture;\n"
		+ "uniform float brightness;\n"
		+ "void main()\n"
		+ "{\n"
		+ "vec4 textureColor = texture(inputImageTexture, textureCoordinate);\n"
		+ "FragColor = vec4(textureColor.rgb + vec3(brightness), textureColor.a);\n"
		+ "}\n";

	return str;
}

