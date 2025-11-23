#ifndef OBSERVER_H
#define OBSERVER_H

///used to implement the Observer design pattern
///help the windows for biologist to stay sincronized

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Subject {
public:
    virtual void addObserver(Observer* obs) = 0;
    virtual void removeObserver(Observer* obs) = 0;
    virtual void notify() = 0;
    virtual ~Subject() = default;
};

#endif