#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>
#include <fstream>

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

enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };
const char* ShaderTypeStrings[2] = { "Vertex", "Fragment" };
const int ShaderTypeConsts[] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };

struct ShaderProgramSource
{
	std::string vertex;
	std::string fragment;
};

ShaderProgramSource LoadShaderSource(std::string filepath)
{
	ShaderProgramSource result;

	std::ifstream infile;
	infile.open(filepath);

	if (!infile.is_open())
	{
		std::cout << "[File Load Error] Failed to load file at " << filepath << std::endl;
		return result;
	}
	
	std::stringstream sourceStream[2];

	enum ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };
	ShaderType type = NONE;

	std::string line;
	while (std::getline(infile, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			sourceStream[(int)type] << line << '\n';
		}
	}

	result.vertex = sourceStream[(int)ShaderType::VERTEX].str();
	result.fragment = sourceStream[(int)ShaderType::FRAGMENT].str();

	return result;
}

bool GL_ValidateShaderCompiled(unsigned int shader)
{
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		int size = 256;
		char* infoLog = (char*)_malloca(sizeof(char*) * size);
		glGetShaderInfoLog(shader, size, &size, infoLog);

		std::cout << "[OpenGL Shader Compile Error] " << infoLog << std::endl;

		_freea(infoLog);
	}

	return success;
}

bool GL_ValidateShaderProgramLinked(unsigned int program)
{
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		int size = 256;
		char* infoLog = (char*)_malloca(sizeof(char*) * size);
		glGetProgramInfoLog(program, size, &size, infoLog);

		std::cout << "[OpenGL Program Link Error] " << infoLog << std::endl;

		_freea(infoLog);
	}

	return success;
}

static unsigned int CompileShader(const std::string& source, ShaderType type)
{
	const char* str = source.c_str();

	unsigned int shader = glCreateShader(ShaderTypeConsts[(int)type]);
	glShaderSource(shader, 1, &str, NULL);
	glCompileShader(shader);

	if (!GL_ValidateShaderCompiled(shader))
	{
		std::cout << "Failed to compile shader (Type: " << ShaderTypeStrings[(int)type] << ")" << std::endl;
		glfwTerminate();
		return -1;
	}

	std::cout << "Successfully compiled shader (Type: " << ShaderTypeStrings[(int)type] << ")" << std::endl;
	return shader;
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

unsigned int CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	unsigned int vertexShader = CompileShader(vertexShaderSource, ShaderType::VERTEX);
	unsigned int fragmentShader = CompileShader(fragmentShaderSource, ShaderType::FRAGMENT);

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

	return shaderProgram;
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

	unsigned int vertexArrayObj;
	glGenVertexArrays(1, &vertexArrayObj);
	glBindVertexArray(vertexArrayObj);

	unsigned int indexBufferObj;
	glGenBuffers(1, &indexBufferObj);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObj);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	ROGLL::VertexBuffer vbo(&vertices, sizeof(vertices));
	vbo.Bind();

	ShaderProgramSource shaderSource = LoadShaderSource("res/shaders/Default.shader");
	unsigned int shaderProgram = CreateShaderProgram(shaderSource.vertex, shaderSource.fragment);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		GL_ProcessInput(window);

		glClearColor(ClearColor->x, ClearColor->y, ClearColor->z, ClearColor->w);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, vertexElementCount, GL_UNSIGNED_INT, (void*)0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
