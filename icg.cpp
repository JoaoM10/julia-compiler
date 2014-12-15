#include <bits/stdc++.h>
#include "ast.h"
#include "icg.h"
using namespace std;


unsigned int Label::cnt = 0;
unsigned int TempAddr::cnt = 0;


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
  printf("\t%s = %s + %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
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
  printf("\t%s = %s - %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
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
  printf("\t%s = %s * %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
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
  printf("\t%s = %s / %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
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
  printf("\t%s = %s ^ %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
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
  printf("\t%s = %s \% %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
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
  printf("\t%s = - %s\n", res->str().c_str(), lr->str().c_str());
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
  printf("\t%s = %s && %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  delete lr;
  delete rr;
  return res;
}
void Exp_And::gen_jmp_code(string ylbl, string nlbl){
  Label rl;
  x1->gen_jmp_code(rl.str(), nlbl);
  printf("%s:\n", rl.str().c_str());
  x2->gen_jmp_code(ylbl, nlbl);
}
Addr* Exp_Or::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  printf("\t%s = %s || %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  delete lr;
  delete rr;
  return res;
}
void Exp_Or::gen_jmp_code(string ylbl, string nlbl){
  Label rl;
  x1->gen_jmp_code(ylbl, rl.str());
  printf("%s:\n", rl.str().c_str());
  x2->gen_jmp_code(ylbl, nlbl);
}
Addr* Exp_Eq::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  printf("\t%s = %s == %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  delete lr;
  delete rr;
  return res;
}
void Exp_Eq::gen_jmp_code(string ylbl, string nlbl){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  printf("\tif %s == %s goto %s\n", lr->str().c_str(), rr->str().c_str(), ylbl.c_str());
  printf("\tgoto %s\n", nlbl.c_str());
  delete lr;
  delete rr;
}
Addr* Exp_Neq::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  printf("\t%s = %s != %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  delete lr;
  delete rr;
  return res;
}
void Exp_Neq::gen_jmp_code(string ylbl, string nlbl){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  printf("\tif %s != %s goto %s\n", lr->str().c_str(), rr->str().c_str(), ylbl.c_str());
  printf("\tgoto %s\n", nlbl.c_str());
  delete lr;
  delete rr;
}
Addr* Exp_Lt::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  printf("\t%s = %s < %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  delete lr;
  delete rr;
  return res;
}
void Exp_Lt::gen_jmp_code(string ylbl, string nlbl){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  printf("\tif %s < %s goto %s\n", lr->str().c_str(), rr->str().c_str(), ylbl.c_str());
  printf("\tgoto %s\n", nlbl.c_str());
  delete lr;
  delete rr;
}
Addr* Exp_Gt::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  printf("\t%s = %s > %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  delete lr;
  delete rr;
  return res;
}
void Exp_Gt::gen_jmp_code(string ylbl, string nlbl){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  printf("\tif %s > %s goto %s\n", lr->str().c_str(), rr->str().c_str(), ylbl.c_str());
  printf("\tgoto %s\n", nlbl.c_str());
  delete lr;
  delete rr;
}
Addr* Exp_Leq::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  printf("\t%s = %s <= %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  delete lr;
  delete rr;
  return res;
}
void Exp_Leq::gen_jmp_code(string ylbl, string nlbl){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  printf("\tif %s <= %s goto %s\n", lr->str().c_str(), rr->str().c_str(), ylbl.c_str());
  printf("\tgoto %s\n", nlbl.c_str());
  delete lr;
  delete rr;
}
Addr* Exp_Geq::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  Addr *res = new TempAddr;
  printf("\t%s = %s >= %s\n", res->str().c_str(), lr->str().c_str(), rr->str().c_str());
  delete lr;
  delete rr;
  return res;
}
void Exp_Geq::gen_jmp_code(string ylbl, string nlbl){
  Addr *lr = x1->gen_code();
  Addr *rr = x2->gen_code();
  printf("\tif %s >= %s goto %s\n", lr->str().c_str(), rr->str().c_str(), ylbl.c_str());
  printf("\tgoto %s\n", nlbl.c_str());
  delete lr;
  delete rr;
}
Addr* Exp_Not::gen_code(){
  Addr *lr = x1->gen_code();
  Addr *res = new TempAddr;
  printf("\t%s = ! %s\n", res->str().c_str(), lr->str().c_str());
  delete lr;
  return res;
}
void Exp_Not::gen_jmp_code(string ylbl, string nlbl){
  x1->gen_jmp_code(nlbl, ylbl);
}



void Cmd_Atr::gen_code(string lbl_nxt){
  Addr *res = x1->gen_code();
  printf("\t%s = %s\n", v1->str().c_str(), res->str().c_str());
  delete res;
}
void Cmd_Seq::gen_code(string lbl_nxt){
  Label med;
  c1->gen_code(med.str());
  printf("%s:\n", med.str().c_str());
  c2->gen_code(lbl_nxt);
}
void Cmd_Print::gen_code(string lbl_nxt){
  Lst *cur = lst;
  while(cur != NULL){
    Addr *res = cur->xp->gen_code();
    printf("\tprint %s\n", res->str().c_str());
    cur = cur->next;
  }
  printf("\tprint '\\n'\n");
}
void Cmd_While::gen_code(string lbl_nxt){
  Label top, body;
  printf("%s:\n", top.str().c_str());
  x1->gen_jmp_code(body.str(), lbl_nxt);
  printf("%s:\n", body.str().c_str());
  c1->gen_code(top.str());
  printf("\tgoto %s\n", top.str().c_str());
}
void Cmd_If::gen_code(string lbl_nxt){
  // missing elseif expressions...
  Label body;
  x1->gen_jmp_code(body.str(), lbl_nxt);
  printf("%s:\n", body.str().c_str());
  c1->gen_code(lbl_nxt);
}
void Cmd_IfElse::gen_code(string lbl_nxt){
  // missing elseif expressions...
  Label then_lbl, else_lbl;
  x1->gen_jmp_code(then_lbl.str(), else_lbl.str());
  printf("%s:\n", then_lbl.str().c_str());
  c1->gen_code(lbl_nxt);
  printf("\tgoto %s\n", lbl_nxt.c_str());
  printf("%s:\n", else_lbl.str().c_str());
  c2->gen_code(lbl_nxt);
}


void Prgm::gen_code(){
  Label lbl;
  c->gen_code(lbl.str());
  printf("%s:\n", lbl.str().c_str());
}


void ast_to_tac(Prgm *r){
  r->gen_code();
  return;
}
