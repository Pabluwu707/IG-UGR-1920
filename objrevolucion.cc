#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include <math.h>
using namespace std ;

// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   // A completar ......(práctica 2)
   ply::read_vertices(archivo, v_perfil);

   crearMalla(v_perfil, num_instancias);
}


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   // A completar
   crearMalla(archivo, num_instancias);
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {
   float angulo, x, y, z;
   Tupla3f verticeRotado, poloSur, poloNorte;
   Tupla3i caraCreada;
   int tamanio_perfil = perfil_original.size();
   bool tienePoloNorte = false, tienePoloSur = false;

   // Comprobar si los vertices estan en orden ascendente o descendente
   bool ascendente = perfil_original.front()(1) < perfil_original.back()(1);

   // Invertimos el vector si no es ascendente
   if (!ascendente) {
      cout << "Valor del front: " << perfil_original.front()(1) << endl;
      cout << "Valor del back: " << perfil_original.back()(1) << endl;
      cout << "No es ascendente." << endl;
      //std::reverse(perfil_original.begin(), perfil_original.end());
   }


   // Comprobamos cuales son los polos
   // Comprobar si hay polo sur
   if (perfil_original.front()(0)==0 && perfil_original.front()(2)==0) {
      poloSur = perfil_original.front();
      perfil_original.erase(perfil_original.begin());
   } else {
      poloSur(0) = 0;
      poloSur(1) = perfil_original.front()(1);
      poloSur(2) = 0;
   }

   // Comprobar si hay polo norte
   if (perfil_original.back()(0)==0 && perfil_original.back()(2)==0) {
      poloNorte = perfil_original.back();
      perfil_original.erase(perfil_original.end());
   } else {
      poloNorte(0) = 0;
      poloNorte(1) = perfil_original.back()(1);
      poloNorte(2) = 0;
   }

   tamanio_perfil = perfil_original.size();

   // Creacion de la tabla de vertices a partir de perfil
   for (int i=0; i<num_instancias; i++) {
      angulo = (2*M_PI/num_instancias) * i;
      for (int j=0; j<tamanio_perfil;j++) {
         x = (perfil_original[j](0) * cos (angulo)) + (perfil_original[j](2) * sin (angulo));
         y = perfil_original[j](1);
         z = (perfil_original[j](0) * -sin (angulo)) + (perfil_original[j](2) * cos (angulo));
         //cout << "Se crea el vertice (" << x << ", " << y << ", " << z << ")" << endl;

         verticeRotado = {x,y,z};
         v.push_back(verticeRotado);
      }
   }


   // Creacion de la tabla de triangulos (a completar)
   for (int i=0; i<num_instancias; i++) {
      for (int j=0; j<tamanio_perfil-1; j++) {
         int a = tamanio_perfil * i + j;
         int b = tamanio_perfil * ((i+1) % num_instancias) + j;

         caraCreada = {a, b, b+1};
         f.push_back(caraCreada);

         caraCreada = {a, b+1, a+1};
         f.push_back(caraCreada);
      }
   }

   if (true) {
      // Insertamos el polo sur
      v.push_back(poloSur);

      // Creamos las caras de la tapa sur
      for (int i=0; i<num_instancias; i++) {
         caraCreada = {v.size()-1, (i+1)*tamanio_perfil, i*tamanio_perfil};
         f.push_back(caraCreada);
      }
   }

   if (true) {
      // Insertamos el polo norte
      v.push_back(poloNorte);

      // Creamos las caras de la tapa norte
      for (int i=0; i<num_instancias; i++) {
         caraCreada = {v.size()-1, ((i+1)*tamanio_perfil)-1, ((i+2)*tamanio_perfil)-1};
         f.push_back(caraCreada);
      }
   }
}
