
#ifndef CODE_B_TREE_H
#define CODE_B_TREE_H
#include<fstream>
#include<cstring>
#include "vector.hpp"
struct myString {//index
private:
    char s[70];
public:
    myString() {};

    myString(char *p) {
        int length = strlen(p);
        if (length > 64) {
            exit(1);
        }
        for (int i = 0; i < length; ++i) {
            s[i] = p[i];
        }
        s[length] = '\0';
    }

    ~myString() = default;

    friend bool operator==(const myString &x, const myString &y) {
        return (!strcmp(x.s, y.s));
    }

    friend bool operator<(const myString &x, const myString &y) {
        return (strcmp(x.s, y.s) < 0);
    }

    friend bool operator<=(const myString &x, const myString &y) {
        return (x < y) || (x == y);
    }

    friend std::ostream &operator<<(std::ostream &x, const myString &y) {
        x << y.s;
        return x;
    };
};

template<class key, class T>
struct point {//叶子上元素
    key index;
    T valu;

    point() = default;

    point(const key &a, const T &b) : index(a), valu(b) {
//        index = a;
//        valu = b;
    }

//    friend bool operator==(const point &a, const point &b) {
//        return (a.index == b.index && a.valu == b.valu);
//    }

    friend bool operator<(const point &a, const point &b) {
        return ((a.index < b.index) || (a.index == b.index && a.valu < b.valu));
    }

//    friend bool operator>(const point &a, const point &b) {
//        return (!(a == b) && (!(a < b)));
//    }

    friend bool operator>=(const point &a, const point &b) {
        return !(a < b);
    }

//    friend bool operator<=(const point &a, const point &b) {
//        return !(a > b);
//    }
};
//struct dir {
//    int pla;//第几号
//    bool lea;//指向的那个是不是叶子
//};

template<class key, class T>
struct block {
    int next = -1;
    int pre = -1;
    point<key, T> mini, maxi;
    int size = 0;
    bool leaf = false;
    int place = 0;
    int parent = -1;

    point<key, T> ele[25];
    int pos[25];//子树位置
    block<key,T>(){
        memset(pos,0,sizeof(pos));

    }
    block<key,T>(const block<key,T>& other){
        next=other.next;
        pre=other.pre;
        mini=other.mini;
        maxi=other.maxi;
        size=other.size;
        leaf=other.leaf;
        place=other.place;
        parent=other.parent;
        for(int i=0;i<size;i++){
            ele[i]=other.ele[i];
            pos[i]=other.pos[i];
        }
        pos[size]=other.pos[size];
    }
//    block(){}
//    block(const block<key,T> &other){
//        next=other.next;
//        pre=other.pre;
//        mini=other.mini;maxi=other.maxi;
//        size=other.size;
//        leaf=other.leaf;
//        place=other.place;
//        parent=other.parent;
//        for(int i=0;i<size;i++){
//            ele[i]=other.ele[i];
//            pos[i]=other.pos[i];
//        }
//        pos[size]=other.pos[size];
//    }
};

template<class key, class T>
class b_plus_tree {
public:
    const int maxsize = 16, minsize = 8,m=17;
    int total=-1;
    sjtu::vector<int> vec;
    sjtu::vector<block<key,T>>ve;
    std::string file;
    std::fstream inout;
    int root=-1;

    b_plus_tree() = default;

    b_plus_tree(std::string name)   {
        file=name;
        inout.open(file);
        if (!inout) {
            block<key, T> tmp;
            std::ofstream out;
            out.open(file);
            //num_of_find = -1;
            root=-1;
            total=-1;
            //num_of_block = -1;
            out.write(reinterpret_cast<char *>(&total), sizeof(total));
            out.write(reinterpret_cast<char *>(&root), sizeof(root));
            out.write(reinterpret_cast<char *>(&tmp), sizeof(tmp));

            out.close();
            inout.open(file);
            return;
        }
        inout.seekg(0);
        inout.read(reinterpret_cast<char *>(&total), sizeof(total));
        inout.read(reinterpret_cast<char *>(&root), sizeof(root));

    }

    ~b_plus_tree() {
        //std::cout<<666666<<std::endl;
        inout.seekp(0);
        inout.write(reinterpret_cast<char *>(&total), sizeof(total));
        inout.write(reinterpret_cast<char *>(&root), sizeof(root));
        inout.close();
    }

