#include "textura.h"
#include "jpg_imagen.hpp"

// *****************************************************************************
//
// Clase Textura
//
// *****************************************************************************

Textura::Textura( const std::string & string ) {
   // Declara puntero a imagen (pimg)
   jpg::Imagen * pimg = NULL;

   // Cargar la imagen
   pimg = new jpg::Imagen(string);

   // Usar con:
   tamx = pimg->tamX();          // Núm. columnas (unsigned)
   tamy = pimg->tamY();          // Núm. filas (unsignedl)
   texels = pimg->leerPixels();  // Puntero texels (unsigned char *)



}

void Textura::activar() {
   if (textura_id == 0) {
      glGenTextures( 1, &textura_id ); // idTex almacena el nuevo identificador

      //Cambiar el identificador de textura activa
      glBindTexture(GL_TEXTURE_2D,textura_id);

      // Especificar la imagen de textura asociada al identificador de textura activa
      gluBuild2DMipmaps(
         GL_TEXTURE_2D,
         GL_RGB, // Formato interno
         tamx, // Num. de columnas (arbitrario)
         tamy, // Num. de filas (arbitrario)
         GL_RGB, // Formato y orden de los texels en RAM
         GL_UNSIGNED_BYTE, // Tipo de cada texel
         texels // Puntero a los bytes con texels (void *)
      );

   } else {
      //Cambiar el identificador de textura activa
      glBindTexture(GL_TEXTURE_2D,textura_id);
   }

}
