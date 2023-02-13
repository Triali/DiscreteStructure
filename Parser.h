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
        cout << "match: " << t << endl;
//        if the current token type matches t
        try
        {
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
        } catch (string msg)
        {
            cerr << msg << endl;
            exit(1);
        }
    }

    void datalogProgram()
    {
        match(SCHEMES);
        match(COLON);
        scheme();
        schemeList();
        match(FACTS);
        match(COLON);
        factList();
        match(RULES);
        match(COLON);
        ruleList();
        match(QUERIES);
        match(COLON);
        query();
        queryList();
        match(ENDFILE);

        cout << "Success!" << endl;
    }

    void schemeList()
    {
        if (tokenType() == ID)
        {
            scheme();
            schemeList();
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
    }

    Predicate scheme()
    {
        // RULE scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN
        if (tokenType() == ID)
        {
            id();
            Predicate scheme = Predicate(curToken.getValue());
            match(LEFT_PAREN);
            id();
            idList();
            match(RIGHT_PAREN);
            return scheme;
        }
    }

    Predicate fact()
    {
        id();
        Predicate fact = Predicate(curToken.getValue());
        match(LEFT_PAREN);
        match(STRING);
        stringList();
        match(RIGHT_PAREN);
        match(PERIOD);
        return fact;
    }

    void rule()
    {
        headPredicate();
        match(COLON_DASH);
        predicate();
        predicateList();
        match(PERIOD);
    }

    Predicate query()
    {
        predicate();
        match(Q_MARK);
    }

    Predicate headPredicate()
    {
        id();
        Predicate headPred = Predicate(curToken.getValue());
        match(LEFT_PAREN);
        id();
//        idList(headPred);
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
        cout << Pred.PredicateToString() << endl;
        return Pred;
    }

    void predicateList()
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            predicate();
            predicateList();
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

    void stringList()
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            match(STRING);
            stringList();
        }
        else
        {
            // lambda
        }
    }

    void idList()
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            id();
//            Pred.AddParameter(id());
            idList();
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
            id();
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

};


#endif //CS236PROJ1_PARSER_H
