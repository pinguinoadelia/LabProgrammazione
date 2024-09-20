//
// Created by Michelino De Laurentiis on 19/09/24.
//

#ifndef LABPROGRAMMAZIONE_OBSERVER_H
#define LABPROGRAMMAZIONE_OBSERVER_H

#include <string>

class Observer {
public:
    virtual ~Observer() = default;

    virtual void onUpdate(const std::string& listName) = 0;
};


#endif //LABPROGRAMMAZIONE_OBSERVER_H
