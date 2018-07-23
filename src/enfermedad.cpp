/** @brief fichero de implementacion de la clase enfermedad

*/
#include "enfermedad.h"

using namespace std;

enfermedad::enfermedad(){
  name="";
  ID="";
  database="";
}

enfermedad::enfermedad(const string & name, const string & ID, const string & database){
    string nm;

    for(auto i:name)
      nm.push_back(tolower(i));

    setName(nm);
    setID(ID);
    setDatabase(database);
}

void enfermedad::setName(const string & name){
    this->name=name;
}

void enfermedad::setID(const string & ID){
    this->ID=ID;
}

void enfermedad::setDatabase(const string & database){
    this->database=database;
}

string enfermedad::getName() const{ return name;}
 
string enfermedad::getID() const{ return ID;}
 
string enfermedad::getDatabase() const { return database;}

enfermedad & enfermedad::operator=(const enfermedad & e){
        
    if(this!=&e){
        setName(e.getName());
        setID(e.getID());
        setDatabase(e.getDatabase());
    }

    return *this;
}

string enfermedad::toString() const{
   return "Datos Enfermedad:\n\t Nombre = " + name + "\n\t ID = " + ID 
          + "\n\t Database = " + database ; 
}

bool enfermedad::operator==(const enfermedad & e) const{
     return name==e.getName();
} 

bool enfermedad::operator!=(const enfermedad & e) const{
    return !(*this==e);
}

bool enfermedad::operator<(const enfermedad & e) const{
    return /*name<e.getName() &&*/ getID()<e.getID();
}

bool enfermedad::nameContains(const string & str) const{
 string::const_iterator it;
 
 it=search(name.begin(),name.end(),str.begin(),str.end());
 return it!=name.end();
}

bool enfermedad::operator>(const enfermedad & e) const{
    return e<*this;
}
 
ostream& operator<< ( ostream& os, const enfermedad & e){
        
    os << e.getName() << ' ';
    os << e.getID() << ' ';
    os << e.getDatabase() << ' ';
   return os;
 }
     
       