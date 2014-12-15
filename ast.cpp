#include <bits/stdc++.h>
#include "ast.h"
#include "icg.h"
using namespace std;


map <string, VAL_TYPE> var_types;


VAL_TYPE Value::get_type(){
  return tp;
}
VAL_TYPE Value::get_value_type(){
  if(tp == VT_VAR)
    return var_types[str()];
  return tp;
}

string Int::str(){
  return to_string(ival);
}
string Float::str(){
  return to_string(fval);
}
string Bool::str(){
  if(bval) return "true";
  else return "false";
}
string Var::str(){
  return sval;
}



VAL_TYPE Exp_Val::get_type(){
  if(rt == VT_UNK)
    return (rt = v1->get_value_type());
  return rt;
}
VAL_TYPE Exp_Add::get_type(){
  if(rt == VT_UNK){
    VAL_TYPE tp1 = x1->get_type();
    VAL_TYPE tp2 = x2->get_type();
    if(tp1 == VT_FLOAT || tp2 == VT_FLOAT)
      return (rt = VT_FLOAT);
    return (rt = VT_INT);
  }
  return rt;
}
VAL_TYPE Exp_Sub::get_type(){
  if(rt == VT_UNK){
    VAL_TYPE tp1 = x1->get_type();
    VAL_TYPE tp2 = x2->get_type();
    if(tp1 == VT_FLOAT || tp2 == VT_FLOAT)
      return (rt = VT_FLOAT);
    return (rt = VT_INT);
  }
  return rt;
}
VAL_TYPE Exp_Mul::get_type(){
  if(rt == VT_UNK){
    VAL_TYPE tp1 = x1->get_type();
    VAL_TYPE tp2 = x2->get_type();
    if(tp1 == VT_FLOAT || tp2 == VT_FLOAT)
      return (rt = VT_FLOAT);
    return (rt = VT_INT);
  }
  return rt;
}
VAL_TYPE Exp_Div::get_type(){
  if(rt == VT_UNK){
    VAL_TYPE tp1 = x1->get_type();
    VAL_TYPE tp2 = x2->get_type();
    if(tp1 == VT_FLOAT || tp2 == VT_FLOAT)
      return (rt = VT_FLOAT);
    return (rt = VT_INT);
  }
  return rt;
}
VAL_TYPE Exp_Pow::get_type(){
  if(rt == VT_UNK){
    VAL_TYPE tp1 = x1->get_type();
    VAL_TYPE tp2 = x2->get_type();
    if(tp1 == VT_FLOAT || tp2 == VT_FLOAT)
      return (rt = VT_FLOAT);
    return (rt = VT_INT);
  }
  return rt;
}
VAL_TYPE Exp_Mod::get_type(){
  if(rt == VT_UNK){
    VAL_TYPE tp1 = x1->get_type();
    VAL_TYPE tp2 = x2->get_type();
    if(tp1 == VT_FLOAT || tp2 == VT_FLOAT)
      return (rt = VT_FLOAT);
    return (rt = VT_INT);
  }
  return rt;
}
VAL_TYPE Exp_Min::get_type(){
  if(rt == VT_UNK)
    return (rt = x1->get_type());
  return rt;
}
VAL_TYPE Exp_And::get_type(){
  return VT_BOOL;
}
VAL_TYPE Exp_Or::get_type(){
  return VT_BOOL;
}
VAL_TYPE Exp_Eq::get_type(){
  return VT_BOOL;
}
VAL_TYPE Exp_Neq::get_type(){
  return VT_BOOL;
}
VAL_TYPE Exp_Lt::get_type(){
  return VT_BOOL;
}
VAL_TYPE Exp_Gt::get_type(){
  return VT_BOOL;
}
VAL_TYPE Exp_Leq::get_type(){
  return VT_BOOL;
}
VAL_TYPE Exp_Geq::get_type(){
  return VT_BOOL;
}
VAL_TYPE Exp_Not::get_type(){
  return VT_BOOL;
}

extern int line_num;
bool Exp_Val::semantic_analysis(){
  if(v1->get_type() == VT_VAR && var_types.find(v1->str()) == var_types.end()){
    fprintf(stderr, "ERROR, Variable \"%s\" used without initialization on line %d!\n", v1->str().c_str(), line_num);
    return false;
  }
  return true;
}
bool Exp_Add::semantic_analysis(){
  return true;
}
bool Exp_Sub::semantic_analysis(){
  return true;
}
bool Exp_Mul::semantic_analysis(){
  return true;
}
bool Exp_Div::semantic_analysis(){
  return true;
}
bool Exp_Pow::semantic_analysis(){
  return true;
}
bool Exp_Mod::semantic_analysis(){
  return true;
}
bool Exp_Min::semantic_analysis(){
  return true;
}
bool Exp_And::semantic_analysis(){
  return true;
}
bool Exp_Or::semantic_analysis(){
  return true;
}
bool Exp_Eq::semantic_analysis(){
  return true;
}
bool Exp_Neq::semantic_analysis(){
  return true;
}
bool Exp_Lt::semantic_analysis(){
  return true;
}
bool Exp_Gt::semantic_analysis(){
  return true;
}
bool Exp_Leq::semantic_analysis(){
  return true;
}
bool Exp_Geq::semantic_analysis(){
  return true;
}
bool Exp_Not::semantic_analysis(){
  return true;
}



bool Cmd_Atr::semantic_analysis(){
  var_types[v1->str()] = x1->get_type();
  return true;
}
bool Cmd_Seq::semantic_analysis(){
  return true;
}
bool Cmd_Print::semantic_analysis(){
  return true;
}
bool Cmd_While::semantic_analysis(){
  if(x1->get_type() != VT_BOOL){
    fprintf(stderr, "ERROR, while condition should be a boolean expression on line %d!\n", line_num);
    return false;
  }
  return true;
}
bool Cmd_If::semantic_analysis(){
  if(x1->get_type() != VT_BOOL){
    fprintf(stderr, "ERROR, if condition should be a boolean expression on line %d!\n", line_num);
    return false;
  }
  return true;
}
bool Cmd_IfElse::semantic_analysis(){
  if(x1->get_type() != VT_BOOL){
    fprintf(stderr, "ERROR, if condition should be a boolean expression on line %d!\n", line_num);
    return false;
  }
  return true;
}



bool ElseIf::semantic_analysis(){
  if(xp->get_type() != VT_BOOL){
    fprintf(stderr, "ERROR, if condition should be a boolean expression on line %d!\n", line_num);
    return false;
  }
  return true;
}


