#include "aux.h"
#include "malla.h"
#include "cuadro.h"

Cuadro::Cuadro(float lado, const std::string & nombre_archivo )
{

   // Inicializar la tabla de vértices
   v.resize(8);
   v[0] = Tupla3f (0,lado,0); // Vértice 4
   v[1] = Tupla3f (lado,lado,0); // Vértice 5
   v[2] = Tupla3f (0,0,0); // Vértice 6
   v[3] = Tupla3f (lado,0,0); // Vértice 7


   // Inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   f.resize(2);
   f[0] = Tupla3i (3,1,0); // Triangulo 5
   f[1] = Tupla3i (2,3,0); // Triangulo 4


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


   // Asignar texturas
   textura = new Textura(nombre_archivo);

   // Coordenadas de textura
   ct.resize(4);
   ct[0] = (Tupla2f(0,1));
   ct[1] = (Tupla2f(1,1));
   ct[2] = (Tupla2f(0,0));
   ct[3] = (Tupla2f(1,0));


}
