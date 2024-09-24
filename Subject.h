
#ifndef LABPROGRAMMAZIONE_SUBJECT_H
#define LABPROGRAMMAZIONE_SUBJECT_H

#include "Observer.h"

class Subject {
public:
    //distruttore della classe dichiarato come virtuale per poter gestire correttamente la memoria
    virtual ~Subject() = default;

    //aggiunge un osservatore alla lista degli osservatori
    virtual void addObserver(Observer* observer) = 0;

    //rimuove un osservatore dalla lista degli osservatori
    virtual void removeObserver(Observer* observer) = 0;

    //notifica tutti gli osservatori registrati di un cambiamento
    virtual void notifyObservers() = 0;
};


#endif //LABPROGRAMMAZIONE_SUBJECT_H
