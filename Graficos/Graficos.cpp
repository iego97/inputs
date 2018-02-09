// Graficos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include <iostream>
using namespace std;


//Declaracion de ventana 
GLFWwindow *window;
GLfloat red, green, blue;
GLfloat ty = 0.0f;
GLfloat tx = 0.0f;
double tiempoAnterior = 0.0;
double velocidad = 0.7;

GLfloat enemigoX = 0.0f;
GLfloat enemigoY = 0.5f;

GLfloat angulo = 0.0f;
GLfloat velocidadAngular = 180.0f;

void checarColisiones()
{
	if (tx >= enemigoX - 0.08
		&& tx <= enemigoX + 0.08
		&& ty >= enemigoY - 0.08
		&& ty <= enemigoY + 0.08)
	{
		exit(0);
	}
}


void actualizar() {
	//Aqui esta bien para cambiar los valores de las variables de mi programa
	/*
	red += 0.001;
	green += 0.002;
	blue += 0.003;

	if (red > 1) red = 0;
	if (green > 1) green = 0;
	if (blue > 1) blue = 0;*/
	double tiempoActual = glfwGetTime();
	double tiempoTranscurrido = tiempoActual - tiempoAnterior;

	//ARRIBA
	int estadoArriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoArriba == GLFW_PRESS)
	{
		/*
		if (ty < 1)
			ty += velocidad * tiempoTranscurrido;
		*/

		tx += cos((angulo + 90) * (3.14159f / 180.0f)) * (velocidad * tiempoTranscurrido);

		ty += sin((angulo + 90) * (3.14159f / 180.0f)) * (velocidad * tiempoTranscurrido);
			

	}


	//ABAJO
	int estadoAbajo = glfwGetKey(window, GLFW_KEY_DOWN);
	if (estadoAbajo == GLFW_PRESS)
	{
		if (ty > -1)
			ty -= velocidad * tiempoTranscurrido;
	}



	int estadoIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoIzquierda == GLFW_PRESS) {
		angulo += velocidadAngular * tiempoTranscurrido;
		if (angulo > 360) {
			angulo -= 360.0f;
		}
	}


	int estadoDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoDerecha == GLFW_PRESS) {
		angulo -= velocidadAngular * tiempoTranscurrido;
		if (angulo < 0)
		{
			angulo += 360.0f;
		}
	}

	checarColisiones();

	tiempoAnterior = tiempoActual;

}

void dibujarHeroe() {
	glPushMatrix();
	glTranslatef(tx, ty, 0.0f);
	glRotatef(angulo, 0.0f, 0.0f, 1.0f);
	glScalef(0.08f, 0.08f, 0.08f);
	glBegin(GL_TRIANGLES);//Inicia la rutina con un modo de dibujo

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -0.5f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -0.5f, 0.0f);


	glEnd();//finaliza rutina
	glPopMatrix();
}


void dibujarEnemigo() {
	glPushMatrix();
	glTranslatef(enemigoX, enemigoY, 0.0f);

	glScalef(0.08f, 0.08f, 0.08f);
	glBegin(GL_TRIANGLES);//Inicia la rutina con un modo de dibujo

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -0.5f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(1.0f, -0.5f, 0.0f);


	glEnd();//finaliza rutina
	glPopMatrix();
}


void dibujar() {
	dibujarHeroe();
	dibujarEnemigo();

}
void key_callback(GLFWwindow* window, int key,
	int scancode, int action, int mods)
{
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (ty < 0.9)
			ty += 0.05;
	}

	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (ty > -0.9)
			ty -= 0.05f;
	}

	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (tx < 0.9)
			tx += 0.05;
	}

	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (tx > -0.9)
			tx -= 0.05f;
	}
}

int main()
{

	//Propiedades de la ventana
	GLfloat ancho = 1024;
	GLfloat alto = 768;

	//Inicializacion de GLFW
	if (!glfwInit()) {
		//Si no se inicio bien, terminar la ejecucion
		exit(EXIT_FAILURE);
	}

	//Inicializar la ventana
	window = glfwCreateWindow(ancho, alto, "Graficos", NULL, NULL);
	//Verificar si se creo bien la ventana
	if (!window) {
		//Cerrar todos los procesos de GLFW
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Establecer "window" como contexto
	glfwMakeContextCurrent(window);

	//se trae las funciones de OpenGL Moderno
	glewExperimental = true;
	//Inicializar GLEW
	GLenum glewError = glewInit();
	//Verificar que GLEW se inicializo bien
	if (glewError != GLEW_OK) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}


	const GLubyte *version = glGetString(GL_VERSION);
	cout << "Version de OpenGL: " << version << endl;

	red = green = blue = 0.0f;

	//glfwSetKeyCallback(window, key_callback);

	tiempoAnterior = glfwGetTime();

	//Ciclo de dibujo
	while (!glfwWindowShouldClose(window)) {
		//Establecer el area de render(Vewport)
		glViewport(0, 0, ancho, alto);
		//Establecer el color con el que se limpia la pantalla


		glClearColor(red, green, blue, 1);

		//Limpiar pantalla
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//rutina de dibujo
		actualizar();
		dibujar();

		//Intercambio de buffers
		glfwSwapBuffers(window);
		//Buscar señales de entrada
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
