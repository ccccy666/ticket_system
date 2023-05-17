#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>

namespace sjtu {
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
    template<typename T>
    class vector {
    public:
        /**
         * TODO
         * a type for actions of the elements of a vector, and you should write
         *   a class named const_iterator with same interfaces.
         */
        /**
         * you can see RandomAccessIterator at CppReference for help.
         */
        //T *array = nullptr;
        T*tmp= nullptr;
        int capacity = 16;
        int length = -1;//下标
        std::allocator<T>alloc;
        class const_iterator;
        class iterator {
            // The following code is written for the C++ type_traits library.
            // Type traits is a C++ feature for describing certain properties of a type.
            // For instance, for an iterator, iterator::value_type is the type that the
            // iterator points to.
            // STL algorithms and containers may use these type_traits (e.g. the following
            // typedef) to work properly. In particular, without the following code,
            // @code{std::sort(iter, iter1);} would not compile.
            // See these websites for more information:
            // https://en.cppreference.com/w/cpp/header/type_traits
            // About value_type: https://blog.csdn.net/u014299153/article/details/72419713
            // About iterator_category: https://en.cppreference.com/w/cpp/iterator
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T *;
            using reference = T &;
            using iterator_category = std::output_iterator_tag;

        private:
            /**
             * TODO add data members
             *   just add whatever you want.
             */
        public:
            int num=-1;
            vector<T> * vec;
            iterator(){
                vec= nullptr;
            }

            iterator(const iterator&it){
                num=it.num;
                vec=it.vec;
            }
            /**
             * return a new iterator which pointer n-next elements
             * as well as operator-
             */
            iterator operator+(const int &n)  {
                iterator itt=*this;
                itt.num+=n;
//                for (int i = 0; i < n; i++) {
//                    itt.point++;
//                    //num++;
//                }
                return itt;
                //TODO
            }

            iterator operator-(const int &n)  {
                iterator itt=*this;
                itt.num-=n;
//                for (int i = 0; i < n; i++) {
//                    itt.point--;
//                }
                return itt;
                //TODO
            }

            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const iterator &rhs) const {
                invalid_iterator ex;
                //exception ex("","invalid_iterator");
                if(vec->tmp!=rhs.vec->tmp)throw ex.what();
                return num-rhs.num>0?num-rhs.num:rhs.num-num;
                //TODO
            }

            iterator &operator+=(const int &n) {
                num+=n;
                return *this;
                //TODO
            }

            iterator &operator-=(const int &n) {
                num-=n;
//                for(int i=0;i<n;i++){
//                    point--;
//                }
                return *this;
                //TODO
            }

            /**
             * TODO iter++
             */
            iterator operator++(int) {
                iterator it=*this;
                num++;
                //point++;
                return it;
            }

            /**
             * TODO ++iter
             */
            iterator &operator++() {
                num++;
                //point++;
                return *this;
            }

            /**
             * TODO iter--
             */
            iterator operator--(int) {
                iterator it=*this;
                num--;
                //point--;
                return it;
            }

            /**
             * TODO --iter
             */
            iterator &operator--() {
                num--;
                //point--;
                return *this;
            }

            /**
             * TODO *it
             */
            T &operator*() const {
                T *tp=vec->tmp;
                tp+=num;
                return *tp;
            }

            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator &rhs) const {
                return num==rhs.num&&rhs.vec->tmp==vec->tmp;
            }

