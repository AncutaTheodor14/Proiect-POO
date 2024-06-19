//
// Created by Theo on 6/18/2024.
//

#ifndef OOP_PERSOANAFACTORY_H
#define OOP_PERSOANAFACTORY_H


#include "Persoana.h"
#include "Antrenor.h"
#include "Jucator.h"

class PersoanaImportanta {
    std::string nume;
    std::string echipa;
    bool transferabil;
    std::string rol;
    int nrGoluri;
    int nrAssisturi;
    int skillGeneral;
    int echipeAntrenate;

    friend class PersoanaBuilder;

public:
    PersoanaImportanta() = default;
};

class PersoanaBuilder {
    PersoanaImportanta p;
public:
    PersoanaBuilder() = default;

    PersoanaBuilder &setNume(const std::string &nume) {
        p.nume = nume;
        return *this;
    }

    PersoanaBuilder &setEchipa(const std::string &echipa) {
        p.echipa = echipa;
        return *this;
    }

    PersoanaBuilder &setTransferabil(bool transferabil) {
        p.transferabil = transferabil;
        return *this;
    }

    PersoanaBuilder &setRol(const std::string &rol) {
        p.rol = rol;
        return *this;
    }

    PersoanaBuilder &setNrGoluri(int nrGoluri) {
        p.nrGoluri = nrGoluri;
        return *this;
    }

    PersoanaBuilder &setNrAssisturi(int nrAssisturi) {
        p.nrAssisturi = nrAssisturi;
        return *this;
    }

    PersoanaBuilder &setSkillGeneral(int skillGeneral) {
        p.skillGeneral = skillGeneral;
        return *this;
    }

    PersoanaBuilder &setEchipeAntrenate(int echipeAntrenate) {
        p.echipeAntrenate = echipeAntrenate;
        return *this;
    }

    std::shared_ptr<Persoana> build() {
        if (p.rol == "portar" || p.rol == "extrema" || p.rol == "inter" || p.rol == "pivot" || p.rol == "centru") {
            return std::make_shared<Jucator>(p.nume, p.echipa, p.transferabil, p.rol, p.nrGoluri, p.nrAssisturi,
                                             p.skillGeneral);
        } else if (p.rol == "antrenor") {
            return std::make_shared<Antrenor>(p.nume, p.echipa, p.transferabil, p.echipeAntrenate);
        }
        throw std::runtime_error("Alt rol!");
    }
};


class PersoanaFactory {
public:
    static std::shared_ptr<Persoana> createPortar() {
        return PersoanaBuilder().setNume("Nume Portar").setEchipa("Echipa Portar").setTransferabil(true).setRol(
                "portar").setSkillGeneral(75).build();
    }

    static std::shared_ptr<Persoana> createExtrema() {
        return PersoanaBuilder().setNume("Nume Extrema").setEchipa("Echipa Extrema").setTransferabil(true).setRol(
                "extrema").setNrGoluri(4).setNrAssisturi(5).setSkillGeneral(75).build();
    }

    static std::shared_ptr<Persoana> createAntrenorPrincipal() {
        return PersoanaBuilder().setNume("Nume Antrenor Principal").setEchipa("Echipa Antrenor").setTransferabil(
                true).setRol("antrenor").setEchipeAntrenate(10).build();
    }
};

#endif //OOP_PERSOANAFACTORY_H
