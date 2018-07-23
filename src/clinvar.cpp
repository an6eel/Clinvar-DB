
#include "clinvar.h"
#include <unordered_set>

using namespace std;

void clinvar::load(string nombreDB){
	ifstream fe;
	string cadena;
	fe.open(nombreDB.c_str(), ifstream::in);

	if (fe.fail()){
		cerr << "Error al abrir el fichero " << nombreDB << endl;
		exit(-1);
	}

	else {
		do{ 
			getline(fe,cadena,'\n'); 
		}while (cadena.find('#')!=string::npos && !fe.eof());

	
		while ( !fe.eof() ){ 
			mutacion mut;
			vector<enfermedad> enfs;
			enfs=mut.contruct_getEnfs(cadena);
			insert(make_pair(mut,enfs));
			getline(fe,cadena,'\n');
		}

	} 

	fe.close();

}


void clinvar::insert(const pair<mutacion,vector<enfermedad>>& x){

	auto itmut=mutDB.insert(x.first).first; // set::iterator// mutDB //
	IDm_map.insert(make_pair(x.first.getID(),itmut)); // IDm_map //  IDmutacion -> Mutacion

	for(auto i:x.second){
		EnfDB.insert(make_pair(i.getID(),i));  // EnfDB // IDenfermedad -> Enfermedad
		IDenf_map.insert(make_pair(i.getID(),itmut)); // IDenf_map // Enfermedad-> Mutacion
	}

	for(auto i:x.first.getGenes()){
		gen_map[i].push_back(itmut); // gen_map //
	}
}


bool clinvar::erase(IDmut ID){
	auto it=IDm_map.find(ID);

	if(it==IDm_map.end())
		return false;

	vector<enfermedad> enfs=getEnfermedades(*(it->second));

	it=IDm_map.find(ID);
	

	for(auto& enf:enfs){
		int i=IDenf_map.count(enf.getID());
		if(i==1)
			EnfDB.erase(enf.getID());
	}


	it=IDm_map.find(ID);

	for(auto it2=IDenf_map.begin();it2!=IDenf_map.end();){
		if(it2->second==it->second){
			auto aux=it2;
			++it2;
			IDenf_map.erase(aux);
		}
		else it2++;
	}

	it=IDm_map.find(ID);

	for(auto i:it->second->getGenes()){
		gen_map[i].remove(it->second);
	}


	it=IDm_map.find(ID);
	int del=IDm_map.erase(ID);

	if(!del)
		return false;


	mutDB.erase(it->second);

	return true;


}


clinvar::iterator clinvar::find_Mut(IDmut ID){
	clinvar::iterator itr;
	auto it=IDm_map.find(ID);


	if(it!=IDm_map.end()){
		itr.it=it->second;
	}
	else{
		itr=end();
	}
	return itr;
}


clinvar::enfermedad_iterator clinvar::find_Enf(IDenf ID){
	clinvar::enfermedad_iterator itr;
	itr=EnfDB.find(ID);
	return itr;
}


vector<enfermedad> clinvar::getEnfermedades(const mutacion & mut){
	vector<enfermedad> enfs;
	
	for(auto i:mut.getEnfermedades()){
		auto enf=EnfDB.find(i);
		if(enf!=EnfDB.end())
			enfs.push_back(enf->second);
	}

	return enfs;
}


list<IDenf> clinvar::getEnfermedades(string keyword){
	list<IDenf> listenf;
	clinvar::enfermedad_iterator it;
	
	for(it=ebegin();it!=eend();++it){
		if(it->second.nameContains(keyword))
			listenf.push_back(it->first);
	}

	return listenf;
}


set<IDmut> clinvar::getMutacionesEnf(IDenf ID){
	auto equal=IDenf_map.equal_range(ID);
	set<IDmut> setMut;

	for(auto it=equal.first;it!=equal.second;++it){
		setMut.insert(it->second->getID());
	}

	return setMut;
}


set<IDmut> clinvar::getMutacionesGen(IDgen ID){
	set<IDmut> setmut;

	auto it=gen_map.find(ID);
	
	if(it!=gen_map.end()){
		
		for(auto itr=it->second.begin();itr!=it->second.end();++itr)
			setmut.insert((*(*itr)).getID());
	}

	return setmut;
}


