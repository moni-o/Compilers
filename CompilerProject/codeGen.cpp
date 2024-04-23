#include "codeGen.h"
#include<iostream>
#include<cctype>
#include<algorithm>

stringstream ss;

void asmCode(vector<SymbolTable_Entries>& Symbol, Quad* quads, int quadsCount){
    string filename;
    linuxCongfig();
    filename = dataSection(Symbol);
    cout<<filename<<endl;
    filename = filename + ".asm";
    bssSection(Symbol);
    codeSection(quads, quadsCount);

    ss<<"fini:\n";
    ss<<"\tmov\teax,sys_exit\n";
    ss<<"\txor\tebx,ebx\n";
    ss<<"\tint\t80h\n";




    //PrintString Procedure
    ss<<"PrintString:\n";
    ss<<"\tpush\tax\n";
    ss<<"\tpush\tdx\n";  
	ss<<"\tmov\teax,4\n";
    ss<<"\tmov\tebx,1\n";
    ss<<"\tmov\tecx,userMsg\n";	
    ss<<"\tmov\tedx,lenUserMsg\n";
    ss<<"\tint\t80h\n";
	ss<<"\tpop\tdx\n";
    ss<<"\tpop\tax\n";
	ss<<"\tret\n";
	ss<<"\n\n";

    //GetAnInteger Procedure
    ss<<"GetAnInteger:\n";
    ss<<"\tmov\teax,3\n";
    ss<<"\tmov\tebx,2\n";
    ss<<"\tmov\tecx,num\n";
    ss<<"\tmov\tedx,6\n";
    ss<<"\tint\t0x80\n";
    ss<<"\tmov\tedx,eax\n";
    ss<<"\tmov\teax,4\n";
    ss<<"\tmov\tebx,1\n";
    ss<<"\tint 80h\n";

    //ConvertStringToInteger
    ss<<"ConvertStringToInteger:\n";
    ss<<"\tmov\tax,0\n";
    ss<<"\tmov[ReadInt],ax\n";
    ss<<"\tmov\tecx,num\n";

    ss<<"\tmov\tbx,0\n";
    ss<<"\tmov\tbl,byte[ecx]\n";

    //Next
    ss<<"Next:\tsub\tbl,'0'\n";
    ss<<"\tmov\tax,[ReadInt]\n";
    ss<<"\tmov\tdx,10\n";
    ss<<"\tmul\tdx\n";
    ss<<"\tadd\tax,bx\n";
    ss<<"\tmov\t[ReadInt],ax\n";

    ss<<"\tmov\tbx,0\n";
    ss<<"\tadd\tecx,1\n";
    ss<<"\tmov\tbl,byte[ecx]\n";

    ss<<"\tcmp\tbl,0XA\n";
    ss<<"\tjne\tNext\n";
    ss<<"\tret\n";

    ss<<"\n\n";
    //ConvertIntegerToString
    ss<<"ConvertIntegerToString:\n";
    ss<<"\tmov\tebx,ResultValue + 4\n";
    //Convert Loop
    ss<<"ConvertLoop:\n";
    ss<<"\tsub\tdx,dx\n";
    ss<<"\tmov\tcx,10\n";
    ss<<"\tdiv\tcx\n";
    ss<<"\tadd\tdl,'0'\n";
    ss<<"\tmov [ebx], dl\n";
    ss<<"\tdec\tebx\n";
    ss<<"\tcmp\tebx,ResultValue\n";
    ss<<"\tjge\tConvertLoop\n";
    ss<<"\tret\n";
    fileX86(filename);
}

