//
// Created by Alston on 2016/9/16.
//

#ifndef PARSING_PARSING_H
#define PARSING_PARSING_H

#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>


namespace hmt {
    template <typename T> void unordered_map_union(T*, T*);
    class Rule;
    class Symbol{
        std::string content;
        std::vector<Rule*> rules;
    public:
        static Symbol const * const epsilon;
        Symbol(std::string);
        bool isTerminal() const;
        std::string name() const;
        void addRule(Rule*);
    };

    struct Rule {
        const Symbol *lhs;
        std::vector<const Symbol*> rhs;
        Rule(const Symbol*, std::vector<const Symbol*>&);
        Rule(const Symbol*, const Symbol**, const int);
    };

    class ItemCollection;

    struct Item {
        Rule *r;
        int pos;
        Item(Rule*, int);
        bool atEnd();
    };

    struct LR1Item : public Item{
        std::unordered_set<Symbol*> end;
    public:
        LR1Item(Rule*, int);
    };

    class LR1ItemCollection{
        std::unordered_map<Rule*, std::unordered_map<std::unordered_set<Symbol*>*, std::vector<LR1Item*>>> content;
        LR1Item* shiftAdd(LR1Item*);
    };

    class parsingTable{
        int type;
        std::vector<std::vector<int>> content;
        std::vector<Symbol*> head;
    };

    class Grammar {
        const Symbol *startSymbol;
        std::unordered_set<const Symbol*> symbolsSet;
        std::unordered_map<const Symbol*, std::vector<const Rule*>> rulesSet;
        std::unordered_set<const Symbol*>* processNTSequence(const std::vector<const Symbol*>&, int);
    public:
        Grammar();
        bool addSymbol(const Symbol *s);
        bool setStartSymbol(const Symbol *s);
        bool addRule(const Rule *r);
        std::unordered_set<const Symbol*>* findFirstSet(const Symbol*);
        //parsingTable* parseLR1();
    };

}



#endif //PARSING_PARSING_H
