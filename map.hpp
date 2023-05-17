/**
 * implement a container like std::map
 */
#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP
// only for std::less<T>
#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"
enum type{fals,right};

namespace sjtu {
    template<
            class Key,
            class T,
            class Compare = std::less<Key>
    >
    class map {
    public:
        /**
         * the internal type of data.
         * it should have a default constructor, a copy constructor.
         * You can use sjtu::map as value_type by typedef.
         */
        typedef pair<const Key, T> value_type;
//        struct my_true_type{
//            //todo
//            static const type t=right;
//        };
//        struct my_false_type{
//            //todo
//            static const type t=fals;
//
//        };
        /**
         * see BidirectionalIterator at CppReference for help.
         *
         * if there is anything wrong throw invalid_iterator.
         *     like it = map.begin(); --it;
         *       or it = map.end(); ++end();
         */
        struct Node {
            value_type data;
            int height = 0;
            Node *left = nullptr;
            Node *right = nullptr;
            Node *parent = nullptr;

            Node() {}

            Node(const value_type va) : data(va) {}

            Node(const Node *val) : data(val->data) {
                height = val->height;
            }
        };

        int siz = 0;
        Node *root = nullptr;

        class const_iterator;

        class iterator {
            /**
             * TODO add data members
             *   just add whatever you want.
             */
        public:
            //using iterator_assignable = my_true_type;
            const static type tp=right;
            Node *point = nullptr;
            bool end = 0;
            map<Key, T, Compare> *assist = nullptr;

            iterator() {}

            iterator(const iterator &other) {
                point = other.point;
                end = other.end;
                assist = other.assist;
            }

            /**
             * TODO iter++
             */
            iterator operator++(int) {
                if (end) {
                    invalid_iterator it;
                    throw it;
                }
                iterator it = *this;
                if (point->right) {
                    point = point->right;
                    while (point->left != nullptr)point = point->left;
                } else {
                    Node *now = point, *tmp = point->parent;
                    while (tmp != nullptr && now == tmp->right) {
                        tmp = tmp->parent;
                        now = now->parent;
                    }
                    if (tmp == nullptr)end = 1;
                    point = tmp;
                }
                return it;
            }

            /**
             * TODO ++iter
             */
            iterator &operator++() {
                if (end) {
                    invalid_iterator it;
                    throw it;
                }
                if (point->right) {
                    point = point->right;
                    while (point->left != nullptr)point = point->left;
                } else {
                    Node *now = point, *tmp = point->parent;
                    while (tmp != nullptr && now == tmp->right) {
                        tmp = tmp->parent;
                        now = now->parent;
                    }
                    if (tmp == nullptr)end = 1;
                    point = tmp;
                }
                return *this;
            }

            /**
             * TODO iter--
             */
            iterator operator--(int) {
                iterator it = *this;
                if (!end) {
                    if (point->left) {
                        point = point->left;
                        while (point->right != nullptr)point = point->right;
                    } else {
                        Node *now = point, *tmp = point->parent;
                        while (tmp != nullptr && now == tmp->left) {
                            tmp = tmp->parent;
                            now = now->parent;
                        }
                        point = tmp;
                    }
                } else {
                    Node *p = assist->root;
                    while (assist->root && p->right != nullptr) {
                        p = p->right;
                    }
                    point = p;
                    if (point)end = 0;
                }
                if (!point) {
                    *this = it;
                    invalid_iterator i;
                    throw i;
                }
                return it;
            }

            /**
             * TODO --iter
             */
            iterator &operator--() {
                iterator it(*this);
                if (!end) {
                    if (point->left) {
                        point = point->left;
                        while (point->right != nullptr)point = point->right;
                    } else {
                        Node *now = point, *tmp = point->parent;
                        while (tmp != nullptr && now == tmp->left) {
                            tmp = tmp->parent;
                            now = now->parent;
                        }
                        point = tmp;
                    }
                } else {
                    Node *p = assist->root;
                    while (assist->root && p->right != nullptr) {
                        p = p->right;
                    }
                    point = p;
                    if (point)end = 0;

                }
                if (!point) {
                    *this = it;
                    invalid_iterator i;
                    throw i;
                }
                return *this;
            }

            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            value_type &operator*() const {
                return point->data;
            }

            bool operator==(const iterator &rhs) const {
                return point == rhs.point && end == rhs.end && assist == rhs.assist;
            }

            bool operator==(const const_iterator &rhs) const {
                return point == rhs.point && end == rhs.end && assist == rhs.assist;
            }

            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return point != rhs.point || end != rhs.end || assist != rhs.assist;
            }

