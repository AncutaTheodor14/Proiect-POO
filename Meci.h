//
// Created by Theo on 5/27/2024.
//

#ifndef OOP_MECI_H
#define OOP_MECI_H

#include<iostream>
#include <string>
#include<vector>
#include "Echipa.h"
#include "Pariu.h"
#include "Persoana.h"

class Meci {
    Echipa &Gazda1;
    Echipa &Oaspete1;
    std::string DataMeci;
    int distanta_orase;
    std::string Locatie;
    std::vector<std::pair<std::shared_ptr<Persoana>, std::shared_ptr<Persoana>>> FazaGol;
    std::vector<Pariu> Pariuri;
    int ScorGazde, ScorOaspeti;
    std::string Rezultat;

public:
    Meci(Echipa &gazda, Echipa &oaspete, const std::string &dataMeci,
         int distanta_orase_,
         std::vector<std::pair<std::shared_ptr<Persoana>, std::shared_ptr<Persoana>>> FazaGol_ = {},
         std::vector<Pariu> Pariuri_ = {}) : Gazda1(gazda), Oaspete1(oaspete), DataMeci(dataMeci),
                                             distanta_orase(distanta_orase_),
                                             Locatie(gazda.get_arena()),
                                             FazaGol(std::move(FazaGol_)), Pariuri(std::move(Pariuri_)) {
        ScorGazde = 0;
        ScorOaspeti = 0;
        Rezultat = std::to_string(ScorGazde) + '-' + std::to_string(ScorOaspeti);
    }

    Meci(const Meci &other);

    //Meci(const Meci& other) = default;
    Meci &operator=(const Meci &other);

    ~Meci() = default;

    friend std::ostream &operator<<(std::ostream &os, const Meci &m);

    void adauga_faza_gol(std::shared_ptr<Persoana> &marcato, std::shared_ptr<Persoana> &pasato);

    std::string verifica_castigator(Echipa &gazda, Echipa &oaspete) const;

    std::pair<double, double> calculeaza_cote();

    void plaseaza_pariu(const Pariu &pariu);

    void evalueaza_pariuri();

    std::vector<std::pair<std::shared_ptr<Persoana>, std::shared_ptr<Persoana>>> &afisez();

    std::vector<Pariu> get_pariuri() const;

    std::string getData() const;

    std::string getLocatie() const;

    int get_cost_oaspeti() const {
        int sum = 0, con = 0, factor;
        if (con == 0)
            factor = 1;
        else
            factor = 2;
        con = 1 - con;
        for (const auto &it: Oaspete1.get_juc()) {
            sum += it->clone()->cost_deplasare(factor, distanta_orase);
        }
        return sum;
    }

};


#endif //OOP_MECI_H
