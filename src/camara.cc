#include "camara.h"
using namespace std ;

Camara::Camara(const Tupla3f eye, const Tupla3f at, const Tupla3f up,
      const TipoCamara tipo, const float near, const float far,
      const float left, const float right, const float top,
      const float bottom){
   this->eye = eye;
   this->at = at;
   this->up = up;

   this->tipo = tipo;
      cout << "Tipo: " << tipo << endl;

   this->near = near;
   this->far = far;

   this->left = left;
   this->right = right;
   this->top = top;
   this->bottom = bottom;

   seleccion = NINGUNO;

}

void Camara::rotarXExaminar(const float angle){
   eye = eye - at;
   Tupla3f eye_antiguo = eye;
   eye(1) = eye_antiguo(1) * cos(angle) - eye_antiguo(2) * sin(angle);
   eye(2) = eye_antiguo(1) * sin(angle) + eye_antiguo(2) * cos(angle);
   eye = eye + at;
}

void Camara::rotarYExaminar(const float angle){
   eye = eye - at;
   Tupla3f eye_antiguo = eye;
   eye(0) = eye_antiguo(0) * cos(angle) + eye_antiguo(2) * sin(angle);
   eye(2) = eye_antiguo(0)* -1 * sin(angle) + eye_antiguo(2) * cos(angle);
   eye = eye + at;
}

void Camara::rotarZExaminar(const float angle){
   eye = eye - at;
   Tupla3f eye_antiguo = eye;
   eye(0) = eye_antiguo(0) * cos(angle) - eye_antiguo(2) * sin(angle);
   eye(1) = eye_antiguo(0) * sin(angle) + eye_antiguo(2) * cos(angle);
   eye = eye + at;
}

void Camara::rotarXFirstPerson(const float angle){
   at = at - eye;
   Tupla3f at_antiguo = at;
   at(1) = at_antiguo(1) * cos(angle) - at_antiguo(2) * sin(angle);
   at(2) = at_antiguo(1) * sin(angle) + at_antiguo(2) * cos(angle);
   at = at + eye;
}
void Camara::rotarYFirstPerson(const float angle){
   at = at - eye;
   Tupla3f at_antiguo = at;
   at(0) = at_antiguo(0) * cos(angle) + at_antiguo(2) * sin(angle);
   at(2) = at_antiguo(0)* -1 * sin(angle) + at_antiguo(2) * cos(angle);
   at = at + eye;
}
void Camara::rotarZFirstPerson(const float angle){
   at = at - eye;
   Tupla3f at_antiguo = at;
   at(0) = at_antiguo(0) * cos(angle) - at_antiguo(2) * sin(angle);
   at(1) = at_antiguo(0) * sin(angle) + at_antiguo(2) * cos(angle);
   at = at + eye;
}

// Mover el at y el eye de la cámara
void Camara::mover(const float x, const float y, const float z){
   at(0) = x;
   at(1) = y;
   at(2) = z;
   eye(0) = x;
   eye(1) = y + 400.0;
   eye(2) = z + 300.0;
}

// Aplicar zoom aumentando o disminuyendo los marcos del frustum
void Camara::zoom(const float factor){
   left *= factor;
   right *= factor;
   top *= factor;
   bottom *= factor;
}

void Camara::girar(const float x, const float y){
   rotarXFirstPerson(-y*0.25*M_PI/180.0);
   rotarYFirstPerson(-x*0.25*M_PI/180.0);
}



// -- SETTERS --

void Camara::setObserver(){
   gluLookAt(eye(0),eye(1),eye(2),
            at(0),at(1),at(2),
            up(0),up(1),up(2));
}

void Camara::setProyeccion(){
   if (tipo == ORTOGONAL) {
      glOrtho(left,right,bottom,top,near,far);
   } else {
      glFrustum(left,right,bottom,top,near,far);
   }
}

void Camara::setLeft(const float valor){
   left = valor;
}

void Camara::setRight(const float valor){
   right = valor;
}

void Camara::setTop(const float valor){
   top = valor;
}

void Camara::setBottom(const float valor){
   bottom = valor;
}


// -- GETTERS --

float Camara::getLeft() const{
   return left;
}

float Camara::getRight() const{
   return right;
}

float Camara::getTop() const{
   return top;
}

float Camara::getBottom() const{
   return bottom;
}

objetoSeleccionado Camara::getObjetoSeleccionado() const{
   return seleccion;
}

void Camara::setObjetoSeleccionado(const objetoSeleccionado obj){
   seleccion = obj;
}