    void myre(int coord, block<key, T> &node) {
        if (coord < 0) {
            exit(1);
        }
        inout.seekg(coord * sizeof(block<key, T>) + 2*sizeof(int));
        inout.read(reinterpret_cast<char *>(&(node.next)), sizeof(node.next));
        inout.read(reinterpret_cast<char *>(&(node.mini)), sizeof(node.mini));
        inout.read(reinterpret_cast<char *>(&(node.maxi)), sizeof(node.maxi));
        inout.read(reinterpret_cast<char *>(&(node.size)), sizeof(node.size));
        inout.read(reinterpret_cast<char *>(&(node.leaf)), sizeof(node.leaf));

    }

    void myread(int coord, block<key, T> &node) {
        if (coord < 0) {
            exit(1);
        }
        inout.seekg(coord * sizeof(block<key, T>) + 2*sizeof(int));
        inout.read(reinterpret_cast<char *>(&node), sizeof(node));
    }

    void mywrite(int coord, block<key, T> &node) {
        if (coord < 0) {
            exit(1);
        }
        //cout<<node.size;
        inout.seekp(coord * sizeof(block<key, T>) + 2*sizeof(int));
        inout.write(reinterpret_cast<char *>(&node), sizeof(node));

    }

    void insert(point<key, T> &ele) {
        block<key, T> new_;
        //myread(0, new_);

        if (root==-1) {

            root=0;
            total=0;
            new_.leaf=1;
            new_.place=0;
            new_.size = 1;
            new_.mini = new_.maxi = ele;
            new_.ele[0] = ele;
            mywrite(total, new_);
            return;
        }
        myread(root,new_);
        ve.push_back(new_);
        while(!new_.leaf){
            //cout<<root<<endl;
            //cout<<new_.size<<' ';cout<<new_.ele[0].valu<<' '<<new_.ele[1].valu<<'\n';
            int low=0,high=new_.size;
            while(low<high){
                //if(fin.leaf)break;

                int mid=(low+high)>>1;
                if(ele.index<new_.ele[mid].index){
                    high=mid;
                }else{
                    low=mid+1;
                }
            }
            //cout<<low;

            vec.push_back(low);
            myread(new_.pos[low],new_);
            if(!new_.leaf)ve.push_back(new_);
        }//找块
        //cout<<new_.parent<<' '<<new_.ele[0].valu<<'\n';

        int tmp=0;
        for(int i=0;i<new_.size;i++){
            if(ele.index<new_.ele[i].index)break;
            tmp++;
        }
        for(int i=new_.size;i>tmp;i--){
            new_.ele[i]=new_.ele[i-1];
        }
        new_.ele[tmp]=ele;
        new_.size++;
        if(new_.size>maxsize){
            //cout<<new_.place<<' '<<total;
            split(new_.place,new_);
        }else{
            new_.mini=new_.ele[0];
            new_.maxi=new_.ele[new_.size-1];
            mywrite(new_.place,new_);
//            if(tmp==0&&root!=0){
//                adjust(new_,ele);
//            }
        }

        ve.clear();
        vec.clear();
    }

    void split(int coord,block<key,T> &node){
        total++;
        //num_of_block++;
        block<key,T> nod,tmp,tm;
        //block<key,T> tmp;
        for(int i=minsize;i<node.size;i++){
            nod.ele[i-minsize]=node.ele[i];
        }
        nod.leaf=1;
        //nod.mini
        nod.size = minsize + 1;
        nod.place=total;
        nod.pre=node.place;
        if(node.next!=-1){
            myread(node.next,tm);
            tm.pre=nod.place;
            mywrite(tm.place,tm);

        }
        nod.next = node.next;
        node.next = nod.place;
        node.size = minsize;
        node.maxi = node.ele[node.size - 1];
        node.mini = node.ele[0];
        nod.maxi = nod.ele[node.size];
        nod.mini = nod.ele[0];
        nod.parent=node.parent;
        //cout<<coord<<' '<<nod.place;

        //cout<<nod.ele[1].valu<<' ';
        if(root==node.place){
            total++;
            root=total;
            node.parent=nod.parent=root;
            tmp.place=root;
            tmp.pos[0]=node.place;
            tmp.pos[1]=nod.place;
            tmp.ele[0]=nod.mini;
            tmp.size++;
            mywrite(total,tmp);
            mywrite(coord, node);
            mywrite(nod.place, nod);
        }else{
            mywrite(coord, node);
            mywrite(nod.place, nod);
            balance_insert(node,nod);

        }
    }

