// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cono.h
//
// #############################################################################

#ifndef CONO_H_INCLUDED
#define CONO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cono hecho por revolución con dos puntos

class Cono : public ObjRevolucion
{
   public:
   Cono(float radio=1, float altura=1, int num_instancias=20) ;

} ;




#endif
