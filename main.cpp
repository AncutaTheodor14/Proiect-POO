#include<iostream>
#include<vector>
#include<memory>
#include<stdexcept>
#include<indicators.hpp>

class eroare_aplicatie : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class eroare_echipa : public eroare_aplicatie {
public:
    explicit eroare_echipa(const std::string &Mesaj) : eroare_aplicatie("Eroare la nivelul echipei, " + Mesaj) {}
};

class eroare_transfer : public eroare_echipa {
public:
    explicit eroare_transfer(const std::string &Nume) : eroare_echipa(
            "membrul echipei " + Nume + " nu se poate transfera") {}
};

class eroare_campionat : public eroare_aplicatie {
public:
    explicit eroare_campionat(const std::string &Mesaj) : eroare_aplicatie(
            "Eroare la nivelul campionatului, " + Mesaj) {}
};

class eroare_numar_jucatori : public eroare_campionat {
public:
    explicit eroare_numar_jucatori(int numar) : eroare_campionat(
            "echipa are in componenta " + std::to_string(numar) + " membrii") {}
};

class Persoana {
private:
    std::string Nume, NumeEchipa;
    bool transferabil;

    virtual void afisare(std::ostream &) const {};
protected:
    Persoana(const Persoana &other) = default;

public:
    Persoana &operator=(const Persoana &other) = default;

    explicit Persoana(const std::string &Nume1, const std::string &NE, bool transferabil_ = true) : Nume(Nume1),
                                                                                                    NumeEchipa(NE),
                                                                                                    transferabil(
                                                                                                            transferabil_) {}

    virtual std::shared_ptr<Persoana> clone() const = 0;

    virtual ~Persoana() = default;

    friend std::ostream &operator<<(std::ostream &os, const Persoana &pers) {
        os << pers.Nume << " este la echipa " << pers.NumeEchipa << ", transferabil = " << pers.transferabil;
        pers.afisare(os);
        return os;
    }

    std::string getNameTeam() const {
        return NumeEchipa;
    }

    std::string getName() const {
        return Nume;
    }

    void change_team(const std::string &alta_echipa) {
        NumeEchipa = alta_echipa;
    }

    void change_status() {
        transferabil = 1 - transferabil;
    }

    int get_status() const {
        return transferabil;
    }
};

class Antrenor : public Persoana {
public:
    explicit Antrenor(const std::string &Nume, const std::string &NE, bool transf, int EA) : Persoana(Nume, NE, transf),
                                                                                             EchipeAntrenate(EA) {}

    std::shared_ptr<Persoana> clone() const override {
        return std::make_shared<Antrenor>(*this);
    }

private:
    int EchipeAntrenate;

    void afisare(std::ostream &os) const override {
        os << ". Are rolul de antrenor si a antrenat pana acum " << EchipeAntrenate << " echipe." << '\n';
    }
};

class Jucator : public Persoana {
private:
    std::string Pozitie;
    int NrGoluri, NrAssisturi, SkillGeneral;

    void afisare(std::ostream &os) const override {
        os << ", Rol: Jucator, " << "Pozitie: " << Pozitie << ", " << "NrGoluri: " << NrGoluri << ", "
           << "NrAssisturi: " << NrAssisturi << ", " << "SkillGeneral: " << SkillGeneral << '\n';
    }

public:
    explicit Jucator(const std::string &nume, const std::string &echipa, bool transf, const std::string &pozitie,
                     int nrgoluri, int nrassisturi, int skillgen) : Persoana(nume, echipa, transf), Pozitie(pozitie),
                                                                    NrGoluri(nrgoluri), NrAssisturi(nrassisturi),
                                                                    SkillGeneral(skillgen) {}

    std::shared_ptr<Persoana> clone() const override {
        return std::make_shared<Jucator>(*this);
    }

    int getskill() const {
        return SkillGeneral;
    }

    void adauga_gol(int nrgoluri) {
        NrGoluri += nrgoluri;
    }

    void adauga_assisturi(int nrassisturi) {
        NrAssisturi += nrassisturi;
    }

    void Skill_Jucator() {
        SkillGeneral += NrGoluri / 5 + NrAssisturi / 7;
    }

    void antreneaza() {
        SkillGeneral += 2;
    }
};

