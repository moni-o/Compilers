#include <iostream>
#include <fstream>
#include <sstream>
#include "FSA.h"
#include "FSA2.h"
#include "POE.h"
#include <vector>
#include <iomanip>
#include "codeGen.h"
using namespace std;

int main(){
    //ofstream myfile("tokens");

    initFSA();
    initFSA2();
   
    string filePath = "Pgm1.txt"; // Path to the file to read
    ifstream file(filePath);
    stringstream buffer;
    int x = 20;
    

    if (!file.is_open()) {
        
        return EXIT_FAILURE;
     }
    buffer << file.rdbuf();
    
     string input = buffer.str();

     file.close(); // Close the file


    ini_PO_TABLE();

   vector<token> tokens =tokenizer(input);
    for(const auto& token: tokens){
        cout<<token.value<<" type: "<< token.classification<<endl;
    };

    vector<SymbolTable_Entries> symbol = SymbolTable(tokens);

    parseTokens(tokens);

    Quad* quads= getQuadArray();
    int quadcount = getQuadCount();
    
    

    cout<<"Symbol"<<setw(x-2)<<" Classification"<<setw(x)<<" Value"<<setw(x)<<" Address"<<setw(x)<<" Segment"<<endl;
     for(const auto& token: symbol){
       cout<<token.symbol<<std::right<<setw(x)<<token.classi<<setw(x)<<token.val<<setw(x)<<token.addr<<setw(x)<<token.seg<<endl;
    }

   asmCode(symbol, quads, quadcount);

    return 0;
}