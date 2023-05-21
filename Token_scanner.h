#include <iostream>

#ifndef CODE_TOKEN_SCANNER_H
#define CODE_TOKEN_SCANNER_H
using std::string;
class scanner{
public:
    string line;
    int pos;
    //bool move=0;
    scanner(){
        line="";
        pos=0;
    }
    ~scanner(){}
    void setInput(string &line_){
        line=line_;
        if(line[line.size()-1]=='\r'||line[line.size()-1]=='\n')line.pop_back();
        pos=0;
        //line=line-line[line.size()-1];
    }

    string nextToken (){
        //if(move)line.pop_back()
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
        while(line[pos]!=' '&&line[pos]!='\0'&&line[pos]!='\n'){
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
        if(line[k]=='\0'||line[k]=='\n')return false;
        return true;
    }
};

#endif //CODE_TOKEN_SCANNER_H
