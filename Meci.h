//
// Created by Theo on 5/27/2024.
//

#ifndef OOP_MECI_H
#define OOP_MECI_H


#include <string>
#include<vector>
#include "Echipa.h"
#include "Pariu.h"
#include "Persoana.h"

class Meci {
    Echipa &Gazda1;
    Echipa &Oaspete1;
    std::string Rezultat, DataMeci, Locatie;
    int ScorGazde, ScorOaspeti;
    std::vector<std::pair<std::shared_ptr<Persoana>, std::shared_ptr<Persoana>>> FazaGol;
    std::vector<Pariu> Pariuri;
public:
    Meci(Echipa &gazda, Echipa &oaspete, const std::string &dataMeci,
         std::vector<std::pair<std::shared_ptr<Persoana>, std::shared_ptr<Persoana>>> FazaGol_ = {},
         std::vector<Pariu> Pariuri_ = {}) : Gazda1(gazda), Oaspete1(oaspete), DataMeci(dataMeci),
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

};


#endif //OOP_MECI_H
