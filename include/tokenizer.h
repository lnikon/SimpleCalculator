#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <istream>

#include "tokentype.h"
#include "token.h"

/**
 * @todo write docs
 */
template <class NumericType>
class Tokenizer
{
public:
    /**
     * Default constructor
     */
    Tokenizer(std::istream&);
    Token<NumericType> GetToken();
    
private:
    std::istream & m_in;
};

template <class NumericType>
Tokenizer<NumericType>::Tokenizer(std::istream& is)
: m_in(is) { }

template<class NumericType> 
Token<NumericType> Tokenizer<NumericType>::GetToken()
{
    char ch;
    NumericType theValue;
    while(m_in.get(ch) && ch == ' ') {}
    
    if(m_in.good() && ch != '\n' && ch != '\0')
    {
        switch(ch)
        {
            case '^': return TokenType::EXP;
            case '/': return TokenType::DIV;
            case '*': return TokenType::MUL;
            case '(': return TokenType::OPAREN;
            case ')': return TokenType::CPAREN;
            case '+': return TokenType::PLUS;
            case '-': return TokenType::MINUS;
        
            default: 
                m_in.putback(ch);
                if(!(m_in >> theValue))
                {
                    std::cerr << "Parse error" << std::endl;
                    return TokenType::EOL;
                }
                return Token<NumericType>(VALUE, theValue);
        }
        
    }
    return TokenType::EOL;
}


#endif // TOKENIZER_H
