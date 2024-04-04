#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

class Jucator {
    std::string Nume, Pozitie;
    int NrGoluri, NrAssisturi, SkillGeneral;
    std::string NumeEchipa;

public:
    Jucator(const std::string &nume, const std::string &pozitie, int nrgoluri, int nrassisturi, int skillgen,
            const std::string &echipa) : Nume{nume}, Pozitie{pozitie}, NrGoluri{nrgoluri}, NrAssisturi{nrassisturi},
                                         SkillGeneral{skillgen}, NumeEchipa{echipa} {}

    Jucator(const Jucator &other) : Nume(other.Nume), Pozitie(other.Pozitie), NrGoluri(other.NrGoluri),
                                    NrAssisturi(other.NrAssisturi), SkillGeneral(other.SkillGeneral),
                                    NumeEchipa{other.NumeEchipa} {}

    Jucator &operator=(const Jucator &other) {
        Nume = other.Nume;
        Pozitie = other.Pozitie;
        NrGoluri = other.NrGoluri;
        NrAssisturi = other.NrAssisturi;
        SkillGeneral = other.SkillGeneral;
        NumeEchipa = other.NumeEchipa;
        return *this;
    }

    ~Jucator() {}

    friend std::ostream &operator<<(std::ostream &os, const Jucator &j) {
        os << "Nume: " << j.Nume << ", pozitie: " << j.Pozitie << ", nrgoluri: " << j.NrGoluri << ", nrassisturi: "
           << j.NrAssisturi << ", skillgeneral: " << j.SkillGeneral << ", Echipa: " << j.NumeEchipa << "\n";
        return os;
    }

    std::string getName() const {
        return Nume;
    }

    int getskill() const {
        return SkillGeneral;
    }

    void change_team(const std::string &alta_echipa) {
        NumeEchipa = alta_echipa;
    }

    void adauga_gol(int nrgoluri) {
        NrGoluri += nrgoluri;
    }

    void adauga_assisturi(int nrassisturi) {
        NrAssisturi += nrassisturi;
    }

    void antreneaza() {
        SkillGeneral += 2;
    }
};

class Echipa {
    std::string NumeEchipa, NumeAntrenor, NumeArenaProprie;
    std::vector<Jucator> jucatori;
    int NrPuncte;

public:
    Echipa(const std::string &nume_e, const std::string &nume_a, const std::string &nume_ar, int NrPct) : NumeEchipa{
            nume_e}, NumeAntrenor{nume_a}, NumeArenaProprie{nume_ar} {
        jucatori.clear();
        NrPuncte = NrPct;
    }

    Echipa(const Echipa &other) : NumeEchipa{other.NumeEchipa}, NumeAntrenor{other.NumeAntrenor},
                                  NumeArenaProprie{other.NumeArenaProprie}, jucatori{other.jucatori},
                                  NrPuncte{other.NrPuncte} {}

    Echipa &operator=(const Echipa &other) {
        NumeEchipa = other.NumeEchipa;
        NumeAntrenor = other.NumeAntrenor;
        NumeArenaProprie = other.NumeArenaProprie;
        jucatori = other.jucatori;
        NrPuncte = other.NrPuncte;
        return *this;
    }

    ~Echipa() {}

    friend std::ostream &operator<<(std::ostream &os, const Echipa &e) {
        os << "NumeEchipa: " << e.NumeEchipa << ", NrPuncte: " << e.NrPuncte << ", NumeAntrenor: " << e.NumeAntrenor
           << ", NumeArenaProprie: " << e.NumeArenaProprie << '\n';
        os << "NumeJucatori: " << '\n';
        for (const auto &jucator: e.jucatori)
            os << jucator.getName() << '\n';
        return os;
    }

    void get_castig(int x) {
        NrPuncte += x;
    }

    std::string get_arena() const {
        return NumeArenaProprie;
    }

    std::string get_num() const {
        return NumeEchipa;
    }

    std::vector<Jucator> &get_juc() {
        return jucatori;
    }

    void transfer_la_echipa(const Echipa &team, Jucator &j1) {
        jucatori.push_back(j1);
        j1.change_team(team.get_num());
    }

