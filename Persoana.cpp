//
// Created by Theo on 5/27/2024.
//
#include<iostream>
#include <string>
#include "Persoana.h"

void Persoana::afisare(std::ostream &) const {}

Persoana::Persoana(const std::string &Nume1, const std::string &NE, bool transferabil_) : Nume(Nume1),
                                                                                          NumeEchipa(NE),
                                                                                          transferabil(
                                                                                                  transferabil_) {}

std::ostream &operator<<(std::ostream &os, const Persoana &pers) {
    os << pers.Nume << " este la echipa " << pers.NumeEchipa << ", transferabil = " << pers.transferabil;
    pers.afisare(os);
    return os;
}

std::string Persoana::getNameTeam() const {
    return NumeEchipa;
}

std::string Persoana::getName() const {
    return Nume;
}

void Persoana::change_team(const std::string &alta_echipa) {
    NumeEchipa = alta_echipa;
}

void Persoana::change_status() {
    transferabil = 1 - transferabil;
}

int Persoana::get_status() const {
    return transferabil;
}
