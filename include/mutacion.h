/* 
 * mutacion.h
 * 
 * Copyright  (C) Juan F. Huete y Carlos Cano 
*/
#ifndef __MUTACION_H
#define __MUTACION_H

#include <string>
#include <iostream> 
#include <vector>
#include <map>

#include "enfermedad.h"
using namespace std;
//! Clase mutacion, asociada a la definición de una mutación/SNP 
/*! mutacion::mutacion,  .....
 * 
*/

/**
 * \class mutacion
 * @brief Gestiona la información de la mutacion
 * 
 **/

typedef string IDenf;

class mutacion {
 private:
  string ID;///< ID asociado a la mutacion
  string chr; ///<  Identificador del cromosoma (string). Los cromosomas válidos son: "1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "X", "Y", "MT"
  unsigned int pos;///<  Identificador de la posición dentro del cromosoma (unsigned int).
  std::vector<string> ref_alt;///< Base(s) en el genoma de referencia y alternativa(s) posible(s) (vector de string)
  std::vector<string> genes;///< Gen(es) asociado(s) al SNP (vector de string)
  bool common;///< Indica si el SNP es común en la población (bool).
  std::vector<float> caf;///< Frecuencia de cada base del SNP en la población (vector de float)
  std::vector<IDenf> enfermedades;///< Enfermedades asociadas al SNP (vector de enfermedad)
  std::vector<int> clnsig;///< Relevancia clínica del SNP para cada enfermedad utilizando el código numérico del campo CLNSIG (vector de int)

 public:
  /// Constructor por defecto
  mutacion();
  /// Constructor de copias
  mutacion(const mutacion& m);
  /// Construye la enfermedad y obtiene el vector de las enfermedades
  const vector<enfermedad> contruct_getEnfs(const string & str);   //para crear objeto mutacion a partir de la cadena que contiene una línea completa del fichero de entrada
  
 /**
  * @brief Establece la id de la mutacion
  * @param id string que se asignara dentro de ID del objeto
  **/
  void setID(const string & id);
  
  /**
  * @brief Establece el identificador de cromosoma
  * @param chr string que se asignara dentro de chr del objeto
  **/
  void setChr(const string & chr);
  
  /**
  * @brief Establece el identificador de posicion dentro del cromosoma de la mutacion
  * @param pos unsigned int que se asignara dentro de la variable pos del objeto 
  **/
  void setPos(const unsigned int & pos);
  
  /**
  * @brief Establece la base(s) en el genoma de referencia y alternativa(s)
  * @param ref_alt std::vector<string> se asignara dentro de la variable ref_alt del objeto 
  **/
  void setRef_alt(const std::vector<string> & ref_alt);
  
  /**
  * @brief Establece el gen(es) asociado(s) al SNP
  * @param genes std::vector<string> se asignara dentro de la variable genes del objeto 
  **/
  void setGenes (const std::vector<string> & genes);
  
  /**
  * @brief Establece el indicador si el SNP es común en la población (bool).
  * @param common bool se asignara dentro de la variable common del objeto instanciado
  **/
  void setCommon (const bool & common);
  
  /**
  * @brief Establece la frecuencia de cada base del SNP en la población (vector de float)
  * @param caf std::vector<float> se asignara dentro de la variable caf del objeto instanciado
  **/
  void setCaf (const std::vector<float> & caf);
  
  /**
  * @brief Establece las enfermedades asociadas al SNP (vector de enfermedad)
  * @param enfermedades std::vector<enfermedad> se asignara dentro de la variable de enfermedades
  **/
  void setEnfermedades (const std::vector<IDenf> & enfermedades);
  
  /**
  * @brief Establece la relevancia clínica del SNP para cada enfermedad utilizando el código numérico del campo CLNSIG (vector de int)
  * @param clnsig std::vector<int> se asignara dentro de la variable de clnsig
  **/
  void setClnsig (const std::vector<int> & clnsig);  
  
  /**
  * @brief ID de la mutacion
  * @return Devuelve la ID de la mutacion
  * 
  **/
  string getID( ) const;
  
  /**
  * @brief Chr de la mutacion
  * @return Devuelve el identificador de cromosoma de la mutacion
  * 
  **/
  string getChr( ) const;
  
  /**
  * @brief Chr de la mutacion
  * @return Devuelve el identificador de cromosoma de la mutacion
  * 
  **/
  unsigned int getPos( ) const;
  
  /**
  * @brief Ref_Alt de la mutacion
  * @return Devuelve la base(s) en el genoma de referencia y alternativa(s)
  * 
  **/
  const std::vector<string> & getRef_alt() const;
  
  /**
  * @brief Genes de la mutacion
  * @return Devuelve el gen(es) asociado(s) al SNP (vector de string)
  * 
  **/
  const std::vector<string> & getGenes() const;
  
  /**
  * @brief Common de la mutacion
  * @return Devuelve un bool diciendo si la mutacion es comun o no.
  * 
  **/
  bool getCommon() const;
  
  /**
  * @brief Frecuencia de cada base del SNP en la población
  * @return Devuelve vector<float> caf de la mutacion.
  * 
  **/
  const std::vector<float> & getCaf () const;
  
  /**
  * @brief Enfermedades asociadas al SNP (vector de enfermedad)
  * @return Devuelve vector<IDenf> por referencia constante de la mutacion
  * 
  **/
  const std::vector<IDenf> & getEnfermedades() const;
  
  /**
  * @brief Relevancia clínica del SNP para cada enfermedad utilizando el código numérico del campo CLNSIG (vector de int)
  * @return Devuelve vector<int> por referencia constante del campo clnsig
  * 
  **/
  const std::vector<int> & getClnsig() const;
    
  /**
  * @brief Operador de asignacion de la clase mutacion
  * @param m objeto al que se igualará el *this
  * @return Devuelve un objeto por referencia del tipo mutacion
  * 
  **/
  mutacion & operator=(const mutacion & m);
  
  /**
  * @brief Operador de comparacion de igualdad de la clase mutacion
  * @param m objeto con el que se comparará el *this
  * @return Devuelve un objeto bool que indica si ambos objetos son iguales o no
  * 
  **/
  bool operator==(const mutacion & m) const;
  
  /**
  * @brief Operador de comparacion menor que de la clase mutacion. El orden viene determinado por Chr y pos. El primer criterio es el número de cromosoma. El orden para el número de cromosoma se rige por "1"<"2"<"3"<...<"22"<"X"<"Y"<"MT". Dos mutaciones del mismo cromosoma deben ordenarse según su posición, de menor posición a mayor (orden natural de enteros). 
  * @param m objeto con el que se comparará el *this
  * @return Devuelve un objeto bool que indica si el objeto *this es mayor que m
  * 
  **/
  bool operator<(const mutacion & m) const;
  
  /**
  * @brief Operador de comparacion menor que de la clase mutacion. El orden viene determinado por Chr y pos. El primer criterio es el número de cromosoma. 
  * @param m objeto con el que se comparará el *this
  * @return Devuelve un objeto bool que indica si el objeto *this es mayor que m
  * 
  **/
  bool operator>(const mutacion & m) const;

};

/**
  * @brief Operador de salida de la clase mutacion
  * @param mut objeto que se imprimirá por el flujo
  * @param os flujo por el que se imprimirá el objeto
  * @return Devuelve un flujo por referencia 
  *
  **/
ostream& operator<< ( ostream& os, const mutacion& mut);   //Imprimir TODOS los campos del objeto mutación.

#endif
