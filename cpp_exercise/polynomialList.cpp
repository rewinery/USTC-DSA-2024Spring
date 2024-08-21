#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

class polynomialList {
private:
    struct term {
        double cof; // coefficient
        int deg; // degree
        term *next;
        term() : cof(0), deg(0), next(nullptr) {} // default constructor, 构造函数
        term(double c, int d) : cof(c), deg(d), next(nullptr) {}
        term(double c, int d, term *n) : cof(c), deg(d), next(n) {}
    };
    term *head;
public:
    polynomialList() : head(nullptr) {}
    polynomialList(const polynomialList &);
    polynomialList operator+(const polynomialList &) const; // overload + operator
    polynomialList operator-(const polynomialList &) const; // overload - operator
    polynomialList operator*(const polynomialList &) const; // overload * operator
    polynomialList &operator=(const polynomialList &);      // overload = operator
    void print() const;
    void read_from_file(const string filename);
    void compress();
    void add_one_term(double, int);
};

polynomialList::polynomialList(const polynomialList &other) {
    // TODO: copy constructor
}

polynomialList polynomialList::operator+(const polynomialList &rhs) const {
    // TODO: overload + operator
}

polynomialList polynomialList::operator-(const polynomialList &rhs) const {
    // TODO: overload - operator
}

polynomialList polynomialList::operator*(const polynomialList &rhs) const {
    // TODO: overload * operator
}

polynomialList &polynomialList::operator=(const polynomialList &rhs) {
    // TODO: overload = operator
}

void polynomialList::read_from_file(const string filename) {
    // TODO: read polynomial from file
}

void polynomialList::compress() { // compress the polynomial list
    term *p = head;
    while (p != nullptr) {
        term *q = p->next;
        if (fabs(p->cof) < 1.0e-6) { // 浮点误差
            delete p;
            p = q;
        } else {
            p = q;
        }
    }
}

void polynomialList::print() const {
    // TODO: print the polynomial list from the biggest degree to the smallest degree, which means you should order the list in an ordered way while constructing it
}

void polynomialList::add_one_term(double cof, int deg) {
    // TODO: add one term to the polynomial list
}

int main() {
    polynomialList p1, p2, p3;
    p1.read_from_file("./data/p1.txt");
    p1.print();
    p2.read_from_file("./data/p2.txt");
    p2.print();
    p3 = p1;
    p3.print();
    p3 = p1 + p2;
    p3.print();
    p3 = p1 - p2;
    p3.print();
    p3 = p1 * p2;
    p3.print();
    return 0;
}