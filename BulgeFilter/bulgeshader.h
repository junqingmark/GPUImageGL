#pragma once
#include <string>

std::string createBulgeFilterVertexShader()
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

std::string createFragmentShader()
{
	std::string str = "";
	str = str + "#version 330 core\n"
		+ "in vec2 textureCoordinate;\n"
		+ "out vec4 FragColor;\n"
		+ "uniform sampler2D inputImageTexture;\n"
		+ "\n"
		+ "void main()\n"
		+ "{\n"
		+ "		FragColor=texture(inputImageTexture, textureCoordinate);\n"
		+ "}\n";

	return str;
}

std::string createBulgeFilterFragmentShader()
{
	std::string str = "";
	str = str + "#version 330 core\n"
		+ "in vec2 textureCoordinate;\n"
		+ "out vec4 FragColor;\n"
		+ "uniform sampler2D inputImageTexture;\n"
		+ "\n"
		+ "uniform float aspectRatio;\n"
		+ "uniform vec2 center;\n"
		+ "uniform float radius;\n"
		+ "uniform float scale;\n"
		+ "\n"
		+ "void main()\n"
		+ "{\n"
		+ "  vec2 textureCoordinateToUse = vec2(textureCoordinate.x, (textureCoordinate.y * aspectRatio + 0.5 - 0.5 * aspectRatio));\n"
		+ "  float dist = distance(center, textureCoordinateToUse);\n"
		+ "  textureCoordinateToUse = textureCoordinate;\n"
		+ "\n"
		+ "if(dist < radius)\n"
		+ "{\n"
		+ "textureCoordinateToUse -= center;\n"
		+ "float percent = 1.0 - ((radius - dist) / radius) * scale;\n"
		+ "percent = percent * percent;\n"
		+ "textureCoordinateToUse = textureCoordinateToUse * percent;\n"
		+ "textureCoordinateToUse += center;\n"
		+ "}\n"
		+ "FragColor = texture(inputImageTexture, textureCoordinateToUse);\n"
		+ "}\n";

	return str;
}