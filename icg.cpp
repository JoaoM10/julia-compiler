#include <bits/stdc++.h>
#include "ast.h"
#include "icg.h"
#define PRINT_TAC 0
#define X first
#define Y second
using namespace std;

typedef pair <int, VAL_TYPE> piv;

              
unsigned int Label::cnt = 0;
unsigned int TempAddr::cnt = 0;
vector <Tac*> tac_code;
FILE *fout;
map <string, piv> var_tac_mips;
int var_sz = 0;

Addr* Exp_Val::gen_code(){
  if(v1->get_type() == VT_VAR)
    return (new ValAddr(v1));
  Addr *res = new TempAddr;
  if(PRINT_TAC) printf("\t%s = %s (load)\n", res->str().c_str(), v1->str().c_str());
  tac_code.push_back(new Tac(TC_LOAD, res, new ValAddr(v1), NULL));
  return res;  
}
void Exp_Val::gen_jmp_code(string ylbl, string nlbl){
  return;
}

Addr* Exp_Add::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  if(PRINT_TAC) printf("\t%s = %s + %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_ADD, res, lr, rr));
  return res;
}
void Exp_Add::gen_jmp_code(string ylbl, string nlbl){
  return;
}
Addr* Exp_Sub::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  if(PRINT_TAC) printf("\t%s = %s - %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_SUB, res, lr, rr));
  return res;
}
void Exp_Sub::gen_jmp_code(string ylbl, string nlbl){
  return;
}
Addr* Exp_Mul::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  if(PRINT_TAC) printf("\t%s = %s * %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_MUL, res, lr, rr));
  return res;
}
void Exp_Mul::gen_jmp_code(string ylbl, string nlbl){
  return;
}
Addr* Exp_Div::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  if(PRINT_TAC) printf("\t%s = %s / %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_DIV, res, lr, rr));
  return res;
}
void Exp_Div::gen_jmp_code(string ylbl, string nlbl){
  return;
}
Addr* Exp_Pow::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  if(PRINT_TAC) printf("\t%s = %s ^ %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_POW, res, lr, rr));
  return res;
}
void Exp_Pow::gen_jmp_code(string ylbl, string nlbl){
  return;
}
Addr* Exp_Mod::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  if(PRINT_TAC) printf("\t%s = %s \% %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_MOD, res, lr, rr));
  return res;
}
void Exp_Mod::gen_jmp_code(string ylbl, string nlbl){
  return;
}
Addr* Exp_Min::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *res = new TempAddr;
  if(PRINT_TAC) printf("\t%s = - %s\n", res->str().c_str(), lr->str().c_str());
  tac_code.push_back(new Tac(TC_MIN, res, lr, NULL));
  return res;
}
void Exp_Min::gen_jmp_code(string ylbl, string nlbl){
  return;
}

