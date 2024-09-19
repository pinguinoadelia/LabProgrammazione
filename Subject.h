//
// Created by Michelino De Laurentiis on 19/09/24.
//

#ifndef LABPROGRAMMAZIONE_SUBJECT_H
#define LABPROGRAMMAZIONE_SUBJECT_H

#include "Observer.h"

class Subject {
public:
    virtual ~Subject()=default;

    virtual void attach(Observer* o)=0;

    virtual void detach(Observer* o)=0;

    virtual void notify()=0;
};


#endif //LABPROGRAMMAZIONE_SUBJECT_H