class Echipa {
    static int nr_total_echipe;
    std::string NumeEchipa, NumeArenaProprie;
    int NrPuncte;
    std::vector<std::shared_ptr<Persoana>> membrii;
public:
    Echipa(const std::string &nume_e, const std::string &nume_a, int NrPuncte_,
           std::vector<std::shared_ptr<Persoana>> membrii_) : NumeEchipa{std::move(nume_e)},
                                                              NumeArenaProprie{std::move(nume_a)},
                                                              NrPuncte{std::move(NrPuncte_)},
                                                              membrii{std::move(membrii_)} {
        nr_total_echipe++;
    }

    Echipa(const Echipa &other) : NumeEchipa{other.NumeEchipa}, NumeArenaProprie{other.NumeArenaProprie},
                                  NrPuncte{other.NrPuncte} {
        for (const auto &mem: other.membrii)
            membrii.emplace_back(mem->clone());
    }

    Echipa &operator=(Echipa other) {
        swap(*this, other);
        return *this;
    }

    friend void swap(Echipa &e1, Echipa &e2) {
        std::swap(e1.NumeEchipa, e2.NumeEchipa);
        std::swap(e1.NumeArenaProprie, e2.NumeArenaProprie);
        std::swap(e1.NrPuncte, e2.NrPuncte);
        std::swap(e1.membrii, e2.membrii);
    }

    ~Echipa() = default;

    friend std::ostream &operator<<(std::ostream &os, const Echipa &e) {
        os << "NumeEchipa: " << e.NumeEchipa << ", NrPuncte: " << e.NrPuncte << ", NumeArenaProprie: "
           << e.NumeArenaProprie << ", ";
        os << "NumeJucatori: " << '\n' << '\n';
        for (const auto &mem: e.membrii)
            os << *mem << '\n';///(*mem).getName()
        return os;
    }

    static void creare_Echipa() {
        nr_total_echipe++;
    }

    void set_castig(int x) {
        NrPuncte += x;
    }

    std::string get_arena() const {
        return NumeArenaProprie;
    }

    std::string get_num() const {
        return NumeEchipa;
    }

    std::vector<std::shared_ptr<Persoana>> &get_juc() {
        return membrii;
    }

    void transfer_la_echipa(Echipa &team, std::shared_ptr<Persoana> &p1) {
        if (p1->get_status() == 0) {
            throw eroare_transfer(p1->getName());
        }
        std::shared_ptr<Persoana> p2;
        p2 = p1;
        std::shared_ptr<Jucator> jucator1 = std::dynamic_pointer_cast<Jucator>(p1);
        if (jucator1)
            membrii.emplace_back(jucator1);
        else {
            std::shared_ptr<Antrenor> antrenor1 = std::dynamic_pointer_cast<Antrenor>(p2);
            membrii.emplace_back(antrenor1);
        }
        p1->change_team(team.get_num());
    }

    void transfer_de_la_echipa(std::shared_ptr<Persoana> &p1) {
        if (p1->get_status() == 0) {
            throw eroare_transfer("Nu se poate transfera");
        }
        int poz = -1;
        for (int i = 0; i < int(membrii.size()); i++) {
            if (membrii[i]->getName() == p1->getName())
                poz = i;
        }
        if (poz > -1)
            membrii.erase(membrii.begin() + poz);
        std::string s = " ";
        p1->change_team(s);
    }

    int Skill_total() {
        int suma = 0;
        for (const auto &membru: membrii) {
            std::shared_ptr<Jucator> juc = std::dynamic_pointer_cast<Jucator>(membru);
            if (juc)
                suma += juc->getskill();
        }
        return suma;
    }
};

int Echipa::nr_total_echipe = 0;

class Pariu {
    std::string NumeParior;
    std::string EchipaPariata;
    double SumaPariata = 0;
    double sumaCastigata = 0;
    bool castigator;
public:
    Pariu(const std::string &nume, const std::string &echipa, double suma, double su = 0, bool cast = false)
            : NumeParior(nume), EchipaPariata(echipa), SumaPariata(suma), sumaCastigata(su), castigator(cast) {}

    std::string getNumeParior() const {
        return NumeParior;
    }

    void suma_Castigata(double &&x) {
        sumaCastigata = x;
    }

    double val_suma_Castigata() const {
        return sumaCastigata;
    }

    std::string getEchipaPariata() const {
        return EchipaPariata;
    }

    double getSumaPariata() const {
        return SumaPariata;
    }

    bool isCastigator() const {
        return castigator;
    }

    void setCastigator(bool status) {
        castigator = status;
    }
};

