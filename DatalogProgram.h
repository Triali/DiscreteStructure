//
// Created by elton on 2/10/2023.
//

#ifndef CS236PROJ1_DATALOGPROGRAM_H
#define CS236PROJ1_DATALOGPROGRAM_H

#include "Rule.h"
#include "Predicate.h"
#include <set>

using namespace std;

class DatalogProgram
{
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;

    set<string> domain;
    set<string>::iterator itr;


public:
    void addScheme(Predicate newScheme)
    {
        schemes.push_back(newScheme);
    }

    void addFact(Predicate newFact)
    {
        facts.push_back(newFact);
        for (int i = 0; i < newFact.getParameters().size(); ++i)
        {
            domain.insert(newFact.getParameters().at(i).getValue());
        }

    }

    void addRule(Rule newRule)
    {
        rules.push_back(newRule);
    }

    void addQuery(Predicate newQuery)
    {
        queries.push_back(newQuery);
    }

    string DatalogProgramToString()
    {
        stringstream dpString;
        dpString << "Schemes(" << schemes.size() << "):" << endl;
        dpString << PredVectToString(schemes);

        dpString << "Facts(" << facts.size() << "):" << endl;
        dpString << PredVectToString(facts);

        dpString << "Rules(" << rules.size() << "):" << endl;
        dpString << RuleVectToString(rules);

        dpString << "Queries(" << queries.size() << "):" << endl;
        dpString << PredVectToString(queries);

        dpString << "Domain(" << domain.size() << "):" << endl;
        dpString << StringSetToString(domain);

        return dpString.str();
    }

    string PredVectToString(vector<Predicate> predVect)
    {
        stringstream predString;
        for (int i = 0; i < predVect.size(); ++i)
        {
            predString << predVect.at(i).PredicateToString()<< endl;
        }
        return predString.str();
    }

    string RuleVectToString(vector<Rule> ruleVect)
    {
        stringstream ruleString;
        for (int i = 0; i < ruleVect.size(); ++i)
        {
            ruleString << ruleVect.at(i).RuleToString() << endl;
        }
        return ruleString.str();
    }

    string StringSetToString(set<string> sSet)
    {
        stringstream setString;
        for (itr = sSet.begin(); itr != sSet.end(); itr++) {
            setString << *itr << endl;
        }
        return setString.str();
    }


};

#endif //CS236PROJ1_DATALOGPROGRAM_H
