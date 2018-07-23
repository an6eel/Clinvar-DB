#include "mutacion.h"

using namespace std;


template<typename T,class Iter>
vector<T> extract(Iter fst,Iter lst,const string c){
	
	vector<T> v;
	auto it=fst;

	while(fst!=lst){
		it=find_first_of(fst,lst,c.begin(),c.end());
		v.push_back(string(fst,it));
		fst=it;
		if(fst!=lst)
			fst++;
	}
	
	return v;
}

template<class T,class Iter,class Oper>
vector<T> extractOP(Iter fst,Iter lst,const char c,Oper op){
	
	vector<T> v;
	string aux;
	string aux2;
	T auxi;
	aux2.push_back(c);
	auto it=fst;
	auto it1=it;

	while(it1!=lst){
		it=find_first_of(it1,lst,aux2.begin(),aux2.end());
		aux=string(it1,it);

		if(aux!="."){
			auxi=op(aux);
			v.push_back(auxi);
		}
		it1=it;
		if(it1!=lst)
			it1++;
		
	}
	
	return v;
}

mutacion::mutacion(){
    ID="";
    chr="";
    pos=0;
    common=false;
}

mutacion::mutacion(const mutacion& m){
    ID=m.getID();
    chr=m.getChr(); 
    pos=m.getPos(); 
    ref_alt=m.getRef_alt(); 
    genes=m.getGenes(); 
    common=m.getCommon();
    caf=m.getCaf();
    enfermedades=m.getEnfermedades();
    clnsig=m.getClnsig();
};

const vector<enfermedad> mutacion::contruct_getEnfs(const string & str){
	map<string,string> map;
	string::const_iterator it1,it2;
	vector<string> vectname,vectdb;
	vector<enfermedad> retur;
  	string charc;
	vector<string> keys={"CHR","POS","ID","REF","ALT","GENEINFO=","COMMON=","CAF=","CLNDSDBID=","CLNDBN=","CLNDSDB=","CLNSIG="};
	unsigned int cont=0;
	it1=it2=str.begin();

	// CONSTRUCCION MAP

 	while(*it2!='.'){
 		
 		if(*it2=='	'){
 			map.insert(make_pair(keys[cont],string(it1,it2)));
 			it2++;
 			it1=it2;
 			cont++;
 		}
 		else it2++;
 	}

 	for(cont;cont<keys.size();++cont){
 		it1=search(str.begin(),str.end(),keys[cont].begin(),keys[cont].end());
 		
 		if(it1!=str.end()){
	   		advance(it1,keys[cont].size());
	   		it2=it1;
	   		while((*it2) != ';' && it2!=str.end())
	   			 ++it2;
	   		map.insert(make_pair(keys[cont],string(it1,it2)));
   		}
 	}

 	// OBTENCION DATOS DEL MAP

 	chr=map["CHR"];
 	pos=atoi(map["POS"].c_str());
 	ID=map["ID"];
 	ref_alt.push_back(map["REF"]);
 	ref_alt.push_back(map["ALT"]);
 	string strg=map["GENEINFO="];
  	charc="|";
 	genes=extract<string>(strg.begin(),strg.end(),charc);
 	common=map["COMMON="]=="1" ? true:false;

 	strg=map["CAF="];
 	if(map["CAF="]!=""){
    		caf=extractOP<float>(strg.begin(),strg.end(),',',[&](string str){ return stof(str);});
      
	}
	strg=map["CLNSIG="];
 	clnsig=extractOP<int>(strg.begin(),strg.end(),'|',[&](string str){return stoi(str);});
 	
  	charc="|,;";
 	vectname=extract<string>(map["CLNDBN="].begin(),map["CLNDBN="].end(),charc);
 	enfermedades=extract<string>(map["CLNDSDBID="].begin(),map["CLNDSDBID="].end(),charc);
 	vectdb=extract<string>(map["CLNDSDB="].begin(),map["CLNDSDB="].end(),charc);

	unsigned int max=vectname.size()>enfermedades.size() ? vectname.size() : enfermedades.size();
	max=max > vectdb.size() ? max : vectdb.size();
	string c1,c2,c3;
	string blanco="";

	// CONSTRUIMOS VECTOR ENFERMEDADES
  
 	for(unsigned int i=0;i<max;++i){
 		c1 = (i >= vectname.size()) ? blanco : vectname[i];
		c2 = (i >= enfermedades.size()) ? blanco : enfermedades[i];
		c3 = (i >= vectdb.size()) ? blanco : vectdb[i];	
 		retur.push_back(enfermedad(c1,c2,c3));
	}

	return retur;


}

