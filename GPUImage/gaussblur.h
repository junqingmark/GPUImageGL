#pragma once
#include <string>

std::string createVertexShader()
{
	std::string str = "";
	str = str + "#version 330 core\n"
		+ "layout (location = 0) in vec3 aPos;\n"
		+ "layout (location = 1) in vec2 inputTextureCoordinate;\n"
		+ "\n"
		+ "out vec2 textureCoordinate;\n"
		+ "\n"
		+ "void main()\n"
		+ "{\n"
		+ "	gl_Position = vec4(aPos, 1.0);\n"
		+ "	textureCoordinate = inputTextureCoordinate;\n"
		+ "}\n";

	return str;
}

std::string createFragmentShader()
{
	std::string str = "";
	str = str + "#version 330 core\n"
		+ "out vec4 FragColor;\n"
		+ "uniform sampler2D inputImageTexture;\n"
		+ "uniform float texelWidthOffset;\n"
		+ "uniform float texelHeightOffset;\n"
		+ "uniform vec2 resolution;\n"
		+ "\n"
		+ "in vec2 textureCoordinate;\n"
		+ "\n"
		+ "void main()\n"
		+ "{\n"
		+ "	  vec3 sum = vec3(0.0);\n"
		+ "   "
		+ "\n"
		+ "    sum += texture(inputImageTexture, textureCoordinate.xy + 4 * textureCoordinate / resolution).rgb * 0.05;\n"
		+ "    sum += texture(inputImageTexture, textureCoordinate.xy + 3 * textureCoordinate / resolution).rgb * 0.09;\n"
		+ "    sum += texture(inputImageTexture, textureCoordinate.xy + 2 * textureCoordinate / resolution).rgb * 0.12;\n"
		+ "    sum += texture(inputImageTexture, textureCoordinate.xy + textureCoordinate / resolution).rgb * 0.15;\n"
		+ "    sum += texture(inputImageTexture, textureCoordinate.xy).rgb * 0.18;\n"
		+ "    sum += texture(inputImageTexture, textureCoordinate.xy - textureCoordinate / resolution).rgb * 0.15;\n"
		+ "    sum += texture(inputImageTexture, textureCoordinate.xy - 2 * textureCoordinate / resolution).rgb * 0.12;\n"
		+ "    sum += texture(inputImageTexture, textureCoordinate.xy - 3 * textureCoordinate / resolution).rgb * 0.09;\n"
		+ "    sum += texture(inputImageTexture, textureCoordinate.xy - 4 * textureCoordinate / resolution).rgb * 0.05;\n"
		+ "\n"
		+ "FragColor = vec4(sum, 1.0);\n"
		+ "}\n";

	return str;
}