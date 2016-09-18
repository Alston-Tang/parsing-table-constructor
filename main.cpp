#include <iostream>
#include "parsing.h"

using namespace std;
using namespace hmt;

int main() {
    Grammar g;

    Symbol *Prog = new Symbol("Prog");
    Symbol *Decls = new Symbol("Decls");
    Symbol *Decl = new Symbol("Decl");
    Symbol *Mode = new Symbol("Mode");
    Symbol *IdList = new Symbol("IdList");
    Symbol *Stmts = new Symbol("Stmts");
    Symbol *Stmt = new Symbol("Stmt");
    Symbol *Expr = new Symbol("Expr");
    Symbol *begin = new Symbol("begin");
    Symbol *end = new Symbol("end");
    Symbol *_int = new Symbol("int");
    Symbol *_bool = new Symbol("bool");
    Symbol *id = new Symbol("id");
    Symbol *print = new Symbol("print");
    Symbol *equal = new Symbol("=");
    Symbol *semicolon = new Symbol(";");
    Symbol *open = new Symbol("(");
    Symbol *close = new Symbol(")");
    Symbol *comma = new Symbol(",");
    Symbol *plus = new Symbol("+");

    const Symbol* r1[] = {begin, Decl, semicolon, Stmt, end};
    const Symbol* r2[] = {Decl};
    const Symbol* r3[] = {Mode, IdList};
    const Symbol* r4[] = {_int};
    const Symbol* r5[] = {_bool};
    const Symbol* r6[] = {id};
    const Symbol* r7[] = {id, comma, IdList};
    const Symbol* r8[] = {Stmt};
    const Symbol* r9[] = {Stmt, semicolon, Stmts};
    const Symbol* r10[] = {id, equal, Expr};
    const Symbol* r11[] = {print, Expr};
    const Symbol* r12[] = {id};
    const Symbol* r13[] = {Expr, plus, Expr};
    const Symbol* r14[] = {open, Expr, close};

    Rule* rule1 = new Rule(Prog, r1, 5);
    Rule* rule2 = new Rule(Decls, r2, 1);
    Rule* rule3 = new Rule(Decl, r3, 2);
    Rule* rule4 = new Rule(Mode, r4, 1);
    Rule* rule5 = new Rule(Mode, r5, 1);
    Rule* rule6 = new Rule(IdList, r6, 1);
    Rule* rule7 = new Rule(IdList, r7, 3);
    Rule* rule8 = new Rule(Stmts, r8, 1);
    Rule* rule9 = new Rule(Stmts, r9, 3);
    Rule* rule10 = new Rule(Stmt, r10, 3);
    Rule* rule11 = new Rule(Stmt, r11, 2);
    Rule* rule12 = new Rule(Expr, r12, 1);
    Rule* rule13 = new Rule(Expr, r13, 3);
    Rule* rule14 = new Rule(Expr, r14, 3);

    g.addSymbol(Prog);
    g.addSymbol(Decls);
    g.addSymbol(Decl);
    g.addSymbol(Mode);
    g.addSymbol(IdList);
    g.addSymbol(Stmts);
    g.addSymbol(Stmt);
    g.addSymbol(Expr);
    g.addSymbol(begin);
    g.addSymbol(end);
    g.addSymbol(id);
    g.addSymbol(_bool);
    g.addSymbol(_int);
    g.addSymbol(print);
    g.addSymbol(equal);
    g.addSymbol(semicolon);
    g.addSymbol(open);
    g.addSymbol(close);
    g.addSymbol(comma);
    g.addSymbol(plus);

    g.addRule(rule1);
    g.addRule(rule2);
    g.addRule(rule3);
    g.addRule(rule4);
    g.addRule(rule5);
    g.addRule(rule6);
    g.addRule(rule7);
    g.addRule(rule8);
    g.addRule(rule9);
    g.addRule(rule10);
    g.addRule(rule11);
    g.addRule(rule12);
    g.addRule(rule13);
    g.addRule(rule14);

    auto res = g.findFirstSet(Expr);
    for (auto elem : *res) {
        cout << elem->name() << " ";
    }


}