//
// Created by nikita on 7/4/19.
//

#ifndef CALCEX_TOKEN_H
#define CALCEX_TOKEN_H

#include <cstring>
#include <stdexcept>

namespace detail {

enum class TokenType
{
    Operator,
    Number,
    Variable,
};

enum class Operator : char
{
    Plus = '+',
    Minus = '-',
    Multiple = '*',
    Divide = '/',
    Exponentiation,
    OpeningBracket = '(',
    ClosingBracket = ')',
    Equate = '=',
};

inline int OperatorPriority(Operator operatorType)
{
    switch (operatorType)
    {
    case Operator::Exponentiation:
        return 1;
    case Operator::Multiple:
    case Operator::Divide:
        return 2;
    case Operator::Plus:
    case Operator::Minus:
        return 3;
    case Operator::OpeningBracket:
    case Operator::ClosingBracket:
        return 4;
    case Operator::Equate:
        return 5;

    default:
        throw std::logic_error("Invalid operator.");
    }
}

class Token
{
public:
    Token(Token &&other);
    explicit Token(double value);
    explicit Token(Operator o);
    explicit Token(std::string &&variable);
    ~Token();

    TokenType getType() const;
    double getValue() const;
    Operator getOperator() const;
    void setOperator(Operator o);
    const char *getVariable() const;

private:
    TokenType _type;
    union
    {
        double _value;
        Operator _operator;
        char *_variable;
    };
};

inline Token::Token(Token &&other) : _type{other._type}
{
    _value = other._value;
    if (_type == TokenType::Variable)
        other._variable = nullptr;
}
inline Token::Token(double value) : _type{TokenType::Number}, _value{value} {}
inline Token::Token(Operator o) : _type{TokenType::Operator}, _operator{o} {}
inline Token::Token(std::string &&variable) : _type{TokenType::Variable}
{
    _variable = new char[variable.size() + 1];
    strncpy(_variable, variable.c_str(), variable.size());
}
inline Token::~Token()
{
    if (_type == TokenType::Variable && _variable)
        delete[] _variable;
}

inline TokenType Token::getType() const { return _type; }
inline Operator Token::getOperator() const { return _operator; }
inline double Token::getValue() const { return _value; }
inline const char *Token::getVariable() const { return _variable; }
inline void Token::setOperator(Operator o) { _operator = o; }

} // namespace detail

#endif //CALCEX_TOKEN_H
