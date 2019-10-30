#include "boolean.h"
using namespace std;
// larger
LargerThan :: LargerThan(NumericExpression *left, NumericExpression *right) : 
BooleanExpression(){
	left_ = left;
	right_ = right;
}
LargerThan :: ~LargerThan(){ // don't delete in destructors, delete in interpreter
	// delete this->left_;
	// delete this->right_;
}
string LargerThan :: format(){
	return this->left_->format() + " > " + this->right_->format();
}
// less
LessThan :: LessThan(NumericExpression *left, NumericExpression *right) : 
BooleanExpression(){
	left_ = left;
	right_ = right;
}
LessThan :: ~LessThan(){ // don't delete in destructors, delete in interpreter
	// delete this->left_;
 	// delete this->right_;
}
string LessThan :: format(){
	return this->left_->format() + " < " + this->right_->format();
}
 // equal
EqualTo :: EqualTo(NumericExpression *left, NumericExpression *right) : 
BooleanExpression(){
	left_ = left;
	right_ = right;
}
EqualTo :: ~EqualTo(){ // don't delete in destructors, delete in interpreter
	// delete this->left_;
 //    delete this->right_;
}
string EqualTo :: format(){
	return this->left_->format() + " = " + this->right_->format();
}

// get value functions
bool LargerThan :: get_value(){
	if (left_->get_value() > right_->get_value()) return true;
	return false;
}
bool LessThan :: get_value(){
	if (left_->get_value() < right_->get_value()) return true;
	return false;
}
bool EqualTo :: get_value(){
	if (left_->get_value() == right_->get_value()) return true;
	return false;
}