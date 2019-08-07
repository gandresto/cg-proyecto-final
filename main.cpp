//Semestre 2019 - 1
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************	González Flores Andrés                  ******//
//*************	Sánchez Díaz Omar Diego                 ******//
//*************	Alonso Sotres Arian                     ******//
//************************************************************//
//************************************************************//

#include <ctime>
#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#define ROTSPEED 0.03
#define TIMERMSECS 5
#define N_PISOS 5
#define POS_IX 0
#define POS_IY 600
#define POS_IZ 3000

const double PI = 3.1415926535897;

// Global variables for measuring time (in milli-seconds)
clock_t startTime;
clock_t prevTime;

int w = 500, h = 500;
int frame=0,timebase=0;
int deltaTime = 0;

//---- PARA LAS ANIMACIONES
float desplaza = 0.0;
float cielo = 0.0;
bool animaGab = false;

GLfloat altura_dron = 0.0;
GLfloat t = 0.0;
GLfloat ang_rot_helices = 0.0;
GLfloat ang_rot_dron = 0.0;
bool anima_dron = true;

// Animación puerta
GLint ang_rot_puerta = 0;

//Variables para keyframes
/////////////////////////////////////////////////////////////////////
float posX = 0.0, posY = 105.0, posZ = 1050.0, rotRodIzq = 0.0, rotRodDer = 0.0, rotManIzqZ = 0.0, rotManDerZ = 0.0, rotManIzqY = 0.0, rotManDerY = 0.0, rotPechoX = 0.0, rotPechoY = 0.0;
float giroPersonaje = 0.0;

#define MAX_FRAMES 10
int i_max_steps = 50;
int i_curr_steps = 0;

typedef struct _frame
{
	float posX;
	float posY;
	float posZ;
	float incX;
	float incY;
	float incZ;
	float rotRodIzq;
	float rotRodDer;
	float rotManIzqZ;
	float rotManDerZ;
	float rotManIzqY;
	float rotManDerY;
	float rotPechoX;
	float rotPechoY;
	float incRotMDZ;
	float incRotMIZ;
	float incRotMDY;
	float incRotMIY;
	float incRotRD;
	float incRotRI;
	float incRotPX;
	float incRotPY;
	float giroPersonaje;
	float giroPersonajeInc;

}FRAME;

float FposX[] = { -1000.0, -850.0, -600.0, -500.0, -250.0, 0.0, 0.0 , 0.0 , 0.0 , 0.0 };
float FposZ[] = { 1800.0, 1800.0, 1800.0 , 1800.0 , 1800.0 , 1800.0 , 1800.0 , 1800.0 , 1800.0 , 1800.0 };
float FrotRodIzq[] = { 0.0, 50.0, -50.0, 50.0, -50.0, 0.0, 0.0 , 0.0 , 0.0 , 0.0 };
float FrotRodDer[] = { 0.0, -50.0, 50.0, -50.0, 50.0, 0.0, 0.0 , 0.0 , 0.0 , 0.0 };
float FrotManIzqZ[] = { 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, -125.0, -125.0, -125.0, 90.0 };
float FrotManDerZ[] = { 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0 };
float FrotManIzqY[] = { 0.0, 45.0, -45.0, 45.0, -45.0, 0.0, 50.0, 50.0, 50.0, 0.0 };
float FrotManDerY[] = { 0.0, -45.0, 45.0, -45.0, 45.0, 0.0, 0.0, 0.0, 0.0 };
float FrotPechoX[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -27.0, -27.0, -27.0, 0.0 };
float FrotPechoY[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 25.0, -25.0, 0.0 };
float FgiroPersonaje[] = { 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 180.0, 180.0, 180.0, 90.0 };

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;
bool play = false;
int playIndex = 0;
/////////////////////////////////////////////////////////////////////

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

// ------- Para la Iluminación
GLfloat diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };			// Diffuse Light Values
GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat position[]= { 2.0f, 10.0f, 10.0f, 0.0f };			// Light Position
GLfloat position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

//--------- TEXTURAS -------------
CTexture text_sky;
CTexture tree;
CTexture ladrilloB; // textura de los ladrillos blancos
CTexture t_humano;
CTexture t_concreto1;
CTexture t_piso_ext; // textura principal del piso exterior
CTexture t_pino;
CTexture t_concreto_cafe;
CTexture t_grass;
CTexture piso_lab;
CTexture t_edificio_p; // textura principal del edificio
CTexture metal_patas;
CTexture t_placa_lab;
CTexture laton;
CTexture helice_dron;
CTexture t_cuerpo_dron;
CTexture t_sky;
CTexture t_sky_large;
CTexture t_piso_lobby;
CTexture t_ventana;
CTexture t_puerta_principal;
CTexture t_puerta_madera;
CTexture t_puerta_madera_lateral;
CTexture t_hackberry_tree;
CTexture t_pupitre;

//--
CTexture t_madera;
CTexture t_monitor;
CTexture t_sesion;
CTexture t_gabinetef;
CTexture t_gabineteR;
CTexture t_gabinete;
CTexture t_teclado;
CTexture t_silla;
CTexture t_pizarron;
CTexture t_techo;
CTexture t_cemento_grava;

// Colores
GLfloat cafe[3] = { 0.466, 0.3294, 0.2117 };
GLfloat verde_pasto[3] = { 0.2902, 0.4078, 0.09411 };

CFiguras sky;
CFiguras cf_objeto;
CFiguras cf_tree;

//Para crear al personaje de los keyframes
CFiguras personaje;

// Funciones para los keyframes
void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq;
	rotRodDer = KeyFrame[0].rotRodDer;
	rotManIzqZ = KeyFrame[0].rotManIzqZ;
	rotManDerZ = KeyFrame[0].rotManDerZ;
	rotManIzqY = KeyFrame[0].rotManIzqY;
	rotManDerY = KeyFrame[0].rotManDerY;
	rotPechoX = KeyFrame[0].rotPechoX;
	rotPechoY = KeyFrame[0].rotPechoY;
	giroPersonaje = KeyFrame[0].giroPersonaje;

}

void interpolation(void)
{
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	KeyFrame[playIndex].incRotRI = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	KeyFrame[playIndex].incRotRD = (KeyFrame[playIndex + 1].rotRodDer - KeyFrame[playIndex].rotRodDer) / i_max_steps;
	KeyFrame[playIndex].incRotMIZ = (KeyFrame[playIndex + 1].rotManIzqZ - KeyFrame[playIndex].rotManIzqZ) / i_max_steps;
	KeyFrame[playIndex].incRotMDZ = (KeyFrame[playIndex + 1].rotManDerZ - KeyFrame[playIndex].rotManDerZ) / i_max_steps;
	KeyFrame[playIndex].incRotMIY = (KeyFrame[playIndex + 1].rotManIzqY - KeyFrame[playIndex].rotManIzqY) / i_max_steps;
	KeyFrame[playIndex].incRotMDY = (KeyFrame[playIndex + 1].rotManDerY - KeyFrame[playIndex].rotManDerY) / i_max_steps;
	KeyFrame[playIndex].incRotPX = (KeyFrame[playIndex + 1].rotPechoX - KeyFrame[playIndex].rotPechoX) / i_max_steps;
	KeyFrame[playIndex].incRotPY = (KeyFrame[playIndex + 1].rotPechoY - KeyFrame[playIndex].rotPechoY) / i_max_steps;
	KeyFrame[playIndex].giroPersonajeInc = (KeyFrame[playIndex + 1].giroPersonaje - KeyFrame[playIndex].giroPersonaje) / i_max_steps;
}

