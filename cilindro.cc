#include "aux.h"
#include "malla.h"
#include "cilindro.h"

Cilindro::Cilindro(float radio, float altura, int num_instancias)
{

   // Crear vector de puntos
   std::vector<Tupla3f> vector_puntos;

   // Inicializar vector de puntos
   vector_puntos.resize(2);
   vector_puntos[0] = Tupla3f (radio,0,0); // Vértice 0
   vector_puntos[1] = Tupla3f (radio,altura,0); // Vértice 1

   // Invocar el método crearMalla con el vector de puntos
   crearMalla(vector_puntos, num_instancias);

   // INICIALIZACIÓN DE COLORES
   // Inicializar colores puntos en Modo inmediato y diferido
   cPuntos.clear();
   for (int i=0; i<v.size(); i++) {
     cPuntos.push_back({0.28,0.25,0.4});
   }

   // Inicializar colores lineas en Modo inmediato y diferido
   cLineas.clear();
   for (int i=0; i<v.size(); i++) {
     cLineas.push_back({0.28,0.25,0.4});
   }

   // Inicializar colores solido para cubo en Modo inmediato y diferido
   cSolido.clear();
   for (int i=0; i<v.size(); i++) {
     cSolido.push_back({1.0,0.42,0.06});
   }

   // Inicializar colores cubo en Modo Ajedrez
   cAjedrez1.clear();
   cAjedrez2.clear();
   for (int i=0; i<v.size(); i++) {
     cAjedrez1.push_back({1.0,0.0,0.64});
     cAjedrez2.push_back({0.97,0.78,0.05});
   }
}
