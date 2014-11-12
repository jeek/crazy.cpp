#include <cmath>
#include <set>
#include <cstdio>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>

struct record {
    int lower;
    int upper;
    long long result;
    char oper;
    record *left;
    record *right;
};

struct seenitem {
    long long result;
    int lower;
    int upper;
    bool operator <(const seenitem& rhs) const {
        if (result != rhs.result) {
            return result < rhs.result;
        }
        if (lower != rhs.lower) {
            return lower < rhs.lower;
        }
        return upper < rhs.upper;
    }
};


long long concatenate(long long x, long long y) {
    long long pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;        
}
                    

void cprocess(record *left, record *right, std::vector< record* > &queue, std::vector< record* > &records, std::set<seenitem> &seen) {
    if ((*left).result == 0) {
        return;
    }
    char *endptr; int base = 10;
    record *temp; int i; bool good;
    // Concatenation
    temp = new record();
    (*temp).left = left;
    (*temp).right = right;
    (*temp).oper = 'E';
    (*temp).lower = (*left).lower;
    (*temp).upper = (*right).upper;
    (*temp).result = concatenate((*left).result, (*right).result);
    if (seen.count(seenitem({(*temp).result, (*temp).lower, (*temp).upper})) == 0) {
        queue.push_back(temp);
        records.push_back(temp);
        seen.insert(seenitem({(*temp).result, (*temp).lower, (*temp).upper}));
    }
}

void oprocess(record *left, std::vector< record* > &queue, std::vector< record* > &records, std::set<seenitem> &seen) {

    char *endptr; int base = 10;
    record *temp; int i; bool good;
    // Sqrt
    if ((*left).result > 1) {
        int root = round(sqrt((*left).result));
        if (root * root == (*left).result) {
            temp = new record();
            (*temp).left = left;
            (*temp).right = left;
            (*temp).oper = 'S';
            (*temp).lower = (*left).lower;
            (*temp).upper = (*left).upper;
            (*temp).result = root;
            if (seen.count(seenitem({(*temp).result, (*temp).lower, (*temp).upper})) == 0) {
                queue.push_back(temp);
                records.push_back(temp);
                seen.insert(seenitem({(*temp).result, (*temp).lower, (*temp).upper}));
            }
        }
        if ((root + 1) * (root + 1) == (*left).result) {
            temp = new record();
            (*temp).left = left;
            (*temp).right = left;
            (*temp).oper = 'S';
            (*temp).lower = (*left).lower;
            (*temp).upper = (*left).upper;
            (*temp).result = root + 1;
            if (seen.count(seenitem({(*temp).result, (*temp).lower, (*temp).upper})) == 0) {
                queue.push_back(temp);
                records.push_back(temp);
                seen.insert(seenitem({(*temp).result, (*temp).lower, (*temp).upper}));
            }
        }
    }

    // Unitary Negation
    if ((*left).oper != 'N') {
        temp = new record();
        (*temp).left = left;
        (*temp).right = left;
        (*temp).oper = 'N';
        (*temp).lower = (*left).lower;
        (*temp).upper = (*left).upper;
        (*temp).result = -(*left).result;
        if (seen.count(seenitem({(*temp).result, (*temp).lower, (*temp).upper})) == 0) {
            queue.push_back(temp);
            records.push_back(temp);
            seen.insert(seenitem({(*temp).result, (*temp).lower, (*temp).upper}));
        }
    }

    // Factorial
    if ((*left).result == 0 | (*left).result > 2) {
        long long temp3 = 1;
        long long temp2 = (*left).result;
        while (temp2 > 1 and temp3 < UPPERLIMIT) {
            temp3 *= temp2;
            temp2 -= 1;
        }
        if (temp2 == 1) {
            temp = new record();
            (*temp).left = left;
            (*temp).right = left;
            (*temp).oper = 'F';
            (*temp).lower = (*left).lower;
            (*temp).upper = (*left).upper;
            (*temp).result = temp3;
            if (seen.count(seenitem({(*temp).result, (*temp).lower, (*temp).upper})) == 0) {
                queue.push_back(temp);
                records.push_back(temp);
                seen.insert(seenitem({(*temp).result, (*temp).lower, (*temp).upper}));
            }
        }
    }
}

