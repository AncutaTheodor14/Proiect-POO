//
// Created by Theo on 5/27/2024.
//
#include<memory>
#include "Echipa.h"
#include "Antrenor.h"
#include "Jucator.h"
#include "Exceptii.h"

Echipa::Echipa(const Echipa &other) : NumeEchipa{other.NumeEchipa}, NumeArenaProprie{other.NumeArenaProprie},
                                      NrPuncte{other.NrPuncte} {
    for (const auto &mem: other.membrii)
        membrii.emplace_back(mem->clone());
}

Echipa &Echipa::operator=(Echipa other) {
    swap(*this, other);
    return *this;
}

void swap(Echipa &e1, Echipa &e2) {
    std::swap(e1.NumeEchipa, e2.NumeEchipa);
    std::swap(e1.NumeArenaProprie, e2.NumeArenaProprie);
    std::swap(e1.NrPuncte, e2.NrPuncte);
    std::swap(e1.membrii, e2.membrii);
}

std::ostream &operator<<(std::ostream &os, const Echipa &e) {
    os << "Nume_Echipa: " << e.NumeEchipa << ", Nr_Puncte: " << e.NrPuncte << ", Nume_Arena_Proprie: "
       << e.NumeArenaProprie << ", ";
    os << "Nume_Jucatori: " << '\n' << '\n';
    for (const auto &mem: e.membrii)
        os << *mem << '\n';///(*mem).getName()
    return os;
}

void Echipa::creare_Echipa() {
    nr_total_echipe++;
}

void Echipa::set_castig(int x) {
    NrPuncte += x;
}

std::string Echipa::get_arena() const {
    return NumeArenaProprie;
}

std::string Echipa::get_num() const {
    return NumeEchipa;
}

std::vector<std::shared_ptr<Persoana>> &Echipa::get_juc() {
    return membrii;
}

void Echipa::transfer_la_echipa(const Echipa &team, std::shared_ptr<Persoana> &p1) {
    if (p1->get_status() == 0) {
        throw eroare_transfer(p1->getName());
    }
    std::shared_ptr<Persoana> p2;
    p2 = p1;
    std::shared_ptr<Jucator> jucator1 = std::dynamic_pointer_cast<Jucator>(p1);
    if (jucator1)
        membrii.emplace_back(jucator1);
    else {
        std::shared_ptr<Antrenor> antrenor1 = std::dynamic_pointer_cast<Antrenor>(p2);
        membrii.emplace_back(antrenor1);
    }
    p1->change_team(team.get_num());
}

void Echipa::transfer_de_la_echipa(std::shared_ptr<Persoana> &p1) {
    if (p1->get_status() == 0) {
        throw eroare_transfer("Nu se poate transfera");
    }
    int poz = -1;
    for (int i = 0; i < int(membrii.size()); i++) {
        if (membrii[i]->getName() == p1->getName())
            poz = i;
    }
    if (poz > -1)
        membrii.erase(membrii.begin() + poz);
    std::string s = " ";
    p1->change_team(s);
}

int Echipa::Skill_total() {
    int suma = 0;
    for (const auto &membru: membrii) {
        std::shared_ptr<Jucator> juc = std::dynamic_pointer_cast<Jucator>(membru);
        if (juc)
            suma += juc->getskill();
    }
    return suma;
}

Echipa::Echipa(const std::string &nume_e, const std::string &nume_a, int NrPuncte_,
               std::vector<std::shared_ptr<Persoana>> membrii_) : NumeEchipa{std::move(nume_e)},
                                                                  NumeArenaProprie{std::move(nume_a)},
                                                                  NrPuncte{std::move(NrPuncte_)},
                                                                  membrii{std::move(membrii_)} {
    nr_total_echipe++;
}

Echipa::~Echipa() {
    nr_total_echipe--;
}

void Echipa::verifica_Skill_jucatori(int skill_minim) {
    for (const auto &player: membrii) {
        std::shared_ptr<Jucator> jucator = std::dynamic_pointer_cast<Jucator>(player);
        if (jucator && jucator->getskill() < skill_minim) {
            throw eroare_regulament(skill_minim);
        }
    }
}