    void transfer_de_la_echipa(Jucator &j1) {
        int poz = -1;
        for (unsigned int i = 0; i < jucatori.size(); i++) {
            if (jucatori[i].getName() == j1.getName())
                poz = i;
        }
        if (poz > -1)
            jucatori.erase(jucatori.begin() + poz);
        std::string s = " ";
        j1.change_team(s);
    }

    int Skill_total() {
        int suma = 0;
        for (const auto &jucator: jucatori) {
            suma += jucator.getskill();
        }
        return suma;
    }
};

class Meci {
    Echipa &Gazda;
    Echipa &Oaspete;
    std::string Rezultat, DataMeci, Locatie;
    int ScorGazde, ScorOaspeti;
    std::vector<std::pair<Jucator, Jucator>> FazaGol;
public:
    Meci(Echipa &gazda, Echipa &oaspete, const std::string &dataMeci) : Gazda(gazda), Oaspete(oaspete),
                                                                        DataMeci(dataMeci), Locatie{Gazda.get_arena()} {
        ScorGazde = 0;
        ScorOaspeti = 0;
        Rezultat = std::to_string(ScorGazde) + '-' + std::to_string(ScorOaspeti);
        FazaGol = {};
    }

    Meci(const Meci &other) : Gazda{other.Gazda}, Oaspete{other.Oaspete}, Rezultat{other.Rezultat},
                              DataMeci{other.DataMeci}, Locatie{other.Locatie}, ScorGazde{other.ScorGazde},
                              ScorOaspeti{other.ScorOaspeti}, FazaGol{other.FazaGol} {}

    Meci &operator=(const Meci &other) {
        Gazda = other.Gazda;
        Oaspete = other.Oaspete;
        Rezultat = other.Rezultat;
        DataMeci = other.DataMeci;
        Locatie = other.Locatie;
        ScorGazde = other.ScorGazde;
        ScorOaspeti = other.ScorOaspeti;
        FazaGol = other.FazaGol;
        return *this;
    }

    ~Meci() {}

    friend std::ostream &operator<<(std::ostream &os, const Meci &m) {
        os << "Gazde: " << m.Gazda.get_num() << ", Oaspeti: " << m.Oaspete.get_num() << ", Rezultat: " << m.Rezultat
           << ", DataMeci: " << m.DataMeci << ", Locatie: " << m.Locatie << '\n';
        return os;
    }

    void adauga_faza_gol(Jucator &marcator, Jucator &pasator) {
        FazaGol.push_back(std::make_pair(marcator, pasator));
        int ok = 0;
        for (auto &it: Gazda.get_juc()) {
            if (it.getName() == marcator.getName()) {
                marcator.adauga_gol(1);
                it = marcator;
                ok = 1;
                ScorGazde++;
            } else if (it.getName() == pasator.getName()) {
                pasator.adauga_assisturi(1);
                it = pasator;
            }
        }
        if (ok == 0) {
            ScorOaspeti++;
            for (auto &it: Oaspete.get_juc()) {
                if (it.getName() == marcator.getName()) {
                    marcator.adauga_gol(1);
                    it = marcator;
                }
                if (it.getName() == pasator.getName()) {
                    pasator.adauga_assisturi(1);
                    it = pasator;
                }
            }
        }
        Rezultat = std::to_string(ScorGazde) + '-' + std::to_string(ScorOaspeti);
    }

    std::string verifica_castigator() {
        if (ScorGazde > ScorOaspeti) {
            Gazda.get_castig(3);
            return Gazda.get_num();
        } else if (ScorGazde < ScorOaspeti) {
            Oaspete.get_castig(3);
            return Oaspete.get_num();
        } else {
            Gazda.get_castig(1);
            Oaspete.get_castig(1);
            return "Egalitate";
        }
    }

    std::vector<std::pair<Jucator, Jucator>> &afisez() {
        return FazaGol;
    }
};

