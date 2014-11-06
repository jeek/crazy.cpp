#include <iostream>  // std::cout
#include <vector>    // std::vector
#include <queue>     // std::priority_queue
#include <math.h>    // pow
#include <sstream>
#include <stdlib.h>

#define UPPERLIMIT 1000000000
#define SUBTRACTION
#define CONCATENATION
#define DISCARDDUPES
#define SHOWNEGATIVES

struct queueelement {
    std::vector< long long > elements;
    std::vector<std::string> strings;
    bool operator<(const queueelement& rhs) const
    {
        if (elements.size() != rhs.elements.size()) {
            return elements.size() < rhs.elements.size();
        }
        for (int i = 0 ; i < elements.size() ; i++) {
            if (elements[i] != rhs.elements[i]) {
                return elements[i] > rhs.elements[i];
            }
        }
        return elements[0] < rhs.elements[0];
    }
} ;

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

int main(void) {
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
            }
        }
    }
#endif /* CONCATENATION */
    while (! mainqueue.empty()) {
        queueelement current = mainqueue.top();
        mainqueue.pop();
#ifdef SHOWNEGATIVES
        if (current.elements.size() == 1 & current.elements[0] < UPPERLIMIT & current.elements[0] > -UPPERLIMIT) {
#endif /* SHOWNEGATIVES */
#ifndef SHOWNEGATIVES
        if (current.elements.size() == 1 & current.elements[0] < UPPERLIMIT & current.elements[0] >= 0) {
#endif /* SHOWNEGATIVES */
            for (std::vector<long long>::iterator it = current.elements.begin() ; it != current.elements.end() ; ++it) {
                std::cout << *it << " ";
            }
            std::cout << "| ";
            for (std::vector<std::string>::iterator it = current.strings.begin() ; it != current.strings.end() ; ++it) {
                std::cout << *it << " ";
            }
            std::cout << std::endl;
        }
        for (int i = 0 ; i + 1 < current.elements.size() ; i++) {
            // Addition
            temp = queueelement();
            temp.elements.clear() ;
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

#ifdef SUBTRACTION
            // Subtraction
            temp = queueelement();
            temp.elements.clear() ;
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

#endif /* SUBTRACTION */
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

#ifdef DIVISION
            // Division
            if (current.elements[i + 1] != 0 & current.elements[i] % current.elements[i + 1] == 0) {
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
#endif /* DIVISION */
            // Exponents
            if (abs(current.elements[i+1]) * log10(abs(current.elements[i])) < log10(UPPERLIMIT)) {
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
        }
#ifdef DISCARDDUPES
        bool good = true;
        while (good & !mainqueue.empty()) {
            if (current.elements.size() != mainqueue.top().elements.size()) {
                good = false;
            } else {
                for (int i = 0 ; i < current.elements.size() ; i++) {
                    if (current.elements[i] != mainqueue.top().elements[i]) {
                        good = false;
                    }
                }
                if (good) {
                    mainqueue.pop();
                }
            }
        }
#endif /* DISCARDDUPES */
    }
}