            bool operator!=(const const_iterator &rhs) const {
                return point != rhs.point || end != rhs.end || assist != rhs.assist;
            }

            /**
             * for the support of it->first.
             * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
             */
            value_type *operator->() const noexcept {
                return &(point->data);
            }
        };

        class const_iterator {
            // it should has similar member method as iterator.
            //  and it should be able to construct from an iterator.
            // data members.
        public:
            //using iterator_assignable = my_false_type;
            const static type tp=fals;
            const Node *point = nullptr;
            bool end = false;
            const map<Key, T, Compare> *assist = nullptr;

            const_iterator() {}

            const_iterator(const const_iterator &other) {
                point = other.point;
                end = other.end;
                assist = other.assist;
            }

            const_iterator(const iterator &other) {
                point = other.point;
                end = other.end;
            }

            const_iterator operator++(int) {
                if (end) {
                    invalid_iterator it;
                    throw it;
                }
                const_iterator it = *this;
                if (point->right) {
                    point = point->right;
                    while (point->left != nullptr)point = point->left;
                } else {
                    const Node *now = point, *tmp = point->parent;
                    while (tmp != nullptr && now == tmp->right) {
                        tmp = tmp->parent;
                        now = now->parent;
                    }
                    if (tmp == nullptr)end = 1;
                    point = tmp;
                }
                return it;
            }

            /**
             * TODO ++iter
             */
            const_iterator &operator++() {
                if (end) {
                    invalid_iterator it;
                    throw it;
                }
                if (point->right) {
                    point = point->right;
                    while (point->left != nullptr)point = point->left;
                } else {
                    const Node *now = point, *tmp = point->parent;
                    while (tmp != nullptr && now == tmp->right) {
                        tmp = tmp->parent;
                        now = now->parent;
                    }
                    if (tmp == nullptr)end = 1;
                    point = tmp;
                }
                return *this;
            }

            /**
             * TODO iter--
             */
            const_iterator operator--(int) {
                const_iterator it = *this;
                if (!end) {
                    if (point->left) {
                        point = point->left;
                        while (point->right != nullptr)point = point->right;

                    } else {
                        const Node *now = point;
                        const Node *tmp = point->parent;
                        while (tmp != nullptr && now == tmp->left) {
                            tmp = tmp->parent;
                            now = now->parent;
                        }
                        point = tmp;
                    }
                } else {
                    point = assist->root;
                    while (assist->root && point->right != nullptr) {
                        point = point->right;
                    }
                    if (point)end = 0;
                }
                if (!point) {
                    *this = it;
                    invalid_iterator i;
                    throw i;
                }
                return it;
            }

            /**
             * TODO --iter
             */
            const_iterator &operator--() {
                const_iterator it = *this;
                if (!end) {
                    if (point->left) {
                        point = point->left;
                        while (point->right != nullptr)point = point->right;
                    } else {
                        const Node *now = point, *tmp = point->parent;
                        while (tmp != nullptr && now == tmp->left) {
                            tmp = tmp->parent;
                            now = now->parent;
                        }
                        point = tmp;
                    }
                } else {
                    point = assist->root;
                    while (assist->root && point->right != nullptr) {
                        point = point->right;
                    }
                    if (point)end = 0;
                }
                if (point == nullptr) {
                    *this = it;
                    invalid_iterator i;
                    throw i;
                }
                return *this;
            }

            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            const value_type &operator*() const {

                return (point->data);
            }

            bool operator==(const iterator &rhs) const {
                return point == rhs.point && end == rhs.end && assist == rhs.assist;
            }

            bool operator==(const const_iterator &rhs) const {
                return point == rhs.point && end == rhs.end && assist == rhs.assist;
            }

            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return point != rhs.point || end != rhs.end || assist != rhs.assist;
            }

            bool operator!=(const const_iterator &rhs) const {
                return point != rhs.point || end != rhs.end || assist != rhs.assist;
            }

