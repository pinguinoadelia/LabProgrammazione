//
// Created by Michelino De Laurentiis on 19/09/24.
//

#ifndef LABPROGRAMMAZIONE_OBSERVER_H
#define LABPROGRAMMAZIONE_OBSERVER_H

#include <string>

class Observer {
public:
    //distruttore della classe dichiarato come virtuale per poter gestire correttamente la memoria
    virtual ~Observer() = default;

    //metodo che viene sovrascritto nelle classi derivate che serve a notificare un aggiornamento
    //della lista specificata
    virtual void onUpdate(const std::string& listName) = 0;
};


#endif //LABPROGRAMMAZIONE_OBSERVER_H
