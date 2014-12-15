#include <bits/stdc++.h>
#include "ast.h"
#include "icg.h"
using namespace std;


unsigned int Label::cnt = 0;
unsigned int TempAddr::cnt = 0;
vector <Tac*> tac_code;

Addr* Exp_Val::gen_code(){
  return (new ValAddr(v1));
}
void Exp_Val::gen_jmp_code(string ylbl, string nlbl){
  return;
}

Addr* Exp_Add::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  //printf("\t%s = %s + %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_ADD, res, lr, rr));
  delete lr;
  delete rr;
  return res;
}
void Exp_Add::gen_jmp_code(string ylbl, string nlbl){
  return;
}
Addr* Exp_Sub::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  //printf("\t%s = %s - %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_SUB, res, lr, rr));
  delete lr;
  delete rr;
  return res;
}
void Exp_Sub::gen_jmp_code(string ylbl, string nlbl){
  return;
}
Addr* Exp_Mul::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  //printf("\t%s = %s * %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_MUL, res, lr, rr));
  delete lr;
  delete rr;
  return res;
}
void Exp_Mul::gen_jmp_code(string ylbl, string nlbl){
  return;
}
Addr* Exp_Div::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  //printf("\t%s = %s / %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_DIV, res, lr, rr));
  delete lr;
  delete rr;
  return res;
}
void Exp_Div::gen_jmp_code(string ylbl, string nlbl){
  return;
}
Addr* Exp_Pow::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  //printf("\t%s = %s ^ %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_POW, res, lr, rr));
  delete lr;
  delete rr;
  return res;
}
void Exp_Pow::gen_jmp_code(string ylbl, string nlbl){
  return;
}
Addr* Exp_Mod::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  //printf("\t%s = %s \% %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_MOD, res, lr, rr));
  delete lr;
  delete rr;
  return res;
}
void Exp_Mod::gen_jmp_code(string ylbl, string nlbl){
  return;
}
Addr* Exp_Min::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *res = new TempAddr;
  //printf("\t%s = - %s\n", res->str().c_str(), lr->str().c_str());
  tac_code.push_back(new Tac(TC_MIN, res, lr, NULL));
  delete lr;
  return res;
}
void Exp_Min::gen_jmp_code(string ylbl, string nlbl){
  return;
}

Addr* Exp_And::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  //printf("\t%s = %s && %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_AND, res, lr, rr));
  delete lr;
  delete rr;
  return res;
}
void Exp_And::gen_jmp_code(string ylbl, string nlbl){
  Label rl;
  x1->gen_jmp_code(rl.str(), nlbl);
  //printf("%s:\n", rl.str().c_str());
  tac_code.push_back(new Tac(TC_LBL, new ConstAddr(rl.str()), NULL, NULL));
  x2->gen_jmp_code(ylbl, nlbl);
}
Addr* Exp_Or::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  //printf("\t%s = %s || %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_OR, res, lr, rr));
  delete lr;
  delete rr;
  return res;
}
void Exp_Or::gen_jmp_code(string ylbl, string nlbl){
  Label rl;
  x1->gen_jmp_code(ylbl, rl.str());
  //printf("%s:\n", rl.str().c_str());
  tac_code.push_back(new Tac(TC_LBL, new ConstAddr(rl.str()), NULL, NULL));
  x2->gen_jmp_code(ylbl, nlbl);
}
Addr* Exp_Eq::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  //printf("\t%s = %s == %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_EQ, res, lr, rr));
  delete lr;
  delete rr;
  return res;
}
void Exp_Eq::gen_jmp_code(string ylbl, string nlbl){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  //printf("\tif %s == %s goto %s\n", lr->str().c_str(), rr->str().c_str(), ylbl.c_str());
  tac_code.push_back(new Tac(TC_IFEQ, lr, rr, new ConstAddr(ylbl)));  
  //printf("\tgoto %s\n", nlbl.c_str());
  tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(nlbl), NULL, NULL));
  delete lr;
  delete rr;
}
Addr* Exp_Neq::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  //printf("\t%s = %s != %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_NEQ, res, lr, rr));
  delete lr;
  delete rr;
  return res;
}
void Exp_Neq::gen_jmp_code(string ylbl, string nlbl){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  //printf("\tif %s != %s goto %s\n", lr->str().c_str(), rr->str().c_str(), ylbl.c_str());
  tac_code.push_back(new Tac(TC_IFNEQ, lr, rr, new ConstAddr(ylbl)));  
  //printf("\tgoto %s\n", nlbl.c_str());
  tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(nlbl), NULL, NULL));
  delete lr;
  delete rr;
}
Addr* Exp_Lt::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  //printf("\t%s = %s < %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_LT, res, lr, rr));
  delete lr;
  delete rr;
  return res;
}
void Exp_Lt::gen_jmp_code(string ylbl, string nlbl){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  //printf("\tif %s < %s goto %s\n", lr->str().c_str(), rr->str().c_str(), ylbl.c_str());
  tac_code.push_back(new Tac(TC_IFLT, lr, rr, new ConstAddr(ylbl)));  
  //printf("\tgoto %s\n", nlbl.c_str());
  tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(nlbl), NULL, NULL));
  delete lr;
  delete rr;
}
Addr* Exp_Gt::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  //printf("\t%s = %s > %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_GT, res, lr, rr));
  delete lr;
  delete rr;
  return res;
}
void Exp_Gt::gen_jmp_code(string ylbl, string nlbl){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  //printf("\tif %s > %s goto %s\n", lr->str().c_str(), rr->str().c_str(), ylbl.c_str());
  tac_code.push_back(new Tac(TC_IFGT, lr, rr, new ConstAddr(ylbl)));  
  //printf("\tgoto %s\n", nlbl.c_str());
  tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(nlbl), NULL, NULL));
  delete lr;
  delete rr;
}
Addr* Exp_Leq::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  //printf("\t%s = %s <= %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_LEQ, res, lr, rr));
  delete lr;
  delete rr;
  return res;
}
void Exp_Leq::gen_jmp_code(string ylbl, string nlbl){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  //printf("\tif %s <= %s goto %s\n", lr->str().c_str(), rr->str().c_str(), ylbl.c_str());
  tac_code.push_back(new Tac(TC_IFLEQ, lr, rr, new ConstAddr(ylbl)));  
  //printf("\tgoto %s\n", nlbl.c_str());
  tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(nlbl), NULL, NULL));
  delete lr;
  delete rr;
}
Addr* Exp_Geq::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  //printf("\t%s = %s >= %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_GEQ, res, lr, rr));
  delete lr;
  delete rr;
  return res;
}
void Exp_Geq::gen_jmp_code(string ylbl, string nlbl){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  //printf("\tif %s >= %s goto %s\n", lr->str().c_str(), rr->str().c_str(), ylbl.c_str());
  tac_code.push_back(new Tac(TC_IFGEQ, lr, rr, new ConstAddr(ylbl)));  
  //printf("\tgoto %s\n", nlbl.c_str());
  tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(nlbl), NULL, NULL));
  delete lr;
  delete rr;
}
Addr* Exp_Not::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *res = new TempAddr;
  //printf("\t%s = ! %s\n", res->str().c_str(), lr->str().c_str());
  tac_code.push_back(new Tac(TC_NOT, res, lr, NULL));
  delete lr;
  return res;
}
void Exp_Not::gen_jmp_code(string ylbl, string nlbl){
  x1->gen_jmp_code(nlbl, ylbl);
}