    void balance_insert(block<key,T> &first,block<key,T>&second){
        block<key,T>tmp;
        while(vec.size()){

            tmp=ve.back();
            ve.pop_back();

            int pla=vec.back();
            vec.pop_back();
            for(int i=tmp.size;i>pla;i--){
                tmp.ele[i]=tmp.ele[i-1];
                tmp.pos[i+1]=tmp.pos[i];
            }
            if(second.leaf){
                tmp.ele[pla]=second.mini;///////////////////
            }else{
                tmp.ele[pla]=first.ele[minsize];
            }
            tmp.pos[pla+1]=second.place;
            tmp.size++;
//            cout<<tmp.place<<' ';
//            cout<<second.ele[0].valu<<' '<<second.ele[1].valu;
            if(tmp.size>maxsize){

                block<key,T>tp=split_find(tmp.place,tmp);
                balance_insert(tmp,tp);
                break;
            }else{
                mywrite(tmp.place,tmp);
                return;

            }
        }
    }
    block<key,T> split_find(int coord,block<key,T> &node){
        total++;
        block<key,T> nod,tmp,tm;
        for(int i=minsize+1;i<=maxsize;i++){
            nod.ele[i-minsize-1]=node.ele[i];
            nod.pos[i-minsize-1]=node.pos[i];
            myread(node.pos[i],tm);
            tm.parent=total;
            mywrite(node.pos[i],tm);
        }
        nod.parent=node.parent;
        nod.pos[maxsize-minsize]=node.pos[node.size];
        myread(node.pos[node.size],tm);
        tm.parent=total;
        mywrite(node.pos[node.size],tm);
        nod.size=minsize;
        nod.place=total;
        nod.pre=node.place;
        if(node.next!=-1){
            myread(node.next,tm);
            tm.pre=nod.place;
            mywrite(tm.place,tm);
        }
        nod.next=node.next;
        node.next=nod.place;
        node.size=minsize;

        //tm=ve.back();
        //tm.ele
        if(coord==root){

            total++;
            root=total;
            tmp.size=1;
            tmp.place=total;
            tmp.ele[0]=node.ele[minsize];
            tmp.pos[0]=node.place;
            tmp.pos[1]=nod.place;
            node.parent=nod.parent=root;
            mywrite(total,tmp);

        }
        mywrite(coord,node);
        mywrite(nod.place,nod);
        return nod;
    }
//    void modify(point<key,T> &p){
//
//    }
    bool exist(key ke) {

        point<key,T>k(ke,T());
        //std::cout<<11111<<std::endl;
        bool flag=0,fla=0;
        //compare cp;

        block<key,T> fin;

        if(root==-1){
            //std::cout<<1<<' ';

//            printf("%s\n","null");
            return flag;

        }

        myread(root,fin);
        //cout<<fin.ele[1].valu;
        while(!fin.leaf){
            //std::cout<<root<<std::endl;
            //cout<<fin.size<<' '<<fin.ele[0].valu<<' '<<fin.ele[1].valu<<' '<<fin.ele[2].valu<<'\n';
            int low=0,high=fin.size;
            while(low<high){

                //if(fin.leaf)break;
                int mid=(low+high)>>1;
                if(k.index<fin.ele[mid].index){
                    high=mid;
                }else{
                    low=mid+1;
                }
            }
            //cout<<low;
            myread(fin.pos[low],fin);
        }
        //cout<<fin.ele[2].valu<<' '<<fin.ele[1].valu<<'\n';


        if(k.index<fin.mini.index){

            //printf("%s\n","null");
            return flag;
        }

        //int siz=fin.size;
        //cout<<fin.ele[0].valu<<fin.ele[1].valu;
        for(int i=0;i<fin.size;i++){
            //cout<<fin.ele[0].valu<<' ';
            if(k.index<fin.ele[i].index)break;
            if(fin.ele[i].index==k.index){
                flag=1;
                break;
                //cout<<1;
                //printf("%d ",fin.ele[i].valu);

//                if(i==fin.size-1&&fin.next!=-1){
//                    //cout<<fin.next;
//                    myread(fin.next,fin);
//                    //cout<<fin.size<<' '<<fin.ele[0].valu<<'\n';
//                    i=-1;
//                    //siz=fin.size;
//                }
            }
//            if((!flag)&&(!fla)&&i==fin.size-1&&fin.next!=-1){
//                myread(fin.next,fin);
//                fla=1;
//                i=-1;
//            }

        }
        return flag;
//        if(!flag)printf("%s\n","null");
//        else printf("\n");
    }
    block<key,T> getblock(key ke){
        point<key,T>k(ke,T());
        bool flag=0,fla=0;
        //compare cp;
        block<key,T> fin;
        myread(root,fin);
        //cout<<fin.ele[1].valu;
        while(!fin.leaf){
            //cout<<fin.size<<' '<<fin.ele[0].valu<<' '<<fin.ele[1].valu<<' '<<fin.ele[2].valu<<'\n';
            int low=0,high=fin.size;
            while(low<high){
                //if(fin.leaf)break;
                int mid=(low+high)>>1;
                if(k.index<fin.ele[mid].index){
                    high=mid;
                }else{
                    low=mid+1;
                }
            }
            //cout<<low;
            myread(fin.pos[low],fin);
        }
        return fin;
//        for(int i=0;i<fin.size;i++){
//            //cout<<fin.ele[0].valu<<' ';
//            //if(k.index<fin.ele[i].index)break;
//            if(fin.ele[i].index==k.index){
//                return fin.ele[i].valu;
//
//            }
//
//        }
    }
    T find(key ke) {
        point<key,T>k(ke,T());
        bool flag=0,fla=0;
        //compare cp;
        block<key,T> fin;
        myread(root,fin);
        //cout<<fin.ele[1].valu;
        while(!fin.leaf){
            //cout<<fin.size<<' '<<fin.ele[0].valu<<' '<<fin.ele[1].valu<<' '<<fin.ele[2].valu<<'\n';
            int low=0,high=fin.size;
            while(low<high){
                //if(fin.leaf)break;
                int mid=(low+high)>>1;
                if(k.index<fin.ele[mid].index){
                    high=mid;
                }else{
                    low=mid+1;
                }
            }
            //cout<<low;
            myread(fin.pos[low],fin);
        }
        for(int i=0;i<fin.size;i++){
            //cout<<fin.ele[0].valu<<' ';
            //if(k.index<fin.ele[i].index)break;
            if(fin.ele[i].index==k.index){
                return fin.ele[i].valu;

            }

        }
    }
    void adjust(block<key,T>new_,point<key,T>&ele){
        while(vec.size()){
            int pla=vec.back();
            vec.pop_back();
            //block<key, T> new__;
            if(pla!=0){
                new_=ve.back();
                new_.ele[pla-1]=ele;
                mywrite(new_.place,new_);

                //break;
            }
            ////////////////
            ve.pop_back();

        }
    };

