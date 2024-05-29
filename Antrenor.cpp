//
// Created by Theo on 5/27/2024.
//

#include "Antrenor.h"

Antrenor::Antrenor(const std::string &Nume, const std::string &NE, bool transf, int EA) : Persoana(Nume, NE, transf),
                                                                                          EchipeAntrenate(EA) {}

std::shared_ptr<Persoana> Antrenor::clone() const {
    return std::make_shared<Antrenor>(*this);
}

void Antrenor::afisare(std::ostream &os) const {
    os << ". Are rolul de antrenor si a antrenat pana acum " << EchipeAntrenate << " echipe." << '\n';
}

double Antrenor::cost_deplasare(int factor_urgenta, int distanta) const {
    double cost_initial = 90 + 20 * EchipeAntrenate;
    double optional = 1;
    if (distanta > 300)
        optional += 150;
    return cost_initial * optional * factor_urgenta;
}
