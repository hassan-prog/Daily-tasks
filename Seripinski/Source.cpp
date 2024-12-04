#define _USE_MATH_DEFINES

#include <iostream>
#include <gl/glew/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl\glm\glm.hpp>
#include <math.h>

using namespace std;
using namespace glm;


enum DrawingMode {
	Points,
	Lines,
	FilledTriangle
};

struct Vertex {
	vec3 position;
	vec3 color;
};

const GLint WIDTH = 600, HEIGHT = 600;
GLuint VBO, BasiceprogramId;
DrawingMode Current_DrawingMode = DrawingMode::FilledTriangle;
std::vector<Vertex> seripinski;

GLuint InitShader(const char* vertex_shader_file_name, const char* fragment_shader_file_name);

void generateSeripinski(vec3 v1, vec3 v2, vec3 v3, int depth) {
	if (depth == 0) {
		seripinski.push_back({ v1, vec3(0.f,0.f,0.f) });
		seripinski.push_back({ v2, vec3(0.f,0.f,0.f) });
		seripinski.push_back({ v3, vec3(0.f,0.f,0.f) });
		return;
	}

	vec3 midV1V2 = (v1 + v2) * 0.5f;
	vec3 midV2V3 = (v2 + v3) * 0.5f;
	vec3 midV1V3 = (v1 + v3) * 0.5f;

	generateSeripinski(v1, midV1V2, midV1V3, depth - 1);
	generateSeripinski(midV1V2, v2, midV2V3, depth - 1);
	generateSeripinski(midV1V3, midV2V3, v3, depth - 1);
}

void createSeripinskiShape(int depth) {
	vec3 v1 = vec3(-0.8f, -0.8f, 0.0f); // bottom left 
	vec3 v2 = vec3(0.8f, -0.8f, 0.0f); // bottom right 
	vec3 v3 = vec3(0.0f, 0.8f, 0.0f); // top

	seripinski.clear();

	generateSeripinski(v1, v2, v3, depth);
	// create buffer object
	glGenBuffers(1, &VBO);

	// binding buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, seripinski.size() * sizeof(Vertex), seripinski.data(), GL_STATIC_DRAW);

	// shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec3)));
	glEnableVertexAttribArray(1);
}


void CompileShader(const char* vertex_shader_file_name, const char* fragment_shader_file_namering, GLuint& programId)
{
	programId = InitShader(vertex_shader_file_name, fragment_shader_file_namering);
	glUseProgram(programId);
}

int Init()
{
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		cout << "Error";
		getchar();
		return 1;
	}
	else
	{
		if (GLEW_VERSION_3_0)
			cout << "Driver support OpenGL 3.0\nDetails:\n";
	}
	cout << "\tUsing glew " << glewGetString(GLEW_VERSION) << endl;
	cout << "\tVendor: " << glGetString(GL_VENDOR) << endl;
	cout << "\tRenderer: " << glGetString(GL_RENDERER) << endl;
	cout << "\tVersion: " << glGetString(GL_VERSION) << endl;
	cout << "\tGLSL:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

	CompileShader("VS4.glsl", "FS4.glsl", BasiceprogramId);
	createSeripinskiShape(2);
	glClearColor(0, 0.5, 0.5, 1);

	return 0;
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	switch (Current_DrawingMode) {
	case Points:
		glPointSize(10);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	case Lines:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case FilledTriangle:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	default:
		break;
	}

	glDrawArrays(GL_TRIANGLES, 0, seripinski.size());
}

int main() {
	sf::ContextSettings context;
	context.depthBits = 24;
	sf::Window window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!", sf::Style::Close, context);

	if (Init()) return 1;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{

			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Num1)
				{
					Current_DrawingMode = DrawingMode::Points;
				}
				if (event.key.code == sf::Keyboard::Num2)
				{
					Current_DrawingMode = DrawingMode::Lines;
				}
				if (event.key.code == sf::Keyboard::Num3)
				{
					Current_DrawingMode = DrawingMode::FilledTriangle;
				}
				break;
			}
			}

		}

		Render();

		window.display();
	}
	return 0;
}