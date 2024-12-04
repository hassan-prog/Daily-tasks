#define _USE_MATH_DEFINES

#include <iostream>
#include <gl/glew/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl\glm\glm.hpp>
#include <math.h>

using namespace std;
using namespace glm;

enum DrawingMode
{
	Points,
	Lines,
	FilledTriangle
};

struct Vertex {
	vec3 position;
	vec3 color;
	//Vertex(vec3 _position, vec3 _color) : position{ _position }, color{ _color } {}
};

const GLint WIDTH = 600, HEIGHT = 600;
GLuint VBO, BasiceprogramId;
DrawingMode Current_DrawingMode = DrawingMode::Lines;

GLuint InitShader(const char* vertex_shader_file_name, const char* fragment_shader_file_name);

void CreateSine()
{
	GLfloat CircleVertices[200 * 6];

	float numberOfVertices = sizeof(CircleVertices) / sizeof(GLfloat);

	for (int i = 0; i < numberOfVertices; i += 6)
	{
		CircleVertices[i] = -1 + 2 * i / numberOfVertices;
		CircleVertices[i + 1] = 0.5 * sin((-1 + 2 * i / numberOfVertices) * 3.14 * 36) * sin((-1 + 2 * i / numberOfVertices) * 3.14 * 3);
		CircleVertices[i + 2] = 0;
		CircleVertices[i + 3] = .7;
		CircleVertices[i + 4] = .1;
		CircleVertices[i + 5] = .4;
	}

	// create buffer object
	glGenBuffers(1, &VBO);

	// binding buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CircleVertices), CircleVertices, GL_STATIC_DRAW);

	// shader
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(GL_FLOAT), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(GL_FLOAT), (char*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
}

void CompileShader(const char* vertex_shader_file_name, const char* fragment_shader_file_name, GLuint& programId) {
	programId = InitShader(vertex_shader_file_name, fragment_shader_file_name);
	glUseProgram(programId);
}

int Init() {
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		cerr << "GLEW initialization error\n";
		getchar();
		return 1;
	}

	// Print OpenGL version info
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

	// Create and configure VBO
	CompileShader("VS3.glsl", "FS3.glsl", BasiceprogramId);
	CreateSine();

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	return 0;
}

void Render() {
	glClear(GL_COLOR_BUFFER_BIT);

	switch (Current_DrawingMode)
	{
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

	glDrawArrays(GL_LINE_STRIP, 0, 200);
}

float theta = 0;
void Update()
{
	// add all tick code
	theta += 0.00005f;

	GLuint Theta_Location = glGetUniformLocation(BasiceprogramId, "theta");
	glUniform1f(Theta_Location, theta);
}

int main() {
	sf::ContextSettings context;
	context.depthBits = 24;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!", sf::Style::Close, context);

	if (Init()) return 1;

	bool isDrawing = false;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();


			switch (event.type) {
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

		Update();
		Render();

		window.display();
	}

	return 0;
}