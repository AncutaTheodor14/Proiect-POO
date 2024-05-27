//
// Created by Theo on 5/27/2024.
//

#ifndef OOP_ECHIPA_H
#define OOP_ECHIPA_H

#include<vector>
#include "Persoana.h"

class Echipa {
    static int nr_total_echipe;
    std::string NumeEchipa, NumeArenaProprie;
    int NrPuncte;
    std::vector<std::shared_ptr<Persoana>> membrii;
public:
    explicit Echipa(const std::string &nume_e, const std::string &nume_a, int NrPuncte_,
                    std::vector<std::shared_ptr<Persoana>> membrii_) : NumeEchipa{std::move(nume_e)},
                                                                       NumeArenaProprie{std::move(nume_a)},
                                                                       NrPuncte{std::move(NrPuncte_)},
                                                                       membrii{std::move(membrii_)} {
        nr_total_echipe++;
    }

    Echipa(const Echipa &other);

    Echipa &operator=(Echipa other);

    friend void swap(Echipa &e1, Echipa &e2);

    ~Echipa() = default;

    friend std::ostream &operator<<(std::ostream &os, const Echipa &e);

    static void creare_Echipa();

    void set_castig(int x);

    std::string get_arena() const;

    std::string get_num() const;

    std::vector<std::shared_ptr<Persoana>> &get_juc();

    void transfer_la_echipa(const Echipa &team, std::shared_ptr<Persoana> &p1);

    void transfer_de_la_echipa(std::shared_ptr<Persoana> &p1);

    int Skill_total();
};


#endif //OOP_ECHIPA_H
