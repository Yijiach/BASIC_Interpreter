#include "command.h"
using namespace std;
Command :: Command(int line) : line_(line){}

NumericExpression* Command :: get_nexp(){
	return NULL; // virtual function
}
//print
Print :: Print(int line, NumericExpression* nexp) : Command(line){
	line_ = line;
	nexp_ = nexp;
}
Print :: ~Print(){delete this->nexp_;}
string Print :: format(){
	return to_string(line_) + " PRINT " + this->nexp_->format();
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
string Let :: format(){
	return to_string(line_) + 
	" LET " + this->var_->format() + " " + this->nexp_->format();
}
//goto
GoTo :: GoTo(int line, int jline) : Command(line){
	line_ = line;
	jline_ = jline;
}
string GoTo :: format(){
	return to_string(line_) + " GOTO <" + to_string(jline_) + ">";
}
//ifthen
IfThen :: IfThen(int line, BooleanExpression* bexp, int jline) : Command(line){
	line_ = line;
	bexp_ = bexp;
	jline_ = jline;
}
IfThen :: ~IfThen(){delete this->bexp_;}
string IfThen :: format(){
	return to_string(line_) + 
	" IF [" + this->bexp_->format() + "] THEN <" + to_string(jline_) + ">";
}
//gosub
GoSub :: GoSub(int line, int jline) : Command(line){
	line_ = line;
	jline_ = jline;
}
string GoSub :: format(){
	return to_string(line_) + " GOSUB <" + to_string(jline_) + ">";
}
//return
Return :: Return(int line) : Command(line){
	line_ = line;
}
string Return :: format(){return to_string(line_) + " RETURN";}
//end
End :: End(int line) : Command(line){
	line_ = line;
}
string End :: format(){return to_string(line_) + " END";}