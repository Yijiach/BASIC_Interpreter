#include "command.h"
using namespace std;
Command :: Command(int line) : line_(line){}

//print
Print :: Print(int line, NumericExpression* nexp) : Command(line){
	line_ = line;
	nexp_ = nexp;
}
Print :: ~Print(){//don't delete in destructos, delete in interperter
	//delete this->nexp_;
}
string Print :: format(){
	return to_string(line_) + " PRINT " + this->nexp_->format();
}
//let
Let :: Let(int line, Variable* var, NumericExpression* nexp) : Command(line){
	line_ = line;
	var_ = var;
	nexp_ = nexp;
}
Let :: ~Let(){//don't delete in destructos, delete in interperter
	// delete this->var_;
	// delete this->nexp_;
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
IfThen :: ~IfThen(){//don't delete in destructos, delete in interperter
	//delete this->bexp_;
}
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

// get line
int Command :: get_line(){
	return line_;
}

// get name of the command
string Print :: get_name(){
	return "PRINT";
}
string Let :: get_name(){
	return "LET";
}
string GoTo :: get_name(){
	return "GOTO";
}
string IfThen :: get_name(){
	return "IF";
}
string GoSub :: get_name(){
	return "GOSUB";
}
string Return :: get_name(){
	return "RETURN";
}
string End :: get_name(){
	return "END";
}

// get nexp, vars, bexp, jline stored in commands
NumericExpression* Print :: get_nexp(){
	return nexp_;
}
Variable* Let :: get_var(){
	return var_;
}
NumericExpression* Let :: get_nexp(){
	return nexp_;
}
int GoTo :: get_jline(){
	return jline_;
}
BooleanExpression* IfThen :: get_bexp(){
	return bexp_;
}
int IfThen :: get_jline(){
	return jline_;
}
int GoSub :: get_jline(){
	return jline_;
}