//
// Created by Theo on 5/27/2024.
//

#include "Exceptii.h"

eroare_echipa::eroare_echipa(const std::string &Mesaj) : eroare_aplicatie("Eroare la nivelul echipei, " + Mesaj) {}

eroare_transfer::eroare_transfer(const std::string &Nume) : eroare_echipa(
        "membrul echipei " + Nume + " nu se poate transfera") {}

eroare_campionat::eroare_campionat(const std::string &Mesaj) : eroare_aplicatie(
        "Eroare la nivelul campionatului, " + Mesaj) {}

eroare_numar_jucatori::eroare_numar_jucatori(int numar) : eroare_campionat(
        "echipa are in componenta " + std::to_string(numar) + " membrii") {}
