
#ifndef B_TREE_TRAIN_H
#define B_TREE_TRAIN_H
#include <iostream>
#include<cstring>
#include<iomanip>
#include "b+ tree.h"
#include "b+ tree__.h"
#include"Account.h"
//#include "link.h"

using std::string;
class trainID {
public:
    char trainid[22];

    trainID() {
        trainid[0] = '\0';
    };

    trainID(std::string &in) {
        //if(in.size()>30)error("Invalid");

        for (int i = 0; i < in.size(); i++) {
            trainid[i] = in[i];
        }
        trainid[in.size()] = '\0';
    }

    trainID(const trainID &other) {
        strcpy(trainid, other.trainid);
    }

    bool operator==(const trainID &other) const {
        return (!strcmp(trainid, other.trainid));
    }

    bool operator!=(const trainID &other) const {
        return (strcmp(trainid, other.trainid));
    }

    bool operator<(const trainID &other) const {
        return (strcmp(trainid, other.trainid) < 0);
    }

    bool operator<=(const trainID &other) const {
        return ((strcmp(trainid, other.trainid) < 0) || (!strcmp(trainid, other.trainid)));
    }

    bool operator>=(const trainID &other) const {
        return !(*this < other);
        //return ((strcmp(trainid,other.trainid)<0)||(!strcmp(trainid,other.trainid)));
    }

    bool operator>(const trainID &other) const {
        return (!(*this < other)) && (!(*this == other));
        //return ((strcmp(trainid,other.trainid)<0)||(!strcmp(trainid,other.trainid)));
    }
};

class station_name {
public:
    char name[22];
    int num = 0;

    station_name() {};

    station_name(std::string &in) {
        //if(in.size()>30)error("Invalid");

        for (int i = 0; i < in.size(); i++) {
            name[i] = in[i];
        }
        name[in.size()] = '\0';
    }

    station_name(const station_name &other) {
        strcpy(name, other.name);
        num = other.num;
    }

    bool operator==(const station_name &other) const {
        return (!strcmp(name, other.name));
    }

    bool operator!=(const station_name &other) const {
        return (strcmp(name, other.name));
    }

    bool operator<(const station_name &other) const {
        return (strcmp(name, other.name) < 0);
    }

    bool operator<=(const station_name &other) const {
        return ((strcmp(name, other.name) < 0) || (!strcmp(name, other.name)));
    }

    bool operator>=(const station_name &other) const {
        return !(*this < other);
        //return ((strcmp(trainid,other.trainid)<0)||(!strcmp(trainid,other.trainid)));
    }

    bool operator>(const station_name &other) const {
        return (!(*this < other)) && (!(*this == other));
        //return ((strcmp(trainid,other.trainid)<0)||(!strcmp(trainid,other.trainid)));
    }
};

//class station_num{
//public:
//
//};
class timepoint {
public:
    char date[8];
    int hour;
    int min;

    timepoint() {};

    timepoint(std::string &in) {
        //if(in.size()>30)error("Invalid");
        int d;
        bool fl = 0;
        for (int i = 0; i < in.size(); i++) {
            date[i] = in[i];
            if (in[i] != ':' && i != in.size() - 1)d = d * 10 + in[i] - '0';
            else {
                if (fl)d = d * 10 + in[i] - '0';
                if (!fl) {
                    fl = 1;
                    hour = d;
                } else {
                    min = d;
                }
                d = 0;
            }
        }
        date[in.size()] = '\0';
    }

    timepoint(const timepoint &other) {
        strcpy(date, other.date);
        hour = other.hour;
        min = other.min;
    }

    bool operator==(timepoint &other) const {
        return (!strcmp(date, other.date));
    }

    bool operator!=(timepoint &other) const {
        return (strcmp(date, other.date));
    }

    bool operator<(timepoint &other) const {
        return (strcmp(date, other.date) < 0);
    }

    bool operator<=(timepoint &other) const {
        return ((strcmp(date, other.date) < 0) || (!strcmp(date, other.date)));
    }

    bool operator>=(timepoint &other) const {
        return !(*this < other);
        //return ((strcmp(trainid,other.trainid)<0)||(!strcmp(trainid,other.trainid)));
    }

    bool operator>(timepoint &other) const {
        return (!(*this < other)) && (!(*this == other));
        //return ((strcmp(trainid,other.trainid)<0)||(!strcmp(trainid,other.trainid)));
    }
};


class saleDate {
public:
    char date[8];
    int month;
    int day;

    saleDate() {};

    saleDate(std::string &in) {
        //if(in.size()>30)error("Invalid");
        int d;
        bool fl = 0;
        for (int i = 0; i < in.size(); i++) {
            date[i] = in[i];
            if (in[i] != '-' && i != in.size() - 1)d = d * 10 + in[i] - '0';
            else {
                if (fl)d = d * 10 + in[i] - '0';
                if (!fl) {
                    fl = 1;
                    month = d;
                } else {
                    day = d;
                }
                d = 0;
            }
        }
        date[in.size()] = '\0';
    }

    saleDate(const saleDate &other) {
        strcpy(date, other.date);
        month = other.month;
        day = other.day;
    }

    bool operator==(const saleDate &other) const {
        return (!strcmp(date, other.date));
    }

    bool operator!=(const saleDate &other) const {
        return (strcmp(date, other.date));
    }

    bool operator<(const saleDate &other) const {
        return (strcmp(date, other.date) < 0);
    }

    bool operator<=(const saleDate &other) const {
        return ((strcmp(date, other.date) < 0) || (!strcmp(date, other.date)));
    }

