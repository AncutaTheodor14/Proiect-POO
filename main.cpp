#include<iostream>
#include<vector>
#include<memory>
#include<stdexcept>
#include<indicators.hpp>
#include "Echipa.h"
#include "Persoana.h"
#include "Antrenor.h"
#include "Jucator.h"
#include "Meci.h"
#include "Pariu.h"
#include "Campionat_Liga_Nationala.h"
#include "Exceptii.h"
#include "Doctor.h"
#include "Psiholog.h"

int Echipa::nr_total_echipe = 0;

int main() {
    try {
        std::shared_ptr<Persoana> p = std::make_shared<Antrenor>("Xavier Pascual", "Dinamo", true, 3);
        p->change_status();
        p->change_status();
        std::cout << *p << '\n';
        std::shared_ptr<Persoana> p1 = std::make_shared<Jucator>("Luca Cindric", "Dinamo", 1, "centru", 5, 3, 1);
        std::cout << *p1 << '\n';
        std::shared_ptr<Jucator> jucator1 = std::dynamic_pointer_cast<Jucator>(p1);
        if (jucator1) {
            std::cout << jucator1->getskill() << '\n';
            jucator1->Skill_Jucator();
            jucator1->antreneaza();
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
        Meci meci1(e1, e2, "21-06-2024", {});
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

        std::shared_ptr<Persoana> doc = std::make_shared<Doctor>("Alin Alin", "Dinamo", 1, "Kinetoterapeut", 6);
        std::cout << *doc << '\n';
        e1.verifica_Skill_jucatori(0);
        std::cout << j1->cost_deplasare(2, 300) << '\n';

        std::shared_ptr<Persoana> psi = std::make_shared<Psiholog>("Dan Ursu", "Dinamo", 1, 4);
        std::cout << *psi << '\n';
        /*j1->change_status();
        std::cout<<*j1<<'\n';
        e2.transfer_la_echipa(e2,j1);

        Echipa e3("Baia Mare", "Lascar Pana Arena", 0, {});
        campionat.adaug_echipa(e3);*/

        // e1.verifica_Skill_jucatori(20);
        //campionat.adaug_meci(meci1);

    }
    catch (const eroare_echipa &e) {
        std::cout << e.what() << '\n';
    }
    catch (const eroare_campionat &e) {
        std::cout << e.what() << '\n';
    }
    catch (const std::exception &e) {
        std::cout << "Alta eroare" << e.what() << '\n';
    }

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

    auto job1 = [&bars, &meci2, &e3, &one, &two]() {
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
                if (one > two)
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                else
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }
    };

    auto job2 = [&bars, &meci2, &e4, &one, &two]() {
        /*while (true) {
            bars.tick<1>();
            if (bars.is_completed<1>())
                break;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }*/
        for (auto &it: meci2.afisez()) {
            if (it.first->getNameTeam() == e4.get_num()) {
                bars.tick<1>();
                if (one > two)
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                else
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    };

    std::thread first_job(job1);
    std::thread second_job(job2);

    first_job.join();
    second_job.join();

    return 0;
}