Addr* Exp_And::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  if(PRINT_TAC) printf("\t%s = %s && %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_AND, res, lr, rr));
  return res;
}
void Exp_And::gen_jmp_code(string ylbl, string nlbl){
  Label rl;
  x1->gen_jmp_code(rl.str(), nlbl);
  if(PRINT_TAC) printf("%s:\n", rl.str().c_str());
  tac_code.push_back(new Tac(TC_LBL, new ConstAddr(rl.str()), NULL, NULL));
  x2->gen_jmp_code(ylbl, nlbl);
}
Addr* Exp_Or::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  if(PRINT_TAC) printf("\t%s = %s || %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_OR, res, lr, rr));
  return res;
}
void Exp_Or::gen_jmp_code(string ylbl, string nlbl){
  Label rl;
  x1->gen_jmp_code(ylbl, rl.str());
  if(PRINT_TAC) printf("%s:\n", rl.str().c_str());
  tac_code.push_back(new Tac(TC_LBL, new ConstAddr(rl.str()), NULL, NULL));
  x2->gen_jmp_code(ylbl, nlbl);
}
Addr* Exp_Eq::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  if(PRINT_TAC) printf("\t%s = %s == %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_EQ, res, lr, rr));
  return res;
}
void Exp_Eq::gen_jmp_code(string ylbl, string nlbl){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  if(PRINT_TAC) printf("\tif %s == %s goto %s\n", lr->str().c_str(), rr->str().c_str(), ylbl.c_str());
  tac_code.push_back(new Tac(TC_IFEQ, lr, rr, new ConstAddr(ylbl)));  
  if(PRINT_TAC) printf("\tgoto %s\n", nlbl.c_str());
  tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(nlbl), NULL, NULL));
}
Addr* Exp_Neq::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  if(PRINT_TAC) printf("\t%s = %s != %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_NEQ, res, lr, rr));
  return res;
}
void Exp_Neq::gen_jmp_code(string ylbl, string nlbl){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  if(PRINT_TAC) printf("\tif %s != %s goto %s\n", lr->str().c_str(), rr->str().c_str(), ylbl.c_str());
  tac_code.push_back(new Tac(TC_IFNEQ, lr, rr, new ConstAddr(ylbl)));  
  if(PRINT_TAC) printf("\tgoto %s\n", nlbl.c_str());
  tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(nlbl), NULL, NULL));
}
Addr* Exp_Lt::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  if(PRINT_TAC) printf("\t%s = %s < %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_LT, res, lr, rr));
  return res;
}
void Exp_Lt::gen_jmp_code(string ylbl, string nlbl){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  if(PRINT_TAC) printf("\tif %s < %s goto %s\n", lr->str().c_str(), rr->str().c_str(), ylbl.c_str());
  tac_code.push_back(new Tac(TC_IFLT, lr, rr, new ConstAddr(ylbl)));  
  if(PRINT_TAC) printf("\tgoto %s\n", nlbl.c_str());
  tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(nlbl), NULL, NULL));
}
Addr* Exp_Gt::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  if(PRINT_TAC) printf("\t%s = %s > %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_GT, res, lr, rr));
  return res;
}
void Exp_Gt::gen_jmp_code(string ylbl, string nlbl){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  if(PRINT_TAC) printf("\tif %s > %s goto %s\n", lr->str().c_str(), rr->str().c_str(), ylbl.c_str());
  tac_code.push_back(new Tac(TC_IFGT, lr, rr, new ConstAddr(ylbl)));  
  if(PRINT_TAC) printf("\tgoto %s\n", nlbl.c_str());
  tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(nlbl), NULL, NULL));
}
Addr* Exp_Leq::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  if(PRINT_TAC) printf("\t%s = %s <= %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_LEQ, res, lr, rr));
  return res;
}
void Exp_Leq::gen_jmp_code(string ylbl, string nlbl){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  if(PRINT_TAC) printf("\tif %s <= %s goto %s\n", lr->str().c_str(), rr->str().c_str(), ylbl.c_str());
  tac_code.push_back(new Tac(TC_IFLEQ, lr, rr, new ConstAddr(ylbl)));  
  if(PRINT_TAC) printf("\tgoto %s\n", nlbl.c_str());
  tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(nlbl), NULL, NULL));
}
Addr* Exp_Geq::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  if(PRINT_TAC) printf("\t%s = %s >= %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  tac_code.push_back(new Tac(TC_GEQ, res, lr, rr));
  return res;
}
void Exp_Geq::gen_jmp_code(string ylbl, string nlbl){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  if(PRINT_TAC) printf("\tif %s >= %s goto %s\n", lr->str().c_str(), rr->str().c_str(), ylbl.c_str());
  tac_code.push_back(new Tac(TC_IFGEQ, lr, rr, new ConstAddr(ylbl)));  
  if(PRINT_TAC) printf("\tgoto %s\n", nlbl.c_str());
  tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(nlbl), NULL, NULL));
}
Addr* Exp_Not::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *res = new TempAddr;
  if(PRINT_TAC) printf("\t%s = ! %s\n", res->str().c_str(), lr->str().c_str());
  tac_code.push_back(new Tac(TC_NOT, res, lr, NULL));
  return res;
}
void Exp_Not::gen_jmp_code(string ylbl, string nlbl){
  x1->gen_jmp_code(nlbl, ylbl);
}