    bool operator>=(const saleDate &other) const {
        return !(*this < other);
        //return ((strcmp(trainid,other.trainid)<0)||(!strcmp(trainid,other.trainid)));
    }

    bool operator>(const saleDate &other) const {
        return (!(*this < other)) && (!(*this == other));
        //return ((strcmp(trainid,other.trainid)<0)||(!strcmp(trainid,other.trainid)));
    }
    int getDays(int mon) const {

        if (mon == 4 || mon == 6 || mon == 9 || mon == 11) return 30;
        else return 31;
    }
    int operator -(const saleDate &other){
        int days;
        if(month==other.month) days= (day - other.day) ;
        else {
            //*this<other?*this:other;
            saleDate mi=std::min(*this,other);
            saleDate ma=std::max(*this,other);
            //int day;
            while(ma.month>mi.month){
                ma.month--;
                ma.day+= getDays(ma.month);

            }
            days= (ma.day - mi.day) ;
        }
        // 如果结果为负数，则将其取反
        if (days < 0) days = -days;

        return days;
    }
};

class Time {
public:
    int month_;
    int day_;
    int hour_;
    int min;

    int getDays(int month) const {

        if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
        else return 31;
    }

    Time() {}

    Time(int month, int day, int hour, int minute) : month_(month), day_(day), hour_(hour), min(minute) {}


    std::string toString() const {
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << month_ << "-" << std::setw(2) << std::setfill('0') << day_
            << " " << std::setw(2) << std::setfill('0') << hour_ << ":" << std::setw(2) << std::setfill('0') << min;
        return oss.str();
    }

    Time operator+(int minutes) const {
        Time result = *this;
        result.min += minutes;

        result.hour_ += result.min / 60;
        result.min %= 60;

        if (result.hour_ >= 24) {
            result.day_ += result.hour_ / 24;
            result.hour_ %= 24;

            if (result.day_ > getDays(result.month_)) {
                result.day_ -= getDays(result.month_);
                result.month_++;
            }
        }

        return result;
    }

    int operator-(const Time &other) const {
        // 计算当前对象和另一个对象的分钟数差
        //Time t=*this;
        int minutes;
        if(month_==other.month_) minutes= (day_ - other.day_) * 24 * 60 + (hour_ - other.hour_) * 60 + (min - other.min);
        else {
            Time mi=std::min(*this,other);
            Time ma=std::max(*this,other);
            //int day;
            while(ma.month_>mi.month_){
                ma.month_--;
                ma.day_+= getDays(ma.month_);

            }
            minutes= (ma.day_ - mi.day_) * 24 * 60 + (ma.hour_ - mi.hour_) * 60 + (ma.min - mi.min);
        }
        // 如果结果为负数，则将其取反
        if (minutes < 0) minutes = -minutes;

        return minutes;
    }

    Time operator-(int minutes) const {
        Time result(*this);

        // 计算总共需要借位的分钟数和需要借位的天数
        int borrow_minutes = minutes % (24 * 60);
        int borrow_days = minutes / (24 * 60);

        // 计算需要借位的小时数和分钟数
        int borrow_hour = borrow_minutes / 60;
        int borrow_minute = borrow_minutes % 60;

        // 依次进行借位和进位操作
        result.min -= borrow_minute;
        if (result.min < 0) {
            result.min += 60;
            borrow_hour++;
        }

        result.hour_ -= borrow_hour;
        if (result.hour_ < 0) {
            result.hour_ += 24;
            borrow_days++;
        }

        // 处理日期借位的逻辑
        while (borrow_days > 0) {
            int days_in_prev_month = getDays(result.month_ - 1);
            if (result.day_ <= borrow_days) {
                borrow_days -= result.day_;
                result.month_--;
                if (result.month_ == 0) {
                    result.month_ = 12;
                    // 如果当前月份是 1 月，则需要借位到上一年的 12 月
                    result.day_ = getDays(result.month_) - borrow_days % days_in_prev_month;
                } else {
                    result.day_ = getDays(result.month_);
                }
            } else {
                result.day_ -= borrow_days;
                borrow_days = 0;
            }
        }

        return result;
    }

    bool operator<(const Time &other) const {
        if (month_ != other.month_) {
            return month_ < other.month_;
        } else if (day_ != other.day_) {
            return day_ < other.day_;
        } else if (hour_ != other.hour_) {
            return hour_ < other.hour_;
        } else {
            return min < other.min;
        }
    }

    bool operator>(const Time &other) const {
        return other < *this;
    }

    bool operator==(const Time &other) const {
        return month_ == other.month_ && day_ == other.day_ && hour_ == other.hour_ && min == other.min;
    }

    bool operator<=(const Time &other) const {
        return *this < other || *this == other;
    }

    bool operator>=(const Time &other) const {
        return *this > other || *this == other;
    }


};
//class Date{
//public:
//    saleDate sd;
//    timepoint tp;
//    Date(){};
//    Date(string &t1,string &t2):sd(t1),tp(t2){}
//    Date(Date &other):sd(other.sd),tp(other.tp){}
//
//};

class train {
public:
    int station_num;
    int seats[105][105];
    station_name name[105];
    trainID id;
    int price[105];
    timepoint startTime;
    int travelTime[105];
    int stopTime[105];
    saleDate startsale;
    saleDate finishsale;

    //saleDate saledate[100];
    char type;
    bool released = 0;

    train() {}