void Personaje()
{
	glPushMatrix();//Pecho
	glScalef(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(0.0, -1.0, 0.0);
	glRotatef(rotPechoX, 1, 0, 0);
	glRotatef(rotPechoY, 0, 1, 0);
	glTranslatef(0.0, 1.0, 0.0);
	personaje.prisma(2.0, 2.0, 1, NULL);

	glPushMatrix();//Cuello
	glTranslatef(0, 1.0, 0.0);
	personaje.cilindro(0.25, 0.25, 15, 0);
	glPushMatrix();//Cabeza
	glTranslatef(0, 1.0, 0);
	personaje.esfera(0.75, 15, 15, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //Brazo derecho
	glTranslatef(1.25, 0.65, 0);
	personaje.esfera(0.5, 12, 12, 0);
	glPushMatrix();
	glTranslatef(0.25, 0, 0);
	glRotatef(-rotManDerZ, 0, 0, 1);
	glRotatef(-rotManDerY, 0, 1, 0);
	glTranslatef(1, 0, 0);
	personaje.prisma(2.0, 0.7, 0.7, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //Brazo izquierdo
	glTranslatef(-1.25, 0.65, 0);
	personaje.esfera(0.5, 12, 12, 0);
	glPushMatrix();
	glTranslatef(-0.25, 0, 0);
	glRotatef(rotManIzqZ, 0, 0, 1);
	glRotatef(rotManIzqY, 0, 1, 0);
	glTranslatef(-1.0, 0, 0);
	personaje.prisma(2.0, 0.7, 0.7, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();//Cintura
	glColor3f(0, 0, 1);
	glTranslatef(0, -1.5, 0);
	personaje.prisma(2, 1, 1, 0);

	glPushMatrix(); //Pie Derecho
	glTranslatef(0.75, -0.5, 0);
	glTranslatef(0, -0.5, 0);
	personaje.prisma(0.5, 1.0, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glRotatef(rotRodDer, 1, 0, 0);
	glTranslatef(0, -0.75, 0);
	personaje.prisma(0.5, 1.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.75, 0.3);
	personaje.prisma(1.2, 0.2, 1.5, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix(); //Pie Izquierdo
	glTranslatef(-0.75, -0.5, 0);
	glTranslatef(0, -0.5, 0);
	personaje.prisma(0.5, 1.0, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glRotatef(rotRodIzq, 1, 0, 0);
	glTranslatef(0, -0.75, 0);
	personaje.prisma(0.5, 1.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.75, 0.3);
	personaje.prisma(1.2, 0.2, 1.5, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPopMatrix();


	glColor3f(1, 1, 1);
	glPopMatrix();
}
/////////////////////////////////////////////////////////////////////

void cargar_texturas() {

	t_pupitre.LoadBMP("textures/pupitre.bmp");
	t_pupitre.BuildGLTexture();
	t_pupitre.ReleaseImage();

	helice_dron.LoadTGA("textures/helice_dron.tga");
	helice_dron.BuildGLTexture();
	helice_dron.ReleaseImage();

	t_humano.LoadTGA("textures/escala_humana.tga");
	t_humano.BuildGLTexture();
	t_humano.ReleaseImage();

	t_concreto1.LoadTGA("textures/concreto01.tga");
	t_concreto1.BuildGLTexture();
	t_concreto1.ReleaseImage();

	ladrilloB.LoadBMP("textures/ladrillo_blanco.bmp");
	ladrilloB.BuildGLTexture();
	ladrilloB.ReleaseImage();

	t_grass.LoadBMP("textures/grass2.bmp");
	t_grass.BuildGLTexture();
	t_grass.ReleaseImage();

	t_piso_ext.LoadTGA("textures/concreto_ext.tga");
	t_piso_ext.BuildGLTexture();
	t_piso_ext.ReleaseImage();

	t_concreto_cafe.LoadTGA("textures/concreto_cafe.tga");
	t_concreto_cafe.BuildGLTexture();
	t_concreto_cafe.ReleaseImage();

	t_pino.LoadTGA("textures/pino1.tga");
	t_pino.BuildGLTexture();
	t_pino.ReleaseImage();

	piso_lab.LoadTGA("textures/piso_lab.tga");
	piso_lab.BuildGLTexture();
	piso_lab.ReleaseImage();

	t_madera.LoadBMP("textures/madera.bmp");
	t_madera.BuildGLTexture();
	t_madera.ReleaseImage();

	t_sesion.LoadBMP("textures/sesion.bmp");
	t_sesion.BuildGLTexture();
	t_sesion.ReleaseImage();

	t_teclado.LoadBMP("textures/teclado.bmp");
	t_teclado.BuildGLTexture();
	t_teclado.ReleaseImage();

	t_monitor.LoadBMP("textures/monitor.bmp");
	t_monitor.BuildGLTexture();
	t_monitor.ReleaseImage();

	t_gabinetef.LoadBMP("textures/gabinetef.bmp");
	t_gabinetef.BuildGLTexture();
	t_gabinetef.ReleaseImage();

	t_gabineteR.LoadBMP("textures/gabineteR.bmp");
	t_gabineteR.BuildGLTexture();
	t_gabineteR.ReleaseImage();

	t_gabinete.LoadBMP("textures/gabinete.bmp");
	t_gabinete.BuildGLTexture();
	t_gabinete.ReleaseImage();

	t_silla.LoadBMP("textures/silla.bmp");
	t_silla.BuildGLTexture();
	t_silla.ReleaseImage();

	t_edificio_p.LoadTGA("textures/t_edificio_p2.tga");
	t_edificio_p.BuildGLTexture();
	t_edificio_p.ReleaseImage();

	metal_patas.LoadTGA("textures/metal_patas.tga");
	metal_patas.BuildGLTexture();
	metal_patas.ReleaseImage();

	laton.LoadTGA("textures/laton.tga");
	laton.BuildGLTexture();
	laton.ReleaseImage();

	t_placa_lab.LoadTGA("textures/placa_lab.tga");
	t_placa_lab.BuildGLTexture();
	t_placa_lab.ReleaseImage();

	t_cuerpo_dron.LoadTGA("textures/t_cracked_b.tga");
	t_cuerpo_dron.BuildGLTexture();
	t_cuerpo_dron.ReleaseImage();

	t_sky.LoadTGA("textures/sky2.tga");
	t_sky.BuildGLTexture();
	t_sky.ReleaseImage();

	t_sky_large.LoadTGA("textures/sky_large.tga");
	t_sky_large.BuildGLTexture();
	t_sky_large.ReleaseImage();

	t_pizarron.LoadTGA("textures/whiteboard.tga");
	t_pizarron.BuildGLTexture();
	t_pizarron.ReleaseImage();

	t_techo.LoadBMP("textures/techo.bmp");
	t_techo.BuildGLTexture();
	t_techo.ReleaseImage();

	t_cemento_grava.LoadTGA("textures/cemento_grava.tga");
	t_cemento_grava.BuildGLTexture();
	t_cemento_grava.ReleaseImage();

	t_piso_lobby.LoadTGA("textures/piso_lobby.tga");
	t_piso_lobby.BuildGLTexture();
	t_piso_lobby.ReleaseImage();

	t_ventana.LoadTGA("textures/ventana.tga");
	t_ventana.BuildGLTexture();
	t_ventana.ReleaseImage();

	t_puerta_principal.LoadTGA("textures/puerta_principal.tga");
	t_puerta_principal.BuildGLTexture();
	t_puerta_principal.ReleaseImage();

	t_puerta_madera.LoadTGA("textures/puerta_madera.tga");
	t_puerta_madera.BuildGLTexture();
	t_puerta_madera.ReleaseImage();

	t_puerta_madera_lateral.LoadTGA("textures/puerta_madera_lateral.tga");
	t_puerta_madera_lateral.BuildGLTexture();
	t_puerta_madera_lateral.ReleaseImage();

	t_hackberry_tree.LoadTGA("textures/hackberry_tree.tga");
	t_hackberry_tree.BuildGLTexture();
	t_hackberry_tree.ReleaseImage();
}

void dibuja_arbol(GLfloat copa, GLfloat alto, GLuint textura) //Un árbol de 20x20 cm
{
	//glColor3f(.75, .8, .75);
	glDisable(GL_LIGHTING);
	glEnable( GL_ALPHA_TEST );
	glAlphaFunc( GL_GREATER, 0.1 );
	glBindTexture(GL_TEXTURE_2D, textura);	
	glPushMatrix();		
		glTranslatef(0.0, alto / 2.0, 0.0);
		for (GLbyte i = 0; i < 4; i++) {
			glRotatef(45*i, 0, 1, 0);
			cf_tree.plano(copa, alto, textura);			
		}
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);	
	glDisable( GL_ALPHA_TEST );
}

// Creacion de metodos para figuras u objetos
void pizzaron()
{
	glRotatef(90.0, 1.0, 0.0, 0.0);	
	glPushMatrix();
		glScalef(600.0, 1.0, 200.0);
		cf_objeto.prisma2(t_pizarron.GLindex, metal_patas.GLindex);
	glPopMatrix();
}

void silla()
{
	//-----------------------------------------------------------------------------------------//
	// Codigo para generar una silla //
	// Patas de la silla //	
	glPushMatrix(); //1
		glTranslatef(-20.5, 22.5, -20.5);
		cf_objeto.prisma(4.0, 45.0, 4.0, metal_patas.GLindex); 
	glPopMatrix();
	glPushMatrix();//2
		glTranslatef(20.5, 22.5, -20.5);
		cf_objeto.prisma(4.0, 45.0, 4.0, metal_patas.GLindex);
	glPopMatrix();
	glPushMatrix();//3
		glTranslatef(20.5, 22.5, 20.5);
		cf_objeto.prisma(4.0, 45.0, 4.0, metal_patas.GLindex);
	glPopMatrix();
	glPushMatrix(); //4
		glTranslatef(-20.5, 22.5, 20.5);
		cf_objeto.prisma(4.0, 45.0, 4.0, metal_patas.GLindex);
	glPopMatrix();

	// Generando el asiento //
	glPushMatrix(); //asiento
		glTranslatef(0.0, 47.0, 0.0); 
		cf_objeto.prisma(45.0, 4.0, 45.0, t_silla.GLindex); 
	glPopMatrix();

	// Generando el respaldo de la silla  //

	glPushMatrix(); //respaldo
		glTranslatef(0.0, 68.0, -20.5); // (yzx)
		cf_objeto.prisma(45.0, 42.0, 4.0, t_silla.GLindex); // (z,y,x) 
	glPopMatrix();
}

void pupitre()
{
	//-----------------------------------------------------------------------------------------//
	// Codigo para generar una silla //
	// Patas de la silla //	
	glPushMatrix();
	glRotatef(90, 0.0, 1.0, 0.0);

	glPushMatrix(); //1
	glTranslatef(-15.0, 22.5, -15); // y
	cf_objeto.prisma(2.0, 45.0, 2.0, metal_patas.GLindex);
	glPopMatrix();
	glPushMatrix();//2
	glTranslatef(15.0, 22.5, -15);
	cf_objeto.prisma(2.0, 45.0, 2.0, metal_patas.GLindex);
	glPopMatrix();
	glPushMatrix();//3
	glTranslatef(15.0, 22.5, 15);
	cf_objeto.prisma(2.0, 45.0, 2.0, metal_patas.GLindex);
	glPopMatrix();
	glPushMatrix(); //4
	glTranslatef(-15.0, 22.5, 15);
	cf_objeto.prisma(2.0, 45.0, 2.0, metal_patas.GLindex);
	glPopMatrix();

	// Generando el asiento //
	glPushMatrix(); //asiento
	glTranslatef(0.0, 47.0, 0.0);
	cf_objeto.prisma(34.0, 4.0, 34.0, t_pupitre.GLindex);
	glPopMatrix();

	// Generando el respaldo de la silla  //

	glPushMatrix(); //respaldo
	glTranslatef(0.0, 85.0, -15); // (yzx)
	cf_objeto.prisma(34.0, 20.0, 2.0, t_pupitre.GLindex); // (y,z,x) 
	glPopMatrix();

	glPushMatrix(); //1
	glTranslatef(-5.0, 68.0, -16); // y
	cf_objeto.prisma(2.0, 37.0, 1.0, metal_patas.GLindex);
	glPopMatrix();
	glPushMatrix();//2
	glTranslatef(5.0, 68.0, -16);
	cf_objeto.prisma(2.0, 37.0, 1.0, metal_patas.GLindex);
	glPopMatrix();

	// Haciendo la paleta de la silla //
	glPushMatrix(); //soporte
	glRotatef(18, 1.0, 0.0, 0.0);
	glTranslatef(-15.0, 57.0, -10);
	cf_objeto.prisma(2.0, 22.0, 2.0, metal_patas.GLindex);
	glPopMatrix();

	glPushMatrix(); //soporte2
	glRotatef(25, 1.0, 0.0, 0.0);
	glTranslatef(-15.0, 58.5, -10);
	cf_objeto.prisma(2.0, 19.0, 2.0, metal_patas.GLindex);
	glPopMatrix();

	glPushMatrix(); //respaldo
	glTranslatef(-5.0, 67.0, 15); // (yzx)
	cf_objeto.prisma(27.0, 2.0, 20.0, t_pupitre.GLindex); // (y,z,x) 
	glPopMatrix();

	glPopMatrix();
}

void mesa_profe()
{
	//-----------------------------------------------------------------------------------------//
	// Codigo para generar una mesa //
	// Patas de la mesa //	
	glPushMatrix(); //1
	glTranslatef(-99.0, 37.5, -28.0);
	cf_objeto.prisma(4.0, 75.0, 4.0, t_madera.GLindex);
	glPopMatrix();
	glPushMatrix();//2
	glTranslatef(99.0, 37.5, -28.0);
	cf_objeto.prisma(4.0, 75.0, 4.0, t_madera.GLindex);
	glPopMatrix();
	glPushMatrix();//3
	glTranslatef(99.0, 37.5, 28.0);
	cf_objeto.prisma(4.0, 75.0, 4.0, t_madera.GLindex);
	glPopMatrix();
	glPushMatrix(); //4
	glTranslatef(-99.0, 37.5, 28.0);
	cf_objeto.prisma(4.0, 75.0, 4.0, t_madera.GLindex);
	glPopMatrix();

	// Generando la tabla //
	glPushMatrix(); //tabla
	glTranslatef(0.0, 77.0, 0.0); // (yzx)
	cf_objeto.prisma(200.0, 4.0, 60.0, t_madera.GLindex); // (y,z,x) 
	glPopMatrix();
}

void mesa()
{
	//-----------------------------------------------------------------------------------------//
	// Codigo para generar una mesa //
	// Patas de la mesa //	
	glPushMatrix(); //1
		glTranslatef(-198.0, 37.5, -28.0);
		cf_objeto.prisma(4.0, 75.0, 4.0, t_madera.GLindex);
	glPopMatrix();
	glPushMatrix();//2
		glTranslatef(198.0, 37.5, -28.0);
		cf_objeto.prisma(4.0, 75.0, 4.0, t_madera.GLindex);
	glPopMatrix();
	glPushMatrix();//3
		glTranslatef(198.0, 37.5, 28.0);
		cf_objeto.prisma(4.0, 75.0, 4.0, t_madera.GLindex);
	glPopMatrix();
	glPushMatrix(); //4
		glTranslatef(-198.0, 37.5, 28.0);
		cf_objeto.prisma(4.0, 75.0, 4.0, t_madera.GLindex);
	glPopMatrix();

	// Generando la tabla //
	glPushMatrix(); //tabla
		glTranslatef(0.0, 77.0, 0.0); // (yzx)
		cf_objeto.prisma(400.0, 4.0, 60.0, t_madera.GLindex); // (y,z,x) 
	glPopMatrix();
}

void monitor()
{
	glPushMatrix(); //Base
		glTranslatef(0.0, 1.0, 0.0); 
		cf_objeto.prisma(20.0, 2.0, 20.0, t_monitor.GLindex); 
	glPopMatrix();

	glPushMatrix(); //Soporte o brazo 
		glTranslatef(0.0, 10.0, 0.0); 
		cf_objeto.prisma(8.0, 20.0, 1.5, t_monitor.GLindex); 
	glPopMatrix();

	glPushMatrix(); //Pantalla
		glTranslatef(0.0, 25.0, 0.75);
		cf_objeto.prisma(45.0, 34.0, 0.07, t_monitor.GLindex); 

		glTranslatef(0.0, 0.0, 0.1);
		glPushMatrix(); //imagen monitor	
			glRotatef(180.0,0.0,1.0,0.0);
			cf_objeto.plano(43.0, 32.0, t_sesion.GLindex); 
		glPopMatrix();
	glPopMatrix();
}

void gabinete()
{
	glPushMatrix();	
		glTranslatef(0.0, 14.0, 0.0);
		glScalef(10.0, 28.0, 30.0);
		cf_objeto.prisma_4_text(t_gabinetef.GLindex, t_gabinete.GLindex, t_gabineteR.GLindex, t_gabinete.GLindex, t_gabinete.GLindex, t_gabinete.GLindex);
	glPopMatrix();
}

void gabineteAnima()
{
	glPushMatrix();
		glTranslatef(0.0, 14.0, 0.0);
		glScalef(10.0, 10.0, 10.0);
		cf_objeto.prismaGabAnima(1.0, 2.8, 3.0, desplaza, t_gabinete.GLindex, t_gabinetef.GLindex, t_gabineteR.GLindex);
	glPopMatrix();

}

void teclado()
{
	glPushMatrix();
	glTranslatef(0.0, 0.75, 0.0); 
	glScaled(42.0, 1.5, 13.0);	
	cf_objeto.prisma2(t_teclado.GLindex, t_gabinete.GLindex); 
	glPopMatrix();
}

void grupo_silla_compu() {
	glPushMatrix();
		glTranslatef(0.0, 0.0, 30.0);
		glRotatef(180.0, 0.0, 1.0, 0.0);
		silla();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 79.0, 20.0);
		teclado();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 79.0, 0.0);
		monitor();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-35.0, 79.0, 0.0);
		gabineteAnima();
		//gabinete();
	glPopMatrix();
}

void mobiliario_lab() {
	mesa();
	glPushMatrix();
		//Sillas y compus 1
		glTranslatef(-150.0, 0.0, 0.0);
		grupo_silla_compu();

		//Sillas y compus 2
		glTranslatef(100.0, 0.0, 0.0);
		grupo_silla_compu();

		//Sillas y compus 3
		glTranslatef(100.0, 0.0, 0.0);
		grupo_silla_compu();

		//Sillas y compus 4
		glTranslatef(100.0, 0.0, 0.0);
		grupo_silla_compu();
	glPopMatrix();
}

void placa_lab() {
	glRotatef(90.0, 1.0, 0.0, 0.0);	
	glPushMatrix();
		glScalef(50.0, 1.0, 43.0);
		cf_objeto.prisma2(t_placa_lab.GLindex, laton.GLindex);
	glPopMatrix();
}

void ala_dron() {
	glColor3f(0.2, 0.2, 0.2);
	cf_objeto.prisma(12.0, 0.2, 1.0,0); //ala dron
	glPushMatrix();
		glTranslatef(5.5, 0.0, 0.0);
		cf_objeto.cilindro(0.5, 1.5, 50.0,0); //balero helice
		glPushMatrix();
			glTranslatef(0.0, 1.5, 0.0);
			glRotatef(90.0, 1.0, 0.0, 0.0);
			glColor3f(1.0, 1.0, 1.0);
			glEnable( GL_ALPHA_TEST );				
			glAlphaFunc( GL_GREATER, 0.1 );
			glRotatef(ang_rot_helices, 0.0, 0.0, 1.0); //animación helices
			cf_objeto.plano(20.0, 20.0, helice_dron.GLindex); //helice
			glDisable(GL_ALPHA_TEST);
		glPopMatrix();
	glPopMatrix();
	glColor3f(1.0, 1.0, 1.0);
}

void dron() {
	cf_objeto.prisma(8.5, 5.0, 22.0, t_cuerpo_dron.GLindex); //cuerpo dron
	glPushMatrix();
		glTranslatef(-8.0, 2.0, -9.0);
		glRotatef(135.0, 0.0, 1.0, 0.0);
		ala_dron();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.0, 2.0, -9.0);
		glRotatef(45.0, 0.0, 1.0, 0.0);
		ala_dron();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-8.0, 2.0, 9.0);
		glRotatef(-135.0, 0.0, 1.0, 0.0);
		ala_dron();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.0, 2.0, 9.0);
		glRotatef(-45.0, 0.0, 1.0, 0.0);
		ala_dron();
	glPopMatrix();
	
}

void dibuja_humano() {
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glBindTexture(GL_TEXTURE_2D, t_humano.GLindex);
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-25, 0.0, 0.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(25, 0.0, 0.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(25, 170.0, 0.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-25, 170.0, 0.0);
	glEnd();
	glDisable(GL_ALPHA_TEST);
}

void dibuja4muros(GLfloat esc_x, GLfloat esc_y, GLfloat esc_z, GLuint textura_lados, GLuint textura_topybot) {	
	glColor3f(1.0, 1.0, 1.0);	
	glPushMatrix();
	glTranslatef(0.0, 0.0, -(esc_z/2.0-7.5));
	cf_objeto.muro(esc_x, esc_y, textura_lados, textura_topybot);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, esc_z / 2.0 - 7.5);
	cf_objeto.muro(esc_x, esc_y, textura_lados, textura_topybot);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-(esc_x / 2.0 - 7.5), 0.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	cf_objeto.muro(esc_z - 30.0, esc_y, textura_lados, textura_topybot);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(esc_x / 2.0 - 7.5, 0.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	cf_objeto.muro(esc_z - 30, esc_y, textura_lados, textura_topybot);
	glPopMatrix();	
}

void dibuja4prismas(GLfloat esc_x, GLfloat esc_y, GLfloat esc_z, GLuint textura, GLfloat tam_text_x, GLfloat tam_text_y) {
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, -(esc_z / 2.0 - 7.5));
	cf_objeto.muro_1text(esc_x, esc_y, textura, tam_text_x, tam_text_y);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, esc_z / 2.0 - 7.5);
	cf_objeto.muro_1text(esc_x, esc_y, textura, tam_text_x, tam_text_y);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-(esc_x / 2.0 - 7.5), 0.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	cf_objeto.muro_1text(esc_z - 30.0, esc_y, textura, tam_text_x, tam_text_y);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(esc_x / 2.0 - 7.5, 0.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	cf_objeto.muro_1text(esc_z - 30, esc_y, textura, tam_text_x, tam_text_y);
	glPopMatrix();
}

void dibuja2muros(GLfloat esc_x, GLfloat esc_y, GLfloat esc_z, GLuint textura, GLfloat tam_text_x, GLfloat tam_text_y) {
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, -(esc_z / 2.0 - 7.5));
	cf_objeto.muro_1text(esc_x, esc_y, textura, tam_text_x, tam_text_y);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, esc_z / 2.0 - 7.5);
	cf_objeto.muro_1text(esc_x, esc_y, textura, tam_text_x, tam_text_y);
	glPopMatrix();
	/*
	glPushMatrix();
	glTranslatef(-(esc_x / 2.0 - 7.5), 0.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	cf_objeto.muro_1text(esc_z - 30.0, esc_y, textura, tam_text_x, tam_text_y);
	glPopMatrix();
	*/
	glPushMatrix();
	glTranslatef(esc_x / 2.0 - 7.5, 0.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	cf_objeto.muro_1text(esc_z - 30, esc_y, textura, tam_text_x, tam_text_y);
	glPopMatrix();
}

