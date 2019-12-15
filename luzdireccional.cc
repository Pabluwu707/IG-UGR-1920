#include "luzdireccional.h"
#include <math.h>

// *****************************************************************************
//
// Clase LuzDireccional
//
// *****************************************************************************


LuzDireccional::LuzDireccional(const Tupla3f & direccion, const GLenum idLuzOpenGL,
   const Tupla4f ambiente, const Tupla4f especular, const Tupla4f difuso) {
      id = idLuzOpenGL;
      colorAmbiente = ambiente;
      colorEspecular = especular;
      colorDifuso = difuso;
      posicion = {direccion(0), direccion(1), direccion(2), 0.0};

      alpha = atan ( posicion(1) / posicion(0) );
      beta = acos ( posicion(2) / ( sqrt((int)posicion(0)^2 + (int)posicion(1)^2 + (int)posicion(2)^2) ) ) ;
   } ;
