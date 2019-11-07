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
   f[1] = Tupla3i (3,2,1); // Triangulo 0
   f[2] = Tupla3i (0,2,3); // Triangulo 0
   f[3] = Tupla3i (0,3,1); // Triangulo 0
}
