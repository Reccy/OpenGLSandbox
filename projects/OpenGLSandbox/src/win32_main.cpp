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

static const char *GL_VertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

static const char *GL_FragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

bool GL_ValidateShaderCompiled(unsigned int shader)
{
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	return success;
}

bool GL_ValidateShaderProgramLinked(unsigned int program)
{
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	return success;
}

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

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &GL_VertexShaderSource, NULL);
	glCompileShader(vertexShader);

	if (!GL_ValidateShaderCompiled(vertexShader))
	{
		std::cout << "Failed to compile vertex shader" << std::endl;
		glfwTerminate();
		return -1;
	}
	else
	{
		std::cout << "Successfully compiled vertex shader" << std::endl;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &GL_FragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	if (!GL_ValidateShaderCompiled(fragmentShader))
	{
		std::cout << "Failed to compile fragment shader" << std::endl;
		glfwTerminate();
		return -1;
	}
	else
	{
		std::cout << "Successfully compiled fragment shader" << std::endl;
	}

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	if (!GL_ValidateShaderProgramLinked(shaderProgram))
	{
		std::cout << "Failed to link shader program" << std::endl;
		glfwTerminate();
		return -1;
	}
	else
	{
		std::cout << "Successfully linked shader program" << std::endl;
	}

	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		GL_ProcessInput(window);

		glClearColor(ClearColor->x, ClearColor->y, ClearColor->z, ClearColor->w);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