void process(record *left, record *right, std::vector< record* > &queue, std::vector< record* > &records, std::set<seenitem> &seen) {
    record *temp; int i; bool good;
    // Addition
    temp = new record();
    (*temp).left = left;
    (*temp).right = right;
    (*temp).oper = '+';
    (*temp).lower = (*left).lower;
    (*temp).upper = (*right).upper;
    (*temp).result = (*left).result + (*right).result;
    if (seen.count(seenitem({(*temp).result, (*temp).lower, (*temp).upper})) == 0) {
        queue.push_back(temp);
        records.push_back(temp);
        seen.insert(seenitem({(*temp).result, (*temp).lower, (*temp).upper}));
    }
    // Multiplication
    if (abs((*left).result) * abs((*right).result) < UPPERLIMIT) {
        temp = new record();
        (*temp).left = left;
        (*temp).right = right;
        (*temp).oper = '*';
        (*temp).lower = (*left).lower;
        (*temp).upper = (*right).upper;
        (*temp).result = (*left).result * (*right).result;
        if (seen.count(seenitem({(*temp).result, (*temp).lower, (*temp).upper})) == 0) {
            queue.push_back(temp);
            records.push_back(temp);
            seen.insert(seenitem({(*temp).result, (*temp).lower, (*temp).upper}));
        }
    }
    // Subtraction
    temp = new record();
    (*temp).left = left;
    (*temp).right = right;
    (*temp).oper = '-';
    (*temp).lower = (*left).lower;
    (*temp).upper = (*right).upper;
    (*temp).result = (*left).result - (*right).result;
    if (seen.count(seenitem({(*temp).result, (*temp).lower, (*temp).upper})) == 0) {
        queue.push_back(temp);
        records.push_back(temp);
        seen.insert(seenitem({(*temp).result, (*temp).lower, (*temp).upper}));
    }
    // Division
    if (((*right).result != 0)) {
      if (((*left).result) % ((*right).result) == 0) {
        temp = new record();
        (*temp).left = left;
        (*temp).right = right;
        (*temp).oper = '/';
        (*temp).lower = (*left).lower;
        (*temp).upper = (*right).upper;
        (*temp).result = (*left).result - (*right).result;
        if (seen.count(seenitem({(*temp).result, (*temp).lower, (*temp).upper})) == 0) {
            queue.push_back(temp);
            records.push_back(temp);
            seen.insert(seenitem({(*temp).result, (*temp).lower, (*temp).upper}));
        }
      }
    }
    // Exponents
    if ((*right).result >= 0) {
      if ((*right).result * log10((*left).result) < log10(UPPERLIMIT)) {
        temp = new record();
        (*temp).left = left;
        (*temp).right = right;
        (*temp).oper = '^';
        (*temp).lower = (*left).lower;
        (*temp).upper = (*right).upper;
        (*temp).result = pow((*left).result, (*right).result);
        if (seen.count(seenitem({(*temp).result, (*temp).lower, (*temp).upper})) == 0) {
            queue.push_back(temp);
            records.push_back(temp);
            seen.insert(seenitem({(*temp).result, (*temp).lower, (*temp).upper}));
        }
      }
    }
}

std::string display(record *current) {
    std::string result = "";
    if ((*current).oper == 'E') {
        return std::to_string((*current).result);
    }
    if ((*current).oper == '+') {
        return "(" + display((*current).left) + " + " + display((*current).right) + ")";
    }
    if ((*current).oper == '*') {
        return "(" + display((*current).left) + " * " + display((*current).right) + ")";
    }
    if ((*current).oper == '-') {
        return "(" + display((*current).left) + " - " + display((*current).right) + ")";
    }
    if ((*current).oper == '/') {
        return "(" + display((*current).left) + " / " + display((*current).right) + ")";
    }
    if ((*current).oper == '^') {
        return "(" + display((*current).left) + " ^ " + display((*current).right) + ")";
    }
    if ((*current).oper == 'S') {
        return "sqrt(" + display((*current).left) + ")";
    }
    if ((*current).oper == 'F') {
        return "(" + display((*current).left) + ")!";
    }
    if ((*current).oper == 'N') {
        return "-" + display((*current).left);
    }
    return "Error";
}


int main(int argc, char *argv[]) {
    
    char *endptr; int base = 10;
    std::set<seenitem> seen;
    std::vector< record* > records;
    std::vector< record* > queue;
    std::vector< std::vector< record > > leftq;
    std::vector< std::vector< record > > rightq;
    leftq.push_back(std::vector<record>());
    rightq.push_back(std::vector<record>());
    leftq.push_back(std::vector<record>());
    rightq.push_back(std::vector<record>());
    for (int i = 1 ; i < argc; i++) {
        leftq.push_back(std::vector<record>());
        rightq.push_back(std::vector<record>());
        record *temp = new record();
        (*temp).left = 0;
        (*temp).right = 0;
        (*temp).oper = 'E';
        (*temp).result = strtoll(argv[i], &endptr, base);
        (*temp).lower = i;
        (*temp).upper = i;
        records.push_back(temp);
        queue.push_back(temp);
        leftq[i].push_back(*temp);
        rightq[i].push_back(*temp);
    }
    for (int i = 0 ; i < queue.size() ; i++) {
        record *current = queue[i];
        for (std::vector< record >::iterator queueiterator = (leftq[(*current).lower - 1]).begin() ; queueiterator < (leftq[(*current).lower - 1]).end() ; queueiterator++) {
            record *other = &(*queueiterator);
            if ((*other).lower != 1 | (*current).upper != (argc - 1)) {
                cprocess(other, current, queue, records, seen);
            }
        }
    }
    for (int i = 0 ; i < queue.size() ; i++) {
        record *current = queue[i];
        for (std::vector< record >::iterator queueiterator = (rightq[(*current).upper + 1]).begin() ; queueiterator < (rightq[(*current).upper + 1]).end() ; queueiterator++) {
            record *other = &(*queueiterator);
            if ((*current).lower != 1 | (*other).upper != (argc - 1)) {
                cprocess(current, other, queue, records, seen);
            }
        }
    }
    for (int i = 0 ; i < queue.size(); i++) {
        record *temp = queue[i];
    }
    while (!queue.empty()) {
        record *current = queue[queue.size() - 1];
        queue.pop_back();
        oprocess(current, queue, records, seen);
        for (std::vector< record >::iterator queueiterator = (leftq[(*current).lower - 1]).begin() ; queueiterator < (leftq[(*current).lower - 1]).end() ; queueiterator++) {
            record *other = &(*queueiterator);
            process(other, current, queue, records, seen);
        }
        for (std::vector< record >::iterator queueiterator = (rightq[(*current).upper + 1]).begin() ; queueiterator < (rightq[(*current).upper + 1]).end() ; queueiterator++) {
            record *other = &(*queueiterator);
            process(current, other, queue, records, seen);
        }
    }
    for (std::vector< record* >::iterator queueiterator = records.begin() ; queueiterator < records.end() ; queueiterator++) {
        if ((*(*queueiterator)).lower == 1 & (*(*queueiterator)).upper == argc - 1) {
            std::cout << (*(*queueiterator)).result << " " << display(*queueiterator) << std::endl;
        }
    }
    return 0;
}
