#include <bits/stdc++.h>
#include "nfa2dfa.h"
using namespace std;

int dfa_global_id;
set<dfa*> visited;
set<dfa*> unvisited;
deque<dfa *> DFA;

dfa::dfa(int d_id, set<State*> childrens){
	id=d_id;
	final=false;
	set<State *>::iterator it;
	for (it=childrens.begin(); it!=childrens.end(); ++it){
		childs.insert(*it);
	}
}

int dfa::getid(){
	return id;
}


void dfa::insert_child(State *nfastate){
	childs.insert(nfastate);
}

set<State*> dfa::get_childs(){
	return childs;
}

bool dfa::isfinal(){
	return final;
}

void dfa::setasfinal(){
	final=true;
}

bool dfa::any_final_child(){
	set<State *>::iterator it;
	for (it=childs.begin(); it!=childs.end(); ++it){
		if((*it)->isfinal())
			return true;
	}
	return false;
}

multimap<char, dfa*> dfa::getallTransitions(){
	return transitions;
}


vector<dfa*> dfa::getTransitions(char alphabet){
	multimap<char, dfa*>::iterator it;
	vector<dfa*> ans;
    for (it=transitions.equal_range(alphabet).first; it!=transitions.equal_range(alphabet).second; ++it){
    	ans.push_back((*it).second);
    }
    return ans;
}




void dfa::add_transition(char ch, dfa *dfastate){
	transitions.insert(pair<char, dfa*>(ch, dfastate));
}





set<State*> ecl(set<State*> a){
	queue<State*>b;
	set<State*>::iterator it;
	set<State*>t;
	for (it=a.begin(); it!=a.end(); ++it)
    	{
    		b.push(*it);
    		t.insert(*it);
    	}	

    while(!b.empty()){
    		vector<State*>z=b.front()->getTransitions(0);
    		int j=z.size();
    	    for(int i=0;i<j;i++){
    	    	if(t.count(z[i])==0){
    	    		t.insert(z[i]);
    	    		b.push(z[i]);
    	    	}	
    	    }
    	    b.pop();
    }
	return t;
}

set<State *> move(set<State*> states, char ch){
	set<State*>::iterator it;
	vector<State*> trans;
	set<State*> ans;
	for(it=states.begin(); it!=states.end(); ++it){
		trans = (*it)->getTransitions(ch);
		for(int i=0; i<trans.size(); i++){
			if(ans.count(trans[i])==0){
				ans.insert(trans[i]);
			}
		}
	}
	return ans;
}

bool checkfordup(dfa *s0){
	for(int i=0; i<DFA.size(); i++){
		dfa *temp = DFA[i];
	}
}

// void create_dfa(){
// 	dfa_global_id=0;
// 	State*start_s =  NFA.front();
// 	set<State*> t;
// 	t.insert(start_s);
// 	set<State*> dfa_start = ecl(t);
// 	dfa *s0 = new dfa(++dfa_global_id, dfa_start);
// 	DFA.insert(s0);
// 	vector<set<State*>>d;
// 	map<set,int>m;
// 	d.push_back(dfa_start);
// 	m.insert(dfa_start,0);

// 	for(int it=0;it<d.size(),++it){
// 			if(m[d[it]==0){
// 				m[d[it]]=1;

// 				=move(d[it],a);
// 				move(d[it],b);
// 				move(d[it],c);
// 				move(d[it],0);//not required;
// 			}
// 	}
// }

// void print_childs(dfa* t){
// 	set<State*>::iterator it;
// 	// for(it=)
// }


