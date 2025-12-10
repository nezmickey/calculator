#ifndef _LEXER_
#define _LEXER_

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
using namespace std;

#include "token.cpp"

class Lexer{
private:
    const vector<char> digits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    const vector<char> operators = {'+', '-', '*', '/', '(', ')'};
    const map<char, TokenType> operator_token = {
        {'+', TokenType::PLUS},
        {'-', TokenType::MINUS},
        {'*', TokenType::MULTIPLY},
        {'/', TokenType::DIVIDE},
        {'(', TokenType::LPAREN},
        {')', TokenType::RPAREN}
    };
    bool is_operator(char c){
        return (find(operators.begin(), operators.end(), c) != operators.end());
    }
    bool is_digit(char c){
        return (find(digits.begin(), digits.end(), c) != digits.end());
    }
    TokenType operator_to_token(char c){
        return operator_token.at(c);
    }
public:
    vector<Token> tokenize(const string& input){
        vector<Token> tokens;
        const int input_length = input.length();
        for(int pos = 0; pos < input_length; pos++){
            char current_char = input[pos];
            if(is_operator(current_char)){
                tokens.push_back({operator_to_token(current_char), 0});
            }else if(is_digit(current_char)){
                bool shouldAddToken = true;
                if(tokens.size() > 0){
                    if(tokens.rbegin() -> type == TokenType::NUMBER){
                        shouldAddToken = false;
                    }
                }
                if(shouldAddToken){
                    tokens.push_back({TokenType::NUMBER, 0});
                }
                int current_digit = current_char - '0';
                tokens.at(tokens.size() - 1).value = (tokens.rbegin() -> value) * 10 + current_digit;
            }else if(isspace(current_char)){
                ; //空白文字は何もしない
            }else{
                // エラー処理：定義されていない文字を検出
                string err = "Unexpected text index:" + to_string(pos) + "  letter:" + current_char;
                throw runtime_error(err);
            }
        }
        tokens.push_back({TokenType::END, 0});
        return tokens;
    }
};

#endif //_LEXER_