void ventana_inclinada() {
	glBindTexture(GL_TEXTURE_2D, t_ventana.GLindex);
	glBegin(GL_QUADS); //plano
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, -300.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0, 0.0, 300.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 230.0, 300.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, 300.0, -300.0);
	glEnd();
}

void jardinera_parte_posterior() {
	GLfloat vertice[8][3] = {
				{0.0 ,0.0, 800.0},    //Coordenadas Vértice 0 V0
				{-1800.0 ,0.0, 800.0},    //Coordenadas Vértice 1 V1
				{-2600.0 ,0.0, -0.0},    //Coordenadas Vértice 2 V2
				{0.0 ,0.0, 0.0},    //Coordenadas Vértice 3 V3
				{0.0 ,100.0, 800.0},    //Coordenadas Vértice 4 V4
				{0.0 ,100.0, 0.0},    //Coordenadas Vértice 5 V5
				{-2600.0 ,100.0, 0.0},    //Coordenadas Vértice 6 V6
				{-1800.0 ,100.0, 800.0},    //Coordenadas Vértice 7 V7
	};

	//glBindTexture(GL_TEXTURE_2D, 0);   // choose the texture to use.
	glColor3fv(cafe);
	glBegin(GL_POLYGON);	//Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON);	//Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON);	//Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[2]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[3]);
	glEnd();

	//glBindTexture(GL_TEXTURE_2D, 0);   // choose the texture to use.
	glColor3fv(verde_pasto);
	glBegin(GL_POLYGON);  //Top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[7]);
	glEnd();

	glPushMatrix();
		glTranslatef(0.0, 0.0, 400.0);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		cf_objeto.cil_semi_eliptico_2_colores(400.0, 400.0, 100.0, 180.0, 30, cafe, verde_pasto);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-400.0, 100.0, 400.0);
		dibuja_arbol(1600.0, 2000.0, t_hackberry_tree.GLindex);
	glPopMatrix();
	glColor3f(1.0, 1.0, 1.0);
}

