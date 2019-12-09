

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
using namespace std ;

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de la escena....
    // .......completar: ...
    // .....

    cubo = new Cubo(50);
    tetraedro = new Tetraedro();
    objPLY = new ObjPLY("./plys/bust.ply");
    objRev = new ObjRevolucion("./plys/peon.ply", 20, true, true);
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//*****************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 0.18, 0.15, 0.3, 0.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

  glEnable(GL_CULL_FACE); // Se habilita el Cull Face

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

void Escena::dibujar()
{
  using namespace std ;

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();

  // Ajuste e inicialización de los ejes

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
  glPointSize(10);
  glLineWidth(4);

  if (visPuntos) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

    if (cuboActivado) {
      cubo->draw(modoDibujado, GL_POINT, visAjedrez);
    }
    if (tetraedroActivado) {
      glPushMatrix();
      glScalef(1.5,1.5,1.5);
      glTranslatef(-80.0,0.0,0.0);
      tetraedro->draw(modoDibujado, GL_POINT, visAjedrez);
      glPopMatrix();
    }
    if (modeloActivado) {
      glPushMatrix();
      glTranslatef(150.0,0.0,0.0);
      glScalef(60.0,60.0,60.0);
      objPLY->draw(modoDibujado, GL_POINT, visAjedrez);
      glPopMatrix();
   }
    if (revolucionActivado) {
      glPushMatrix();
      glScalef(60.0,60.0,60.0);
      objRev->draw(modoDibujado, GL_POINT, visAjedrez);
      glPopMatrix();
   }
  }

  if (visLineas) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (cuboActivado) {
      cubo->draw(modoDibujado, GL_LINE, visAjedrez);
    }
    if (tetraedroActivado) {
      glPushMatrix();
      glScalef(1.5,1.5,1.5);
      glTranslatef(-80.0,0.0,0.0);
      tetraedro->draw(modoDibujado, GL_LINE, visAjedrez);
      glPopMatrix();
    }
    if (modeloActivado) {
      glPushMatrix();
      glTranslatef(150.0,0.0,0.0);
      glScalef(60.0,60.0,60.0);
      objPLY->draw(modoDibujado, GL_LINE, visAjedrez);
      glPopMatrix();
    }
    if (revolucionActivado) {
      glPushMatrix();
      glScalef(60.0,60.0,60.0);
      objRev->draw(modoDibujado, GL_LINE, visAjedrez);
      glPopMatrix();
   }
  }

  if (visSolido) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (cuboActivado) {
      cubo->draw(modoDibujado, GL_FILL, visAjedrez);
    }
    if (tetraedroActivado) {
      glPushMatrix();
      glScalef(1.5,1.5,1.5);
      glTranslatef(-80.0,0.0,0.0);
      tetraedro->draw(modoDibujado, GL_FILL, visAjedrez);
      glPopMatrix();
    }
    if (modeloActivado) {
      glPushMatrix();
      glTranslatef(150.0,0.0,0.0);
      glScalef(60.0,60.0,60.0);
      objPLY->draw(modoDibujado, GL_FILL, visAjedrez);
      glPopMatrix();
    }
    if (revolucionActivado) {
      glPushMatrix();
      glScalef(60.0,60.0,60.0);
      objRev->draw(modoDibujado, GL_FILL, visAjedrez);
      glPopMatrix();
   }
  }

  if (visAjedrez) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (cuboActivado) {
      cubo->draw(modoDibujado, GL_FILL, visAjedrez);
    }
    if (tetraedroActivado) {
      glPushMatrix();
      glScalef(1.5,1.5,1.5);
      glTranslatef(-80.0,0.0,0.0);
      tetraedro->draw(modoDibujado, GL_FILL, visAjedrez);
      glPopMatrix();
    }
    if (modeloActivado) {
      glPushMatrix();
      glTranslatef(150.0,0.0,0.0);
      glScalef(60.0,60.0,60.0);
      objPLY->draw(modoDibujado, GL_FILL, visAjedrez);
      glPopMatrix();
    }
  }


  /*
  glPolygonMode(GL_FRONT_AND_BACK, modoVisualizacion);
  glShadeModel(GL_FLAT);
  glPointSize(10);
  glLineWidth(1.5);

  switch (objetoVisualizado)
  {
    case 0 :
      cubo->draw(modoDibujado);
      break;
    case 1 :
      tetraedro->draw(modoDibujado);
      break;
    default :
      cout << "Error, número incorrecto." << endl;
      break;
  }
  */
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
          }
        }
        break ;
      case 'A' :
        if (modoMenu==SELVISUALIZACION) {
          cout << "Modo de visualización: Ajedrez." << endl;
          // Se activa/desactiva la visualización en modo ajedrez
          if (visAjedrez) {
            visAjedrez = false;
          } else {
            visAjedrez = true;
            visPuntos = false;
            visLineas = false;
            visSolido = false;
          }
        }
        break ;

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
        }
        break ;
      case '2' :
        if (modoMenu==SELDIBUJADO) {
          cout << "Dibujado usando: VBO." << endl;
          // Se activa la visualización usando Vertex Buffer Objects (VBOs)
          modoDibujado = 1;
        }
        break ;
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