    train(const train &other) : startsale(other.startsale), finishsale(other.finishsale), id(other.id),
                                startTime(other.startTime) {
        station_num = other.station_num;

        for (int i = 1; i <= station_num - 1; i++) {
            name[i] = other.name[i];
//            if(i>=1){
//
//            }
            stopTime[i] = other.stopTime[i];
            travelTime[i] = other.travelTime[i];
            price[i] = other.price[i];

        }
        for(int i=1;i<=finishsale-startsale+1;i++){
            for(int j=1;j<=station_num-1;j++){
                seats[i][j] = other.seats[i][j];
            }
        }

        type = other.type;
        released = other.released;
    }

    ~train() {}

    bool operator<(const train &other) const {
        return (id < other.id);
    }

    bool operator==(const train &other) const {
        return id == other.id;
    }

    bool operator>(const train &other) const {
        return id > other.id;
    }
};

struct output1 {
    int seat;
    string s;
    int time;
    int cost;
    trainID id;

    bool operator<(const output1 &other) {
        return (time < other.time) || (time == other.time && id < other.id);
    }
};

struct output2 {
    int seat;
    string s;
    int cost;
    trainID id;

    bool operator<(const output2 &other) {
        return (cost < other.cost) || (cost == other.cost && id < other.id);
    }
};

struct out1 {
    int time;
    int cost=1e8;
    int cost1, cost2;
    trainID id1, id2;
    string s1, s2;
    int seat1,seat2;
    bool operator<(const out1 &other) const{
        return (time < other.time) || (time == other.time && cost < other.cost) ||
                                       (time == other.time && cost == other.cost && id1 < other.id1) ||
                                       (time == other.time && cost == other.cost && id1 == other.id1 &&
                                        id2 < other.id2);
    }
};


struct out2 {
    int time=1e5;
    int cost;
    int cost1, cost2;
    trainID id1, id2;
    string s1, s2;
    int seat1,seat2;
    bool operator<(const out2 &other) const{
        return (cost < other.cost) || (cost == other.cost && time < other.time) ||
               (time == other.time && cost == other.cost && id1 < other.id1) ||
               (time == other.time && cost == other.cost && id1 == other.id1 &&
                id2 < other.id2);
    }
};
class ticket_information{
public:
    int d;
    int time=0;
    int from,to;
    char status[20];
    trainID id;
    user_id uid;
    saleDate date;
    char describe[150];
    int price;
    int num;
    ticket_information(){};
    ticket_information(const ticket_information&other):id(other.id),uid(other.uid),date(other.date){
        strcpy(status,other.status);
        strcpy(describe,other.describe);
        price=other.price;
        num=other.num;
        time=other.time;
        d=other.d;
        from=other.from;to=other.to;
    }
    bool operator<(const ticket_information& other)const{
        return time<other.time;
    }
    bool operator==(const ticket_information& other)const{
        return time==other.time;
    }
    friend std::ostream &operator<<(std::ostream &x, const ticket_information &y) {
        x << '['<<y.status<<']'<<' '<<y.id.trainid<<' '<<y.describe<<' '<<y.price<<' '<<y.num;
        return x;
    };
};

class order{
public:
    b_plus_tree_<user_id,ticket_information> tr;
    order():tr("order"){}
    void insert(point_<user_id,ticket_information> &el){
        tr.insert(el);
    }
    bool exist(user_id &uid){
        return tr.exist(uid);
    }
    void queryorder(user_id &uid){
        tr.find(uid);
    }
    void clear(){
        tr.root=tr.total=-1;
    }
    bool refund_ticket(user_id &uid,int num,ticket_information &infor){
        point_<user_id,ticket_information>k(uid,ticket_information());
        bool flag=0,fla=0;
        //compare cp;
        block_<user_id,ticket_information> fin;
        if(tr.root==-1){
            printf("-1\n");
            return 0;

        }
        //cout<<root<<'\n';
        tr.myread(tr.root,fin);
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
            tr.myread(fin.pos[low],fin);
        }
        //cout<<fin.ele[2].valu<<' '<<fin.ele[1].valu<<'\n';

        if(k.index<fin.mini.index){

            printf("-1\n");
            return 0;
        }
        //int tmp=1;
        sjtu::vector<ticket_information>v;

