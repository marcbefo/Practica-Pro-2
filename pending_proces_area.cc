#include "pending_proces_area.hh"

bool proces_area::search(string idpri, string idproc){
    list<Proces> l = pr[idpri].proclist;
    for(auto it = l.begin(); it != l.end(); ++it){
        Proces p = *it;
        if (p.identifier()==idproc){
            return true;
        }
    }
    return false;
}

proces_area::proces_area(const vector<string>& p){
    int n = p.size();
    for (int i=0; i<n; ++i){
        pr[p[i]];
    }
}

bool proces_area::add_priority(string id){
    if(pr.find(id) == pr.end()){
        pr[id];
        return true;
    }
    return false;
}

int proces_area::remove_priority(string id){
    if(pr.find(id) == pr.end()) return 1;
    if ( not pr[id].proclist.empty()) return 2;
    pr.erase(pr.find(id));
    return 0;
}

int proces_area::add_proces(string id, Proces& p){
    if(pr.find(id) == pr.end()){
        return 1;
    }
    if(not search(id, p.identifier())){
        pr[id].proclist.push_back(p);
        return 0; 
    }
    return 2;
}

void proces_area::add_proces_to_cluster(cluster& c, int n){
   if (n == 0) return;
   for (auto itmap = pr.begin(); itmap != pr.end(); ++itmap){
    auto itlist = itmap->second.proclist.begin();
    while (itlist != itmap->second.proclist.end()){
        bool erased = false;
        Proces p = *itlist;
        string id = c.where_add(p.identifier(), p.memory());
        if (id == "..."){
            ++ itmap->second.rejected;
        }
        else {
            ++itmap->second.accepted;
            c.add_proces_directly(id, p);
            itlist = itmap->second.proclist.erase(itlist);
            erased = true;
        }
        if (not erased) ++itlist;
        --n;
        if (n == 0) return;
    }
   }
}

bool proces_area::exist_priority(string id){
    if(pr.find(id) == pr.end()) return false;
    return true;
}

void proces_area::write_priority(string id){
    list<Proces> l = pr[id].proclist;
    for(auto it = l.begin(); it != l.end(); ++it){
        Proces p = *it;
        p.write_proces();
    }
    cout << pr[id].accepted << " " << pr[id].rejected << endl;
}

void proces_area::write_pending_proces_area(){
     for (auto i = pr.begin(); i != pr.end(); i++){
        cout << i->first << endl;
        list<Proces> l = i->second.proclist;
         for(auto it = l.begin(); it != l.end(); ++it){
            Proces p = *it;
            p.write_proces();
        }
        cout <<  i->second.accepted << " " <<  i->second.rejected << endl;
     }
}