void linuxCongfig(){
    ss<<"sys_exit\tequ\t1\n";
    ss<<"sys_read\tequ\t3\n";
    ss<<"sys_write\tequ\t4\n";
    ss<<"stdin\t\tequ\t0\n";
    ss<<"stdout\t\tequ\t1\n";
    ss<<"\n\n";
}
string dataSection(vector<SymbolTable_Entries>& Symbol){

    string filename;

    ss<<"section\t.data\n";
    ss<<"\tuserMsg\tdb\t\'Enter a integer:(lesst than 32,765):'\n";
    ss<<"\tlenUserMsg\tequ\t$\t-\tuserMsg\n";
    ss<<"\tdisplayMsg\tdb\t'You entered: '\n";
    ss<<"\tlenDisplayMsg\tequ\t$-displayMsg\n";
    ss<<"\tnewline\tdb\t0xA\n";
    ss<<"\tTen\tDW\t10\n";
    ss<<"\tprintTempchar\tdb\t'Tempchar = :'\n";
    ss<<"\tlenPrintTempchar\tequ\t$-printTempchar\n";
    ss<<"\tResult\tdb\t'Ans='\n";
    ss<<"\tResultValue\tdb\'aaaaa'\n";
    ss<<"\t\t\tdb\t0xA\n";
    ss<<"\tResultEnd\tequ\t$-Result\n";
    ss<<"\tnum\ttimes 6 db'ABCDEF'\n";
    ss<<"\tnumEnd\t\tequ\t$-num\n";

    for(int i = 0; i<Symbol.size(); i++){
     if(Symbol[i].classi == "Program Name"){
        filename = Symbol[i].symbol;
     }
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
    return filename;
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

    ss<<"\n\n";

}
void codeSection(Quad* quad, int count){
  
    ss<<"\tglobal\t_start\n\n";
    ss<<"section\t.text\n\n";
    ss<<"_start:\t\tnop\n";
    ss<<"Again:";



    for(int i = 0; i < count; i++){
        string OP = quad[i].op; // I save the Operator value in the string OP
        string arg1 = quad[i].arg1;
        string arg2 = quad[i].arg2;
        string result = quad[i].result;

         if (isNumericLiteral(arg1)) {
            arg1 = "Lit" + arg1;  // Prefix numeric literals
        }
        if (isNumericLiteral(arg2)) {
            arg2 = "Lit" + arg2;  // Prefix numeric literals
        }




        switch(OP[0]){  // I use the first character of the OP string  to determine the operation, this allowed me to use switch statments
            case('+'): 
                ss<<"\tmov\tax,"<<"["<<arg1<<"]"<<"\n";
                ss<<"\tadd\tax,"<<"["<<arg2<<"]"<<"\n";
                ss<<"\tmov\t"<<"["<<result<<"]"<<",ax\n";
                break;
            case('-'):
                ss<<"\tmov\tax,"<<"["<<arg1<<"]"<<"\n";
                ss<<"\tsub\tax,"<<"["<<arg2<<"]"<<"\n";
                ss<<"\tmov\t"<<"["<<result<<"]"<<",ax\n";
                break;
            case('*'):
                ss<<"\tmov\tax,"<<"["<<arg1<<"]"<<"\n";
                ss<<"\tmul\tword\t"<<"["<<arg2<<"]"<<"\n";
                ss<<"\tmov\t"<<"["<<result<<"]"<<",ax\n";
                break;
            case('/'):
                ss<<"\tmov\tax,"<<"["<<arg1<<"]"<<"\n";
                ss<<"\tdiv\t"<<"["<<arg2<<"]"<<"\n";
                ss<<"\tmov\t"<<"["<<result<<"]"<<",ax\n";
                break;
            case('>'):
                ss<<"\tmov\tax,"<<"["<<arg1<<"]"<<"\n";
                ss<<"\tcmp\tax,"<<"["<<arg2<<"]"<<"\n";
                break;
            case('<'):
                ss<<"\tmov\tax,"<<"["<<arg1<<"]"<<"\n";
                ss<<"\tcmp\tax,"<<"["<<arg2<<"]"<<"\n";
                break;
            case('L'):
                ss<<OP<<":"<<"\tNOP\n";
                break;
            default: //If none of the above cases are met, then the default case , this contains if statemtns and checks the whole string.
                 if(quad[i].op == "CIN"){
                    ss<<"\tcall PrintString\n";
                    ss<<"\tcall GetAnInteger\n";
                    ss<<"\tmov\tax,[ReadInt]\n";
                    ss<<"\tmov\t["<<arg1<<"]"<<",ax\n";
                }
                if(quad[i].op == "COUT"){
                    ss<<"\tmov\tax,"<<"["<<arg1<<"]"<<"\n";
                    ss<<"\tcall\tConvertIntegerToString\n";
                    ss<<"\tmov\teax,4\n";
                    ss<<"\tmov\tebx,1\n";
                    ss<<"\tmov\tecx,Result\n";
                    ss<<"\tmov\tedx,ResultEnd\n";
                    ss<<"\tint\t80h\n";
                }
                if(quad[i].op == "THEN"){
                    ss<<"\t"<<arg2<<"\t"<<arg1<<"\n";
                    break;
                }
                if(quad[i].op == "=="){ //Needed to be in the default case because of the == operator
                   ss<<"\tmov\tax,"<<"["<<arg1<<"]"<<"\n";
                   ss<<"\tcmp\tax,"<<"["<<arg2<<"]"<<"\n";
                    break;
                }
                if(quad[i].op == "="){ //Needed to be in the default case because I needed to check to make sure the operator was an equal sign
                    ss<<"\tmov\tax,"<<"["<<arg2<<"]"<<"\n";
                    ss<<"\tmov\t"<<"["<<arg1<<"]"<<",ax\n";
                    break;
                }
                if(quad[i].op == "ELSE"){
                    ss<<"\tJMP\t"<<arg1<<"\n";
                    break;
                }
                if(quad[i].op == "WHILE"){
                    ss<<arg1<<":";
                    break;
                }
                if(quad[i].op.substr(0,1) == "W" && OP != "WHILE"){
                    ss<<"\tJMP\t"<<OP<<"\n";
                     break;
                }
                if(quad[i].op == "DO"){
                    ss<<"\t"<<arg2<<"\t"<<arg1<<"\n";
                    break;
                }
               
                break;

            
        }
        
    }

    ss<<"\n\n";
    




    
}

bool isNumericLiteral(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}


void fileX86(const string& filename){
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