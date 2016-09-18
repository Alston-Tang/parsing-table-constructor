//
// Created by Alston on 2016/9/16.
//


#include "parsing.h"
#include <iostream>
#include <algorithm>

namespace hmt {

    template <typename T> void unordered_map_union(T *a, T *b) {
        for (auto element : *b) {
            a->insert(element);
        }
    }

    Symbol const * const Symbol::epsilon = new Symbol("");
    Symbol::Symbol(std::string _content) : content(_content){}
    bool Symbol::isTerminal() const {
        return rules.empty();
    }
    std::string Symbol::name() const {
        return content;
    }
    void Symbol::addRule(Rule *r) {
        rules.push_back(r);
    }

    Rule::Rule(const Symbol *_lhs, std::vector<const Symbol*> &_rhs) : lhs(_lhs), rhs(_rhs) {}
    Rule::Rule(const Symbol *_lhs, const Symbol **_rhs, const int len) : lhs(_lhs) {
        for (int i = 0; i < len; i++) {
            rhs.push_back(_rhs[i]);
        }
    }

    Item::Item(Rule *_r, int _pos) : r(_r), pos(_pos) {}
    bool Item::atEnd() {
        return pos >= r->rhs.size();
    }

    LR1Item::LR1Item(Rule *_r, int _pos) : Item(_r, _pos) {}
    LR1Item* LR1ItemCollection::shiftAdd(LR1Item *item) {
        if (item->atEnd()) return NULL;
        std::vector<LR1Item*> container = content[item->r][&(item->end)];
        Item *result = container[item->pos];
        if (result->atEnd()) {
            return NULL;
        }
        if (container.size() <= item->pos){
            container.push_back(NULL);
        }
        if (container[item->pos + 1] == NULL) {
            LR1Item *newItem = new LR1Item(item->r, item->pos + 1);
            container[item->pos + 1] = newItem;
            return newItem;
        } else {
            return container[item->pos + 1];
        }
    }

    Grammar::Grammar() : startSymbol(NULL) { }
    bool Grammar::addSymbol(const Symbol *s) {
        if (symbolsSet.find(s) == symbolsSet.end()) {
            symbolsSet.insert(s);
            return true;
        }
        return false;
    }
    bool Grammar::setStartSymbol(const Symbol *s) {
        if (symbolsSet.find(s) != symbolsSet.end() && startSymbol == NULL) {
            startSymbol = s;
            return true;
        }
        return false;
    }
    bool Grammar::addRule(const Rule *r) {
        auto it = rulesSet.find(r->lhs);
        if (it == rulesSet.end()) {
            rulesSet.insert(std::pair<const Symbol*, std::vector<const Rule*>>(r->lhs, std::vector<const Rule*>(1, r)));
            return true;
        } else {
            if (std::find(it->second.begin(), it->second.end(), r) == it->second.end()) {
                it->second.push_back(r);
                return true;
            }
        }
        return false;
    }
    std::unordered_set<const Symbol*>* Grammar::findFirstSet(const Symbol* s) {
        std::unordered_set<const Symbol*> *rv = new std::unordered_set<const Symbol*>();
        for (const Rule *r : rulesSet[s]) {
            if (r->rhs[0] != Symbol::epsilon) {
                const Symbol *firstSymbol = r->rhs[0];
                if (firstSymbol->isTerminal()) {
                    rv->insert(firstSymbol);
                } else {
                    auto res = processNTSequence(r->rhs, 0);
                    unordered_map_union<std::unordered_set<const Symbol*>>(rv, res);
                }
            } else {
                rv->insert(Symbol::epsilon);
            }
        }
        return rv;
    }
    std::unordered_set<const Symbol*>* Grammar::processNTSequence(const std::vector<const Symbol*> &seq, int pos) {
        auto res = findFirstSet(seq[pos]);
        if (res->find(Symbol::epsilon) != res->end()) {
            if (pos < seq.size()) {
                if (seq[pos + 1]->isTerminal()) {
                    res->insert(seq[pos + 1]);
                } else {
                    auto nextRes = processNTSequence(seq, pos + 1);
                    unordered_map_union<std::unordered_set<const Symbol *>>(res, nextRes);
                }
            } else {
                res->insert(Symbol::epsilon);
            }
        }
        return res;
    }
}


