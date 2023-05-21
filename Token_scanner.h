#include <iostream>

#ifndef B_TREE_TOKEN_SCANNER_H
#define B_TREE_TOKEN_SCANNER_H
using std::string;
class scanner{
public:
    string line;
    int pos;
    scanner(){}
    ~scanner(){}
    void setInput(string &line_){
        line=line_;
        pos=0;
    }

    string nextToken (){
        bool flag=0;
        for(int j=0;j<line.length();j++){
            if(line[j]!=' '){
                flag=1;
                break;
            }
        }
        if(!flag){
            return " ";
        }
        if(!hasMoreTokens())return "";
        //int i=0;

        std::string ss;

        while(line[pos]==' '){
            pos++;
        }
        while(line[pos]!=' '&&line[pos]!='\0'){
            //if(line[pos]<32||line[pos]==127)return "";
            ss+=line[pos];
            pos++;
            //i++;
        }
        return ss;
    }

    bool hasMoreTokens(){
        int k=pos;
        while(line[k]==' '){
            k++;
        }
        if(line[k]=='\0')return false;
        return true;
    }
};

#endif //B_TREE_TOKEN_SCANNER_H
