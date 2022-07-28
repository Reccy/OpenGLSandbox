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

struct Vector4
{
	float x, y, z, w;
};

static Vector4 Red { 1.0f, 0.0f, 0.0f, 1.0f };
static Vector4 Green { 0.0f, 1.0f, 0.0f, 1.0f };
static Vector4 Blue { 0.0f, 0.0f, 1.0f, 1.0f };
static Vector4 White { 1.0f, 1.0f, 1.0f, 1.0f };

static Vector4* ClearColor = &Red;

static ROGLL::Shader* ShaderA = nullptr;
static ROGLL::Shader* ShaderB = nullptr;
static ROGLL::Shader* CurrentShader = nullptr;

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
		CurrentShader = ShaderA;

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		CurrentShader = ShaderB;
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

	ROGLL::Shader a("res/shaders/Default.shader");
	ROGLL::Shader b("res/shaders/Error.shader");

	ShaderA = &a;
	ShaderB = &b;
	CurrentShader = ShaderA;

	std::cout << "Uniform Location: "
		<< a.GetUniformLocation("uColor") << std::endl;

	ROGLL::Material mat(a);
	mat.Set4("uColor", ROGLL::Vector4<float> { 1, 0, 0, 1 });

	while (!glfwWindowShouldClose(window))
	{
		GL_ProcessInput(window);

		CurrentShader->Bind();

		glClearColor(ClearColor->x, ClearColor->y, ClearColor->z, ClearColor->w);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, vertexElementCount, GL_UNSIGNED_INT, (void*)0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
