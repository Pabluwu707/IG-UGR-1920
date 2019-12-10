#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro()
{

   // inicializar la tabla de vértices
   v.resize(100);
   v[0] = Tupla3f (0,0,0); // Vértice 0
   v[1] = Tupla3f (50,0,0); // Vértice 1
   v[2] = Tupla3f (25, 0, 43); // Vértice 2
   v[3] = Tupla3f (25,43,25); // Vértice 3

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   f.resize(100);
   f[0] = Tupla3i (1,2,0); // Triangulo 0
   f[1] = Tupla3i (3,2,1); // Triangulo 1
   f[2] = Tupla3i (0,2,3); // Triangulo 2
   f[3] = Tupla3i (0,3,1); // Triangulo 3


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
     cSolido.push_back({0.47,0.11,0.58});
   }

   // Inicializar colores cubo en Modo Ajedrez
   cAjedrez1.clear();
   cAjedrez2.clear();
   for (int i=0; i<v.size(); i++) {
     cAjedrez1.push_back({1.0,0.0,0.64});
     cAjedrez2.push_back({0.97,0.78,0.05});
   }
}
