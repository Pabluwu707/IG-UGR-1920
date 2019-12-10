#include "objply.h"
#include "ply_reader.h"


// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, this->v, this->f );


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
     cSolido.push_back({1.0,0.0,0.64});
   }

   // Inicializar colores cubo en Modo Ajedrez
   cAjedrez1.clear();
   cAjedrez2.clear();
   for (int i=0; i<v.size(); i++) {
     cAjedrez1.push_back({1.0,0.0,0.64});
     cAjedrez2.push_back({0.97,0.78,0.05});
   }
}