        //int siz=fin.size;
        //cout<<fin.ele[0].valu<<fin.ele[1].valu;
        for(int i=0;i<fin.size;i++){
            //cout<<fin.ele[0].valu<<' ';
            if(k.index<fin.ele[i].index)break;
            if(fin.ele[i].index==k.index){
                flag=1;
                //cout<<1;
                v.push_back(fin.ele[i].valu);
                //printf("%d ",fin.ele[i].valu);

                if(i==fin.size-1&&fin.next!=-1){
                    //cout<<fin.next;
                    tr.myread(fin.next,fin);
                    //cout<<fin.size<<' '<<fin.ele[0].valu<<'\n';
                    i=-1;
                    //siz=fin.size;
                }
            }
//            if((!flag)&&(!fla)&&i==fin.size-1&&fin.next!=-1){
//                myread(fin.next,fin);
//                fla=1;
//                i=-1;
//            }

        }
        if(!flag||num>v.size()){
            printf("-1\n");
            return 0;
        }
        else {
            infor=v[v.size()-num];
            string ss=(std::string)infor.status;

            if(ss=="pending"||ss=="success"){
                point_<user_id,ticket_information> p(uid,infor);
                block_<user_id,ticket_information> blk=tr.getblock_(p);

                int tmp=0;
                for(int i=0;i<blk.size;i++){
                    if(p==blk.ele[i])break;
                    tmp++;
                }
                string sss="refunded";
                for(int i=0;i<sss.size();i++){
                    blk.ele[tmp].valu.status[i]=sss[i];
                }
                blk.ele[tmp].valu.status[sss.size()]='\0';
                tr.mywrite(blk.place,blk);
                if(ss=="success"){
                    //todo
                    return 1;
                }
            }

            //return 1;
//            printf("%d\n",v.size());
//            for(int i=0;i<v.size();i++){
//                std::cout<<v[i]<<'\n';
//            }
        }
    }
};
class pending{
public:
    int d;//距离首发车的天数
    int from,to;
    int time=0;
    //char status[20];
    trainID id;
    user_id uid;
    saleDate date;
    //char describe[150];
    int price;
    int num;
    pending(){};
    pending(const pending&other):id(other.id),uid(other.uid),date(other.date){
        //strcpy(status,other.status);
        //strcpy(describe,other.describe);
        price=other.price;
        num=other.num;
        time=other.time;
        d=other.d;
        from=other.from;to=other.to;
    }
    bool operator<(const pending& other)const{
        return time<other.time;
    }
    bool operator==(const pending &other)const{
        return time==other.time;
    }
};
class pendings{
public:
    b_plus_tree_<trainID,pending>tr;
    pendings():tr("pending"){}
    void insert(point_<trainID,pending> &el){
        tr.insert(el);
    }
    bool exist(trainID &id){
        return tr.exist(id);
    }
    bool refresh(saleDate &date,int from,int to,trainID &id,int d,int num,pending &pen){
        point_<trainID,pending>k(id,pending());
        bool flag=0,fla=0;
        bool update=0;
        //compare cp;
        block_<trainID,pending> fin;
        if(tr.root==-1){
            printf("-1\n");
            return 0;

        }
        //cout<<root<<'\n';
        tr.myread(tr.root,fin);
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
            tr.myread(fin.pos[low],fin);
        }
        //cout<<fin.ele[2].valu<<' '<<fin.ele[1].valu<<'\n';

        if(k.index<fin.mini.index){

            printf("-1\n");
            return 0;
        }

        for(int i=0;i<fin.size;i++){
            //cout<<fin.ele[0].valu<<' ';
            if(k.index<fin.ele[i].index)break;
            if(fin.ele[i].index==k.index){
                flag=1;
                if(fin.ele[i].valu.date==date){

                }


                if(i==fin.size-1&&fin.next!=-1){
                    //cout<<fin.next;
                    tr.myread(fin.next,fin);
                    //cout<<fin.size<<' '<<fin.ele[0].valu<<'\n';
                    i=-1;
                    //siz=fin.size;
                }
            }
            if((!flag)&&(!fla)&&i==fin.size-1&&fin.next!=-1){
                tr.myread(fin.next,fin);
                fla=1;
                i=-1;
            }

        }
        return update;
//        if(!flag)printf("-1\n");
//        else {
//            printf("%d\n",v.size());
//            for(int i=0;i<v.size();i++){
//                std::cout<<v[i]<<'\n';
//            }
//        }
    }
};
class All_train {
public:
    //string file;
    b_plus_tree<trainID, train> tr;
    b_plus_tree_<station_name, train> tr1;
    //linklist_<>
    All_train() : tr("train"), tr1("station") {}

    ~All_train() {}

    bool exist(trainID &id) {
        return tr.exist(id);
    }

    void insert(train &acc) {
        for (int i = 1; i <= acc.station_num; i++) {
            point_<station_name, train> pp(acc.name[i], acc);
            tr1.insert(pp);
        }
        point<trainID, train> p(acc.id, acc);
        tr.insert(p);
    }

    train find(trainID &id) {

        return tr.find(id);
    }

    void mywrite_(block_<station_name, train> &bk) {
        tr1.mywrite(bk.place, bk);
    }

    void mywrite(block<trainID, train> &bk) {

        tr.mywrite(bk.place, bk);
    }

    block<trainID, train> getblock(trainID &id) {
        return tr.getblock(id);
    }

    block_<station_name, train> getblock_(point_<station_name, train> &st) {
        return tr1.getblock_(st);
    }

    void del(point<trainID, train> &p) {

        tr.del(p);
    }

    void del_(point_<station_name, train> &p) {
        tr1.del(p);
    }

    void clear() {
        tr.root = -1;
        tr.total = -1;
        tr1.root=-1;
        tr1.total=-1;
    }

    void merge1(output1 *a, int l, int r) {
        if (l < r) {
            int mid = l + r >> 1;
            merge1(a, l, mid);
            merge1(a, mid + 1, r);
            merge1sort(a, l, mid, r);
        }
    }

    void merge1sort(output1 *a, int l, int mid, int r) {
        output1 *b = new output1[10005];
        int i = l, j = mid + 1, k = 0;
        while (i <= mid && j <= r) {
            if (a[j] < a[i]) {
                b[k++] = a[j++];
            } else {
                b[k++] = a[i++];

            }
        }
        while (i <= mid) {
            b[k++] = a[i++];

        }
        while (j <= r) {
            b[k++] = a[j++];
        }
        for (i = l; i <= r; i++) {
            a[i] = b[i - l];
        }
        delete[]b;
    }

    void merge2(output2 *a, int l, int r) {
        if (l < r) {
            int mid = l + r >> 1;
            merge2(a, l, mid);
            merge2(a, mid + 1, r);
            merge2sort(a, l, mid, r);
        }
    }

