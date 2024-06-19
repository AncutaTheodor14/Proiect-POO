//
// Created by Theo on 6/19/2024.
//

#ifndef OOP_ECHIPAPOOL_H
#define OOP_ECHIPAPOOL_H


#include "Echipa.h"
#include "Antrenor.h"
#include<vector>
#include<algorithm>
#include<memory>

class EchipaPool {
private:
    static const int MAX_ECHIPE = 16;
    std::vector<std::shared_ptr<Echipa>> pool = {
            Echipa("Dinamo", "Stefan cel Mare", 0, {Antrenor{"Xavier Pascual", "Dinamo", 1, 3}.clone(),
                                                    Jucator{"Luca1 Cindric", "Dinamo", 1, "centru", 5, 3, 1}.clone(),
                                                    Jucator{"Vladimir Ciupara", "Dinamo", 1, "portar", 4, 6, 3}.clone()
            }).clone(), Echipa("A", "B", 0,
                               {}).clone()};//aici trebuie sa fie 16 echipe, 16 fiind nr maxim de echipe intr-un campionat
    std::vector<std::shared_ptr<Echipa>> activeTeams;
public:
    std::shared_ptr<Echipa> getEchipa() {
        for (auto &echipa: pool) {
            if (!echipa->e_activ()) {
                echipa->activate();
                activeTeams.push_back(echipa);
                return echipa;
            }
        }
        throw std::runtime_error("Toate echipele joaca!");
    }

    void releaseEchipa(std::shared_ptr<Echipa> echipa) {
        echipa->deactivate();
        auto it = std::find(activeTeams.begin(), activeTeams.end(), echipa);
        if (it != activeTeams.end()) {
            activeTeams.erase(it);
        }
    }
};

#endif //OOP_ECHIPAPOOL_H
