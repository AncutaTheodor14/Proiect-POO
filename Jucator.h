//
// Created by Theo on 5/27/2024.
//

#ifndef OOP_JUCATOR_H
#define OOP_JUCATOR_H

#include<iostream>
#include "Persoana.h"

class Jucator : public Persoana {
private:
    std::string Pozitie;
    int NrGoluri, NrAssisturi, SkillGeneral;

    void afisare(std::ostream &os) const override;

public:
    explicit Jucator(const std::string &nume, const std::string &echipa, bool transf, const std::string &pozitie,
                     int nrgoluri, int nrassisturi, int skillgen);

    std::shared_ptr<Persoana> clone() const override;

    int getskill() const;

    void adauga_gol(int nrgoluri);

    void adauga_assisturi(int nrassisturi);

    void Skill_Jucator();

    void antreneaza();
};


#endif //OOP_JUCATOR_H
