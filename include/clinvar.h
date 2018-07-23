/** 
 *  @file  clinvar.h
 *  @author  Ángel García Malagón
 *  @version 1.0 
 *  
 *  @brief Clinvar DataBase
 *
 *  @section DESCRIPCIÓN
 * 
 *  Interfaz que permite diferentes consultas
 *  de forma eficiente sobra la Base de Datos
 *  ClinVar.
 *  
 **/

#ifndef _CLINVAR_H_
#define _CLINVAR_H_

#include "mutacion.h"
#include "enfermedad.h"
#include <map>
#include <set>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;


typedef string IDgen;
typedef string IDmut;
typedef string IDenf;

/// Functor ProbMutaciones

class ProbMutaciones{
public:
	bool operator()(const mutacion& a,const mutacion& b){
		return (1-a.getCaf()[0])>=(1-b.getCaf()[0]);
	}
};

/**
* \class clinvar
* @brief Gestiona los datos de la Base de Datos Clinvar
* 
**/

class clinvar{
public:

	class iterator;
	class gen_iterator;
	typedef map<IDenf,enfermedad>::iterator enfermedad_iterator;
	
	/** @brief Lee los datos de un archivo, e inserta los datos en Clinvar
	  * @param nombreDB Nombre del archivo a leer
	  */

	void load (string nombreDB);

	/** @brief Inserta una nueva mutacion en CLinvar
	  * @param x Mutacion a insertar
	  */

	void insert (const pair<mutacion,vector<enfermedad>> & x);

	/** @brief Eliminar una mutacion de la base de datos.
	  *  Ademas si hay una enfermedad asociada a esta mutacion
	  *  tambien se elimina
	  *
	  * @param ID ID de la mutacion a borrar
	  * @retval true Si el elemento se ha borrado correctamente
	  * @retval false Si el elemento no se ha borrado correctamente
	  */

	bool erase (IDmut ID);

	/** @brief Busca la mutacion con identificador ID
	  *
	  * @param ID Identificador de la mutacion a buscar
	  * @retval iterator Iterador a la posicion de la mutacion encontrada
	  * @retval end() si no se ha encontrado la mutacion
	  */

	iterator find_Mut (IDmut ID);

	/** @brief Busca la enfermedad con identificador ID
	  *
	  * @param ID identificador de la enfermedad a buscar
	  * @retval enfermedad_iterator a la posicion de la enfermedad encontrada
	  * @retval eend() si no se ha encontrado la enfermedad
	  */

	enfermedad_iterator find_Enf(IDenf ID);

	/** @brief Obtiene las enfermedades asociadas a una mutacion
	  *
	  * @param mut Mutacion de la que obtenemos las enfermedades
	  * @return Vector<enfermedad> Vector de enfermedades asociadas a la mutacion
	  */

	vector<enfermedad> getEnfermedades(const mutacion & mut);

	/** @brief Obtiene los identificadores de enfermedades
	  * que contienen en su nombre la palabra keyword
	  *
	  * @param keyword Palabra a buscar en las enfermedades
	  * @return List<IDenf> Lista de identificadores de enfermedades que contienen keyword
	  */

	list<IDenf> getEnfermedades(string keyword);

	/** @brief Obtiene el conjunto de mutaciones asociadas a la enfermedad ID
	  *
	  * @param ID Identificador de la enfermedad
	  * @return Set<IDmut> Set de mutaciones asociadas a la enfermedad ID
	  */

	set<IDmut> getMutacionesEnf (IDenf ID);

	/** @brief Obtiene el conjunto de mutaciones asociadas al gen ID
	  *
	  * @param ID Identificador del gen
	  * @return Set de mutaciones asociadas al gen ID
	  */

	set<IDmut> getMutacionesGen (IDgen ID);

	/** @brief Obtiene un conjunto ordenado de mutaciones con las k mutaciones
	  * mas frecuentes en la poblacion asociadas con la enfermedad keyword
	  *
	  * @param k Numero de mutaciones mas frecuentes a buscar
	  * @param keyword Enfermedad a buscar
	  * @return Set ordenado en orden decreciente de probabilidad con las k mutaciones mas frecuentes
	  */
	
	set< mutacion,ProbMutaciones> topKMutaciones (int k, string keyword);

	/* Métodos relacionados con los iteradores */

	/** @brief Iterador correspondiente a la primera mutacion/enfermedad/gen
	  * segun el criterio de ordenacion de cada elemento
	  */

	iterator begin();
	enfermedad_iterator ebegin();
	gen_iterator gbegin();
	

	/** @brief Busquedas por rango en funcion de cromosoma/posicion
	  *
	  * @param cromosoma Cromosoma a buscar
	  * @param posicion Posicion a buscar
	  * @return iterator a la posicion encontrada segun lower_bound o upper_bound
	  */
	iterator lower_bound(string cromosoma, unsigned int posicion);
	iterator upper_bound(string cromosoma, unsigned int posicion);

	/** @brief Iterador correspondiente al elemento siguiente al ultimo elemento
	  * segun el criterio de ordenacion de cada elemento
	  */

	iterator end();
	enfermedad_iterator eend();
	gen_iterator gend();

	void size(){
	 	cout << "Tamaño mutDB--> " << mutDB.size() << endl;
	 	cout << "Tamaño IDm_map--> " << IDm_map.size() << endl;
	 	cout << "Tamaño gen_map--> " << gen_map.size() << endl;
	 	cout << "Tamaño EnfDB--> " << EnfDB.size() << endl;
	 	cout << "Tamaño IDenf_map--> " <<IDenf_map.size() << endl;
 	}


	/** 
	  * \class Iterator
	  */

	class iterator{
	public:
		iterator():it(0){}
		iterator(const iterator& x):it(x.it){}
		const mutacion& operator*(){return *it;}
		iterator& operator++(){++it;return *this;}
		iterator operator++(int){iterator aux(*this);++it;return aux;}
		iterator& operator--(){--it;return *this;}
		iterator operator--(int){iterator aux(*this);--it;return aux;}
		bool operator==(const iterator& x){return it==x.it;}
		bool operator!=(const iterator& x){return it!=x.it;}
		iterator& operator=(const iterator& x){
			if(this!=&x)
				it=x.it;
			return *this;
		}

	private:
		friend class clinvar;
		set<mutacion>::iterator it;

	};

	/** 
	  * \class gen_iterator
	  */

	class gen_iterator{
	public:
		gen_iterator():itmap(0){}
		gen_iterator(const gen_iterator& x);
		const mutacion& operator*();
		gen_iterator& operator++();
		gen_iterator operator++(int);
		bool operator==(const gen_iterator& x);
		bool operator!=(const gen_iterator& x);
		gen_iterator& operator=(const gen_iterator& x);

	private:
		friend class clinvar;
		map<IDgen, list< set<mutacion>::iterator>>::iterator itmap;
		list<set<mutacion>::iterator>::iterator itlist;
		clinvar *ptrclinvar;
	};

private:
	friend class iterator;
	friend class gen_iterator;

	set<mutacion> mutDB; //< DB que contiene toda la informacion asociada a una mutacion
	unordered_map<IDmut,set<mutacion>::iterator> IDm_map; //< Asocia IDmutacion con mutacion
	map<IDgen,list<set<mutacion>::iterator>> gen_map; //< Asocia genes con mutaciones
	map<IDenf,enfermedad> EnfDB; //< DB de enfermedades
	multimap<IDenf,set<mutacion>::iterator> IDenf_map; //< Asocia enfermedad con mutaciones
};








#endif