#include <iostream>
#include <fstream>
#include "FSA.h"
#include <vector>
using namespace std;

int main(){
    //ofstream myfile("tokens");
    string a = "hello world";
    initFSA();
    cout<<"please enter a character: "<<endl;
    
    vector<token> tokens =tokenizer(a);
    for(const auto& token: tokens){
        cout<<"Token "<<token.value<<" type: "<< token.classification<<endl;
    }
    

}