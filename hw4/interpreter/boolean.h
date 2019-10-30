#ifndef BOOLEAN_HPP
#define BOOLEAN_HPP

#include <string>
#include "arithmetic.h"

class BooleanExpression{
public:
 	BooleanExpression(){} // Base class, empty constructor
 	virtual std::string format() = 0;
 	virtual ~BooleanExpression(){}
 	virtual bool get_value() = 0; // pure virtual get value function
};

class LargerThan : public BooleanExpression{
public:
 	LargerThan(NumericExpression *left, NumericExpression *right);
 	virtual ~LargerThan();
 	std::string format();
 	bool get_value(); // get boolean value
private:
 	NumericExpression *left_;
 	NumericExpression *right_;
};

class LessThan : public BooleanExpression{
public:
	LessThan(NumericExpression *left, NumericExpression *right);
 	virtual ~LessThan();
	std::string format();
	bool get_value(); // get boolean value
private:
 	NumericExpression *left_;
 	NumericExpression *right_;
};

class EqualTo : public BooleanExpression{
public:
 	EqualTo(NumericExpression *left, NumericExpression *right);
 	virtual ~EqualTo();
 	std::string format();
 	bool get_value(); // get boolean value
private:
 	NumericExpression *left_;
 	NumericExpression *right_;
};
#endif