#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

typedef enum {ORTOGONAL, PERSPECTIVA} TipoCamara;

typedef enum {NINGUNO, METTATON, CUBO, TETRAEDRO, MODELOPLY, OBJREV, CILINDRO, CONO, ESFERA, PEON, CUADRO, MONEDA1, MONEDA2, MONEDA3, FLOR, NUBE} objetoSeleccionado;

class Camara{
	private:

	public:
		Tupla3f eye;
		Tupla3f at;
		Tupla3f up;

		TipoCamara tipo;
		float left, right, bottom, top, near, far;

		objetoSeleccionado seleccion;

		Camara(const Tupla3f eye, const Tupla3f at, const Tupla3f up,
			const TipoCamara tipo, const float near, const float far,
			const float left, const float right, const float top,
         const float bottom);

		void rotarXExaminar(const float angle);
		void rotarYExaminar(const float angle);
		void rotarZExaminar(const float angle);
		void rotarXFirstPerson(const float angle);
		void rotarYFirstPerson(const float angle);
		void rotarZFirstPerson(const float angle);

		void mover(const float x, const float y, const float z);
		void girar(const float x, const float y);
		void girarEx(int x, int y);
		void zoom(const float factor);

		void setObserver();
		void setProyeccion();

		void setObjetoSeleccionado(const objetoSeleccionado obj);
		objetoSeleccionado getObjetoSeleccionado() const;

	   void setLeft(const float valor);
	   void setRight(const float valor);
	   void setTop(const float valor);
	   void setBottom(const float valor);
	   float getLeft() const;
	   float getRight() const;
	   float getTop() const;
	   float getBottom() const;

};

#endif
