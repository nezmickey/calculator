#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#include "token.cpp"
#include "lexer.cpp"
#include "parser.cpp"

# define STR(var) #var

int main(){
    string input_expression;
    getline(cin, input_expression);
    Lexer lexer;
    vector<Token> tokens = lexer.tokenize(input_expression);
    Parser parser(tokens);
    int ans = parser.calculate();
    cout << ans << endl;
    return 0;
}