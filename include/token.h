#ifndef TOKEN_H
#define TOKEN_H

#include "tokentype.h"

/**
 * @todo write docs
 */
template <class NumericType>
class Token
{
public:
    /**
     * Default constructor
     */
    Token(TokenType tt = EOL, const NumericType& nt = 0)
    : m_theType(tt), m_theValue(nt) { }
    
    TokenType GetType() const;
    const NumericType& GetValue() const;
private:
    TokenType m_theType = EOL;
    NumericType m_theValue = 0;
};

template <class NumericType>
TokenType Token<NumericType>::GetType() const
{
    return m_theType;
}

template <class NumericType>
const NumericType& Token<NumericType>::GetValue() const
{
    return m_theValue;
}
#endif // TOKEN_H
