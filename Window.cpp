#pragma once

#include "Window.h"

#include <stdlib.h>
#include <iostream>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Texture.h"

#define __CURRENT_LESSION__		8

// --------------------------------------
#define __GET_STARTED__			1
#define __HELLO_TRIANGLE__		2
#define __SHADERS__				3
#define __TEXTURES__			4
#define __TRANSFORMATION__		5
#define	__COORDINATE_SYSTEM__	6
#define __CAMERA__				7
#define __LIGHTING_BASIC__		8
#define __LIGHTING_MAP__		9
#define __LIGHTING_CASTER__		10
#define __MULTIPLE_LIGHT__		11
#define __MODEL__ 				12
#define __DEPTH_TEST__			13
#define __STENCIL_TEST__		14
#define __BLENDING__			15
#define __FRAME_BUFFERS__		16
#define __CUBE_MAP__			17
#define __UNIFORM_BUFFERS__		18
#define __INSTANCING__			19
#define __ANTI_ALIASING__		20
#define __ADVANCED_LIGHTING__	21
#define __GAMMA_CORRECTION__	22
#define __SHADOW_MAPPING__		23
#define __POINT_SHADOW__		24
#define __NORMAL_MAPPING__		25
#define __PARALLAX_MAPPING__	26
#define __HIGH_DYNAMIC_RANGE__	27
#define __BLOOM__				28
#define __FOG_EFFECT__			29
#define __TOON_SHADING__		30
#define __DEBUGGING__			31
#define __TEXT_RENDERING__		32
#define	__2D_GAME_PRACTICE__	33
// --------------------------------------

using std::cout;
using std::endl;


int isFlashLightOn = 1; // 1 is on, 0 is off

// callbacks
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void cursor_callback(GLFWwindow *window, double xPos, double yPos);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

double last_time = glfwGetTime(), cur_time = glfwGetTime();
double deltaTime = 0.0F;

Camera camera(glm::vec3(0.0F, 0.0F, 3.0F));
int width, height;
bool cameraKey[Camera::CameraDirection::TOTAL_KEY];
bool cameraFirstMouseInput = true;
double cameraMouseX = 0.0F, cameraMouseY = 0.0F;
void updateCamera();


Window::Window(const char * title, unsigned int width, unsigned int height)
{
	// -------------------------------------------------------------
	// init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GL_TRUE);

	// -------------------------------------------------------------
	// create GLFW Window and current context
	window = glfwCreateWindow(1024, 768, "Learn OpenGL 3", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);

	// -------------------------------------------------------------
	// init glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		exit(-2);
	}

	// -------------------------------------------------------------
	// setup GL Viewport
	glfwGetFramebufferSize(window, &::width, &::height);
	glViewport(0, 0, ::width, ::height);

	// -------------------------------------------------------------
	// disable mouse cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	initCallbackFunction();
	initTime();

	disableCursor();
	firstMouseEvent = false;
}


Window::~Window()
{
	terminate();
}


void Window::clearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) 
{
	glClearColor(red, green, blue, alpha);
}


void Window::clear(GLbitfield mask) 
{
	glClear(mask);
}

#if __CURRENT_LESSION__ == __GET_STARTED__

int Window::exec() {

	// --------------------------------------------------------------
	// prepare for game loop



	// --------------------------------------------------------------
	// game loop
	while (!windowShouldClose())
	{
		glfwPollEvents();

		::deltaTime = glfwGetTime() - ::last_time;
		::last_time = glfwGetTime();
		/* calculate FPS */
		GLfloat fps = 1.0f / deltaTime;
		while (glfwGetTime() - ::last_time < 1.0f / FPS) {

		}
		updateCamera();

		// drawing
		clearColor(0, 0, 0, 0);
		clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		swapBuffer();
	}

	return 0;
}

#elif __CURRENT_LESSION__ == __HELLO_TRIANGLE__

