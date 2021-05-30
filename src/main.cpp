#include "freeglut.h"
#include "Mundo.h"
#include "ETSIDI.h"
#include "GestorDeTeclado.h"
#include "CoordinadorIsaac.h"

void OnDraw(void); //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	
void OnKeyboardUp(unsigned char key, int x, int y);
void onSpecialKeyboardDown(int key, int x, int y);
void onSpecialKeyboardUp(int key, int x, int y);

//Mundo mundo;
CoordinadorIsaac isaac;

int main(int argc, char* argv[]){
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(1024, 576);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("ISAAC");

	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 16.0f / 9.0f, 0.1, 180);

	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);
	glutKeyboardUpFunc(OnKeyboardUp);
	glutSpecialFunc(onSpecialKeyboardDown); //gestion de los cursores
	glutSpecialUpFunc(onSpecialKeyboardUp);



	///INICIALIZACIONES
	isaac.inicializa();


	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();

	return 0;
}

void OnDraw(void){
	//Borrado de la pantalla	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	///LLAMADA A FUNCION DE DIBUJO
	isaac.dibuja();

	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}

void OnKeyboardDown(unsigned char key, int x_t, int y_t){
	
	//LLAMADAS DE TECLADO
	//poner aqui el código de teclado
	GestorDeTeclado::pressKey(key);
	isaac.tecla();
	//isaac.tecla_disparo();

	GestorDeTeclado::update();
	glutPostRedisplay();
}

void OnKeyboardUp(unsigned char key, int x_t, int y_t) {
	GestorDeTeclado::releaseKey(key);
	isaac.tecla();
	//mundo.tecla_up(key);

	GestorDeTeclado::update();
	glutPostRedisplay();
}

void onSpecialKeyboardDown(int key, int x, int y)
{
	GestorDeTeclado::pressKey(key);
	isaac.teclaEspecial();

	GestorDeTeclado::update();
	glutPostRedisplay();
}

void onSpecialKeyboardUp(int key, int x, int y) {
	GestorDeTeclado::releaseKey(key);
	isaac.teclaEspecial();

	GestorDeTeclado::update();
	glutPostRedisplay();
}

void OnTimer(int value){

	//CÓDIGO DE ANIMACION
	isaac.mueve();
	
	GestorDeTeclado::update();
	//no borrar estas lineas
	glutTimerFunc(25, OnTimer, 0);
	glutPostRedisplay();
}