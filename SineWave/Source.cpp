#define _USE_MATH_DEFINES

#include <iostream>
#include <gl/glew/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl\glm\glm.hpp>
#include <math.h>

using namespace std;
using namespace glm;

struct Vertex {
	vec3 position;
	vec3 color;
	Vertex(vec3 _position, vec3 _color) : position{ _position }, color{ _color } {}
};

const GLint WIDTH = 600, HEIGHT = 600;
GLuint VBO, VAO, BasiceprogramId;

vector<Vertex> currentLine;
vector<vector<Vertex>> lines;

GLuint InitShader(const char* vertex_shader_file_name, const char* fragment_shader_file_name);

// Updates the VBO with the current line data
void UpdateBuffer() {
	if (!currentLine.empty()) {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, currentLine.size() * sizeof(Vertex), currentLine.data(), GL_DYNAMIC_DRAW);
	}
}

void CompileShader(const char* vertex_shader_file_name, const char* fragment_shader_file_name, GLuint& programId) {
	programId = InitShader(vertex_shader_file_name, fragment_shader_file_name);
	glUseProgram(programId);
}

int Init() {
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		cerr << "GLEW initialization error\n";
		return 1;
	}

	// Print OpenGL version info
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

	// Create and configure VAO and VBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	CompileShader("VS3.glsl", "FS3.glsl", BasiceprogramId);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	return 0;
}

void Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(3.0f);

	glUseProgram(BasiceprogramId);
	glBindVertexArray(VAO);

	for (const auto& line : lines) {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, line.size() * sizeof(Vertex), line.data(), GL_DYNAMIC_DRAW);

		glDrawArrays(GL_LINE_STRIP, 0, line.size());
	}

	if (!currentLine.empty()) {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, currentLine.size() * sizeof(Vertex), currentLine.data(), GL_DYNAMIC_DRAW);

		glDrawArrays(GL_LINE_STRIP, 0, currentLine.size());
	}
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


			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);

				float ndcX = 2.0f * mousePos.x / WIDTH - 1.0f;
				float ndcY = 1.0f - 2.0f * mousePos.y / HEIGHT;

				Vertex newVertex(vec3(ndcX, ndcY, 0.0f), vec3(0.0f, 0.0f, 0.0f));
				currentLine.push_back(newVertex);

				UpdateBuffer();
			}

			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				if (!currentLine.empty()) {
					lines.push_back(currentLine);
					currentLine.clear();
				}
			}
		}

		Render();
		window.display();
	}

	return 0;
}