int Window::exec() {

	// --------------------------------------------------------------
	// prepare for game loop

	//float vertices[] = {
	//	-0.5f, -0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	0.0f,  0.5f, 0.0f
	//};

	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	Shader shader("shaders/hello_triangle_vs.glsl", "shaders/hello_triangle_fs.glsl");

	VertexBuffer vbBuffer;
	VertexArray va;
	ElementBuffer eBuffer;

	// ======================================================
	// draw first triangle
	
	//va.bind();
	//vbBuffer.bind();
	//vbBuffer.setData(sizeof(vertices), vertices);
	//va.enableAttribute(shader.getAttribLocation("position"));
	//va.vertexAttribArray(shader.getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	//vbBuffer.unbind();
	//va.unbind();
	
	// ======================================================


	// ======================================================
	// draw more triangle using element buffer

	va.bind();
	vbBuffer.bind();
	vbBuffer.setData(sizeof(vertices), vertices);
	eBuffer.bind();
	eBuffer.setData(sizeof(indices), indices);
	va.enableAttribute(shader.getAttribLocation("position"));
	va.vertexAttribArray(shader.getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat), 0);
	vbBuffer.unbind();
	va.unbind();

	// ======================================================


	// --------------------------------------------------------------
	// game loop
	while (!windowShouldClose())
	{
		glfwPollEvents();

		::deltaTime = glfwGetTime() - ::last_time;
		::last_time = glfwGetTime();
		/* calculate FPS */
		GLfloat fps = 1.0f / deltaTime;
		while (glfwGetTime() - ::last_time < 1.0f / FPS) {

		}
		updateCamera();

		// drawing
		clearColor(0, 0, 0, 0);
		clear(GL_COLOR_BUFFER_BIT);

		shader.use();

		va.bind();
		eBuffer.renderElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		va.unbind();

		swapBuffer();
	}

	return 0;
}

#elif __CURRENT_LESSION__ == __SHADERS__

