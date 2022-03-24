#ifndef _PAIR_HPP_
#define _PAIR_HPP_

template <class T1, class T2>
class Pair {
private:
    T1 first;
    T2 second;
public:
    Pair() {}
    Pair(T1 first, T2 second) {
        this->first = first;
        this->second = second;
    }
    T1 getFirst() const {
        return this->first;
    }
    T2 getSecond() const {
        return this->second;
    }
    void setFirst(T1 first) {
        this->first = first;
    }
    void setSecond(T2 second) {
        this->second = second;
    }
};

#endif