    void merge2sort(output2 *a, int l, int mid, int r) {
        output2 *b = new output2[10005];
        int i = l, j = mid + 1, k = 0;
        while (i <= mid && j <= r) {
            //i++,j++;
            if (a[j] < a[i]) {
                b[k++] = a[j++];
            } else {
                b[k++] = a[i++];

            }
        }
        while (i <= mid) {
            b[k++] = a[i++];

        }
        while (j <= r) {
            b[k++] = a[j++];
        }
        for (i = l; i <= r; i++) {
            a[i] = b[i - l];
        }
        delete[]b;
    }

    void query_ticket(station_name &begin, station_name &end, saleDate &date, int mode) {
        output1 ans1[10005];
        output2 ans2[10005];
        int cnt = 0;
        bool flag1 = 0, flag2 = 0, fla1 = 0, fla2;
        point_<station_name, train> first(begin, train()), second(end, train());
        block_<station_name, train> fin, finn;
        tr1.myread(tr1.root, fin);
        //cout<<fin.ele[1].valu;
        while (!fin.leaf) {
            //cout<<fin.size<<' '<<fin.ele[0].valu<<' '<<fin.ele[1].valu<<' '<<fin.ele[2].valu<<'\n';
            int low = 0, high = fin.size;
            while (low < high) {
                //if(fin.leaf)break;
                int mid = (low + high) >> 1;
                if (first < fin.ele[mid]) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }
            //cout<<low;
            tr1.myread(fin.pos[low], fin);
        }
        tr1.myread(tr1.root, finn);
        //cout<<fin.ele[1].valu;
        while (!finn.leaf) {
            //cout<<fin.size<<' '<<fin.ele[0].valu<<' '<<fin.ele[1].valu<<' '<<fin.ele[2].valu<<'\n';
            int low = 0, high = finn.size;
            while (low < high) {
                //if(fin.leaf)break;
                int mid = (low + high) >> 1;
                if (second < finn.ele[mid]) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }
            tr1.myread(finn.pos[low], finn);
        }
        if (first.index < fin.mini.index || second.index < finn.mini.index) {
            printf("0\n");
            return;
        }
        int i = 0, j = 0;
        for (; i < fin.size && j < finn.size; i++, j++) {
//            //cout<<fin.ele[0].valu<<' ';
            if (first.index < fin.ele[i].index || second.index < finn.ele[j].index)break;
            if (fin.ele[i].index == first.index && finn.ele[j].index != second.index)i--;
            if (fin.ele[i].index != first.index && finn.ele[j].index == second.index)j--;
            if (fin.ele[i].index == first.index && finn.ele[j].index == second.index) {
                flag1 = 1;
                flag2 = 1;
//                //cout<<1;
                //printf("%d ",fin.ele[i].valu);
                if (fin.ele[i].valu < finn.ele[j].valu) {
                    j--;
                    continue;
                } else if (fin.ele[i].valu > finn.ele[j].valu) {
                    i--;
                    continue;
                }
                if (fin.ele[i].index.num >= finn.ele[j].index.num)continue;
                int num1 = fin.ele[i].index.num, num2 = finn.ele[j].index.num;
                train tra = fin.ele[i].valu;
                int traveltime = tra.travelTime[num1 - 1] + tra.stopTime[num1];
                //int hour,min,month,day;
                Time tim1(tra.startsale.month, tra.startsale.day, tra.startTime.hour, tra.startTime.min);
                Time tim2(tra.finishsale.month, tra.finishsale.day, tra.startTime.hour, tra.startTime.min);
                tim1 = tim1 + traveltime;//首班车从站1离开时间
                tim2 = tim2 + traveltime;//末班车
                Time ti, t;//出发时间,到达时间
                ti.month_ = date.month, ti.day_ = date.day;
                ti.hour_ = tim1.hour_, ti.min = tim1.day_;
                int d=(ti-tim1)/1440;
                if (ti < tim1 || ti > tim2)continue;
                string put;
                traveltime = tra.travelTime[num2 - 1] - tra.travelTime[num1 - 1] + tra.stopTime[num2 - 1] -
                             tra.stopTime[num1];
                t = ti + traveltime;
                int price, seat = 1e5 + 5;
                price = tra.price[num2 - 1] - tra.price[num1 - 1];
                for (int k = num1; k < num2; k++) {
                    seat = std::min(seat, tra.seats[d+1][k]);
                }
                put= getstr(begin,end,ti,t);

                if (mode == 1) {
                    ans1[++cnt] = {seat, put, traveltime, price, tra.id};
                } else {
                    ans2[++cnt] = {seat, put, price, tra.id};
                }
                //put+=(ti.hour_<10?"0"+std::to_string(ti.day_):std::to_string(ti.day_))
                if (i == fin.size - 1 && fin.next != -1) {
                    tr1.myread(fin.next, fin);
                    i = -1;
                }
                if (j == finn.size - 1 && finn.next != -1) {
                    //cout<<fin.next;
                    tr1.myread(finn.next, finn);
//                    //cout<<fin.size<<' '<<fin.ele[0].valu<<'\n';
                    j = -1;
//                    //siz=fin.size;
                }
            }
            if ((!flag1) && (!fla1) && i == fin.size - 1 && fin.next != -1) {
                tr1.myread(fin.next, fin);
                fla1 = 1;
                i = -1;
            }
            if ((!flag2) && (!fla2) && j == finn.size - 1 && finn.next != -1) {
                tr1.myread(finn.next, finn);
                fla2 = 1;
                j = -1;
            }
        }
        printf("%d\n", cnt);
        if (cnt == 0)return;
        if (mode == 1) {
            merge1(ans1, 1, cnt);
            for (int k = 1; k <= cnt; k++) {
                printf("%s %s %d %d\n", ans1[k].id.trainid, ans1[k].s.c_str(), ans1[k].cost, ans1[k].seat);
            }
        } else {
            merge2(ans2, 1, cnt);
            for (int k = 1; k <= cnt; k++) {
                printf("%s %s %d %d\n", ans2[k].id.trainid, ans2[k].s.c_str(), ans2[k].cost, ans2[k].seat);
            }
        }

    }
    string getstr(station_name &begin,station_name &end,Time &ti,Time &t){
        string put;
        put += (std::string) begin.name + " " + "0" + std::to_string(ti.month_) + "-";
        if (ti.day_ < 10)put += "0";
        put += std::to_string(ti.day_) + " ";
        if (ti.hour_ < 10)put += "0";
        put += std::to_string(ti.hour_) + ":";
        if (ti.min < 10)put += "0";
        put += std::to_string(ti.min) + " -> " + (std::string) end.name + " " + "0" + std::to_string(t.month_) +
               "-";
        if (t.day_ < 10)put += "0";
        put += std::to_string(t.day_) + " ";
        if (t.hour_ < 10)put += "0";
        put += std::to_string(t.hour_) + ":";
        if (t.min < 10)put += "0";
        put += std::to_string(t.min);
        return put;
    }

