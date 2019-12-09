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
    id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size()*3 * sizeof(float), v.data() );
  }
  if (id_vbo_tri == 0) {
    id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*3 * sizeof(int), f.data() );
  }

  if (id_vbo_col == 0) {
    id_vbo_col = CrearVBO(GL_ARRAY_BUFFER, c.size()*3 * sizeof(float), c.data() );
  }

  glEnableClientState(GL_VERTEX_ARRAY); // Habilitar tabla de vértices
  glEnableClientState(GL_COLOR_ARRAY); // Habilitar tabla de colores


  // Especificar localización y formato de la tabla de vértices
  glBindBuffer(GL_ARRAY_BUFFER,id_vbo_ver); // Activar VBO de vértices
  glVertexPointer( 3,GL_FLOAT, 0, 0 ); // Especifica formato y offset (=0)
  glBindBuffer(GL_ARRAY_BUFFER, 0 ); // Desactivar VBO de vértices.

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

  // INICIALIZACIÓN DE COLORES
  // Inicializar colores solido para ObjPLY en Modo inmediato y diferido
  cPLY.clear();
  for (int i=0; i<v.size(); i++) {
    cPLY.push_back({1.0,0.0,0.64});
  }

  // Inicializar colores solido para cubo en Modo inmediato y diferido
  cCubo.clear();
  for (int i=0; i<v.size(); i=i+2) {
    cCubo.push_back({1.0,0.0,0.64});
    cCubo.push_back({0.97,0.78,0.05});
  }

  // Inicializar colores lineas y puntos en Modo inmediato y diferido
  cLineas.clear();
  for (int i=0; i<v.size(); i++) {
    cLineas.push_back({0.28,0.25,0.4});
  }

  // Inicializar colores cubo en Modo Ajedrez
  cAjedrez1.clear();
  cAjedrez2.clear();
  for (int i=0; i<v.size(); i++) {
    cAjedrez1.push_back({1.0,0.0,0.64});
    cAjedrez2.push_back({0.97,0.78,0.05});
  }

  if (ajedrezActivado) {
    draw_ModoAjedrez();
  } else {
    switch (visualizacion) {
      case GL_POINT:
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
        c = cCubo;
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
