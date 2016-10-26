#pragma once

#include <string>
#include <iostream>

#include "Graph.h"


using namespace std;

class File {

public:
    //Laduje dane z pliku dla problemu komiwojazera
    static bool loadTspFile(Graph &data);

    //Laduje dane z pliku dla problemu komiwojazera
    static bool load(const string &fileName, Graph &data);
};

