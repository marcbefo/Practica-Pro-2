#include "proces.hh"

Proces::Proces(){
    id = "0";
    mem = 0;
    necesarytime = 0;
    timeleft = 0;
}
 
Proces::Proces(string id, int mem, int necesarytime){
    this->id = id;
    this->mem = mem;
    this->necesarytime = necesarytime;
    timeleft = necesarytime;
}

Proces::Proces(string id){
    this->id = id;
}

void Proces::read_proces(){
    string i;
    int m, t;
    cin >> i >> m >> t;
    id = i;
    mem = m;
    necesarytime = t;
    timeleft = t;
}

string Proces::identifier(){
    return id;
}

void Proces::write_proces(){
    cout << id << " " << mem << " " << timeleft << endl;
}

int Proces::memory(){
    return mem;
}

int Proces::increase_time(int t){
    timeleft -= t;
    return timeleft;
}
int Proces::remainingtime(){
    return timeleft;
}
