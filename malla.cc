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
  glDrawElements( GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data() );
  glDisableClientState( GL_VERTEX_ARRAY );
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido()
{
  // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
  if (id_vbo_ver == 0) {
    id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size()*3, v.data() );
    id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*3, f.data() );
  }

  // Especificar localización y formato de la tabla de vértices, habilitar tabla
  glBindBuffer(GL_ARRAY_BUFFER,id_vbo_ver); // Activar VBO de vértices
  glVertexPointer( 3,GL_FLOAT, 0, 0 ); // Especifica formato y offset (=0)
  glBindBuffer(GL_ARRAY_BUFFER, 0 ); // Desactivar VBO de vértices.
  glEnableClientState(GL_VERTEX_ARRAY); // Habilitar tabla de vértices

  // Visualizar triángulos con glDrawElements(puntero a tabla == 0)
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
  glColorPointer( 3, GL_FLOAT, 0, cA1.data() ) ;
  glDrawElements( GL_TRIANGLES, f1.size()*3, GL_UNSIGNED_INT, f1.data() );
  glDisableClientState( GL_VERTEX_ARRAY );

  // Visualizar la malla usando glDrawElements,
  glEnableClientState( GL_VERTEX_ARRAY );
  glVertexPointer( 3, GL_FLOAT, 0, v.data() );
  glColorPointer( 3, GL_FLOAT, 0, cA2.data() ) ;
  glDrawElements( GL_TRIANGLES, f2.size()*3, GL_UNSIGNED_INT, f2.data() );
  glDisableClientState( GL_VERTEX_ARRAY );
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(int modo)
{
  switch (modo) {
    case 0:
      draw_ModoInmediato();
      break;
    case 1:
      draw_ModoDiferido();
      break;
    case 2:
      draw_ModoAjedrez();
      break;
    default:
      draw_ModoInmediato();
      break;
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
