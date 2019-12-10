// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cilindro.h
//
// #############################################################################

#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cilindro con dos puntos

class Cilindro : public ObjRevolucion
{
   public:
   Cilindro(float radio=1, float altura=1, int num_instancias=20) ;

} ;




#endif
