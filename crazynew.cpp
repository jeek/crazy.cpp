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
    long long left;
    long long right;
    bool operator <(const record& rhs) const {
        if (result != rhs.result) {
            return result < rhs.result;
        }
        if (lower != rhs.lower) {
            return lower < rhs.lower;
        }
        return upper < rhs.upper;
    }
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
    };
    bool operator ==(const seenitem& rhs) const {
        if (result != rhs.result) {
            return false;
        }
        if (lower != rhs.lower) {
            return false;
        }
        if (upper != rhs.upper) {
            return false;
        }
        return true;
    };
};

long long concatenate(long long y, long long x) {
    long long pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;        
}

std::string display(std::vector< record> &queue, long long i) {
    if (queue[i].oper == 'E') {
        return std::to_string(queue[i].result);
    }
    if (queue[i].oper == '+') {
        return "(" + display(queue, queue[i].right) + " + " + display(queue, queue[i].left) + ")";
    }
    if (queue[i].oper == '*') {
        return "(" + display(queue, queue[i].right) + " * " + display(queue, queue[i].left) + ")";
    }
    if (queue[i].oper == '^') {
        return "(" + display(queue, queue[i].right) + " ^ " + display(queue, queue[i].left) + ")";
    }
    return "Error";
}

int main(int argc, char *argv[]) {
    std::vector< record > queue;
    std::vector< std::set< long long > > leftq;
    std::vector< std::set< long long > > rightq;
    std::set<seenitem> seen;
    int base = 10; char *endptr;
    leftq.push_back(std::set<long long>());
    rightq.push_back(std::set<long long>());
    leftq.push_back(std::set<long long>());
    rightq.push_back(std::set<long long>());
    for (int i = 1 ; i < argc; i++) {
        leftq.push_back(std::set<long long>());
        rightq.push_back(std::set<long long>());
        record temp;
        (temp).left = -1;
        (temp).right = -1;
        (temp).oper = 'E';
        (temp).result = strtoll(argv[i], &endptr, base);
        (temp).lower = i;
        (temp).upper = i;
        seen.insert(seenitem({temp.result, temp.lower, temp.upper}));
        queue.push_back(temp);
        leftq[i].insert(queue.size()-1);
        rightq[i].insert(queue.size()-1);
//        std::cout << temp.result << std::endl;
    }
#ifdef CONCATENATION
    for (int i = 0 ; i < queue.size() ; i++) {
       for (int j = 0 ; j < queue.size() ; j++) {
           if ((queue[i].upper + 1) == (queue[j].lower)) {
               if ((queue[i].lower != 1 | queue[j].upper != (argc-1)) & seen.count(seenitem{concatenate(queue[j].result, queue[i].result), queue[i].lower, queue[j].upper}) == 0) {
//                   std::cout << concatenate(queue[j].result, queue[i].result) << " " << queue[i].lower << " " << queue[j].upper << " "  << std::endl;
                   seen.insert(seenitem({concatenate(queue[j].result, queue[i].result), queue[i].lower, queue[j].upper}));
                   queue.push_back(record({queue[i].lower, queue[j].upper, concatenate(queue[j].result, queue[i].result), 'E', j, i}));
                   leftq[queue[i].lower].insert(queue.size()-1);
                   rightq[queue[j].upper].insert(queue.size()-1);
               }
           }
       }
    }
#endif /* CONCATENATION */
    for (int i = 0 ; i < queue.size() ; i++) {
        std::cout << queue.size() << " " << i << " " << queue[i].result << " " << queue[i].lower << " " << queue[i].upper << std::endl;
        if ((queue[i].lower == 1) & (queue[i].upper == (argc - 1)) & (queue[i].result < UPPERLIMIT)) {
            std::cout << queue[i].result << " " << display(queue, i) << std::endl;
        }
        //for (int j = 0 ; j < queue.size() ; j++) {
        for (std::set<long long>::iterator it = leftq[queue[i+1].upper].begin() ; it != (leftq[queue[i+1].upper]).end(); ++it) {
           long long j = *it;
           std::cout << "    " << j << " " << queue[j].result << " " << queue[j].lower << " " << queue[j].upper << std::endl;
//           if ((queue[i].upper + 1) == (queue[j].lower)) {
#ifdef ADDITION
               if (seen.count(seenitem{queue[i].result + queue[j].result, queue[i].lower, queue[j].upper}) < 5) {
//                   std::cout << (queue[j].result + queue[i].result) << " " << queue[j].upper << " " << queue[i].lower << std::endl;
                   seen.insert(seenitem({(queue[i].result + queue[j].result), queue[i].lower, queue[j].upper}));
                   queue.push_back(record({queue[i].lower, queue[j].upper, (queue[j].result + queue[i].result), '+', j, i}));
                   leftq[queue[i].lower].insert(queue.size()-1);
                   rightq[queue[j].upper].insert(queue.size()-1);
               }
#endif /* ADDITION */
#ifdef MULTIPLICATION
               if (seen.count(seenitem{queue[i].result * queue[j].result, queue[i].lower, queue[j].upper}) < 5) {
//                   std::cout << (queue[j].result + queue[i].result) << " " << queue[j].upper << " " << queue[i].lower << std::endl;
                   seen.insert(seenitem({(queue[i].result * queue[j].result), queue[i].lower, queue[j].upper}));
                   queue.push_back(record({queue[i].lower, queue[j].upper, (queue[j].result * queue[i].result), '*', j, i}));
                   leftq[queue[i].lower].insert(queue.size()-1);
                   rightq[queue[j].upper].insert(queue.size()-1);
               }
#endif /* MULTIPLICATION */
#ifdef EXPONENTS
//               if (seen.count(seenitem{pow(queue[j].result, queue[i].result), queue[i].lower, queue[j].upper}) == 0) {
//                 if (queue[i].result * log10(queue[j].result) < log10(UPPERLIMIT)) {
//                   std::cout << (queue[j].result * queue[i].result) << " " << queue[j].upper << " " << queue[i].lower << std::endl;
//                   seen.insert(seenitem({pow(queue[j].result, queue[i].result), queue[i].lower, queue[j].upper}));
//                   queue.push_back(record({queue[i].lower, queue[j].upper, pow(queue[j].result, queue[i].result), '^', j, i}));
//                   leftq[queue[i].lower].insert(i);
//                   rightq[queue[j].upper].insert(j);
//                 }
//               }
#endif /* EXPONENTS */
//           }            
        }
    }
}
