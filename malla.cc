#include "aux.h"
#include "malla.h"
using namespace std ;

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato()
{
  // Visualizar la malla usando glDrawElements,
  glEnableClientState( GL_VERTEX_ARRAY );
  glVertexPointer( 3, GL_FLOAT, 0, v.data() );
  glColorPointer( 3, GL_FLOAT, 0, c.data() ) ;

  if (glIsEnabled(GL_LIGHTING)) {
      glEnableClientState(GL_NORMAL_ARRAY);
      glNormalPointer( GL_FLOAT, 0, nv.data() ) ;
      m.aplicar();
  }

  dibujarElementos();
  //glDrawElements( GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data() );
  glDisableClientState( GL_VERTEX_ARRAY );

  if (glIsEnabled(GL_LIGHTING)) {
     glDisableClientState( GL_NORMAL_ARRAY );
  }
}

void Malla3D::dibujarElementos() {
   glDrawElements( GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data() );
}

// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido()
{
  // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
  if (id_vbo_ver == 0) {
    id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size()*3 * sizeof(float), v.data() );
  }
  if (id_vbo_tri == 0) {
    id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*3 * sizeof(int), f.data() );
  }

  if (id_vbo_col == 0) {
    id_vbo_col = CrearVBO(GL_ARRAY_BUFFER, c.size()*3 * sizeof(float), c.data() );
  }

  if (id_vbo_nor == 0) {
    id_vbo_nor = CrearVBO(GL_ARRAY_BUFFER, nv.size()*3 * sizeof(float), nv.data() );
  }

  glEnableClientState(GL_VERTEX_ARRAY); // Habilitar tabla de vértices
  glEnableClientState(GL_COLOR_ARRAY); // Habilitar tabla de colores
  glEnableClientState(GL_NORMAL_ARRAY);

  // Especificar localización y formato de la tabla de vértices
  glBindBuffer(GL_ARRAY_BUFFER,id_vbo_ver); // Activar VBO de vértices
  glVertexPointer( 3,GL_FLOAT, 0, 0 ); // Especifica formato y offset (=0)
  glBindBuffer(GL_ARRAY_BUFFER, 0 ); // Desactivar VBO de vértices.

  // Especificar localización y formato de la tabla de normales
  if (glIsEnabled(GL_LIGHTING)) {
     glBindBuffer(GL_ARRAY_BUFFER,id_vbo_nor); // Activar VBO de vértices
     glNormalPointer( GL_FLOAT, 0, 0 ); // Especifica formato y offset (=0)
     glBindBuffer(GL_ARRAY_BUFFER, 0 ); // Desactivar VBO de vértices.
     m.aplicar();
  }

  // Especificar localización y formato de la tabla de colores
  glBindBuffer(GL_ARRAY_BUFFER,id_vbo_col); // Activar VBO de colores
  glColorPointer( 3,GL_FLOAT, 0, 0 ); // Especifica formato y offset (=0)
  glBindBuffer(GL_ARRAY_BUFFER, 0 ); // Desactivar VBO de colores.

  // Visualizar triángulos con glDrawElements (puntero a tabla == 0)
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vbo_tri); // Activar VBO de triángulos
  glDrawElements(GL_TRIANGLES, 3*f.size(),GL_UNSIGNED_INT, 0 );
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0 ); // Desactivar VBO de triángulos
}

// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoAjedrez()
{
  std::vector<Tupla3i> f1 ;
  std::vector<Tupla3i> f2 ;

  for (int i=0; i<f.size(); i++) {
    if (i%2 == 0) {
      f1.push_back(f[i]);
    } else {
      f2.push_back(f[i]);
    }
  }

  // Visualizar la malla usando glDrawElements,
  glEnableClientState( GL_VERTEX_ARRAY );
  glVertexPointer( 3, GL_FLOAT, 0, v.data() );
  glColorPointer( 3, GL_FLOAT, 0, cAjedrez1.data() ) ;
  glDrawElements( GL_TRIANGLES, f1.size()*3, GL_UNSIGNED_INT, f1.data() );
  glDisableClientState( GL_VERTEX_ARRAY );

  // Visualizar la malla usando glDrawElements,
  glEnableClientState( GL_VERTEX_ARRAY );
  glVertexPointer( 3, GL_FLOAT, 0, v.data() );
  glColorPointer( 3, GL_FLOAT, 0, cAjedrez2.data() ) ;
  glDrawElements( GL_TRIANGLES, f2.size()*3, GL_UNSIGNED_INT, f2.data() );
  glDisableClientState( GL_VERTEX_ARRAY );
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(int modo, GLenum visualizacion, bool ajedrezActivado)
{

   if (ajedrezActivado) {
    draw_ModoAjedrez();
  } else {
    switch (visualizacion) {
      case GL_POINT:
        c = cPuntos;
        switch (modo) {
          case 0:
            draw_ModoInmediato();
            break;
          case 1:
            draw_ModoDiferido();
            break;
        }
        break;
      case GL_LINE:
        c = cLineas;
        switch (modo) {
          case 0:
            draw_ModoInmediato();
            break;
          case 1:
            draw_ModoDiferido();
            break;
        }
      break;
      case GL_FILL:
        c = cSolido;
        switch (modo) {
          case 0:
            draw_ModoInmediato();
            break;
          case 1:
            draw_ModoDiferido();
            break;
        }
      break;
    }
  }
}

GLuint Malla3D::CrearVBO (GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram) {
  GLuint id_vbo; // Resultado: identificador de VBO
  glGenBuffers (1, &id_vbo); // Crear nuevo VBO, obtener identificador (nunca 0)
  glBindBuffer (tipo_vbo, id_vbo); // Activar el VBO usando su identificador

  // Esta instrucción hace la transferencia de datos desde RAM hacia GPU
  glBufferData (tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);
  glBindBuffer (tipo_vbo, 0); // Desactivación del VBO (activar 0)
  return id_vbo; // Devolver el identificador resultado
}


void Malla3D::calcular_normales () {
   Tupla3f A, B, Mc, Nc;

   // Inicializar vector
   for (int j=0; j < v.size(); j++) {
      nv.push_back({0,0,0});
   }

   // Calcular tabla de normales de las caras
   for (int i=0; i < f.size(); i++) {
      // Calcular vectores A y B
      A = v[f[i](1)] - v[f[i](0)];
      B = v[f[i](2)] - v[f[i](0)];

      // Calcular el vector mc perpendicular a la cara (producto vectorial de a y b)
      Mc = A.cross(B);

      // Calcular el vector normal Nc
      if (Mc.lengthSq() != 0)
         Nc = Mc.normalized();

      // Insertar en vector nf;
      nf.push_back(Nc);
   }

   // Calcular normales de los vertices
   // Calcular a partir de nf
   for (int i=0; i < f.size(); i++) {
      nv[f[i](0)] = nv[f[i](0)] + nf[i];
      nv[f[i](1)] = nv[f[i](1)] + nf[i];
      nv[f[i](2)] = nv[f[i](2)] + nf[i];
   }

   // Normalizar vertices
   for (int j=0; j < nv.size(); j++) {
      if (nv[j].lengthSq() != 0)
         nv[j] = nv[j].normalized();
   }
}



void Malla3D::establecerMaterial(const Material & material){
   m.setMaterial(material);
}