    int bound(int low,int high,block<key,T>&fin,point<key,T>&ele){
        while(low<high){
            //if(fin.leaf)break;
            int mid=(low+high)>>1;
            if(ele.index<fin.ele[mid].index){
                high=mid;
            }else{
                low=mid+1;
            }
        }
        return low;
    }
    void del(point<key, T> &ele) {
        if(root==-1)return;
        block<key,T>fin;
        myread(root,fin);
        while(!fin.leaf){
            //cout<<fin.size<<' '<<fin.ele[0].valu<<' '<<fin.ele[1].valu<<' '<<fin.ele[2].valu<<'\n';
            int low=0,high=fin.size;
            low= bound(low,high,fin,ele);
            //cout<<low<<'\n';
            myread(fin.pos[low],fin);
        }//找块
        //cout<<fin.size<<' '<<fin.ele[0].valu<<' '<<fin.ele[1].valu<<'\n';
        //}
//        myread(fin.pre,fin);
//        cout<<fin.size<<' '<<fin.ele[0].valu<<' '<<fin.ele[1].valu<<'\n';

        int tmp=0;
        for(int i=0;i<fin.size;i++){
            if(ele.index==fin.ele[i].index)break;
            tmp++;
        }
        for(int i=tmp;i<fin.size-1;i++){
            fin.ele[i]=fin.ele[i+1];
        }
        if(tmp==fin.size)return;
        fin.size--;
        if(root!=fin.place){
            if(tmp==0){
                point<key,T>el=fin.ele[0];
                change(fin,ele,el);

            }
            if(fin.size>=minsize){
                fin.mini=fin.ele[0];
                fin.maxi=fin.ele[fin.size-1];

                mywrite(fin.place,fin);

            }else{
                dispose(fin);
            }
        }else{
            mywrite(fin.place,fin);
        }

    }
    void change(block<key,T> node,point<key,T>&past,point<key,T>new_){
        while(node.parent!=-1){
            myread(node.parent,node);
            int low=0,high=node.size;
            while(low<high){
                int mid=(high+low)>>1;
                if(past.index<node.ele[mid].index){
                    high=mid;
                }else{
                    low=mid+1;
                }
            }

            if(low!=0){
                node.ele[low-1]=new_;
                mywrite(node.place,node);
                break;
            }
        }
    }
    void dispose(block<key,T> &node){
        block<key,T>nxt;
        if(node.next!=-1){
            myread(node.next,nxt);
            if(nxt.size>minsize){
                node.ele[node.size]=nxt.ele[0];
                node.size++;
                node.maxi=nxt.ele[0];
                point<key,T>ele=nxt.ele[1],el=nxt.ele[0];
                nxt.mini=nxt.ele[1];

                for(int i=1;i<nxt.size;i++){
                    nxt.ele[i-1]=nxt.ele[i];
                }
                nxt.size--;
                mywrite(node.place,node);
                mywrite(nxt.place,nxt);

                change(nxt,el,ele);
            }else{
                if(nxt.parent==node.parent){
                    merge(node,nxt);
                }else{
                    myread(node.pre,nxt);
                    if(nxt.size>minsize){
                        point<key,T>ele=nxt.ele[nxt.size-1],el=node.ele[0];
                        for(int i=node.size;i>0;i--){
                            node.ele[i]=node.ele[i-1];
                        }
                        node.ele[0]=nxt.ele[nxt.size-1];

                        node.size++;

                        node.mini=nxt.ele[0];
                        nxt.maxi=nxt.ele[nxt.size-2];


                        nxt.size--;
                        mywrite(node.place,node);
                        mywrite(nxt.place,nxt);

                        change(node,el,ele);
                    }else{
                        merge(nxt,node);
                    }
                }
            }
        }else{
            myread(node.pre,nxt);
            if(nxt.size>minsize){
                point<key,T>ele=nxt.ele[nxt.size-1],el=node.ele[0];
                for(int i=node.size;i>0;i--){
                    node.ele[i]=node.ele[i-1];
                }
                node.ele[0]=nxt.ele[nxt.size-1];
                node.size++;
                node.mini=nxt.ele[0];
                nxt.maxi=nxt.ele[nxt.size-2];
                nxt.size--;
                mywrite(node.place,node);
                mywrite(nxt.place,nxt);
                change(node,el,ele);
            }else{
                merge(nxt,node);
            }
        }
    }
    void merge(block<key,T>&first,block<key,T>&second){
        block<key, T>tp;
        for(int i=first.size;i<first.size+second.size;i++){
            first.ele[i]=second.ele[i-first.size];
        }
        if(second.next!=-1){
            myread(second.next,tp);
            tp.pre=first.place;
            mywrite(tp.place,tp);
        }
        first.next=second.next;
        first.size+=second.size;
        first.maxi=first.ele[first.size-1];
        mywrite(first.place,first);
        balance_delete(first,second);
    }
    void balance_delete(block<key,T>&first,block<key,T>&second){
        //std::cout<<1<<std::endl;
        block<key,T>tmp,tm,son,pa;
        if(first.parent!=-1){
            myread(second.parent,tmp);
            int low = 0, high = tmp.size;
            //if(first.parent==second.parent) {
            low= bound(low,high,tmp,second.ele[0]);

            for (int i = low; i < tmp.size; i++) {
                tmp.ele[i - 1] = tmp.ele[i];
                tmp.pos[i] = tmp.pos[i + 1];
            }
            tmp.size--;
            if(tmp.place==root){
                if(tmp.size==0){
                    myread(tmp.pos[0],son);
                    root=son.place;
                    son.parent=-1;
                    mywrite(son.place,son);
                }
                mywrite(tmp.place,tmp);
            }else if(tmp.size<minsize&&tmp.next!=-1){
                myread(tmp.next,tm);
                if(tm.size>minsize&&tmp.parent==tm.parent){
                    point<key,T> k=tm.ele[0];
                    myread(tmp.parent,pa);
                    myread(tm.pos[0],son);
                    son.parent=tmp.place;
                    //while()
                    low=bound(0,pa.size,pa,k);
                    tmp.ele[minsize-1]=pa.ele[low-1];
                    tmp.pos[minsize]=tm.pos[0];
                    pa.ele[low-1]=tm.ele[0];
                    tmp.size++;

                    mywrite(son.place,son);
                    for(int i=1;i<tm.size;i++){
                        tm.ele[i-1]=tm.ele[i];

                        tm.pos[i-1]=tm.pos[i];
                    }
                    tm.pos[tm.size-1]=tm.pos[tm.size];
                    tm.size--;
                    mywrite(pa.place,pa);
                    mywrite(tmp.place,tmp);
                    mywrite(tm.place,tm);
                    //change(tm,el,ele);
                }else{
                    if(tm.parent==tmp.parent){
                        merge_find(tmp,tm);
                        balance_delete(tmp,tm);
                    }else{
                        myread(tmp.pre,tm);
                        if(tm.size>minsize){
                            point<key,T> k=tm.ele[tm.size-1];
                            myread(tmp.parent,pa);
                            myread(tm.pos[tm.size],son);
                            son.parent=tmp.place;
                            mywrite(son.place,son);

                            //while()
                            low=bound(0,pa.size,pa,k);
                            for(int i=tmp.size;i>0;i--){
                                tmp.ele[i]=tmp.ele[i-1];

                                tmp.pos[i+1]=tmp.pos[i];
                            }
                            tmp.pos[1]=tmp.pos[0];
                            tmp.ele[0]=pa.ele[low];
                            pa.ele[low]=tm.ele[tm.size-1];
                            tmp.pos[0]=tm.pos[tm.size];
                            tmp.size++;
                            //tm.pos[tm.size-1]=tm.pos[tm.size];
                            tm.size--;
                            mywrite(pa.place,pa);
                            mywrite(tmp.place,tmp);
                            mywrite(tm.place,tm);
                        }else{
                            merge_find(tm,tmp);
                            balance_delete(tm,tmp);
                        }

                    }
                }
                //break;
            }else if(tmp.size<minsize&&tmp.next==-1){
                myread(tmp.pre,tm);
                if(tm.size>minsize){
                    point<key,T> k=tm.ele[tm.size-1];
                    myread(tmp.parent,pa);
                    myread(tm.pos[tm.size],son);
                    son.parent=tmp.place;
                    mywrite(son.place,son);

                    //while()
                    low=bound(0,pa.size,pa,k);
                    for(int i=tmp.size;i>0;i--){
                        tmp.ele[i]=tmp.ele[i-1];

                        tmp.pos[i+1]=tmp.pos[i];
                    }
                    tmp.pos[1]=tmp.pos[0];
                    tmp.ele[0]=pa.ele[low];
                    pa.ele[low]=tm.ele[tm.size-1];
                    tmp.pos[0]=tm.pos[tm.size];
                    tmp.size++;

                    //tm.pos[tm.size-1]=tm.pos[tm.size];
                    tm.size--;
                    mywrite(pa.place,pa);
                    mywrite(tmp.place,tmp);
                    mywrite(tm.place,tm);
                }else{
                    merge_find(tm,tmp);
                    balance_delete(tm,tmp);
                }
            }else{
                mywrite(tmp.place,tmp);
            }

            //break;
        }
    }

    void merge_find(block<key,T> &first,block<key,T> &second){
        block<key,T>blk;
        for(int i=first.size+1;i<=first.size+second.size;i++){
            first.ele[i]=second.ele[i-first.size-1];
            first.pos[i]=second.pos[i-first.size-1];
            myread(second.pos[i-first.size-1],blk);
            blk.parent=first.place;
            mywrite(blk.place,blk);
            if(i==first.size+1){
                myread(first.parent,blk);
                int low=bound(0,blk.size,blk,second.ele[0]);

                first.ele[first.size]=blk.ele[low-1];
            }
        }
        first.pos[first.size+second.size+1]=second.pos[second.size];
        myread(second.pos[second.size],blk);
        blk.parent=first.place;
        mywrite(blk.place,blk);
        if(second.next!=-1){
            myread(second.next,blk);
            blk.pre=first.place;
            mywrite(blk.place,blk);
        }
        first.next=second.next;
        first.size+=(second.size+1);
        first.maxi=first.ele[first.size-1];
        mywrite(first.place,first);
    }

};

#endif //CODE_B_TREE_H
