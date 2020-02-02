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
   cilindro = new Cilindro(0.5, 1.5, 30);
   cono = new Cono(0.5, 1.5, 20);
   esfera = new Esfera(0.4, 24);

   mesa = new Cubo(50);
   peonBlanco = new ObjRevolucion("./plys/peon.ply", 20, true);
   peonNegro = new ObjRevolucion("./plys/peon.ply", 20, true);

   objmettaton = new Mettaton();

   cuadro = new Cuadro(50, "./texturas/fondo.jpg");


   florMario = new ObjPLY("./plys/flor.ply");
   monedaMario1 = new ObjPLY("./plys/moneda.ply");
   monedaMario2 = new ObjPLY("./plys/moneda.ply");
   monedaMario3 = new ObjPLY("./plys/moneda.ply");
   nubeMario = new ObjPLY("./plys/nube.ply");

   // Crear materiales a usar
   Material oro ({0.24725, 0.1995, 0.0745, 1}, {0.75164, 0.60648, 0.22648, 1}, {0.628281, 0.555802, 0.366065, 1}, 0.4*128.0f);
   Material plata({0.19225, 0.19225, 0.19225, 1}, {0.50754, 0.50754, 0.50754, 1}, {0.508273, 0.508273, 0.508273, 1}, 0.4*128.0f);
   Material bronce({0.2125, 0.1275, 0.054, 1}, {0.714, 0.04284, 0.18144, 1}, {0.393548, 0.271906, 0.166721, 1}, 0.2*128.0f);
   Material rubi({0.61424, 0.04136, 0.04136, 1}, {0.61424, 0.04136, 0.04136, 1}, {0.727811, 0.626959, 0.626959, 1}, 0.7*128.0f);
   Material turquesa({0.1, 0.18725, 0.1745, 1}, {0.396, 0.074151, 0.69102, 1}, {0.297254, 0.30829, 0.306678, 1}, 0.1*128.0f);
   Material plasticoVerde({0.0, 0.0, 0.0, 1}, {0.1, 0.35, 0.1, 1}, {0.45, 0.55, 0.45, 1}, 0.25*128.0f);
   Material plasticoCian({0.0, 0.1, 0.06, 1}, {0.0, 0.50980392, 0.50980392, 1}, {0.50196078, 0.50196078, 0.50196078, 1}, 0.25*128.0f);
   Material plasticoRojo({0.0,0.0,0.0,1.0},{0.5,0.0,0.0,1.0},{0.7,0.6,0.6,1.0},128.0*0.25);

   // Aplicar materiales en objetos de la escena
   cilindro->establecerMaterial(plasticoCian);
   esfera->establecerMaterial(plasticoRojo);
   cubo->establecerMaterial(rubi);
   tetraedro->establecerMaterial(plata);
   objRev->establecerMaterial(oro);
   objPLY->establecerMaterial(plasticoVerde);
   cono->establecerMaterial(plasticoVerde);
   mesa->establecerMaterial(bronce);
   peonNegro->establecerMaterial(rubi);
   peonBlanco->establecerMaterial(turquesa);
   florMario->establecerMaterial(rubi);
   monedaMario1->establecerMaterial(oro);
   monedaMario2->establecerMaterial(oro);
   monedaMario3->establecerMaterial(oro);


   // Crear luces de la escena
   luz0 = new LuzPosicional({0, 500, 0}, GL_LIGHT0, {0,0,0,1}, {1,1,1,1}, {1,1,1,1});
   luz1 = new LuzDireccional({0,0,1}, GL_LIGHT1, {0,0,0,1}, {1,1,1,1}, {1,1,1,1});
   luzPuntual = new LuzPosicional({250, 100, 0}, GL_LIGHT2, {0,0,0,1}, {1,1,1,1}, {1,1,1,1});

   cout << endl << "--- MENÚ PRINCIPAL ---" << endl
        << "Opciones disponibles: " << endl
        << "\t [O] Menú: Selección de objetos" << endl
        << "\t [V] Menú: Modos de visualización de objetos" << endl
        << "\t [D] Menú: Modo dibujado" << endl << endl

        << "\t [A] Activar/Desactivar animaciones automáticas" << endl
        << "\t [+] Aumentar velocidad de animación automática" << endl
        << "\t [-] Disminuir velocidad de animación automática" << endl
        << "\t [M] Menú: Grados de libertad del modelo jerárquico" << endl << endl

        << "\t [9] Activar/desactivar tapas de objetos por revolución" << endl << endl

        << "\t [Q] Salir y cerrar el programa" << endl;
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
      glPushMatrix();
         glRotatef(giroLuz, 0, 1, 0);
         luzPuntual->activar();
      glPopMatrix();
      dibujarUsandoVisualizacion(GL_FILL, false);
   }
}



