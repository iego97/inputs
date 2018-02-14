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
double tiempoAnterior = 0.0;
double velocidadBarras = 0.7;
double velocidadPelota = 0.7;

GLfloat barraIzquierdaY = 0.0f;
GLfloat barraIzquierdaX = -0.85f;

GLfloat barraDerechaX = 0.80f;
GLfloat barraDerechaY = 0.0f;

GLfloat pelotaX = 0.0f;
GLfloat pelotaY = 0.0f;
GLfloat anguloPelota = 0.0f;



bool moviendose = true;
bool choqueIzquierda = false;
bool choqueSuperior = false;
bool choqueDerecha = false;
bool choqueInferior = false;



GLfloat velocidadAngular = 180.0f;

void checarColisionesIzquierda()
{
			

	
	if (
		   pelotaX <= barraIzquierdaX + 0.15
		&& pelotaX >= barraIzquierdaX - 0.15
		&& pelotaY <= barraIzquierdaY + 0.18
		&& pelotaY >= barraIzquierdaY - 0.25
		 )
	{
		moviendose = false;
		choqueIzquierda = true;

	
		velocidadPelota += 0.02;
		
	}
	
}



void checarColisionesDerecha()
{



	if (
		   pelotaX <= barraDerechaX + 0.05
		&& pelotaX >= barraDerechaX - 0.05
		&& pelotaY <= barraDerechaY + 0.18
		&& pelotaY >= barraDerechaY - 0.25
		)
	{
		choqueSuperior = false;
		choqueInferior = false;
		choqueIzquierda = false;
		choqueDerecha = true;
	

		velocidadPelota += 0.02;

	}

}

void checarColisionesSuperior()
{



	if (
		pelotaX <= 1.0
		&& pelotaX >= -1.0
		&& pelotaY <= 0.90
		&& pelotaY >= 0.85
		)
	{
		
		choqueIzquierda = false;
		choqueSuperior = true;

		velocidadPelota += 0.02;
	}

}

void checarColisionesInferior()
{



	if (
		pelotaX <= 1.0
		&& pelotaX >= -1.0
		&& pelotaY <= -0.95
		&& pelotaY >= -1.0
		)
	{
		choqueSuperior = false;
		choqueDerecha = false;

		velocidadPelota += 0.02;
		
	}

}






void actualizarPelota(double tiempoTranscurrido)
{
	if (moviendose)
	{
		pelotaX -= (tiempoTranscurrido * velocidadPelota) /2 ;
	}
	else if (choqueIzquierda )
	{

		pelotaX += -cos((anguloPelota + 135) * (3.14159f / 180.0f)) *
			velocidadPelota * 1.05 * tiempoTranscurrido;
		pelotaY += sin((anguloPelota + 135) * (3.14159f / 180.0f)) *
			velocidadPelota * 1.05 * tiempoTranscurrido;

	}
	else if (choqueDerecha)
	{
		pelotaX += -cos((anguloPelota + 37) * (3.14159f / 180.0f)) *
			velocidadPelota * 1.05 * tiempoTranscurrido;
		pelotaY += -sin((anguloPelota + 37) * (3.14159f / 180.0f)) *
			velocidadPelota * 1.05 * tiempoTranscurrido;
	}
	else if (choqueSuperior)
	{
		pelotaX += cos((anguloPelota + 37) * (3.14159f / 180.0f)) *
			velocidadPelota * 1.05 * tiempoTranscurrido;
		pelotaY += -sin((anguloPelota + 37) * (3.14159f / 180.0f)) *
			velocidadPelota * 1.05 * tiempoTranscurrido;
	}
	else if (choqueInferior)
	{
		pelotaX += -cos((anguloPelota + 67.5) * (3.14159f / 180.0f)) *
			velocidadPelota * 1.05 * tiempoTranscurrido;
		pelotaY += sin((anguloPelota + 67.5) * (3.14159f / 180.0f)) *
			velocidadPelota * 1.05 * tiempoTranscurrido;
	}


}


