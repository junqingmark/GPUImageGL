
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include "shader.h"
#include "gaussblur.h"

GLfloat fbovertices[] = {
	1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

	1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
	-1.0f, 1.0f, 0.0f, 0.0f, 0.0f
};

GLfloat vertices[] = {
	1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

	1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	-1.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

/*
std::string createVertexShader(unsigned int blurRadius)
{
	char* varyingStr = new char[200];
	snprintf(varyingStr, 100, "varying vec2 blurCoordinates[%lu];\n", (unsigned long)(blurRadius * 2 + 1));
	std::string str = "";
	str = str + "#version 330 core\n"
		+ "layout (location = 0) in vec3 aPos;\n"
		+ "layout (location = 1) in vec2 inputTextureCoordinate;\n"
		+ "uniform float texelWidthOffset;\n"
		+ "uniform float texelHeightOffset;\n"
		+ std::string(varyingStr)
		+ "void main()\n"
		+ "{\n"
		+ "gl_Position = vec4(aPos, 1.0);\n"
		+ "vec2 singleStepOffset = vec2(texelWidthOffset, texelHeightOffset);\n";

	for (unsigned int currentBlurCoordinateIndex = 0; currentBlurCoordinateIndex < (blurRadius * 2 + 1); currentBlurCoordinateIndex++)
	{
		int offsetFromCenter = currentBlurCoordinateIndex - blurRadius;
		if (offsetFromCenter < 0)
		{
			snprintf(varyingStr, 200, "blurCoordinates[%lu] = inputTextureCoordinate - singleStepOffset *%f;\n", (unsigned long)currentBlurCoordinateIndex, (float)(-offsetFromCenter));
		}
		else if(offsetFromCenter > 0)
		{
			snprintf(varyingStr, 200, "blurCoordinates[%lu] = inputTextureCoordinate + singleStepOffset *%f;\n", (unsigned long)currentBlurCoordinateIndex, (float)(offsetFromCenter));
		}
		else
		{
			snprintf(varyingStr, 200, "blurCoordinates[%lu] = inputTextureCoordinate;\n", (unsigned long)currentBlurCoordinateIndex);
		}

		str += std::string(varyingStr);
	}

	str += "}\n";

	return str;

}

std::string createFragmentShader(unsigned int blurRadius, float sigma)
{
	GLfloat* standardGaussianWeights = new GLfloat[blurRadius + 1];
	GLfloat sumOfWeights = 0.0;

	for (unsigned int currentGaussianWeightIndex = 0; currentGaussianWeightIndex < blurRadius + 1; currentGaussianWeightIndex++)
	{
		standardGaussianWeights[currentGaussianWeightIndex] = (1.0 / sqrt(2.0 * M_PI * pow(sigma, 2.0))) * exp(-pow(currentGaussianWeightIndex, 2.0) / (2.0 * pow(sigma, 2.0)));
		if (currentGaussianWeightIndex == 0)
		{
			sumOfWeights += standardGaussianWeights[currentGaussianWeightIndex];
		}
		else
		{
			sumOfWeights += 2.0 * standardGaussianWeights[currentGaussianWeightIndex];
		}
	}

	for (unsigned int currentGaussianWeightIndex = 0; currentGaussianWeightIndex < blurRadius + 1; currentGaussianWeightIndex++)
	{
		standardGaussianWeights[currentGaussianWeightIndex] = standardGaussianWeights[currentGaussianWeightIndex] / sumOfWeights;
	}

	char* varyingStr = new char[200];
	snprintf(varyingStr, 100, "varying vec2 blurCoordinates[%lu];\n", (unsigned long)(blurRadius * 2 + 1));

	std::string str = "";
	str = str + "#version 330 core\n"
		+"out vec4 FragColor;\n"
		+ "uniform sampler2D inputImageTexture;\n"
		+ std::string(varyingStr)
		+ "void main()\n"
		+ "{\n"
		+ "vec4 sum = vec4(0.0);\n";

	for (unsigned int currentBlurCoordinateIndex = 0; currentBlurCoordinateIndex < (blurRadius * 2 + 1); currentBlurCoordinateIndex++)
	{
		int offsetFromCenter = currentBlurCoordinateIndex - blurRadius;

		if (offsetFromCenter < 0)
		{
			snprintf(varyingStr, 200, "sum += texture2D(inputImageTexture, blurCoordinates[%lu]) * %f;\n", (unsigned long)currentBlurCoordinateIndex, standardGaussianWeights[-offsetFromCenter]);
		}
		else
		{
			snprintf(varyingStr, 200, "sum += texture2D(inputImageTexture, blurCoordinates[%lu]) * %f;\n", (unsigned long)currentBlurCoordinateIndex, standardGaussianWeights[offsetFromCenter]);
		}

		str += std::string(varyingStr);
	}

	str += "FragColor = sum;\n";
	str += "}\n";

	return str;

}
*/


GLuint createRTTTexture(int width, int height)
{
	//create fbo texture
	GLuint fboTexture;

	glGenTextures(1, &fboTexture);
	glBindTexture(GL_TEXTURE_2D, fboTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return fboTexture;
}

GLuint createSceneTexture(int width, int height, void* pixels)
{
	GLuint sceneTexture;

	glGenTextures(1, &sceneTexture);
	glBindTexture(GL_TEXTURE_2D, sceneTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return sceneTexture;
}

GLuint createFBO(GLuint texture)
{
	GLuint fbo;

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Fail to create fbo" << std::endl;
		return 0;
	}

	return fbo;
}

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return -1;
	}

	SDL_Surface* surface = IMG_Load("test.jpg");

	SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGB888, 0);
	int width = surface->w;
	int height = surface->h;

	GLvoid * pixels = surface->pixels;

	SDL_Window* window = SDL_CreateWindow("opengl window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (window == NULL)
	{
		SDL_Log("Fail to create SDL Window: %s", SDL_GetError());
		return -1;
	}

	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (context == NULL)
	{
		SDL_Log("Fail to create SDL Context: %s", SDL_GetError());
		return -1;
	}

	SDL_GL_MakeCurrent(window, context);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Fail to init GLEW");
		return -1;
	}

	

	GLuint fboVAO, fboVBO;
	glGenVertexArrays(1, &fboVAO);
	glBindVertexArray(fboVAO);

	glGenBuffers(1, &fboVBO);
	glBindBuffer(GL_ARRAY_BUFFER, fboVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fbovertices), fbovertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)NULL);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)NULL);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	//Shader shader(createVertexShader(blurSize), createFragmentShader(blurSize, sigma));
	Shader shader(createVertexShader(), createFragmentShader());
	shader.use();

	shader.setFloat("texelWidthOffset", 0.0f);
	shader.setFloat("texelHeightOffset", 1.0f);
	shader.setVec2("resolution", (float)width, (float)height);

	GLuint sceneTexture = createSceneTexture(width, height, pixels);
	GLuint fboTexture = createRTTTexture(width, height);

	GLuint fbo = createFBO(fboTexture);

	std::cout << "fbo texture is " << fboTexture << std::endl;

	if (fbo > 0)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glBindVertexArray(fboVAO);
		glBindTexture(GL_TEXTURE_2D, sceneTexture);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	//Shader shader("gaussBlurVertex.glsl", "gaussBlurFragment.glsl");

	//shader.setVec4("vColor1", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	//shader.setVec4("vColor2", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	//shader.setVec2("resolution", glm::vec2(800.0f, 600.0f));

	shader.setFloat("texelWidthOffset", 1.0f);
	shader.setFloat("texelHeightOffset", 0.0f);

	int running = 1;
	SDL_Event event;
	while (running)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = 0;

			}
		}

		shader.use();
		glViewport(0, 0, width, height);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, fboTexture);

		glDrawArrays(GL_TRIANGLES, 0, 6);
		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
