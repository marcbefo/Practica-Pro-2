/**
 * @file proces.hh
 * @brief Esprcificació de la classe procès
 * 
 */

#ifndef PROCES_HH
#define PROCES_HH

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <iostream>
#include <string>
#endif

using namespace std;
/** @class Proces
 * @brief Representa un procès
 * format per un identificador, una prioritat, el temps necessari, l'espai que ocupa a memòria i el temps actual
 * 
 */
class Proces{
private:
string id;
int mem;
int necesarytime;
int timeleft;

public:
//Constructores
    Proces();
    Proces(string id, int mem, int necessarytime);
    Proces(string id);
//Modificadores

    /**
     * @brief Llegeix les dades d'un procès del canal d'entrada.
     * 
     * \pre *true*
     * \post Les dades introduides es troben al P.I.
     * 
     */
    void read_proces();
//Consultores

    string identifier();

    int memory();

    /**
     * @brief Escriu les dades del procès al canal de sortida.
     * \pre *true*
     * \post Les dades del procès es troben al canal de sortida.
     * 
     */
    void write_proces();

    int remainingtime();

    int increase_time(int t);
};
#endif