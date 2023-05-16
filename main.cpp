//#include <iostream>
#include "Token_scanner.h"
#include "Account.h"
#include "Train.h"
#include "map.hpp"
//#include"order.h"
using std::string;
int hour,min,month,day;

int stringToInt(std::string &str) {
    int num = 0;
    for (int i = 0; i < str.length(); i++) {
        num = num * 10 + str[i] - 'a';
    }
    return num;
}

void stringTochar(std::string &s, char a[]) {
    for (int i = 0; i < s.length(); i++) {
        a[i] = s[i];
    }
    a[s.length()] = '\0';
}

void dealtime(int &traveltime){
    //traveltime=tra.travelTime[i];
    int addhour=traveltime/60,addmin=traveltime%60;
    min+=addmin;
    if(min>=60){
        addhour+=1;
        min%=60;
    }
    hour+=addhour;
    if(hour>=24){
        day+=hour/24;
        hour%=24;
    }
    if(month==6&&day>=31){
        month+=1;
        day-=30;
    }
    if((month==7&&day>=32)||(month==8&&day>=32)){
        month+=1;
        day-=31;
    }
}

void print(){
    printf("0%d-",month);
    if(day<10)printf("0");
    printf("%d ",day);
    if(hour<10)printf("0");
    printf("%d:",hour);
    if(min<10)printf("0");
    printf("%d ",min);
}

