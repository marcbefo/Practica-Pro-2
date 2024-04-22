#include "procesor.hh"    //molt semblant a classe estudiant

Procesor::Procesor(){
  id = "0";
  max_mem = 0;
}

Procesor:: Procesor(string id, int maxmem){
  this->id = id;
  max_mem = maxmem;
  freemem = maxmem;
  m3[maxmem].insert(0);
}

void Procesor::unify_free_memory(){       //swap xata
   m3.clear();
   int posicioActual = 0;
    for (auto it = m2.begin(); it != m2.end(); ++it) {
        int posicio = it->first;
        int espai = it->second.memory();

        if (posicio > posicioActual) {
            int espaiLliure = posicio - posicioActual;
            m3[espaiLliure].insert(posicioActual);
        }

        posicioActual = posicio + espai;
    }

    // Comprova l'espai lliure després de l'última entrada
    int ultimaPosicio = posicioActual;
    if (ultimaPosicio < max_mem) {
        int espaiLliure = max_mem - ultimaPosicio;
        m3[espaiLliure].insert(ultimaPosicio);
    }
}
  /*m3.clear();
  int pos = 0;
  if (m2.empty()){
    m3[max_mem].insert(0);
  }
  else{
    bool first = true;
   for (auto it = m2.begin(); it != m2.end(); ++it){
    if (first){
      if (it->first != 0){
      m3[it->first-1].insert(0);
      pos = (it->first) + (it->second.memory());
      ++it;
      if(it == m2.end()) return;
     }
     first = false;
    }
      if (pos == it->first){
        pos += it->second.memory();
      } 
      else if(pos < it->first){
        m3[pos].insert((it->first)-pos);
        pos = it->first;
      }
    }
  }
  */


//void Procesor::read_procesor(){}

void Procesor::compact_memory(){
  if (m2.empty() or m3.empty()) return;
  map <int, Proces> m2aux;
  int pos = 0;
  for(auto it = m2.begin(); it != m2.end(); ++it){
    m1[it->second.identifier()] = pos;
    m2aux[pos]= it->second;
    pos += it->second.memory();
  }
  m3[max_mem-pos+1].insert(max_mem-pos+1);
  m2 = m2aux;
}
  
bool Procesor::is_executing(){
  return not m1.empty();
}

string Procesor::identifier(){
  return id;
}

void Procesor::write(){
  for (auto it = m2.begin(); it != m2.end(); ++it){
    cout << it->first << " " << it->second.identifier() << " " << it->second.memory() << " " << it->second.remainingtime() << "/n";
  }
}

void Procesor::increase_time(int t){ // definir un map = m2 aux per a no editar m2 durant l'execució
  auto it = m2.begin();
  while (it != m2.end()){
    bool erased = false;
    if (m2[it->first].increase_time(t) <= 0){
      int inipos = it->first;
      int memory = it->second.memory();
      string idproces = it->second.identifier();
      m1.erase(idproces);
      it = m2.erase(it);
      m3[memory].insert(inipos); 
      unify_free_memory();
      erased = true;
      freemem = freemem + memory;
    }
    if (not erased) ++it;
  }
}

int Procesor::add_proces(Proces& p){
  int necesary_mem = p.memory();
  if (m1.find(p.identifier()) != m1.end()) return 2;
  if (m3.lower_bound(necesary_mem) == m3.end()) return 3;
  auto it = m3.lower_bound(necesary_mem);
  int pos = *(it->second.begin());
  int memory = it->first;
  if (memory > necesary_mem){
    m3[memory-necesary_mem].insert(pos+necesary_mem);
  }
  m3[memory].erase(pos);
  if(m3[memory].empty()) m3.erase(memory);
  m1[p.identifier()] = pos;
  m2[pos] = p;
  freemem -= necesary_mem;
  return 0;
}

int Procesor::maxmem(){
  return max_mem;
}

bool Procesor::remove_proces(string idproces){
  if (m1.find(idproces) == m1.end()) return false;
  auto it = m1.find(idproces);
  int inipos = it->second;
  int memory = m2[inipos].memory();
  m1.erase(idproces);
  m2.erase(inipos);
  m3[memory].insert(inipos);
  freemem += memory;
  unify_free_memory();
  return true;
}

pair <int, int> Procesor::fit (int mem){
  pair <int, int> out;
  auto it = m3.lower_bound(mem);
  if (it == m3.end()){
    out.first = -1;
    out.second = -1;
    return out;
  }
  out.first = it-> first - mem;
  out.second = freemem - mem;
  return out;
}

bool Procesor:: exist(string identifier){
  if (m1.find(identifier) == m1.end()) return false;
  return true;
}

