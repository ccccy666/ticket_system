//
// Created by DELL on 2023/5/23.
//

#ifndef CODE_LINKED_HASH_MAP_H
#define CODE_LINKED_HASH_MAP_H
#include<fstream>
#include<iostream>
//template<class T>
//struct node{
//
//};
template<class T>
class list{
public:
    int total=-1;
    std::string file;
    std::fstream inout;
    list(std::string name)   {
        file=name;
        inout.open(file);
        if (!inout) {
            T tmp;
            std::ofstream out;
            out.open(file);
            //num_of_find = -1;
            //root=-1;
            total=-1;
            //num_of_block = -1;
            out.write(reinterpret_cast<char *>(&total), sizeof(total));
            //out.write(reinterpret_cast<char *>(&root), sizeof(root));
            out.write(reinterpret_cast<char *>(&tmp), sizeof(tmp));

            out.close();
            inout.open(file);
            return;
        }
        inout.seekg(0);
        inout.read(reinterpret_cast<char *>(&total), sizeof(total));
        //inout.read(reinterpret_cast<char *>(&root), sizeof(root));

    }

    ~list() {
        //std::cout<<666666<<std::endl;
        inout.seekp(0);
        inout.write(reinterpret_cast<char *>(&total), sizeof(total));
        //inout.write(reinterpret_cast<char *>(&root), sizeof(root));
        inout.close();
    }

//    void myre(int coord, T &node) {
//        if (coord < 0) {
//            exit(1);
//        }
//        inout.seekg(coord * sizeof(T) + sizeof(int));
//        inout.read(reinterpret_cast<char *>(&(node.next)), sizeof(node.next));
//        inout.read(reinterpret_cast<char *>(&(node.mini)), sizeof(node.mini));
//        inout.read(reinterpret_cast<char *>(&(node.maxi)), sizeof(node.maxi));
//        inout.read(reinterpret_cast<char *>(&(node.size)), sizeof(node.size));
//        inout.read(reinterpret_cast<char *>(&(node.leaf)), sizeof(node.leaf));
//
//    }

    void myread(int coord, T &node) {
        if (coord < 0) {
            exit(1);
        }
        inout.seekg(coord * sizeof(T) + sizeof(int));
        inout.read(reinterpret_cast<char *>(&node), sizeof(node));
    }

    void mywrite(int coord, T &node) {
        if (coord < 0) {
            exit(1);
        }
        //cout<<node.size;
        inout.seekp(coord * sizeof(T) + sizeof(int));
        inout.write(reinterpret_cast<char *>(&node), sizeof(node));

    }



};
#endif //CODE_LINKED_HASH_MAP_H
