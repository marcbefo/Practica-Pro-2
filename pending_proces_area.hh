/**
 * @file pending_proces_area.hh
 * @brief Especificació de l'area de processos pendents
 * 
 */

#ifndef PENDING_PROCES_AREA_HH
#define PENDING_PROCES_AREA_HH

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <iostream>
#include <set>
#include <map>
#endif

#include "proces.hh"
#include "cluster.hh"
/** @class proces_area
 * @brief Representa una area de processos pendents.
 * Formada per una llista de programes ordenada per prioritat
 * 
 */
class proces_area{
private:
struct Priority{
  int accepted = 0;
  int rejected = 0;
  list<Proces> proclist;
};
map <string,Priority> pr;

bool search(string idpri, string idproc);

public:

//Consutuctor

  /**
   * @brief Construeix una nova area de procesos pendents.
   * \pre p es un conjunt no buit d'identificadors de prioritat.
   * \post S'ha creat l'objecte amb p al parametre implicit.
   * 
   * @param p
   */
  proces_area(const vector<string>& p);

  //Modificadores

  /**
 * @brief Afegeix la prioritat id al conjunt de prioritats.
 * \pre *true*
 * \post S'afegeix la prioritat id al conjunt de prioritats.

 * @param id Idenificador de prioritat
 * @return *true* si l'identificador s'ha afegit a la llista de prioritats
 * @return *false* si l'identificador no es pot afegir a la llista de prioritats
 */
  bool add_priority(string id);

  /**
 * @brief Elimina la prioritat id del conjunt de prioritats.
 * \pre *true*
 * \post Retorna l'area de processos pendents amb els processos de prioritat id eliminats.
 * 
 * @param id identificador de prioritats
 * @return *true* si l'identificador s'ha esborrat de la llista de prioritats.
 * @return *false* si l'identificador no es pot esborrar de la llista de prioritats.
 */
  int remove_priority(string id);
  
  /**
   * @brief Afegeix un procès a l'area de processos pendents
   * \pre *true*
   * \post Retorna l'area de processos pendents amb els processos de prioritat id eliminats.
   * 
   * @param p Procès que s'ha d'afegir a l'àrea
   * @param id Identificador de prioritat
   * @return *true* si el procès s'ha afegit a la llista de prioritats
   * @return *false* si el procès no es pot afegir a la llista de prioritats 
   */
  int add_proces(string id, Proces& p);

  /**
   * @brief Afegeix el procès més antic i amb més prioritat a c.
   * 
   *\pre *true*
   *\post EL proès més antic i amb més prioritat ah sigut afegit a c.
   * 
   * @param c Cluster on s'ha d'agefit el procès de l'àrea de processos pendents.
   * 
   * @return *true* si es pot afegir el procès.
   * @return *false* si no es pot afegir el procès.
   */
  void add_proces_to_cluster(cluster& c, int n);
  //Consultores

  /**
   * @brief Retorna si l'identificador existeix en el conjunt de prioritats
   * \pre *true*
   * \post Retorna si l'identificador existeix en el conjunt de prioritats.
   * 
   * @param id Identificador de prioritat.
   * @return *true* si l'identificador s'ha afegit a la llista de prioritats.
   * @return *false* si l'identificador no es pot afegir a la llista de prioritats.
   */
  bool exist_priority(string id);

  /**
   * @brief Escriu la llista de la prioritat id.
   * \pre *true*
   * \post La llista de prioritats es troba al canal de sortida.
   * @param id Identificador de prioritat.
   * 
   */
  void write_priority(string id);

  /**
   * @brief Esctiu l'area de processos pendents al canal de sorida.
   * 
   * \pre L'area de processos ha d'estar inicialitda.
   * \post S'escriu la llista de procesos al canal de sortida.
   * 
   */
  void write_pending_proces_area();
};
#endif
