#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include <math.h>
using namespace std ;

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
   Front_plane       = 50.0;
   Back_plane        = 2000.0;
   Observer_distance = 5*Front_plane;
   Observer_angle_x  = 0.0 ;
   Observer_angle_y  = 0.0 ;

   ejes.changeAxisSize( 5000 );

   // Crear los objetos de la escena....
   cubo = new Cubo(50);
   tetraedro = new Tetraedro();
   objPLY = new ObjPLY("./plys/palmera.ply");
   objRev = new ObjRevolucion("./plys/peon.ply", 20, true);
   cilindro = new Cilindro(0.5, 1.5, 20);
   cono = new Cono(0.5, 1.5, 20);
   esfera = new Esfera(0.5, 12);
   mesa = new Cubo(50);
   peonBlanco = new ObjRevolucion("./plys/peon.ply", 20, true);
   peonNegro = new ObjRevolucion("./plys/peon.ply", 20, true);

   // Crear materiales a usar
   Material oro ({0.24725, 0.1995, 0.0745, 1}, {0.75164, 0.60648, 0.22648, 1}, {0.628281, 0.555802, 0.366065, 1}, 0.4*128.0f);
   Material plata({0.19225, 0.19225, 0.19225, 1}, {0.50754, 0.50754, 0.50754, 1}, {0.508273, 0.508273, 0.508273, 1}, 0.4*128.0f);
   Material bronce({0.2125, 0.1275, 0.054, 1}, {0.714, 0.04284, 0.18144, 1}, {0.393548, 0.271906, 0.166721, 1}, 0.2*128.0f);
   Material rubi({0.61424, 0.04136, 0.04136, 1}, {0.61424, 0.04136, 0.04136, 1}, {0.727811, 0.626959, 0.626959, 1}, 0.7*128.0f);
   Material turquesa({0.1, 0.18725, 0.1745, 1}, {0.396, 0.074151, 0.69102, 1}, {0.297254, 0.30829, 0.306678, 1}, 0.1*128.0f);
   Material plasticoVerde({0.0, 0.0, 0.0, 1}, {0.1, 0.35, 0.1, 1}, {0.45, 0.55, 0.45, 1}, 0.25*128.0f);
   Material plasticoCian({0.0, 0.1, 0.06, 1}, {0.0, 0.50980392, 0.50980392, 1}, {0.50196078, 0.50196078, 0.50196078, 1}, 0.25*128.0f);

   // Aplicar materiales en objetos de la escena
   cilindro->establecerMaterial(oro);
   esfera->establecerMaterial(oro);
   cubo->establecerMaterial(plata);
   tetraedro->establecerMaterial(plata);
   objPLY->establecerMaterial(plasticoVerde);
   cono->establecerMaterial(plasticoCian);
   mesa->establecerMaterial(bronce);
   peonNegro->establecerMaterial(rubi);
   peonBlanco->establecerMaterial(turquesa);


   // Crear luces de la escena
   luz0 = new LuzPosicional({0, 120, 0}, GL_LIGHT0, {0,0,0,1}, {1,1,1,1}, {1,1,1,1});
   luz1 = new LuzDireccional({0,10,0}, GL_LIGHT1, {0,0,0,1}, {1,1,1,1}, {1,1,1,1});
}

//**************************************************************************
// Inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//*****************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 0.18, 0.15, 0.3, 0.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer
   glEnable(GL_CULL_FACE); // Se habilita el Cull Face
   glEnable(GL_NORMALIZE);

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar() {
   using namespace std ;

   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
   change_observer();

   // Ajuste e inicialización de los ejes

   glDisable(GL_LIGHTING);
   glLineWidth(1);
   ejes.draw();


   // COMPLETAR
   // Dibujar los diferentes elementos de la escena
   // Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
   // y hacer
   // cubo.draw()
   // o
   // tetraedro.draw()

   // Ajustes de los modelos
   glShadeModel(GL_SMOOTH);
   glPointSize(7);
   glLineWidth(3);



   if (visPuntos) {
      glDisable(GL_LIGHTING);
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      dibujarUsandoVisualizacion(GL_POINT, visAjedrez);
   }

   if (visLineas) {
      glDisable(GL_LIGHTING);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      dibujarUsandoVisualizacion(GL_LINE, visAjedrez);
   }

   if (visSolido) {
      glDisable(GL_LIGHTING);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      dibujarUsandoVisualizacion(GL_FILL, visAjedrez);
   }

   if (visAjedrez) {
      glDisable(GL_LIGHTING);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      dibujarUsandoVisualizacion(GL_FILL, visAjedrez);
   }

   if (visLuces) {
      glEnable(GL_LIGHTING);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      luz0->activar();
      luz1->activar();
      dibujarUsandoVisualizacion(GL_FILL, false);
   }
}



