#include "Tokenizer.h"

using namespace detail;

std::vector<Token> Tokenizer::tokenize() {
    if (_raw.empty())
        return {};

    std::vector<Token> tokens;
    for (unsigned i = 0; i < _raw.size(); i++) {
        if (isdigit(_raw[i])) {
            unsigned start = i;
            while (isdigit(_raw[i]) || _raw[i] == '.') i++;
            tokens.emplace_back(std::stod(_raw.substr(start, i - start)));
            i--;
            continue;
        }

        switch (auto o = static_cast<OperatorType>(_raw[i])){
            case OperatorType::Plus:
            case OperatorType::Minus:
            case OperatorType::Multiple:
            case OperatorType::Divide:
                tokens.emplace_back(o);
                continue;
        }
    }

    return tokens;
}
