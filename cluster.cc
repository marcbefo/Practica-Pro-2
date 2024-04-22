#include "cluster.hh"
#include <map>
#include <utility>
#include <string>

cluster::cluster(){
    string dada = "0";
    c = BinTree<string>(dada);
    time = 0;
}

//cluster::cluster(Procesor& p, cluster& le, cluster& ri){}

void cluster::read_cluster(){
    read(c);

}

void cluster::modify_processor(string id, const Procesor& p){
    auto it = m.find(id);
    it -> second = p;
}

void cluster::insert_cluster(const map<string, Procesor>& newmap, const BinTree<string>& newbintree, const string& p){
    c = add(p, c, newbintree);
    m.insert(newmap.begin(), newmap.end());
    m.erase(p);
}

int cluster::add_proces_directly(string idpro, Proces& p){
    if (m.find(idpro) == m.end()) return 1;
    return m[idpro].add_proces(p);
}

void cluster::increase_time(int t){
    time += t;
    for (auto i = m.begin(); i != m.end(); i++){
        i->second.increase_time(t);
    }
}

void cluster::compact_memory(){
    for (auto it = m.begin(); it != m.end(); ++it){
        it->second.compact_memory();
    }
}

int cluster::remove_proces(string idprocesor, string idproces){
    if (m.find(idprocesor) == m.end()) return 1;
    if (not m[idprocesor].remove_proces(idproces)) return 2;
    return 0;
}

void cluster::write_procesors(){
    for (auto it = m.begin(); it != m.end(); ++it){
        cout << it->first << "/n";
        it->second.write();
    }
}

bool cluster::exist(string id){
    if (m.find(id) == m.end()) return false;
    return true;
}
  
bool cluster::aux_procesors(const string& p){
    return search(c, p);
}

Procesor cluster::search_procesor(string id){
    return m[id];
}

void cluster::write_structure(){
    write_i_struct(c);
    cout << "/n";
}

string cluster::where_add(string id, int mem){
    info best;
    where_i_add(c, best, mem, id);
    if (best.cap) return best.idprocesor;
    return "...";
}

void cluster::write_i_procesor(const BinTree<string>& cl){
    if (not cl.empty()){
        cout << cl.value() << "/n";
        m[cl.value()].write();
        BinTree<string> le = cl.left();
        BinTree<string> ri = cl.right();
        write_i_procesor(le);
        write_i_procesor(ri);
    }
}


void cluster::write_i_struct(const BinTree<string>& cl){
    if (cl.empty()) cout << " ";
    else{
        cout << "(";
        cout << cl.value();
        BinTree<string> le = cl.left();
        BinTree<string> ri = cl.right();
        write_i_struct(le);
        write_i_struct(ri);
        cout << ")";
    }
}

void cluster::read(BinTree<string>& cl){
    string s;
    int num;
    cin >> s;
    if (s != "*"){
        cin >> num;
        m[s]=Procesor(s, num);
        BinTree<string> le, ri;
        read(le);
        read(ri);
        cl = BinTree<string>(s, le, ri);
    }

}

bool cluster::search(const BinTree<string>&cl, const string& p){
    if (cl.empty()) return true;
    if (cl.value() == p){
        if (cl.left().empty() and cl.right().empty()) return true;
        return false;
    }
    return search(cl.left(), p) or search(cl.right(), p);

}

BinTree<string>  cluster::add(string k, const BinTree<string>& a, const BinTree<string>& n) {
/* Pre: cert */
/* Post: El valor de cada node del resultat és la suma del valor del node
corresponent d’a i el valor k */
if (a.empty()) return BinTree<string>();
if (a.value() == k) return n;
else {
return BinTree<string>(a.value(), add(k, a.left(), n), add(k, a.right(), n));
}
}
BinTree<string> cluster::bintree_cluster(){
    return c;
}

 map<string, Procesor> cluster::map_cluster(){
    return m;
 }

 void cluster::where_i_add(const BinTree<string>& t, info& space, int mem, string idproces){
    if(t.empty()){      // cas base t es buit
        space.cap = false;
        return;
    }
    if(t.left().empty() and t.right().empty()){   // cas base t no te fills
        if(not m[t.value()].exist(idproces)){
            pair <int, int> p = m[t.value()].fit(mem);
            if(p.first == -1){
                space.cap = false;
                return;
            }
            space.idprocesor = t.value();
            space.forat = p.first;
            space.freemem = p.second;
            space.cap = true;
            return;
        }
        else {
            space.cap = false;
            return;
        }
    }
    // pas inductiu
    if (t.left().empty() xor t.right().empty()){    // cas inductiu t té 1 fill
        info bestvalue, bestson;
        pair <int, int> p = m[t.value()].fit(mem);
        if (p.first == -1){
            bestvalue.cap = false;
        }
        else {
            bestvalue.idprocesor = t.value();
            bestvalue.forat = p.first;
            bestvalue.freemem = p.second;
            bestvalue.cap = true;
        }
        if(t.left().empty()){
            where_i_add(t.right(), bestson, mem, idproces);
        }
        else where_i_add(t.left(), bestson, mem, idproces);
        if (best2(bestvalue, bestson) == 1){
            space = bestvalue;
            return;
        }
        else{
            space = bestson;
            return;
        }
    }
    // cas inductiu t té 2 fills
    info bestvalue, bestle, bestri;
    pair <int, int> p = m[t.value()].fit(mem);
    if (p.first == -1){
        bestvalue.cap = false;
    }
    else {
        bestvalue.idprocesor = t.value();
        bestvalue.forat = p.first;
        bestvalue.freemem = p.second;
        bestvalue.cap = true;
    }
    where_i_add(t.left(), bestle, mem, idproces);
    where_i_add(t.right(), bestri, mem, idproces);
    if(best2(bestle, bestri) == 1){
        if (best2(bestvalue, bestle) == 1){
            space = bestvalue;
            return;
        }
        else{
            space = bestle;
            return;
        }
    }
    else {
        if (best2(bestvalue, bestri) == 1){
            space = bestvalue;
            return;
        }
        else{
            space = bestri;
            return;
        }
    }
    return;
    }

 int cluster::best2(info a, info b){
    if (not a.cap) return 2;
    if (not b.cap) return 1;
    if (not a.cap and not b.cap) return 1;
    if (a.forat == b.forat and a.freemem == b.freemem) return 1;
    if (a.forat < b.forat) return 1;
    if (a.forat > b.forat) return 2;
    if (a.freemem > b.freemem) return 1;
    if (a.freemem < b.freemem) return 2;
    return 0;
 }

int cluster::best3(info a, info b, info c){
    int n = best2(a, b);
    if (n == 1){
        n = best2(a, b);
        if (n == 1) return 1;
        else return 2;
    }
    n = best2(b, c);
    if (n == 1) return 2;
    return 3;
    
}