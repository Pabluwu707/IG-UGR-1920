#include "luzdireccional.h"
#include <math.h>
using namespace std;

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
      r = sqrt(direccion.lengthSq());

      alpha = atan(( sqrt(pow(direccion(0),2) + pow(direccion(1),2) ) / direccion(2) ));
      beta = atan(direccion(1)/r);
   } ;

void LuzDireccional::variarAnguloAlpha(float incremento) {

      cout << "Alpha:" << alpha << "   " << posicion;

      double r2 = M_PI * incremento / 180.0;
      alpha = alpha + r2;


      posicion(0) = sin(alpha) * cos(beta) * r;
      posicion(1) = sin(alpha) * sin(beta) * r;
      posicion(2) = cos(alpha) * 1 * r;
}

void LuzDireccional::variarAnguloBeta(float incremento) {

      double r2 = M_PI * incremento / 180.0;
      beta = beta + r2;

      posicion(0) = sin(alpha) * cos(beta) * r;
      posicion(1) = sin(beta) * r;
      posicion(2) = cos(alpha) * cos(beta) * r;
}
