// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzdireccional.h
// -- declaraciones de clase LuzDireccional
//
// #############################################################################

#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

class LuzDireccional : public Luz {
   protected:
      float alpha;
      float beta;
      float r;
   public:
      // inicializar la fuente de luz
      LuzDireccional(const Tupla3f & direccion, const GLenum idLuzOpenGL,
         const Tupla4f colorAmbiente, const Tupla4f colorEspecular, const Tupla4f colorDifuso);

      // Cambiar ángulo:
      void variarAnguloAlpha(float incremento);
      void variarAnguloBeta(float incremento);
} ;

#endif
