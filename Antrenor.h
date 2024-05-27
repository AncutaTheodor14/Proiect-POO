//
// Created by Theo on 5/27/2024.
//

#ifndef OOP_ANTRENOR_H
#define OOP_ANTRENOR_H


#include "Persoana.h"
#include<iostream>

class Antrenor : public Persoana {
public:
    explicit Antrenor(const std::string &Nume, const std::string &NE, bool transf, int EA);

    std::shared_ptr<Persoana> clone() const override;

private:
    int EchipeAntrenate;

    void afisare(std::ostream &os) const override;
};


#endif //OOP_ANTRENOR_H
