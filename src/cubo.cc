#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // Inicializar la tabla de vértices
   v.resize(8);
   v[0] = Tupla3f (0,lado,lado); // Vértice 0
   v[1] = Tupla3f (lado,lado,lado); // Vértice 1
   v[2] = Tupla3f (0,0,lado); // Vértice 2
   v[3] = Tupla3f (lado,0,lado); // Vértice 3
   v[4] = Tupla3f (0,lado,0); // Vértice 4
   v[5] = Tupla3f (lado,lado,0); // Vértice 5
   v[6] = Tupla3f (0,0,0); // Vértice 6
   v[7] = Tupla3f (lado,0,0); // Vértice 7


   // Inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   f.resize(12);
   f[0] = Tupla3i (2,1,0); // Triangulo 0
   f[1] = Tupla3i (1,2,3); // Triangulo 1
   f[2] = Tupla3i (3,5,1); // Triangulo 2
   f[3] = Tupla3i (3,7,5); // Triangulo 3
   f[4] = Tupla3i (7,4,5); // Triangulo 5
   f[5] = Tupla3i (7,6,4); // Triangulo 4
   f[6] = Tupla3i (6,0,4); // Triangulo 6
   f[7] = Tupla3i (2,0,6); // Triangulo 7
   f[8] = Tupla3i (0,5,4); // Triangulo 11
   f[9] = Tupla3i (0,1,5); // Triangulo 10
   f[10] = Tupla3i (2,6,3); // Triangulo 8
   f[11] = Tupla3i (3,6,7); // Triangulo 9


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
   for (int i=0; i<v.size(); i=i+2) {
     cSolido.push_back({1.0,0.0,0.64});
     cSolido.push_back({0.97,0.78,0.05});
   }

   // Inicializar colores cubo en Modo Ajedrez
   cAjedrez1.clear();
   cAjedrez2.clear();
   for (int i=0; i<v.size(); i++) {
     cAjedrez1.push_back({1.0,0.0,0.64});
     cAjedrez2.push_back({0.97,0.78,0.05});
   }

   // Calcular normales del cubo
   calcular_normales();



}
