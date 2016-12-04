#include "Menu.h"

using namespace std;

void Menu::printError(int er) {
    if (er == -1)
        cout << "Bledne dane!" << endl;
    if (er == 1)
        cout << "Bledny wybor!" << endl;
}

void Menu::tspMenu() {
    int op = -1;
    int check = 0;
    int err = 0;

    Graph *data = new Graph();
    do {
        printError(err);
        err = 0;
        printf("\n\nProblem komiwojazera:\n"
                       "[1] Laduj Plik\n"
                       "[2] Generuj Dane\n"
                       "[3] Zapisz Graf\n"
                       "[4] Algorytm Przegladu Zupelnego\n"
                       "[5] Algorytm Podzialu i Ograniczen\n"
                       "[0] Zakoncz\n"
                       "Wybierz: ");
        check = scanf("%d", &op);
        if (check != 1) {
            err = -1;
            fflush(stdin);
            continue;
        }
        switch (op) {
            case 1:
                File::load(*data);
                data->print();
                break;
            case 2:
                err = tspGenerate(data);
                data->print();
                break;
            case 3:
                if (File::save(*data))
                    puts("zapisano");
                else puts("\nbrak grafu");
                break;
            case 4:
                if (data->getPoints() == 0) {
                    puts("\nbrak grafu");
                    continue;
                }

                printf("Caly graf:\n");
                data->print();

                ATSP::BruteForce(data)->print();
                fflush(stdin);
                break;
            default:
                err = 1;
                break;
        }
    } while (op != 0);
}

int Menu::tspGenerate(Graph *data) {
    int size;
    cout << "Podaj ilosc miast: ";
    int check = scanf("%d", &size);
    if (check != 1) {
        data->generate(0);
        return -1;
    }
    data->generate(size, true);
    return 0;
}
