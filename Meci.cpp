//
// Created by Theo on 5/27/2024.
//

#include "Meci.h"
#include "Jucator.h"

Meci::Meci(const Meci &other) : Gazda1{other.Gazda1}, Oaspete1{other.Oaspete1}, DataMeci{other.DataMeci},
                                distanta_orase(other.distanta_orase), Locatie{other.Locatie},
                                FazaGol{other.FazaGol}, Pariuri1{other.Pariuri1}, Pariuri2{other.Pariuri2},
                                ScorGazde{other.ScorGazde},
                                ScorOaspeti{other.ScorOaspeti}, Rezultat{other.Rezultat} {}

Meci &Meci::operator=(const Meci &other) {
    Gazda1 = other.Gazda1;
    Oaspete1 = other.Oaspete1;
    Rezultat = other.Rezultat;
    DataMeci = other.DataMeci;
    Locatie = other.Locatie;
    ScorGazde = other.ScorGazde;
    ScorOaspeti = other.ScorOaspeti;
    distanta_orase = other.distanta_orase;
    FazaGol = other.FazaGol;
    Pariuri1 = other.Pariuri1;
    Pariuri2 = other.Pariuri2;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Meci &m) {
    os << "Gazde: " << m.Gazda1.get_num() << ", Oaspeti: " << m.Oaspete1.get_num() << ", _Rezultat: " << m.Rezultat
       << ", Data_Meci: " << m.DataMeci << ", _Locatie: " << m.Locatie << '\n';
    return os;
}

void Meci::adauga_faza_gol(std::shared_ptr<Persoana> &marcato, std::shared_ptr<Persoana> &pasato) {
    std::shared_ptr<Jucator> marcator = std::dynamic_pointer_cast<Jucator>(marcato);
    std::shared_ptr<Jucator> pasator = std::dynamic_pointer_cast<Jucator>(pasato);
    if (marcator && pasator) {
        FazaGol.emplace_back(std::make_pair(marcator, pasator));
        int ok = 0;
        for (auto &it: Gazda1.get_juc()) {
            if (it->getName() == marcator->getName()) {
                marcator->adauga_gol(1);
                it = marcator;
                ok = 1;
                ScorGazde++;
            } else if (it->getName() == pasator->getName()) {
                pasator->adauga_assisturi(1);
                it = pasator;
            }
        }
        if (ok == 0) {
            ScorOaspeti++;
            for (auto &it: Oaspete1.get_juc()) {
                if (it->getName() == marcator->getName()) {
                    marcator->adauga_gol(1);
                    it = marcator;
                }
                if (it->getName() == pasator->getName()) {
                    pasator->adauga_assisturi(1);
                    it = pasator;
                }
            }
        }
        Rezultat = std::to_string(ScorGazde) + '-' + std::to_string(ScorOaspeti);
    }
}

std::string Meci::verifica_castigator(Echipa &gazda, Echipa &oaspete) const {
    if (ScorGazde > ScorOaspeti) {
        gazda.set_castig(2);
        return gazda.get_num();
    } else if (ScorGazde < ScorOaspeti) {
        oaspete.set_castig(2);
        return oaspete.get_num();
    } else {
        gazda.set_castig(1);
        oaspete.set_castig(1);
        return "Egalitate";
    }
}

std::pair<double, double> Meci::calculeaza_cote() {
    int skillGazde = Gazda1.Skill_total();
    int skillOaspeti = Oaspete1.Skill_total();
    double totalSkill = skillGazde + skillOaspeti;
    double cotaGazde = (totalSkill / skillGazde) * 1.5;
    double cotaOaspeti = (totalSkill / skillOaspeti) * 1.5;
    return {cotaGazde, cotaOaspeti};
}

void Meci::plaseaza_pariu_jetoane(const Pariu<int> &pariu) {
    Pariuri1.emplace_back(pariu);
}

void Meci::evalueaza_pariuri() {
    std::string castigator = verifica_castigator(Gazda1, Oaspete1);
    for (auto &pariu: Pariuri1) {
        if (pariu.getEchipaPariata() == castigator) {
            pariu.setCastigator(true);
            if (castigator == Gazda1.get_num())
                pariu.suma_Castigata(pariu.getSumaPariata() * calculeaza_cote().first);
            else if (castigator == Oaspete1.get_num())
                pariu.suma_Castigata(pariu.getSumaPariata() * calculeaza_cote().second);
        }
    }
    for (auto &pariu: Pariuri2) {
        if (pariu.getEchipaPariata() == castigator) {
            pariu.setCastigator(true);
            int valoare_curenta_jeton = rand() % 5000;
            if (castigator == Gazda1.get_num())
                pariu.suma_Castigata(pariu.getSumaPariata() * calculeaza_cote().first * valoare_curenta_jeton);
            else if (castigator == Oaspete1.get_num())
                pariu.suma_Castigata(pariu.getSumaPariata() * calculeaza_cote().second * valoare_curenta_jeton);
        }
    }
}

std::vector<std::pair<std::shared_ptr<Persoana>, std::shared_ptr<Persoana>>> &

Meci::afisez() {
    return FazaGol;
}

std::vector<Pariu<int>> Meci::get_pariuri_jetoane() const {
    return Pariuri1;
}

std::string Meci::getData() const {
    return DataMeci;
}

std::string Meci::getLocatie() const {
    return Locatie;
}

std::vector<Pariu<double>> Meci::get_pariuri_suma() const {
    return Pariuri2;
}

void Meci::plaseaza_pariu_suma(const Pariu<double> &pariu) {
    Pariuri2.emplace_back(pariu);
}