set<mutacion,ProbMutaciones> clinvar::topKMutaciones(int k,string keyword){
	list<IDenf> lst=getEnfermedades(keyword);
	

	priority_queue<mutacion,deque<mutacion>,ProbMutaciones> prio_queue;
	ProbMutaciones prob;
	unordered_set<IDmut> unset;

	int a=0;
	for(auto it=lst.begin();it!=lst.end();++it){
		multimap<IDenf,set<mutacion>::iterator>::iterator itr;
		auto equal=IDenf_map.equal_range(*it);
		for(itr=equal.first;itr!=equal.second;++itr){
			
			if(a<k){
				if((itr->second)->getCaf().size()!=0){
					if(unset.find( (itr->second)->getID() )== unset.end()){
						unset.insert( (itr->second)->getID() );	
						prio_queue.push(*(itr->second));
						++a;
					}
				}
			}			
			else if((itr->second)->getCaf().size()!=0){
				if(prob(*(itr->second),prio_queue.top())){
					if(unset.find( (itr->second)->getID() )== unset.end()){
						unset.insert((itr->second)->getID());
						prio_queue.pop();
						prio_queue.push(*(itr->second));
					}
				}

			}
		}
	}

	set<mutacion,ProbMutaciones> mut;

	unsigned int tama=prio_queue.size();

	for(unsigned int i=0;i<tama;++i){
		mut.insert(prio_queue.top());
		prio_queue.pop();
	}

	return mut;


}


clinvar::iterator clinvar::begin(){
	clinvar::iterator itr;
	itr.it=mutDB.begin();

	return itr;
}

clinvar::enfermedad_iterator clinvar::ebegin(){
	clinvar::enfermedad_iterator itr;
	itr=EnfDB.begin();

	return itr;
}

clinvar::gen_iterator clinvar::gbegin(){
	clinvar::gen_iterator itr;
	itr.itmap=gen_map.begin();
	itr.itlist=itr.itmap->second.begin();
	itr.ptrclinvar=this;

	return itr;
}

clinvar::iterator clinvar::end(){
	clinvar::iterator itr;
	itr.it=mutDB.end();

	return itr;
}

clinvar::enfermedad_iterator clinvar::eend(){
	clinvar::enfermedad_iterator itr;
	itr=EnfDB.end();

	return itr;
}

clinvar::gen_iterator clinvar::gend(){
	clinvar::gen_iterator itr;
	auto it=gen_map.end();
	--it;
	itr.itlist=it->second.end();
	itr.itmap=gen_map.end();
	itr.ptrclinvar=this;

	return itr;
}

clinvar::iterator clinvar::lower_bound(string cromosoma,unsigned int posicion){
	mutacion x;
	clinvar::iterator itr;
	x.setChr(cromosoma);
	x.setPos(posicion);

	itr.it=std::lower_bound(mutDB.begin(),mutDB.end(),x);

	return itr;

}

clinvar::iterator clinvar::upper_bound(string cromosoma,unsigned int posicion){
	mutacion x;
	clinvar::iterator itr;
	x.setChr(cromosoma);
	x.setPos(posicion);

	itr.it=std::upper_bound(mutDB.begin(),mutDB.end(),x);

	return itr;

}

clinvar::gen_iterator::gen_iterator(const gen_iterator& x){
	itmap=x.itmap;
	itlist=x.itlist;
	ptrclinvar=x.ptrclinvar;
}

const mutacion& clinvar::gen_iterator::operator*(){
	return *(*itlist);
}

clinvar::gen_iterator& clinvar::gen_iterator::operator++(){
	++itlist;
	if(itlist==itmap->second.end()){
		++itmap;
		if(itmap!=ptrclinvar->gen_map.end())
			itlist=itmap->second.begin();
	}

	return *this;
}

clinvar::gen_iterator  clinvar::gen_iterator::operator++(int){
	clinvar::gen_iterator aux(*this);
	++(*this);
	return aux;
}

bool  clinvar::gen_iterator::operator==(const gen_iterator& x){
	return itmap==x.itmap && itlist==x.itlist && ptrclinvar==x.ptrclinvar;
}

bool  clinvar::gen_iterator::operator!=(const gen_iterator& x){
	return !(*this==x);
}

clinvar::gen_iterator&  clinvar::gen_iterator::operator=(const gen_iterator& x){
	if(this!=&x){
		itmap=x.itmap;
		itlist=x.itlist;
		ptrclinvar=x.ptrclinvar;
	}

	return *this;
}