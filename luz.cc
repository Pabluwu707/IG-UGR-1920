#include "luz.h"
using namespace std;

// *****************************************************************************
//
// Clase Luz
//
// *****************************************************************************

void Luz::activar() {
   // COnfiguración de la luz
   //if (!luzActivada) {
      glLightfv(id, GL_AMBIENT, colorAmbiente);
      glLightfv(id, GL_DIFFUSE, colorDifuso);
      glLightfv(id, GL_SPECULAR, colorEspecular);
      glLightfv(id, GL_POSITION, posicion);
   //}
}

void Luz::encender() {
   glEnable(id);
   luzActivada = true;
}

void Luz::apagar() {
   glDisable(id);
   luzActivada = false;
}

bool Luz::getActivada() {
   return luzActivada;
}
