//
// Created by Theo on 5/27/2024.
//

#ifndef OOP_PARIU_H
#define OOP_PARIU_H

#include<iostream>
#include<string>

template<typename T>
class Pariu {
    std::string NumeParior;
    std::string EchipaPariata;
    T SumaPariata;
    T sumaCastigata;
    bool castigator;
public:
    Pariu(const std::string &nume, const std::string &echipa, T suma, T su = 0, bool cast = false) : NumeParior(nume),
                                                                                                     EchipaPariata(
                                                                                                             echipa),
                                                                                                     SumaPariata(suma),
                                                                                                     sumaCastigata(su),
                                                                                                     castigator(cast) {}

    std::string getNumeParior() const {
        return NumeParior;
    }

    void suma_Castigata(T &&x) {
        sumaCastigata = x;
    }

    T val_suma_Castigata() const {
        return sumaCastigata;
    }

    std::string getEchipaPariata() const {
        return EchipaPariata;
    }

    T getSumaPariata() const {
        return SumaPariata;
    }

    bool isCastigator() const {
        return castigator;
    }

    void setCastigator(bool status) {
        castigator = status;
    }
};


#endif //OOP_PARIU_H