            /**
             * for the support of it->first.
             * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
             */
            const value_type *const operator->() const noexcept {
                if (point)return &(point->data);
            }
            // And other methods in iterator.
            // And other methods in iterator.
            // And other methods in iterator.
        };

        /**
         * TODO two constructors
         */
        map() {
            siz = 0;
            root = nullptr;
        }

        map(const map &other) {
            *this = other;
        }

        /**
         * TODO assignment operator
         */
        Node *copy(Node *node) {
            if (node == nullptr) {
                Node *t = nullptr;
                return t;
            }
            Node *tmp = new Node(node);
            tmp->left = copy(node->left);
            if (tmp->left)tmp->left->parent = tmp;
            tmp->right = copy(node->right);
            if (tmp->right)tmp->right->parent = tmp;
            return tmp;
        };

        map &operator=(const map &other) {
            if (root == other.root) {
                return *this;
            }
            clear(root);
            siz = other.siz;
            root = new Node(other.root);
            root->left = copy(other.root->left);
            if (root->left)root->left->parent = root;
            root->right = copy(other.root->right);
            if (root->right)root->right->parent = root;
            return *this;
        }

        void clear(Node *&node) {
            siz = 0;
            if (node == nullptr)return;
            clear(node->left);
            clear(node->right);
            delete node;
            node = nullptr;
        }

        /**
         * TODO Destructors
         */
        ~map() {
            clear(root);
        }

        /**
         * TODO
         * access specified element with bounds checking
         * Returns a reference to the mapped value of the element with key equivalent to key.
         * If no such element exists, an exception of type `index_out_of_bound'
         */
        T &at(const Key &key) {
            Compare cp;
            Node *tmp = root;
            index_out_of_bound ex;
            while (tmp != nullptr && (cp(key, tmp->data.first) || (cp(tmp->data.first, key)))) {
                while (tmp != nullptr && cp(key, tmp->data.first)) {
                    tmp = tmp->left;
                }
                while (tmp != nullptr && cp(tmp->data.first, key)) {
                    tmp = tmp->right;
                }
            }
            if (tmp == nullptr)throw ex;
            return tmp->data.second;
        }

        const T &at(const Key &key) const {
            Compare cp;
            Node *tmp = root;
            index_out_of_bound ex;
            while (tmp != nullptr && (cp(key, tmp->data.first) || (cp(tmp->data.first, key)))) {
                while (tmp != nullptr && cp(key, tmp->data.first)) {
                    tmp = tmp->left;
                }
                while (tmp != nullptr && cp(tmp->data.first, key)) {
                    tmp = tmp->right;
                }
            }

            if (tmp == nullptr)throw ex;
            return tmp->data.second;
        }////////
        /**
         * TODO
         * access specified element
         * Returns a reference to the value that is mapped to a key equivalent to key,
         *   performing an insertion if such key does not already exist.
         */
        T &operator[](const Key &key) {
            if (count(key)) {
                return at(key);
            }
            value_type val(key, T());
            Node *t = insert(val).first.point;
            return t->data.second;
        }

        /**
         * behave like at() throw index_out_of_bound if such key does not exist.
         */
        const T &operator[](const Key &key) const {
            return at(key);
        }

        /**
         * return a iterator to the beginning
         */
        iterator begin() {
            iterator it;
            it.assist = this;
            it.point = root;
            if (root == nullptr) {
                it.end = 1;
                return it;
            }
            while (it.point->left != nullptr) {
                it.point = it.point->left;
            }
            return it;
        }

        const_iterator cbegin() const {
            const_iterator it;
            it.assist = this;
            it.point = root;
            if (root == nullptr) {
                it.end = 1;
                return it;
            }
            while (it.point->left != nullptr) {
                it.point = it.point->left;
            }
            return it;
        }

        /**
         * return a iterator to the end
         * in fact, it returns past-the-end.
         */
        iterator end() {
            iterator it;
            it.point = nullptr;
            it.assist = this;
            it.end = 1;
            return it;
        }

        const_iterator cend() const {
            const_iterator it;
            it.point = nullptr;
            it.assist = this;
            it.end = 1;
            return it;
        }

        /**
         * checks whether the container is empty
         * return true if empty, otherwise false.
         */
        bool empty() const {
            return root == nullptr;
        }

        /**
         * returns the number of elements.
         */
        size_t size() const {
            return siz;
        }

        /**
         * clears the contents
         */
        void clear() {
            clear(root);
        }

        /**
   * insert an element.
   * return a pair, the first of the pair is
   *   the iterator to the new element (or the element that prevented the insertion),
   *   the second one is true if insert successfully, or false.
   */
        int height(Node *&node) {
            return node == nullptr ? (-1) : node->height;
        }

        void _insert(const value_type &value, Node *&node, Node *&father, int dir, bool &f) {
            Compare cp;
            if (node == nullptr) {
                node = new Node(value);
                if (dir == 1) {
                    father->left = node;
                } else if (dir == 2) {
                    father->right = node;
                }
                node->parent = father;
            } else if (cp(value.first, node->data.first)) {
                _insert(value, node->left, node, 1, f);
                if (height(node->left) - height(node->right) == 2) {
                    if (cp(value.first, node->left->data.first))LL(node);
                    else {
                        RR(node->left);
                        LL(node);
                    }
                }
            } else if (cp(node->data.first, value.first)) {///////////////////////////////////////////////
                _insert(value, node->right, node, 2, f);
                if (height(node->right) - height(node->left) == 2) {
                    if (cp(node->right->data.first, value.first)) {
                        RR(node);
                    } else {
                        LL(node->right);
                        RR(node);
                    }
                }
            } else if (!(cp(value.first, node->data.first) || cp(node->data.first, value.first))) {
                f = false;
            }
            node->height = max(height(node->left), height(node->right)) + 1;
        }

        int max(const int &a, const int &b) {
            return a >= b ? a : b;
        }

        pair<iterator, bool> insert(const value_type &value) {
            //iterator it;
            pair<iterator, bool> pa;
            Node *tmp = nullptr;
            bool flag = 1;
            _insert(value, root, tmp, 0, flag);
            pa.second = flag;
            //std::cout<<root->data.second<<std::endl;
            pa.first = find(value.first);
            if (pa.second) {
                siz++;
                //pa.second = 1;
            }
            //it.end = (it.point == nullptr ? 1 : 0);
            return pa;
        }

        void LL(Node *node) {
            Node *tp = node->left;
            node->left = tp->right;
            if (tp->right)tp->right->parent = node;
            if (node->parent != nullptr) {
                if (node == node->parent->left)node->parent->left = tp;
                else node->parent->right = tp;
            }
            tp->parent = node->parent;
            node->parent = tp;
            tp->right = node;
            if (tp->parent == nullptr)root = tp;
            node->height = max(height(node->left), height(node->right)) + 1;
            tp->height = max(height(tp->left), height(tp->right)) + 1;
        }

        void RR(Node *node) {
            Node *tp = node->right;
            node->right = tp->left;
            if (tp->left)tp->left->parent = node;
            if (node->parent != nullptr) {
                if (node == node->parent->left)node->parent->left = tp;
                else node->parent->right = tp;
            }
            tp->parent = node->parent;
            node->parent = tp;
            tp->left = node;
            if (tp->parent == nullptr)root = tp;
            node->height = max(height(node->left), height(node->right)) + 1;
            tp->height = max(height(tp->left), height(tp->right)) + 1;
        }

        /**
         * erase the element at pos.
         *
         * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
         */
        void erase(iterator pos) {
            invalid_iterator i;
            Compare cp;
            if (pos.assist != this || pos.end || !pos.point)throw i;
            Key key = pos.point->data.first;
            if (count(key) == 0)throw i;
            siz--;
            remove(root, key);
        }

        void del(Node *node) {
            bool flag = 0;
            Node *tmp = node->parent;
            if (node == root) {
                Node *tp = root;
                if (node->right) {
                    node->right->parent = nullptr;
                    root = root->right;
                    root->left = nullptr;
                } else if (node->left) {
                    node->left->parent = nullptr;
                    root = root->left;
                    root->left = nullptr;
                } else flag = 1;
                delete tp;
                tp = nullptr;
                if (flag)root = nullptr;
                return;
            }
            if (tmp && tmp->left == node) {
                if (node->right) {
                    node->right->parent = tmp;
                    tmp->left = node->right;
                } else if (node->left) {
                    node->left->parent = tmp;
                    tmp->left = node->left;
                } else tmp->left = nullptr;
            } else if (tmp && tmp->right == node) {
                if (node->right) {
                    node->right->parent = tmp;
                    tmp->right = node->right;
                } else if (node->left) {
                    node->left->parent = tmp;
                    tmp->right = node->left;
                } else {
                    tmp->right = nullptr;
                }
            }
            delete node;
            node = nullptr;
        }

        void swap(Node *tmp, Node *tm) {
            if (tmp == root) root = tm;
            if (tm == tmp->right) {
                tmp->right = tm->right;
                if (tm->right)tm->right->parent = tmp;
                tm->left = tmp->left;
                tmp->left->parent = tm;
                tmp->left = nullptr;
                tm->parent = tmp->parent;
                tm->right = tmp;
                if (tmp->parent) {
                    if (tmp->parent->left == tmp)tmp->parent->left = tm;
                    else tmp->parent->right = tm;
                }
                tmp->parent = tm;
            } else {
                Node *t = tmp->right;
                tmp->right = tm->right;
                if (tm->right)tm->right->parent = tm;
                t->parent = tm;
                tm->right = t;
                tm->left = tmp->left;
                tmp->left->parent = tm;
                tmp->left = nullptr;
                tm->parent->left = tmp;
                if (tmp->parent) {
                    if (tmp->parent->left == tmp)tmp->parent->left = tm;
                    else tmp->parent->right = tm;
                }
                Node *p = tm->parent;
                tm->parent = tmp->parent;
                tmp->parent = p;
            }
            int h = tm->height;
            tm->height = tmp->height;
            tmp->height = h;
        }

        bool remove(Node *&tmp, const Key &key) {
            Compare cp;
            if (tmp == nullptr) {
                return true;
            }
            if (!(cp(key, tmp->data.first) || (cp(tmp->data.first, key)))) {
                if (tmp->right == nullptr || tmp->left == nullptr) {
                    del(tmp);
                    return false;
                } else {//两个儿子
                    Node *tm = tmp->right;
                    while (tm->left != nullptr) {
                        tm = tm->left;
                    }
                    swap(tmp, tm);
                    if (remove(tm->right, key))return true;
                    return change(tm, 1);
                }
            }
            if (cp(key, tmp->data.first)) {
                if (remove(tmp->left, key))return true;

                return change(tmp, 0);

            }
            if (cp(tmp->data.first, key)) {
                if (remove(tmp->right, key))return true;

                return change(tmp, 1);
            }
        }

        bool change(Node *tmp, bool dir) {
            if (tmp) {
                if (dir) {//右边变短
                    if ((height(tmp->left) - height(tmp->right) == 1)) {
                        return true;
                    }
                    if (height(tmp->left) == height(tmp->right)) {
                        tmp->height--;
                        return false;
                    }
                    if (tmp->left && height(tmp->left->right) > height(tmp->left->left)) {
                        RR(tmp->left);
                        LL(tmp);
                        return false;
                    }
                    LL(tmp);
                } else {//左边变短
                    if (height(tmp->left) - height(tmp->right) == -1) {
                        return true;
                    }
                    if (height(tmp->left) == height(tmp->right)) {
                        tmp->height--;
                        return false;
                    }
                    if (tmp->right && height(tmp->right->left) > height(tmp->right->right)) {
                        LL(tmp->right);
                        RR(tmp);
                        return false;
                    }
                    RR(tmp);
                }
                if (height(tmp->right) == height(tmp->left))return false;
                return true;
            }
            return true;
        }

        /**
         * Returns the number of elements with key
         *   that compares equivalent to the specified argument,
         *   which is either 1 or 0
         *     since this container does not allow duplicates.
         * The default method of check the equivalence is !(a < b || b > a)
         */
        size_t count(const Key &key) const {
            Node *tmp = root;
            Compare cp;
            while (tmp != nullptr && (cp(key, tmp->data.first) || (cp(tmp->data.first, key)))) {
                while (tmp != nullptr && cp(key, tmp->data.first)) {
                    tmp = tmp->left;
                }
                while (tmp != nullptr && cp(tmp->data.first, key)) {
                    tmp = tmp->right;
                }
            }
            if (tmp == nullptr) {
                return 0;
            }
            return 1;
        }

        /**
         * Finds an element with key equivalent to key.
         * key value of the element to search for.
         * Iterator to an element with key equivalent to key.
         *   If no such element is found, past-the-end (see end()) iterator is returned.
         */
        iterator find(const Key &key) {
            iterator it;
            Compare cp;
            it.point = root;
            it.assist = this;
            while (it.point != nullptr && (cp(key, it.point->data.first) || cp(it.point->data.first, key))) {
                while (it.point != nullptr && cp(key, it.point->data.first)) {
                    it.point = it.point->left;
                }
                while (it.point != nullptr && cp(it.point->data.first, key)) {
                    it.point = it.point->right;
                }
            }
            if (it.point == nullptr) {
                it.end = 1;
            }
            return it;
        }

        const_iterator find(const Key &key) const {
            Compare cp;
            const_iterator it;
            it.point = root;
            it.assist = this;
            while (it.point != nullptr && (cp(key, it.point->data.first) || cp(it.point->data.first, key))) {
                while (it.point != nullptr && cp(key, it.point->data.first)) {
                    it.point = it.point->left;
                }
                while (it.point != nullptr && cp(it.point->data.first, key)) {
                    it.point = it.point->right;
                }
            }
            if (it.point == nullptr) it.end = 1;
            return it;
        }
    };
    template<typename T>
    struct my_type_traits{
        const static bool value=T::tp==right?1:0;
        //using iterator_assignable = typename T::iterator_assignable;
    };

}
#endif
