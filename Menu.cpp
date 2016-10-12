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
                       "[1] Algorytm Przegladu Zupelnego\n"
                       "[2] Laduj Plik\n"
                       "[0] Powrot\nWybierz: ");
        check = scanf("%d", &op);
        if (check != 1) {
            err = -1;
            fflush(stdin);
            continue;
        }
        switch (op) {
            case 1:
                if (data->getPoints() == 0) {
                    printf("\nBrak grafu\n");
                    continue;
                }

                printf("Caly graf:\n");
                data->print();

                ATSP::BruteForce(data)->print();
                fflush(stdin);
                break;
            case 2:
                FileSupport::loadTspFile(*data);
                data->print();
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
    cout << "Skierowany? [1]Nie [2]Tak: ";
    int oneway;
    check += scanf("%d", &oneway);
    if (check != 2) {
        data->generate(0);
        return -1;
    }
    data->generate(size, bool(oneway - 1));
    return 0;
}
