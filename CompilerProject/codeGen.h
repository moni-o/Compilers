#ifndef codeGen_h
#define codeGen_h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "FSA2.h"
#include "POE.h"
using namespace std;



void asmCode(vector<SymbolTable_Entries>& Symbol, Quad* q, int count);

void linuxCongfig();
void dataSection(vector<SymbolTable_Entries>& Symbol);
void bssSection(vector<SymbolTable_Entries>& Symbol);
void codeSection(Quad* q, int count);
bool isNumericLiteral(const string& str);
void writeX86(const string& filename);
   





#endif // codeGen_h