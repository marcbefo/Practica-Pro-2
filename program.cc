/**
 * @file main.cc
 * @author Marc Bel Fonollosa (marc.bel.fonollosa@estudiantat.upc.edu)
 * @brief Programa principal de la practica simulació del rendiment de processadors interconectats
 * @version Especificació
 * @date 05-04-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <iostream>
#include <set>
#endif

#include "cluster.hh"
#include "pending_proces_area.hh"
using namespace std;

int main(){
  cluster c;
  c.read_cluster();
  // Llegim la llista de prioritats
  int n;
  cin >> n;
  vector<string> priorities (n);
  for (int i = 0; i<n; ++i){
    string in;
    cin >> in;
    priorities[i]=in;
  }
  proces_area a (priorities);
  // Bucle de comandes
  string comand;
  cin >> comand;
  while (comand != "fin"){
    if(comand == "configurar_cluster" or comand == "cc"){
      cout << "#" << comand << "/n";
      cluster copy;
      copy.read_cluster();
      c = copy;
    }
    else if(comand == "modificar_cluster" or comand == "mc"){
      string id;
      cin >> id;
      cout << "#" << comand << " " << id << "/n";
      cluster n;
      n.read_cluster();
      if (c.exist(id)){
        Procesor p = c.search_procesor(id);
        if(not p.is_executing()){
             if (c.aux_procesors(id)){
                c.insert_cluster(n.map_cluster(), n.bintree_cluster(), id);
             }
             else cout << "error: procesador con auxiliares" << "/n";
        }
        else cout << "error: procesador con procesos" << "/n";
      }
      else cout << "error: no existe procesador" << "/n";
    }
    else if(comand == "alta_prioridad" or comand == "ap"){
      string id;
      cin >> id;
      cout << "#" << comand << " " << id << "/n";
      if(not a.add_priority(id)) cout << "error: ya existe prioridad" << "/n";
    }
    else if(comand == "baja_prioridad" or comand == "bp"){
      string id;
      cin >> id;
      cout << "#" << comand << " " << id << "/n";
      int error = a.remove_priority(id);
      if (error == 1) cout << "error: no existe prioridad" << "/n";
      else if (error == 2) cout << "error: prioridad con procesos" << "/n";
    }
    else if(comand == "alta_proceso_espera" or comand == "ape"){
      string id;
      cin >> id;
      Proces p;
      p.read_proces();
      cout << "#" << comand << " " << id << " " << p.identifier() << "/n";
      int error = a.add_proces(id, p);
      if (error == 1) cout << "error: no existe prioridad" << "/n";
      else if (error == 2) cout << "error: ya existe proceso" << "/n";
    }
    else if(comand == "alta_proceso_procesador" or comand == "app"){
      string idprocesor;
      cin >> idprocesor;
      Proces p;
      p.read_proces();
      cout << "#" << comand << " " << idprocesor << " " << p.identifier() << "/n";
      int error = c.add_proces_directly(idprocesor, p);
      if (error == 1) cout << "error: no existe procesador" << "/n";
      else if (error == 2) cout << "error: ya existe proceso" << "/n";
      else if (error == 3) cout << "error: no cabe proceso" << "/n";
    }
    else if(comand == "baja_proceso_procesador" or comand == "bpp"){
      string idprocesor, idproces;
      cin >> idprocesor >> idproces;
      cout << "#" << comand << " " << idprocesor << " " << idproces << "/n";
      int error = c.remove_proces(idprocesor, idproces);
      if (error == 1) cout << "error: no existe procesador" << "/n";
      else if (error == 2) cout << "error: no existe proceso" << "/n";

      if (not c.remove_proces(idprocesor, idproces)) cout << error << "/n";
    }
    else if(comand == "enviar_procesos_cluster" or comand == "epc"){
      int n;
      cin >> n;
      cout << "#" << comand << " " << n << "/n";
      a.add_proces_to_cluster(c, n);
    }
    else if(comand == "avanzar_tiempo" or comand == "at"){
      int t;                
      cin >> t;
      cout << "#" << comand << " " << t << "/n";            
      c.increase_time(t);
    }
    else if(comand == "imprimir_prioridad" or comand == "ipri"){
      string id;
      cin >> id;
      cout << "#" << comand << " " << id << "/n";
      if (a.exist_priority(id)) a.write_priority(id);
      else cout << "error: no existe prioridad" << "/n";
    }
    else if(comand == "imprimir_area_espera" or comand == "iae"){
      cout << "#" << comand << "/n";
      a.write_pending_proces_area();
    }
    else if(comand == "imprimir_procesador" or comand == "ipro"){
      string id;
      cin >> id;
      cout << "#" << comand << " " << id << "/n";
      if (c.exist(id)){
        Procesor pro = c.search_procesor(id);
        pro.write();
      }
      else cout << "error: no existe procesador" << "/n";
    }
    else if(comand == "imprimir_procesadores_cluster" or comand == "ipc"){
      cout << "#" << comand << "/n";
      c.write_procesors();
    }
    else if(comand == "imprimir_estructura_cluster" or comand == "iec"){
      cout << "#" << comand << "/n";
      c.write_structure();
    }
    else if(comand == "compactar_memoria_procesador" or comand == "cmp"){
      string id;
      cin >> id;
      cout << "#" << comand << " " << id << "/n";
      if(c.exist(id)){
        Procesor pro = c.search_procesor(id);
        pro.compact_memory();
        c.modify_processor(id, pro);
      }
      else cout << "error: no existe procesador" << "/n";;
    }
    else if(comand == "compactar_memoria_cluster" or comand == "cmc"){
      cout << "#" << comand << "/n";
      c.compact_memory();
    }
    cin >> comand;
  }
}
