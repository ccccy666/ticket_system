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
        num = num * 10 + str[i] - '0';
    }
    return num;
}

void stringTochar(std::string &s, char *a) {
    strcpy(a,s.c_str());
//    for (int i = 0; i < s.length(); i++) {
//        a[i] = s[i];
//    }
//    a[s.length()] = '\0';
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
    freopen("in1.txt","r",stdin);
    freopen("1.txt", "w", stdout);
    //fclose(stdin);
    //fclose(stdout);
    sjtu::map<user_id, account> now_user;
    //if(now_user.)
    //int log_num=0;
    string line, op, opp;
    All_account all_ac;
    All_train all_train;
    seats seat_;
    order order_;
    pendings wait;
    //op="",opp="";
    scanner scan;
    //int x=1;


    while (getline(std::cin, line)) {////////////////
        //std::cout<<1<<std::endl;
        //if(line=="\n")continue;

        bool flag=0;
        scan.setInput(line);
        op = scan.nextToken();
        //std::cout<<all_ac.tr.root<<std::endl;
        //if(op==" "||op=="")break;
        //return "bye";
        string  s ;
        for(int i=1;i<op.size()-1;i++){
            s+=op[i];
        }

        std::cout<<op<<' ';

        //printf("d ",tim);
        op = scan.nextToken();
        if (op == "add_user") {
            account ac,a;//new account
            //string mid,mi;
            bool empty=1;
            while (scan.hasMoreTokens()) {

                user_id _id;
                op = scan.nextToken();
                opp = scan.nextToken();
                if (op == "-g") {
                    if (now_user.empty()) {
                        ac.privilege = 10;
                    } else {

                        ac.privilege = stringToInt(opp);
                        //std::cout<<ac.privilege<<std::endl;
                        //std::cout<<opp;
                    }
                } else if (op == "-c" && !now_user.empty()) {
                    empty=0;
                    _id = opp;
                    if (!all_ac.exist(_id)) {
                        //std::cout<<1<<' ';
                        printf("-1\n");
                        flag=1;
                        break;
                    }
                    a=all_ac.find(_id);
                    auto it = now_user.find(_id);
                    if (it == now_user.end()) {
                        //std::cout<<1<<' ';
                        printf("-1\n");
                        flag=1;
                        break;
                    }
                } else if (op == "-u") {
                    //_id = opp;
                    ac.id = opp;

                } else if (op == "-p") {
                    //std::cout<<opp<<std::endl;
                    stringTochar(opp, ac.password);
                } else if (op == "-n") {
                    strcpy(ac.name,opp.c_str());
                    //stringTochar(opp, ac.name);
//                    string f="Estelle";
//                    mi=opp;
//                    if(strcmp(ac.id.userid,f.c_str())==0)std::cout<<mi.size()<<' ';

                } else if (op == "-m") {
//                    for (int i = 0; i < opp.length(); i++) {
//                        ac.email[i] = opp[i];
//                    }
//                    ac.email[opp.length()] = '\0';
                    strcpy(ac.email,opp.c_str());
//                    string f="Estelle";
//                    if(strcmp(ac.id.userid,f.c_str())==0)std::cout<<ac.email<<' ';
                    //mid=opp;
                }

            }

            if(flag)continue;
            if(!empty){
                if(a.id==ac.id||a.privilege<=ac.privilege){
                    printf("-1\n");
                    continue;

                }
            }

//            strcpy(ac.name,mi.c_str());
//            strcpy(ac.email,mid.c_str());
//            string f="Estelle";
//            if(strcmp(ac.id.userid,f.c_str())==0)std::cout<<ac.name<<'\n';

            all_ac.insert(ac);
            printf("0\n");
        } else if (op == "login") {
            char word[42];
            account ac;
            user_id idd;

            while (scan.hasMoreTokens()) {
                op = scan.nextToken();
                opp = scan.nextToken();
                if (op == "-u") {
                    idd = opp;
                    auto it=now_user.find(idd);
                    //std::cout<<1<<std::endl;
                    //all_ac.exist(idd);

                    if (!all_ac.exist(idd)||it!=now_user.end()) {

                        printf("-1\n");
                        flag=1;
                        break;
                    }

                    ac = all_ac.find(idd);
                } else if (op == "-p") {

                    stringTochar(opp, word);
                    //std::cout<<word<<std::endl;
                }

            }

            if(flag)continue;
            //std::cout<<op;
            if (strcmp(ac.password, word)) {

                printf("-1\n");
                //flag=1;
                continue;
            }

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
            if(flag)continue;
            account a=now_user[_id];

            if (a!=ac&&a.privilege <= ac.privilege) {
                printf("-1\n");
                continue;

            }

            //printf("0\n");
            //std::cout<<ac.id.userid<<' '<<ac.name<<' '<<ac.email<<' '<<ac.privilege<<'\n';
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
                    strcpy(ac.email,opp.c_str());
                    //stringTochar(opp, ac.email);

                }
            }
            if(flag)continue;
            int tmp = 0;
            for (int i = 0; i < blk.size; i++) {
                if (id == blk.ele[i].index)break;
                tmp++;
            }//blk.ele[tmp].valu.password=ac.password;
            account a=now_user[_id];
            if ((a!=ac&&a.privilege <= blk.ele[tmp].valu.privilege)||ac.privilege>a.privilege) {
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
            int seatt;
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
                    seatt=stringToInt(opp);
//                    for(int i=1;i<104;i++){
//                        tra.seats[i]=seat;
//                    }

                }else if(op=="-s"){
                    for(int i=0;i<opp.size();i++){
                        if(opp[i]=='|'||i==opp.length()-1){
                            if(i==opp.length()-1)word+=opp[i];
                            tra.name[tmp]=word;
                            tra.name[tmp].num=tmp;

//
                            tmp++;

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
//                            string f="puzzletheNewWorld";
//                            if(strcmp(tra.id.trainid,f.c_str())==0){
//                                //std::cout<<tmp<<' ';
//                                std::cout<<tra.price[tmp-1]<<std::endl;
//                            }
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
            tra.maxseat=seatt;
            printf("0\n");

            seat se;
            se.id=tra.id;
            se.max=tra.maxseat;
            se.num=tra.station_num;
            for(int j=1;j<=se.num-1;j++){
                se.sea[j]=tra.maxseat;
            }

            for(int i=0;i<=tra.finishsale-tra.startsale;i++){
                train_seat ts;
                ts.id=tra.id;
                ts.d=i;
//                string f="TOFOREIGNLANDS";
//                if(strcmp(tra.id.trainid,f.c_str())==0)std::cout<<ts.d<<std::endl;
                point<train_seat,seat>p(ts,se);
                seat_.insert(p);
            }

            all_train.insert(tra);
            //std::cout<<all_train.tr.root<<' ';

        } else if (op == "delete_train") {
            op=scan.nextToken();
            opp=scan.nextToken();
            trainID id;
            train tra;
            id=opp;
            if(!all_train.exist(id)){
                printf("-1\n");
                continue;
            }
            tra=all_train.find(id);
            if(tra.released){
                printf("-1\n");
            }else{
                printf("0\n");
                int d=tra.finishsale-tra.startsale;
                train_seat ts;
                ts.id=tra.id;
                seat se;
                se.id=tra.id;
                for(int i=0;i<=d;i++){
                    ts.d=i;

                    point<train_seat,seat>pi(ts,se);
                    seat_.tr.del(pi);
                }
//                for(int i=1;i<=tra.station_num;i++){
//                    point_<station_name,train>pp(tra.name[i],tra);
//                    all_train.del_(pp);
//                }

                point<trainID,train>p(id,tra);
                all_train.del(p);
            }

        } else if (op == "release_train") {
            op=scan.nextToken();
            opp=scan.nextToken();
            trainID id;
            train tra;
            block<trainID,train> blk;
            //block_<station_name,train> bk;
            id=opp;
//            std::cout<<id.trainid<<' ';
//            all_train.tr.myread(0,blk);
            //std::cout<<id.trainid<<std::endl;
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
            if(blk.ele[tmp].valu.released==0){
                blk.ele[tmp].valu.released=1;
                tra.released=1;

//                string f="INSCRIPTIONS";
//                if(strcmp(tra.id.trainid,f.c_str())==0)std::cout<<tra.name[14].name<<std::endl;
                for (int i = 1; i <= tra.station_num; i++) {

                    point_<station_name, train> pp(tra.name[i], tra);
                    all_train.tr1.insert(pp);
                }
            }else{
                printf("-1\n");
                continue;
            }


            all_train.mywrite(blk);
            printf("0\n");
        } else if (op == "query_train") {
            saleDate sd;
            trainID id;
            train tra;
            seat se;
            train_seat ts;
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

                    ts.id=tra.id;

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
            ts.d=delt;
            se=seat_.find(ts);
            printf("%s %c\n",tra.id.trainid,tra.type);
            for(int i=1;i<=tra.station_num;i++){
                printf("%s ",tra.name[i].name);
                if(i==1){
                    printf("xx-xx xx:xx -> ");
                    printf("%s %s %d %d\n",sd.date,tra.startTime.date,tra.price[i-1],se.sea[i]);
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
                    printf("%d %d",tra.price[i-1],se.sea[i]);
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
            seat se;
            bool flagp=0,flagt=0,flagc=0;
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
            if(flag)continue;
            int notuse= stringToInt(s);
            if(!flagp)all_train.query_ticket(from,to,sd,1,seat_,notuse);
            else if(flagt)all_train.query_ticket(from,to,sd,1,seat_,notuse);
            else if(flagc)all_train.query_ticket(from,to,sd,2,seat_,notuse);
        } else if (op == "query_transfer") {
            trainID id;
            train tra;
            station_name from,to;
            saleDate sd;
            bool flagp=0,flagt=0,flagc=0;
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
            int notuse= stringToInt(s);
            if(!flagp)all_train.query_transfer(from,to,sd,1,seat_,notuse);
            else if(flagt)all_train.query_transfer(from,to,sd,1,seat_,notuse);
            else if(flagc)all_train.query_transfer(from,to,sd,2,seat_,notuse);
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
            string put;long long price=0;
            ticket_information in;
            //int nouse= stringToInt(s);
            //std::cout<<66666<<std::endl;
            int back=all_train.buy_ticket(seat_,n,from,to,num,tra,flat,sd,put,price,in);

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
//                if(n==9292){
//                    std::cout<<sd.month<<' '<<sd.day<<std::endl;
//                }
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
            if(!all_ac.exist(uid)){

                printf("-1\n");
                continue;
            }
            auto it=now_user.find(uid);
            if(it==now_user.end()){

                printf("-1\n");
                continue;
            }
//            if(s=="1132"){
//                std::cout<<6666<<std::endl;
//            }
            order_.queryorder(uid);

        } else if (op == "refund_ticket") {
            user_id uid;
            int num=1;
            while(scan.hasMoreTokens()){
                op=scan.nextToken();
                opp=scan.nextToken();
                if(op=="-u"){
                    uid=opp;
                    auto it=now_user.find(uid);
                    if(!all_ac.exist(uid)||it==now_user.end()){
                        printf("-1\n");
                        flag=1;
                        break;
                    }
                }else if(op=="-n"){
                    num= stringToInt(opp);
                }
            }
            if(flag)continue;

            ticket_information infor;
            if(!order_.refund_ticket(uid,num,infor))continue;
            //train tra;
            //string f="Bagpipe";
            int n= stringToInt(s);

            train_seat ts;
            ts.id=infor.id,ts.d=infor.d;

            block<train_seat,seat>blk;
            blk=seat_.get_block(ts);
            //tra=all_train.find(infor.id);
            int tmp=0;
            for(int i=0;i<blk.size;i++){
                if(blk.ele[i].index==ts)break;
                tmp++;
            }
            for(int i=infor.from;i<infor.to;i++){
                blk.ele[tmp].valu.sea[i]+=infor.num;

            }
            seat_.tr.mywrite(blk.place,blk);
            seat se=blk.ele[tmp].valu;

            pending pe;
            point_<trainID,pending>k(infor.id,pending());
            bool fla=0,flag1=0;
            //bool update=0;
            //compare cp;
            block_<trainID,pending> fin;
            if(wait.tr.root==-1){
                //printf("-1\n");
                continue;

            }
            //bool fla1=0,fla=0;
            wait.tr.myread(wait.tr.root,fin);

            //cout<<fin.ele[1].valu;
            while(!fin.leaf){
//                string f="Gitano";
//                if(!strcmp(f.c_str(),uid.userid))std::cout<<fin.place<<std::endl;
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

                //cout<<fin.ele[0].valu<<' ';
                if(k.index<fin.ele[i].index)break;
                if(fin.ele[i].index==k.index){

                    flag1=1;
                    if(fin.ele[i].valu.date==infor.date){

                        int seatt=1e5+5;
                        pe=fin.ele[i].valu;
                        for(int j=pe.from;j<pe.to;j++){
                            seatt=std::min(seatt,se.sea[j]);
                        }
//                        if(n==65528){
//                            std::cout<<pe.from<<' '<<pe.to<<' '<<pe.num<<' '<<pe.uid.userid<<' '<<seatt<<std::endl;
//                            //std::cout<<se.sea[3]<<' '<<blk.ele[tmp].valu.sea[3]<<std::endl;
//
//                            //std::cout<<infor.date.month<<' '<<infor.date.day<<' '<<pe.num<<std::endl;
//                        }

//                        if(strcmp(uid.userid,f.c_str())==0){
//                            std::cout<<fin.ele[i].valu.id.trainid<<' '<<fin.ele[i].valu.num<<' '<<fin.ele[i].valu.date.month<<' '<<fin.ele[i].valu.date.day<<std::endl;
//                            std::cout<<seatt<<' '<<pe.num<<std::endl;
//                        }
                        if(seatt>=pe.num){
                            point_<trainID,pending> po(pe.id,pe);
                            wait.del(po);
                            order_.change(pe.uid,pe.time);
//                            blk=seat_.get_block(ts);
//                            //tra=all_train.find(infor.id);
//                            tmp=0;
//                            for(int l=0;l<blk.size;l++){
//                                if(blk.ele[l].index==ts)break;
//                                tmp++;
//                            }
                            for(int l=pe.from;l<pe.to;l++){
                                blk.ele[tmp].valu.sea[l]-=pe.num;
                                se.sea[l]-=pe.num;
                            }

                            seat_.tr.mywrite(blk.place,blk);
                            //break;
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
                if((!flag1)&&(!fla)&&i==fin.size-1&&fin.next!=-1){
                    wait.tr.myread(fin.next,fin);
                    fla=1;
                    i=-1;
                }

            }


        } else if (op == "clean") {
            now_user.clear();
            all_ac.clear();
            all_train.clear();
            order_.clear();
            wait.clear();
            printf("0\n");
        } else if (op == "exi"||op=="exit") {
            //std::cout<<all_ac.tr.root;
            //std::cout<<"bye"<<std::endl;
            printf("bye\n");
            break;
        }else if(op==" ")break;
    }

    return 0;
}