void jardinera_trapecio() {
	GLfloat vertice [8][3] = {
				{800.0 ,0.0, 0.0},    //Coordenadas Vértice 0 V0
				{0.0 ,0.0, 0.0},    //Coordenadas Vértice 1 V1
				{0.0 ,0.0, -2400.0},    //Coordenadas Vértice 2 V2
				{800.0 ,0.0, -1600.0},    //Coordenadas Vértice 3 V3
				{800.0 ,100.0, 0.0},    //Coordenadas Vértice 4 V4
				{800.0 ,100.0, -1600.0},    //Coordenadas Vértice 5 V5
				{0.0 ,100.0, -2400.0},    //Coordenadas Vértice 6 V6
				{0.0 ,100.0, 0.0},    //Coordenadas Vértice 7 V7
				};
		
	//glBindTexture(GL_TEXTURE_2D, 0);   // choose the texture to use.
	glColor3fv(cafe);
	glBegin(GL_POLYGON);	//Front
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[4]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[1]);
	glEnd();
	
	glBegin(GL_POLYGON);	//Right
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON);	//Back
		glNormal3f( 0.0f, 0.0f,-1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[6]);
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[5]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[3]);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[1]);
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[7]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[6]);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[2]);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[3]);
	glEnd();

	//glBindTexture(GL_TEXTURE_2D, 0);   // choose the texture to use.
	glColor3fv(verde_pasto);
	glBegin(GL_POLYGON);  //Top
		glNormal3f( 0.0f,1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[4]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[7]);
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
}

