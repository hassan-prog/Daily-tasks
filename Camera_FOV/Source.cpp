#include <iostream>
#include <gl/glew/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl\glm\glm.hpp>
#include <gl\glm\gtc\type_ptr.hpp>
#include <gl\glm\gtx\transform.hpp>
#include "Source.h"

using namespace std;
using namespace glm;

enum DrawingMode
{
	Points,
	Lines,
	FilledTriangle
};

struct vertex
{
	vec3 position;
	vec3 color;
	vertex() {}
	vertex(vec3 _position, vec3 _color) :position{ _position }, color{ _color }
	{
	}
	vertex(vec3 _position) :position{ _position }, color{ _position }
	{
	}
};

GLuint InitShader(const char* vertex_shader_file_name, const char* fragment_shader_file_name);

const GLint WIDTH = 600, HEIGHT = 600;
GLuint VBO_Triangle, VBO_Cube, IBO, BasiceprogramId;
DrawingMode Current_DrawingMode = DrawingMode::FilledTriangle;

// Camera
vec3 cameraPos(0.0f, 0.0f, 3.0f);
vec3 cameraLookAt(0.0f, 0.0f, -1.0f);
vec3 cameraUp(0.0f, 1.0f, 0.0f);

float fov = 60.0f;
float x_mouseMovement = -90.0f;
float y_mouseMovement = 0.0f;

glm::mat4 viewMat;

float deltaTime = 0.f;
// Mouse
float mouseSensitivity = 0.005f;
//sf::Vector2i lastMousePos;
sf::Vector2i lastMousePos(WIDTH / 2, HEIGHT / 2);

// transformation
GLuint modelMatLoc, viewMatLoc, projMatLoc;

void CreateTriangle() {
	vertex TriangleVertices[] =
	{
		vec3(-1,-1,0),vec3(0,1,0),
		vec3(1,-1,0),vec3(0,0,1),
		vec3(0,1,0),vec3(1,0,0)
	};

	// create buffer object
	glGenBuffers(1, &VBO_Triangle);

	// binding buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Triangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TriangleVertices), TriangleVertices, GL_STATIC_DRAW);

	// shader
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(GL_FLOAT), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(GL_FLOAT), (char*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	//GLuint Vertex_Position_Location = glGetAttribLocation(BasiceprogramId, "vertex_position");
}

void BindTriangle()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Triangle);

	// shader
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(GL_FLOAT), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(GL_FLOAT), (char*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
}

vertex cube_core_vertices[] = {
{vec3(-0.5, 0.5, 0.5),vec3(1,0,0)},
{vec3(-0.5, -0.5, 0.5),vec3(0,1,0)},
{vec3(0.5, -0.5, 0.5),vec3(1,0,1)},
{vec3(0.5, 0.5, 0.5),vec3(0,0,1)},
{vec3(0.5, 0.5, -0.5),vec3(1,1,0)},
{vec3(0.5, -0.5, -0.5),vec3(0,1,1)},
{vec3(-0.5, -0.5, -0.5),vec3(1,1,1)},
{vec3(-0.5, 0.5, -0.5),vec3(0,0,0)}
};

void CreateCube()
{
	int vertices_Indeces[] = {
		//front
		0,
		1,
		2,

		0,
		2,
		3,
		//Right
		3,
		2,
		5,

		3,
		5,
		4,
		//Back
		4,
		5,
		6,

		4,
		6,
		7,
		//Left
		7,
		6,
		1,

		7,
		1,
		0,
		//Top
		7,
		0,
		3,

		7,
		3,
		4,
		//Bottom
		2,
		1,
		6,

		2,
		6,
		5
	};

	// create VBO
	glGenBuffers(1, &VBO_Cube);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Cube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_core_vertices), cube_core_vertices, GL_STATIC_DRAW);

	// Index Buffer
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices_Indeces), vertices_Indeces, GL_STATIC_DRAW);

	// shader
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertex), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(vertex), (char*)(sizeof(vec3)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(vertex), (char*)(2 * sizeof(vec3)));
	glEnableVertexAttribArray(2);

}

void BindCube()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Cube);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertex), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(vertex), (char*)(sizeof(vec3)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(vertex), (char*)(2 * sizeof(vec3)));
	glEnableVertexAttribArray(2);
}

void CompileShader(const char* vertex_shader_file_name, const char* fragment_shader_file_namering, GLuint& programId)
{
	programId = InitShader(vertex_shader_file_name, fragment_shader_file_namering);
	glUseProgram(programId);
}

int Init() {
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

	CompileShader("VS2.glsl", "FS2.glsl", BasiceprogramId);

	//CreateTriangle();
	CreateCube();

	modelMatLoc = glGetUniformLocation(BasiceprogramId, "modelMat");
	viewMatLoc = glGetUniformLocation(BasiceprogramId, "viewMat");
	projMatLoc = glGetUniformLocation(BasiceprogramId, "projMat");

	glm::mat4 viewMat = lookAt(cameraPos, cameraPos + cameraLookAt, cameraUp);
	glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));

	glm::mat4 projMat = glm::perspectiveFov(fov, (float)WIDTH, (float)HEIGHT, 0.1f, 100.0f);
	glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));

	glClearColor(0, 0.5, 0.5, 1);
	glEnable(GL_DEPTH_TEST);

	return 0;
}

