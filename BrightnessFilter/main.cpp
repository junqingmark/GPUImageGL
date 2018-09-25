#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include "shader.h"
#include "brightnessshader.h"

GLfloat vertices[] = {
	1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

	1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
	-1.0f, 1.0f, 0.0f, 0.0f, 0.0f
};

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
	Shader shader(createBrightnessFilterVertexShader(), createBrightnessFilterFragmentShader());
	shader.use();

	//-1.0f To 1.0f
	shader.setFloat("brightness", 0.5f);

	GLuint sceneTexture = createSceneTexture(width, height, pixels);

	//Shader shader("gaussBlurVertex.glsl", "gaussBlurFragment.glsl");

	//shader.setVec4("vColor1", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	//shader.setVec4("vColor2", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	//shader.setVec2("resolution", glm::vec2(800.0f, 600.0f));

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
		glBindTexture(GL_TEXTURE_2D, sceneTexture);

		glDrawArrays(GL_TRIANGLES, 0, 6);
		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
