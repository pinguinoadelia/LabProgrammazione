//
// Created by Michelino De Laurentiis on 19/09/24.
//

#ifndef LABPROGRAMMAZIONE_SUBJECT_H
#define LABPROGRAMMAZIONE_SUBJECT_H

#include "Observer.h"

class Subject {
public:
    virtual ~Subject() = default;

    virtual void addObserver(Observer* observer) = 0;

    virtual void removeObserver(Observer* observer) = 0;

    virtual void notifyObservers() = 0;
};


#endif //LABPROGRAMMAZIONE_SUBJECT_H
