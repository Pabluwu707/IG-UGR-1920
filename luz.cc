#include "luz.h"
using namespace std ;

// *****************************************************************************
//
// Clase Luz
//
// *****************************************************************************

void Luz::activar() {
   // COnfiguración de la luz
   glLightfv(id, GL_AMBIENT, colorAmbiente);
   glLightfv(id, GL_DIFFUSE, colorDifuso);
   glLightfv(id, GL_SPECULAR, colorEspecular);

   glEnable(id);

   luzActivada = true;
}

void Luz::desactivar() {
   glDisable(id);
   luzActivada = false;
}