void mutacion::setID(const string & id){
    ID=id;
}

void mutacion::setChr(const string & chr){
    this->chr=chr;
}

void mutacion::setPos(const unsigned int & pos){
    this->pos=pos;
}

void mutacion::setRef_alt(const std::vector<string> & ref_alt){
    this->ref_alt = ref_alt;
}

void mutacion::setGenes (const std::vector<string> & genes){
    this->genes=genes;
}

void mutacion::setCommon (const bool & common){
    this->common=common;
}

void mutacion::setCaf (const std::vector<float> & caf){
    this->caf=caf;
}

void mutacion::setEnfermedades (const std::vector<IDenf> & enfermedades){
    this->enfermedades=enfermedades;
}

void mutacion::setClnsig (const std::vector<int> & clnsig){
    this->clnsig=clnsig;
}  

string mutacion::getID( ) const{
    return ID;
}

string mutacion::getChr( ) const{
    return chr;
}

unsigned int mutacion::getPos( ) const{
    return pos;
}

const std::vector<string> & mutacion::getRef_alt () const{
    return ref_alt;
}

const std::vector<string> & mutacion::getGenes () const{
    return genes;
}

bool mutacion::getCommon () const{
    return common;
}

const std::vector<float> & mutacion::getCaf () const{
    return caf;
}

const std::vector<IDenf> & mutacion::getEnfermedades () const{
    return enfermedades;
}

const std::vector<int> & mutacion::getClnsig () const{
    return clnsig;
}

mutacion & mutacion::operator=(const mutacion & m){
    if(this != &m){
        ID=m.getID();
        chr=m.getChr(); 
        pos=m.getPos(); 
        ref_alt=m.getRef_alt(); 
        genes=m.getGenes(); 
        common=m.getCommon();
        caf=m.getCaf();
        enfermedades=m.getEnfermedades();
        clnsig=m.getClnsig();
    }
    
    return *this;
}

bool mutacion::operator==(const mutacion & m) const{
    bool iguales = true;
    
    if(ID != m.getID() || chr != m.getChr() || pos != m.getPos() ){
        iguales = false;
    }
    
    return iguales;
}

bool mutacion::operator<(const mutacion & m) const{
    
    if(chr!=m.getChr()){
        unsigned int local=0,fg=0;
        
        if(chr != "X" && chr != "Y" && chr != "MT")
            local=stoi(chr);
      
        else if(chr=="X")
            local=23;

        else if(chr=="Y")
            local=24;

        else
            local=25;


        if(m.getChr() != "X" && m.getChr() != "Y" && m.getChr() != "MT")
            fg=stoi(m.getChr());
        
        else if(m.getChr()=="X")
            fg=23;

        else if(m.getChr()=="Y")
            fg=24;

        else
            fg=25;

        return local<fg;   
    }
        
    else return pos<m.getPos();

} 

bool mutacion::operator>(const mutacion & m) const{
    return m<*this;
}
  
ostream& operator<< ( ostream& os, const mutacion& mut){
    os <<  mut.getChr() << "  " << mut.getPos() << "  " << mut.getID() << " ";
    
    os<< mut.getRef_alt().at(0) << "  ";
    
    auto i= mut.getRef_alt().begin();
    ++i;
    while( i != mut.getRef_alt().end()){
        os << (*i);
        i++;
        if(i != mut.getRef_alt().end())
            os << ',';
        
    }
    os << ' ';
    
    os << "GENEINFO=";
    vector<string>::const_iterator ij = mut.getGenes().begin();
    while(ij != mut.getGenes().end()){
        os << (*ij);
        ++ij;
        if(ij!=mut.getGenes().end())
            os << '|';
    }
    
    os << ';';
    
    os << "COMMON=";
    if(mut.getCommon()) 
        os << '1';
    else
        os << '0';
    os << "; ";
        
    os << "CAF=";
    vector<float>::const_iterator j=mut.getCaf().begin();
    while(j != mut.getCaf().end()){
        os << (*j);
        ++j;
        if(j!=mut.getCaf().end()) 
            os << ',';
    }
    os << "; ";
    
    string clndsdbid="";
    
    for(auto i=mut.getEnfermedades().begin();i!=mut.getEnfermedades().end();){
      clndsdbid+=(*i);

      ++i;
      if(i!=mut.getEnfermedades().end()){
        clndsdbid+='|';
      }

    }

    os << "CLNDSDBID=";
    os << clndsdbid;
    os << "; ";
    
    
    return os;
};