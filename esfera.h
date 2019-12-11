// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Esfera.h
//
// #############################################################################

#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Esfera hecha por revolución dado el radio

class Esfera : public ObjRevolucion
{
   public:
   Esfera(float radio=1, int num_instancias=20) ;

} ;




#endif
