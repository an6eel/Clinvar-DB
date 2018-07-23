/* 
 * enfermedad.h
 * 
 * Copyright  (C) Juan F. Huete y Carlos Cano 
*/
#ifndef __ENFERMEDAD_H
#define __ENFERMEDAD_H

#include <string>
#include <iostream> 
#include <algorithm>

using namespace std;
//! Clase enfermedad, asociada al TDA enfermedad
/*! enfermedad::enfermedad,  .....
 * Descripción contiene toda la información asociada a una enfermedad almacenada en la BD ClinVar-dbSNP (nombre de la enfermedad, id, BD que provee el id)

*/

/**
 * \class Enfermedad
 * @brief Gestiona la información de la enfermedad
 * 
 **/
 
class enfermedad {
private:
  string  name; ///< Nombre de la Enfermedad
  string  ID;  ///< ID asociado a la Enfermedad
  string  database; ///< Base de datos que provee el ID

public:
 
 /// Constructor por defecto
 enfermedad ();
 
 /// Constructor por parametros
 enfermedad (const string & name, const string & ID, const string & database); 

/**
 * @brief Establece el nombre de la enfermedad
 * 
 **/
 
 void setName(const string & name);
 
 /**
 * @brief Establece el ID de la enfermedad
 * 
 **/
 
 void setID(const string & ID);
 
 /**
 * @brief Establece la database que provee la ID de la enfermedad
 * 
 **/
 
 void setDatabase(const string & database);

 /**
  * @brief Nombre de la Enfermedad
  * @return Devuelve el nombre de la enfermedad
  * 
  **/
  
 string getName( ) const;
 
 /**
  * @brief ID de la Enfermedad
  * @return Devuelve el ID de la enfermedad
  * 
  **/
  
 string getID( ) const;
 
 /**
  * @brief database que provee la ID de la Enfermedad
  * @return Devuelve el nombre de la database de la enfermedad
  * 
  **/
  
 string getDatabase( ) const;
 
 /// Operador de asignación
 enfermedad & operator=(const enfermedad & e);
 
 /// Descripción de la enfermedad
 string toString() const;

 /// Operador relacional de igualdad
 bool operator==(const enfermedad & e) const; 
 
 /// Operador relacional de desigualdad
 bool operator!=(const enfermedad & e) const;
 
 /// Operador relacional <
 bool operator<(const enfermedad & e) const;	//Orden alfabético por campo name. 
 
 ///Operador relacional >
 bool operator>(const enfermedad & e) const;	//Orden alfabético por campo name. 
 

 /**
  * @brief Comprueba si el paramétro está contenido dentro del nombre de la enfermedad
  * @param str string que se busca dentro del nombre
  * @retval true Si str está incluido en el nombre 
  * @retval false Si str no está incluido en el nombre
  * 
  **/
  
 bool nameContains(const string & str) const;   //Devuelve True si str está incluido en el nombre de la enfermedad, aunque no se trate del nombre completo. No debe ser sensible a mayúsculas/minúsculas. 

};

/// Operador de Salida <<
ostream& operator<< ( ostream& os, const enfermedad & e); //imprime enfermedad (con TODOS sus campos)



#endif