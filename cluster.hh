/**
 * @file cluster.hh
 * @brief Especificació de la classe cluster
 * 
 */

#ifndef CLUSTER_HH
#define CLUSTER_HH

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <iostream>
#include <map>
#include <string>
#endif

#include "procesor.hh"
using namespace std;

/** @class cluster
 * @brief Representa un cluster en forma d'arbre binari.
 * Està format per processadors i processos.
 */
class cluster{
private:
BinTree<string> c;
map<string, Procesor> m;
int time;

struct info{
  bool cap;
  int forat;
  int freemem;
  string idprocesor;
};
int best2 (info a, info b);
int best3 (info a, info b, info c);

public:

  // Constructores
  /**
   * @brief Crea un nou cluster inicialitzat
   * \pre *true*
   * \post S'ha inicialitzat un nou cluster.
   */
  cluster();

  /**
   * @brief Crea un nou cluster format pel pare p i els clusters fills le i ri
   * \pre *true*
   * \post S'ha inicialitzat un nou cluster format per dos clusters le i ri units per un pare p.
   * @param p Processador pare
   * @param le Fill esquerre del cluster
   * @param ri Fill dret del cluster
   *  
   */
  cluster(Procesor& p, cluster& le, cluster& ri);
  // Modificadores

  /**
   * @brief Llegeix els components d'un cluster.
   * \pre El cluster està inicialitzat i/o conte dades.
   * \post El cluster actual conté les dades introduides a l'entrada. </p> Si el cluster C contenía dades, aquestes s'han eliminat.
   */
  void read_cluster();

  /**
   * @brief Canvia les dades del processador amb identificador id per les del processador p.
   * \pre L'identificador de p == id i existeix un procesador al cluster amb identificador id.
   * \post 
   * 
   * @param id Identificador del processador que es vol modificar
   * @param p Processador pel qual es vol modificar
   */
  void modify_processor(string id, const Procesor& p);

  /**
   * @brief Insereix una nova branca al cluster.
   * \pre El processador arrel de c existeix a C, no te processos en execució ni processadors auxiliars.
   * \post Es retorna el cluster C amb el cluster c adherit al pricessador arrel.
   * @param c Cluster d'entrada amb un processador id que ja està dintre del cluster C
   */
  void insert_cluster(const map<string, Procesor>& newmap, const BinTree<string>& newbintree, const string& p);

  /**
   * @brief Intenta afegir el procès p al processador amb identificador id.
   * 
   * \pre *true*
   * \post S'afegeix el procès p al procesador id.
   * 
   * @param id Identificador del processador on es vol inserir el procès.
   * @param p Procès que es vol inserir.
   * @return *true* si el procès s'ha insertat al processador o aquest no existeix al cluster.
   * @return *false* si el procès no es pot insertar al processador o aquest no existeix al cluster.
   */
  int add_proces_directly(string id, Proces& p);

  /**
   * @brief Incrementa el temps del rellotge t unitats de temps.
   * \pre *true*
   * \post T = T + t.
   * 
   * @param t Unitats de temps que han transcorregut.
   */
  void increase_time(int t);

  /**
   * @brief Compacta la memòria de tots els processadors del cluster.
   * \pre El cluster està inicialitzat.
   * \post Es retorna el cluster amb la memòria de tots els processadors compactada.
   * 
   */
  void compact_memory();

  /**
   * @brief Elimina un procès d'un processador.
   * 
   * @param idprocesor Identificador del processador.
   * @param idproces  Identificador del procès.
   * @return *true* si el procès s'ha afegit al processador.
   * @return *false* si el procès no es pot afegir al processador.
   */
  int remove_proces(string idprocesor, string idproces);
  //Consultores

  /**
   * @brief Escriu els processados al canal de sortida.
   * \pre *true*
   * \post El canal de sortida conté les dades de tots els processadors del cluster.
   * 
   */
  void write_procesors();
  /**
   * @brief Retorna si el processador amb identificador existeix.
   * 
   * \pre Id es un string d'identificador vàlid
   * \post Retorna si el processador id existeix
   * @param id Identificador del processador
   * @return *true* si el processador existeix.
   * @return *false* si el processador no existeix.
   */
  bool exist(string id);
  
  /**
   * @brief Retorna una parella amb els processadors auxiliars de p.
   * \pre El processador p existeix al cluster.
   * \post Retorna els processadors auxiliars de p. Si un d'aquests està buit retorna processadors amb identificador -1.
   * 
   * @param p Procesador que existeix al cluster
   * @return pair<Procesor, Procesor> 
   */
  bool aux_procesors(const string& p);

  /**
   * @brief Cerca el processador amb identificador id.
   * 
   * \pre El procesador amb identificador id existeix al cluster.
   * \post Es retorna el processador id.
   * @param id Identificador del processador
   * @return Procesor
   */
  Procesor search_procesor(string id);

  /**
   * @brief Escriu l'estructura del cluster al canal de sortida.
   *\pre El cluster està inicialitzat.
   * \post L'estructura del cluster es troba al canal de sortida.
   * 
   */
  void write_structure();
  BinTree<string> bintree_cluster();
  map<string, Procesor> map_cluster();
  string where_add(string id, int mem);
  private:
  void write_i_procesor(const BinTree<string>& cl);
  void write_i_struct(const BinTree<string>& cl);
  void read(BinTree<string>& c);
  bool search(const BinTree<string>&cl, const string& p);
  BinTree<string> add(string k, const BinTree<string>& a, const BinTree<string>& n);
  void where_i_add(const BinTree<string>& t, info& space, int mem, string idproces);

};
#endif
