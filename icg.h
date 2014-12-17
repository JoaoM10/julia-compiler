#include <bits/stdc++.h>
using namespace std;

class Label {
  static unsigned int cnt;
  const unsigned int lnum;
public:
  Label () : lnum(cnt ++) { }
  string str() const {
    return ("L" + to_string(lnum));
  }
};



class Addr {
public:
  virtual string str() = 0;
  virtual VAL_TYPE get_type() = 0;
};
class TempAddr : public Addr {
  static unsigned int cnt;
  const unsigned int lnum;
public:
  TempAddr () : lnum(cnt ++) { }
  string str(){
    return ("$t" + to_string(lnum));
  }
  VAL_TYPE get_type(){
    return VT_UNK;
  }
};
class ValAddr : public Addr {
  Value *v;
public:
  ValAddr (Value *v1) : v(v1) { }
  string str(){
    return v->str();
  }
  VAL_TYPE get_type(){
    return v->get_type();
  }
};
class ConstAddr : public Addr {
  string s;
public:
  ConstAddr (string x) : s(x) { }
  string str(){
    return s;
  }
  VAL_TYPE get_type(){
    return VT_UNK;
  }
};




enum TC_OP { TC_PRINT, TC_PRINT_ENDL, TC_ADD, TC_SUB, TC_MUL, TC_DIV, TC_POW, TC_MOD, TC_MIN, TC_AND, TC_OR, TC_EQ, TC_NEQ, TC_LT, TC_GT, TC_LEQ, TC_GEQ, TC_NOT, TC_ATR, TC_LBL, TC_GOTO, TC_IFEQ, TC_IFNEQ, TC_IFLT, TC_IFGT, TC_IFLEQ, TC_IFGEQ, TC_LOAD };
class Tac {
public:
  TC_OP op;
  Addr *r1, *r2, *r3;
  Tac (TC_OP t, Addr *t1, Addr *t2, Addr *t3) : op(t), r1(t1), r2(t2), r3(t3) { }
  void gen_mips(void);
};



void compile(Prgm*, bool, char*);
