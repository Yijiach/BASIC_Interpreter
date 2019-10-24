#include "boolean.h"
using namespace std;
// larger
LargerThan :: LargerThan(NumericExpression *left, NumericExpression *right) : 
BooleanExpression(){
	left_ = left;
	right_ = right;
}
LargerThan :: ~LargerThan(){
	if (left_ != NULL){
        delete this->left_;
        left_ = NULL;
    }
    if (right_ != NULL){
        delete this->right_;
        right_ = NULL;
    }
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
LessThan :: ~LessThan(){
	if (left_ != NULL){
        delete this->left_;
        left_ = NULL;
    }
    if (right_ != NULL){
        delete this->right_;
        right_ = NULL;
    }
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
EqualTo :: ~EqualTo(){
	if (left_ != NULL){
        delete this->left_;
        left_ = NULL;
    }
    if (right_ != NULL){
        delete this->right_;
        right_ = NULL;
    }
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