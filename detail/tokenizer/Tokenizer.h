#include <utility>

//
// Created by nikita on 7/8/19.
//

#ifndef CALCEX_AUTOMATICTOKENIZER_H
#define CALCEX_AUTOMATICTOKENIZER_H

#include "TokenizerInterface.h"
#include <optional>

namespace detail {

class Tokenizer : public TokenizerInterface
{
public:
    Tokenizer(std::string str);
    std::vector<Token> tokenize() override;

private:
    std::optional<Operator> getOperator(char ch);

private:
    enum class State
    {
        Scan,
        ReadingNumber,
        ReadingVariable,
        ReadingOperator,
    };

    std::string _raw;
    State _state;
};

inline Tokenizer::Tokenizer(std::string str) : _raw{std::move(str)}, _state{Tokenizer::State::Scan} {}

} // namespace detail

#endif //CALCEX_AUTOMATICTOKENIZER_H
