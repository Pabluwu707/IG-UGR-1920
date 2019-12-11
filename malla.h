// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: malla.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:

   // Dibuja el objeto en modo inmediato
   void draw_ModoInmediato();

   // Dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();

   // Dibuja el objeto en modo ajedrez
   void draw_ModoAjedrez();

   // Función que redibuja el objeto
   // Está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   // o bien a 'draw_ModoAjedrez' (modo inmediato con dos listas de tríangulos)
   void draw(int modo, GLenum visualizacion, bool ajedrezActivado) ;

   protected:

   void calcular_normales() ; // Calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ;   // una terna de 3 enteros por cada cara o triángulo

   // Función que crea los VBO en la primera llamada a draw_ModoDiferido()
   GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram);

   // IDs de los objetos VBO de los vértices y los triángulos respectivamente
   int id_vbo_ver = 0 ;
   int id_vbo_tri = 0 ;
   int id_vbo_col = 0 ;

   // Vectores de colores del cubo (modo Inmediato y Diferido, y modo Ajedrez)
   std::vector<Tupla3f> c   ; // Vector de colores (modo Inmediato y Diferido)

   std::vector<Tupla3f> cSolido   ; // Vector para visualización sólida (modo Inmediato y Diferido)
   std::vector<Tupla3f> cLineas   ; // Vector para lineas (modo Inmediato y Diferido)
   std::vector<Tupla3f> cPuntos   ; // Vector para puntos (modo Inmediato y Diferido)
   std::vector<Tupla3f> cAjedrez1 ; // 1a tabla de colores (modo Ajedrez)
   std::vector<Tupla3f> cAjedrez2 ; // 2a tabla de colores (modo Ajedrez)

   // Función que llama a glDrawElements (se sobreecribe en objRevolucion)
   virtual void dibujarElementos();

   // A completar: tabla de normales de vértices (practica 3)
   std::vector<Tupla3f> normalesf ;
   std::vector<Tupla3f> normalesv ;

} ;


#endif
