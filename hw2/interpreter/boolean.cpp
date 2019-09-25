#include "boolean.h"
using namespace std;

LargerThan :: LargerThan(NumericExpression *left, NumericExpression *right) : 
left_(left), right_(right){}
LargerThan :: ~LargerThan(){
	delete this->left_;
	delete this->right_;
}
string LargerThan :: format(){
	return this->left_->format() + " > " + this->right_->format();
}

LessThan :: LessThan(NumericExpression *left, NumericExpression *right) : 
left_(left), right_(right){}
LessThan :: ~LessThan(){
	delete this->left_;
	delete this->right_;
}
string LessThan :: format(){
	return this->left_->format() + " < " + this->right_->format();
}

EqualTo :: EqualTo(NumericExpression *left, NumericExpression *right) : 
left_(left), right_(right){}
EqualTo :: ~EqualTo(){
	delete this->left_;
	delete this->right_;
}
string EqualTo :: format(){
	return this->left_->format() + " = " + this->right_->format();
}