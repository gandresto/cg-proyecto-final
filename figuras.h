//#include <windows.h>  //Solo para Windows
//#include <GL/gl.h>     // The GL Header File
//#include <stdio.h>

//#include <math.h>
#include "Main.h"


class CFiguras
{
	public:

	float text_der;
	float text_izq;

	void esfera(GLfloat radio, int meridianos, int paralelos, GLuint text); //Funcíon creacion esfera
	void cilindro(float radio, float altura, int resolucion, GLuint text);	//Funcíon creacion cilindro
	void cono(float altura, float radio, int resolucion, GLuint text);		//Funcíon creacion cono
	void prisma_anun (GLuint text, GLuint text2);							//Funcíon creacion movimiento
	void prisma (float largo, float altura, float profundidad, GLuint text);
	void muro(float largo, float altura, GLuint text_ladrillos, GLuint text_concreto); //Función de creacion de un muro con dos texturas
	void muro_1text(float largo, float altura, GLuint textura, GLfloat tam_text_x, GLfloat tam_text_y);
	void plano(GLfloat largo, GLfloat alto, GLuint textura);
	void plano_text(GLfloat largo, GLfloat alto, GLuint textura, GLfloat tam_text);
	void losa(float esc_x, float esc_z, GLuint text_top, GLuint text_bot);
	void prismaGabAnima(float largo, float altura, float profundidad, float desplaza, GLuint text1, GLuint text2, GLuint text3);
	//Funcíon creacion prisma
	void prisma_text(float largo, float altura,float profundidad, GLuint textura, GLfloat tam_text_x, GLfloat tam_text_y); 
	void prisma2 (GLuint text_top, GLuint text_sides);
	void prisma_4_text(GLuint text_front, GLuint text_back, GLuint text_right, GLuint text_left, GLuint text_top, GLuint text_bot);  //Funcion creacion prisma con 6 texturas, una de para cada cara
	void skybox(float altura, float largo, float profundidad, GLuint text);	//Funcion creacion cielo
	void skybox2 (float altura, float largo, float profundidad, GLuint text);
	void skybox_anim(float altura, float largo, float profundidad, float cielo, GLuint text);	//Funcion creacion cielo
	void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos);
	void cilindro_eliptico(float a, float b,  float altura, int resolucion, GLuint text);
	void cil_semi_eliptico(float a, float b, float altura, float angulo, int resolucion, GLuint text);
	void cil_semi_eliptico_2_colores(float a, float b, float altura, float angulo, int resolucion, GLfloat * color_lados, GLfloat * color_top_bot);

};
