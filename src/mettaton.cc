#include "aux.h"
#include "malla.h"
#include "mettaton.h"
using namespace std ;

Mettaton::Mettaton()
{

    cuerpo = new MettatonCuerpo();
    paloI = new MettatonPalo();
    paloE = new MettatonPalo();
    brazoIzq = new MettatonBrazoIzquierdo();
    brazoDer = new MettatonBrazoDerecho();
    manoIzq = new MettatonManoIzquierda();
    manoDer = new MettatonManoDerecha();
    rueda = new MettatonRueda();
}

void Mettaton::draw(int modo, GLenum visualizacion, bool ajedrezActivado) {
   glPushMatrix();

      glTranslatef(3.3,1,-2.5);
      glRotatef(giroPersonaje, 0, 0, 1);
      glTranslatef(-3.3,-1,2.5);

      glPushMatrix();
         glTranslatef(3.3,-4.5,-2.5);
         glRotatef(giroRueda, 0, 1, 0);
         glTranslatef(-3.3,4.5,2.5);
         rueda->draw(modo, visualizacion, ajedrezActivado);
      glPopMatrix();

      paloE->draw(modo, visualizacion, ajedrezActivado);

      glPushMatrix();
         glTranslatef(0.0,alturaCuerpoBrazos,0.0);
         glPushMatrix();
            glTranslatef(0.35,0.0,-0.25);
            glScalef(0.9,0.9,0.9);
            paloI->draw(modo, visualizacion, ajedrezActivado);
         glPopMatrix();
         glPushMatrix();
            glTranslatef(0.0,alturaBrazos,0.0);
            glPushMatrix();
               glTranslatef(-3.3,0.5,-2.5);
               glRotatef(giroManoIzq, 0, 0, 1);
               glTranslatef(3.3,-0.5,2.5);
               manoIzq->draw(modo, visualizacion, ajedrezActivado);
            glPopMatrix();
            brazoIzq->draw(modo, visualizacion, ajedrezActivado);
            manoDer->draw(modo, visualizacion, ajedrezActivado);
            brazoDer->draw(modo, visualizacion, ajedrezActivado);
         glPopMatrix();
         cuerpo->draw(modo, visualizacion, ajedrezActivado);
      glPopMatrix();
   glPopMatrix();
}

void Mettaton::rotarMano(float incremento) {
   if (contadorManoIzq+incremento > 20) {
      ascendiendoGiroMano = false;
   } else if (contadorManoIzq-incremento < -30) {
      ascendiendoGiroMano = true;
   }

   if (ascendiendoGiroMano) {
      contadorManoIzq += incremento;
      giroManoIzq = 20;
   } else {
      contadorManoIzq -= incremento;
      giroManoIzq = -20;
   }

   //<cout << giroBrazos << endl;
}

void Mettaton::rotarBrazos(float incremento) {
   if (giroBrazos+incremento > 20) {
      ascendiendo = false;
   } else if (giroBrazos-incremento < -30) {
      ascendiendo = true;
   }

   if (ascendiendo) {
      giroBrazos += incremento;
   } else {
      giroBrazos -= incremento;
   }

   //<cout << giroBrazos << endl;
}

void Mettaton::elevarBrazos(float incremento) {
   incrementoConvertidoB = incremento * 0.01;

   if (alturaBrazos+incrementoConvertidoB > 0.8) {
      ascendiendoBrazos = false;
   } else if (alturaBrazos-incrementoConvertidoB < 0) {
      ascendiendoBrazos = true;
   }

   if (ascendiendoBrazos) {
      alturaBrazos += incrementoConvertidoB;
   } else {
      alturaBrazos -= incrementoConvertidoB;
   }

   //cout << alturaBrazos << endl;
}

void Mettaton::elevarCuerpoBrazos(float incremento) {
   incrementoConvertidoCB = incremento * 0.01;

   if (alturaCuerpoBrazos+incrementoConvertidoCB > 1.5) {
      ascendiendoCuerpoBrazos = false;
   } else if (alturaCuerpoBrazos-incrementoConvertidoCB < -0.5) {
      ascendiendoCuerpoBrazos = true;
   }


   if (ascendiendoCuerpoBrazos) {
      alturaCuerpoBrazos += incrementoConvertidoCB;
   } else {
      alturaCuerpoBrazos -= incrementoConvertidoCB;
   }

   //cout << alturaBrazos << endl;
}

void Mettaton::rotarRueda(float incremento) {
   giroRueda += incremento;

   //cout << giroRueda << endl;
}

void Mettaton::rotarPersonaje(float incremento) {
   if (giroPersonaje+(incremento / 2.0) > 4) {
      ascendiendoPersonaje = false;
   } else if (giroPersonaje-(incremento / 2.0) < -4) {
      ascendiendoPersonaje = true;
   }

   if (ascendiendoPersonaje) {
      giroPersonaje += (incremento / 2.0);
   } else {
      giroPersonaje -= (incremento / 2.0);
   }

   //cout << giroPersonaje << endl;
}

void Mettaton::setColorSolido(const Tupla3f & nuevoColor) {
   cuerpo->setColorSolido(nuevoColor);
   paloI->setColorSolido(nuevoColor);
   paloE->setColorSolido(nuevoColor);
   brazoIzq->setColorSolido(nuevoColor);
   brazoDer->setColorSolido(nuevoColor);
   manoIzq->setColorSolido(nuevoColor);
   manoDer->setColorSolido(nuevoColor);
   rueda->setColorSolido(nuevoColor);
}
