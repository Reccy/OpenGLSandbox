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

static void _ProcessInput(const ROGLL::Window& windowRef)
{
	GLFWwindow* window = windowRef.GetHandle();

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
	ROGLL::Window window("OpenGL Sandbox", 800, 600);

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
	ROGLL::IndexBuffer indexBuffer(&indices, sizeof(indices));
	ROGLL::VertexBuffer vertexBuffer(&vertices, sizeof(vertices));

	ROGLL::VertexAttributes layout;
	layout.Add<float>(2);

	vertexArray.SetBuffer(layout, vertexBuffer);

	ROGLL::Shader shader("res/shaders/Default.shader");
	ROGLL::Material mat(shader);

	while (!window.ShouldClose())
	{
		_ProcessInput(window);

		mat.Set4("uColor", *MaterialColor);
		mat.Bind();

		glClearColor(ClearColor->x, ClearColor->y, ClearColor->z, ClearColor->w);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, vertexElementCount, GL_UNSIGNED_INT, (void*)0);

		window.SwapBuffers();
		window.PollEvents();
	}

	return 0;
}
