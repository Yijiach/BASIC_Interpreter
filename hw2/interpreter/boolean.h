#ifndef BOOLEAN_HPP
#define BOOLEAN_HPP

#include <string>
#include "arithmetic.h"
using namespace std;

class BooleanExpression{
public:
 	BooleanExpression(){}
 	virtual string format() = 0;
 	virtual ~BooleanExpression(){}
};

class LargerThan : public BooleanExpression{
public:
 	LargerThan(NumericExpression *left, NumericExpression *right);
 	virtual ~LargerThan();
 	string format();
private:
 	NumericExpression *left_;
 	NumericExpression *right_;
};

class LessThan : public BooleanExpression{
public:
	LessThan(NumericExpression *left, NumericExpression *right);
 	virtual ~LessThan();
	string format();
private:
 	NumericExpression *left_;
 	NumericExpression *right_;
};

class EqualTo : public BooleanExpression{
public:
 	EqualTo(NumericExpression *left, NumericExpression *right);
 	virtual ~EqualTo();
 	string format();
private:
 	NumericExpression *left_;
 	NumericExpression *right_;
};
#endif