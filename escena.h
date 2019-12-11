#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO} menu;
class Escena
{

   private:



 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)

       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();



   void clear_window();

   menu modoMenu=NADA;

   //Variables para los menus
   int objetoVisualizado = 0;
   GLenum modoVisualizacion = GL_FILL;
   int modoDibujado = 0;
   bool visPuntos = false, visLineas = true, visSolido = true, visAjedrez = false;
   bool cuboActivado = true, tetraedroActivado = true, modeloActivado = true, revolucionActivado = true, cilindroActivado = true, conoActivado = true, esferaActivado = true;
   bool ajedrezActivado = false;
   bool tapasEscenaActivadas = true;

   // Objetos de la escena
   Ejes ejes;
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro = nullptr ; // es importante inicializarlo a 'nullptr'
   ObjPLY * objPLY = nullptr ; // es importante inicializarlo a 'nullptr'
   ObjRevolucion * objRev = nullptr ; // es importante inicializarlo a 'nullptr'
   Cilindro * cilindro = nullptr;
   Cono * cono = nullptr;
   Esfera * esfera = nullptr;

   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

};
#endif
