//
// Created by nikita on 7/8/19.
//

#include "Tokenizer.h"
#include <ctype.h>
#include <map>
#include <string>

namespace detail {

std::vector<Token> Tokenizer::tokenize()
{
    _state = State::Scan;
    std::vector<Token> output;

    unsigned tokenStart = 0;
    for (unsigned i = 0; i <= _raw.length(); i++)
    {
        if (_state == State::Scan && i != _raw.length())
        {
            if (isdigit(_raw[i]))
            {
                tokenStart = i;
                _state = State::ReadingNumber;
            }
            else if (isalpha(_raw[i]))
            {
                tokenStart = i;
                _state = State::ReadingSymbol;
            }
            else if (getOperator(_raw[i]))
            {
                i--;
                _state = State::ReadingOperator;
            }
        }
        else if (_state == State::ReadingNumber)
        {
            if (i == _raw.length() || !(isdigit(_raw[i]) || _raw[i] == '.'))
            {
                output.emplace_back(std::stod(_raw.substr(tokenStart, i - tokenStart)));
                _state = State::Scan;
                i--;
            }
        }
        else if (_state == State::ReadingOperator)
        {
            if (i == _raw.length())
                continue;

            if (auto op = getOperator(_raw[i]))
            {
                //TODO there must be a better way
                if (op.value() == Operator::Minus && (output.empty() || output.back().getType() == TokenType::Operator))
                {
                    _state = State::ReadingNumber;
                    tokenStart = i;
                }
                else if (op.value() == Operator::Multiple && output.back().getType() == TokenType::Operator && output.back().getOperator() == Operator::Multiple)
                {
                    output.back().setOperator(Operator::Exponentiation);
                }
                else
                {
                    output.emplace_back(op.value());
                }
            }
            else
            {
                _state = State::Scan;
                i--;
            }
        }
        else if (_state == State::ReadingSymbol)
        {
            if (i == _raw.length() || !(isdigit(_raw[i]) || isalpha(_raw[i]) || _raw[i] == '_'))
            {
                auto symbol = _raw.substr(tokenStart, i - tokenStart);
                if(symbol == "print")
                    output.emplace_back(Operator::Print);
                else
                    output.emplace_back(symbol);

                _state = State::Scan;
                i--;
            }
        }
    }
    return output;
}

std::optional<Operator> Tokenizer::getOperator(char ch)
{
    switch (auto o = static_cast<Operator>(ch); o)
    {
    case Operator::Plus:
    case Operator::Minus:
    case Operator::Multiple:
    case Operator::Divide:
    case Operator::OpeningBracket:
    case Operator::ClosingBracket:
    case Operator::Equate:
        return o;
    default:
        return {};
    }
}
} // namespace detail