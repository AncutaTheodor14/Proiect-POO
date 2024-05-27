//
// Created by Theo on 5/27/2024.
//

#ifndef OOP_CAMPIONAT_LIGA_NATIONALA_H
#define OOP_CAMPIONAT_LIGA_NATIONALA_H

#include<iostream>
#include "Echipa.h"
#include "Meci.h"

class Campionat_Liga_Nationala {
    int NrEchipe, NrEtape;
    std::vector<Echipa> echipe;
    std::vector<Meci> meciuri;
public:
    Campionat_Liga_Nationala(int nrechipe, int nretape);

    Campionat_Liga_Nationala(const Campionat_Liga_Nationala &other);

    Campionat_Liga_Nationala &operator=(const Campionat_Liga_Nationala &other);

    ~Campionat_Liga_Nationala() {}

    friend std::ostream &operator<<(std::ostream &os, const Campionat_Liga_Nationala &m);

    void adaug_echipa(Echipa &ech);

    void adaug_meci(Meci &game);
};


#endif //OOP_CAMPIONAT_LIGA_NATIONALA_H