void Cmd_Atr::gen_code(string lbl_nxt){
  Addr *res = x1->gen_code();
  //printf("\t%s = %s\n", v1->str().c_str(), res->str().c_str());
  tac_code.push_back(new Tac(TC_ATR, new ValAddr(v1), res, NULL));  
  delete res;
}
void Cmd_Seq::gen_code(string lbl_nxt){
  Label med;
  c1->gen_code(med.str());
  //printf("%s:\n", med.str().c_str());
  tac_code.push_back(new Tac(TC_LBL, new ConstAddr(med.str()), NULL, NULL));
  c2->gen_code(lbl_nxt);
}
void Cmd_Print::gen_code(string lbl_nxt){
  Lst *cur = lst;
  while(cur != NULL){
    Addr *res = cur->xp->gen_code();
    //printf("\tprint %s\n", res->str().c_str());
    tac_code.push_back(new Tac(TC_PRINT, res, NULL, NULL));
    cur = cur->next;
  }
  //printf("\tprint '\\n'\n");
  tac_code.push_back(new Tac(TC_PRINT_ENDL, NULL, NULL, NULL));
}
void Cmd_While::gen_code(string lbl_nxt){
  Label top, body;
  //printf("%s:\n", top.str().c_str());
  tac_code.push_back(new Tac(TC_LBL, new ConstAddr(top.str()), NULL, NULL));
  x1->gen_jmp_code(body.str(), lbl_nxt);
  //printf("%s:\n", body.str().c_str());
  tac_code.push_back(new Tac(TC_LBL, new ConstAddr(body.str()), NULL, NULL));
  c1->gen_code(top.str());
  //printf("\tgoto %s\n", top.str().c_str());
  tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(top.str()), NULL, NULL));
}
void Cmd_If::gen_code(string lbl_nxt){
  if(el == NULL){
    Label body;
    x1->gen_jmp_code(body.str(), lbl_nxt);
    //printf("%s:\n", body.str().c_str());
    tac_code.push_back(new Tac(TC_LBL, new ConstAddr(body.str()), NULL, NULL));
    c1->gen_code(lbl_nxt);
  }
  else{
    Label then_lbl, else_lbl;
    x1->gen_jmp_code(then_lbl.str(), else_lbl.str());
    //printf("%s:\n", then_lbl.str().c_str());
    tac_code.push_back(new Tac(TC_LBL, new ConstAddr(then_lbl.str()), NULL, NULL));
    c1->gen_code(lbl_nxt);
    //printf("\tgoto %s\n", lbl_nxt.c_str());
    tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(lbl_nxt), NULL, NULL));
    //printf("%s:\n", else_lbl.str().c_str());
    tac_code.push_back(new Tac(TC_LBL, new ConstAddr(else_lbl.str()), NULL, NULL));
    ElseIf *cur = el;
    while(cur != NULL){
      Label t1, e1;
      cur->xp->gen_jmp_code(t1.str(), e1.str());
      //printf("%s:\n", t1.str().c_str());
      tac_code.push_back(new Tac(TC_LBL, new ConstAddr(t1.str()), NULL, NULL));
      cur->c->gen_code(lbl_nxt);
      //printf("\tgoto %s\n", lbl_nxt.c_str());
      tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(lbl_nxt), NULL, NULL));
      if(cur->next != NULL){
        //printf("%s:\n", e1.str().c_str());
        tac_code.push_back(new Tac(TC_LBL, new ConstAddr(e1.str()), NULL, NULL));
      }
      cur = cur->next;
    }
  }
}
void Cmd_IfElse::gen_code(string lbl_nxt){
  if(el == NULL){
    Label then_lbl, else_lbl;
    x1->gen_jmp_code(then_lbl.str(), else_lbl.str());
    //printf("%s:\n", then_lbl.str().c_str());
    tac_code.push_back(new Tac(TC_LBL, new ConstAddr(then_lbl.str()), NULL, NULL));
    c1->gen_code(lbl_nxt);
    //printf("\tgoto %s\n", lbl_nxt.c_str());
    tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(lbl_nxt), NULL, NULL));
    //printf("%s:\n", else_lbl.str().c_str());
    tac_code.push_back(new Tac(TC_LBL, new ConstAddr(else_lbl.str()), NULL, NULL));
    c2->gen_code(lbl_nxt);
  }
  else{
    Label then_lbl, else_lbl;
    x1->gen_jmp_code(then_lbl.str(), else_lbl.str());
    //printf("%s:\n", then_lbl.str().c_str());
    tac_code.push_back(new Tac(TC_LBL, new ConstAddr(then_lbl.str()), NULL, NULL));
    c1->gen_code(lbl_nxt);
    //printf("\tgoto %s\n", lbl_nxt.c_str());
    tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(lbl_nxt), NULL, NULL));
    //printf("%s:\n", else_lbl.str().c_str());
    tac_code.push_back(new Tac(TC_LBL, new ConstAddr(else_lbl.str()), NULL, NULL));
    ElseIf *cur = el;
    while(cur != NULL){
      Label t1, e1;
      cur->xp->gen_jmp_code(t1.str(), e1.str());
      //printf("%s:\n", t1.str().c_str());
      tac_code.push_back(new Tac(TC_LBL, new ConstAddr(t1.str()), NULL, NULL));
      cur->c->gen_code(lbl_nxt);
      //printf("\tgoto %s\n", lbl_nxt.c_str());
      tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(lbl_nxt), NULL, NULL));
      //printf("%s:\n", e1.str().c_str());
      tac_code.push_back(new Tac(TC_LBL, new ConstAddr(e1.str()), NULL, NULL));
      cur = cur->next;
    }
    c2->gen_code(lbl_nxt);
  }
}


