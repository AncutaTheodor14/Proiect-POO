//
// Created by Theo on 5/27/2024.
//

#include "Campionat_Liga_Nationala.h"
#include "Echipa.h"
#include "Meci.h"
#include "Exceptii.h"

Campionat_Liga_Nationala::Campionat_Liga_Nationala(int nrechipe, int nretape) : NrEchipe{nrechipe}, NrEtape{nretape},
                                                                                echipe{}, meciuri{} {}

Campionat_Liga_Nationala::Campionat_Liga_Nationala(const Campionat_Liga_Nationala &other) : NrEchipe{other.NrEchipe},
                                                                                            NrEtape{other.NrEtape},
                                                                                            echipe{other.echipe},
                                                                                            meciuri{other.meciuri} {}

Campionat_Liga_Nationala &Campionat_Liga_Nationala::operator=(const Campionat_Liga_Nationala &other) {
    NrEchipe = other.NrEchipe;
    NrEtape = other.NrEtape;
    echipe = other.echipe;
    meciuri = other.meciuri;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Campionat_Liga_Nationala &m) {
    os << "Nr_Echipe: " << m.NrEchipe << ", Nr_Etape: " << m.NrEtape << '\n';
    for (auto it: m.echipe)
        os << it.get_num() << '\n';
    os << '\n';
    return os;
}

void Campionat_Liga_Nationala::adaug_echipa(Echipa &ech) {
    int var = ech.get_juc().size();
    if (var < 1 || var >= 14)
        throw eroare_numar_jucatori(var);
    echipe.emplace_back(ech);
}

void Campionat_Liga_Nationala::adaug_meci(Meci &game) {
    meciuri.emplace_back(game);
}
