#include <bits/stdc++.h>
using namespace std;

extern bool sem_ok;

enum VAL_TYPE { VT_INT, VT_FLOAT, VT_BOOL, VT_VAR };
class Value {
public:
  VAL_TYPE tp;
  VAL_TYPE get_value_type();
  VAL_TYPE get_type();
  virtual string get_var() = 0;
};
class Int : public Value {
public:
  int ival;
  Int (int x) : ival(x) { tp = VT_INT; }
  string get_var();
};
class Float : public Value {
public:
  double fval;
  Float (double x) : fval(x) { tp = VT_FLOAT; }
  string get_var();
};
class Bool : public Value {
public:
  bool bval;
  Bool (bool x) : bval(x) { tp = VT_BOOL; }  
  string get_var();
};
class Var : public Value {
public:
  string sval;
  Var (char *x) : sval(x) { tp = VT_VAR; }
  string get_var();
};



enum EXP_TYPE { ET_AND, ET_OR, ET_EQ, ET_NEQ, ET_LT, ET_GT, ET_LEQ, ET_GEQ, ET_NOT, ET_MIN, ET_ADD, ET_SUB, ET_MUL, ET_DIV, ET_POW, ET_MOD, ET_VAL };
class Exp {
public:
  EXP_TYPE tp;
  Exp *x1, *x2;
  Value *v1;
  Exp (EXP_TYPE t, Exp *p1, Exp *p2) : tp(t), x1(p1), x2(p2) { }
  Exp (EXP_TYPE t, Value *z1) : tp(t), v1(z1) { }
  virtual VAL_TYPE get_type() = 0;
  virtual bool semantic_analysis() = 0;
};
// Variables...
class Exp_Val : public Exp {
public:
  Exp_Val (Value *v) : Exp(ET_VAL, v) { sem_ok = sem_ok && semantic_analysis(); }
  VAL_TYPE get_type();
  bool semantic_analysis();
};
// Numeric Expressions...
class Exp_Add : public Exp {
public:
  Exp_Add (Exp *p1, Exp *p2) : Exp(ET_ADD, p1, p2) { sem_ok = sem_ok && semantic_analysis(); }
  VAL_TYPE get_type();
  bool semantic_analysis();
};
class Exp_Sub : public Exp {
public:
  Exp_Sub (Exp *p1, Exp *p2) : Exp(ET_SUB, p1, p2) { sem_ok = sem_ok && semantic_analysis(); }
  VAL_TYPE get_type();
  bool semantic_analysis();
};
class Exp_Mul : public Exp {
public:
  Exp_Mul (Exp *p1, Exp *p2) : Exp(ET_MUL, p1, p2) { sem_ok = sem_ok && semantic_analysis(); }
  VAL_TYPE get_type();
  bool semantic_analysis();
};
class Exp_Div : public Exp {
public:
  Exp_Div (Exp *p1, Exp *p2) : Exp(ET_DIV, p1, p2) { sem_ok = sem_ok && semantic_analysis(); }
  VAL_TYPE get_type();
  bool semantic_analysis();
};
class Exp_Pow : public Exp {
public:
  Exp_Pow (Exp *p1, Exp *p2) : Exp(ET_POW, p1, p2) { sem_ok = sem_ok && semantic_analysis(); }
  VAL_TYPE get_type();
  bool semantic_analysis();
};
class Exp_Mod : public Exp {
public:
  Exp_Mod (Exp *p1, Exp *p2) : Exp(ET_MOD, p1, p2) { sem_ok = sem_ok && semantic_analysis(); }
  VAL_TYPE get_type();
  bool semantic_analysis();
};
class Exp_Min : public Exp {
public:
  Exp_Min (Value *v) : Exp(ET_MIN, v) { sem_ok = sem_ok && semantic_analysis(); }
  VAL_TYPE get_type();
  bool semantic_analysis();
};
// Boolean Expressions...
class Exp_And : public Exp {
public:
  Exp_And (Exp *p1, Exp *p2) : Exp(ET_AND, p1, p2) { sem_ok = sem_ok && semantic_analysis(); }
  VAL_TYPE get_type();
  bool semantic_analysis();
};
class Exp_Or : public Exp {
public:
  Exp_Or (Exp *p1, Exp *p2) : Exp(ET_OR, p1, p2) { sem_ok = sem_ok && semantic_analysis(); }
  VAL_TYPE get_type();
  bool semantic_analysis();
};
class Exp_Eq : public Exp {
public:
  Exp_Eq (Exp *p1, Exp *p2) : Exp(ET_EQ, p1, p2) { sem_ok = sem_ok && semantic_analysis(); }
  VAL_TYPE get_type();
  bool semantic_analysis();
};
class Exp_Neq : public Exp {
public:
  Exp_Neq (Exp *p1, Exp *p2) : Exp(ET_NEQ, p1, p2) { sem_ok = sem_ok && semantic_analysis(); }
  VAL_TYPE get_type();
  bool semantic_analysis();
};
class Exp_Lt : public Exp {
public:
  Exp_Lt (Exp *p1, Exp *p2) : Exp(ET_LT, p1, p2) { sem_ok = sem_ok && semantic_analysis(); }
  VAL_TYPE get_type();
  bool semantic_analysis();
};
class Exp_Gt : public Exp {
public:
  Exp_Gt (Exp *p1, Exp *p2) : Exp(ET_GT, p1, p2) { sem_ok = sem_ok && semantic_analysis(); }
  VAL_TYPE get_type();
  bool semantic_analysis();
};
class Exp_Leq : public Exp {
public:
  Exp_Leq (Exp *p1, Exp *p2) : Exp(ET_LEQ, p1, p2) { sem_ok = sem_ok && semantic_analysis(); }
  VAL_TYPE get_type();
  bool semantic_analysis();
};
class Exp_Geq : public Exp {
public:
  Exp_Geq (Exp *p1, Exp *p2) : Exp(ET_GEQ, p1, p2) { sem_ok = sem_ok && semantic_analysis(); }
  VAL_TYPE get_type();
  bool semantic_analysis();
};
class Exp_Not : public Exp {
public:
  Exp_Not (Exp *p1) : Exp(ET_NOT, p1, NULL) { sem_ok = sem_ok && semantic_analysis(); }
  VAL_TYPE get_type();
  bool semantic_analysis();
};


