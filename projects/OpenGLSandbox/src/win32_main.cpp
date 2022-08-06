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
static RML::Tuple4<float>* MaterialColor = &White;

static bool MoveDown = false;
static bool MoveUp = false;
static bool MoveLeft = false;
static bool MoveRight = false;
static bool MoveForward = false;
static bool MoveBackward = false;
static bool RotateXClockwise = false;
static bool RotateXCounterClockwise = false;
static bool RotateYClockwise = false;
static bool RotateYCounterClockwise = false;
static bool RotateZClockwise = false;
static bool RotateZCounterClockwise = false;
static float VMove = 0;
static float HMove = 0;
static float DMove = 0;
static float RotX = 0;
static float RotY = 0;
static float RotZ = 0;
static float Fov = 90;

static float CamXRot = 0;
static float CamYRot = 0;

static int WIDTH = 1024;
static int HEIGHT = 768;

static void _ProcessInput(const ROGLL::Window& windowRef)
{
	GLFWwindow* window = windowRef.GetHandle();

	MoveDown = glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS;
	MoveUp = glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS;
	MoveLeft = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
	MoveRight = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
	MoveForward = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
	MoveBackward = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;

	RotateXClockwise = glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS;
	RotateXCounterClockwise = glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS;
	RotateYClockwise = glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS;
	RotateYCounterClockwise = glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS;
	RotateZClockwise = glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS;
	RotateZCounterClockwise = glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS;

	VMove = (MoveUp * 1) - (MoveDown * 1);
	HMove = (MoveRight * 1) - (MoveLeft * 1);
	DMove = (MoveForward * 1) - (MoveBackward * 1);

	RotX = (RotateXClockwise * 1) - (RotateXCounterClockwise * 1);
	RotY = (RotateYClockwise * 1) - (RotateYCounterClockwise * 1);
	RotZ = (RotateZClockwise * 1) - (RotateZCounterClockwise * 1);

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		Fov += 0.5;

	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		Fov -= 0.5;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

struct VertexLayout
{
	RML::Tuple3<float> pos;
	float u, v;
};

int main(void)
{
	ROGLL::Window window("OpenGL Sandbox", WIDTH, HEIGHT);

	RML::Tuple3<float> xyz(-0.5, -0.5, -0.5);
	RML::Tuple3<float> xYz(-0.5,  0.5, -0.5);
	RML::Tuple3<float> Xyz( 0.5, -0.5, -0.5);
	RML::Tuple3<float> XYz( 0.5,  0.5, -0.5);

	RML::Tuple3<float> xyZ(-0.5, -0.5, 0.5);
	RML::Tuple3<float> xYZ(-0.5,  0.5, 0.5);
	RML::Tuple3<float> XyZ( 0.5, -0.5, 0.5);
	RML::Tuple3<float> XYZ( 0.5,  0.5, 0.5);

	VertexLayout cubeVertices[] = {
		// FRONT
		{ xyz, 0, 0 },
		{ Xyz, 1, 0 },
		{ XYz, 1, 1 },
		{ xYz, 0, 1 },
		//BACK
		{ xYZ, 1, 1 }, // idx 4
		{ XYZ, 0, 1 },
		{ XyZ, 0, 0 },
		{ xyZ, 1, 0 },
		//TOP
		{ xYz, 0, 0 }, // idx 8
		{ XYz, 1, 0 },
		{ XYZ, 1, 1 },
		{ xYZ, 0, 1 },
		//BOTTOM
		{ xyZ, 0, 0 }, // idx 12
		{ XyZ, 1, 0 },
		{ Xyz, 1, 1 },
		{ xyz, 0, 1 },
		//LEFT
		{ xyZ, 0, 0 }, // idx 16
		{ xyz, 1, 0 },
		{ xYz, 1, 1 },
		{ xYZ, 0, 1 },
		//RIGHT
		{ XyZ, 0, 0, }, // idx 20
		{ XYZ, 0, 1 },
		{ XYz, 1, 1 },
		{ Xyz, 1, 0 },
	};

	VertexLayout groundVertices[] = {
		{ { -100, -0.5, -100 }, 0, 0, },
		{ {  100, -0.5, -100 }, 0, 1, },
		{ {  100, -0.5,  100 }, 1, 1, },
		{ { -100, -0.5,  100 }, 1, 0, },
	};

	unsigned int cubeIndices[] = {
		// FRONT
		0, 1, 2,
		2, 3, 0,
		// BACK
		4, 5, 6,
		6, 7, 4,
		// TOP
		8, 9, 10,
		10, 11, 8,
		// BOTTOM
		12, 13, 14,
		14, 15, 12,
		// LEFT
		16, 17, 18,
		18, 19, 16,
		// RIGHT
		20, 21, 22,
		22, 23, 20,
		// FLOOR
		24, 25, 26,
		26, 27, 24
	};

	unsigned int groundIndices[] = {
		0, 1, 2,
		2, 3, 0,
	};

	ROGLL::VertexArray cubeVertexArray;
	ROGLL::IndexBuffer cubeIndexLayout(cubeIndices, sizeof(cubeIndices));
	ROGLL::VertexBuffer cubeVertexBuffer(cubeVertices, sizeof(cubeVertices));

	ROGLL::VertexAttributes layout;
	layout.Add<float>(3); // XYZ Position
	layout.Add<float>(2); // UV
	
	cubeVertexArray.SetBuffer(layout, cubeVertexBuffer);

	ROGLL::VertexArray groundVertexArray;
	ROGLL::IndexBuffer groundIndexLayout(groundIndices, sizeof(groundIndices));
	ROGLL::VertexBuffer groundVertexBuffer(groundVertices, sizeof(groundVertices));

	groundVertexArray.SetBuffer(layout, groundVertexBuffer);

	ROGLL::Shader shader("res/shaders/Default.shader");
	ROGLL::Texture groundTexture("res/textures/Block.png");
	ROGLL::Texture companionCubeTexture("res/textures/Companion.png");

	ROGLL::Material cubeMaterial(shader);
	cubeMaterial.SetTextureSlot(0, companionCubeTexture);
	cubeMaterial.Set("uTexture", (unsigned int)0);

	ROGLL::Material groundMaterial(shader);
	groundMaterial.SetTextureSlot(0, groundTexture);
	groundMaterial.Set("uTexture", (unsigned int)0);

	ROGLL::Renderer renderer;

	RML::Matrix<double, 4, 4> mvp;

	RML::Transform model;
	ROGLL::Camera cam(WIDTH, HEIGHT, 60);
	cam.transform.translate(0, 0, -10);

	double speedFactor = 0.25;

	while (!window.ShouldClose())
	{
		_ProcessInput(window);

		cam.SetPerspective(WIDTH, HEIGHT, RML::Trig::degrees_to_radians(Fov));

		cubeMaterial.Set4("uColor", *MaterialColor);

		cam.transform.position += cam.transform.rotation.inverse()
			* RML::Vector(HMove * speedFactor,
				VMove * speedFactor,
				DMove * speedFactor);

		CamXRot += RotX;
		CamYRot += RotY;

		cam.transform.rotation = RML::Quaternion::euler_angles(CamXRot, CamYRot, 0);

		mvp = cam.GetProjectionMatrix() * cam.GetViewMatrix() * model.matrix();
		cubeMaterial.Set4x4("uMVP", mvp);

		renderer.SetClearColor(*ClearColor);
		renderer.Clear();

		renderer.Draw(cubeVertexArray, cubeIndexLayout, cubeMaterial);
		renderer.Draw(groundVertexArray, groundIndexLayout, groundMaterial);

		window.SwapBuffers();
		window.PollEvents();
	}

	return 0;
}
