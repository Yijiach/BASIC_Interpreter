#include "command.h"
using namespace std;
Command :: Command(int line) : line_(line){}
//print
Print :: Print(int line, NumericExpression* nexp) : Command(line){
	line_ = line;
	nexp_ = nexp;
}
Print :: ~Print(){delete this->nexp_;}
string Print :: format(){
	return "PRINT " + this->nexp_->format();
}
//let
Let :: Let(int line, Variable* var, NumericExpression* nexp) : Command(line){
	line_ = line;
	var_ = var;
	nexp_ = nexp;
}
	
Let :: ~Let(){
	delete this->var_;
	delete this->nexp_;
}
NumericExpression* Let :: get_var(){return var_;}
string Let :: format(){
	return "LET " + this->var_->format() + " " + this->nexp_->format();
}
//goto
GoTo :: GoTo(int line, int jline) : Command(line){
	line_ = line;
	jline_ = jline;
}
string GoTo :: format(){
	return "GOTO " + to_string(jline_);
}
//ifthen
IfThen :: IfThen(int line, BooleanExpression* bexp, int jline) : Command(line){
	line_ = line;
	bexp_ = bexp;
	jline_ = jline;
}
IfThen :: ~IfThen(){delete this->bexp_;}
string IfThen :: format(){
	return "IF [" + this->bexp_->format() + "] THEN <" + to_string(jline_) + ">";
}
//gosub
GoSub :: GoSub(int line, int jline) : Command(line){
	line_ = line;
	jline_ = jline;
}
string GoSub :: format(){
	return "GOSUB " + to_string(jline_);
}
//return
Return :: Return(int line) : Command(line){
	line_ = line;
}
string Return :: format(){return "RETURN";}
//end
End :: End(int line) : Command(line){
	line_ = line;
}
string End :: format(){return "END";}