#ifndef PRECEDENCE_H
#define PRECEDENCE_H

struct Precedence 
{
    int inputSymbol = 0;
    int topOfStack = 0;
} PREC_TABLE[] = 
{
    {0,   -1}, {0, 0},   // EOL, VALUE
    {100, 0}, {0, 99},  // OPAREN, CPAREN
    {6,   5},           // EXP
    {3,   4}, {3, 4},   // MULT, DIV
    {1,   2}, {1, 2}   // PLUS, MINUS
};

#endif