void jardinera_frente() {
	GLfloat vertice[8][3] = {
				{0.0 ,0.0, 0.0},    //Coordenadas Vértice 0 V0
				{-950.0 ,0.0, 0.0},    //Coordenadas Vértice 1 V1
				{-950.0 ,0.0, -850},    //Coordenadas Vértice 2 V2
				{0.0 ,0.0, -850},    //Coordenadas Vértice 3 V3
				{0.0 ,100.0, 0.0},    //Coordenadas Vértice 4 V4
				{0.0 ,100.0, -850},    //Coordenadas Vértice 5 V5
				{-950.0 ,100.0, -850},    //Coordenadas Vértice 6 V6
				{-950.0 ,100.0, 0.0},    //Coordenadas Vértice 7 V7
	};

	//glBindTexture(GL_TEXTURE_2D, 0);   // choose the texture to use.
	glColor3fv(cafe);
	glBegin(GL_POLYGON);	//Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON);	//Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON);	//Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[2]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[3]);
	glEnd();

	//glBindTexture(GL_TEXTURE_2D, 0);   // choose the texture to use.
	glColor3fv(verde_pasto);
	glBegin(GL_POLYGON);  //Top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[7]);
	glEnd();

	glPushMatrix();
		glTranslatef(-950.0, 0.0, 0.0);
		glRotatef(180.0, 0.0, 1.0, 0.0);
		cf_objeto.cil_semi_eliptico_2_colores(500.0, 850.0, 100.0, 90.0, 30, cafe, verde_pasto);
	glPopMatrix();
	glColor3f(1.0, 1.0, 1.0);
}

void jardinera_pino() {
	glPushMatrix();
		//glTranslatef(3900.0, 0.0, 0.0);
		glRotatef(180, 0.0, 1.0, 0.0);
		jardinera_trapecio();
		glPushMatrix();
			glTranslatef(800.0, 0.0, -1600.0);
			glPushMatrix();
				glRotatef(135, 0.0, 1.0, 0.0);
				cf_objeto.cil_semi_eliptico_2_colores(1100.0, 800.0, 100.0, 90.0, 30.0, cafe, verde_pasto);
			glPopMatrix();
			glPushMatrix();
				glRotatef(45, 0.0, 1.0, 0.0);
				cf_objeto.cil_semi_eliptico_2_colores(800.0, 400.0, 100.0, 135.0, 30.0, cafe, verde_pasto);
			glPopMatrix();
		glPopMatrix();
		glTranslatef(600.0, 100.0, -1800.0);
		dibuja_arbol(500.0,1200.0,t_pino.GLindex);
	glPopMatrix();
}

void puerta_madera(GLfloat largo, GLfloat alto, GLfloat profundidad) {
	glPushMatrix();
	glScalef(largo, alto, profundidad);
	cf_objeto.prisma_4_text(t_puerta_madera.GLindex, t_puerta_madera.GLindex, t_puerta_madera_lateral.GLindex, t_puerta_madera_lateral.GLindex, t_puerta_madera_lateral.GLindex, t_puerta_madera_lateral.GLindex);
	glPopMatrix();
}

void lobby_principal() // dibuja toda la parte central del edificio
{
	// Escalones y espacio al aire libre
	glPushMatrix();
		glTranslatef(0.0, 90.0, -1700.0);
		cf_objeto.losa(1000.0, 600.0, t_piso_lobby.GLindex, t_concreto1.GLindex);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 6.25, -2375.0);
		for (GLbyte i = 0; i < 8; i++) {
			cf_objeto.prisma_text(1000.0, 12.5, 50.0, t_piso_lobby.GLindex, 50.0,50.0);
			glTranslatef(0.0, 12.5, 50.0);
		}
	glPopMatrix();

	// ------------------  Entrada trasera
	glPushMatrix();
		glTranslatef(0.0, 100.0, -1392.5);
		glPushMatrix();
			glTranslatef(300.0, 0.0, 0.0);
			cf_objeto.muro_1text(400.0, 300.0, t_edificio_p.GLindex, 100.0,100.0); //muro lateral
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-300.0, 0.0, 0.0);
			cf_objeto.muro_1text(400.0, 300.0, t_edificio_p.GLindex, 100.0,100.0);  //muro lateral
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, 200.0, 0.0);
			cf_objeto.muro_1text(200.0, 100.0, t_edificio_p.GLindex, 100.0,100.0); //muro de arriba de la puerta
		glPopMatrix();

		//Puerta de madera
		glPushMatrix();
			//mover el eje para rotar la puerta
			glTranslatef(100.0, 0.0, 0.0);
			glRotatef(-ang_rot_puerta, 0.0, 1.0, 0.0);

			glTranslatef(-50.0, 100.0, 0.0);
			puerta_madera(100.0,200.0,10.0);
			
		glPopMatrix();

		glPushMatrix();
			//mover el eje para rotar la puerta
			glTranslatef(-100.0, 0.0, 0.0);
			glRotatef(ang_rot_puerta, 0.0, 1.0, 0.0);

			glTranslatef(50.0, 100.0, 0.0);
			puerta_madera(100.0,200.0,10.0);			
		glPopMatrix();

	glPopMatrix();

	// Lobby
	glPushMatrix();
		glTranslatef(0.0, 90.0, -700.0);
		//Piso
		cf_objeto.losa(1000.0, 1400.0, t_piso_lobby.GLindex, t_concreto1.GLindex);
		//Pequeños muros de 80 cm arriba de la puerta principal
		glPushMatrix();
			glTranslatef(0.0, 310.0, 0.0);
			dibuja4prismas(1000.0, 80.0, 1400.0, t_edificio_p.GLindex, 100.0,100.0);
			cf_objeto.losa(990.0, 1390.0, t_edificio_p.GLindex, t_concreto1.GLindex);
		glPopMatrix();
	glPopMatrix();

	// -- Entrada frontal
	// muros laterales
	glPushMatrix();
		glTranslatef(692.5, 0.0, 300.0);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		cf_objeto.muro_1text(600.0, 100.0, t_edificio_p.GLindex, 100.0, 100.0); //muro 1m
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-692.5, 0.0, 300.0);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		cf_objeto.muro_1text(600.0, 100.0, t_edificio_p.GLindex, 100.0, 100.0); //muro 1m
	glPopMatrix();

	// muros frontales
	glPushMatrix();
		glTranslatef(350, 0.0, 1192.5);
		cf_objeto.muro_1text(300.0, 120.0, t_edificio_p.GLindex, 100.0, 100.0); //muro 1.2m
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-350, 0.0, 1192.5);
		cf_objeto.muro_1text(300.0, 120.0, t_edificio_p.GLindex, 100.0, 100.0); //muro 1.2m
	glPopMatrix();

	// Muros semielipticos
	glPushMatrix();
		glTranslatef(500.0, 0.0, 600.0);
		cf_objeto.cil_semi_eliptico(200.0, 600.0, 330.0, 90.0, 20.0, 0); //muro lado este
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-500.0, 0.0, 600.0);
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		cf_objeto.cil_semi_eliptico(600.0, 200.0, 330.0, 90.0, 20.0, 0); //muro lado oeste
	glPopMatrix();

	// Piso inclinado entrada frontal
	glPushMatrix();
		glTranslatef(0.0, 50.0, 600.0);
		glRotatef(94.76, 1.0, 0.0, 0.0);
		cf_objeto.plano_text(1000, 1204.2, t_piso_lobby.GLindex,50.0);
	glPopMatrix();

	//----------------------------------------------------------------------------//

}

void dibuja_mob_lab() {
	// Mobiliario Lab
	glPushMatrix();
		glPushMatrix();
			glTranslatef(400.0, 0.0, -400.0);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			dibuja_humano(); 
		glPopMatrix();

		glTranslatef(-200.0, 0.0, -400.0);
		glTranslatef(0.0, 0.0, -300);
		for (byte i = 0; i < 6; i++) {
			glPushMatrix();
			glTranslatef(GLfloat(i*160.0), 0.0, 0.0);
			glRotatef(90.0, 0.0, -1.0, 0.0);
			mobiliario_lab();
			glPopMatrix();
		}

		glTranslatef(0.0, 0.0, 600);
		for (byte i = 0; i < 6; i++) {
			glPushMatrix();
			glTranslatef(GLfloat(i*160.0), 0.0, 0.0);
			glRotatef(90.0, 0.0, -1.0, 0.0);
			mobiliario_lab();
			glPopMatrix();
		}
	glPopMatrix();		
			
	glPushMatrix();
		glTranslatef(984.5, 190.0, -400.0);
		glRotatef(90.0, 0.0, -1.0, 0.0);
		pizzaron(); // Pizarron
	glPopMatrix();
}