void Cmd_Atr::gen_code(string lbl_nxt){
  Addr *res = x1->gen_code();
  if(PRINT_TAC) printf("\t%s = %s\n", v1->str().c_str(), res->str().c_str());
  tac_code.push_back(new Tac(TC_ATR, new ValAddr(v1), res, NULL));  
}
void Cmd_Seq::gen_code(string lbl_nxt){
  Label med;
  c1->gen_code(med.str());
  if(PRINT_TAC) printf("%s:\n", med.str().c_str());
  tac_code.push_back(new Tac(TC_LBL, new ConstAddr(med.str()), NULL, NULL));
  c2->gen_code(lbl_nxt);
}
void Cmd_Print::gen_code(string lbl_nxt){
  Lst *cur = lst;
  while(cur != NULL){
    Addr *res = cur->xp->gen_code();
    if(PRINT_TAC) printf("\tprint %s\n", res->str().c_str());
    tac_code.push_back(new Tac(TC_PRINT, res, NULL, NULL));
    cur = cur->next;
  }
  if(PRINT_TAC) printf("\tprint '\\n'\n");
  tac_code.push_back(new Tac(TC_PRINT_ENDL, NULL, NULL, NULL));
}
void Cmd_While::gen_code(string lbl_nxt){
  Label top, body;
  if(PRINT_TAC) printf("%s:\n", top.str().c_str());
  tac_code.push_back(new Tac(TC_LBL, new ConstAddr(top.str()), NULL, NULL));
  x1->gen_jmp_code(body.str(), lbl_nxt);
  if(PRINT_TAC) printf("%s:\n", body.str().c_str());
  tac_code.push_back(new Tac(TC_LBL, new ConstAddr(body.str()), NULL, NULL));
  c1->gen_code(top.str());
  if(PRINT_TAC) printf("\tgoto %s\n", top.str().c_str());
  tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(top.str()), NULL, NULL));
}
void Cmd_If::gen_code(string lbl_nxt){
  if(el == NULL){
    Label body;
    x1->gen_jmp_code(body.str(), lbl_nxt);
    if(PRINT_TAC) printf("%s:\n", body.str().c_str());
    tac_code.push_back(new Tac(TC_LBL, new ConstAddr(body.str()), NULL, NULL));
    c1->gen_code(lbl_nxt);
  }
  else{
    Label then_lbl, else_lbl;
    x1->gen_jmp_code(then_lbl.str(), else_lbl.str());
    if(PRINT_TAC) printf("%s:\n", then_lbl.str().c_str());
    tac_code.push_back(new Tac(TC_LBL, new ConstAddr(then_lbl.str()), NULL, NULL));
    c1->gen_code(lbl_nxt);
    if(PRINT_TAC) printf("\tgoto %s\n", lbl_nxt.c_str());
    tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(lbl_nxt), NULL, NULL));
    if(PRINT_TAC) printf("%s:\n", else_lbl.str().c_str());
    tac_code.push_back(new Tac(TC_LBL, new ConstAddr(else_lbl.str()), NULL, NULL));
    ElseIf *cur = el;
    while(cur != NULL){
      Label t1, e1;
      cur->xp->gen_jmp_code(t1.str(), e1.str());
      if(PRINT_TAC) printf("%s:\n", t1.str().c_str());
      tac_code.push_back(new Tac(TC_LBL, new ConstAddr(t1.str()), NULL, NULL));
      cur->c->gen_code(lbl_nxt);
      if(PRINT_TAC) printf("\tgoto %s\n", lbl_nxt.c_str());
      tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(lbl_nxt), NULL, NULL));
      if(cur->next != NULL){
        if(PRINT_TAC) printf("%s:\n", e1.str().c_str());
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
    if(PRINT_TAC) printf("%s:\n", then_lbl.str().c_str());
    tac_code.push_back(new Tac(TC_LBL, new ConstAddr(then_lbl.str()), NULL, NULL));
    c1->gen_code(lbl_nxt);
    if(PRINT_TAC) printf("\tgoto %s\n", lbl_nxt.c_str());
    tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(lbl_nxt), NULL, NULL));
    if(PRINT_TAC) printf("%s:\n", else_lbl.str().c_str());
    tac_code.push_back(new Tac(TC_LBL, new ConstAddr(else_lbl.str()), NULL, NULL));
    c2->gen_code(lbl_nxt);
  }
  else{
    Label then_lbl, else_lbl;
    x1->gen_jmp_code(then_lbl.str(), else_lbl.str());
    if(PRINT_TAC) printf("%s:\n", then_lbl.str().c_str());
    tac_code.push_back(new Tac(TC_LBL, new ConstAddr(then_lbl.str()), NULL, NULL));
    c1->gen_code(lbl_nxt);
    if(PRINT_TAC) printf("\tgoto %s\n", lbl_nxt.c_str());
    tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(lbl_nxt), NULL, NULL));
    if(PRINT_TAC) printf("%s:\n", else_lbl.str().c_str());
    tac_code.push_back(new Tac(TC_LBL, new ConstAddr(else_lbl.str()), NULL, NULL));
    ElseIf *cur = el;
    while(cur != NULL){
      Label t1, e1;
      cur->xp->gen_jmp_code(t1.str(), e1.str());
      if(PRINT_TAC) printf("%s:\n", t1.str().c_str());
      tac_code.push_back(new Tac(TC_LBL, new ConstAddr(t1.str()), NULL, NULL));
      cur->c->gen_code(lbl_nxt);
      if(PRINT_TAC) printf("\tgoto %s\n", lbl_nxt.c_str());
      tac_code.push_back(new Tac(TC_GOTO, new ConstAddr(lbl_nxt), NULL, NULL));
      if(PRINT_TAC) printf("%s:\n", e1.str().c_str());
      tac_code.push_back(new Tac(TC_LBL, new ConstAddr(e1.str()), NULL, NULL));
      cur = cur->next;
    }
    c2->gen_code(lbl_nxt);
  }
}