    void query_transfer(station_name &begin, station_name &end, saleDate &date, int mode) {
        out1 ans1;
        out2 ans2;
        int cnt = 0;
        bool flag1 = 0, flag2 = 0, fla1 = 0, fla2=0;
        point_<station_name, train> first(begin, train());
        //point_<station_name, train> second(end, train());
        block_<station_name, train> fin;
        //block_<station_name, train> finn;
        tr1.myread(tr1.root, fin);
        while (!fin.leaf) {
            int low = 0, high = fin.size;
            while (low < high) {
                int mid = (low + high) >> 1;
                if (first < fin.ele[mid]) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }
            tr1.myread(fin.pos[low], fin);
        }
        if (first.index < fin.mini.index) {
            printf("0\n");
            return;
        }
        int i = 0, j = 0;

        for (i = 0; i < fin.size; i++) {
            if (first.index < fin.ele[i].index)break;
            if (first.index == fin.ele[i].index) {
                train tra = fin.ele[i].valu;
                int num1 = fin.ele[i].index.num;
                flag1 = 1;
                Time tim1(tra.startsale.month, tra.startsale.day, tra.startTime.hour, tra.startTime.min);
                Time tim2(tra.finishsale.month, tra.finishsale.day, tra.startTime.hour, tra.startTime.min);
                int traveltime = tra.travelTime[num1 - 1] + tra.stopTime[num1];
                tim1 = tim1 + traveltime;//首班车从站1离开时间
                tim2 = tim2 + traveltime;//末班车
                Time ti,t;
                ti.month_ = date.month, ti.day_ = date.day;
                ti.hour_ = tim1.hour_, ti.min = tim1.day_;
                if (ti < tim1||ti > tim2)continue;
                for (j = num1+1; j <= tra.station_num; j++) {
                    station_name mid=tra.name[j];
                    traveltime=tra.travelTime[j-1]-tra.travelTime[num1-1]+tra.stopTime[j-1]-tra.stopTime[num1];
                    t=ti+traveltime;
                    int price, seat = 1e5 + 5;
                    price = tra.price[j - 1] - tra.price[num1 - 1];
                    int d=ti-tim1;
                    d/=1440;
                    for (int k = num1; k < j; k++) {
                        seat = std::min(seat, tra.seats[d+1][k]);
                    }
                    out1 an1;
                    out2 an2;
                    string put= getstr(begin,mid,ti,t);
                    if(mode==1){
                        an1.time=traveltime;
                        an1.cost=price;
                        an1.id1=tra.id;
                        an1.cost1=price;
                        an1.s1=put;
                        an1.seat1=seat;
                    }else{
                        an2.time=traveltime;
                        an2.cost=price;
                        an2.id1=tra.id;
                        an2.cost1=price;
                        an2.s1=put;
                        an2.seat1=seat;
                    }
                    int num=find_transfer(mid,end,t,mode,an1,an2);
                    cnt+=num;
                    if(num!=0){
                        if(mode==1){
                            ans1=std::min(ans1,an1);
                        }else{
                            ans2=std::min(ans2,an2);
                        }
                    }

                }
                if (i == fin.size - 1 && fin.next != -1) {
                    tr1.myread(fin.next, fin);
                    i = -1;
                }
            }
            if ((!flag1) && (!fla1) && i == fin.size - 1 && fin.next != -1) {
                tr1.myread(fin.next, fin);
                fla1 = 1;
                i = -1;
            }
        }
        if(cnt==0){
            printf("0\n");
            return;
        }
        if(mode==1){
            printf("%s %s %d %d\n",ans1.id1.trainid,ans1.s1.c_str(),ans1.cost1,ans1.seat1);
            printf("%s %s %d %d\n",ans1.id2.trainid,ans1.s2.c_str(),ans1.cost2,ans1.seat2);
        }else{
            printf("%s %s %d %d\n",ans2.id1.trainid,ans2.s1.c_str(),ans2.cost1,ans2.seat1);
            printf("%s %s %d %d\n",ans2.id2.trainid,ans2.s2.c_str(),ans2.cost2,ans2.seat2);
        }



    }
    int find_transfer(station_name &begin, station_name &end, Time &date, int mode,out1 &ans1,out2 &ans2) {
        //long long pri
        int cnt = 0;
        //bool fl=0;
        bool flag1 = 0, flag2 = 0, fla1 = 0, fla2=0;
        point_<station_name, train> first(begin, train()), second(end, train());
        block_<station_name, train> fin, finn;
        tr1.myread(tr1.root, fin);
        //cout<<fin.ele[1].valu;
        while (!fin.leaf) {
            int low = 0, high = fin.size;
            while (low < high) {
                //if(fin.leaf)break;
                int mid = (low + high) >> 1;
                if (first < fin.ele[mid]) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }
            //cout<<low;
            tr1.myread(fin.pos[low], fin);
        }
        tr1.myread(tr1.root, finn);
        //cout<<fin.ele[1].valu;
        while (!finn.leaf) {
            int low = 0, high = finn.size;
            while (low < high) {
                //if(fin.leaf)break;
                int mid = (low + high) >> 1;
                if (second < finn.ele[mid]) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }
            tr1.myread(finn.pos[low], finn);
        }
        if (first.index < fin.mini.index || second.index < finn.mini.index) {
            //printf("0\n");
            return 0;
        }
        int i = 0, j = 0;
        for (; i < fin.size && j < finn.size; i++, j++) {
//            //cout<<fin.ele[0].valu<<' ';
            if (first.index < fin.ele[i].index || second.index < finn.ele[j].index)break;
            if (fin.ele[i].index == first.index && finn.ele[j].index != second.index)i--;
            if (fin.ele[i].index != first.index && finn.ele[j].index == second.index)j--;
            if (fin.ele[i].index == first.index && finn.ele[j].index == second.index) {
                flag1 = 1;
                flag2 = 1;
//                //cout<<1;
                //printf("%d ",fin.ele[i].valu);
                if (fin.ele[i].valu < finn.ele[j].valu) {
                    j--;
                    continue;
                } else if (fin.ele[i].valu > finn.ele[j].valu) {
                    i--;
                    continue;
                }
                if (fin.ele[i].index.num >= finn.ele[j].index.num)continue;
                int num1 = fin.ele[i].index.num, num2 = finn.ele[j].index.num;
                train tra = fin.ele[i].valu;


                int traveltime = tra.travelTime[num1 - 1] + tra.stopTime[num1];
                //int hour,min,month,day;
                Time tim1(tra.startsale.month, tra.startsale.day, tra.startTime.hour, tra.startTime.min);
                Time tim2(tra.finishsale.month, tra.finishsale.day, tra.startTime.hour, tra.startTime.min);
                tim1 = tim1 + traveltime;//首班车从站1离开时间
                tim2 = tim2 + traveltime;//末班车
                Time ti, t;//出发时间,到达时间
                //ti=date;//前一趟车到站时间
                ti.month_ = date.month_, ti.day_ = date.day_;
                ti.hour_ = tim1.hour_, ti.min = tim1.day_;
                //int wait;

                if (date > tim2){
                    continue;//要找的那一天晚于末班车
                }else if(date<tim1){
                    ti=tim1;
                    //fl=1;
                    //wait=tim1-date;//前一辆车到换乘站时间太早
                }else if(ti<date) {
//                    fl=1;
//                    wait=date-ti;
                    ti = ti + 1440;
                }
//                }else {
//                    continue;/////////////////////
//                }
                string put;
                traveltime = tra.travelTime[num2 - 1] - tra.travelTime[num1 - 1] + tra.stopTime[num2 - 1] -
                             tra.stopTime[num1];
                t = ti + traveltime;

                int d=ti-tim1;


                int price, seat = 1e5 + 5;
                price = tra.price[num2 - 1] - tra.price[num1 - 1];
                for (int k = num1; k < num2; k++) {
                    seat = std::min(seat, tra.seats[d+1][k]);
                }
                put= getstr(begin,end,ti,t);
                traveltime+=ti-date;
                //else traveltime+=wait;
                if (mode == 1) {
                    if(cnt==0){
                        ans1.time+=traveltime;
                        ans1.cost+=price;
                        ans1.cost2=price;
                        ans1.s2=put;
                        ans1.id2=tra.id;
                        ans1.seat2=seat;
                    }else{
                        out1 a1=ans1;
                        a1.time+=traveltime;
                        a1.cost+=price;
                        a1.s2=put;
                        a1.cost2=price;
                        a1.id2=tra.id;
                        a1.seat2=seat;
                        ans1=std::min(a1,ans1);
                    }

                } else {
                    if(cnt==0){
                        ans2.time+=traveltime;
                        ans2.cost+=price;
                        ans2.cost2=price;
                        ans2.s2=put;
                        ans2.id2=tra.id;
                        ans2.seat2=seat;
                    }else{
                        out2 a2=ans2;
                        a2.time+=traveltime;
                        a2.cost+=price;
                        a2.s2=put;
                        a2.cost2=price;
                        a2.id2=tra.id;
                        a2.seat2=seat;
                        ans2=std::min(a2,ans2);
                    }
                }
                cnt++;
                if (i == fin.size - 1 && fin.next != -1) {
                    tr1.myread(fin.next, fin);
                    i = -1;
                }
                if (j == finn.size - 1 && finn.next != -1) {

                    tr1.myread(finn.next, finn);
                    j = -1;
                }
            }
            if ((!flag1) && (!fla1) && i == fin.size - 1 && fin.next != -1) {
                tr1.myread(fin.next, fin);
                fla1 = 1;
                i = -1;
            }
            if ((!flag2) && (!fla2) && j == finn.size - 1 && finn.next != -1) {
                tr1.myread(finn.next, finn);
                fla2 = 1;
                j = -1;
            }
        }
        return cnt;

    }
    int buy_ticket(int tt,station_name &begin,station_name &end,int num,train &trai,bool flag,saleDate &date,string &put,long long &price,ticket_information &in){
        //bool flag1 = 0, flag2 = 0, fla1 = 0, fla2=0;

        bool find=0,pend=0;
        long long pri;
        point_<station_name, train> first(begin, trai), second(end, trai);
        block_<station_name, train> fin, finn;
        tr1.myread(tr1.root, fin);
        while (!fin.leaf) {
            int low = 0, high = fin.size;
            while (low < high) {
                //if(fin.leaf)break;
                int mid = (low + high) >> 1;
                if (first < fin.ele[mid]) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }
            tr1.myread(fin.pos[low], fin);
        }
        tr1.myread(tr1.root, finn);
        //cout<<fin.ele[1].valu;
        while (!finn.leaf) {
            int low = 0, high = finn.size;
            while (low < high) {
                //if(fin.leaf)break;
                int mid = (low + high) >> 1;
                if (second < finn.ele[mid]) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }
            tr1.myread(finn.pos[low], finn);
        }
        if (first.index < fin.mini.index || second.index < finn.mini.index) {
            printf("-1\n");
            return 0;
        }
        int i = 0, j = 0;
        for (; i < fin.size && j < finn.size; i++, j++) {
            if (first < fin.ele[i] || second < finn.ele[j])break;
            if (fin.ele[i] == first && finn.ele[j] < second)i--;
            if (fin.ele[i] < first && finn.ele[j] == second)j--;
            if (fin.ele[i] == first && finn.ele[j] == second) {

//                if (fin.ele[i].valu < finn.ele[j].valu) {
//                    j--;
//                    continue;
//                } else if (fin.ele[i].valu > finn.ele[j].valu) {
//                    i--;
//                    continue;
//                }
                if (fin.ele[i].index.num >= finn.ele[j].index.num)break;

//                flag1 = 1;
//                flag2 = 1;
                int num1 = fin.ele[i].index.num, num2 = finn.ele[j].index.num;
                train tra = fin.ele[i].valu;
                in.from=num1,in.to=num2;

                int traveltime = tra.travelTime[num1 - 1] + tra.stopTime[num1];
                //int hour,min,month,day;
                Time tim1(tra.startsale.month, tra.startsale.day, tra.startTime.hour, tra.startTime.min);
                Time tim2(tra.finishsale.month, tra.finishsale.day, tra.startTime.hour, tra.startTime.min);
                tim1 = tim1 + traveltime;//首班车从站1离开时间
                tim2 = tim2 + traveltime;//末班车
                Time ti, t;//出发时间,到达时间
                //ti=date;//前一趟车到站时间
                ti.month_ = date.month, ti.day_ = date.day;
                ti.hour_ = tim1.hour_, ti.min = tim1.day_;
                //int wait;
                if(ti<tim1||ti>tim2)break;
                find=1;
                Time mid=ti;
                mid=mid-traveltime;
                date.month=mid.month_,date.day=mid.day_;
                int d=ti-tim1;
                in.d=d;
                 price=tra.price[num2-1]-tra.price[num1-1];
                traveltime=tra.travelTime[num2-1]+tra.travelTime[num1-1]+tra.stopTime[num2-1]-tra.stopTime[num1];
                t=ti+traveltime;
                int seat=1e5+5;
                put= getstr(begin,end,ti,t);
                for(int k=num1;k<num2;k++){
                    seat=std::min(seat,tra.seats[d+1][k]);
                }
                if(seat>=num){
                    block<trainID,train>blk=tr.getblock(tra.id);
                    int tmp=0;
                    for(int l=0;l<blk.size;i++){
                        if(tra.id==blk.ele[l].index)break;
                        tmp++;
                    }
                    for(int k=num1;k<num2;k++){
                        //todo
                        blk.ele[tmp].valu.seats[d+1][k]-=seat;
                        tra.seats[d+1][k]-=seat;////////////


                    }
                    mywrite(blk);
                    pri=price*seat;
                }else{
                    if(flag){
                        pend=1;
                    }
                }

//                if (i == fin.size - 1 && fin.next != -1) {
//                    tr1.myread(fin.next, fin);
//                    i = -1;
//                }
//                if (j == finn.size - 1 && finn.next != -1) {
//
//                    tr1.myread(finn.next, finn);
//                    j = -1;
//                }
            }
//            if ((!flag1) && (!fla1) && i == fin.size - 1 && fin.next != -1) {
//                tr1.myread(fin.next, fin);
//                fla1 = 1;
//                i = -1;
//            }
//            if ((!flag2) && (!fla2) && j == finn.size - 1 && finn.next != -1) {
//                tr1.myread(finn.next, finn);
//                fla2 = 1;
//                j = -1;
//            }
        }
        if(!find){
            printf("-1\n");
            return 0;
        }else{
            if(pend){
                printf("queue\n");

                //todo
                return 1;
            }else{
                std::cout<<pri<<'\n';
                return 2;
            }
        }

    }
};

#endif //B_TREE_TRAIN_H
