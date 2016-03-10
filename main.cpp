#include <iostream>


#include "nfa2dfa.h"
#include "re2nfa.h"
using namespace std;

int main(){
	// State a(1), b(2);
	// a.addTransition('a', &b);
	// b.addTransition('a', &a);
	// a.addTransition('a', &a);
		// ios::sync_with_stdio(false);
		// cin.tie(0);
	
	/*this will get all the transitions for a state*/
	// multimap<char, State*> as = a.getallTransitions();
	// multimap<char, State*>::iterator it;
 //    for (it=as.equal_range('a').first; it!=as.equal_range('a').second; ++it){
 //    	cout << "transitions on alphabet a are " << (*it).second->get_s_id() << endl;
 //    }
	/*end here*/

	/*This will print all the transitins on alphabet'a'*/
	// vector<State*> as = b.getTransitions('a');
	// for(int i=0; i<as.size(); i++){
	// 	cout << "hello " << as[i]->get_s_id() << endl;
	// }
	/*end here*/

	/*this is for checking preprocessed string*/
	// string expression("abc*d");
	// string result=preprocessing(expression);
	// cout << "original String =" << expression << endl;
	// cout << "after preprocessing string = " << result << endl;
	/*end here*/

	// push('z');
	// deque<State *> ayu;
	// ayu = operand_stack.top();
	// vector<State*> as = (ayu.front())->getTransitions('z');
	// for(int i=0; i<as.size(); i++){
	// 	cout << "hello " << as[i]->get_s_id() << endl;
	// }
	string regexp;
	cout <<"Enter the regular expression:";
	cin >> regexp;
	CreateNFA(regexp);
	createTable();
	cout << "\n\nnow creating DFA from the given NFA....\n\n" << endl;
	create_dfa();
	printDFA();
	ayush();
	srm();
	return 0;
}