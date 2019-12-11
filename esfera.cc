#include "aux.h"
#include "malla.h"
#include "esfera.h"
#include <math.h>

Esfera::Esfera(float radio, int num_instancias) {

   // Inicializar vector de puntos
   float angulo, x, y, z;
   for (int i=0; i <= num_instancias; i++) {
      angulo = (M_PI/num_instancias * i);
      x = (0 * cos (angulo)) + (radio * -sin (angulo));
      y = (0 * sin (angulo)) + (radio * cos (angulo));
      z = 0;
      v_perfil.push_back({x, y, z}); // Vértice i
   }

   // Invocar el método crearMalla con el vector de puntos
   crearMalla(v_perfil, num_instancias);


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
     cSolido.push_back({1.0,0.00,0.32});
   }

   // Inicializar colores cubo en Modo Ajedrez
   cAjedrez1.clear();
   cAjedrez2.clear();
   for (int i=0; i<v.size(); i++) {
     cAjedrez1.push_back({1.0,0.0,0.64});
     cAjedrez2.push_back({0.97,0.78,0.05});
   }
}
