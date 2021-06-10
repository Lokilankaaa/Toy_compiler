//
// Created by xurunsen on 6/10/21.
//

#include "CodeGenerator.h"
using namespace TOY_COMPILER;
using namespace std;

void CodeGenerator::generate_LR(rootProgram &program)
{
    cout << "[INFO] IR Generation begins." << endl;
    program.codeGen(*this);
    cout << "[INFO] IR Generation ends." << endl;
}