int main() {
    freopen("in.txt","r",stdin);
    freopen("1.txt", "w", stdout);
    sjtu::map<user_id, account> now_user;
    //if(now_user.)
    //int log_num=0;
    string line, op, opp;
    All_account all_ac;
    All_train all_train;
    order order_;
    pendings wait;
    scanner scan;
    while (getline(std::cin, line)) {////////////////
        //std::cout<<1<<std::endl;
        bool flag=0;
        scan.setInput(line);
        op = scan.nextToken();
        //return "bye";
        string  s ;
        for(int i=1;i<op.size()-1;i++){
            s+=op[i];
        }
        std::cout<<'['<<s<<']'<<' ';
        //printf("d ",tim);
        op = scan.nextToken();
        if (op == "add_user") {
            account ac;//new account
            while (scan.hasMoreTokens()) {
                user_id _id;
                op = scan.nextToken();
                opp = scan.nextToken();
                if (op == "-g") {
                    if (now_user.empty()) {
                        ac.privilege = 10;
                    } else {
                        ac.privilege = stringToInt(opp);
                    }
                } else if (op == "-c" && !now_user.empty()) {
                    if (all_ac.exist(_id)) {
                        printf("-1\n");
                        flag=1;
                        break;
                    }
                    _id = opp;
                    auto it = now_user.find(_id);
                    if (it == now_user.end()) {
                        printf("-1\n");
                        flag=1;
                        break;
                    }
                } else if (op == "-u") {
                    _id = opp;
                    ac.id = opp;

                } else if (op == "-p") {
                    stringTochar(opp, ac.password);
                } else if (op == "-n") {
                    stringTochar(opp, ac.name);
                } else if (op == "-m") {
                    stringTochar(opp, ac.email);
                }
            }
            if(flag)continue;
            printf("0\n");

            all_ac.insert(ac);
        } else if (op == "login") {
            char word[32];
            account ac;
            user_id idd;
            while (scan.hasMoreTokens()) {
                op = scan.nextToken();
                opp = scan.nextToken();
                if (op == "-u") {
                    idd = opp;
                    if (!all_ac.exist(idd)) {
                        printf("-1\n");
                        flag=1;
                        break;
                    }
                    ac = all_ac.find(idd);
                } else if (op == "-p") {
                    stringTochar(opp, word);
                }

            }
            if (strcmp(ac.password, word)) {
                printf("-1\n");
                flag=1;
                break;
            }
            if(flag)continue;
            printf("0\n");

            now_user[idd] = ac;
        } else if (op == "logout") {
            user_id _id;
            op = scan.nextToken();
            opp = scan.nextToken();
            _id = opp;
            auto it = now_user.find(_id);
            if (it == now_user.end()) {
                printf("-1\n");
                continue;

                //break;
            }
            printf("0\n");

            now_user.erase(it);
        } else if (op == "query_profile") {
            account ac;
            user_id _id, id;//_id查询者,id被查询者
            while (scan.hasMoreTokens()) {
                op = scan.nextToken();
                opp = scan.nextToken();
                if (op == "-c") {
                    _id = opp;
                    auto it = now_user.find(_id);
                    if (it == now_user.end()) {
                        printf("-1\n");
                        flag=1;
                        break;
                    }

                } else if (op == "-u") {
                    id = opp;
                    if (!all_ac.exist(id)) {
                        printf("-1\n");
                        flag=1;
                        break;
                    }
                    ac = all_ac.find(id);
                }
            }
            if (now_user[_id].privilege < ac.privilege) {
                printf("-1\n");
                flag=1;

            }
            if(flag)continue;
            //printf("0\n");

            printf("%s %s %s %d\n", ac.id.userid, ac.name, ac.email, ac.privilege);
            //std::cout<<ac;
        } else if (op == "modify_profile") {
            block<user_id, account> blk;
            bool flagp = 0, flagn = 0, flagm = 0, flagg = 0;
            account ac;
            user_id _id, id;//_id查询者,id被查询者
            while (scan.hasMoreTokens()) {
                op = scan.nextToken();
                opp = scan.nextToken();
                if (op == "-g") {
                    flagg = 1;
                    ac.privilege = stringToInt(opp);
                } else if (op == "-c") {
                    _id = opp;
                    auto it = now_user.find(_id);
                    if (it == now_user.end()) {
                        printf("-1\n");
                        flag=1;
                        break;
                    }
                } else if (op == "-u") {
                    id = opp;
                    ac.id = id;
                    if (!all_ac.exist(id)) {
                        printf("-1\n");
                        flag=1;
                        break;
                    }
                    blk = all_ac.getblock(id);
                } else if (op == "-p") {
                    flagp = 1;
                    stringTochar(opp, ac.password);
                } else if (op == "-n") {
                    flagn = 1;
                    stringTochar(opp, ac.name);
                } else if (op == "-m") {
                    flagm = 1;
                    stringTochar(opp, ac.email);
                }
            }
            if(flag)continue;
            int tmp = 0;
            for (int i = 0; i < blk.size; i++) {
                if (id == blk.ele[i].index)break;
                tmp++;
            }//blk.ele[tmp].valu.password=ac.password;
            if (now_user[_id].privilege < blk.ele[tmp].valu.privilege) {
                printf("-1\n");
                continue;
            }

            if (flagp)strcpy(blk.ele[tmp].valu.password, ac.password);
            if (flagn)strcpy(blk.ele[tmp].valu.name, ac.name);
            if (flagm)strcpy(blk.ele[tmp].valu.email, ac.email);
            if (flagg)blk.ele[tmp].valu.privilege = ac.privilege;
            printf("%s %s %s %d\n", blk.ele[tmp].valu.id.userid, blk.ele[tmp].valu.name, blk.ele[tmp].valu.email,
                   blk.ele[tmp].valu.privilege);
//            if(tmp==0){
//                point<user_id,account>p=blk.mini;
//                blk.mini=blk.ele[0];
//                all_ac.tr.change(blk,p,blk.mini);
//            }
            all_ac.mywrite(blk);
        } else if (op == "add_train") {
            int seat;
            trainID id;
            train tra;
            while(scan.hasMoreTokens()){
                int tmp=1;
                string word;
                op=scan.nextToken();
                opp=scan.nextToken();
                if(op=="-i"){
                    id=opp;
                    if(all_train.exist(id)){
                        printf("-1\n");
                        flag=1;
                        break;
                    }
                    tra.id=opp;
                }else if(op=="-n"){
                    tra.station_num= stringToInt(opp);
                }else if(op=="-m"){
                     seat=stringToInt(opp);
//                    for(int i=1;i<104;i++){
//                        tra.seats[i]=seat;
//                    }

                }else if(op=="-s"){
                    for(int i=0;i<opp.size();i++){
                        if(opp[i]=='|'||i==opp.length()-1){
                            if(i==opp.length()-1)word+=opp[i];
                            tra.name[tmp].num=tmp;
                            tra.name[tmp++]=word;
                            word="";
                            continue;
                        }
                        word+=opp[i];
                    }
                }else if(op=="-p"){
                    for(int i=0;i<opp.size();i++){
                        if(opp[i]=='|'||i==opp.length()-1){
                            if(i==opp.length()-1)word+=opp[i];
                            tra.price[tmp]= tra.price[tmp-1]+stringToInt(word);//从第一站走i个站票价
                            tmp++;
                            word="";
                            continue;
                        }
                        word+=opp[i];
                    }
                }else if(op=="-x"){
                    tra.startTime=opp;
                    //stringTochar(opp,tra.startTime);
                }else if(op=="-t"){
                    for(int i=0;i<opp.size();i++){
                        if(opp[i]=='|'||i==opp.length()-1){
                            if(i==opp.length()-1)word+=opp[i];
                            tra.travelTime[tmp]=tra.travelTime[tmp-1]+ stringToInt(word);
                            tmp++;
                            word="";
                            continue;
                        }
                        word+=opp[i];
                    }
                }else if(op=="-o"){
                    if(opp!="_"){
                        for(int i=0;i<opp.size();i++){
                            if(opp[i]=='|'||i==opp.length()-1){
                                if(i==opp.length()-1)word+=opp[i];
                                tra.stopTime[tmp+1]=tra.stopTime[tmp]+ stringToInt(word);
                                tmp++;
                                word="";
                                continue;
                            }
                            word+=opp[i];
                        }
                    }

                }else if(op=="-d"){
                    string a,b;
                    bool fl=0;
                    //char b[8];
                    for(int i=0;i<opp.size();i++){
                        if(opp[i]=='|'||i==opp.length()-1){
                            if(i==opp.length()-1)word+=opp[i];
                            if(!fl){
                                a=word;fl=1;
                            }
                            else b=word;
                            word="";
                            continue;
                        }
                        word+=opp[i];
                    }
                    if(a<=b){
                        tra.startsale=a;
                        tra.finishsale=b;
//                        strcpy(tra.startsale.date,a);
//                        strcpy(.date,b);
                    }else{
                        tra.startsale=b;
                        tra.finishsale=a;
//                        strcpy(tra.startsale,b);
//                        strcpy(tra.finishsale,a);
                    }
                }else if(op=="-y"){
                    tra.type=opp[0];
                }
            }
            if(flag)continue;
            printf("0\n");
            for(int i=1;i<=tra.finishsale-tra.startsale+1;i++){
                for(int j=1;j<=tra.station_num-1;j++){
                    tra.seats[i][j]=seat;
                }
            }
            all_train.insert(tra);
        } else if (op == "delete_train") {
            trainID id;
            train tra;
            id=opp;
            tra=all_train.find(id);
            if(tra.released){
                printf("-1\n");
            }else{
                printf("0\n");
                for(int i=1;i<=tra.station_num;i++){
                    point_<station_name,train>pp(tra.name[i],tra);
                    all_train.del_(pp);
                }
                point<trainID,train>p(id,tra);
                all_train.del(p);
            }

        } else if (op == "release_train") {
            trainID id;
            train tra;
            block<trainID,train> blk;
            block_<station_name,train> bk;
            id=opp;
            if(!all_train.exist(id)){
                printf("-1\n");
                continue;
            }
            blk=all_train.getblock(id);
            int tmp=0;
            for (int i = 0; i < blk.size; i++) {
                if (id == blk.ele[i].index){
                    tra=blk.ele[i].valu;
                    break;
                }
                tmp++;
            }
            blk.ele[tmp].valu.released=1;
            for(int i=1;i<=tra.station_num;i++){
                point_<station_name,train> p(tra.name[i],tra);
                bk=all_train.getblock_(p);
                int tp=0;
                for (int j = 0; j < blk.size; j++) {
                    if (p == bk.ele[j]){
                        //tra=blk.ele[i].valu;
                        break;
                    }
                    tp++;
                }
                bk.ele[tp].valu.released=1;
                all_train.mywrite_(bk);
            }
//            if(tmp==0){
//                point<trainID,train>p=blk.mini;
//                blk.mini=blk.ele[0];
//                all_train.tr.change(blk,p,blk.mini);
//            }
            all_train.mywrite(blk);
            printf("0\n");
        } else if (op == "query_train") {
            saleDate sd;
            trainID id;
            train tra;
            char stTime[8];
            while(scan.hasMoreTokens()){
                op=scan.nextToken();
                opp=scan.nextToken();
                if(op=="-i"){
                    id=opp;
                    if(!all_train.exist(id)){
                        printf("-1\n");
                        flag=1;
                        break;
                    }
                    tra=all_train.find(id);
                }else if(op=="-d"){
                    sd=opp;
                    stringTochar(opp,stTime);

                }
            }
            if(strcmp(stTime,tra.startsale.date)<0|| strcmp(stTime,tra.finishsale.date)>0){
                printf("-1\n");
                flag=1;
            }
            if(flag)continue;
            int traveltime;
            int delt=sd-tra.startsale;
            for(int i=1;i<=tra.station_num;i++){
                printf("%s ",tra.name[i].name);
                if(i==1){
                    printf("xx-xx xx:xx -> ");
                    printf("%s %s %d %d\n",sd.date,tra.startTime.date,tra.price[i-1],tra.seats[delt+1][i]);
                    hour=tra.startTime.hour,min=tra.startTime.min;
                    month=sd.month,day=sd.day;

                }else if(i==tra.station_num){
                    print();
                    printf("-> ");
                    printf("xx-xx xx:xx ");
                    printf("%d x",tra.price[i-1]);
                }else{
                    print();
                    printf("-> ");//到站信息
                    traveltime=tra.stopTime[i]-tra.stopTime[i-1];
                    dealtime(traveltime);
                    print();
                    printf("%d %d",tra.price[i-1],tra.seats[delt+1][i]);
                }
                traveltime=tra.travelTime[i]-tra.travelTime[i-1];
                dealtime(traveltime);
                //price+=tra.price[i];
            }

        } else if (op == "query_ticket") {
            trainID id;
            train tra;
            station_name from,to;
            saleDate sd;
            bool flagp=0,flagt,flagc;
            while(scan.hasMoreTokens()){
                op=scan.nextToken();
                opp=scan.nextToken();
                if(op=="-s"){
                    from=opp;
                }else if(op=="-t"){
                    to=opp;
                }else if(op=="-d"){
                    sd=opp;
                }else if(op=="-p"){
                    flagp=1;
                    if(opp[0]=='t')flagt=1;
                    else flagc=1;
                }

            }
            //if(flag)continue;
            if(!flagp)all_train.query_ticket(from,to,sd,1);
            else if(flagt)all_train.query_ticket(from,to,sd,1);
            else if(flagc)all_train.query_ticket(from,to,sd,2);
        } else if (op == "query_transfer") {
            trainID id;
            train tra;
            station_name from,to;
            saleDate sd;
            bool flagp=0,flagt,flagc;
            while(scan.hasMoreTokens()){
                op=scan.nextToken();
                opp=scan.nextToken();
                if(op=="-s"){
                    from=opp;
                }else if(op=="-t"){
                    to=opp;
                }else if(op=="-d"){
                    sd=opp;
                }else if(op=="-p"){
                    flagp=1;
                    if(opp[0]=='t')flagt=1;
                    else flagc=1;
                }

            }
            if(!flagp)all_train.query_transfer(from,to,sd,1);
            else if(flagt)all_train.query_transfer(from,to,sd,1);
            else if(flagc)all_train.query_transfer(from,to,sd,2);
        } else if (op == "buy_ticket") {
            trainID id;
            train tra;
            saleDate sd;
            station_name from,to;
            bool flat=0;
            user_id uid;
            int num=0;
            while(scan.hasMoreTokens()){
                op=scan.nextToken();
                opp=scan.nextToken();
                if(op=="-u"){
                    uid=opp;
                    auto it=now_user.find(uid);
                    if(it==now_user.end()){
                        printf("-1\n");
                        flag=1;
                        break;
                    }

                }else if(op=="-i"){
                    id=opp;
                    if(!all_train.exist(id)){
                        printf("-1\n");
                        flag=1;
                        break;
                    }
                    tra=all_train.find(id);
                    if(!tra.released){
                        printf("-1\n");
                        flag=1;
                        break;
                    }

                }else if(op=="-d"){
                    sd=opp;

                }else if(op=="-n"){
                    num= stringToInt(opp);
                }else if(op=="-f"){
                    from=opp;
                }else if(op=="-t"){
                    to=opp;
                }else if(op=="-q"){
                    //flagq=1;
                    if(opp=="true"){
                        flat=1;
                    }
                }
            }
            if(flag)continue;
            int n= stringToInt(s);
            string put;long long price;
            ticket_information in;
            int back=all_train.buy_ticket(n,from,to,num,tra,flat,sd,put,price,in);

            if(back==0)continue;
            in.price=price;
            stringTochar(put,in.describe);
            in.time= n;
            in.num=num;
            in.uid=uid;
            in.date=sd;
            in.id=id;
            string r;
            if(back==1){
                r="pending";
                pending pe;
                pe.from=in.from,pe.to=in.to;
                pe.time=n;
                pe.date=sd;
                pe.price=price;
                pe.num=num;
                pe.id=id,pe.uid=uid;
                pe.d=in.d;
                point_<trainID,pending> ele(id,pe);
                wait.insert(ele);
                //stringTochar(r,in.status);
            }else if(back==2){
                r="success";
            }
            stringTochar(r,in.status);
            point_<user_id,ticket_information> ele(uid,in);
            order_.insert(ele);
        } else if (op == "query_order") {
            user_id uid;

            op=scan.nextToken();
            opp=scan.nextToken();
            uid=opp;
            auto it=now_user.find(uid);
            if(it==now_user.end()){
                printf("-1\n");
                continue;
            }

            order_.queryorder(uid);

        } else if (op == "refund_ticket") {
            user_id uid;
            int num=1;
            while(scan.hasMoreTokens()){
                op=scan.nextToken();
                opp=scan.nextToken();
                if(op=="-u"){
                    uid=opp;
                }else if(op=="-n"){
                    num= stringToInt(opp);
                }
            }
            ticket_information infor;
            if(!order_.refund_ticket(uid,num,infor))continue;
            train tra;
            block<trainID,train>blk=all_train.getblock(infor.id);
            tra=all_train.find(infor.id);
            int tmp=0;
            for(int i=0;i<blk.size;i++){
                if(blk.ele[i].index==infor.id)break;
                tmp++;
            }
            for(int i=infor.from;i<infor.to;i++){
                blk.ele[tmp].valu.seats[infor.d+1][i]+=infor.num;

                point_<station_name,train>p(tra.name[i],tra);
                block_<station_name,train>bk=all_train.getblock_(p);
                int tp=0;
                for(int j=0;j<bk.size;j++){
                    if(bk.ele[j].valu==tra)break;
                    tp++;
                }
                for(int j=infor.from;j<infor.to;j++){
                    tra.seats[infor.d+1][j]=bk.ele[tmp].valu.seats[infor.d+1][j]+=infor.num;
                }
                all_train.mywrite_(bk);
            }
            all_train.mywrite(blk);


            pending pe;
            point_<trainID,pending>k(infor.id,pending());
            bool fla=0;flag=0;
            bool update=0;
            //compare cp;
            block_<trainID,pending> fin;
            if(wait.tr.root==-1){
                //printf("-1\n");
                continue;

            }
            //cout<<root<<'\n';
            wait.tr.myread(order_.tr.root,fin);
            //cout<<fin.ele[1].valu;
            while(!fin.leaf){
                //cout<<fin.size<<' '<<fin.ele[0].valu<<' '<<fin.ele[1].valu<<' '<<fin.ele[2].valu<<'\n';
                int low=0,high=fin.size;
                while(low<high){
                    //if(fin.leaf)break;
                    int mid=(low+high)>>1;
                    if(k<fin.ele[mid]){
                        high=mid;
                    }else{
                        low=mid+1;
                    }
                }
                //cout<<low;
                wait.tr.myread(fin.pos[low],fin);
            }
            //cout<<fin.ele[2].valu<<' '<<fin.ele[1].valu<<'\n';

            if(k.index<fin.mini.index){

                continue;
            }

            for(int i=0;i<fin.size;i++){
                int seat=1e5+5;
                //cout<<fin.ele[0].valu<<' ';
                if(k.index<fin.ele[i].index)break;
                if(fin.ele[i].index==k.index){
                    flag=1;
                    if(fin.ele[i].valu.date==infor.date){
                        pe=fin.ele[i].valu;
                        for(int j=pe.from;j<pe.to;j++){
                            seat=std::min(seat,tra.seats[infor.d+1][j]);
                        }
                        if(seat>=pe.num){
                            blk=all_train.getblock(infor.id);
                            tra=all_train.find(infor.id);
                            tmp=0;
                            for(int l=0;l<blk.size;l++){
                                if(blk.ele[l].index==infor.id)break;
                                tmp++;
                            }
                            for(int l=pe.from;l<pe.to;l++){
                                blk.ele[tmp].valu.seats[infor.d+1][l]-=pe.num;

                                point_<station_name,train>p(tra.name[l],tra);
                                block_<station_name,train>bk=all_train.getblock_(p);
                                int tp=0;
                                for(int j=0;j<bk.size;j++){
                                    if(bk.ele[j].valu==tra)break;
                                    tp++;
                                }
                                for(int j=pe.from;j<pe.to;j++){
                                    tra.seats[infor.d+1][j]=bk.ele[tmp].valu.seats[infor.d+1][j]-=pe.num;
                                }
                                all_train.mywrite_(bk);
                            }
                            all_train.mywrite(blk);
                            break;
                        }
                    }


                    if(i==fin.size-1&&fin.next!=-1){
                        //cout<<fin.next;
                        wait.tr.myread(fin.next,fin);
                        //cout<<fin.size<<' '<<fin.ele[0].valu<<'\n';
                        i=-1;
                        //siz=fin.size;
                    }
                }
                if((!flag)&&(!fla)&&i==fin.size-1&&fin.next!=-1){
                    wait.tr.myread(fin.next,fin);
                    fla=1;
                    i=-1;
                }

            }
            //return update;

            //if(!wait.refresh(infor.date,infor.from,infor.to,infor.id,infor.d,infor.num,pe))continue;

        } else if (op == "clean") {
            now_user.clear();
            all_ac.clear();
            all_train.clear();
            order_.clear();
            printf("0\n");
        } else if (op == "exit") {
            printf("bye\n");
        }
    }

    return 0;
}