class Meci {
    Echipa &Gazda;
    Echipa &Oaspete;
    std::string Rezultat, DataMeci, Locatie;
    int ScorGazde, ScorOaspeti;
    std::vector<std::pair<std::shared_ptr<Persoana>, std::shared_ptr<Persoana>>> FazaGol;
    std::vector<Pariu> &Pariuri;
public:
    Meci(Echipa &gazda, Echipa &oaspete, const std::string &dataMeci,
         std::vector<std::pair<std::shared_ptr<Persoana>, std::shared_ptr<Persoana>>> FazaGol_ = {},
         std::vector<Pariu> Pariuri_ = {}) : Gazda(gazda), Oaspete(oaspete), DataMeci(dataMeci),
                                             FazaGol(std::move(FazaGol_)), Pariuri(Pariuri_) {
        Locatie = gazda.get_arena();
        ScorGazde = 0;
        ScorOaspeti = 0;
        Rezultat = std::to_string(ScorGazde) + '-' + std::to_string(ScorOaspeti);
    }

    Meci(const Meci &other) : Gazda{other.Gazda}, Oaspete{other.Oaspete}, Rezultat{other.Rezultat},
                              DataMeci{other.DataMeci}, Locatie{other.Locatie}, ScorGazde{other.ScorGazde},
                              ScorOaspeti{other.ScorOaspeti}, FazaGol{other.FazaGol}, Pariuri{other.Pariuri} {}

    //Meci(const Meci& other) = default;
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

    ~Meci() = default;

    friend std::ostream &operator<<(std::ostream &os, const Meci &m) {
        os << "Gazde: " << m.Gazda.get_num() << ", Oaspeti: " << m.Oaspete.get_num() << ", Rezultat: " << m.Rezultat
           << ", DataMeci: " << m.DataMeci << ", Locatie: " << m.Locatie << '\n';
        return os;
    }

