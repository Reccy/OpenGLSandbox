#include <iostream>
#include <sstream>

#include <ROGLL.h>
#include <RML/RML.h>

// === Learning Resources ===
// Learn OpenGL: https://learnopengl.com/
// The Cherno's OpenGL Playlist: https://youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2
// Documentation: https://docs.gl/
// Open.GL: https://open.gl/

static RML::Tuple4<float> Red { 1.0f, 0.0f, 0.0f, 1.0f };
static RML::Tuple4<float> Green { 0.0f, 1.0f, 0.0f, 1.0f };
static RML::Tuple4<float> Blue { 0.0f, 0.0f, 1.0f, 1.0f };
static RML::Tuple4<float> White { 1.0f, 1.0f, 1.0f, 1.0f };

static RML::Tuple4<float>* ClearColor = &White;
static RML::Tuple4<float>* MaterialColor = &Red;

static bool MoveDown = false;
static bool MoveUp = false;
static bool MoveLeft = false;
static bool MoveRight = false;
static bool RotLeft = false;
static bool RotRight = false;
static float VMove = 0;
static float HMove = 0;
static float Rot = 0;

static void _ProcessInput(const ROGLL::Window& windowRef)
{
	GLFWwindow* window = windowRef.GetHandle();

	MoveDown = glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS;
	MoveUp = glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS;
	MoveLeft = glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS;
	MoveRight = glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS;
	RotLeft = glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS;
	RotRight = glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS;

	VMove = (MoveUp * 1) - (MoveDown * 1);
	HMove = (MoveRight * 1) - (MoveLeft * 1);
	Rot = (RotRight * 1) - (RotLeft * 1);

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

	float vertices[] = {
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
	ROGLL::IndexBuffer indexBuffer(indices, sizeof(indices));
	ROGLL::VertexBuffer vertexBuffer(vertices, sizeof(vertices));

	ROGLL::VertexAttributes layout;
	layout.Add<float>(2);

	vertexArray.SetBuffer(layout, vertexBuffer);

	ROGLL::Shader shader("res/shaders/Default.shader");
	ROGLL::Material mat(shader);

	ROGLL::Renderer renderer;

	RML::Matrix<double, 4, 4> mvp;

	RML::Transform model;
	ROGLL::Camera cam(800, 600, 90);
	cam.transform.translate(100, 0,-100);
	cam.transform.rotate(0, -10, 0);

	model.scale(100, 100, 1);

	while (!window.ShouldClose())
	{
		_ProcessInput(window);

		mat.Set4("uColor", *MaterialColor);

		model.translate(0, -0.2, 0);
		model.rotate(0, 0, 0.5);

		cam.transform.rotate(0, 0, Rot);
		cam.transform.translate(HMove * 10, VMove * 10, 0);

		mvp = cam.GetViewProjectionMatrix() * model.matrix();
		mat.Set4x4("uMVP", mvp);

		renderer.SetClearColor(*ClearColor);
		renderer.Clear();

		renderer.Draw(vertexArray, indexBuffer, mat);

		window.SwapBuffers();
		window.PollEvents();
	}

	return 0;
}
