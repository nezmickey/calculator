#ifndef _TOKEN_
#define _TOKEN_

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
using namespace std;

enum class TokenType {
    PLUS,       // +
    MINUS,      // -
    MULTIPLY,   // *
    DIVIDE,     // /
    LPAREN,     // (
    RPAREN,     // )
    NUMBER,     // 数字 digitの集まり
    END         // ファイル終端（解析終了）を示す
};

const map<TokenType, string> map_type_strings = {
    {TokenType::PLUS, "PLUS"},
    {TokenType::MINUS, "MINUS"},
    {TokenType::MULTIPLY, "MULTIPLY"},
    {TokenType::DIVIDE, "DIVIDE"},
    {TokenType::LPAREN, "LPAREN"},
    {TokenType::RPAREN, "RPAREN"},
    {TokenType::NUMBER, "NUMBER"},
    {TokenType::END, "END"}
};

// トークンの定義
struct Token {
    TokenType type;       // トークンの種類
    int value = 0;         // NUMBERの場合の数値
};

string type_to_string(TokenType t){
    return map_type_strings.at(t);
}

#endif //_TOKEN_