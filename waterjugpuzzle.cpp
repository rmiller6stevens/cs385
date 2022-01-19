/*******************************************************************************
 * Name    : waterJug.cpp
 * Author  : Robert MIller
 * Version : 1.0
 * Date    : October 9th, 2021
 * Description : Does the water Jug Problem
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <queue>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

/*using the pseudo code from intro to water jug, may need to add the capacities in here?
string bfs(int a, int b, int c){
adds the intro state to the queue, (0,0,c)
while(queue is not empty){
	current = front of queue
	pop current from the queue
	if current = goal
	return the backtracked solution
	if current has already been seen
	maybe exit? if not then we will continue
	mark current as having been seen
	try the 6 solutions again
}
return no solution
}*/


/* returns a string OR part of the queue, or even a pointer 6checks(int aw, int bw, int cw, int ac, int bc, int cc){
	pointer would point to null if it fails, or something like that
	//aw = a water, ac = a capacity
	1 c -> a if(ac == aw || cw == 0)
		no solution
	else it does aw = aw + (cw -  (ac - aw)), and cw = cw - ac, must check that cw - ac is >= 0, revise in post
	2 b -> a if(ac == aw || bw ==0)
		no solution
	else it does the thing
	3 c -> b if(bc == bw || cw == 0)
		no solution
	else it does the thing
	4 a -> b if(bc == bw || aw == 0)
		no solution
	else it does the thing
	5 b -> c if(cc = cw || bw == 0)
		no solution
	else it does the thing
	6 a -> c if(cc == cw || aw == 0)
		no solution
	else it does the thing
}*/


//I think the best course of action to detect for no solution, or to end a branch, is to make:
//for(int i = 0; i <= (int)queue.size() - 1 [or whatever function returns the length of the queue]; i++){
//would find an infinate loop
	

int main() {
	int jugs[6];
	
	//checks for usage error:
	if(argc != 7){
	cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;;
	return 1;
	}
	
	//checks that all args are ints
	istringstream iss;
	for(int i = 1; i<= argc; i++){
		iss(argv[i]);
	if(!iss >> jugs[i-1]){
		if(i == 1){
		cerr << "Error: Invalid capacity '" << argv[i] << "' for jug A" << endl; 
		return 1;
		} else if(i == 2){
		cerr << "Error: Invalid capacity '" << argv[i] << "' for jug B" << endl; 
		return 1;
		} else if(i == 3){
		cerr << "Error: Invalid capacity '" << argv[i] << "' for jug C" << endl; 
		return 1;
		} else if(i == 4){
		cerr << "Error: Invalid goal '" << argv[i] << "' for jug A" << endl; 
		return 1;
		} else if(i == 5){
		cerr << "Error: Invalid goal '" << argv[i] << "' for jug B" << endl; 
		return 1;
		} else if(i == 6){
		cerr << "Error: Invalid goal '" << argv[i] << "' for jug C" << endl; 
		return 1;
		}
	}
		iss.clear();
		//if it gets through the checks, the array will be full of the correct values
	}
	//Goal error check for bad input
	if(jugs[3] > jugs[0]){
		cerr << "Error: Goal cannot exceed capacity of jug A" << endl;
		return 1;
	} else if(jugs[4] > jugs[1]){
		cerr << "Error: Goal cannot exceed capacity of jug B" << endl;
		return 1;
	} else if(jugs[5] > jugs[2]){
		cerr << "Error: Goal cannot exceed capacity of jug C" << endl;
		return 1;
	}
	//final error check that there is enough water to complete the task
	if(jugs[3] + jugs[4] + jugs[5] > jugs[2]){
	cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C" << endl;
	return 1;
	}
	
    State s(0, 0, 8, "Initial state.");
    cout << s.to_string() << endl;
    s.a += 3;
    s.c -= 3;
    cout << s.to_string() << endl;
    return 0;
}
