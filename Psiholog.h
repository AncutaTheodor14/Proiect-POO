//
// Created by Theo on 5/29/2024.
//

#ifndef OOP_PSIHOLOG_H
#define OOP_PSIHOLOG_H

#include<iostream>
#include "Persoana.h"

class Psiholog : public Persoana {
private:
    int aniExperienta;

    void afisare(std::ostream &os) const override {
        os << ", Rol: Psiholog, Ani de experienta: " << aniExperienta << '\n';
    }

public:
    explicit Psiholog(const std::string &nume, const std::string &echipa, bool transf, int aniExp)
            : Persoana(nume, echipa, transf), aniExperienta(aniExp) {}

    std::shared_ptr<Persoana> clone() const override {
        return std::make_shared<Psiholog>(*this);
    }

    double cost_deplasare(int factor_urgenta, int distanta) const override {
        double Cost_initial = 70 + aniExperienta;
        int optional = 1;
        if (distanta > 1000)
            optional = 2;
        return Cost_initial * factor_urgenta * optional;
    }
};


#endif //OOP_PSIHOLOG_H