int Window::exec() {

	// --------------------------------------------------------------
	// prepare for game loop

	float vertices[] = {
		// positions         // colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};

	Shader shader("shaders/hello_shader_vs.glsl", "shaders/hello_shader_fs.glsl");

	VertexArray va;
	VertexBuffer vb;

	va.bind();
	vb.bind();
	vb.setData(sizeof(vertices), vertices);
	va.enableAttribute(shader.getAttribLocation("position"));
	va.vertexAttribArray(shader.getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	va.enableAttribute(shader.getAttribLocation("color"));
	va.vertexAttribArray(shader.getAttribLocation("color"), 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	vb.unbind();
	va.unbind();


	// --------------------------------------------------------------
	// game loop
	while (!windowShouldClose())
	{
		glfwPollEvents();

		::deltaTime = glfwGetTime() - ::last_time;
		::last_time = glfwGetTime();
		/* calculate FPS */
		GLfloat fps = 1.0f / deltaTime;
		while (glfwGetTime() - ::last_time < 1.0f / FPS) {

		}
		updateCamera();

		// drawing
		clearColor(0, 0, 0, 0);
		clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		
		va.bind();
		vb.bind();
		vb.renderBuffer(GL_TRIANGLES, 0, 3);
		vb.unbind();
		va.unbind();

		swapBuffer();
	}

	return 0;
}

#elif __CURRENT_LESSION__ == __TEXTURES__

int Window::exec() {

	// --------------------------------------------------------------
	// prepare for game loop

	float vertices[] = {
		// positions            // texture coords
		0.5f,  0.5f, 0.0f,      2.0f, 2.0f,   // top right
		0.5f, -0.5f, 0.0f,      2.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,     0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,     0.0f, 2.0f    // top left 
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	Shader shader("shaders/hello_texture_vs.glsl", "shaders/hello_texture_fs.glsl");

	VertexArray va;
	VertexBuffer vb;
	ElementBuffer eb;

	va.bind();
	vb.bind();
	vb.setData(sizeof(vertices), vertices);
	eb.bind();
	eb.setData(sizeof(indices), indices);
	va.enableAttribute(shader.getAttribLocation("position"));
	va.vertexAttribArray(shader.getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	va.enableAttribute(shader.getAttribLocation("uv"));
	va.vertexAttribArray(shader.getAttribLocation("uv"), 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	vb.unbind();
	va.unbind();

	Texture tex;
	tex.bind();
	tex.loadImage("textures/wall.png", true);
	tex.setMagFilter(GL_LINEAR);
	tex.setMinFilter(GL_LINEAR);
	tex.setWrap(GL_REPEAT);
	tex.unbind();

	Texture tex2;
	tex2.bind();
	tex2.loadImage("textures/wood.png", true);
	tex2.setMagFilter(GL_LINEAR);
	tex2.setMinFilter(GL_LINEAR);
	tex2.setWrap(GL_REPEAT);
	tex2.unbind();

	shader.use();
	shader.setUniform1i("tex", tex.getTextureID());
	shader.setUniform1i("tex2", tex2.getTextureID());

	// --------------------------------------------------------------
	// game loop
	while (!windowShouldClose())
	{
		glfwPollEvents();

		::deltaTime = glfwGetTime() - ::last_time;
		::last_time = glfwGetTime();
		/* calculate FPS */
		GLfloat fps = 1.0f / deltaTime;
		while (glfwGetTime() - ::last_time < 1.0f / FPS) {

		}
		updateCamera();

		// drawing
		clearColor(0, 0, 0, 0);
		clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

		tex.bind();
		Texture::active(tex.getTextureID());
		tex2.bind();
		Texture::active(tex2.getTextureID());

		va.bind();
		vb.bind();
		eb.bind();
		eb.renderElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		vb.unbind();
		va.unbind();

		swapBuffer();
	}

	return 0;
}

#elif __CURRENT_LESSION__ == __TRANSFORMATION__

int Window::exec() {

	// --------------------------------------------------------------
	// prepare for game loop

	float vertices[] = {
		// positions          // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	Shader shader("shaders/hello_transform_vs.glsl", "shaders/hello_transform_fs.glsl");

	VertexArray va;
	VertexBuffer vb;
	ElementBuffer eb;

	va.bind();
	vb.bind();
	vb.setData(sizeof(vertices), vertices);
	eb.bind();
	eb.setData(sizeof(indices), indices);
	va.enableAttribute(shader.getAttribLocation("position"));
	va.vertexAttribArray(shader.getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	va.enableAttribute(shader.getAttribLocation("uv"));
	va.vertexAttribArray(shader.getAttribLocation("uv"), 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	vb.unbind();
	va.unbind();

	Texture tex;
	tex.bind();
	tex.loadImage("textures/wall.png", true);
	tex.setMagFilter(GL_LINEAR);
	tex.setMinFilter(GL_LINEAR);
	tex.setWrap(GL_REPEAT);
	tex.unbind();

	shader.use();
	shader.setUniform1i("tex", tex.getTextureID());

	// --------------------------------------------------------------
	// game loop
	while (!windowShouldClose())
	{
		glfwPollEvents();

		::deltaTime = glfwGetTime() - ::last_time;
		::last_time = glfwGetTime();
		/* calculate FPS */
		GLfloat fps = 1.0f / deltaTime;
		while (glfwGetTime() - ::last_time < 1.0f / FPS) {

		}
		updateCamera();

		// drawing
		clearColor(0.3, 0.3, 0.5, 0);
		clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

		glm::mat4 transform;
		transform = glm::rotate(transform, (float)glfwGetTime() * 5, glm::vec3(0.0, 1.0, 0.0));
		shader.setUniformMatrix4fv("transform", 1, GL_FALSE, glm::value_ptr(transform));

		tex.bind();
		Texture::active(tex.getTextureID());

		va.bind();
		vb.bind();
		eb.bind();
		eb.renderElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		vb.bind();
		va.bind();

		swapBuffer();
	}

	return 0;
}

#elif __CURRENT_LESSION__ == __COORDINATE_SYSTEM__

int Window::exec() {

	// --------------------------------------------------------------
	// prepare for game loop

	// cube
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	Shader shader("shaders/hello_coord_vs.glsl", "shaders/hello_coord_fs.glsl");

	VertexArray va;
	VertexBuffer vb;

	va.bind();
	vb.bind();
	vb.setData(sizeof(vertices), vertices);
	va.enableAttribute(shader.getAttribLocation("position"));
	va.vertexAttribArray(shader.getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	va.enableAttribute(shader.getAttribLocation("uv"));
	va.vertexAttribArray(shader.getAttribLocation("uv"), 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	vb.unbind();
	va.unbind();

	Texture tex;
	tex.bind();
	tex.loadImage("textures/wood.png");
	tex.setDefaultParameters();
	tex.unbind();

	glEnable(GL_DEPTH_TEST);

	// --------------------------------------------------------------
	// game loop
	while (!windowShouldClose())
	{
		glfwPollEvents();

		::deltaTime = glfwGetTime() - ::last_time;
		::last_time = glfwGetTime();
		/* calculate FPS */
		GLfloat fps = 1.0f / deltaTime;
		while (glfwGetTime() - ::last_time < 1.0f / FPS) {

		}
		updateCamera();

		// drawing
		clearColor(0, 0.2, 0.3, 0);
		clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

		glm::mat4 model, view, projection;

		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

		shader.setUniformMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(model));
		shader.setUniformMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(view));
		shader.setUniformMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(projection));

		shader.setUniform1i("tex", tex.getTextureID());
		tex.bind();
		Texture::active(tex.getTextureID());

		va.bind();
		vb.bind();
		vb.renderBuffer(GL_TRIANGLES, 0, 36);
		vb.unbind();
		va.unbind();

		swapBuffer();
	}

	return 0;
}

#elif __CURRENT_LESSION__ == __CAMERA__

int Window::exec() {

	// --------------------------------------------------------------
	// prepare for game loop

	// cube
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	Shader shader("shaders/hello_coord_vs.glsl", "shaders/hello_coord_fs.glsl");

	VertexArray va;
	VertexBuffer vb;

	va.bind();
	vb.bind();
	vb.setData(sizeof(vertices), vertices);
	va.enableAttribute(shader.getAttribLocation("position"));
	va.vertexAttribArray(shader.getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	va.enableAttribute(shader.getAttribLocation("uv"));
	va.vertexAttribArray(shader.getAttribLocation("uv"), 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	vb.unbind();
	va.unbind();

	Texture tex;
	tex.bind();
	tex.loadImage("textures/wood.png");
	tex.setDefaultParameters();
	tex.unbind();

	glEnable(GL_DEPTH_TEST);

	// --------------------------------------------------------------
	// game loop
	while (!windowShouldClose())
	{
		glfwPollEvents();

		::deltaTime = glfwGetTime() - ::last_time;
		::last_time = glfwGetTime();
		/* calculate FPS */
		GLfloat fps = 1.0f / deltaTime;
		while (glfwGetTime() - ::last_time < 1.0f / FPS) {

		}
		updateCamera();

		// drawing
		clearColor(0, 0, 0, 0);
		clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

		glm::mat4 model, view, projection;

		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
		view = camera.getViewMatrix();
		projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

		shader.setUniformMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(model));
		shader.setUniformMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(view));
		shader.setUniformMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(projection));

		shader.setUniform1i("tex", tex.getTextureID());
		tex.bind();
		Texture::active(tex.getTextureID());

		va.bind();
		vb.bind();
		vb.renderBuffer(GL_TRIANGLES, 0, 36);
		vb.unbind();
		va.unbind();

		swapBuffer();
	}

	return 0;
}

#elif __CURRENT_LESSION__ == __LIGHTING_BASIC__

int Window::exec() {

	// --------------------------------------------------------------
	// prepare for game loop

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	Shader shader("shaders/lighting_basic_vs.glsl", "shaders/lighting_basic_fs.glsl");

	VertexArray va;
	VertexBuffer vb;

	va.bind();
	vb.bind();
	vb.setData(sizeof(vertices), vertices);
	va.vertexAttribArray(shader.getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	va.enableAttribute(shader.getAttribLocation("position"));
	va.vertexAttribArray(shader.getAttribLocation("normal"), 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
	va.enableAttribute(shader.getAttribLocation("normal"));
	vb.unbind();
	va.unbind();

	glEnable(GL_DEPTH_TEST);

	// --------------------------------------------------------------
	// game loop
	while (!windowShouldClose())
	{
		glfwPollEvents();

		::deltaTime = glfwGetTime() - ::last_time;
		::last_time = glfwGetTime();
		/* calculate FPS */
		GLfloat fps = 1.0f / deltaTime;
		while (glfwGetTime() - ::last_time < 1.0f / FPS) {

		}
		updateCamera();

		// drawing
		clearColor(0.1, 0.2, 0.3, 0);
		clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();


		// matrices ---------------------------------------------------------------------
		glm::mat4 model, view, projection;

		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
		view = camera.getViewMatrix();
		projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

		shader.setUniformMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(model));
		shader.setUniformMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(view));
		shader.setUniformMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(projection));
		// matrices ---------------------------------------------------------------------


		// fragments ---------------------------------------------------------------------
		shader.setUniform3f("fragColor", 0.5, 0.23, 0.4);
		// fragments ---------------------------------------------------------------------


		// lights ---------------------------------------------------------------------
		shader.setUniform3f("eyePos", camera.cameraPosition.x, camera.cameraPosition.y, camera.cameraPosition.z);
		shader.setUniform3f("lightColor", 1, 1, 1);
		shader.setUniform3f("lightPos", camera.cameraPosition.x, camera.cameraPosition.y, camera.cameraPosition.z);
		// lights ---------------------------------------------------------------------

		va.bind();
		vb.bind();
		vb.renderBuffer(GL_TRIANGLES, 0, 36);
		vb.unbind();
		va.unbind();

		swapBuffer();
	}

	return 0;
}

#elif __CURRENT_LESSION__ == __LIGHTING_MAP__

int Window::exec() {

	// --------------------------------------------------------------
	// prepare for game loop

	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	Shader shader("shaders/lighting_map_vs.glsl", "shaders/lighting_map_fs.glsl");

	VertexArray va;
	VertexBuffer vb;

	va.bind();
	vb.bind();
	vb.setData(sizeof(vertices), vertices);
	va.vertexAttribArray(shader.getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	va.enableAttribute(shader.getAttribLocation("position"));
	va.vertexAttribArray(shader.getAttribLocation("normal"), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
	va.enableAttribute(shader.getAttribLocation("normal"));
	va.vertexAttribArray(shader.getAttribLocation("uv"), 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(6 * sizeof(GLfloat)));
	va.enableAttribute(shader.getAttribLocation("uv"));
	vb.unbind();
	va.unbind();

	glEnable(GL_DEPTH_TEST);

	// --------------------------------------------------------------
	// game loop
	while (!windowShouldClose())
	{
		glfwPollEvents();

		::deltaTime = glfwGetTime() - ::last_time;
		::last_time = glfwGetTime();
		/* calculate FPS */
		GLfloat fps = 1.0f / deltaTime;
		cout << fps << endl;
		while (glfwGetTime() - ::last_time < 1.0f / FPS)
		{

		}
		updateCamera();

		// drawing
		clearColor(0.1, 0.2, 0.3, 0);
		clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();


		// matrices ---------------------------------------------------------------------
		glm::mat4 model, view, projection;

		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
		view = camera.getViewMatrix();
		projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

		shader.setUniformMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(model));
		shader.setUniformMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(view));
		shader.setUniformMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(projection));
		// matrices ---------------------------------------------------------------------

		// materials --------------------------------------------------------------------

		// materials --------------------------------------------------------------------

		// lights -----------------------------------------------------------------------
		shader.setUniform3f("eyePos", camera.cameraPosition.x, camera.cameraPosition.y, camera.cameraPosition.z);
		// lights -----------------------------------------------------------------------



		va.bind();
		vb.bind();
		vb.renderBuffer(GL_TRIANGLES, 0, 36);
		vb.unbind();
		va.unbind();

		swapBuffer();

		swapBuffer();
	}

	return 0;
}

#endif


void Window::terminate() {
	glfwTerminate();
}


void Window::setMousePos(double x, double y) {
	glfwSetCursorPos(window, x, y);
}


void Window::disableCursor() {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void Window::hideCursor() {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}


void Window::showCursor() {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::setKeyCallback(GLFWkeyfun func)
{
	glfwSetKeyCallback(window, func);
}

void Window::setMouseButtonCallback(GLFWmousebuttonfun func)
{
	glfwSetMouseButtonCallback(window, func);
}

void Window::setCursorPosCallback(GLFWcursorposfun func)
{
	glfwSetCursorPosCallback(window, func);
}


void Window::swapBuffer() 
{
	glfwSwapBuffers(window);
}


int Window::windowShouldClose() 
{
	return glfwWindowShouldClose(window);
}


void Window::setWindowShouldClose(int value) {
	glfwSetWindowShouldClose(window, value);
}


void Window::windowHint(int target, int value) {
	glfwWindowHint(target, value);
}


void Window::windowViewport(GLint x, GLint y, GLuint width, GLuint height) {
	glViewport(x, y, width, height);
}


void Window::initTime() {
	::last_time = glfwGetTime();
	::deltaTime = 0;
}


void Window::initCallbackFunction() {
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
}


void updateCamera()
{
	if (cameraKey[Camera::CameraDirection::FORWARD])
		camera.processKeyboard(Camera::CameraDirection::FORWARD, deltaTime);
	if (cameraKey[Camera::CameraDirection::BACKWARD])
		camera.processKeyboard(Camera::CameraDirection::BACKWARD, deltaTime);
	if (cameraKey[Camera::CameraDirection::LEFT])
		camera.processKeyboard(Camera::CameraDirection::LEFT, deltaTime);
	if (cameraKey[Camera::CameraDirection::RIGHT])
		camera.processKeyboard(Camera::CameraDirection::RIGHT, deltaTime);
}


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (key == GLFW_KEY_F && action == GLFW_RELEASE)
	{
		if (isFlashLightOn)
			isFlashLightOn = 0;
		else
			isFlashLightOn = 1;
	}

	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_W)
			cameraKey[Camera::CameraDirection::FORWARD] = true;
		if (key == GLFW_KEY_S)
			cameraKey[Camera::CameraDirection::BACKWARD] = true;
		if (key == GLFW_KEY_A)
			cameraKey[Camera::CameraDirection::LEFT] = true;
		if (key == GLFW_KEY_D)
			cameraKey[Camera::CameraDirection::RIGHT] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		if (key == GLFW_KEY_W)
			cameraKey[Camera::CameraDirection::FORWARD] = false;
		if (key == GLFW_KEY_S)
			cameraKey[Camera::CameraDirection::BACKWARD] = false;
		if (key == GLFW_KEY_A)
			cameraKey[Camera::CameraDirection::LEFT] = false;
		if (key == GLFW_KEY_D)
			cameraKey[Camera::CameraDirection::RIGHT] = false;
	}
}

void cursor_callback(GLFWwindow *window, double xPos, double yPos)
{
	if (cameraFirstMouseInput)
	{
		cameraFirstMouseInput = false;
		lastPosX = xPos;
		lastPosY = yPos;
	}

	GLfloat xOffset = xPos - lastPosX;
	GLfloat yOffset = lastPosY - yPos;

	lastPosX = xPos;
	lastPosY = yPos;

	camera.processMouseMovement(xOffset, yOffset);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{

}
