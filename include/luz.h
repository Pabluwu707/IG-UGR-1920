// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luz.h
// -- declaraciones de clase Luz usada en LuzDireccional y LuzPosicional
//
// #############################################################################

#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

class Luz {
   public:
      void activar();
      void encender();
      void apagar();
      bool getActivada();
   protected:
      Tupla4f posicion;
      GLenum id;
      Tupla4f colorAmbiente;
      Tupla4f colorDifuso;
      Tupla4f colorEspecular;
      bool luzActivada = false;
} ;

#endif
