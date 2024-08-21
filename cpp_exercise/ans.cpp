#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cassert>

using namespace std;

class polynomialList {
private:
    struct term {
        double cof; // coefficient
        int deg; // degree
        term *next;
        term() : cof(0), deg(0), next(nullptr) {} // default constructor, 构造函数
        term(double c, int d) : cof(c), deg(d), next(nullptr) {}
        term(double c, int d, term *nex) : cof(c), deg(d), next(nex) {}
    };
    term *head;
public:
    polynomialList() : head(nullptr) {}
    polynomialList(const polynomialList &other) : head(nullptr) {
        term *p = other.head;
        while (p != nullptr) {
            add_one_term(p->cof, p->deg);
            p = p->next;
        }
    }
    polynomialList &operator=(const polynomialList &); // overload = operator
    polynomialList operator+(const polynomialList &) const; // overload + operator
    polynomialList operator-(const polynomialList &) const; // overload - operator
    polynomialList operator*(const polynomialList &) const; // overload * operator
    void print() const;
    void read_from_file(const string &filename);
    void compress();
    void add_one_term(double, int);
};

polynomialList polynomialList::operator+(const polynomialList &rhs) const {
    polynomialList res = *this;
    term *q = rhs.head;
    while (q != nullptr) {
        res.add_one_term(q->cof, q->deg);
        q = q->next;
    }
    res.compress();
    return res;
}

polynomialList polynomialList::operator-(const polynomialList &rhs) const {
    polynomialList res = *this;
    term *q = rhs.head;
    while (q != nullptr) {
        res.add_one_term(-q->cof, q->deg);
        q = q->next;
    }
    res.compress();
    return res;
}

polynomialList polynomialList::operator*(const polynomialList &rhs) const {
    polynomialList res;
    term *p = head;
    while (p != nullptr) {
        term *q = rhs.head;
        while (q != nullptr) {
            res.add_one_term(p->cof*q->cof, p->deg+q->deg);
            q = q->next;
        }
        p = p->next;
    }
    res.compress();
    return res;
}

polynomialList &polynomialList::operator=(const polynomialList &rhs) {
    if (this == &rhs) {
        return *this;
    }
    term *p = head;
    while (p != nullptr) {
        term *q = p->next;
        delete p;
        p = q;
    }
    head = nullptr;
    term *q = rhs.head;
    while (q != nullptr) {
        this->add_one_term(q->cof, q->deg);
        q = q->next;
    }
    return *this;
}

void polynomialList::read_from_file(const string &filename) {
    ifstream fin(filename, ios::in);
    assert(fin);
    int n;
    fin >> n;
    for (int i = 0; i < n; i++) {
        int deg;
        double cof;
        fin >> cof >> deg;
        add_one_term(cof, deg);
    }
    fin.close();
    compress();
}

void polynomialList::compress() {
    if (!head) return ;
    term *prev = new term(0, 0, head);
    term *q = prev;
    term *p = head;
    while (p != nullptr) {
        if (fabs(p->cof) < 1.0e-6) {
            prev->next = p->next;
            delete p;
            p = prev->next;
        } else {
            prev = p;
            p = p->next;
        }
    }
    head = q->next;
    delete q;
}

void polynomialList::print() const {
    term *p = head;
    if (p == nullptr) {
        cout << 0 << endl;
        return ;
    }
    if (p->cof < 0) {
        cout << "-";
    }
    while (p != nullptr) {
        if (p->deg == 0) {
            cout << fabs(p->cof) << endl;
            return ;
        }
        if (fabs(fabs(p->cof)-1.0) > 1.0e-6) {
            cout << fabs(p->cof);
        }
        cout << "x";
        if (p->deg != 1) cout << "^" << p->deg;
        if ((p=p->next) != nullptr) {
            if (p->cof > 0) {
                cout << " + ";
            } else {
                cout << " - ";
            }
        }
    }
    cout << endl;
}

void polynomialList::add_one_term(double cof, int deg) {
    if (head == nullptr) {
        head = new term(cof, deg);
        return;
    }
    term *p = head;
    term *prev = new term(0, 0, head);
    term *q = prev;
    while (p != nullptr) {
        if (p->deg <= deg) {
            break;
        }
        prev = p;
        p = p->next;
    }
    if (p == nullptr) {
        prev->next = new term(cof, deg);
    }
    else if (p->deg == deg) {
        p->cof += cof;
    } else {
        prev->next = new term(cof, deg, p);
    }
    delete q;
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