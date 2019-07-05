//
// Created by nikita on 7/4/19.
//

#ifndef CALCEX_TOKENIZER_H
#define CALCEX_TOKENIZER_H

#include <string>
#include <vector>
#include "Token.h"


namespace detail {
    class Tokenizer {
    public:
        Tokenizer(std::string && input) : _raw{input} {}

        std::vector<Token> tokenize();

    private:
        std::string _raw;
    };
}

#endif //CALCEX_TOKENIZER_H
