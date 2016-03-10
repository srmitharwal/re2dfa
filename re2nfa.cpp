#include <bits/stdc++.h>
#include "re2nfa.h"
using namespace std;

/*extern variables defined*/
int global_id=0;
stack<deque<State*> > operand_stack;
stack<char> operator_stack;
deque<State *> NFA;

/*Class Constructor*/
State::State(int id){
	s_id = id;
	final=false;
}

/*check if the state is final state*/
bool State::isfinal(){
		return final;
}

/*this sets state(this.setasfinal()) as final*/
void State::setasfinal(){
	final=true;
}

/*return the state ID*/
int State::get_s_id(){
		return s_id;
}

/*returns a multimap of all the transitions possible from the state on which function is called*/
multimap<char, State*> State::getallTransitions(){
	return transitions;
}

/*returns a state vector of all states which can be reached on a specific alphabet transisition*/
vector<State*> State::getTransitions(char alphabet){
	multimap<char, State*>::iterator it;
	vector<State*> ans;
    for (it=transitions.equal_range(alphabet).first; it!=transitions.equal_range(alphabet).second; ++it){
    	ans.push_back((*it).second);
    }
    return ans;
}

/*Adds a transition on alphabet to a state which is specified by the user*/
void State::addTransition(char alphabet, State *st){
	transitions.insert(pair<char, State*>(alphabet, st));
}

/*Check if the character passed as parameter is an operand(*,|,(,),#)*/
bool isoperator(char ch){
	return ((ch == 42) || (ch == 124) || (ch == 40) || (ch == 41) || (ch == 35));
}

/*Check if the charachter passed is a valid alphabet*/
bool isalphabet(char ch){
	return !isoperator(ch);
}

/*Preprocess the given regular expression and add '#' at places where concatenation is possible*/
string preprocessing(string regexp){
	string ans;
	char left, right;
	for(int i=0; i<regexp.length()-1; i++){
		left = regexp[i];
		right = regexp[i+1];
		ans+=left;
		if(isalphabet(left) || left==')' || left=='*'){
			if(isalphabet(right) || right=='(')
				ans+=char(35);
		}
	}
	ans+=regexp[regexp.length()-1];
	// cout << ans << endl;
	return ans;
}

/*push a deque of an alphabet state transitions into operand_stack*/
void push(char alpha){
	State *a1=new State(++global_id);
	State *a2=new State(++global_id);
	a1->addTransition(alpha,a2);
	// a2->setasfinal();
	deque<State*>table;
	table.push_back(a1);
	table.push_back(a2);
	operand_stack.push(table);
}

/*Sitaram*/

bool Pop(deque<State*> *b){
	if(!operand_stack.empty()){
		*b=operand_stack.top();
		operand_stack.pop();
		return true;
	}
	return false;
}

bool concat(){
	deque<State*>a;
	//cout<<&a<<"don"<<endl;
	deque<State*>b;
	if(!Pop(&b) || !Pop(&a)){
		return false;
	}
	//cout<<a[a.size()-1]->get_s_id()<<endl;
	a[a.size()-1]->addTransition(0,b[0]);
	a.insert(a.end(),b.begin(),b.end());
	operand_stack.push(a);
	
	return true;
}
bool star(){
	deque<State*>a;
	//deque<State*>b;
	if(!Pop(&a)){
		return false;
	}
	State* ss=new State(++global_id);
	State* es=new State(++global_id);
	ss->addTransition(0,a[0]);
	ss->addTransition(0,es);
	// es->setasfinal();
	a[a.size()-1]->addTransition(0,a[0]);
	a[a.size()-1]->addTransition(0,es);
	a.push_front(ss);
	a.push_back(es);
	operand_stack.push(a);
    return true;

}

bool unio(){
	deque<State*>a;
	deque<State*>b;
	if(!Pop(&a) || !Pop(&b)){
		return false;
	}
   State* ss=new State(++global_id);
   State* es=new State(++global_id);
   ss->addTransition(0,b[0]);
   ss->addTransition(0,a[0]);
   a[a.size()-1]->addTransition(0,es);
   b[b.size()-1]->addTransition(0,es);
   // es->setasfinal();
   b.push_back(es);
   a.push_front(ss);
   a.insert(a.end(),b.begin(),b.end());
   operand_stack.push(a);
   // cout << "in unio"  << operand_stack.top().front()->get_s_id() << endl;
   return true;
}

