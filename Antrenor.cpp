//
// Created by Theo on 5/27/2024.
//

#include "Antrenor.h"
#include<iostream>

Antrenor::Antrenor(const std::string &Nume, const std::string &NE, bool transf, int EA) : Persoana(Nume, NE, transf),
                                                                                          EchipeAntrenate(EA) {}

std::shared_ptr<Persoana> Antrenor::clone() const {
    return std::make_shared<Antrenor>(*this);
}

void Antrenor::afisare(std::ostream &os) const {
    os << ". Are rolul de antrenor si a antrenat pana acum " << EchipeAntrenate << " echipe." << '\n';
}
