#include <iostream>
#include <fstream>
#include "Token.h"
#include "Scanner.h"
#include <string>
#include "Parser.h"

/*
int main(int argc, char* argv[])
{
    string fileName = argv[1];
//    cout << "file name: " << fileName << endl;

    ifstream myfile;
    string input;
    myfile.open(fileName);
    while (!myfile.eof())
    {
        string sub;
        getline(myfile, sub);//make a loop for reading whole file
        input = input + sub + "\n";
    }
    input.pop_back();
    myfile.close();

Scanner t = Scanner(input);
        t.PrintOutput();
        string output = t.TokenVectorToString();

//        ofstream outputFile;
//    outputFile.open("output.txt");
//    outputFile << output;
//    outputFile.close();

}
/*/


int main()
{
    ifstream myfile;
    string input;
    myfile.open("input.txt");
    while (!myfile.eof())
    {
        string sub;
        getline(myfile, sub);//make a loop for reading whole file
        input = input + sub + "\n";
    }
    input.pop_back();
    myfile.close();

    Scanner t = Scanner(input);
    t.scanAll();
//    string output = t.TokenVectorToString();
//    t.PrintOutput();
    vector<Token> tokens = t.getTokenList();
//            {
//            Token(STRING,"Ned",2),
//            Token(LEFT_PAREN,"(",2),
//            Token(COMMA,",",2),
//
//            Token(ID,"Ted",2),
//            Token(LEFT_PAREN,"(",2),
//            Token(ID,"Zed",2),
//            Token(COMMA,",",2),
//            Token(ID,"Ned",2),
//            Token(RIGHT_PAREN,")",2),
//            Token(COLON_DASH,":-",2),
//
//            Token(ID,"Ted",2),
//            Token(LEFT_PAREN,"(",2),
//            Token(STRING,"Ned",2),
//            Token(ID,"Zed",2),
//            Token(COMMA,",",2),
//            Token(STRING,"Zed",2),
//            Token(ID,"Ned",2),
//            Token(RIGHT_PAREN,")",2),
//            Token(PERIOD,".",2),
//
//            Token(COMMA,",",2),
//            Token(ID,"Ted",2),
//            Token(LEFT_PAREN,"(",2),
//            Token(STRING,"Ned",2),
//            Token(ID,"Zed",2),
//            Token(COMMA,",",2),
//            Token(ID,"Zed",2),
//            Token(STRING,"Ned",2),
//            Token(ID,"Zed",2),
//            Token(RIGHT_PAREN,")",2),
//            Token(ENDFILE,"",2),
//    };

    Parser p = Parser(tokens);
    p.datalogProgram();
//    p.advanceToken();
}
// check endlines in undefined string