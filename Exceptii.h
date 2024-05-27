//
// Created by Theo on 5/27/2024.
//

#ifndef OOP_EXCEPTII_H
#define OOP_EXCEPTII_H

#include<iostream>
#include <stdexcept>

class eroare_aplicatie : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class eroare_echipa : public eroare_aplicatie {
public:
    explicit eroare_echipa(const std::string &Mesaj);
};

class eroare_transfer : public eroare_echipa {
public:
    explicit eroare_transfer(const std::string &Nume);
};

class eroare_campionat : public eroare_aplicatie {
public:
    explicit eroare_campionat(const std::string &Mesaj);
};

class eroare_numar_jucatori : public eroare_campionat {
public:
    explicit eroare_numar_jucatori(int numar);
};


#endif //OOP_EXCEPTII_H
