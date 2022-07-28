#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>

#include <ROGLL.h>

// === Learning Resources ===
// Learn OpenGL: https://learnopengl.com/
// The Cherno's OpenGL Playlist: https://youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2
// Documentation: https://docs.gl/
// Open.GL: https://open.gl/

using ROGLL::Vector1;
using ROGLL::Vector2;
using ROGLL::Vector3;
using ROGLL::Vector4;

static Vector4<float> Red { 1.0f, 0.0f, 0.0f, 1.0f };
static Vector4<float> Green { 0.0f, 1.0f, 0.0f, 1.0f };
static Vector4<float> Blue { 0.0f, 0.0f, 1.0f, 1.0f };
static Vector4<float> White { 1.0f, 1.0f, 1.0f, 1.0f };

static Vector4<float>* ClearColor = &Red;
static Vector4<float>* MaterialColor = &Red;

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

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		MaterialColor = &Red;

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		MaterialColor = &Green;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		MaterialColor = &Blue;

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		MaterialColor = &White;
}

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Starting...", NULL, NULL);

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

	const GLubyte* glVersion = glGetString(GL_VERSION);

	std::cout << "OpenGL Initialized. Version: " << glVersion << std::endl;

	std::stringstream ss;
	ss << "OpenGL Sandbox (Driver: " << glVersion << ")";

	std::string strWindowTitle = ss.str();

	std::string glWindowTitle = strWindowTitle;

	glfwSetWindowTitle(window, glWindowTitle.c_str());
	glfwSwapInterval(1);

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, GL_FramebufferResized);

	const unsigned int vertexCount = 4;
	const unsigned int vertexElementCount = vertexCount * 2;
	float vertices[vertexElementCount] = {
		-0.5, -0.5,
		 0.5, -0.5,
		 0.5,  0.5,
		-0.5, 0.5,
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
	};

	ROGLL::VertexArray vertexArray;
	vertexArray.Bind();

	ROGLL::IndexBuffer indexBuffer(&indices, sizeof(indices));
	indexBuffer.Bind();

	ROGLL::VertexBuffer vertexBuffer(&vertices, sizeof(vertices));
	vertexBuffer.Bind();

	ROGLL::VertexAttributes layout;
	layout.Add<float>(2);

	vertexArray.SetBuffer(layout, vertexBuffer);

	ROGLL::Shader shader("res/shaders/Default.shader");
	ROGLL::Material mat(shader);

	while (!glfwWindowShouldClose(window))
	{
		GL_ProcessInput(window);

		mat.Set4("uColor", *MaterialColor);
		mat.Bind();

		glClearColor(ClearColor->x, ClearColor->y, ClearColor->z, ClearColor->w);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, vertexElementCount, GL_UNSIGNED_INT, (void*)0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
