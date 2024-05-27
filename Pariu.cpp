//
// Created by Theo on 5/27/2024.
//

#include "Pariu.h"

Pariu::Pariu(const std::string &nume, const std::string &echipa, double suma, double su, bool cast)
        : NumeParior(nume), EchipaPariata(echipa), SumaPariata(suma), sumaCastigata(su), castigator(cast) {}

std::string Pariu::getNumeParior() const {
    return NumeParior;
}

void Pariu::suma_Castigata(double &&x) {
    sumaCastigata = x;
}

double Pariu::val_suma_Castigata() const {
    return sumaCastigata;
}

std::string Pariu::getEchipaPariata() const {
    return EchipaPariata;
}

double Pariu::getSumaPariata() const {
    return SumaPariata;
}

bool Pariu::isCastigator() const {
    return castigator;
}

void Pariu::setCastigator(bool status) {
    castigator = status;
}
