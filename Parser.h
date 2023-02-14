//
// Created by elton on 2/6/2023.
//

#ifndef CS236PROJ1_PARSER_H
#define CS236PROJ1_PARSER_H

#include <vector>
#include "Token.h"
#include <iostream>
#include <sstream>
#include "DatalogProgram.h"

using namespace std;

class Parser
{
private:
    vector<Token> tokens;
    Token curToken = Token(ENDFILE, "", -1);


public:
    Parser(const vector<Token> &tokens) : tokens(tokens)
    {}

    void parse()
    {
        DatalogProgram datalogProgram1;
        try
        {
            datalogProgram(datalogProgram1);
        }
        catch (string msg)
        {
            cerr << msg << endl;
            exit(1);
        }

        cout << "Success!" << endl;
        cout << datalogProgram1.DatalogProgramToString();
    }

    TokenType tokenType()
    {
        curToken = tokens.at(0);
        return tokens.at(0).getType();
    }

    void PrintCurToken()
    {
        cout << curToken.toString() << endl;
    }

    void advanceToken()
    {
        tokens.erase(tokens.begin());
    }

    void throwError()
    {

        stringstream error;
        error << "Failure!\n  " << tokens.at(0).toString();
        throw error.str();

    }

    void match(TokenType t)
    {
//        cout << "match: " << t << endl;
//        if the current token type matches t

        if (t == tokenType())
        {
//        advance to the next token
            advanceToken();
        }
        else
        {
//        report a syntax error
//cout << t << endl;
//cout << curToken.getType() <<endl;
            throwError();
        }

    }

    void datalogProgram(DatalogProgram& datalogProgram)
    {
        match(SCHEMES);
        match(COLON);
//        cout << scheme().PredicateToString() << endl;
        datalogProgram.addScheme(scheme());
        schemeList(datalogProgram);
        match(FACTS);
        match(COLON);
        factList();
        match(RULES);
        match(COLON);
        ruleList();
        match(QUERIES);
        match(COLON);
        datalogProgram.addQuery(query());
        queryList();
        match(ENDFILE);

    }

    void schemeList(DatalogProgram &dP)
    {
        if (tokenType() == ID)
        {
            dP.addScheme(scheme());
            schemeList(dP);
        }
        else
        {
            //lambda
        }
    }

    void factList()
    {
        if (tokenType() == ID)
        {
            fact();
            factList();
        }
        else
        {
            //lambda
        }
    }

    void ruleList()
    {
        if (tokenType() == ID)
        {
            rule();
            ruleList();
        }
        else
        {
            //lambda
        }
    }

    void queryList()
    {
        if (tokenType() == ID)
        {
            query();
            queryList();
        }
        else
        {
            //lambda
        }
//        cout << "finished QList" << endl;
    }

    Predicate scheme()
    {
        // RULE scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN
        id();
        Predicate scheme = Predicate(curToken.getValue());
        match(LEFT_PAREN);
        scheme.AddParameter(id());
        idList(scheme);
        match(RIGHT_PAREN);
//        cout << scheme.PredicateToString() << endl;
        return scheme;
    }

    Predicate fact()
    {
        id();
        Predicate fact = Predicate(curToken.getValue());
        match(LEFT_PAREN);
        stringM();
        stringList(fact);
        match(RIGHT_PAREN);
        match(PERIOD);
        fact.getEnd(".");
//        cout << fact.PredicateToString() << endl;
        return fact;
    }

    Rule rule()
    {

        Predicate HP = headPredicate();
        match(COLON_DASH);
        Predicate FP = predicate();
        Rule Ru = Rule(HP, FP);
        predicateList(Ru);
//        cout << Ru.RuleToString() << endl;
        match(PERIOD);
        return Ru;


    }

    Predicate query()
    {
        Predicate query = predicate();
        match(Q_MARK);
        query.getEnd("?");
//        cout << query.PredicateToString() << endl;
        return query;

    }

    Predicate headPredicate()
    {
        id();
        Predicate headPred = Predicate(curToken.getValue());
        match(LEFT_PAREN);
        id();
        idList(headPred);
        match(RIGHT_PAREN);
        return headPred;
    }

    Predicate predicate()
    {
        // declare predicate variable

        id();
//        PrintCurToken();
        Predicate Pred = Predicate(curToken.getValue());
        match(LEFT_PAREN);
        Pred.AddParameter(parameter());
        parameterList(Pred);
        match(RIGHT_PAREN);
//        cout << Pred.PredicateToString() << endl;
        return Pred;
    }

    void predicateList(Rule &Ru)
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            Ru.addPredicate(predicate());
            predicateList(Ru);
        }
        else
        {
            // lambda
        }
    }

    void parameterList(Predicate &Pred)
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            Pred.AddParameter(parameter());
            parameterList(Pred);
        }
        else
        {
            // lambda
        }
    }

    void stringList(Predicate &Pred)
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            Pred.AddParameter(stringM());
            stringList(Pred);
        }
        else
        {
            // lambda
        }
    }

    void idList(Predicate &Pred)
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
//            id();
            Pred.AddParameter(id());
            idList(Pred);
        }
        else
        {
            // lambda
        }
    }

    Parameter parameter()
    {

        if (tokenType() == STRING)
        {
            match(STRING);
        }
        else
        {
            match(ID);
        }


        Parameter Para = Parameter(curToken.getValue());
//        cout << Para.getValue() << endl;
        return Para;
    };

    Parameter id()
    {
        match(ID);
        Parameter Para = Parameter(curToken.getValue());
        return Para;
    }

    Parameter stringM()
    {
        match(STRING);
        Parameter Para = Parameter(curToken.getValue());
        return Para;
    }

};


#endif //CS236PROJ1_PARSER_H