class Lst {
public:
  Exp *xp;
  Lst *next;
  Lst (Exp *x1) : xp(x1) { next = NULL; }
  Lst (Exp *x1, Lst *rst) : xp(x1), next(rst) { }
};

class ElseIf;

enum CMD_TYPE { CT_ATR, CT_SEQ, CT_PRINT, CT_WHILE, CT_IF };
class Cmd {
public:
  CMD_TYPE tp;
  Var *v1;
  Exp *x1;
  Cmd *c1, *c2;
  Lst *lst;
  ElseIf *el;
  Cmd (CMD_TYPE t) : tp(t) { }
  virtual bool semantic_analysis() = 0;
};
class Cmd_Atr : public Cmd {
public:
  Cmd_Atr (Var *z, Exp *p1) : Cmd(CT_ATR) { v1 = z; x1 = p1; sem_ok = sem_ok && semantic_analysis(); }
  bool semantic_analysis();
};
class Cmd_Seq : public Cmd {
public:
  Cmd_Seq (Cmd *r1, Cmd *r2) : Cmd(CT_SEQ) { c1 = r1; c2 = r2; sem_ok = sem_ok && semantic_analysis(); } 
  bool semantic_analysis();
};
class Cmd_Print : public Cmd {
public:
  Cmd_Print (Lst *ls) : Cmd(CT_PRINT) { lst = ls; sem_ok = sem_ok && semantic_analysis(); }
  bool semantic_analysis();
};
class Cmd_While : public Cmd {
public:
  Cmd_While (Exp *p1, Cmd *r1) : Cmd(CT_WHILE) { x1 = p1; c1 = r1; sem_ok = sem_ok && semantic_analysis(); }
  bool semantic_analysis();
};
class Cmd_If : public Cmd {
public:
  Cmd_If (Exp *p1, Cmd *r1) : Cmd(CT_IF) { x1 = p1; c1 = r1; el = NULL; sem_ok = sem_ok && semantic_analysis(); }
  Cmd_If (Exp *p1, Cmd *r1, ElseIf *ei) : Cmd(CT_IF) { x1 = p1; c1 = r1; el = ei; sem_ok = sem_ok && semantic_analysis(); } 
  Cmd_If (Exp *p1, Cmd *r1, ElseIf *ei, Cmd *r2) : Cmd(CT_IF) { x1 = p1; c1 = r1; el = ei; c2 = r2; sem_ok = sem_ok && semantic_analysis(); }
  bool semantic_analysis();
};


class ElseIf {
public:
  Exp *xp;
  Cmd *c;
  ElseIf *next;
  ElseIf (Exp *x1, Cmd *c1) : xp(x1), c(c1) { next = NULL; }
  ElseIf (Exp *x1, Cmd *c1, ElseIf *rst) : xp(x1), c(c1), next(rst) { }
};



class Prgm {
public:
  Cmd *c;
  Prgm (Cmd *c1) : c(c1) { }
};
