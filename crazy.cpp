#include <set>       // std::set
#include <algorithm> // std::sort
#include <iostream>  // std::cout
#include <vector>    // std::vector
#include <queue>     // std::priority_queue
#include <math.h>    // pow
#include <sstream>
#include <stdlib.h>

#define UPPERLIMIT 1000
#define ADDITION
#define SUBTRACTION
#define MULTIPLICATION
#define DIVISION
#define EXPONENTS
#define CONCATENATION
#define DISCARDDUPES
#define SHOWNEGATIVES
#define SQUAREROOT
//#define DEBUG

#ifdef SQUAREROOT
bool is_perfect_square(int n) {
    if (n <= 1) // in this program, we don't care about 0 or 1
        return false;
    int root(round(sqrt(n)));
    return (n == root * root) | (n == (root + 1) * (root + 1));
}
#endif /* SQUAREROOT */

struct queueelement {
    std::vector< long long > elements;
    std::vector<std::string> strings;
    bool operator<(const queueelement& rhs) const
    {
        if (elements.size() != rhs.elements.size()) {
            return elements.size() < rhs.elements.size();
        }
        for (int i = 0 ; i < elements.size() ; i++) {
            if (abs(elements[i]) != abs(rhs.elements[i])) {
                return abs(elements[i]) > abs(rhs.elements[i]);
            }
        }
        for (int i = 0 ; i < elements.size() ; i++) {
            if (elements[i] != rhs.elements[i]) {
                return elements[i] > rhs.elements[i];
            }
        }
        size_t a = 0; size_t b = 0;
        for (int i = 0 ; i < strings.size() ; i++) {
            a += std::count(strings[i].begin(), strings[i].end(), '-');
            b += std::count(rhs.strings[i].begin(), rhs.strings[i].end(), '-');
        }
        if (a != b)
            return a < b;
        return elements[0] < rhs.elements[0];
    }
    bool operator==(const queueelement& rhs) const
    {
        if (elements.size() != rhs.elements.size()) {
            return false;
        }
        for (int i = 0 ; i < elements.size() ; i++) {
            if (elements[i] != rhs.elements[i]) {
                return false;
            }
        }
        return true;
    }
} ;

