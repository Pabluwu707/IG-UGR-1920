// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: material.h
// -- declaraciones de clase Material
//
// #############################################################################

#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "aux.h"

class Material {
   public:
      Material ();
      Material (Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float brillo);
      void aplicar();
      void setMaterial(const Material & material);
   protected:
      Tupla4f ambiente;
      Tupla4f difuso;
      Tupla4f especular;
      float brillo;
} ;

#endif
