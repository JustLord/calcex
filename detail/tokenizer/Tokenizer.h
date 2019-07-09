//
// Created by nikita on 7/4/19.
//

#ifndef CALCEX_TOKENIZER_H
#define CALCEX_TOKENIZER_H

#include <string>
#include <vector>
#include "Token.h"
#include "TokenizerInterface.h"


namespace detail {
    class Tokenizer : public TokenizerInterface{
    public:
        Tokenizer(std::string && input) : _raw{input} {}

        std::vector<Token> tokenize() override;

    private:
        std::string _raw;
    };
}

#endif //CALCEX_TOKENIZER_H
