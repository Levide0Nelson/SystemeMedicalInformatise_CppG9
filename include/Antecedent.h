#ifndef ANTECEDENT_H
#define ANTECEDENT_H

#include <string>
#include <iostream>
using namespace std;

class Antecedent {
private:
    string type;
    string description;
    string date;

public:
    Antecedent(string _type, string _description, string _date)
        : type(_type), description(_description), date(_date) {}

    void afficher() const {
        cout << " - Type : " << type << endl;
        cout << "   Description : " << description << endl;
        cout << "   Date : " << date << endl;
    }
};

#endif

