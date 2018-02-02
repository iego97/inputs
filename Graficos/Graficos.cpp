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

//Declaración de venta
GLFWwindow *window;
GLfloat red, green, blue;
GLfloat ty = 0.0f;
GLfloat tx = 0.0f;




void actualizar()
{
	//Aquí está bien para cambiar los valores de las variables de mi programa
	
	int estadoArriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoArriba == GLFW_PRESS)
	{
		if (ty < 1)
		{
			ty += 0.05f;
		}
	}

}

void dibujar()
{
	glPushMatrix();

	
	glTranslatef(tx, ty, 0.0);
	glScalef(0.08f, 0.08f, 0.08f);

	glBegin(GL_TRIANGLES); //INICIA LA RUTINA

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f,-0.5f,0.0f);


	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -0.5f, 0.0f);
	

	glEnd(); //FINALIZA LA RUTINA

	glPopMatrix();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (ty < 1)
		{
			ty += 0.05f;
		}
	}

	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (ty > -1)
		{
			ty -= 0.05f;
		}
	}
	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (tx > -1)
		{
			tx -= 0.05f;
		}
	}
	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (tx < 1)
		{
			tx += 0.05f;
		}
	}
}

int main()
{

	
	//Propiedades de la ventana
	GLfloat ancho = 1024;
	GLfloat alto = 768;

	//Inicialización de GLFW

	if (!glfwInit())
	{
		//Si no se inició bien, terminar la ejecución
		exit(EXIT_FAILURE);
	}

	//INICIALIZAR VENTANA

	window = glfwCreateWindow(ancho, alto, "Gráficos", NULL, NULL);


	//verificar si se creó la ventana
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	//Establecer "window" como contexto
	glfwMakeContextCurrent(window);


	//se trae las funciones de OpenGL Moderno
	glewExperimental = true;

	//INICIALIZAR GLEW

	GLenum glewError = glewInit();

	//verificar que GLEW se inicializó bien
	if (glewError != GLEW_OK)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	const GLubyte *version = glGetString(GL_VERSION);
	cout << "Version de OpenGl: " << version << endl;

	red = green = blue = 0.0f;

	//glfwSetKeyCallback(window, key_callback);


	//Ciclo de dibujo
	while (!glfwWindowShouldClose(window))
	{
			//ESTABLECER AREA DE RENDER
		glViewport(0, 0, ancho, alto);
		//ESTABLECER EL COLOR CON EL QUE SE VA A LIMPIAR LA PANTALLA



			glClearColor(red, green, blue, 1);
		


		//LIMPIAR PANTALLA
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		


		//rutina de dibujo
		actualizar();
		dibujar();

		//intercambio de buffers
		glfwSwapBuffers(window);

		//Buscar señales de entrada
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;

}

