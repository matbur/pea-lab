#pragma once

#include "Graph.h"

#include <iostream>
#include <string>

using namespace std;

class FileSupport {

public:
    //Laduje dane z pliku dla problemu komiwojazera
    static bool loadTspFile(Graph &data);

    //Laduje dane z pliku dla problemu komiwojazera
    static bool loadTspFile(const string &fileName, Graph &data);
};

