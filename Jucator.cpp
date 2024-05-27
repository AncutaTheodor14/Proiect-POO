//
// Created by Theo on 5/27/2024.
//

#include "Jucator.h"

void Jucator::afisare(std::ostream &os) const {
    os << ", Rol: Jucator, " << "_Pozitie: " << Pozitie << ", " << "Nr_Goluri: " << NrGoluri << ", "
       << "Nr_Assisturi: " << NrAssisturi << ", " << "Skill_General: " << SkillGeneral << '\n';
}

Jucator::Jucator(const std::string &nume, const std::string &echipa, bool transf, const std::string &pozitie,
                 int nrgoluri, int nrassisturi, int skillgen) : Persoana(nume, echipa, transf), Pozitie(pozitie),
                                                                NrGoluri(nrgoluri), NrAssisturi(nrassisturi),
                                                                SkillGeneral(skillgen) {}

std::shared_ptr<Persoana> Jucator::clone() const {
    return std::make_shared<Jucator>(*this);
}

int Jucator::getskill() const {
    return SkillGeneral;
}

void Jucator::adauga_gol(int nrgoluri) {
    NrGoluri += nrgoluri;
}

void Jucator::adauga_assisturi(int nrassisturi) {
    NrAssisturi += nrassisturi;
}

void Jucator::Skill_Jucator() {
    SkillGeneral += NrGoluri / 5 + NrAssisturi / 7;
}

void Jucator::antreneaza() {
    SkillGeneral += 2;
}
