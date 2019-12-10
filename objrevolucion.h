// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: objrevolucion.h
//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "ply_reader.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Objeto de revolución obtenido a partir de un perfil (en un PLY
// o en un vector de puntos)

class ObjRevolucion : public Malla3D
{
   public:
      ObjRevolucion();
      ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
      ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
   protected:
      std::vector<Tupla3f> v_perfil ;   // tabla de coordenadas de vértices del perfil
      void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_sup=true, bool tapa_inf=true);
} ;




#endif
