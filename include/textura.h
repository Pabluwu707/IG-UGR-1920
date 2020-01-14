// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: textura.h

//
// #############################################################################

#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include "aux.h"



// *****************************************************************************
//
// Clase Textura (práctica 2)
//
// *****************************************************************************
class Textura {
   public:
      Textura( const std::string & string );
      void activar();
   private:
      GLuint textura_id = 0;
      unsigned char * texels;
      int tamx;
      int tamy;
};

#endif
