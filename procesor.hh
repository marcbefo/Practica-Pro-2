/**
 * @file procesor.hh
 * @brief Especificació de la classe processador
 * 
 */

#ifndef PROCESOR_HH
#define PROCESOR_HH
 
#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <iostream>
#include <vector>
#include <utility>
#include <list>
#include <map>
#include <set>
#endif

#include "proces.hh"
using namespace std;
/** @class Procesor
 * @brief Representa un processador.
 * Format per una identificació, una memòria i una llista de processos.
 * 
 */
class Procesor{
private:
string id;
int max_mem;
int freemem;
map <string, int> m1;      // id proces, posicó inicial
map <int, Proces> m2;      // posició inicial, proces
map <int, set<int>> m3;  // memoria lliure, posició on es troba
void unify_free_memory();

public:
  //Constructores
  Procesor();

  Procesor(string id, int maxmem);
  //Modificadores
  /**
   * @brief Llegeix les dades del processador del sistema d'entrada
   * \pre *true*
   * \post Les dades del sistema d'entrada estan desades al P.I.
   * 
   */
  void read_procesor();

  /**
   * @brief Compacta la memoria del processador.
   * \pre *true*
   * \post Es retorna el mateix processador amb la memòria compactada.
   */
  void compact_memory();
  //Consultores

/**
 * @brief Retorna si s'esta executant algun proces
 * 
 * \pre *true*
 * \post Retorna si s'esta executant algun procès.
 * @return *true* si s'età executant algún procès.
 * @return *false* si no s'està executant cap procès.
 */
  bool is_executing();

/**
 * @brief Retorna l'identificador del processador.
 * \pre *true*
 * \post Retorna l'identificador del processador.
 * 
 */
  string identifier();

  /**
   * @brief Escriu les dades del processdor al canal de sortida.
   * \pre El procesador està inicialitzat.
   * \post El canal de sortida conté les dades del procesador.
   * 
   */
  void write();

  int maxmem();

  int add_proces(Proces& p);

  void increase_time(int t);

  bool remove_proces(string idproces);

/*
 * first == -1 si no cap 
 *    else si cap, first = mida forat
 *  second == memòria lliure despres del procès.
 * 
 */
  pair <int, int> fit(int mem);
bool exist(string identifier);
};
#endif