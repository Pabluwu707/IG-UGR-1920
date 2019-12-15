// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzposicional.h
// -- declaraciones de clase LuzPosicional
//
// #############################################################################

#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

class LuzPosicional : public Luz {
   public:
      // inicializar la fuente de luz
      LuzPosicional(const Tupla3f & posicion, const GLenum idLuzOpenGL,
         const Tupla4f colorAmbiente, const Tupla4f colorEspecular, const Tupla4f colorDifuso);

} ;

#endif
