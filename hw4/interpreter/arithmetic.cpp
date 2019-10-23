#include "arithmetic.h"
using namespace std;

Constant :: Constant(int val) : val_(val){}
string Constant :: format(){
	return to_string(val_);
}

Variable :: Variable(string name, int val) : NumericExpression(){
    name_ = name;
    val_ = val;
}
// integervariable
IntegerVariable :: IntegerVariable(string name,int val) : Variable(name, val){
    name_ = name;
    val_ = val;
}
string IntegerVariable :: format(){return name_;}
// arrayvariable
ArrayVariable :: ArrayVariable(string name, NumericExpression *index, int val) : 
Variable(name, val) {
	name_ = name;
	index_ = index;
    val_ = val;
}
ArrayVariable :: ~ArrayVariable(){delete this->index_;}
string ArrayVariable :: format(){
    return name_ + "[" + this->index_->format() + "]";
}
// addition
AdditionExpression::AdditionExpression(NumericExpression* left, NumericExpression* right) :
NumericExpression(){
    left_ = left;
    right_ = right;
} 
AdditionExpression::~AdditionExpression() {
    delete this->left_;
    delete this->right_;
}
string AdditionExpression::format(){
    return "(" + this->left_->format() + " + " + this->right_->format() + ")";
}
// subtraction
SubtractionExpression::SubtractionExpression(NumericExpression* left, NumericExpression* right) :
NumericExpression(){
    left_ = left;
    right_ = right;
} 
SubtractionExpression::~SubtractionExpression() {
    delete this->left_;
    delete this->right_;
}
string SubtractionExpression::format(){
    return "(" + this->left_->format() + " - " + this->right_->format() + ")";
}
//multiplication
MultiplicationExpression::MultiplicationExpression(NumericExpression* left, 
    NumericExpression* right) :
NumericExpression(){
    left_ = left;
    right_ = right;
} 
MultiplicationExpression::~MultiplicationExpression() {
    delete this->left_;
    delete this->right_;
}
string MultiplicationExpression::format(){
    return "(" + this->left_->format() + " * " + this->right_->format() + ")";
}
// division
DivisionExpression::DivisionExpression(NumericExpression* left, NumericExpression* right) :
NumericExpression(){
    left_ = left;
    right_ = right;
} 
DivisionExpression::~DivisionExpression() {
    delete this->left_;
    delete this->right_;
}
string DivisionExpression::format(){
    return "(" + this->left_->format() + " / " + this->right_->format() + ")";
}

// set value function
void Variable :: set_value(NumericExpression* nexp){
    val_ = nexp->get_value();
}

// get_value functions
int Constant :: get_value(){
    return val_;
}
int Variable :: get_value(){
    return val_;
}
int AdditionExpression :: get_value(){
    return left_->get_value() + right_->get_value();
}
int SubtractionExpression :: get_value(){
    return left_->get_value() - right_->get_value();
}
int MultiplicationExpression :: get_value(){
    return left_->get_value() * right_->get_value();
}
int DivisionExpression :: get_value(){
    return left_->get_value() / right_->get_value();
}

// get name function
string Variable :: get_name(){
    return name_;
}