void Prgm::gen_code(){
  Label lbl;
  c->gen_code(lbl.str());
  //printf("%s:\n", lbl.str().c_str());
  tac_code.push_back(new Tac(TC_LBL, new ConstAddr(lbl.str()), NULL, NULL));
}


void ast_to_tac(Prgm *r){
  tac_code.clear();
  r->gen_code();
  return;
}


void Tac::gen_mips(){
  switch(op){
    
  case TC_PRINT:
    break;
  case TC_PRINT_ENDL: 
    break;

  case TC_ADD:
    break;
  case TC_SUB:
    break;
  case TC_MUL:
    break;
  case TC_DIV:
    break;
  case TC_POW:
    break;
  case TC_MOD:
    break;
  case TC_MIN:
    break;

  case TC_AND:
    break;
  case TC_OR:
    break;
  case TC_EQ:
    break;
  case TC_NEQ:
    break;
  case TC_LT:
    break;
  case TC_GT:
    break;
  case TC_LEQ:
    break;
  case TC_GEQ:
    break;
  case TC_NOT:
    break;

  case TC_ATR:
    break;
  case TC_LBL:
    break;
  case TC_GOTO:
    break;
  case TC_IFEQ:
    break;
  case TC_IFNEQ:
    break;
  case TC_IFLT:
    break;
  case TC_IFGT:
    break;
  case TC_IFLEQ:
    break;
  case TC_IFGEQ:
    break;
  }
}


void tac_to_mips(){  
  for(int i = 0; i < (int)tac_code.size(); i ++)
    tac_code[i]->gen_mips();
}


void compile(Prgm *r){
  ast_to_tac(r);
  tac_to_mips();
}
