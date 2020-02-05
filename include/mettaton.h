#ifndef METTATON_H_INCLUDED
#define METTATON_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "ply_reader.h"
#include "mettatoncuerpo.h"
#include "mettatonpalo.h"
#include "mettatonbrazoizquierdo.h"
#include "mettatonbrazoderecho.h"
#include "mettatonmanoizquierda.h"
#include "mettatonmanoderecha.h"
#include "mettatonrueda.h"

class Mettaton
{
   public:
      Mettaton();
      void draw(int modo, GLenum visualizacion, bool ajedrezActivado);
      void rotarRueda(float incremento);
      void rotarMano(float incremento);
      void rotarBrazos(float incremento);
      void elevarBrazos(float incremento);
      void elevarCuerpoBrazos(float incremento);
      void rotarPersonaje(float incremento);

      void setColorSolido(const Tupla3f & colorNuevo);
   protected:
   private:
      // Partes del modelo jerárquico
      MettatonCuerpo * cuerpo = nullptr;
      MettatonPalo * paloI = nullptr;
      MettatonPalo * paloE = nullptr;
      MettatonBrazoIzquierdo * brazoIzq = nullptr;
      MettatonBrazoDerecho * brazoDer = nullptr;
      MettatonManoIzquierda * manoIzq = nullptr;
      MettatonManoDerecha * manoDer = nullptr;
      MettatonRueda * rueda = nullptr;

      // Valores de los grados de libertad
      float giroManoIzq = 0;
      float contadorManoIzq = 0;
      bool ascendiendoGiroMano = true;

      float giroBrazos = 0;
      bool ascendiendo = true;

      float alturaBrazos = 0;
      float incrementoConvertidoB;
      bool ascendiendoBrazos = true;

      float alturaCuerpoBrazos = 0;
      float incrementoConvertidoCB;
      bool ascendiendoCuerpoBrazos = true;

      float giroRueda;

      float giroPersonaje = 0;
      bool ascendiendoPersonaje = true;

} ;




#endif
