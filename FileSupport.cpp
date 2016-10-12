#include "FileSupport.h"


bool FileSupport::loadTspFile(const string &fileName, Graph &data) {
    FILE *filePtr;
    int el = 0;
    int check;
    int value;
    if ((filePtr = fopen(fileName.c_str(), "r")) != NULL) {
        check = fscanf(filePtr, "%d", &el);
        if (check != 1) {
            data.reset(0);
            cout << "Blad wczytywania z pliku!" << endl;
            return false;
        }
        data.reset(el);
        for (int it = 0; it < el; it++) {
            for (int i = 0; i < el; i++) {
                check = fscanf(filePtr, "%d", &value);
                if (check == 1) {
                    if (value != 0 and value != -1)
                        data.addEdge(it, i, value);
                }
                else {
                    data.reset(0);
                    cout << "Blad wczytywania z pliku! Nieprawidlowa ilsoc parametrow!" << endl;
                    return false;
                }
            }
        }
        check = fscanf(filePtr, "%d", &value);
        if (check == 1) {
            data.reset(0);
            cout << "Blad wczytywania z pliku! Dodatkowe elementy grafu!" << endl;
            return false;
        }
    } else {
        data.reset(0);
        cout << "Blad wczytywania z pliku! Nie odnaleziono pliku!" << endl;
        return false;
    }
    return true;
}

bool FileSupport::loadTspFile(Graph &data) {
    string fileName;
    cout << "Podaj nazwe pliku: ";
    cin >> fileName;
    return loadTspFile(fileName, data);
}



