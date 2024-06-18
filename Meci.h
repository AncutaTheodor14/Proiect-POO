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
    std::vector<Pariu<int>> Pariuri1;//pariez jetoane
    std::vector<Pariu<double>> Pariuri2;//pariez sume
    int ScorGazde, ScorOaspeti;
    std::string Rezultat;

public:
    Meci(Echipa &gazda, Echipa &oaspete, const std::string &dataMeci,
         int distanta_orase_,
         std::vector<std::pair<std::shared_ptr<Persoana>, std::shared_ptr<Persoana>>> FazaGol_ = {},
         std::vector<Pariu<int>> Pariuri_ = {}, std::vector<Pariu<double>> _Pariuri = {}) : Gazda1(gazda),
                                                                                            Oaspete1(oaspete),
                                                                                            DataMeci(dataMeci),
                                             distanta_orase(distanta_orase_),
                                             Locatie(gazda.get_arena()),
                                                                                            FazaGol(std::move(
                                                                                                    FazaGol_)),
                                                                                            Pariuri1(std::move(
                                                                                                    Pariuri_)),
                                                                                            Pariuri2(std::move(
                                                                                                    _Pariuri)) {
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

    void plaseaza_pariu_jetoane(const Pariu<int> &pariu);

    void plaseaza_pariu_suma(const Pariu<double> &pariu);

    void evalueaza_pariuri();

    std::vector<std::pair<std::shared_ptr<Persoana>, std::shared_ptr<Persoana>>> &afisez();

    std::vector<Pariu<int>> get_pariuri_jetoane() const;

    std::vector<Pariu<double>> get_pariuri_suma() const;

    std::string getData() const;

    std::string getLocatie() const;

    int get_cost_oaspeti() const {
        int sum = 0;
        std::vector<int> factor = {1, 2, 3, 4, 5, 6, 7, 8};
        int ind = rand() % factor.size();
        int ales = factor[ind];
        for (const auto &it: Oaspete1.get_juc()) {
            sum += it->clone()->cost_deplasare(ales, distanta_orase);
        }
        return sum;
    }

};


#endif //OOP_MECI_H