void dibuja_mob_salon() {
	//------------------------------------//
	glPushMatrix();
		glPushMatrix();
			glTranslatef(800.0, 0.0, -400.0);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			dibuja_humano();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(500.0, 0.0, 100.0);
		glScalef(1.0, 1.0, -1.0);
		for (byte j = 0; j < 10; j = j++)
		{
			for (byte i = 0; i < 11; i = i++)
			{
				glPushMatrix();
					glTranslatef(GLfloat(-j * 100), 0.0, GLfloat(i * 100)); //yzx
					pupitre();
				glPopMatrix();
			}
		}
		glPopMatrix();

		glPushMatrix();
			glTranslatef(984.5, 190.0, -400.0);
			glRotatef(90.0, 0.0, -1.0, 0.0);
			pizzaron(); // Pizarron
		glPopMatrix();

		//-- Mesa del profesor  --//
		glPushMatrix();
			glTranslatef(800.0, 0.0, -800.0);
			glRotatef(-90.0, 0.0, 1.0, 0.0);
			mesa_profe(); //  mesa
			glPushMatrix();
				glRotatef(180.0, 0.0, 1.0, 0.0);
				glTranslatef(-80.0, 0.0, 0.0);
				glPushMatrix();
					glTranslatef(0.0, 80, 0.0);
					gabinete();
					glPushMatrix();
						glTranslatef(45.0, 0.0, -10.0);
						monitor();
					glPopMatrix();
					glPushMatrix();
						glTranslatef(45.0, 0.0, 20.0);
						teclado();
					glPopMatrix();
					glPushMatrix();
						glRotatef(-180.0, 0.0, -1.0, 0.0);
						glTranslatef(-40.0, -80.0, -60.0);
						silla();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void dibuja_edificio_p(bool es_laboratorio) {
	glPushMatrix();
		// ----- Paredes restantes edificio
		glPushMatrix();
			glTranslatef(-1000.0, 190.0, 300.0);
			for (GLbyte i = 0; i < N_PISOS-1; i++) {
				glTranslatef(0.0, 380.0, 0.0);
				cf_objeto.prisma_text(15.0, 380.0, 1400.0, t_edificio_p.GLindex, 100.0,100.0);
			}
		glPopMatrix();
		for (byte i = 0; i < N_PISOS; i++)
		{
			// Losa
			glPushMatrix();
				glTranslatef(0.0, -10.0, 0.0);
				cf_objeto.losa(2000.0, 2000.0, piso_lab.GLindex, t_concreto1.GLindex);
			glPopMatrix();
			
			//Techo
			glPushMatrix();
				glTranslatef(0.0, 369.0, 0.0);
				glRotatef(90.0, 1.0, 0.0, 0.0);
				cf_objeto.plano(2000.0, 2000.0, t_techo.GLindex);
			glPopMatrix();

			// Muros exteriores
			//dibuja3prismas(2000.0, 380.0, 2000.0, t_edificio_p.GLindex, 100.0, 100.0);
			// Muro sólido
			glPushMatrix();
				glTranslatef(992.5, 0.0, 0.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				cf_objeto.muro_1text(2000.0, 380.0, t_edificio_p.GLindex, 100.0, 100.0);
			glPopMatrix();

			//Muros ventanas cubiculos
			glPushMatrix();
				glTranslatef(0.0, 0.0, 992.5);
				cf_objeto.muro_1text(1985.0, 50.0, t_edificio_p.GLindex, 100.0, 100.0); //abajo
				glTranslatef(0.0, 330.0, 0.0);
				cf_objeto.muro_1text(1985.0, 50.0, t_edificio_p.GLindex, 100.0, 100.0); //arriba
				glTranslatef(900.0, -280.0, 0.0);
				cf_objeto.muro_1text(170.0, 280.0, t_edificio_p.GLindex, 100.0, 100.0); //medio
			glPopMatrix();

			// Muros ventanas salones
			glPushMatrix();
				glTranslatef(0.0, 0.0, -992.5);
				cf_objeto.muro_1text(1985.0, 50.0, t_edificio_p.GLindex, 100.0, 100.0); //abajo
				
				glTranslatef(0.0, 50.0, 0.0);
				glPushMatrix();
					glTranslatef(-700.0, 0.0, 0.0);
					cf_objeto.muro_1text(600.0, 280.0, t_edificio_p.GLindex, 100.0, 100.0); //medio
				glPopMatrix();
				glPushMatrix();
					glTranslatef(900.0, 0.0, 0.0);
					cf_objeto.muro_1text(200.0, 280.0, t_edificio_p.GLindex, 100.0, 100.0); //medio
				glPopMatrix();
				glTranslatef(0.0, 280.0, 0.0);
				cf_objeto.muro_1text(1985.0, 50.0, t_edificio_p.GLindex, 100.0, 100.0); //arriba
			glPopMatrix();	

			// Muro parcial exterior
			glPushMatrix();
				glTranslatef(-992.5, 0.0, -700.0);
				glRotatef(90.0, 0.0, -1.0, 0.0);
				cf_objeto.muro_1text(600.0, 380.0, t_edificio_p.GLindex, 100.0, 100.0);
			glPopMatrix();

			if (es_laboratorio) dibuja_mob_lab();
			else dibuja_mob_salon();

			// Muro intermedio salones
			glPushMatrix();
				glTranslatef(100.0, 0.0, 200.0);
				cf_objeto.muro(1400.0, 380.0, ladrilloB.GLindex, t_concreto1.GLindex);
				glTranslatef(0.0, 250.0, 8.5);
				if (es_laboratorio) placa_lab(); //placa :D
			glPopMatrix();

			// Muro intermedio cubiculos
			glPushMatrix();
				glTranslatef(0.0, 0.0, 600.0);
				cf_objeto.muro(1975.0, 380.0, ladrilloB.GLindex, t_concreto1.GLindex);
			glPopMatrix();

			// Muro intermedio cubiculos-lobby
			glPushMatrix();
				glTranslatef(-992.5, 0.0, 800.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				cf_objeto.muro_1text(400.0, 380.0, t_edificio_p.GLindex, 100.0,100.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-800.0, 0.0, 992.5);
				cf_objeto.muro_1text(370.0, 380.0, t_edificio_p.GLindex, 100.0,100.0);
			glPopMatrix();

			// Muro intermedio escaleras
			glPushMatrix();
				glTranslatef(-600.0, 0.0, -400.0);
				glRotatef(90.0, 0.0, -1.0, 0.0);
				cf_objeto.muro(1190.0, 380.0, ladrilloB.GLindex, t_concreto1.GLindex);
			glPopMatrix();
			//Nos movemos al siguiente piso
			glTranslatef(0.0, 380.0, 0.0);
		}
		// Techo edificio este
		glPushMatrix();
			dibuja4prismas(2000.0, 80.0, 2000.0, t_edificio_p.GLindex, 100.0,100.0);
			cf_objeto.losa(1990.0, 1990.0, t_edificio_p.GLindex, t_concreto1.GLindex);
		glPopMatrix();
	glPopMatrix();

	
}

void dibuja_base_edificio() {
	glPushMatrix();
		glTranslatef(0.0, 50.0, 0.0);
		cf_objeto.plano_text(5000.0, 100.0, t_concreto_cafe.GLindex, 100.0);
			
		glPushMatrix();
			glTranslatef(2500.0, 0.0, -1000.0);
			glRotatef(90.0, 0.0, 1.0,0.0);
			cf_objeto.plano_text(2000.0, 100.0, t_concreto_cafe.GLindex, 100.0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-2500.0, 0.0, -1000.0);
			glRotatef(90.0, 0.0, 1.0,0.0);
			cf_objeto.plano_text(2000.0, 100.0, t_concreto_cafe.GLindex, 100.0);
		glPopMatrix();

		glTranslatef(0.0, 0.0, -2000.0);
		cf_objeto.plano_text(5000.0, 100.0, t_concreto_cafe.GLindex, 100.0);
	glPopMatrix();
}

void dibujar_jardineras() {
	//------------------------ JARDINERA ESTE ----------------
	glPushMatrix();
		glTranslatef(-3900.0, 0.0, -600.0);
		jardinera_trapecio();
	glPopMatrix();

	//------------------------ JARDINERA OESTE ----------------
	glPushMatrix();
		glTranslatef(3900.0, 0.0, -600.0);
		glScalef(-1.0, 1.0, 1.0);
		jardinera_trapecio();
	glPopMatrix();	

	//------------ JARDINERAS SEMIELIPTICAS FRENTE ------------//
	glBindTexture(GL_TEXTURE_2D, 0);
	glPushMatrix();
		glTranslatef(700.0, 0.0, 0.0);
		cf_objeto.cil_semi_eliptico_2_colores(1800.0, 1200.0, 100.0, 90.0, 30.0, cafe, verde_pasto);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-700.0, 0.0, 0.0);
		glScalef(-1.0, 1.0, 1.0);
		cf_objeto.cil_semi_eliptico_2_colores(1800.0, 1200.0, 100.0, 90.0, 30.0, cafe, verde_pasto);
	glPopMatrix();
	// -------------------------------------------- //

	// Jardineras parte posterior
	glPushMatrix();
		glTranslatef(-900.0, 0.0, -3400.0);
		jardinera_parte_posterior();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(900.0, 0.0, -3400.0);
		glScalef(-1.0, 1.0, 1.0);
		jardinera_parte_posterior();
	glPopMatrix();

	// Jardineras frente
	glPushMatrix();
		glTranslatef(-500.0, 0.0, 3000.0);			
		jardinera_frente();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(500.0, 0.0, 3000.0);	
		glScalef(-1.0, 1.0, 1.0);
		jardinera_frente();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(3900.0, 0.0, 0.0);
		jardinera_pino();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-3900.0, 0.0, 0.0);
		glScalef(-1.0, 1.0, 1.0);
		jardinera_pino();
	glPopMatrix();

}

void ventanas_salones() {
	//Ventanas salones
	glPushMatrix();
		for (size_t i = 0; i < N_PISOS; i++)
		{
			glPushMatrix();
			for (size_t j = 0; j < 4; j++)
			{
				cf_objeto.plano(300, 280.0, t_ventana.GLindex);
				glTranslatef(300, 0.0, 0.0);
			}
			glPopMatrix();
			glTranslatef(0.0, 380.0, 0.0);
		}			
	glPopMatrix();
}

void ventanas_cubiculos() {
	//Ventanas salones
	glPushMatrix();
		for (size_t i = 0; i < N_PISOS; i++)
		{
			glPushMatrix();
			for (size_t j = 0; j < 5; j++)
			{
				cf_objeto.plano(300, 280.0, t_ventana.GLindex);
				glTranslatef(300, 0.0, 0.0);
			}
			glPopMatrix();
			glTranslatef(0.0, 380.0, 0.0);
		}			
	glPopMatrix();
}

void objetos_translucidos() {
	//----------------- VENTANAS --------------------------//
	glEnable (GL_BLEND); 
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//Ventanas entrada principal
		glPushMatrix();
			glTranslatef(0.0, 330.0, 900.0);
			glRotatef(90.0, 1.0, 0.0, 0.0);
			cf_objeto.plano(400, 600, t_ventana.GLindex);
			glPushMatrix();
				glTranslatef(350.0, 0.0, 0.0);
				cf_objeto.plano(300, 600, t_ventana.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-350.0, 0.0, 0.0);
				cf_objeto.plano(300, 600, t_ventana.GLindex);
			glPopMatrix();
		glPopMatrix();

		// entrada principal - ventanas frontales
		glPushMatrix();
			glTranslatef(-350.0, 225.0, 1200.0);
			cf_objeto.plano(300, 210, t_ventana.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(350.0, 225.0, 1200.0);
			cf_objeto.plano(300, 210, t_ventana.GLindex);
		glPopMatrix();

		// entrada principal - ventanas superiores inclinadas
		glPushMatrix();
			glTranslatef(600.0, 365.0, 300.0);
			glRotatef(96.65, 1.0, 0.0, 0.0);
			cf_objeto.plano(200, 604.1, t_ventana.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-600.0, 365.0, 300.0);
			glRotatef(96.65, 1.0, 0.0, 0.0);
			cf_objeto.plano(200, 604.1, t_ventana.GLindex); //ventana extremo
		glPopMatrix();
		glPushMatrix();
			glTranslatef(350.0, 365.0, 300.0);
			glRotatef(96.65, 1.0, 0.0, 0.0);
			cf_objeto.plano(300, 604.1, t_ventana.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-350.0, 365.0, 300.0);
			glRotatef(96.65, 1.0, 0.0, 0.0);
			cf_objeto.plano(300, 604.1, t_ventana.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, 365.0, 300.0);
			glRotatef(96.65, 1.0, 0.0, 0.0);
			cf_objeto.plano(400, 604.1, t_ventana.GLindex);
		glPopMatrix();

		// entrada principal - ventanas laterales
		glPushMatrix();
			glTranslatef(700.0, 100.0, 300.0);
			ventana_inclinada();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-700.0, 100.0, 300.0);
			ventana_inclinada();
		glPopMatrix();

		//puerta principal
		glPushMatrix();
			glTranslatef(0.0, 165.0, 1200.0);
			cf_objeto.plano(400, 330.0, t_puerta_principal.GLindex);
		glPopMatrix();

		//Ventanas salones y lab
		glPushMatrix();
			glTranslatef(1250.0, 290.0, -1992.5);
			ventanas_salones();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-1250.0, 290.0, -1992.5);
			glScalef(-1.0, 1.0, 1.0);
			ventanas_salones();
		glPopMatrix();

		//Ventanas cubiculos
		glPushMatrix();
			glTranslatef(1035.0, 290.0, -7.5);
			ventanas_cubiculos();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-1035.0, 290.0, -7.5);
			glScalef(-1.0, 1.0, 1.0);
			ventanas_cubiculos();
		glPopMatrix();

	glDisable (GL_BLEND); 
	glBindTexture(GL_TEXTURE_2D, 0);
}