class Campionat_Liga_Nationala {
    int NrEchipe, NrEtape;
    std::vector<Echipa> echipe;
    std::vector<Meci> meciuri;
public:
    Campionat_Liga_Nationala(int nrechipe, int nretape) : NrEchipe{nrechipe},
                                                                                   NrEtape{nretape},
                                                                                   echipe{},
                                                                                   meciuri{} {
    }

    Campionat_Liga_Nationala(const Campionat_Liga_Nationala &other)
            : NrEchipe{other.NrEchipe}, NrEtape{other.NrEtape}, echipe{other.echipe}, meciuri{other.meciuri} {}

    Campionat_Liga_Nationala &
    operator=(const Campionat_Liga_Nationala &other) {
        NrEchipe = other.NrEchipe;
        NrEtape = other.NrEtape;
        echipe = other.echipe;
        meciuri = other.meciuri;
        return *this;
    }

    ~Campionat_Liga_Nationala() {}

    friend std::ostream &operator<<(std::ostream &os, const Campionat_Liga_Nationala &m) {
        os << "NrEchipe: " << m.NrEchipe << ", NrEtape: " << m.NrEtape << '\n';
        for (auto it: m.echipe)
            os << it.get_num() << '\n';
        return os;
    }

    void adaug_echipa(Echipa &ech) {
        echipe.push_back(ech);
    }
};

int main() {
    Campionat_Liga_Nationala campionat(14, 28);
    Jucator jucator1("Luka Cindric", "Playmaker", 4, 9, 99, "Dinamo");
    Jucator jucator2("Nicusor Negru", "Left Wing", 6, 8, 94, "Dinamo");
    Jucator jucator3("Vladimir Cupara", "Goalkeeper", 0, 3, 96, "Dinamo");
    Jucator jucator4("Cedric Sorhaindo", "Pivot", 8, 3, 92, "Dinamo");
    Jucator jucator5("Ionut Nistor", "Right Wing", 12, 2, 88, "CSM Constanta");
    Jucator jucator6("Ionut Rada", "Left Back", 23, 5, 79, "CSM Constanta");
    Echipa echipa1("Dinamo", "Xavi Pascual", "Sala Stefan cel Mare", 0);
    Echipa echipa2("CSM Constanta", "George Buricea", "Sala Sporturilor Constanta", 0);
    echipa1.transfer_la_echipa(echipa1, jucator1);
    echipa1.transfer_de_la_echipa(jucator1);
    echipa1.transfer_la_echipa(echipa1, jucator2);
    echipa1.transfer_la_echipa(echipa1, jucator3);
    echipa1.transfer_la_echipa(echipa1, jucator4);
    echipa2.transfer_la_echipa(echipa2, jucator5);
    echipa2.transfer_la_echipa(echipa2, jucator6);
    campionat.adaug_echipa(echipa1);
    campionat.adaug_echipa(echipa2);
    Meci meci1(echipa1, echipa2, "21-06-2024");
    std::cout << campionat << '\n';
    std::cout << "Detalii inceput meci: " << meci1 << '\n';
    meci1.adauga_faza_gol(jucator2, jucator4);
    meci1.adauga_faza_gol(jucator4, jucator2);
    std::cout << "Detalii final meci: " << meci1 << '\n';
    std::cout << "Echipa castigatoare: " << meci1.verifica_castigator() << '\n' << '\n';
    std::cout << "Istoric marcatori:" << '\n';
    for (auto &it: meci1.afisez())
        std::cout << "Marcheaza " << it.first.getName() << " din pasa lui " << it.second.getName() << '\n';
    std::cout << '\n';
    std::cout << "Statistici jucatori:" << '\n';
    std::cout << jucator2;
    std::cout << jucator4 << '\n';
    jucator2.antreneaza();
    jucator4.antreneaza();
    std::cout << "Skilul jucatorilor dupa antrenament:" << '\n';
    std::cout << jucator2.getskill() << '\n';
    std::cout << jucator4.getskill() << '\n';
    std::cout << '\n';
    std::cout << "Skilul total al echipei " << echipa1.get_num() << " este ";
    std::cout << echipa1.Skill_total();
    std::cout << '\n';
    return 0;
}