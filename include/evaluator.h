#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

#include "tokentype.h"
#include "token.h"
#include "tokenizer.h"
#include "precedence.h"

/**
 * @todo write docs
 */
template <class NumericType>
class Evaluator
{
public:
    /**
     * Default constructor
     */
    Evaluator(const std::string &);
    
    NumericType GetValue();
    
private:
    std::vector<TokenType> m_opStack;
    std::vector<NumericType> m_postFixStack;
    
    std::istringstream m_str;
    
    NumericType GetTop();
    
    void BinaryOp(TokenType topOp);
    void ProcessToken(const Token<NumericType>&);
};

template<class NumericType> 
Evaluator<NumericType>::Evaluator(const std::string& str)
: m_str(str)
{
    m_opStack.push_back(TokenType::EOL);
}

template<class NumericType> 
NumericType Evaluator<NumericType>::GetValue()
{
    Tokenizer<NumericType> tok(m_str);
    Token<NumericType> lastToken;
    
    do 
    {
        lastToken = tok.GetToken();
        ProcessToken(lastToken);
    } while(lastToken.GetType() != EOL);
    
    if(m_postFixStack.empty())
    {
        std::cerr << "Missing operand!" << std::endl;
        return 0;
    }
    
    NumericType theResult = m_postFixStack.back();
    m_postFixStack.pop_back();
    if(!m_postFixStack.empty())
    {
        std::cerr << "Missing operators!\n" << std::endl;
    }
    return theResult;
}

template<class NumericType> 
NumericType Evaluator<NumericType>::GetTop()
{
    if(m_postFixStack.empty())
    {
        std::cerr << "Missing operand" << std::endl;
        return 0;
    }
    
    NumericType tmp = m_postFixStack.back();
    m_postFixStack.pop_back();
    return tmp;
}

template<class NumericType>
void Evaluator<NumericType>::BinaryOp(TokenType topOp)
{
    if(topOp == TokenType::OPAREN)
    {
        std::cerr << "Unbalanced parentheses" << std::endl;
        m_opStack.pop_back();
        return;
    }
    
    NumericType rhs = GetTop();
    NumericType lhs = GetTop();
    
    if(topOp == TokenType::EXP)
    {
        m_postFixStack.push_back(pow(lhs, rhs));
    }
    else if(topOp == TokenType::PLUS)
    {
        m_postFixStack.push_back(lhs + rhs);
    }
    else if(topOp == TokenType::MINUS)
    {
        m_postFixStack.push_back(lhs - rhs);
    }
    else if(topOp == TokenType::MUL)
    {
        m_postFixStack.push_back(lhs * rhs);
    }
    else if(topOp == TokenType::DIV)
    {
        if(rhs != 0)
        {
            m_postFixStack.push_back(lhs / rhs);
        }
        else 
        {
            std::cerr << "Division by zero!" << std::endl;
            m_postFixStack.push_back(lhs);
        }
    }
    m_opStack.pop_back();
}

template<class NumericType>
void Evaluator<NumericType>::ProcessToken(const Token<NumericType>& lastToken)
{
    TokenType topOp;
    TokenType lastType = lastToken.GetType();
    
    switch(lastType)
    {
        case TokenType::VALUE:
            m_postFixStack.push_back(lastToken.GetValue());
            return;
            
        case TokenType::CPAREN:
            while(((topOp = m_opStack.back()) != TokenType::OPAREN) 
                && (topOp != TokenType::EOL))
            {
                BinaryOp(topOp);
            }
            if(topOp == TokenType::OPAREN)
            {
                m_opStack.pop_back();
            }
            else 
            {
                std::cerr << "Missing open parenthesis" << std::endl;
            }
            break;
            
        default:
            while(PREC_TABLE[lastType].inputSymbol <= 
                  PREC_TABLE[topOp = m_opStack.back()].topOfStack)
            {
                BinaryOp(topOp);
            }
            
            if(lastToken.GetType() != TokenType::EOL)
            {
                m_opStack.push_back(lastType);
            }
            break;
    }
}

#endif // EVALUATOR_H
