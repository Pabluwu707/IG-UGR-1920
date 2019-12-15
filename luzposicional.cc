#include "luzposicional.h"

// *****************************************************************************
//
// Clase LuzPosicional
//
// *****************************************************************************

LuzPosicional::LuzPosicional(const Tupla3f & pos, const GLenum idLuzOpenGL, const Tupla4f ambiente, const Tupla4f especular, const Tupla4f difuso) {
      id = idLuzOpenGL;
      colorAmbiente = ambiente;
      colorEspecular = especular;
      colorDifuso = difuso;
      posicion = {pos(0), pos(1), pos(2), 1};
};