float theta = 0;

void Update() {
	// add all tick code
	theta += 0.001f;
}


void createBody() {
	glm::mat4 ModelMat;
	// Head
	ModelMat = glm::translate(glm::vec3(0.f, 1.5f, -0.5f)) *
		//glm::rotate(theta * 180 / 3.14f, glm::vec3(0.f, 1.f, 0.f)) *
		glm::scale(glm::vec3(0.4f, 0.4f, 0.4f));
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(ModelMat));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

	// Body
	ModelMat = glm::translate(glm::vec3(0.f, 0.8f, -0.5f)) *
		//glm::rotate(theta * 180 / 3.14f, glm::vec3(0.f, 1.f, 0.f)) *
		glm::scale(glm::vec3(0.6f, 1.0f, 0.4f));
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(ModelMat));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

	// Left Arm
	ModelMat = glm::translate(glm::vec3(-0.4f, 0.9f, -0.5f)) *
		//glm::rotate(theta * 180 / 3.14f, glm::vec3(0.f, 1.f, 0.f)) *
		glm::scale(glm::vec3(0.2f, 0.7f, 0.2f));
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(ModelMat));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

	// Right Arm
	ModelMat = glm::translate(glm::vec3(0.4f, 0.9f, -0.5f)) *
		//glm::rotate(theta * 180 / 3.14f, glm::vec3(0.f, 1.f, 0.f)) *
		glm::scale(glm::vec3(0.2f, 0.7f, 0.2f));
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(ModelMat));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

	// Left Leg
	ModelMat = glm::translate(glm::vec3(-0.2f, 0.0f, -0.5f)) *
		//glm::rotate(theta * 180 / 3.14f, glm::vec3(0.f, 1.f, 0.f)) *
		glm::scale(glm::vec3(0.2f, 0.7f, 0.2f));
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(ModelMat));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

	// Right Leg
	ModelMat = glm::translate(glm::vec3(0.2f, 0.0f, -0.5f)) *
		//glm::rotate(theta * 180 / 3.14f, glm::vec3(0.f, 1.f, 0.f)) *
		glm::scale(glm::vec3(0.2f, 0.7f, 0.2f));
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(ModelMat));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
}

void handleInput() {
	float cameraSpeed = 2.5f * deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		cameraPos += cameraSpeed * cameraLookAt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		cameraPos -= cameraSpeed * cameraLookAt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		cameraPos += normalize(cross(cameraLookAt, cameraUp)) * cameraSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		cameraPos -= normalize(cross(cameraLookAt, cameraUp)) * cameraSpeed;
	}

	viewMat = lookAt(cameraPos, cameraPos + cameraLookAt, cameraUp);
	glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
}

void Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

	BindCube();
	createBody();
}

int main()
{
	bool mouseGrabbed = true;
	bool mouseVisible = false;
	bool rightMousePressed = false;

	sf::ContextSettings context;
	context.depthBits = 24;

	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!", sf::Style::Close, context);

	if (Init()) return 1;

	window.setMouseCursorVisible(mouseVisible);
	window.setMouseCursorGrabbed(mouseGrabbed);

	while (window.isOpen()) {
		deltaTime = clock.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: {
				window.close();
				break;
			}
			case sf::Event::KeyPressed: {
				if (event.key.code == sf::Keyboard::Num1) {
					Current_DrawingMode = DrawingMode::Points;
				}
				if (event.key.code == sf::Keyboard::Num2) {
					Current_DrawingMode = DrawingMode::Lines;
				}
				if (event.key.code == sf::Keyboard::Num3) {
					Current_DrawingMode = DrawingMode::FilledTriangle;
				}
				// press Left Ctrl to enable mouse curser
				if (event.key.code == sf::Keyboard::LControl) {
					mouseGrabbed = !mouseGrabbed;
					mouseVisible = !mouseVisible;
					window.setMouseCursorVisible(mouseVisible);
					window.setMouseCursorGrabbed(mouseGrabbed);
				}
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				if (event.mouseButton.button == sf::Mouse::Right) {
					rightMousePressed = true;
					sf::Mouse::setPosition(sf::Vector2i(WIDTH / 2, HEIGHT / 2), window);
				}
				break;
			}
			case sf::Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == sf::Mouse::Right) {
					rightMousePressed = false;
				}
				break;
			}
			case sf::Event::MouseMoved:
			{
				if (rightMousePressed) {
					sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
					sf::Vector2i mouseDelta = currentMousePos - lastMousePos;

					x_mouseMovement += mouseDelta.x * mouseSensitivity;
					y_mouseMovement -= mouseDelta.y * mouseSensitivity;

					y_mouseMovement = clamp(y_mouseMovement, -89.0f, 89.0f);

					cameraLookAt.x = cos(x_mouseMovement) * cos(y_mouseMovement);
					cameraLookAt.y = sin(y_mouseMovement);
					cameraLookAt.z = sin(x_mouseMovement) * cos(y_mouseMovement);

					cameraLookAt = normalize(cameraLookAt);

					sf::Mouse::setPosition(sf::Vector2i(WIDTH / 2, HEIGHT / 2), window);
					lastMousePos = sf::Vector2i(WIDTH / 2, HEIGHT / 2);
				}
				break;
			}
			}
		}
		handleInput();

		Update();
		Render();

		window.display();
	}
	return 0;
}