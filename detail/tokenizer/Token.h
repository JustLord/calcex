//
// Created by nikita on 7/4/19.
//

#ifndef CALCEX_TOKEN_H
#define CALCEX_TOKEN_H

#include <stdexcept>

namespace detail {

    enum class TokenType {
        Operator,
        Number,
    };

    enum class OperatorType : char {
        Plus = '+',
        Minus = '-',
        Multiple = '*',
        Divide = '/',
        Exponentiation
    };

    inline int OperatorPriority(OperatorType operatorType) {
        switch (operatorType) {
            case OperatorType::Plus:
            case OperatorType::Minus:
                return 1;
            case OperatorType::Multiple:
            case OperatorType::Divide:
                return 2;
            case OperatorType::Exponentiation:
                return 3;
            default:
                throw std::logic_error("Invalid operator type.");
        }
    }

    struct Operator {
        OperatorType type;
        int priority;

        Operator(OperatorType t);
    };

    inline Operator::Operator(OperatorType t) : type{t}, priority{OperatorPriority(t)} {}


    class Token {
    public:
        explicit Token(double value);

        explicit Token(Operator o);

        TokenType getType() const;

        double getNumber() const;

        Operator getOperator() const;

    private:
        TokenType _type;
        union {
            double _number;
            Operator _operator;
        };
    };

    inline Token::Token(double value) : _type{TokenType::Number}, _number{value} {}

    inline Token::Token(Operator o) : _type{TokenType::Operator}, _operator{o} {}

    inline TokenType Token::getType() const { return _type; }

    inline Operator Token::getOperator() const { return _operator; }

    inline double Token::getNumber() const { return _number; }

}

#endif //CALCEX_TOKEN_H
