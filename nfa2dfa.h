#ifndef NFA2DFA_H
#define NFA2DFA_H

#include <bits/stdc++.h>
#include "re2nfa.h"
using namespace std;

class dfa{
private:
	int id;
	bool final;
	multimap<char, dfa*> transitions;
	set<State *> childs;
public:
	dfa(int, set<State*>);
	void setasfinal();
	bool isfinal();
	void insert_child(State *);
	bool any_final_child();
	int getid();
	set<State*> get_childs();
	void add_transition(char, dfa*);
	vector<dfa*> getTransitions(char alphabet);
	multimap<char, dfa*> getallTransitions();
	// ~dfa();	/*will implement it later*/
};

set<State*> ecl(set<State*>);
void create_dfa();
void printDFA();
void srm();

extern int dfa_global_id;
extern deque<dfa *> DFA;

void ayush();/*temp function*/

#endif