void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	/*glShadeModel (GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);	
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable ( GL_COLOR_MATERIAL );
*/
	//glDisable(GL_LIGHTING);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	cargar_texturas();
	objCamera.Position_Camera(POS_IX, POS_IY, POS_IZ, 
								POS_IX, POS_IY, POS_IZ-500, 
								0.0, 1.0, 0.0);

	// Varibles para los keyframes
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = FposX[i];
		KeyFrame[i].posY = posY;
		KeyFrame[i].posZ = FposZ[i];
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;
		KeyFrame[i].rotRodIzq = FrotRodIzq[i];
		KeyFrame[i].rotRodDer = FrotRodDer[i];
		KeyFrame[i].rotManIzqZ = FrotManIzqZ[i];
		KeyFrame[i].rotManDerZ = FrotManDerZ[i];
		KeyFrame[i].rotManIzqY = FrotManIzqY[i];
		KeyFrame[i].rotManDerY = FrotManDerY[i];
		KeyFrame[i].rotPechoX = FrotPechoX[i];
		KeyFrame[i].rotPechoY = FrotPechoY[i];
		KeyFrame[i].incRotMDZ = 0;
		KeyFrame[i].incRotMIZ = 0;
		KeyFrame[i].incRotMDY = 0;
		KeyFrame[i].incRotMIY = 0;
		KeyFrame[i].incRotRD = 0;
		KeyFrame[i].incRotRI = 0;
		KeyFrame[i].incRotPX = 0;
		KeyFrame[i].incRotPY = 0;
		KeyFrame[i].giroPersonaje = FgiroPersonaje[i];
		KeyFrame[i].giroPersonajeInc = 0;
		FrameIndex++;
	}
	/////////////////////////////////////////////////////////////////////

}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
		
	glPushMatrix();
		glRotatef(g_lookupdown,1.0f,0,0);
		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
		glPushMatrix();		
			glPushMatrix(); //Creamos cielo
				//glDisable(GL_LIGHTING);
				glTranslatef(0,60,0);
				sky.skybox_anim(10000.0, 10000.0, 10000.0, cielo, t_sky.GLindex);
				//glEnable(GL_LIGHTING);
			glPopMatrix();
		glPopMatrix();

		//---------------------------- Ejes ------------------------------
		glPushMatrix();			
			glLineWidth(5.0);
			glBegin(GL_LINES);
				//x
				glColor3f(1.0, 0.0, 0.0);
				glVertex3f(0.0, 0.0, 0.0);
				glVertex3f(10000.0, 0.0, 0.0);
				//y
				glColor3f(0.0, 1.0, 0.0);
				glVertex3f(0.0, 0.0, 0.0);
				glVertex3f(0.0, 10000.0, 0.0);
				//z
				glColor3f(0.0, 0.0, 1.0);
				glVertex3f(0.0, 0.0, 0.0);
				glVertex3f(0.0, 0.0, 10000.0);
			glEnd();
		glPopMatrix();
		glColor3f(1.0, 1.0, 1.0);

			//Creacion del personaje de los keyframes
