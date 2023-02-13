//
// Created by elton on 2/10/2023.
//

#ifndef CS236PROJ1_PREDICATE_H
#define CS236PROJ1_PREDICATE_H


#include "Parameter.h"
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Predicate
{
private:

    string name;
    vector<Parameter> parameters;

public:
    //contructor
    Predicate(string name)
    {
        this->name = name;
    }

    //get fuctions

    //get name
    string getName()
    {
        return name;
    }
    //get parameters
    vector<Parameter> getParameters()
    {
        return parameters;
    }

    //add parameter
    void AddParameter(Parameter newParameter)
    {
        parameters.push_back(newParameter);
    }

    string PredicateToString()
    {
        stringstream predicateString;
        //add name ( parameter, ... parameter)
        predicateString << "  " <<name << "(";
        for (int i = 0; i < getParaSize(); ++i)
        {
//            add the parameter
            predicateString << parameters.at(i).getValue();
//            add comma if not at the last index of vector
            if (i != getParaSize()-1)
            {
                predicateString << ",";
            }
        }
//        add last paranthisis
        predicateString << ")";
        return predicateString.str();
    }

    int getParaSize()
    {
        return parameters.size();
    }




};
#endif //CS236PROJ1_PREDICATE_H