void displayqueueelement(queueelement i) {
    for (std::vector<long long>::iterator it = i.elements.begin() ; it != i.elements.end() ; ++it) {
        std::cout << *it << " ";
    }
    std::cout << "| ";
    for (std::vector<std::string>::iterator it = i.strings.begin() ; it != i.strings.end() ; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}


#ifdef CONCATENATION
long long concatenatenumber(long long a, long long b) {
    long long temp = 0;
    b *= 10;
    b += 1;
    while (b > 0) {
        temp *= 10;
        temp += b % 10;
        b /= 10;
    }
    while (temp > 0) {
        a *= 10;
        a += temp % 10;
        temp /= 10;
    }
    return a / 10;
}
#endif /* CONCATENATION */

int main(void) {
    std::set< long long > seen;
    std::priority_queue< queueelement > mainqueue;
    queueelement temp;
    std::string tempstring;
    std::vector< long long > elements;
    elements.clear();
    int i = 0; int j = 0;
    while (std::cin >> i) {
        elements.push_back(i);
    }
    temp.elements = elements;
    temp.strings.clear();
    i = 0;
    for (i = 0; i < elements.size() ; i++) {
        tempstring = static_cast<std::ostringstream*>( &(std::ostringstream() << elements[i]) )->str();
        temp.strings.push_back(tempstring);
    }
    mainqueue.push(temp);

#ifdef CONCATENATION
    // Concatenation
    std::vector< queueelement > concatqueue;
    concatqueue.push_back(temp);
    while (! concatqueue.empty()) {
        queueelement current = concatqueue.back();
        concatqueue.pop_back();
        for (int i = 0 ; i + 1 < current.elements.size() ; i++) {
            temp = queueelement();
            temp.elements.clear();
            temp.strings.clear();
            for (int j = 0 ; j + 1 < current.elements.size() ; j++) {
                if (j < i) {
                    temp.elements.push_back(current.elements[j]);
                    temp.strings.push_back(current.strings[j]);
                } else {
                    if (j == i) {
                        temp.elements.push_back(concatenatenumber(current.elements[j], current.elements[j + 1]));
                        temp.strings.push_back(current.strings[j] + current.strings[j + 1]);
                    } else {
                        if (j + 1 > i) {
                            temp.elements.push_back(current.elements[j + 1]);
                            temp.strings.push_back(current.strings[j + 1]);
                        }
                    }
                }
            }
            if (temp.strings.size() > 1) {
                mainqueue.push(temp);
                concatqueue.push_back(temp);
//                std::sort(concatqueue.begin(), concatqueue.end());
                std::unique(concatqueue.begin(), concatqueue.end());
            }
        }
    }
#endif /* CONCATENATION */
    int startsize = 10;
    while (! mainqueue.empty()) {
        queueelement current = mainqueue.top();
        if (current.elements.size() < startsize) {
            startsize = current.elements.size();
            std::cout << startsize << "..." << std::endl;
        }
#ifdef DEBUG
        std::cout << mainqueue.size() << " " << current.elements.size() << " !" << std::endl;
#endif /* DEBUG */
        mainqueue.pop();

#ifdef DISCARDDUPES
        while (!mainqueue.empty() & current == mainqueue.top()) {
            mainqueue.pop();
        }
#endif /* DISCARDDUPES */

#ifdef SHOWNEGATIVES
        if (current.elements.size() == 1 & current.elements[0] < UPPERLIMIT & current.elements[0] > -UPPERLIMIT & seen.count(current.elements[0]) == 0) {
#endif /* SHOWNEGATIVES */

#ifndef SHOWNEGATIVES
        if (current.elements.size() == 1 & current.elements[0] < UPPERLIMIT & current.elements[0] >= 0 & seen.count(current.elements[0]) == 0) {
#endif /* SHOWNEGATIVES */

            displayqueueelement(current);
        }
        for (int i = 0 ; i < current.elements.size() ; i++) {

#ifdef SQUAREROOT
            // Square Root
            if (is_perfect_square(current.elements[i])) {
                temp = queueelement();
                temp.elements.clear();
                temp.strings.clear();
                for (int j = 0 ; j < current.elements.size() ; j++) {
                    if (j != i) {
                        temp.elements.push_back(current.elements[j]);
                        temp.strings.push_back(current.strings[j]);
                    } else {
                        if (j == i) {
                            int root(round(sqrt(current.elements[j])));
                            if ((root * root) == current.elements[j]) {
                                temp.elements.push_back(root);
                                temp.strings.push_back("sqrt(" + current.strings[j] + ")");
                            } else {
                                root = root + 1;
                                if ((root * root) == current.elements[j]) {
                                    temp.elements.push_back(root);
                                    temp.strings.push_back("sqrt(" + current.strings[j] + ")");
                                }
                            }
                        }
                    } 
                }
                mainqueue.push(temp);
            }

#ifdef DEBUG
                displayqueueelement(current);
                displayqueueelement(temp);
                std::cout << std::endl;
#endif /* DEBUG */

#endif /* SQUAREROOT */

#ifdef ADDITION
        }
        for (int i = 0 ; i + 1 < current.elements.size() ; i++) {
            // Addition
            temp = queueelement();
            temp.elements.clear();
            temp.strings.clear();
            for (int j = 0 ; j + 1 < current.elements.size() ; j++) {
                if (j < i) {
                    temp.elements.push_back(current.elements[j]);
                    temp.strings.push_back(current.strings[j]);
                } else {
                    if (j == i) {
                        temp.elements.push_back(current.elements[j] + current.elements[j + 1]);
                        temp.strings.push_back("(" + current.strings[j] + " + " + current.strings[j + 1] + ")");
                    } else {
                        if (j + 1 > i) {
                            temp.elements.push_back(current.elements[j + 1]);
                            temp.strings.push_back(current.strings[j + 1]);
                        }
                    }
                }
            }
            mainqueue.push(temp);

#ifdef DEBUG
                displayqueueelement(current);
                displayqueueelement(temp);
                std::cout << std::endl;
#endif /* DEBUG */

#endif /* ADDITION */

#ifdef SUBTRACTION
            // Subtraction
            temp = queueelement();
            temp.elements.clear();
            temp.strings.clear();
            for (int j = 0 ; j + 1 < current.elements.size() ; j++) {
                if (j < i) {
                    temp.elements.push_back(current.elements[j]);
                    temp.strings.push_back(current.strings[j]);
                } else {
                    if (j == i) {
                        temp.elements.push_back(current.elements[j] - current.elements[j + 1]);
                        temp.strings.push_back("(" + current.strings[j] + " - " + current.strings[j + 1] + ")");
                    } else {
                        if (j + 1 > i) {
                            temp.elements.push_back(current.elements[j + 1]);
                            temp.strings.push_back(current.strings[j + 1]);
                        }
                    }
                }
            }
            mainqueue.push(temp);

#ifdef DEBUG
                displayqueueelement(current);
                displayqueueelement(temp);
                std::cout << std::endl;
#endif /* DEBUG */

#endif /* SUBTRACTION */

#ifdef MULTIPLICATION
            // Multiplication
            if (log10(abs(current.elements[i+1])) + log10(abs(current.elements[i])) < log10(UPPERLIMIT)) {
                temp = queueelement();
                temp.elements.clear();
                temp.strings.clear();
                for (int j = 0 ; j + 1 < current.elements.size() ; j++) {
                    if (j < i) {
                        temp.elements.push_back(current.elements[j]);
                        temp.strings.push_back(current.strings[j]);
                    } else {
                        if (j == i) {
                            temp.elements.push_back(current.elements[j] * current.elements[j + 1]);
                            temp.strings.push_back("(" + current.strings[j] + " * " + current.strings[j + 1] + ")");
                        } else {
                            if (j + 1 > i) {
                                temp.elements.push_back(current.elements[j + 1]);
                                temp.strings.push_back(current.strings[j + 1]);
                            }
                        }
                    }
                }
            }
            mainqueue.push(temp);

#ifdef DEBUG
                displayqueueelement(current);
                displayqueueelement(temp);
                std::cout << std::endl;
#endif /* DEBUG */

#endif /* MULTIPLICATION */

#ifdef DIVISION
            // Division
//            std::cout << "i " << current.elements[i] << " " << current.elements[i+1] << std::endl;
            if ((current.elements[i + 1]) != 0 and current.elements[i] % current.elements[i + 1] == 0) {
                temp = queueelement();
                temp.elements.clear();
                temp.strings.clear();
                for (int j = 0 ; j + 1 < current.elements.size() ; j++) {
                    if (j < i) {
                        temp.elements.push_back(current.elements[j]);
                        temp.strings.push_back(current.strings[j]);
                    } else {
                        if (j == i) {
                            temp.elements.push_back(current.elements[j] / current.elements[j + 1]);
                            temp.strings.push_back("(" + current.strings[j] + " / " + current.strings[j + 1] + ")");
                        } else {
                            if (j + 1 > i) {
                                temp.elements.push_back(current.elements[j + 1]);
                                temp.strings.push_back(current.strings[j + 1]);
                            }
                        }
                    }
                }
            }
            mainqueue.push(temp);

#ifdef DEBUG
                displayqueueelement(current);
                displayqueueelement(temp);
                std::cout << std::endl;
#endif /* DEBUG */

#endif /* DIVISION */

#ifdef EXPONENTS
            // Exponents
            if (current.elements[i+1] >=0 & abs(current.elements[i+1]) * log10(abs(current.elements[i])) < log10(UPPERLIMIT)) {
                temp = queueelement();
                temp.elements.clear();
                temp.strings.clear();
                for (int j = 0 ; j + 1 < current.elements.size() ; j++) {
                    if (j < i) {
                        temp.elements.push_back(current.elements[j]);
                        temp.strings.push_back(current.strings[j]);
                    } else {
                        if (j == i) {
                            temp.elements.push_back(pow(current.elements[j] , current.elements[j + 1]));
                            temp.strings.push_back("(" + current.strings[j] + " ** " + current.strings[j + 1] + ")");
                        } else {
                            if (j + 1 > i) {
                                temp.elements.push_back(current.elements[j + 1]);
                                temp.strings.push_back(current.strings[j + 1]);
                            }
                        }
                    }
                }
            }
            mainqueue.push(temp);

#ifdef DEBUG
                displayqueueelement(current);
                displayqueueelement(temp);
                std::cout << std::endl;
#endif /* DEBUG */

#endif /* EXPONENTS */
        }
    }
}