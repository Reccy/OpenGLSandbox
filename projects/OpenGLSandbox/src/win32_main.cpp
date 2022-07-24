#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

struct Vector4
{
	float x, y, z, w;
};

static Vector4 Red { 1.0f, 0.0f, 0.0f, 1.0f };
static Vector4 Green { 0.0f, 1.0f, 0.0f, 1.0f };
static Vector4 Blue { 0.0f, 0.0f, 1.0f, 1.0f };
static Vector4 White { 1.0f, 1.0f, 1.0f, 1.0f };

static Vector4 *ClearColor = &Red;

void GL_FramebufferResized(GLFWwindow* window, int width, int height)
{
	std::cout << "Framebuffer resized (" << width << "x, " << height << "y)" << std::endl;
	glViewport(0, 0, width, height);
}

void GL_ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		ClearColor = &Red;

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		ClearColor = &Green;

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		ClearColor = &Blue;

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		ClearColor = &White;
}

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, GL_FramebufferResized);

	while (!glfwWindowShouldClose(window))
	{
		GL_ProcessInput(window);

		glClearColor(ClearColor->x, ClearColor->y, ClearColor->z, ClearColor->w);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