/*Sitaram*/



/*Dont know*/
bool evaluate(){
	if(operator_stack.size()>0){
		char operat = operator_stack.top();
		operator_stack.pop();
		switch(operat){
			case '*':
				return star();
				break;
			case '|':
				return unio();
				break;
			case '#':
				return concat();
				break;
			default:
				return false;
		}
	}
	return false;
}

bool precedence(char opLeft, char opRight){
	if(opLeft == opRight)
		return true;

	if(opLeft == '*')
		return false;

	if(opRight == '*')
		return true;

	if(opLeft == 35)
		return false;

	if(opRight == 35)
		return true;

	if(opLeft == '|')
		return false;
	
	return true;
}


/*This will create the NFA from regular expression*/
bool CreateNFA(string regexp){
	regexp = preprocessing(regexp);
	for(int i=0; i<regexp.length(); i++){
		char temp = regexp[i];

		if(isalphabet(temp)){
			push(temp);
		}
		else if(operator_stack.empty()){
			// cout << "temp = " << temp << endl;
			operator_stack.push(temp);
		}
		else if(temp=='('){
			// cout << "openbracket inserted" << endl;
			operator_stack.push(temp);
		}
		else if(temp==')'){
			while(operator_stack.top()!='('){
				if(!evaluate())
					return false;
			}
			operator_stack.pop();
		}
		else{
			while(!operator_stack.empty() && precedence(temp, operator_stack.top())){
				// cout << "this ran on temp = " << temp << endl;
				if(!evaluate())
					return false;
			}
			operator_stack.push(temp);
		}
	}

	while(!operator_stack.empty()){
		if(!evaluate())
			return false;
	}

	if(!Pop(&NFA)){
		cout << "error here" << endl;
		return false;
	}

	NFA[NFA.size()-1]->setasfinal();
	return true;
}
	
void createTable(){
	deque<State*> temp = NFA;
	vector<int> finalstates;
	cout<<endl<<"now creating NFA from the given RE...."<<endl;
	while(!temp.empty()){
		if(temp.front()->isfinal()){
			finalstates.push_back(temp.front()->get_s_id());
		}
		multimap<char, State*> as = temp.front()->getallTransitions();
		cout << "current state = " << temp.front()->get_s_id() << endl;
		multimap<char, State*>::iterator it;
	    for (it=as.equal_range('a').first; it!=as.equal_range('a').second; ++it){
	    	cout << "transitions on alphabet a are " << (*it).second->get_s_id() << endl;
	    }
	    for (it=as.equal_range('b').first; it!=as.equal_range('b').second; ++it){
	    	cout << "transitions on alphabet b are " << (*it).second->get_s_id() << endl;
	    }
	    for (it=as.equal_range('c').first; it!=as.equal_range('c').second; ++it){
	    	cout << "transitions on alphabet c are " << (*it).second->get_s_id() << endl;
	    }
	    for (it=as.equal_range(0).first; it!=as.equal_range(0).second; ++it){
	    	cout << "transitions on alphabet epsilon are " << (*it).second->get_s_id() << endl;
	    }
	    temp.pop_front();
	}
	// for(int i=0; i<finalstates.size(); i++){
	// 	cout << "\t" << finalstates[i];
	// }
	cout << endl;
}


void create_NFAtable(){
	int tstateid;
	char alphabets[5]={'a', 'b', 'c', 'd', 0};
	cout << "\ta\tb\tc\td\tepsilon" << endl;  
	while(!NFA.empty()){
		State *tstate = NFA.front();
		cout << tstate->get_s_id() << "\t";
		for(int i=0; i<5; i++){
			vector<State*> as = tstate->getTransitions(alphabets[i]);
			for(int j=0; j<as.size(); j++){
				cout << as[i]->get_s_id() << ",";
			}
			cout << "hello\t";
		}
		cout << endl;
		NFA.pop_front();
		cout << "popped";
	}
}