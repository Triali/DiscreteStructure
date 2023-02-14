//
// Created by elton on 2/10/2023.
//

#ifndef CS236PROJ1_RULE_H
#define CS236PROJ1_RULE_H
using namespace std;

#include "Predicate.h"

class Rule
{
private:
    vector<Predicate> predicates;


public:
    //constructor
    Rule(Predicate HP, Predicate FP)
    {
        predicates.push_back(HP);
        predicates.push_back(FP);
//        cout << "finished Constructor" << endl;

    }

    void addPredicate(Predicate newPredicate)
    {
//        cout << "running addPredicate" << endl;
        predicates.push_back(newPredicate);
    }

    string RuleToString()
    {
//        cout << "running RuleToString" << endl;
        stringstream ruleString;
        ruleString << "  " << predicates.at(0).PredicateToStringR();
        ruleString << " :- ";
        for (int i = 1; i < predicates.size(); ++i)
        {
//            add the parameter
            ruleString << predicates.at(i).PredicateToStringR();
//            add comma if not at the last index of vector
            if (i != predicates.size()-1)
            {
                ruleString << ",";
            }
        }
        ruleString << ".";
        return ruleString.str();
    }


};
#endif //CS236PROJ1_RULE_H
