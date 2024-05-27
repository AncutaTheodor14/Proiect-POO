//
// Created by Theo on 5/27/2024.
//

#include "Exceptii.h"

eroare_echipa::eroare_echipa(const std::string &Mesaj) : eroare_aplicatie(
        std::string("Eroare la nivelul echipei, ") + Mesaj) {}

eroare_transfer::eroare_transfer(const std::string &Nume) : eroare_echipa(
        std::string("membrul echipei ") + Nume + std::string(" nu se poate transfera")) {}

eroare_campionat::eroare_campionat(const std::string &Mesaj) : eroare_aplicatie(
        std::string("Eroare la nivelul campionatului, ") + Mesaj) {}

eroare_numar_jucatori::eroare_numar_jucatori(int numar) : eroare_campionat(
        std::string("echipa are in componenta ") + std::to_string(numar) + std::string(" membrii")) {}
