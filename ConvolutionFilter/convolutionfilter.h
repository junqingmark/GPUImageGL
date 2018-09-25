#pragma once
#include <string>

std::string createConvolutionFilterVertexShader()
{
	std::string str = "";

	str = str + "#version 330 core\n"
		+ "layout (location = 0) in vec3 position;\n"
		+ "layout (location = 1) in vec2 inputTextureCoordinate;\n"
		+ "uniform float texelWidth;\n"
		+ "uniform float texelHeight;\n"
		+ "\n"
		+ "out vec2 textureCoordinate;\n"
		+ "out vec2 leftTextureCoordinate;\n"
		+ "out vec2 rightTextureCoordinate;\n"
		+ "\n"
		+ "out vec2 topTextureCoordinate;\n"
		+ "out vec2 topLeftTextureCoordinate;\n"
		+ "out vec2 topRightTextureCoordinate;\n"
		+ "\n"
		+ "out vec2 bottomTextureCoordinate;\n"
		+ "out vec2 bottomLeftTextureCoordinate;\n"
		+ "out vec2 bottomRightTextureCoordinate;\n"
		+ "\n"
		+ "void main()\n"
		+ "{\n"
		+ " gl_Position = vec4(position, 1.0);\n"
		+ "vec2 widthStep = vec2(texelWidth, 0.0);\n"
		+ "vec2 heightStep = vec2(0.0, texelHeight);\n"
		+ "vec2 widthHeightStep = vec2(texelWidth, texelHeight);\n"
		+ "vec2 widthNegativeHeightStep = vec2(texelWidth, -texelHeight);\n"
		+ "\n"
		+ "textureCoordinate = inputTextureCoordinate.xy;\n"
		+ "leftTextureCoordinate = inputTextureCoordinate.xy - widthStep;\n"
		+ "rightTextureCoordinate = inputTextureCoordinate.xy + widthStep;\n"
		+ "\n"
		+ "topTextureCoordinate = inputTextureCoordinate.xy - heightStep;\n"
		+ "topLeftTextureCoordinate = inputTextureCoordinate.xy - widthHeightStep;\n"
		+ "topRightTextureCoordinate = inputTextureCoordinate.xy + widthNegativeHeightStep;\n"
		+ "\n"
		+ "bottomTextureCoordinate = inputTextureCoordinate.xy + heightStep;\n"
		+ "bottomLeftTextureCoordinate = inputTextureCoordinate.xy - widthNegativeHeightStep;\n"
		+ "bottomRightTextureCoordinate = inputTextureCoordinate.xy + widthHeightStep;\n"
		+ "}\n";

	return str;

}

std::string createConvolutionFilterFragmentShader()
{
	std::string str = "";

	str = str + "#version 330 core\n"
		+ "uniform sampler2D inputImageTexture;\n"
		+ "uniform mat3 convolutionMatrix;\n"
		+ "out vec4 FragColor;\n"
		+ "\n"
		+ "in vec2 textureCoordinate;\n"
		+ "in vec2 leftTextureCoordinate;\n"
		+ "in vec2 rightTextureCoordinate;\n"
		+ "\n"
		+ "in vec2 topTextureCoordinate;\n"
		+ "in vec2 topLeftTextureCoordinate;\n"
		+ "in vec2 topRightTextureCoordinate;\n"
		+ "\n"
		+ "in vec2 bottomTextureCoordinate;\n"
		+ "in vec2 bottomLeftTextureCoordinate;\n"
		+ "in vec2 bottomRightTextureCoordinate;\n"
		+ "\n"
		+ "void main()\n"
		+ "{\n"
		+ "vec4 bottomColor = texture(inputImageTexture, bottomTextureCoordinate);\n"
		+ "vec4 bottomLeftColor = texture(inputImageTexture, bottomLeftTextureCoordinate);\n"
		+ "vec4 bottomRightColor = texture(inputImageTexture, bottomRightTextureCoordinate);\n"
		+ "vec4 centerColor = texture(inputImageTexture, textureCoordinate);\n"
		+ "vec4 leftColor = texture(inputImageTexture, leftTextureCoordinate);\n"
		+ "vec4 rightColor = texture(inputImageTexture, rightTextureCoordinate);\n"
		+ "vec4 topColor = texture(inputImageTexture, topTextureCoordinate);\n"
		+ "vec4 topRightColor = texture(inputImageTexture, topRightTextureCoordinate);\n"
		+ "vec4 topLeftColor = texture(inputImageTexture, topLeftTextureCoordinate);\n"
		+ "vec4 resultColor = topLeftColor * convolutionMatrix[0][0] + topColor * convolutionMatrix[0][1] + topRightColor * convolutionMatrix[0][2];\n"
		+ "resultColor += leftColor * convolutionMatrix[1][0] + centerColor * convolutionMatrix[1][1] + rightColor * convolutionMatrix[1][2];\n"
		+ "resultColor += bottomLeftColor * convolutionMatrix[2][0] + bottomColor * convolutionMatrix[2][1] + bottomRightColor * convolutionMatrix[2][2];\n"
		+ "\n"
		+ "FragColor = resultColor;\n"
		+ "}\n";

	return str;
}