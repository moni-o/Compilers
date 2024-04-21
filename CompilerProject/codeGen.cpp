#include "codeGen.h"
#include<iostream>

stringstream ss;

void asmCode(vector<SymbolTable_Entries>& Symbol, Quad* quads, int quadsCount){
    linuxCongfig();
    dataSection(Symbol);
    bssSection(Symbol);
    codeSection(quads, quadsCount);



    writeX86("Pgm1.asm");
}

void linuxCongfig(){
    ss<<"sys_exit\teque\t1\n";
    ss<<"sys_read\teque\t3\n";
    ss<<"sys_write\teque\t4\n";
    ss<<"stdin\t\teque\t0\n";
    ss<<"stdout\t\teque\t1\n";
}
void dataSection(vector<SymbolTable_Entries>& Symbol){
    ss<<"section.data\n";
    ss<<"\tuserMsg\tdb\t\"Enter a integer:(lesst than 32,765):'\n";
    ss<<"\tlenUserMsgequ\t$-userMsg\n";
    ss<<"\tdisplayMsg\tdb\t'You entered: '\n";
    ss<<"\tlenDisplayMsg\tequ\t$-displayMsg\n";
    ss<<"\tnewline\tdb\t0xA\n";
    ss<<"\tTen\tDW\t10\n";
    ss<<"\tprintTempchar\tdb\t'Tempchar = :'\n";
    ss<<"\tlenPrintTempchar\tequ\t$-printTempchar\n";
    ss<<"\tResult\tdb\t'Ans='\n";
    ss<<"\tResultValue\tdb\'aaaaa'\n";
    ss<<"\t\t\tdb\t0xA\n";
    ss<<"\tResultEnd\tequ\t$-Result'\n";
    ss<<"\tnum\ttimes 6 db'ABCDEF'\n";
    ss<<"\tnumEnd\t\tequ\t$-num\n";

    for(int i = 0; i<Symbol.size(); i++){
    if(Symbol[i].classi == "ConstVar"){
        ss<<"\t"<<Symbol[i].symbol<<"\t\tDW\t"<<Symbol[i].val<<"\n";
    }
    else if(Symbol[i].classi == "Numeric Literal"){
        bool isDuplicate = false;
        int j = 0;
        while(j < i){
            if(Symbol[j].symbol == Symbol[i].symbol && Symbol[j].classi == "Numeric Literal"){
                isDuplicate = true;
                break;
            }
            j++;
        }
        if(!isDuplicate){
            ss<<"\tLit"<<Symbol[i].symbol<<"\tDW\t"<<Symbol[i].val<<"\n";
        }
        }
    }
    ss<<"\n\n";
}
void bssSection(vector<SymbolTable_Entries>& Symbol){
    ss<<"section\t.bss\n";
    ss<<"\tTempChar\tRESB\t1\n";
    ss<<"\ttestchar\tRESB\t1\n";
    ss<<"\tReadInt\t\tRESW\t1\n";
    ss<<"\ttempint\t\tRESW\t1\n";
    ss<<"\tnegflag\t\tRESB\t1\n";
    for(int i = 0; i<Symbol.size(); i++){
        if(Symbol[i].classi == "VAR" || Symbol[i].classi == "Var (int)"){
            ss<<"\t"<<Symbol[i].symbol<<"\t\tRESW\t1\n";
        }
    }

}
void codeSection(Quad* quad, int count){
    
    ss<<"\tglobal_start\n";
    ss<<"section.text\n";
    ss<<"_start:\t\tnop\n";


    for(int i = 0; i < count; i++){
        string OP = quad[i].op;
        switch(OP[0]){
            case('+'):
                ss<<"\tmov\tax,"<<"["<<quad[i].arg1<<"]"<<"\n";
                ss<<"\tadd\tax,"<<"["<<quad[i].arg2<<"]"<<"\n";
                ss<<"\tmov\t"<<"["<<quad[i].result<<"]"<<",ax\n";
                break;
            case('-'):
                ss<<"\tmov\tax,"<<"["<<quad[i].arg1<<"]"<<"\n";
                ss<<"\tsub\tax,"<<"["<<quad[i].arg2<<"]"<<"\n";
                ss<<"\tmov\t"<<"["<<quad[i].result<<"]"<<",ax\n";
                break;
            case('*'):
                ss<<"\tmov\tax,"<<"["<<quad[i].arg1<<"]"<<"\n";
                ss<<"\tmul\t"<<"["<<quad[i].arg2<<"]"<<"\n";
                ss<<"\tmov\t"<<"["<<quad[i].result<<"]"<<",ax\n";
                break;
            case('/'):
                ss<<"\tmov\tax,"<<"["<<quad[i].arg1<<"]"<<"\n";
                ss<<"\tdiv\t"<<"["<<quad[i].arg2<<"]"<<"\n";
                ss<<"\tmov\t"<<"["<<quad[i].result<<"]"<<",ax\n";
                break;
            case('>'):
                ss<<"\tmov\tax,"<<"["<<quad[i].arg1<<"]"<<"\n";
                ss<<"\tcmp\tax,"<<"["<<quad[i].arg2<<"]"<<"\n";
                break;
            case('<'):
                ss<<"\tmov\tax,"<<"["<<quad[i].arg1<<"]"<<"\n";
                ss<<"\tcmp\tax,"<<"["<<quad[i].arg2<<"]"<<"\n";
                break;
            case('L'):
                ss<<quad[i].op<<":"<<"\tNOP\n";
                
                break;
            default:
                if(quad[i].op == "THEN"){
                    ss<<"\t"<<quad[i].arg2<<"\t"<<quad[i].arg1<<"\n";
                    break;
                }
                if(quad[i].op == "=="){
                   ss<<"\tmov\tax,"<<"["<<quad[i].arg1<<"]"<<"\n";
                   ss<<"\tcmp\tax,"<<"["<<quad[i].arg2<<"]"<<"\n";
                    break;
                }
                if(quad[i].op == "="){
                    ss<<"\tmov\tax,"<<"["<<quad[i].arg2<<"]"<<"\n";
                    ss<<"\tmov\t"<<"["<<quad[i].arg1<<"]"<<",ax\n";
                    break;
                }
                if(quad[i].op == "ELSE"){
                    ss<<"\tJMP\t"<<quad[i].arg1<<"\n";
                    break;
                }
                if(quad[i].op == "WHILE"){
                    ss<<quad[i].arg1<<":";
                    break;
                }
                if(quad[i].op == "DO"){
                    ss<<"\t"<<quad[i].arg2<<"\t"<<quad[i].arg1<<"\n";
                    break;
                }
                if(quad[i].op == "CIN"){
                    //Confused?

                }
                if(quad[i].op == "COUT"){
                    //confused?
                }
                
                break;

            
        }
        
    }
}

void writeX86(const string& filename){
    ofstream file;
    file.open(filename);
    if(!file){
       cerr<<"Error: File not found\n";
    }
    else{
        file<<ss.str();
        file.close();
    }
}