/////////////////////////////////////////////////////////////////////
		glPushMatrix();
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHTING);
			glEnable(GL_COLOR_MATERIAL);
			glColor3f(1, 1, 1);
			glTranslatef(posX, posY, posZ);
			glRotatef(giroPersonaje, 0, 1, 0);
			glScalef(20.0, 45.0, 20.0);
			Personaje();
			glDisable(GL_COLOR_MATERIAL);
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
		glPopMatrix();
		/////////////////////////////////////////////////////////////////////

		// ------------------ JARDINERAS ----------------//
		dibujar_jardineras();		

		// --------- BASE 1m EDIFICIO ------------------ //
		dibuja_base_edificio();		

		//--------------------- EDIFICIO ESTE ------------------//
		glPushMatrix();
			glTranslatef(1500.0, 100.0, -1000.0);
			dibuja_edificio_p(true);
		glPopMatrix();

		//--------------------- EDIFICIO OESTE ------------------//
		glPushMatrix();
			glTranslatef(-1500.0, 100.0, -1000.0);
			glScalef(-1.0, 1.0, 1.0);
			dibuja_edificio_p(false);
		glPopMatrix();

		//-------------------------- LOBBY PRINCIPAL  -------------------------------//
		lobby_principal(); // dibuja toda la parte central del edificio
		
		//----------------- PISO EXTERIOR (92m x 77m) -----------------------------------------//
		glPushMatrix();
			glTranslatef(0.0, -10.0, 0.0);
			glRotatef(90.0, 1.0, 0.0, 0.0);
			cf_objeto.plano_text(9200.0, 7700.0, t_piso_ext.GLindex, 100.0);
		glPopMatrix();

		// ---------------- Escala Humana
		glPushMatrix();
			glTranslatef(0.0, 0.0, 1300.0);
			dibuja_humano();
		glPopMatrix();

		// ---------- DRON sobrevolando -----------------------------------------//
		glPushMatrix();
			glTranslatef(0.0, 0.0, 500.0);
			glRotatef(GLfloat(ang_rot_dron), 0.0, 1.0, 0.0);
			glTranslatef(500.0, 1000.0+altura_dron, 0.0);
			dron();
		glPopMatrix();

		objetos_translucidos();

		// Pruebas en el origen
		glPushMatrix();
			glTranslatef(0.0, 0.0, 2000.0);

		glPopMatrix();

	glPopMatrix();
	glutSwapBuffers ();
}

void animacion()
{
	// Set up the next timer tick (do this first)
    //glutTimerFunc(TIMERMSECS, animacion, 0);

	// Measure the elapsed time
	clock_t currTime = clock();
	//double timeSincePrevFrame = double(currTime - prevTime)/CLOCKS_PER_SEC;
	double elapsedTime = double(currTime - startTime)/CLOCKS_PER_SEC;
	
	//printf_s("%f\n", elapsedTime);

	//Condición para correr la animación de los gabinetes
	if (animaGab)
		desplaza += 0.1;

	//Condición para detener la animación de los gabinetes
	if (!animaGab || desplaza >= 5.0) {
		desplaza = 0.0;
		animaGab = false;
	}
	//Variable para mover el cielo
	cielo = elapsedTime*0.01;

	//Animación dron
	//if (anima_dron) {
	if (true) {
		ang_rot_dron = fmod((elapsedTime * 36),360);
		//altura_dron = 100.0*sin(0.05*t);
		altura_dron = 100.0*sin((PI/2)*elapsedTime);
		ang_rot_helices = fmod((elapsedTime * 1080),360);
	} //else 

	//Movimiento del personaje por keyframes
/////////////////////////////////////////////////////////////////////
	if (play)
	{
		if (i_curr_steps >= i_max_steps)
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else
			{
				i_curr_steps = 0;
				interpolation();

			}
		}
		else
		{
			posX += KeyFrame[playIndex].incX;
			posY += KeyFrame[playIndex].incY;
			posZ += KeyFrame[playIndex].incZ;

			rotRodIzq += KeyFrame[playIndex].incRotRI;
			rotRodDer += KeyFrame[playIndex].incRotRD;
			rotManIzqZ += KeyFrame[playIndex].incRotMIZ;
			rotManDerZ += KeyFrame[playIndex].incRotMDZ;
			rotManIzqY += KeyFrame[playIndex].incRotMIY;
			rotManDerY += KeyFrame[playIndex].incRotMDY;
			rotPechoX += KeyFrame[playIndex].incRotPX;
			rotPechoY += KeyFrame[playIndex].incRotPY;
			giroPersonaje += KeyFrame[playIndex].giroPersonajeInc;

			i_curr_steps++;
		}

	}
	/////////////////////////////////////////////////////////////////////


	glutPostRedisplay();
	prevTime = currTime;
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 15000.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	GLfloat dist = 2500.0;
	switch ( key ) {

		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED/*+0.2*/ );
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED/*+0.2*/));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED/*+0.4*/));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED/*+0.4*/ );
			break;

		//posicion de inicio
		case 'h':
		case 'H':	
			objCamera.Position_Camera(POS_IX, POS_IY, POS_IZ, 
								POS_IX, POS_IY, POS_IZ-500, 
								0.0, 1.0, 0.0);
			break;

		//nos posicionamos en el lab
		case 'l':
		case 'L':
			objCamera.Position_Camera(950.0,270.0,-1400.0, 
									1450.0,270.0,-1400.0, 0.0, 
									1.0, 0.0);
			break;
		
		//nos posicionamos en el salon
		case 'k':
		case 'K':
			objCamera.Position_Camera(-950.0,270.0,-1400.0, 
									-1450.0,270.0,-1400.0, 
									0.0, 1.0, 0.0);
			break;

		//proyección isométrica
		case 'j':
		case 'J':
			objCamera.Position_Camera(sqrt(3)*dist, sqrt(3)*dist, sqrt(3)*dist,
										sqrt(3)*(dist-500.0), sqrt(3)*(dist-500.0), sqrt(3)*(dist-500.0),
										-1, 1, -1);
			break;
		
		//Con 1 se reproduce la animación de los gabinetes
		case '1':
			animaGab ^= true;
			break;

		//Con 2 se reproduce la animación del dron
		case '2':
			anima_dron = !anima_dron;
			break;

		//Con 3 se reproduce la animación de por keyframes
		case '3':
			if (play == false && (FrameIndex > 1))
			{

				resetElements();
				interpolation();

				play = true;
				playIndex = 0;
				i_curr_steps = 0;
			}
			else play = false;
			break;

		// Animacion de la puerta
		case 'p':
			if (ang_rot_puerta < 90 && ang_rot_puerta >= -90) {
				ang_rot_puerta = ang_rot_puerta + 15.0;
			}			
			break;
		case 'P':
			if (ang_rot_puerta <= 90 && ang_rot_puerta > -90) {
				ang_rot_puerta = ang_rot_puerta - 15;
			}
			break;

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED+1.0);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-(CAMERASPEED+1.0));
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= ROTSPEED+0.5;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += ROTSPEED+0.5;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-ROTSPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View(ROTSPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}

void menuKeyFrame(int id)
{
	switch (id)
	{
	case 0:
		if (FrameIndex < MAX_FRAMES)
		{
		}
		break;

	case 1:
		if (play == false && FrameIndex > 1)
		{

			resetElements();
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;


	}
}

void menu(int id)
{

}

int main ( int argc, char** argv )   // Main Function
{
	int submenu;
	char soundfile[] = "02. Speaking Gently.wav";
	PlaySound((LPCSTR)soundfile, NULL, SND_FILENAME | SND_ASYNC);

	glutInit            (&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize  (1000, 768);	// Tamaño de la Ventana
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1000) / 2,
								(glutGet(GLUT_SCREEN_HEIGHT) - 768) / 2);	//Posicion de la Ventana
	glutCreateWindow    ("Proyecto Final (Test)"); // Nombre de la Ventana
	//glutFullScreen     ( );         // Full Screen
	InitGL ();						// Parametros iniciales de la aplicacion
	glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
	glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
	glutSpecialFunc     ( arrow_keys );	//Otras
	glutPostRedisplay();

	glutIdleFunc		  ( animacion );
	//glutTimerFunc(TIMERMSECS, animacion, 0);

	// Initialize the time variables
	startTime = glutGet(GLUT_ELAPSED_TIME);
	prevTime = startTime;

	submenu = glutCreateMenu(menuKeyFrame);
	glutAddMenuEntry("Guardar KeyFrame", 0);
	glutAddMenuEntry("Reproducir Animacion", 1);
	glutCreateMenu(menu);
	glutAddSubMenu("Animacion Personaje", submenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop( );  // 

	return 0;	
}
