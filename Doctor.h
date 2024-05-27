//
// Created by Theo on 5/28/2024.
//

#ifndef OOP_DOCTOR_H
#define OOP_DOCTOR_H


#include<iostream>
#include "Persoana.h"

class Doctor : public Persoana {
private:
    int aniExperienta;
    std::string specializare;

    void afisare(std::ostream &os) const override;

public:
    explicit Doctor(const std::string &nume, const std::string &echipa, bool transf, const std::string &spec,
                    int aniExp);

    std::shared_ptr<Persoana> clone() const override;
};


#endif //OOP_DOCTOR_H