void actualizar() {
	//Aqui esta bien para cambiar los valores de las variables de mi programa

	double tiempoActual = glfwGetTime();
	double tiempoTranscurrido = tiempoActual - tiempoAnterior;

	//MOVIMIENTO PELOTA
	
	actualizarPelota(tiempoTranscurrido);
	


	//ARRIBA izquierda
	int estadoArriba = glfwGetKey(window, GLFW_KEY_W);
	if (estadoArriba == GLFW_PRESS)
	{

		if (barraIzquierdaY < 0.75f)
		{
			barraIzquierdaY += velocidadBarras * tiempoTranscurrido;
		}

	}


	//ABAJO izquierda
	int estadoAbajo = glfwGetKey(window, GLFW_KEY_S);
	if (estadoAbajo == GLFW_PRESS)
		if (barraIzquierdaY > -0.75f)
		{
			barraIzquierdaY -= velocidadBarras * tiempoTranscurrido;
		}

	//ARRIBA derecha
	int estadoArribaDerecha = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoArribaDerecha == GLFW_PRESS)
	{

		if (barraDerechaY < 0.75f)
		{
			barraDerechaY += velocidadBarras * tiempoTranscurrido;
		}

	}


	//ABAJO derecha
	int estadoAbajoDerecha = glfwGetKey(window, GLFW_KEY_DOWN);
	if (estadoAbajoDerecha == GLFW_PRESS)
		if (barraDerechaY > -0.75f)
		{
			barraDerechaY -= velocidadBarras * tiempoTranscurrido;
		}







	checarColisionesIzquierda();
	checarColisionesSuperior();
	checarColisionesDerecha();
	checarColisionesInferior();
	
	


	tiempoAnterior = tiempoActual;

}

void dibujarLimites()
{
	glPushMatrix();
	glBegin(GL_QUADS);

	glColor3f(1.0f, 1.0f, 1.0f);
	//limiteSuperior
	glVertex3f(-1.0f,0.95f,0.0f);
	glVertex3f(-1.0f, 0.99f, 0.0f);
	glVertex3f(1.0f, 0.99f, 0.0f);
	glVertex3f(1.0f, 0.95f, 0.0f);
	


	glEnd();

	glBegin(GL_QUADS);

	//limiteInferior
	
	glColor3f(1.0f, 1.0f, 1.0f);

	glVertex3f(-1.0f, -0.95f, 0.0f);
	glVertex3f(-1.0f, -0.99f, 0.0f);
	glVertex3f(1.0f, -0.99f, 0.0f);
	glVertex3f(1.0f, -0.95f, 0.0f);

	glEnd();


	glPopMatrix();
}

void dibujarHeroe() {
	glPushMatrix();
	glTranslatef(0.0f, barraIzquierdaY, 0.0f);


	glBegin(GL_QUADS);//Inicia la rutina con un modo de dibujo

	glColor3f(1.0f, 1.0f, 1.0f);

	glVertex3f(-0.85f, -0.2f, 0.0f);
	glVertex3f(-0.85f, 0.2f, 0.0f);
	glVertex3f(-0.90f, 0.2f, 0.0f);
	glVertex3f(-0.90f, -0.2f, 0.0f);



	glEnd();//finaliza rutina
	glPopMatrix();
}

void dibujarEnemigo() {
	glPushMatrix();
	glTranslatef(0.0f, barraDerechaY, 0.0f);

	glBegin(GL_QUADS);//Inicia la rutina con un modo de dibujo

	glColor3f(1.0f, 1.0f, 1.0f);

	glVertex3f(0.85f, -0.2f, 0.0f);
	glVertex3f(0.85f, 0.2f, 0.0f);
	glVertex3f(0.90f, 0.2f, 0.0f);
	glVertex3f(0.90f, -0.2f, 0.0f);




	glEnd();//finaliza rutina
	glPopMatrix();
}

void dibujarPelota()
{
	glPushMatrix();
	glTranslatef(pelotaX, pelotaY, 0.0f);
	glScalef(0.15f, 0.15f, 0.15f);
	
	glBegin(GL_POLYGON);

		glColor3f(1.0f, 1.0f, 1.0f);

	for (float i = 0; i < 360; i++)
	{
		glVertex3f(0.2*cos(i) + -0.79, 0.2*sin(i) + 0.4, 0.0f);

	}

	glEnd();

	glPopMatrix();
}




void dibujar() {
	dibujarHeroe();
	dibujarEnemigo();
	dibujarPelota();
		dibujarLimites();
}
void key_callback(GLFWwindow* window, int key,
	int scancode, int action, int mods)
{

	// iquierda
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (barraIzquierdaY < 0.9)
			barraIzquierdaY += 0.09;
	}

	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (barraIzquierdaY > -0.9)
			barraIzquierdaY -= 0.09f;
	}

	//derecha

	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (barraDerechaY < 0.9)
			barraDerechaY += 0.09;
	}

	if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (barraDerechaY > -0.9)
			barraDerechaY -= 0.09f;
	}

		

}

int main()
{

	//Propiedades de la ventana
	GLfloat ancho = 1000;
	GLfloat alto = 700;

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
