#pragma once
#include <string>

std::string createSaturationFilterVertexShader()
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

std::string createSaturationFilterFragmentShader()
{
	std::string str = "";
	str = str + "#version 330 core\n"
		+ "in vec2 textureCoordinate;\n"
		+ "out vec4 FragColor;\n"
		+ "uniform sampler2D inputImageTexture;\n"
		+ "uniform float saturation;\n"
		+ "const vec3 luminanceWeight = vec3(0.2125, 0.7154, 0.0721);\n"
		+ "\n"
		+ "void main()\n"
		+ "{\n"
		+ "vec4 textureColor = texture(inputImageTexture, textureCoordinate);\n"
		+ "float luminance = dot(textureColor.rgb, luminanceWeight);\n"
		+ "vec3 grayScaleColor = vec3(luminance);\n"
		+ "\n"
		+ "FragColor = vec4(mix(grayScaleColor, textureColor.rgb, saturation), textureColor.a);\n"
		+ "}\n";

	return str;
}
