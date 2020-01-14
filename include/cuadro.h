// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cuadro.h
//
// #############################################################################

#ifndef CUADRO_H_INCLUDED
#define CUADRO_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto (con textura)
// (tiene 9 vertices y 6 caras)

class Cuadro : public Malla3D
{
   public:
   Cuadro(float l, const std::string & nombre_archivo ) ;

} ;




#endif