void create_dfa(){
	vector<dfa*> unvisited, visited;
	State *start_s = NFA.front();
	set<State*> t;
	t.insert(start_s);
	set<State*> dfa_start = ecl(t);
	dfa *s0 = new dfa(++dfa_global_id, dfa_start);
	set<State*> haha = s0->get_childs();
	DFA.push_back(s0);
	unvisited.push_back(s0);
	char srm[26]={'a', 'b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	while(!unvisited.empty()){
		dfa *cur= unvisited[unvisited.size()-1];
		unvisited.pop_back();
		set<State*>t1;
		for(int i=0; i<=25; i++){
			set<State*> haha = cur->get_childs();
			t1=move(cur->get_childs(),srm[i]);
			t1=ecl(t1);

			if(t1.empty()){
				continue;
			}

			bool found=false;
			int j;
			for(j=0; j<DFA.size(); j++){
				if(DFA[j]->get_childs() == t1){
					found=true;
					break;
				}
			}
			if(!found){
				dfa *s1 = new dfa(++dfa_global_id, t1);
				cur->add_transition(srm[i], s1);
				set<State*> t1 = s1->get_childs();
				unvisited.push_back(s1);
				DFA.push_back(s1);
			}
			else{
				cur->add_transition(srm[i], DFA[j]);
			}
		}
	}
}


void printDFA(){
	deque<dfa*> temp = DFA;
	cout << "size of DFA is = " << temp.size() << endl;
	while(!temp.empty()){
		multimap<char, dfa*> as = temp.front()->getallTransitions();
		cout << "current state = " << temp.front()->getid() << endl;
		multimap<char, dfa*>::iterator it;
	    for (it=as.equal_range('a').first; it!=as.equal_range('a').second; ++it){
	    	cout << "transitions on alphabet a are " << (*it).second->getid() << endl;
	    }
	    for (it=as.equal_range('b').first; it!=as.equal_range('b').second; ++it){
	    	cout << "transitions on alphabet b are " << (*it).second->getid() << endl;
	    }
	    for (it=as.equal_range('c').first; it!=as.equal_range('c').second; ++it){
	    	cout << "transitions on alphabet c are " << (*it).second->getid() << endl;
	    }
	    for (it=as.equal_range(0).first; it!=as.equal_range(0).second; ++it){
	    	cout << "transitions on alphabet epsilon are " << (*it).second->getid() << endl;
	    }
	    temp.pop_front();
	}

}

void ayush(){
	deque<dfa*>::iterator it;
	for(it=DFA.begin(); it!=DFA.end(); ++it){
		if((*it)->any_final_child()){
			cout << "final state " << (*it)->getid() << endl;
		}
	}
}
void srm(){
	char y;
	cout<<"do u want to simulate string on generated DFA [y/n]"<<endl;
	cin>>y;
	while(y=='y'){
		string s;
		cout<<endl;
		cout<<"enter a string that u wannt to simulate string on generated DFA"<<endl;
		cin>>s;

		cout<<"simulation....."<<endl;
		int j1=s.size();
		deque<dfa*> temp = DFA;
		dfa *j=temp.front();
	     vector<dfa*>z;
	     int i;
		for(i=0;i<j1;i++){
			z=j->getTransitions(s[i]);
			
	     	if(z.empty()){
	     		break;
	     	}
	     	else{
	     		j=z[0];
	     		cout<<" "<<"on "<<s[i]<<" goes from"<<" "<<j->getid()<<"to"<<" "<<z[0]->getid()<<endl;
	     	}
		}
		int count=0;
		if(i==j1){
			deque<dfa*>::iterator it;
			for(it=DFA.begin(); it!=DFA.end(); ++it){
				if((*it)->any_final_child()){
					if((*it)->getid()==j->getid()){
						cout<<"we are in final state"<<endl;
						count=1;
					}

				}
			}
			if(count==0){
				cout<<"Given string is not in the language of give RE"<<endl;
			}
		}
		else {
			cout<<"stuck...."<<" ";
			cout<<"Given string is not in the language of give RE"<<endl;
		}
	cout<<endl;
	cout<<"do u want to simulate string on generated DFA [y/n]"<<endl;
	char x;
	cin>>x;
	y=x;
	}

}