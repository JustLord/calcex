//
// Created by nikita on 7/8/19.
//

#include "AutomaticTokenizer.h"
#include <ctype.h>
#include <map>
#include <string>

namespace detail {

std::vector<Token> AutomaticTokenizer::tokenize()
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
            else if (isOperator(_raw[i]))
            {
                i--;
                _state = State::ReadingOperator;
            }
        }
        else if (_state == State::ReadingNumber)
        {
            if (i == _raw.length() || !isdigit(_raw[i]))
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

            if (auto op = isOperator(_raw[i]))
            {
                if (op.value() == OperatorType::Multiple && output.back().getType() == TokenType::Operator && output.back().getOperator().type == OperatorType::Multiple)
                    output.back().getOperator().type = OperatorType::Exponentiation;
                else
                    output.emplace_back(op.value());
            }
            else
            {
                _state = State::Scan;
                i--;
            }
        }
    }
    return output;
}

std::optional<OperatorType> AutomaticTokenizer::isOperator(char ch)
{
    switch (auto o = static_cast<OperatorType>(ch); o)
    {
    case OperatorType::Plus:
    case OperatorType::Minus:
    case OperatorType::Multiple:
    case OperatorType::Divide:
    case OperatorType::OpeningBracket:
    case OperatorType::ClosingBracket:
        return o;
    default:
        return {};
    }
}
} // namespace detail