void Prgm::gen_code(){
  Label lbl;
  c->gen_code(lbl.str());
  if(PRINT_TAC) printf("%s:\n", lbl.str().c_str());
  tac_code.push_back(new Tac(TC_LBL, new ConstAddr(lbl.str()), NULL, NULL));
}


void ast_to_tac(Prgm *r){
  tac_code.clear();
  r->gen_code();
  return;
}


int calc_sp(string vn){
  piv elem = var_tac_mips[vn];
  return ((var_sz - elem.X - 1) * 4); 
}

void create_mips_var(string vn, VAL_TYPE vtp){
  var_tac_mips[vn] = piv(var_sz ++, vtp);
  fprintf(fout, "\taddi\t$sp, $sp, -4\n");
}

void Tac::gen_mips(){
  switch(op){
    
  case TC_PRINT:
    if(var_tac_mips[r1->str()].Y != VT_FLOAT){
      fprintf(fout, "\tli\t$v0, 1\n");
      fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r1->str()));
      fprintf(fout, "\tmove\t$a0, $t1\n");
    }
    else{
      fprintf(fout, "\tli\t$v0, 2\n");
      fprintf(fout, "\tlwc1\t$f1, %d($sp)\n", calc_sp(r1->str()));
      fprintf(fout, "\tmov.s\t$f12, $f1\n");
    }
    fprintf(fout, "\tsyscall\n");
    break;
  case TC_PRINT_ENDL:
    fprintf(fout, "\tli\t$v0, 4\n");
    fprintf(fout, "\tla\t$a0, endl\n");
    fprintf(fout, "\tsyscall\n");
    break;

  case TC_ADD:
    if(var_tac_mips[r2->str()].Y != VT_FLOAT && var_tac_mips[r3->str()].Y != VT_FLOAT){
      if(var_tac_mips.find(r1->str()) == var_tac_mips.end())
        create_mips_var(r1->str(), var_tac_mips[r2->str()].Y);
      fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tlw\t$t2, %d($sp)\n", calc_sp(r3->str()));
      fprintf(fout, "\tadd\t$t3, $t1, $t2\n");
      fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
      fprintf(fout, "\tsw\t$t3, ($t0)\n");
    }
    else{
      // should convert both members to float...
      if(var_tac_mips.find(r1->str()) == var_tac_mips.end())
        create_mips_var(r1->str(), VT_FLOAT);
      fprintf(fout, "\tlwc1\t$f1, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tlwc1\t$f2, %d($sp)\n", calc_sp(r3->str()));
      fprintf(fout, "\tadd.s\t$f3, $f1, $f2\n");
      fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
      fprintf(fout, "\tswc1\t$f3, ($t0)\n");
    }
    break;
  case TC_SUB:
    if(var_tac_mips[r2->str()].Y != VT_FLOAT && var_tac_mips[r3->str()].Y != VT_FLOAT){
      if(var_tac_mips.find(r1->str()) == var_tac_mips.end())
        create_mips_var(r1->str(), var_tac_mips[r2->str()].Y);
      fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tlw\t$t2, %d($sp)\n", calc_sp(r3->str()));
      fprintf(fout, "\tsub\t$t3, $t1, $t2\n");
      fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
      fprintf(fout, "\tsw\t$t3, ($t0)\n");
    }
    else{
      // should convert both members to float...
      if(var_tac_mips.find(r1->str()) == var_tac_mips.end())
        create_mips_var(r1->str(), VT_FLOAT);
      fprintf(fout, "\tlwc1\t$f1, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tlwc1\t$f2, %d($sp)\n", calc_sp(r3->str()));
      fprintf(fout, "\tsub.s\t$f3, $f1, $f2\n");
      fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
      fprintf(fout, "\tswc1\t$f3, ($t0)\n");
    }
    break;
  case TC_MUL:
    if(var_tac_mips[r2->str()].Y != VT_FLOAT && var_tac_mips[r3->str()].Y != VT_FLOAT){
      if(var_tac_mips.find(r1->str()) == var_tac_mips.end())
        create_mips_var(r1->str(), var_tac_mips[r2->str()].Y);
      fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tlw\t$t2, %d($sp)\n", calc_sp(r3->str()));
      fprintf(fout, "\tmult\t$t1, $t2\n");
      fprintf(fout, "\tmflo\t$t3\n");
      fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
      fprintf(fout, "\tsw\t$t3, ($t0)\n");
    }
    else{
      // should convert both members to float...
      if(var_tac_mips.find(r1->str()) == var_tac_mips.end())
        create_mips_var(r1->str(), VT_FLOAT);
      fprintf(fout, "\tlwc1\t$f1, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tlwc1\t$f2, %d($sp)\n", calc_sp(r3->str()));
      fprintf(fout, "\tmul.s\t$f3, $f1, $f2\n");
      fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
      fprintf(fout, "\tswc1\t$f3, ($t0)\n");
    }
    break;
  case TC_DIV:
    if(var_tac_mips[r2->str()].Y != VT_FLOAT && var_tac_mips[r3->str()].Y != VT_FLOAT){
      if(var_tac_mips.find(r1->str()) == var_tac_mips.end())
        create_mips_var(r1->str(), var_tac_mips[r2->str()].Y);
      fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tlw\t$t2, %d($sp)\n", calc_sp(r3->str()));
      fprintf(fout, "\tdiv\t$t1, $t2\n");
      fprintf(fout, "\tmflo\t$t3\n");
      fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
      fprintf(fout, "\tsw\t$t3, ($t0)\n");
    }
    else{
      // should convert both members to float...
      if(var_tac_mips.find(r1->str()) == var_tac_mips.end())
        create_mips_var(r1->str(), VT_FLOAT);
      fprintf(fout, "\tlwc1\t$f1, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tlwc1\t$f2, %d($sp)\n", calc_sp(r3->str()));
      fprintf(fout, "\tdiv.s\t$f3, $f1, $f2\n");
      fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
      fprintf(fout, "\tswc1\t$f3, ($t0)\n");
    }
    break;
  case TC_POW:
    fprintf(fout, "\tpow function here!\n");
    break;
  case TC_MOD:
    if(var_tac_mips[r2->str()].Y != VT_FLOAT && var_tac_mips[r3->str()].Y != VT_FLOAT){
      if(var_tac_mips.find(r1->str()) == var_tac_mips.end())
        create_mips_var(r1->str(), var_tac_mips[r2->str()].Y);
      fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tlw\t$t2, %d($sp)\n", calc_sp(r3->str()));
      fprintf(fout, "\tdiv\t$t1, $t2\n");
      fprintf(fout, "\tmfhi\t$t3\n");
      fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
      fprintf(fout, "\tsw\t$t3, ($t0)\n");
    }
    else
      fprintf(fout, "\tfloat mod function here!\n"); 
    break;
  case TC_MIN:
    if(var_tac_mips[r2->str()].Y != VT_FLOAT && var_tac_mips[r3->str()].Y != VT_FLOAT){
      if(var_tac_mips.find(r1->str()) == var_tac_mips.end())
        create_mips_var(r1->str(), var_tac_mips[r2->str()].Y);
      fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tsub\t$t2, $zero, $t1\n");
      fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
      fprintf(fout, "\tsw\t$t2, ($t0)\n");
    }
    else{
      if(var_tac_mips.find(r1->str()) == var_tac_mips.end())
        create_mips_var(r1->str(), VT_FLOAT);
      fprintf(fout, "\tli.s\t$f1, 0.0\n");
      fprintf(fout, "\tlwc1\t$f2, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tsub.s\t$f3, $f1, $f2\n");
      fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
      fprintf(fout, "\tswc1\t$f3, ($t0)\n");
    }
    break;

  case TC_AND:
    if(var_tac_mips.find(r1->str()) == var_tac_mips.end())
      create_mips_var(r1->str(), var_tac_mips[r2->str()].Y);
    fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r2->str()));
    fprintf(fout, "\tlw\t$t2, %d($sp)\n", calc_sp(r3->str()));
    fprintf(fout, "\tand\t$t3, $t1, $t2\n");
    fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
    fprintf(fout, "\tsw\t$t3, ($t0)\n");
    break;
  case TC_OR:
    if(var_tac_mips.find(r1->str()) == var_tac_mips.end())
      create_mips_var(r1->str(), var_tac_mips[r2->str()].Y);
    fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r2->str()));
    fprintf(fout, "\tlw\t$t2, %d($sp)\n", calc_sp(r3->str()));
    fprintf(fout, "\tor\t$t3, $t1, $t2\n");
    fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
    fprintf(fout, "\tsw\t$t3, ($t0)\n");
    break;
  case TC_EQ:
    if(var_tac_mips.find(r1->str()) == var_tac_mips.end())
      create_mips_var(r1->str(), VT_BOOL);
    fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r2->str()));
    fprintf(fout, "\tlw\t$t2, %d($sp)\n", calc_sp(r3->str()));
    fprintf(fout, "\tslt\t$t3, $t1, $t2\n");
    fprintf(fout, "\tslt\t$t4, $t2, $t1\n");
    fprintf(fout, "\tor\t$t5, $t3, $t4\n");
    fprintf(fout, "\txori\t$t5, $t5, 1\n");
    fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
    fprintf(fout, "\tsw\t$t5, ($t0)\n");
    break;
  case TC_NEQ:
    if(var_tac_mips.find(r1->str()) == var_tac_mips.end())
      create_mips_var(r1->str(), VT_BOOL);
    fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r2->str()));
    fprintf(fout, "\tlw\t$t2, %d($sp)\n", calc_sp(r3->str()));
    fprintf(fout, "\tslt\t$t3, $t1, $t2\n");
    fprintf(fout, "\tslt\t$t4, $t2, $t1\n");
    fprintf(fout, "\tor\t$t5, $t3, $t4\n");
    fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
    fprintf(fout, "\tsw\t$t5, ($t0)\n");
    break;
  case TC_LT:
    if(var_tac_mips.find(r1->str()) == var_tac_mips.end())
      create_mips_var(r1->str(), VT_BOOL);
    fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r2->str()));
    fprintf(fout, "\tlw\t$t2, %d($sp)\n", calc_sp(r3->str()));
    fprintf(fout, "\tslt\t$t3, $t1, $t2\n");
    fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
    fprintf(fout, "\tsw\t$t3, ($t0)\n");
    break;
  case TC_GT:
    if(var_tac_mips.find(r1->str()) == var_tac_mips.end())
      create_mips_var(r1->str(), VT_BOOL);
    fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r2->str()));
    fprintf(fout, "\tlw\t$t2, %d($sp)\n", calc_sp(r3->str()));
    fprintf(fout, "\tslt\t$t3, $t2, $t1\n");
    fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
    fprintf(fout, "\tsw\t$t3, ($t0)\n");
    break;
  case TC_LEQ:
    if(var_tac_mips.find(r1->str()) == var_tac_mips.end())
      create_mips_var(r1->str(), VT_BOOL);
    fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r2->str()));
    fprintf(fout, "\tlw\t$t2, %d($sp)\n", calc_sp(r3->str()));
    fprintf(fout, "\tslt\t$t3, $t2, $t1\n");
    fprintf(fout, "\txori\t$t3, $t3, 1\n");
    fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
    fprintf(fout, "\tsw\t$t3, ($t0)\n");
    break;
  case TC_GEQ:
    if(var_tac_mips.find(r1->str()) == var_tac_mips.end())
      create_mips_var(r1->str(), VT_BOOL);
    fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r2->str()));
    fprintf(fout, "\tlw\t$t2, %d($sp)\n", calc_sp(r3->str()));
    fprintf(fout, "\tslt\t$t3, $t1, $t2\n");
    fprintf(fout, "\txori\t$t3, $t3, 1\n");
    fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
    fprintf(fout, "\tsw\t$t3, ($t0)\n");
    break;
  case TC_NOT:
    if(var_tac_mips.find(r1->str()) == var_tac_mips.end())
      create_mips_var(r1->str(), var_tac_mips[r2->str()].Y);
    fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r2->str()));
    fprintf(fout, "\txori\t$t2, $t1, 1\n");
    fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
    fprintf(fout, "\tsw\t$t2, ($t0)\n");
    break;
    
  case TC_LOAD:
    create_mips_var(r1->str(), r2->get_type());
    if(r2->get_type() != VT_FLOAT){
      fprintf(fout, "\tli\t$t1, %s\n", r2->str().c_str());
      fprintf(fout, "\tsw\t$t1, 0($sp)\n");
    }
    else{
      fprintf(fout, "\tli.s\t$f1, %s\n", r2->str().c_str());
      fprintf(fout, "\tswc1\t$f1, 0($sp)\n");
    }
    break;
  case TC_ATR:
    if(var_tac_mips.find(r1->str()) == var_tac_mips.end())
      create_mips_var(r1->str(), var_tac_mips[r2->str()].Y);
    if(var_tac_mips[r2->str()].Y != VT_FLOAT){
      fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tmove\t$t2, $t1\n");
      fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
      fprintf(fout, "\tsw\t$t2, ($t0)\n");
    }
    else{
      fprintf(fout, "\tlwc1\t$f1, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tmov.s\t$f2, $f1\n");
      fprintf(fout, "\tla\t$t0, %d($sp)\n", calc_sp(r1->str()));    
      fprintf(fout, "\tswc1\t$f2, ($t0)\n");
    }
    break;
  case TC_LBL:
    fprintf(fout, "%s:\n", r1->str().c_str());
    break;
  case TC_GOTO:
    fprintf(fout, "jal\t%s\n", r1->str().c_str());
    break;
  case TC_IFEQ:
    if(var_tac_mips[r1->str()].Y != VT_FLOAT){
      fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r1->str()));
      fprintf(fout, "\tlw\t$t2, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tbeq\t$t1, $t2, %s\n", r3->str().c_str());
    }
    else{
      fprintf(fout, "\tlwc1\t$f1, %d($sp)\n", calc_sp(r1->str()));
      fprintf(fout, "\tlwc1\t$f2, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tc.eq.s\t$f1, $f2\n");
      fprintf(fout, "\tbc1t\t%s\n", r3->str().c_str());
    }
    break;
  case TC_IFNEQ:
    if(var_tac_mips[r1->str()].Y != VT_FLOAT){
      fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r1->str()));
      fprintf(fout, "\tlw\t$t2, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tbne\t$t1, $t2, %s\n", r3->str().c_str());
    }
    else{
      fprintf(fout, "\tlwc1\t$f1, %d($sp)\n", calc_sp(r1->str()));
      fprintf(fout, "\tlwc1\t$f2, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tc.eq.s\t$f1, $f2\n");
      fprintf(fout, "\tbc1f\t%s\n", r3->str().c_str());
    }
    break;
  case TC_IFLT:
    if(var_tac_mips[r1->str()].Y != VT_FLOAT){
      fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r1->str()));
      fprintf(fout, "\tlw\t$t2, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tblt\t$t1, $t2, %s\n", r3->str().c_str());
    }
    else{
      fprintf(fout, "\tlwc1\t$f1, %d($sp)\n", calc_sp(r1->str()));
      fprintf(fout, "\tlwc1\t$f2, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tc.lt.s\t$f1, $f2\n");
      fprintf(fout, "\tbc1t\t%s\n", r3->str().c_str());
    }
    break;
  case TC_IFGT:
    if(var_tac_mips[r1->str()].Y != VT_FLOAT){
      fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r1->str()));
      fprintf(fout, "\tlw\t$t2, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tbgt\t$t1, $t2, %s\n", r3->str().c_str());
    }
    else{
      fprintf(fout, "\tlwc1\t$f1, %d($sp)\n", calc_sp(r1->str()));
      fprintf(fout, "\tlwc1\t$f2, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tc.le.s\t$f1, $f2\n");
      fprintf(fout, "\tbc1f\t%s\n", r3->str().c_str());
    }
    break;
  case TC_IFLEQ:
    if(var_tac_mips[r1->str()].Y != VT_FLOAT){
      fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r1->str()));
      fprintf(fout, "\tlw\t$t2, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tble\t$t1, $t2, %s\n", r3->str().c_str());
    }
    else{
      fprintf(fout, "\tlwc1\t$f1, %d($sp)\n", calc_sp(r1->str()));
      fprintf(fout, "\tlwc1\t$f2, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tc.le.s\t$f1, $f2\n");
      fprintf(fout, "\tbc1t\t%s\n", r3->str().c_str());
    }
    break;
  case TC_IFGEQ:
    if(var_tac_mips[r1->str()].Y != VT_FLOAT){
      fprintf(fout, "\tlw\t$t1, %d($sp)\n", calc_sp(r1->str()));
      fprintf(fout, "\tlw\t$t2, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tbge\t$t1, $t2, %s\n", r3->str().c_str());
    }
    else{
      fprintf(fout, "\tlwc1\t$f1, %d($sp)\n", calc_sp(r1->str()));
      fprintf(fout, "\tlwc1\t$f2, %d($sp)\n", calc_sp(r2->str()));
      fprintf(fout, "\tc.lt.s\t$f1, $f2\n");
      fprintf(fout, "\tbc1f\t%s\n", r3->str().c_str());
    }
    break;
  }
}


void tac_to_mips(){  
  fprintf(fout, ".data\n");
  fprintf(fout, "endl:\t.asciiz \"\\n\"\n");  
  fprintf(fout, ".text\n");
  fprintf(fout, "main:\n");
  for(int i = 0; i < (int)tac_code.size(); i ++)
    tac_code[i]->gen_mips();
  fprintf(fout, "\tli\t$v0, 10\n");
  fprintf(fout, "\tsyscall\n");
}


void compile(Prgm *r){
  ast_to_tac(r);
  
  fout = fopen("a.asm", "w");
  tac_to_mips();
  fclose(fout);
}
