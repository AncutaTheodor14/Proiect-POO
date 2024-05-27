//
// Created by Theo on 5/27/2024.
//

#ifndef OOP_PARIU_H
#define OOP_PARIU_H

#include<iostream>
#include<string>

class Pariu {
    std::string NumeParior;
    std::string EchipaPariata;
    double SumaPariata = 0;
    double sumaCastigata = 0;
    bool castigator;
public:
    Pariu(const std::string &nume, const std::string &echipa, double suma, double su = 0, bool cast = false);

    std::string getNumeParior() const;

    void suma_Castigata(double &&x);

    double val_suma_Castigata() const;

    std::string getEchipaPariata() const;

    double getSumaPariata() const;

    bool isCastigator() const;

    void setCastigator(bool status);
};


#endif //OOP_PARIU_H