            bool operator==(const const_iterator &rhs) const {
                return num==rhs.num&&rhs.vec->tmp==vec->tmp;
            }

            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return num!=rhs.num||rhs.vec->tmp!=vec->tmp;
            }

            bool operator!=(const const_iterator &rhs) const {
                return num!=rhs.num||rhs.vec->tmp!=vec->tmp;
            }
        };

        /**
         * TODO
         * has same function as iterator, just for a const object.
         */
        class const_iterator {
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T *;
            using reference = T &;
            using iterator_category = std::output_iterator_tag;
            //pointer point,head;
            int num=-1;
            const vector<T>* vec= nullptr;
            const_iterator operator+(const int &n)  {
                const_iterator itt=*this;
                itt.num+=n;
//                for (int i = 0; i < n; i++) {
//                    itt.point++;
//                    //num++;
//                }
                return itt;
                //TODO
            }

            const_iterator operator-(const int &n)  {
                const_iterator itt=*this;
                itt.num-=n;
//                for (int i = 0; i < n; i++) {
//                    itt.point--;
//                }
                return itt;
                //TODO
            }

            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const const_iterator &rhs) const {
                invalid_iterator ex;
                //exception ex("","invaild_iterator");
                if(vec->tmp!=rhs.vec->tmp)throw ex.what();
                return num-rhs.num>0?num-rhs.num:rhs.num-num;
                //TODO
            }

            const_iterator &operator+=(const int &n) {
                num+=n;
//                for(int i=0;i<n;i++){
//                    point++;
//                }
                return *this;
                //TODO
            }

            const_iterator &operator-=(const int &n) {
                num-=n;
//                for(int i=0;i<n;i++){
//                    point--;
//                }
                return *this;
                //TODO
            }

            /**
             * TODO iter++
             */
            const_iterator operator++(int) {
                const_iterator it=*this;
                num++;
                //point++;
                return it;
            }

            /**
             * TODO ++iter
             */
            const_iterator &operator++() {
                num++;
                //point++;
                return *this;
            }

            /**
             * TODO iter--
             */
            const_iterator operator--(int) {
                const_iterator it=*this;
                num--;
                //point--;
                return it;
            }

            /**
             * TODO --iter
             */
            const_iterator &operator--() {
                num--;
                return *this;
            }

            /**
             * TODO *it
             */
            T &operator*() const {
                T*tp=vec->tmp;
                tp+=num;
                return *tp;
            }

            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator &rhs) const {
                return num==rhs.num&&rhs.vec->tmp==vec->tmp;
            }

            bool operator==(const const_iterator &rhs) const {
                return num==rhs.num&&rhs.vec->tmp==vec->tmp;
            }

            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return num!=rhs.num||rhs.vec->tmp!=vec->tmp;
            }

            bool operator!=(const const_iterator &rhs) const {
                return num!=rhs.num||rhs.vec->tmp!=vec->tmp;
            }

        };

        /**
         * TODO Constructs
         * At least two: default constructor, copy constructor
         */
        vector() {
            tmp=alloc.allocate(capacity);
//            for(int i=0;i<capacity;i++){
//                alloc.construct(tmp+i,array[i]);
//            }
            length = -1;
        }

        vector(const vector &other) {
            if(tmp== nullptr){
                tmp=alloc.allocate(capacity);
                length = -1;
            }
            if (other.tmp != tmp) {
                for(int i=0;i<=length;i++){
                    alloc. destroy(tmp+i);
                }
                alloc.deallocate(tmp,capacity);
                capacity=other.capacity;
                tmp=alloc.allocate(capacity);
                length = other.length;
                for(int i=0;i<=length;i++){
                    alloc.construct(tmp+i,*(other.tmp+i));
                    //if(i<=length)array[i]=other.array[i];
                }
            }

        }
        /**
         * TODO Destructor
         */
        ~vector() {
            for(int i=0;i<=length;i++){
                alloc. destroy(tmp+i);
            }
            alloc.deallocate(tmp,capacity);
        }

        /**
         * TODO Assignment operator
         */
        vector &operator=(const vector &other) {
            if (other.tmp == tmp) {
                return *this;
            }
            for(int i=0;i<=length;i++){
                alloc. destroy(tmp+i);
            }
            alloc.deallocate(tmp,capacity);
            capacity=other.capacity;
            tmp=alloc.allocate(capacity);
            length = other.length;
            for(int i=0;i<=length;i++){
                alloc.construct(tmp+i,*(other.tmp+i));
                //if(i<=length)array[i]=other.array[i];
            }
            return *this;
        }

        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         */
        T &at(const size_t &pos) {
            index_out_of_bound ex;
            //exception ex("", "index_out_of_bound");
            //ex.detail="index_out_of_bound";
            if (pos > length || pos < 0)throw ex.what();
            return *(tmp+pos);
        }

        const T &at(const size_t &pos) const {
            index_out_of_bound ex;

            //exception ex("", "index_out_of_bound");
            if (pos > length || pos < 0)throw ex.what();
            return *(tmp+pos);
        }

        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         * !!! Pay attentions
         *   In STL this operator does not check the boundary but I want you to do.
         */
        T &operator[](const size_t &pos) {
            index_out_of_bound ex;

            //exception ex("", "index_out_of_bound");
            if (pos > length || pos < 0)throw ex.what();
            return *(tmp+pos);
        }

        const T &operator[](const size_t &pos) const {
            index_out_of_bound ex;

            //exception ex("", "index_out_of_bound");
            if (pos > length || pos < 0)throw ex.what();
            return *(tmp+pos);
        }

        /**
         * access the first element.
         * throw container_is_empty if size == 0
         */
        const T &front() const {
            container_is_empty ex;
            //exception ex("", "container_is_empty");
            if(length<0){
                throw ex.what();
            }
            return *tmp;
        }

        /**
         * access the last element.
         * throw container_is_empty if size == 0
         */
        const T &back() const {
            container_is_empty ex;

            //exception ex("", "container_is_empty");
            if(length<0){
                throw ex.what();
            }
            return *(tmp+length);
        }

        /**
         * returns an iterator to the beginning.
         */
        iterator begin() {
            iterator it;
            it.num=0;
            it.vec=this;
            return it;
        }

        const_iterator cbegin() const {
            const_iterator it;
            it.num=0;
            it.vec=this;
            //it.point=it.head=&array[0];
            return it;
        }

        /**
         * returns an iterator to the end.
         */
        iterator end() {
            iterator it;
            it.num=length+1;
            it.vec=this;
            return it;
        }

        const_iterator cend() const {
            const_iterator it;
            it.vec=this;
            it.num=length+1;
            return it;
        }

        /**
         * checks whether the container is empty
         */
        bool empty() const {
            return length<0;
        }

        /**
         * returns the number of elements
         */
        size_t size() const {
            return length+1;
        }

        /**
         * clears the contents
         */
        void clear() {
            for(int i=0;i<=length;i++){
                alloc.destroy(tmp+i);
            }
            length=-1;
        }

        void double_size(){

            T*mid;T*temp;
            std::allocator<T>alloca;
            temp=alloca.allocate(capacity);
            for(int i=0;i<=length;i++){
                alloca. construct(temp+i,*(tmp+i));
                alloc. destroy(tmp+i);
                //mid[i]=array[i];
            }
            alloc.deallocate(tmp,capacity);
            capacity*=2;
            tmp=alloc.allocate(capacity);
            for(int i=0;i<=length;i++){
                alloc. construct(tmp+i,*(temp+i));
                alloca. destroy(temp+i);
            }
            alloca.deallocate(temp,capacity/2);
        }
        /**
         * inserts value before pos
         * returns an iterator pointing to the inserted value.
         */
        iterator insert(iterator pos, const T &value) {
            if(length+1<capacity-1){
                for(int i=length+1;i>pos.num;i--){
                    *(tmp+i)=*(tmp+i-1);
                }
                length++;
                *(tmp+pos.num)=value;
                return pos;
            }else{
                double_size();
                return insert(pos,value);
            }
        }
        /**
         * inserts value at index ind.
         * after inserting, this->at(ind) == value
         * returns an iterator pointing to the inserted value.
         * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
         */
        iterator insert(const size_t &ind, const T &value) {
            if(length+1<capacity-1){
                index_out_of_bound ex;
                //exception ex("","index_out_of_bound");
                if(ind>length+1){
                    throw ex.what();
                }else {
                    for(int i=length+1;i>ind;i--){
                        *(tmp+i)=*(tmp+i-1);
                    }
                    *(tmp+ind)=value;
                }
                iterator it;
                it.num=ind;
                it.vec=this;
//                it.head=&array[0];
//                it.point=&array[ind];
                return it;
            }else{
                double_size();
                return insert(ind,value);
            }
        }

        /**
         * removes the element at pos.
         * return an iterator pointing to the following element.
         * If the iterator pos refers the last element, the end() iterator is returned.
         */
        iterator erase(iterator pos) {
            for(int i=pos.num;i<length;i++){
                *(tmp+i)=*(tmp+i+1);
            }
            alloc. destroy(tmp+length);
            length--;
            return pos;
        }
        /**
         * removes the element with index ind.
         * return an iterator pointing to the following element.
         * throw index_out_of_bound if ind >= size
         */
        iterator erase(const size_t &ind) {
            iterator it;
            for(int i=ind;i<length;i++){
                *(tmp+i)=*(tmp+i+1);
            }
            alloc. destroy(tmp+length);
            length--;
//            it.head=&array[0];
//            it.point=&array[ind];
            it.num=ind;
            it.vec=this;
            return it;
        }

        /**
         * adds an element to the end.
         */
        void push_back(const T &value) {
            if(length+1<capacity-1){
                length++;
                alloc. construct(tmp+length,value);
                //array[++length]=value;
                return;
            }
            double_size();
            push_back(value);
        }

        /**
         * remove the last element from the end.
         * throw container_is_empty if size() == 0
         */
        void pop_back() {
            alloc. destroy(tmp+length);
            length--;
        }
    };


}

#endif
