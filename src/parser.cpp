#ifndef _PARSER_
#define _PARSER_

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#include "token.cpp"

class Parser{
private:
    const vector<Token>& tokens;
    int current_index;
    Token current_token(){
        return tokens[current_index];
    }
    void consume_token(){
        current_index++;
    }
    //TokenTypeをチェックし違ったらエラーを出す
    void expect(TokenType expected_type){
        if(current_token().type != expected_type){
            string err = "Unexpected token Expected type:" + type_to_string(expected_type) + 
            " Actual token type:" + type_to_string(current_token().type);
            throw runtime_error(err);
        }
    }
    int parse_factor(){
        if(current_token().type == TokenType::NUMBER){
            int value = current_token().value;
            consume_token();
            return value;
        }else if(current_token().type == TokenType::LPAREN){
            consume_token();
            int value = parse_expr();
            if(current_token().type == TokenType::RPAREN){
                consume_token();
                return value;
            }else{
                throw runtime_error("Expected token \")\" was not found in parse_factor");
            }
        }else{
            throw runtime_error("Unexpected token in parse_factor");
        }
    }
    int parse_term(){
        int value = parse_factor();
        while(current_token().type == TokenType::MULTIPLY || current_token().type == TokenType::DIVIDE){
            TokenType op = current_token().type;
            consume_token();
            int right = parse_factor();
            if(op == TokenType::MULTIPLY){
                value *= right;
            }else{
                if (right == 0) {
                    throw runtime_error("Division by zero.");
                }
                value /= right;
            }
        }
        return value;
    }
    int parse_expr(){
        int value = parse_term();
        while(current_token().type == TokenType::PLUS || current_token().type == TokenType::MINUS){
            TokenType op = current_token().type;
            consume_token();
            int right = parse_term();
            if(op == TokenType::PLUS){
                value += right;
            }else{
                value -= right;
            }
        }
        return value;
    }
    void reset(){
        current_index = 0;
    }
public:
    Parser(const vector<Token>& list) 
        : tokens(list), current_index(0){
    }
    int calculate(){
        reset();
        return parse_expr();
    }
};

#endif //_PARSER_