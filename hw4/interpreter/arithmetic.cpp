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
ArrayVariable :: ~ArrayVariable(){
    if (index_ != NULL){
        delete this->index_;
        index_ = NULL;
    }
}  
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
    if (left_ != NULL){
        delete this->left_;
        left_ = NULL;
    }
    if (right_ != NULL){
        delete this->right_;
        right_ = NULL;
    }
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
    if (left_ != NULL){
        delete this->left_;
        left_ = NULL;
    }
    if (right_ != NULL){
        delete this->right_;
        right_ = NULL;
    }
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
    if (left_ != NULL){
        delete this->left_;
        left_ = NULL;
    }
    if (right_ != NULL){
        delete this->right_;
        right_ = NULL;
    }
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
    if (left_ != NULL){
        delete this->left_;
        left_ = NULL;
    }
    if (right_ != NULL){
        delete this->right_;
        right_ = NULL;
    }
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
    if (right_->get_value() == 0){
        string temp1 = "Division by 0: ";
        string temp2 = to_string(left_->get_value());
        string temp3 = " = ";
        string temp4 = to_string(right_->get_value());
        string temp5 = ", ";
        string temp6 = ".";
        string temp = temp1 + left_->format() + temp3 + temp2 + temp5 + 
        right_->format() + temp3 + temp4 + temp6;
        // string temp = "Division by 0: " + left_->format() + " = " +
        //  left_->get_value() + ", " + right_->format() + " = " +
        //  right_->get_value() + ".";
         throw runtime_error(temp); // division by 0 error
    }
    return left_->get_value() / right_->get_value();
}

// get name function
string Variable :: get_name(){
    return name_;
}

// check whether arr or int
bool IntegerVariable :: is_arr(){
    return false;
}
bool ArrayVariable :: is_arr(){
    return true;
}

// get index
NumericExpression* ArrayVariable :: get_index(){
    return index_;
}