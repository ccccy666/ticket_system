#include <iostream>
#include <cstring>
#include "b+tree.h"

using std::string;
#ifndef CODE_ACCOUNT_H
#define CODE_ACCOUNT_H
class user_id{
public:
    char userid[22];
    user_id(){};
    user_id(std::string &in){
        //if(in.size()>20)printf("-1\n");

        for(int i=0;i<in.size();i++){
            userid[i]=in[i];
        }
        userid[in.size()]='\0';
    }
    user_id(const user_id &other){
        strcpy(userid,other.userid);
    }
    ~user_id(){}
    bool operator==(const user_id &other)const{
        return (!strcmp(userid,other.userid));
    }
    bool operator!=(const user_id &other)const{
        return (strcmp(userid,other.userid));
    }
    bool operator <(const user_id &other)const{
        return (strcmp(userid,other.userid)<0);
    }
    bool operator <=(const user_id &other)const{
        return ((strcmp(userid,other.userid)<0)||(!strcmp(userid,other.userid)));
    }
    bool operator >=(const user_id &other)const{
        return !(*this<other);
        //return ((strcmp(userid,other.userid)<0)||(!strcmp(userid,other.userid)));
    }
    bool operator >(const user_id &other)const{
        return (!(*this<other))&&(!(*this==other));
        //return ((strcmp(userid,other.userid)<0)||(!strcmp(userid,other.userid)));
    }
};

class account{
public:
    user_id id;
    char password[32];
    char name[20];
    char email[42];
    int privilege=0;
    account():id(){
        password[0]='\0';
        name[0]='\0';
        email[0]='\0';
    }
    account(const account &other):id(other.id){
        strcpy(password,other.password);
        strcpy(name,other.name);
        strcpy(email,other.email);
        //strcpy(id.userid,other.id.userid);
        privilege=other.privilege;
    }
    ~account(){}
    bool operator<(const account &other)const{
        return id<other.id;
    }
    bool operator==(const account &other)const{
        return id==other.id;
    }
    bool operator!=(const account &other)const{
        return !(id==other.id);
    }
};

class All_account{
public:
    //string file;
    b_plus_tree<user_id,account> tr;
    All_account():tr("ac"){};
    ~All_account(){}

    bool exist(user_id &id){
        return tr.exist(id);
    }

    void insert(account &acc){
        point<user_id,account> p(acc.id,acc);
        tr.insert(p);
    }
    account find(user_id &id){

        return tr.find(id);
    }

    void mywrite(block<user_id,account> &bk){

        tr.mywrite(bk.place,bk);
    }
    block<user_id,account> getblock(user_id &id){
        return tr.getblock(id);
    }
    void clear(){
        tr.root=-1;
        tr.total=-1;
    }
    void del(){

    };

};
#endif //CODE_ACCOUNT_H
