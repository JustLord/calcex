#include <utility>

//
// Created by nikita on 7/8/19.
//

#ifndef CALCEX_AUTOMATICTOKENIZER_H
#define CALCEX_AUTOMATICTOKENIZER_H

#include "TokenizerInterface.h"
#include <optional>

namespace detail {
    class AutomaticTokenizer : public TokenizerInterface {
    public:
        AutomaticTokenizer(std::string str);

        std::vector<Token> tokenize() override;

    private:
        std::optional<OperatorType> isOperator(char ch);

    private:
        enum class AutomaticState {
            Scan,
            ReadingNumber,
            ReadingOperator,
        };

        std::string _raw;
        AutomaticState _state;
    };

    inline AutomaticTokenizer::AutomaticTokenizer(std::string str) : _raw{std::move(str)} {}
}


#endif //CALCEX_AUTOMATICTOKENIZER_H