    void adauga_faza_gol(std::shared_ptr<Persoana> &marcato, std::shared_ptr<Persoana> &pasato) {
        std::shared_ptr<Jucator> marcator = std::dynamic_pointer_cast<Jucator>(marcato);
        std::shared_ptr<Jucator> pasator = std::dynamic_pointer_cast<Jucator>(pasato);
        if (marcator && pasator) {
            FazaGol.emplace_back(std::make_pair(marcator, pasator));
            int ok = 0;
            for (auto &it: Gazda.get_juc()) {
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
                for (auto &it: Oaspete.get_juc()) {
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

    std::string verifica_castigator(Echipa &Gazda, Echipa &Oaspete) const {
        if (ScorGazde > ScorOaspeti) {
            Gazda.set_castig(2);
            return Gazda.get_num();
        } else if (ScorGazde < ScorOaspeti) {
            Oaspete.set_castig(2);
            return Oaspete.get_num();
        } else {
            Gazda.set_castig(1);
            Oaspete.set_castig(1);
            return "Egalitate";
        }
    }

    std::pair<double, double> calculeaza_cote() {
        int skillGazde = Gazda.Skill_total();
        int skillOaspeti = Oaspete.Skill_total();
        double totalSkill = skillGazde + skillOaspeti;
        double cotaGazde = (totalSkill / skillGazde) * 1.5;
        double cotaOaspeti = (totalSkill / skillOaspeti) * 1.5;
        return {cotaGazde, cotaOaspeti};
    }

    void plaseaza_pariu(const Pariu &pariu) {
        Pariuri.emplace_back(pariu);
    }

    void evalueaza_pariuri() {
        std::string castigator = verifica_castigator(Gazda, Oaspete);
        for (auto &pariu: Pariuri) {
            if (pariu.getEchipaPariata() == castigator) {
                pariu.setCastigator(true);
                if (castigator == Gazda.get_num())
                    pariu.suma_Castigata(pariu.getSumaPariata() * calculeaza_cote().first);
                else if (castigator == Oaspete.get_num())
                    pariu.suma_Castigata(pariu.getSumaPariata() * calculeaza_cote().second);
            }
        }
    }

    std::string get_rez() const {
        return Rezultat;
    }

    std::vector<std::pair<std::shared_ptr<Persoana>, std::shared_ptr<Persoana>>> &afisez() {
        return FazaGol;
    }

    std::vector<Pariu> get_pariuri() const {
        return Pariuri;
    }

};

class Campionat_Liga_Nationala {
    int NrEchipe, NrEtape;
    std::vector<Echipa> echipe;
    std::vector<Meci> meciuri;
public:
    Campionat_Liga_Nationala(int nrechipe, int nretape) : NrEchipe{nrechipe}, NrEtape{nretape}, echipe{}, meciuri{} {}

    Campionat_Liga_Nationala(const Campionat_Liga_Nationala &other) : NrEchipe{other.NrEchipe}, NrEtape{other.NrEtape},
                                                                      echipe{other.echipe}, meciuri{other.meciuri} {}

    Campionat_Liga_Nationala &operator=(const Campionat_Liga_Nationala &other) {
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
        os << '\n';
        return os;
    }

    void adaug_echipa(Echipa &ech) {
        int var = ech.get_juc().size();
        if (var < 1 || var >= 14)
            throw eroare_numar_jucatori(var);
        echipe.emplace_back(ech);
    }

    void adaug_meci(Meci &game) {
        meciuri.emplace_back(game);
    }
};

int main() {
    try {
        Persoana *p = new Antrenor("Xavier Pascual", "Dinamo", 1, 3);
        p->change_status();
        p->change_status();
        std::cout << *p << '\n';
        Persoana *p1 = new Jucator("Luca Cindric", "Dinamo", 1, "centru", 5, 3, 1);
        std::cout << *p1 << '\n';
        Jucator *jucator = dynamic_cast<Jucator *>(p1);
        if (jucator) {
            std::cout << jucator->getskill() << '\n';
            jucator->Skill_Jucator();
            jucator->antreneaza();
        } else
            std::cout << "p1 nu e Jucator" << '\n';
        Echipa e1("Dinamo", "Stefan cel Mare", 0, {Antrenor{"Xavier Pascual", "Dinamo", 1, 3}.clone(),
                                                   Jucator{"Luca1 Cindric", "Dinamo", 1, "centru", 5, 3, 1}.clone(),
                                                   Jucator{"Vladimir Ciupara", "Dinamo", 1, "portar", 4, 6, 3}.clone()
        });
        Echipa::creare_Echipa();
        Echipa e2("Constanta", "Dobrogea Arena", 0, {Antrenor{"George Buricea", "Constanta", 1, 5}.clone(),
                                                     Jucator{"Vitaly Komogorov", "Constanta", 1, "inter stang", 3, 5,
                                                             2}.clone(),
                                                     Jucator{"Vasile Ion", "Constanta", 1, "extrema stanga", 7, 3,
                                                             4}.clone()
        });
        Echipa::creare_Echipa();
        std::shared_ptr<Persoana> j1 = std::make_shared<Jucator>("Dan Nistor", "Constanta", 1, "inter drept", 8, 2, 2);
        std::shared_ptr<Persoana> j2 = std::make_shared<Jucator>("Nicusor Negru", "Dinamo", 1, "extrema stanga", 5, 5,
                                                                 5);
        std::shared_ptr<Persoana> a1 = std::make_shared<Antrenor>("Stefan Enache", "CSM Bucuresti", 1, 2);
        Jucator j3("Dan Nistor", "Constanta", 1, "inter drept", 8, 2, 2);
        Jucator j4("Nicusor Negru", "Dinamo", 1, "extrema stanga", 5, 5, 5);
        std::cout << *j1 << '\n';
        e1.transfer_la_echipa(e1, j1);
        std::cout << *j1 << '\n';
        e1.transfer_la_echipa(e1, a1);
        e1.transfer_de_la_echipa(a1);
        a1->change_team(e1.get_num());
        std::cout << e1.Skill_total() << '\n';
        std::cout << *a1 << '\n';
        std::cout << e1 << '\n';
        std::cout << '\n';
        Meci meci1(e1, e2, "21-06-2024");
        meci1.adauga_faza_gol(j1, j2);

        Pariu pariu1("Ion Ion", "Dinamo", 100.3);
        Pariu pariu2("Vasile Vasile", "Constanta", 100.5);
        meci1.plaseaza_pariu(pariu1);
        meci1.plaseaza_pariu(pariu2);

        std::cout << meci1 << '\n';
        std::cout << "Echipa castigatoare: " << meci1.verifica_castigator(e1, e2) << '\n' << '\n';
        meci1.evalueaza_pariuri();
        for (const auto &pariu: meci1.get_pariuri()) {
            std::cout << "Parior: " << pariu.getNumeParior() << ", Echipa: " << pariu.getEchipaPariata() << ", Suma: "
                      << pariu.getSumaPariata() << ", Castigator: " << (pariu.isCastigator() ? "Da" : "Nu")
                      << ", Suma castigata: " << pariu.val_suma_Castigata() << '\n' << '\n';
        }
        for (auto &it: meci1.afisez())
            std::cout << "Marcheaza " << it.first->getName() << " din pasa lui " << it.second->getName() << '\n';
        std::cout << '\n';
        Campionat_Liga_Nationala campionat(2, 30);
        std::cout << campionat << '\n';
        campionat.adaug_echipa(e1);
        campionat.adaug_echipa(e2);
        campionat.adaug_meci(meci1);
        std::cout << campionat << '\n';

        /*j1->change_status();
        std::cout<<*j1<<'\n';
        e2.transfer_la_echipa(e2,j1);

        Echipa e3("Baia Mare", "Lascar Pana Arena", 0, {});
        campionat.adaug_echipa(e3);*/

        std::cout << "----------------------------------------------------------------------------------------------"
                  << '\n' << '\n' << '\n';

        Echipa e3("Dinamo", "Stefan cel Mare", 0, {Antrenor{"Xavier Pascual", "Dinamo", 1, 3}.clone(),
                                                   Jucator{"Luca1 Cindric", "Dinamo", 1, "centru", 5, 3, 1}.clone(),
                                                   Jucator{"Vladimir Ciupara", "Dinamo", 1, "portar", 4, 6, 3}.clone(),
                                                   Jucator{"Luca1 Cindric1", "Dinamo", 1, "centru", 5, 3, 1}.clone(),
                                                   Jucator{"Luca1 Cindric2", "Dinamo", 1, "centru", 5, 3, 1}.clone(),
                                                   Jucator{"Luca1 Cindric3", "Dinamo", 1, "centru", 5, 3, 1}.clone(),
                                                   Jucator{"Luca1 Cindric4", "Dinamo", 1, "centru", 5, 3, 1}.clone(),
                                                   Jucator{"Luca1 Cindric5", "Dinamo", 1, "centru", 5, 3, 1}.clone(),
                                                   Jucator{"Luca1 Cindric6", "Dinamo", 1, "centru", 5, 3, 1}.clone(),
                                                   Jucator{"Luca1 Cindric7", "Dinamo", 1, "centru", 5, 3, 1}.clone()
        });
        Echipa::creare_Echipa();
        Echipa e4("Constanta", "Dobrogea Arena", 0, {Antrenor{"George Buricea", "Constanta", 1, 5}.clone(),
                                                     Jucator{"Vitaly Komogorov", "Constanta", 1, "inter stang", 3, 5,
                                                             2}.clone(),
                                                     Jucator{"Vasile Ion", "Constanta", 1, "extrema stanga", 7, 3,
                                                             4}.clone(),
                                                     Jucator{"Vasile Ion1", "Constanta", 1, "extrema stanga", 7, 3,
                                                             4}.clone(),
                                                     Jucator{"Vasile Ion2", "Constanta", 1, "extrema stanga", 7, 3,
                                                             4}.clone(),
                                                     Jucator{"Vasile Ion3", "Constanta", 1, "extrema stanga", 7, 3,
                                                             4}.clone(),
                                                     Jucator{"Vasile Ion4", "Constanta", 1, "extrema stanga", 7, 3,
                                                             4}.clone(),
                                                     Jucator{"Vasile Ion5", "Constanta", 1, "extrema stanga", 7, 3,
                                                             4}.clone(),
                                                     Jucator{"Vasile Ion6", "Constanta", 1, "extrema stanga", 7, 3,
                                                             4}.clone()
        });

        std::shared_ptr<Persoana> j5 = std::make_shared<Jucator>("Luca1 Cindric", "Dinamo", 1, "centru", 5, 3, 1);
        std::shared_ptr<Persoana> j6 = std::make_shared<Jucator>("Luca1 Cindric1", "Dinamo", 1, "centru", 5, 3, 1);
        std::shared_ptr<Persoana> j7 = std::make_shared<Jucator>("Vasile Ion", "Constanta", 1, "extrema stanga", 7, 3,
                                                                 4);
        std::shared_ptr<Persoana> j8 = std::make_shared<Jucator>("Vasile Ion1", "Constanta", 1, "extrema stanga", 7, 3,
                                                                 4);

        Meci meci2(e3, e4, "30-06-2024");
        meci2.adauga_faza_gol(j5, j6);
        meci2.adauga_faza_gol(j7, j8);
        meci2.adauga_faza_gol(j7, j8);
        meci2.adauga_faza_gol(j7, j8);
        meci2.adauga_faza_gol(j5, j6);
        meci2.adauga_faza_gol(j5, j6);
        meci2.adauga_faza_gol(j7, j8);
        meci2.adauga_faza_gol(j5, j6);
        meci2.adauga_faza_gol(j7, j8);
        meci2.adauga_faza_gol(j5, j6);
        meci2.adauga_faza_gol(j5, j6);
        meci2.adauga_faza_gol(j5, j6);
        meci2.adauga_faza_gol(j7, j8);
        meci2.adauga_faza_gol(j7, j8);
        meci2.adauga_faza_gol(j7, j8);
        meci2.adauga_faza_gol(j5, j6);
        meci2.adauga_faza_gol(j7, j8);
        meci2.adauga_faza_gol(j7, j8);
        meci2.adauga_faza_gol(j7, j8);
        meci2.adauga_faza_gol(j7, j8);
        meci2.adauga_faza_gol(j7, j8);
        meci2.adauga_faza_gol(j7, j8);
        meci2.adauga_faza_gol(j7, j8);
        meci2.adauga_faza_gol(j7, j8);

        //std::string castigator = meci2.verifica_castigator(e3,e4);
        int one = 0, two = 0;
        for (auto &it: meci2.afisez()) {
            if (it.first->getNameTeam() == e3.get_num()) {
                one++;
            } else
                two++;
        }
        std::cout << one << " " << two << '\n';

        using namespace indicators;
        // Configure first progress bar
        ProgressBar bar1{
                option::BarWidth{70},
                option::Start{"["},
                option::Fill{"■"},
                option::Lead{"■"},
                option::Remainder{" "},
                option::End{" ]"},
                option::ForegroundColor{Color::yellow},
                //option::ShowElapsedTime{true},
                //option::ShowRemainingTime{true},
                //option::PrefixText{e3.get_num() + "    "},
                option::PrefixText{"Echipa 1: "},
                option::FontStyles{std::vector<FontStyle>{FontStyle::bold}},
                option::MaxProgress{one + two},
                option::PostfixText{std::to_string(one)}
        };

        // Configure second progress bar

        ProgressBar bar2{
                option::BarWidth{70},
                option::Start{"["},
                option::Fill{"■"},
                option::Lead{"■"},
                //option::Fill{"="},
                //option::Lead{">"},
                option::Remainder{" "},
                option::End{" ]"},
                option::ForegroundColor{Color::cyan},
                //option::ShowElapsedTime{true},
                //option::ShowRemainingTime{true},
                //option::PrefixText{e4.get_num() + " "},
                option::PrefixText{"Echipa 2: "},
                option::FontStyles{std::vector<FontStyle>{FontStyle::bold}},
                option::MaxProgress{one + two},
                option::PostfixText{std::to_string(two)}
        };

        // Construct MultiProgress object
        indicators::MultiProgress<indicators::ProgressBar, 2> bars(bar1, bar2);

        std::cout << "Simulare meci campionat, detalii:" << meci2 << '\n';

        auto job1 = [&bars, &meci2, &e3]() {
            /*while (true) {
                bars.tick<0>();
                if (bars.is_completed<0>())
                    break;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }*/
            for (auto &it: meci2.afisez()) {
                if (it.first->getNameTeam() == e3.get_num()) {
                    bars.tick<0>();
                    //bar
                    //std::this_thread::sleep_for(std::chrono::milliseconds(200));
                }
            }
        };

        auto job2 = [&bars, &meci2, &e4]() {
            /*while (true) {
                bars.tick<1>();
                if (bars.is_completed<1>())
                    break;
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }*/
            for (auto &it: meci2.afisez()) {
                if (it.first->getNameTeam() == e4.get_num()) {
                    bars.tick<1>();
                    //std::this_thread::sleep_for(std::chrono::milliseconds(200));
                }
            }
        };

        std::thread first_job(job1);
        std::thread second_job(job2);

        first_job.join();
        second_job.join();

        return 0;
    }
    catch (const eroare_transfer &e) {
        std::cout << "Eroare transfer: " << e.what() << '\n';
    }
    catch (const eroare_numar_jucatori &e) {
        std::cout << "Eroare numar jucatori: " << e.what() << '\n';
    }
    catch (const std::exception &e) {
        std::cout << "Alta eroare" << e.what() << '\n';
    }
    return 0;
}