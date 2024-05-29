//
// Created by Theo on 5/27/2024.
//
#include<iostream>
#include <string>
#include<memory>

#ifndef OOP_PERSOANA_H
#define OOP_PERSOANA_H

class Persoana {
private:
    std::string Nume, NumeEchipa;
    bool transferabil;

    virtual void afisare(std::ostream &) const;

protected:
    Persoana(const Persoana &other) = default;

public:
    virtual double cost_deplasare(int factor_urgenta, int distanta) const = 0;

    Persoana &operator=(const Persoana &other) = default;

    explicit Persoana(const std::string &Nume1, const std::string &NE, bool transferabil_ = true);

    virtual std::shared_ptr<Persoana> clone() const = 0;

    virtual ~Persoana() = default;

    friend std::ostream &operator<<(std::ostream &os, const Persoana &pers);

    std::string getNameTeam() const;

    std::string getName() const;

    void change_team(const std::string &alta_echipa);

    void change_status();

    int get_status() const;
};


#endif //OOP_PERSOANA_H
