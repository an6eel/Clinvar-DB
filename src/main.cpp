/** 
 *  @file  main,cpp
 *  @author  Ángel García Malagón
 *  @version 1.0 
 *  
 *  @brief Clinvar DataBase Test
 *
 *  @section DESCRIPCIÓN
 * 
 *  Interfaz que permite diferentes consultas
 *  de forma eficiente sobra la Base de Datos
 *  ClinVar.
 *  
 **/


#include "clinvar.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;


int main(){

	clinvar X;
	high_resolution_clock::time_point inicio,fin;
    duration<double> tiempo_transcurrido;
	
	// Prueba de los metodos load e insert                       <----------- LOAD && INSERT

	inicio=high_resolution_clock::now();

	X.load("./data/clinvar_20160831.vcf");

	fin=high_resolution_clock::now();
	tiempo_transcurrido  = duration_cast<duration<double> >(fin- inicio);

	cout << "Lectura de la base de datos completada.Tiempo transcurrido: " << tiempo_transcurrido.count() << " s." << endl;

	X.size();

	// Prueba de los metodos find_Mut y erase              <------------ FIND_MUT && ERASE

	cout << endl << "Buscamos rs11368665" << endl;
	auto it=X.find_Mut("rs11368665");

	if(it!=X.end())
		cout << *it << endl;

	cout <<  "Borramos rs11368665" << endl;
	X.erase("rs11368665");

	auto it1=X.find_Mut("rs11368665");

	if(it1!=X.end())
		cout << *it1 << endl;
	else
		cout << "Se ha borrado " << endl;
	
	/*// Prueba de iteracion con iterator                 <--------------- ITERATOR
	
	for (clinvar::iterator it=X.begin();it!=X.end();it++)
		cout << *it << endl;

	// Prueba de iteracion con enfermedad_iterator      <---------------- ENFERMEDAD_ITERATOR

	for (clinvar::enfermedad_iterator it=X.ebegin();it!=X.eend();it++)
		cout << it->second << endl;

	// Prueba de iteracion con gen_iterator                  <-------------- GEN_ITERATOR

	
	for (clinvar::gen_iterator itg=X.gbegin(); itg!=X.gend();++itg)
		cout << *itg << endl;

	*/// Prueba de la busquedas de enfermedades asociadas a un gen  <---------------- GET_MUTACIONESGEN
	cout << endl << "Buscamos el gen A2ML1:144568" << endl;
	auto set1=X.getMutacionesGen("A2ML1:144568");

	for(auto it2=set1.begin();it2!=set1.end();++it2){
		cout << *X.find_Mut(*it2) << endl;
	}

	// Prueba de la busqueda de enfermedades asociadas a una mutacion o a una palabra  <------------- GET_ENFERMEDADES (KEYWORD) && GET_ENFERMEDADES (MUTACION)
	
	auto it3=X.find_Mut("rs863224951");
	auto enfs=X.getEnfermedades(*it3);
	cout << endl << "Hay " << enfs.size() << " enfermedades asociadas a la mutacion rs863224951" << endl;
	for(auto& enf:enfs){
		cout << "\t-"<<enf << endl;
	}

	string enfermedad="cancer";
	auto lst=X.getEnfermedades(enfermedad);
	cout << endl << "Hay " << lst.size() << " enfermedades asociadas con la palabra " << enfermedad << endl;

	for(auto& i:lst){
		cout << "\t-"<< X.find_Enf(i)->second <<endl;
	}
	


	// Prueba de la busqueda de enfermedades, borrado de mutaciones asociadas a la enfermedad <---------------  FIND_ENF && GET_MUTACIONESENF && ERASE(ENF)

	string idenf="CN233179"; //<---- Cambiarlo para usar otro
	cout << endl << "Buscamos la enfermedadad asociada al ID " << idenf << endl;

	auto enfit=X.find_Enf(idenf);

	if(enfit!=X.eend()){
		cout << enfit->second << endl;
		auto set2=X.getMutacionesEnf(idenf);

		cout << "Las mutaciones asociadas a estan enfermedad son:"<< endl;
		for(auto& i:set2){
			cout << "-"<< *X.find_Mut(i) <<endl; 
			X.erase(i);
		}

	}

	else
		cout << "No existe." << endl;

	cout << "Hemos borrado las mutaciones asociadas a esa enfermedad" << endl;
	cout << "Volvemos a buscar la enfermedad..." << endl;

	auto enfit2=X.find_Enf(idenf);
	if(enfit2!=X.eend())
		cout << enfit2->second << endl;
	else
		cout << "No existe." << endl;

	
	// Prueba de la busqueda de las k mutaciones mas probables asociadas a una enfermedad    <-------------- TOP_K_MUTACIONES

	cout << endl << "Buscamos las 10 mutaciones mas probables asociadas a la palabra cancer" << endl;
	auto set=X.topKMutaciones(10,"cancer");

	for(auto it=set.begin();it!=set.end();++it)
		cout << *it << endl;

	string chr="4";
	unsigned int pos=0;

	// Prueba de los metodos Lower_Bound y Upper-Bound del TDA CLinvar          <-------------------- LOWER_BOUND && UPPER_BOUND

	cout << endl << "Buscamos el lower-bound de Mut(4,0): " << endl;
	cout << *(X.lower_bound(chr,pos)) << endl;  							

	cout << endl << "Buscamos el upper-bound de Mut(4,0): " << endl;
	cout << *(X.upper_bound(chr,pos)) << endl;
	


}