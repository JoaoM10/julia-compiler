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
};
class TempAddr : public Addr {
  static unsigned int cnt;
  const unsigned int lnum;
public:
  TempAddr () : lnum(cnt ++) { }
  string str(){
    return ("t" + to_string(lnum));
  }
};
class ValAddr : public Addr {
  Value *v;
public:
  ValAddr (Value *v1) : v(v1) { }
  string str(){
    return v->str();
  }
};



void ast_to_tac(Prgm*);
