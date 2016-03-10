#ifndef RE2NFA_H
#define RE2NFA_H
#include <bits/stdc++.h>
using namespace std;

class State{
private:
	multimap<char, State*> transitions;
	int s_id;
	bool final;
public:
	State(int);
	bool isfinal();
	int get_s_id();
	multimap<char, State*> getallTransitions();
	vector<State*> getTransitions(char);
	void addTransition(char, State*);
	void setasfinal();
};

bool concat();
bool star();
bool unio();
bool evaluate();
bool isoperator(char);
bool isalphabet(char);
string preprocessing(string);
void push(char);
bool Pop(deque<State*>*);
bool CreateNFA(string);
void create_NFAtable();
void createTable();



/*extern variables declared*/
extern int global_id;
extern stack<deque<State*> > operand_stack;
extern stack<char> operator_stack;
extern deque<State *> NFA;
#endif