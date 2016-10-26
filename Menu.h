#pragma once

#include "Graph.h"
#include "File.h"
#include "ATSP.h"

class Menu {
private:
    static void printError(int er);

    static int tspGenerate(Graph *data);

public:
    static void tspMenu();
};