void Escena::dibujarUsandoVisualizacion(GLenum modoVisualizacionAUsar, bool visAjedrez) {
   if (cuboActivado) {
      glPushMatrix();
      glTranslatef(70.0,0.0,-90.0);
      cubo->draw(modoDibujado, modoVisualizacionAUsar, visAjedrez);
      glPopMatrix();
   }
   if (tetraedroActivado) {
      glPushMatrix();
      glTranslatef(-220.0,0.0,-40.0);
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
      glTranslatef(0.0,70.0,-150.0);
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
      glTranslatef(-220.0,0.0,-150.0);
      glScalef(60.0,60.0,60.0);
      cono->draw(modoDibujado, modoVisualizacionAUsar, visAjedrez);
      glPopMatrix();
   }
   if(esferaActivado) {
      glPushMatrix();
      glTranslatef(150.0,30.0,-120.0);
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
   if (objmettatonActivado) {
      glPushMatrix();
      glScalef(12.0,12.0,12.0);
      glRotatef(180.0,0,1,0);
      glTranslatef(-3,5.8,5.0);
      objmettaton->draw(modoDibujado, modoVisualizacionAUsar, visAjedrez);
      glPopMatrix();
   }
   if (cuadroActivado) {
      glPushMatrix();
      glScalef(50.0,50.0,50.0);
      glTranslatef(-25.0,-20.0,-20.0);
      cuadro->draw(modoDibujado, modoVisualizacionAUsar, visAjedrez);
      glPopMatrix();
   }
   if (objetosMarioActivado) {
      glPushMatrix();
      glScalef(4.0,4.0,4.0);
      glTranslatef(10.0,7.0,20.0);
      glRotatef(90.0,1,0,0);
      glRotatef(90.0,0,0,1);
      glRotatef(giroMoneda,0,0,1);
      monedaMario1->draw(modoDibujado, modoVisualizacionAUsar, visAjedrez);
      glPopMatrix();

      glPushMatrix();
      glScalef(4.0,4.0,4.0);
      glTranslatef(23.0,7.0,20.0);
      glRotatef(90.0,1,0,0);
      glRotatef(90.0,0,0,1);
      glRotatef(giroMoneda,0,0,1);
      monedaMario2->draw(modoDibujado, modoVisualizacionAUsar, visAjedrez);
      glPopMatrix();

      glPushMatrix();
      glScalef(4.0,4.0,4.0);
      glTranslatef(36.0,7.0,20.0);
      glRotatef(90.0,1,0,0);
      glRotatef(90.0,0,0,1);
      glRotatef(giroMoneda,0,0,1);
      monedaMario3->draw(modoDibujado, modoVisualizacionAUsar, visAjedrez);
      glPopMatrix();


      glPushMatrix();
      glScalef(5.0,5.0,5.0);
      glTranslatef(-15.0,0.0,3.0);
      glRotatef(30.0,0,1,0);
      glRotatef(270.0,1,0,0);
      florMario->draw(modoDibujado, modoVisualizacionAUsar, visAjedrez);
      glPopMatrix();

      glPushMatrix();
      glScalef(30.0,30.0,30.0);
      glTranslatef(-5.0,8.0,-5.0);
      nubeMario->draw(modoDibujado, modoVisualizacionAUsar, visAjedrez);
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
   cout << endl << endl << endl << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu == VARALFA || modoMenu == VARBETA) {
            modoMenu = SELILUMINACION;
         } else if (modoMenu == SELILUMINACION) {
            modoMenu = SELVISUALIZACION;
         } else if (modoMenu!=NADA)
          modoMenu=NADA;
        else {
          salir=true ;
        }
        break ;

      case '9' :
         if (modoMenu == NADA) {
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
         }
         break ;


      // ----------------------------------------------

      case 'O' :
         if (modoMenu == NADA) {
            cout << "-- Modo: Selección de objeto --" << endl;
            // ESTAMOS EN MODO SELECCION DE OBJETO
            modoMenu=SELOBJETO;
            break ;
         }

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

      case 'R' :
         if (modoMenu==SELOBJETO) {
            // Se visualiza/oculta el Objeto Revolución
            if (revolucionActivado) {
               cout << "Desactivando: Objeto Revolución." << endl;
               revolucionActivado = false;
            } else {
               cout << "Activando: Objeto Revolución." << endl;
               revolucionActivado = true;
            }
         }
         break ;

      case 'E' :
         if (modoMenu == SELOBJETO) {
            // Se visualiza/oculta la Esfera
            if (esferaActivado) {
               cout << "Desactivando: Esfera." << endl;
               esferaActivado = false;
            } else {
               cout << "Activando: Esfera." << endl;
               esferaActivado = true;
            }
         }
         break;

      // ----------------------------------------------

      case 'V' :
         if (modoMenu == NADA ) {
            cout << "-- Modo: Selección de modo de visualización --" << endl;
            // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
            modoMenu=SELVISUALIZACION;
         }
         break ;
      case 'P' :
         if (modoMenu == SELOBJETO) {
            // Se visualiza/oculta el Tetraedro
            if (modeloActivado) {
               cout << "Desactivando: Modelo PLY." << endl;
               modeloActivado = false;
            } else {
               cout << "Activando: Modelo PLY." << endl;
               modeloActivado = true;
            }
         } else if (modoMenu == SELILUMINACION) {
            if (luzPuntualEnMovimiento) {
               cout << "Desactivando movimiento de Luz 2" << endl;
               luzPuntualEnMovimiento = false;
            } else {
               cout << "Activando movimiento de Luz 2" << endl;
               luzPuntualEnMovimiento = true;
            }
         } else if (modoMenu==SELVISUALIZACION) {
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
         if (modoMenu == NADA) {
            if (animacionesAutomaticas == true){
               cout << "-- Animaciones automáticas desactivadas --" << endl;
               animacionesAutomaticas = false;
               velAnimacionAutomatica = 0;
            } else {
               cout << "-- Animaciones automáticas activadas --" << endl;
               animacionesAutomaticas = true;
            }
         } else if (modoMenu == SELOBJETO) {
            // Se visualiza/oculta el Cono
            if (conoActivado) {
             cout << "Desactivando: Cono." << endl;
             conoActivado = false;
            } else {
             cout << "Activando: Cono." << endl;
             conoActivado = true;
            }
         } else if (modoMenu == SELVISUALIZACION) {
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
         } else if (modoMenu == SELILUMINACION) {
             cout << "Modo Variación de Ángulo Alfa" << endl;
             modoMenu=VARALFA;
         }
         break ;
      case 'I' :
         if (modoMenu==SELOBJETO) {
            // Se visualiza/oculta el Tetraedro
            if (cilindroActivado) {
               cout << "Desactivando: Cilindro." << endl;
               cilindroActivado = false;
            } else {
               cout << "Activando: Cilindro." << endl;
               cilindroActivado = true;
            }
         } else if (modoMenu == SELVISUALIZACION) {
            // Se activa/desactiva la visualización en modo luces
            if (visLuces) {
               cout << "Desactivando modo de visualización de luces" << endl;
               visLuces = false;
            } else {
               cout << "Modo de visualización: Luces." << endl;
               // ESTAMOS EN MODO SELECCION DE LUCES
               modoMenu=SELILUMINACION;

               visLuces = true;
               visAjedrez = false;
               visPuntos = false;
               visLineas = false;
               visSolido = false;
            }
         }
         break ;

      case '0':
         if (modoMenu == GRADOSLIBERTAD) {
            cout << "Grado de libertad elegido: Rotación de rueda." << endl;
            gradoLibertadElegido = 0;
         } else if (modoMenu == SELILUMINACION){
            if (!luz0->getActivada()) {
               luz0->encender();
            } else{
               luz0->apagar();
            }
         }
         break;

      case 'M':
         if (modoMenu == NADA) {
            cout << "-- Animaciones automáticas desactivadas --" << endl;
            cout << "-- Modo: Movimiento manual de grados de libertad --" << endl;
            modoMenu = GRADOSLIBERTAD;
            animacionGradoLibertad = true;
            animacionesAutomaticas = false;
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
       } else if (modoMenu == GRADOSLIBERTAD) {
          cout << "Grado de libertad elegido: Rotación de mano." << endl;
          gradoLibertadElegido = 1;
       } else if (modoMenu == SELILUMINACION){
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
       } else if (modoMenu == GRADOSLIBERTAD) {
          cout << "Grado de libertad elegido: Traslación de brazos + manos." << endl;
          gradoLibertadElegido = 2;
       } else if (modoMenu == SELILUMINACION){
           if (!luzPuntual->getActivada()) {
              luzPuntual->encender();
           } else {
              luzPuntual->apagar();
           }
        }
        break ;
      // ----------------------------------------------
      case 'B' :
         if (modoMenu == SELILUMINACION) {
            cout << "Modo Variación de Ángulo Beta" << endl;
            modoMenu=VARBETA;
         }
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


      // ----------------------------------------------

      case '3':
         if (modoMenu == GRADOSLIBERTAD) {
            cout << "Grado de libertad elegido: Traslación de cuerpos más brazos." << endl;
            gradoLibertadElegido = 3;
         }
         break;

      case '4':
         if (modoMenu == GRADOSLIBERTAD) {
            cout << "Grado de libertad elegido: Rotación de personaje completo." << endl;
            gradoLibertadElegido = 4;
         }
         break;

      case '+' :
         if (modoMenu == NADA) {
            velAnimacionAutomatica += 0.2;
         } else if (modoMenu == GRADOSLIBERTAD){
            velGradoLibertad += 0.2;
         }
         break ;

      case '-' :
         if (modoMenu == NADA) {
            velAnimacionAutomatica -= 0.2;
         } else if (modoMenu == GRADOSLIBERTAD){
            velGradoLibertad -= 0.2;
         }
         break ;
   }

   cout << endl;

   switch(modoMenu){
      case NADA:
         cout << "--- MENÚ PRINCIPAL ---" << endl
              << "Opciones disponibles: " << endl
              << "\t [O] Menú: Selección de objetos" << endl
              << "\t [V] Menú: Modos de visualización de objetos" << endl
              << "\t [D] Menú: Modo dibujado" << endl << endl

              << "\t [A] Activar/Desactivar animaciones automáticas" << endl
              << "\t [+] Aumentar velocidad de animación automática" << endl
              << "\t [-] Disminuir velocidad de animación automática" << endl
              << "\t [M] Menú: Grados de libertad del modelo jerárquico" << endl << endl

              << "\t [9] Activar/desactivar tapas de objetos por revolución" << endl << endl

              << "\t [Q] Salir y cerrar el programa" << endl;

         break;

      case SELOBJETO:
         cout << "--- MENU: Selección de objetos ---" << endl
              << "Opciones: " << endl
              << "\t [C] Mostrar/ocultar cubo" << endl
              << "\t [T] Mostrar/ocultar tetraedro" << endl
              << "\t [A] Mostrar/ocultar cono" << endl
              << "\t [E] Mostrar/ocultar esfera" << endl
              << "\t [I] Mostrar/ocultar cilindro" << endl
              << "\t [P] Mostrar/ocultar objeto PLY" << endl
              << "\t [R] Mostrar/ocultar objeto por revolucion" << endl
              << "\t [Q] Salir del menu" << endl;
         break;

      case SELVISUALIZACION:
         cout << "--- MENU: Selección de modo de visualización ---" << endl
              << "Modos de visualización disponibles:" << endl
              << "\t [P] Activar/desactivar: Visualización Puntos" << endl
              << "\t [L] Activar/desactivar: Visualización Líneas" << endl
              << "\t [S] Activar/desactivar: Visualización Solido" << endl
              << "\t [A] Activar/desactivar: Visualización Ajedrez" << endl
              << "\t [I] Activar el Modo Iluminación" << endl
              << "\t [Q] Salir del modo Visualización y volver al Menú Principal" << endl;
         break;

      case SELILUMINACION:
         cout << "--- MENU: Modo Iluminación ---" << endl
              << "Luces disponibles:" << endl
              << "\t [0] Activar/desactivar Luz 0: Posicional" << endl
              << "\t [1] Activar/desactivar Luz 1: Direccional" << endl
              << "\t [2] Activar/desactivar Luz 2: Posicional Animada" << endl << endl
              << "Opciones de luces:" << endl
              << "\t [A] Variar angulo Alfa de Luz direccional" << endl
              << "\t [B] Variar angulo Beta de Luz direccional" << endl
              << "\t [P] Activar/desactivar animación de luz puntual" << endl
              << "\t [Q] Salir del Modo Iluminación y volver a Selección de Modo de Visualización" << endl;
          break;

      case SELDIBUJADO:
         cout << "--- MENU: Selección de modo de dibujado ---" << endl
              << "Opciones disponibles: " << endl
              << "\t [1] Dibujado inmediato" << endl
              << "\t [2] Dibujado diferido (VBO)" << endl
              << "\t [Q] Salir y volver al menú principal" << endl;

         break;


     case VARALFA:
       cout << "--- MENU: Modo Iluminación - Variar ángulo Alfa (luz direccional) ---" << endl
            << "Opciones disponibles: " << endl
            << "\t [<] Disminuir ángulo alfa" << endl
            << "\t [>] Aumentar ángulo alfa" << endl
            << "\t [B] Variar ángulo Beta" << endl
            << "\t [Q] Salir del Modo Variar angulo Alfa y volver a Modo Iluminación" << endl;
       break;

      case VARBETA:
       cout << "--- MENU: Modo Iluminación - Variar ángulo Beta (luz direccional) ---" << endl
            << "Opciones disponibles: " << endl
            << "\t [<] Disminuir ángulo beta" << endl
            << "\t [>] Aumentar ángulo beta" << endl
            << "\t [A] Variar ángulo Alfa" << endl
            << "\t [Q] Salir del Modo Variar angulo Beta y volver a Modo Iluminación" << endl;
       break;

      case GRADOSLIBERTAD:
         cout << "--- MENU: Selección de grados de libertad ---" << endl
              << "Elige un grado de libertad a modificar:" << endl
              << "\t [0] Grado de libertad 0: Giro de rueda" << endl
              << "\t [1] Grado de libertad 1: Giro de mano derecha (2 frames)" << endl
              << "\t [2] Grado de libertad 2: Traslación de brazos" << endl
              << "\t [3] Grado de libertad 3: Traslación de cuerpo" << endl
              << "\t [4] Grado de libertad 4: Rotación de personaje completo" << endl << endl

              << "Opciones de modificación:" << endl
              << "\t [+] Aumentar velocidad de animación" << endl
              << "\t [-] Disminuir velocidad de animación" << endl << endl

              << "\t [Q] Volver al menú principal" << endl;
         break;
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

void Escena::animarModeloJerarquico() {
   giroMoneda += (incrementoMoneda);
   if (animacionesAutomaticas) {
      objmettaton->rotarRueda(2 + velAnimacionAutomatica);
      objmettaton->rotarMano(4 + velAnimacionAutomatica);
      objmettaton->elevarBrazos(3 + velAnimacionAutomatica);
      objmettaton->elevarCuerpoBrazos(1 + velAnimacionAutomatica);
      objmettaton->rotarPersonaje(1 + velAnimacionAutomatica);
   } else if (animacionGradoLibertad) {
      if (gradoLibertadElegido == 0) {
         objmettaton->rotarRueda(velGradoLibertad);
      } else if (gradoLibertadElegido == 1) {
         objmettaton->rotarMano(velGradoLibertad);
      } else if (gradoLibertadElegido == 2)  {
         objmettaton->elevarBrazos(velGradoLibertad);
      } else if (gradoLibertadElegido == 3)  {
         objmettaton->elevarCuerpoBrazos(velGradoLibertad);
      } else if (gradoLibertadElegido == 4)  {
         objmettaton->rotarPersonaje(velGradoLibertad * 0.3);
      }
   }
}

void Escena::animarLuces() {
   if (luzPuntualEnMovimiento) {
      giroLuz += (incrementoLuz);
   }
}
