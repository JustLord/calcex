//
// Created by nikita on 7/8/19.
//

#include "AutomaticTokenizer.h"
#include <map>

namespace detail {

    std::vector<Token> AutomaticTokenizer::tokenize() {
        _state = AutomaticState::Scan;
        std::vector<Token> output;

        unsigned tokenStart = 0;
        for (unsigned i = 0; i <= _raw.length(); i++) {
            if (_state == AutomaticState::Scan && i != _raw.length()) {
                if (isdigit(_raw[i])) {
                    tokenStart = i;
                    _state = AutomaticState::ReadingNumber;
                } else if (isOperator(_raw[i])) {
                    tokenStart = i;
                    _state = AutomaticState::ReadingOperator;
                }
            } else if (_state == AutomaticState::ReadingNumber) {
                if (i == _raw.length() || !isdigit(_raw[i])) {
                    output.emplace_back(std::stod(_raw.substr(tokenStart, i - tokenStart)));
                    _state = AutomaticState::Scan;
                    i--;
                }
            } else if (_state == AutomaticState::ReadingOperator) {
                if (i == _raw.length() || !isOperator(_raw[i])) {
                    if (auto operatorType = getOperator(_raw.substr(tokenStart, i - tokenStart)); operatorType) {
                        output.emplace_back(operatorType.value());
                        _state = AutomaticState::Scan;
                        i--;
                    }
                }
            }

        }
        return output;
    }

    bool AutomaticTokenizer::isOperator(char ch) {
        switch (auto o = static_cast<OperatorType >(ch); o) {
            case OperatorType::Plus:
            case OperatorType::Minus:
            case OperatorType::Multiple:
            case OperatorType::Divide:
                return true;
            default:
                return false;
        }
    }

    std::optional<OperatorType> AutomaticTokenizer::getOperator(const std::string &str) const {
        static std::map<std::string, OperatorType> operators = {{"*",  OperatorType::Multiple},
                                                                {"/",  OperatorType::Divide},
                                                                {"+",  OperatorType::Plus},
                                                                {"-",  OperatorType::Minus},
                                                                {"**", OperatorType::Exponentiation}};

        auto iterator = operators.find(str);

        if (iterator != operators.end())
            return iterator->second;

        return {};
    }
}