void Escena::dibujarUsandoVisualizacion(GLenum modoVisualizacionAUsar, bool visAjedrez) {
   if (cuboActivado) {
      glPushMatrix();
      glTranslatef(80.0,0.0,50.0);
      cubo->draw(modoDibujado, modoVisualizacionAUsar, visAjedrez);
      glPopMatrix();
   }
    if (tetraedroActivado) {
      glPushMatrix();
      glTranslatef(-170.0,0.0,20.0);
      glScalef(1.1,1.1,1.1);
      tetraedro->draw(modoDibujado, modoVisualizacionAUsar, visAjedrez);
      glPopMatrix();
    }
    if (modeloActivado) {
      glPushMatrix();
      glTranslatef(150.0,0.0,0.0);
      glScalef(60.0,60.0,60.0);
      objPLY->draw(modoDibujado, modoVisualizacionAUsar, visAjedrez);
      glPopMatrix();
   }
    if (revolucionActivado) {
      glPushMatrix();
      glTranslatef(0.0,70.0,-90.0);
      glScalef(50.0,50.0,50.0);
      objRev->draw(modoDibujado, modoVisualizacionAUsar, visAjedrez);
      glPopMatrix();
   }
    if (cilindroActivado) {
      glPushMatrix();
      glTranslatef(-100.0,0.0,-80.0);
      glScalef(60.0,60.0,60.0);
      cilindro->draw(modoDibujado, modoVisualizacionAUsar, visAjedrez);
      glPopMatrix();
   }
    if(conoActivado) {
      glPushMatrix();
      glTranslatef(-160.0,0.0,-30.0);
      glScalef(60.0,60.0,60.0);
      cono->draw(modoDibujado, modoVisualizacionAUsar, visAjedrez);
      glPopMatrix();
   }
    if(esferaActivado) {
      glPushMatrix();
      glTranslatef(100.0,30.0,-60.0);
      glScalef(60.0,60.0,60.0);
      esfera->draw(modoDibujado, modoVisualizacionAUsar, visAjedrez);
      glPopMatrix();
   }
    if(mesaActivado) {
      glPushMatrix();
      glScalef(2.0,0.05,2.0);
      glTranslatef(-22.0,0.0,-5.0);
      mesa->draw(modoDibujado, modoVisualizacionAUsar, visAjedrez);
      glPopMatrix();
   }
    if(peonBlancoActivado) {
      glPushMatrix();
      glScalef(14.0,14.0,14.0);
      glTranslatef(-0.8,1.7,2.0);
      peonBlanco->draw(modoDibujado, modoVisualizacionAUsar, visAjedrez);
      glPopMatrix();
   }
    if(peonNegroActivado) {
      glPushMatrix();
      glScalef(14.0,14.0,14.0);
      glTranslatef(2.2,1.7,4.7);
      peonNegro->draw(modoDibujado, modoVisualizacionAUsar, visAjedrez);
      glPopMatrix();
   }
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
        if (modoMenu!=NADA)
          modoMenu=NADA;
        else {
          salir=true ;
        }
        break ;
      case '9' :
        if (tapasEscenaActivadas) {
           cilindro->tapasActivadas = false;
           cono->tapasActivadas = false;
           esfera->tapasActivadas = false;
           objRev->tapasActivadas = false;
           tapasEscenaActivadas = false;
        } else {
           cilindro->tapasActivadas = true;
           cono->tapasActivadas = true;
           esfera->tapasActivadas = true;
           objRev->tapasActivadas = true;
           tapasEscenaActivadas = true;
        }
        break ;
      /*
      case '9' :
         if (tapasEscenaActivadas) {
            cilindro.tapasActivadas = false;

        } else {
        }
      break;
      */



      // ----------------------------------------------

      case 'O' :
        cout << "-- Modo: Selección de objeto --" << endl;
        // ESTAMOS EN MODO SELECCION DE OBJETO
        modoMenu=SELOBJETO;
        break ;

      case 'C' :
        if (modoMenu==SELOBJETO) {
          // Se visualiza/oculta el Tetraedro
          objetoVisualizado = 0;
          if (cuboActivado) {
            cout << "Desactivando: Cubo." << endl;
            cuboActivado = false;
          } else {
            cout << "Activando: Cubo." << endl;
            cuboActivado = true;
          }
        }
        break ;
      case 'T' :
        if (modoMenu==SELOBJETO) {
          // Se visualiza/oculta el Tetraedro
          objetoVisualizado = 1;
          if (tetraedroActivado) {
            cout << "Desactivando: Tetraedro." << endl;
            tetraedroActivado = false;
          } else {
            cout << "Activando: Tetraedro." << endl;
            tetraedroActivado = true;
          }
        }
        break ;
      case 'M' :
        if (modoMenu==SELOBJETO) {
          // Se visualiza/oculta el Tetraedro
          if (modeloActivado) {
            cout << "Desactivando: Modelo PLY." << endl;
            modeloActivado = false;
          } else {
            cout << "Activando: Modelo PLY." << endl;
            modeloActivado = true;
          }
        }
        break ;
      case 'R' :
        if (modoMenu==SELOBJETO) {
          // Se visualiza/oculta el Tetraedro
          if (revolucionActivado) {
            cout << "Desactivando: Objeto Revolución." << endl;
            revolucionActivado = false;
          } else {
            cout << "Activando: Objeto Revolución." << endl;
            revolucionActivado = true;
          }
        }
        break ;
      case 'W' :
      if (modoMenu==SELOBJETO) {
        // Se visualiza/oculta el Tetraedro
        if (cilindroActivado) {
          cout << "Desactivando: Cilindro." << endl;
          cilindroActivado = false;
        } else {
          cout << "Activando: Cilindro." << endl;
          cilindroActivado = true;
        }
      }
      break ;

      // ----------------------------------------------

      case 'V' :
        cout << "-- Modo: Selección de modo de visualización --" << endl;
        // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
        modoMenu=SELVISUALIZACION;
        break ;

      case 'P' :
        if (modoMenu==SELVISUALIZACION) {
          cout << "Modo de visualización: Puntos." << endl;
          // Se activa/desactiva la visualización en modo puntos
          modoVisualizacion = GL_POINT;
          if (visPuntos) {
            visPuntos = false;
          } else {
            visPuntos = true;
            visAjedrez = false;
            visLuces = false;
          }
        }
        break ;
      case 'L' :
        if (modoMenu==SELVISUALIZACION) {
          cout << "Modo de visualización: Lineas." << endl;
          // Se activa/desactiva la visualización en modo líneas
          modoVisualizacion = GL_LINE;
          if (visLineas) {
            visLineas = false;
          } else {
            visLineas = true;
            visAjedrez = false;
            visLuces = false;
          }
        }
        break ;
      case 'S' :
        if (modoMenu==SELVISUALIZACION) {
          cout << "Modo de visualización: Sólido." << endl;
          // Se activa/desactiva la visualización en modo sólido (por defecto)
          modoVisualizacion = GL_FILL;
          if (visSolido) {
            visSolido = false;
          } else {
            visSolido = true;
            visAjedrez = false;
            visLuces = false;
          }
        }
        break ;
      case 'A' :
         if (visLuces == true) {
             cout << "Modo Variación de Ángulo Alfa" << endl;
             modoMenu=VARALFA;
          } else {
             cout << "Modo de visualización: Ajedrez." << endl;
             // Se activa/desactiva la visualización en modo ajedrez
             if (visAjedrez) {
               visAjedrez = false;
             } else {
                  visAjedrez = true;
                  visPuntos = false;
                  visLineas = false;
                  visSolido = false;
                  visLuces = false;
             }
          }
        break ;
      case 'I' :
        if (modoMenu==SELVISUALIZACION) {
       cout << "Modo de visualización: Luces." << endl;
         // ESTAMOS EN MODO SELECCION DE LUCES
          //modoMenu=SELILUMINACION;
          // Se activa/desactiva la visualización en modo ajedrez
          if (visLuces) {
            visLuces = false;
          } else {
            visLuces = true;
            visAjedrez = false;
            visPuntos = false;
            visLineas = false;
            visSolido = false;
          }
        }
       break ;
     case '0':
      if (visLuces == true){
         if (!luz0->getActivada()) {
            luz0->encender();
         } else{
            luz0->apagar();
         }
      }

      break;

      // ----------------------------------------------

      case 'D' :
        cout << "-- Modo: Selección de dibujado --" << endl;
        // ESTAMOS EN MODO SELECCION DE DIBUJADO
        modoMenu=SELDIBUJADO;
        break ;

      case '1' :
        if (modoMenu==SELDIBUJADO) {
          cout << "Dibujado usando: glDrawElements." << endl;
          // Se activa la visualización usando glDrawElements
          modoDibujado = 0;
       } else if (visLuces == true){
           if (!luz1->getActivada()) {
              luz1->encender();
           } else {
              luz1->apagar();
           }
        }
        break;
      case '2' :
        if (modoMenu==SELDIBUJADO) {
          cout << "Dibujado usando: VBO." << endl;
          // Se activa la visualización usando Vertex Buffer Objects (VBOs)
          modoDibujado = 1;
        }
        break ;
      // ----------------------------------------------
      case 'B' :
         cout << "Modo Variación de Ángulo Alfa" << endl;
        modoMenu=VARBETA;
        break ;
      case '<':
         if (modoMenu == VARALFA){
            luz1->variarAnguloAlpha(-2);
         } else if (modoMenu == VARBETA){
            luz1->variarAnguloBeta(-2);

         } else {
            cout << "ERROR: Opcion no valida" << endl;
         }
         break;

      case '>':
         if (modoMenu == VARALFA){
            luz1->variarAnguloAlpha(2);
         } else if (modoMenu == VARBETA){
            luz1->variarAnguloBeta(2);

         } else {
            cout << "ERROR: Opcion no valida" << endl;
         }
         break;
       // ----------------------------------------------
   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
