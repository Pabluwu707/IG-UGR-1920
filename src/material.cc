#include "material.h"
using namespace std;

// *****************************************************************************
//
// Clase Material
//
// *****************************************************************************

Material::Material() {
   ambiente  = {0.2, 0.2, 0.2, 1.0f};
   difuso    = {0.8, 0.8, 0.8, 1.0f};
   especular = {0.0, 0.0, 0.0, 1.0f};
   brillo    = 0;
   //cout << "Inicializando material." << endl;
}

Material::Material(Tupla4f mambiente, Tupla4f mdifuso,
   Tupla4f mespecular, float mbrillo) {
   ambiente = mambiente;
   difuso = mdifuso;
   especular = mespecular;
   brillo = mbrillo;
}

void Material::aplicar() {
   /*
   cout << "Aplicando material." << endl;
   cout << "Ambiente: " << ambiente(0) << " - " << ambiente(1) << " - " << ambiente(2) << endl;
   cout << "Difuso: " << difuso(0) << " - " << difuso(1) << " - " << difuso(2) << endl;
   cout << "Especular: " << especular(0) << " - " << especular(1) << " - " << especular(2) << endl;
   */
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
   glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
   glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void Material::setMaterial(const Material & material){
   ambiente = material.ambiente;
   difuso = material.difuso;
   especular = material.especular;
   brillo = material.brillo;
}
