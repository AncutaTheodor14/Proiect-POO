//
// Created by Theo on 5/28/2024.
//

#include "Doctor.h"

void Doctor::afisare(std::ostream &os) const {
    os << ", Rol: Doctor, " << "Specializare: " << specializare << ", Ani de experienta: " << aniExperienta << '\n';
}

Doctor::Doctor(const std::string &nume, const std::string &echipa, bool transf, const std::string &spec, int aniExp)
        : Persoana(nume, echipa, transf), aniExperienta(aniExp), specializare(spec) {}

std::shared_ptr<Persoana> Doctor::clone() const {
    return std::make_shared<Doctor>(*this);
}

double Doctor::cost_deplasare(int factor_urgenta, int distanta) const {
    int cost_initial = 200 + 10 * aniExperienta + 2 * specializare.size();
    double optional = 1;
    if (distanta > 250)
        optional += 200.50;
    return cost_initial * factor_urgenta * optional;
}
