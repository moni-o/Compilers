#include <iostream>
#include <fstream>
#include <sstream>
#include "FSA.h"
#include <vector>
using namespace std;

int main(){
    //ofstream myfile("tokens");

    initFSA();
   
    string a = "hello";

    string filePath = "Pgm1.txt"; // Path to the file to read
    ifstream file(filePath);
    stringstream buffer;

    if (!file.is_open()) {
        
        return EXIT_FAILURE;
    }
    buffer << file.rdbuf();
    
    string input = buffer.str();

    file.close(); // Close the file




   vector<token> tokens =tokenizer(input);
    for(const auto& token: tokens){
        cout<<token.value<<" type: "<< token.classification<<endl;
    }
    

}