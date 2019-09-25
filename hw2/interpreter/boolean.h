#ifndef BOOLEAN_HPP
#define BOOLEAN_HPP

#include <string>
#include "arithmetic.h"

class BooleanExpression{
public:
 	BooleanExpression(){}
 	virtual std::string format() = 0;
 	virtual ~BooleanExpression(){}
};

class LargerThan : public BooleanExpression{
public:
 	LargerThan(NumericExpression *left, NumericExpression *right);
 	virtual ~LargerThan();
 	std::string format();
private:
 	NumericExpression *left_;
 	NumericExpression *right_;
};

class LessThan : public BooleanExpression{
public:
	LessThan(NumericExpression *left, NumericExpression *right);
 	virtual ~LessThan();
	std::string format();
private:
 	NumericExpression *left_;
 	NumericExpression *right_;
};

class EqualTo : public BooleanExpression{
public:
 	EqualTo(NumericExpression *left, NumericExpression *right);
 	virtual ~EqualTo();
 	std::string format();
private:
 	NumericExpression *left_;
 	NumericExpression *right_;
};
#endif