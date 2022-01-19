/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Robert Miller
 * Date        : 9/28/2021
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

//This function is here just for spacing reasons
int numDigits(int num_stairs){
    int c = 0;
    while(num_stairs >= 1){
        num_stairs /= 10;
        c++;
    }
    return c;
}
vector< vector<int> > get_ways(int num_stairs) {
    //please dont question why I made a separate empty vector instead of just pushing back a new temp one
    vector< vector<int> >  ways;
    vector<int>  null;
    if(num_stairs <= 0){
        ways.push_back(null);
        //adds 'blank' steps at the end of everything and ends recursion step here
        return ways;
    } 
        for(int i = 1; i < 4; i++){
            if(num_stairs >= i){
                vector<vector<int> > result = get_ways(num_stairs - i);
                //recursion begins
                for(int j = 0; j <= (int)result.size() - 1; j++){
                    result.at(j).push_back(i);
                }
                for(vector<int> j : result){
                    ways.push_back(j);
                }
            }
        }
    return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    //in the last lab I casted each .size() but now I know I can just make it unsigned at the start
    for (int i = 0; i < (int) ways.size(); i++) {
		cout << setw(numDigits(ways.size())) << i + 1 << ". " << "[";
        //prints out the number of step and begins
		for (int j = (int)ways.at(i).size()-1; j > 0; j--) {
			cout << ways[i][j] << ", ";
		}
        //this prints out the final step, and is separate since so it doesn't put a comma there
		cout << ways[i][0] << "]" << endl;
	}
}

int main(int argc, char * const argv[]) {
    int num_stairs;
    int wSize = 0;
    //checks that the correct amount of arguments is used
if(argc != 2){
    cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
    return 1;
}
istringstream iss;
iss.str(argv[1]);
if(!(iss >> num_stairs)){
    cerr << "Error: Number of stairs must be a positive integer." << endl;
    return 1;
}
iss.clear();
//for memory leak
if(num_stairs <= 0){
    cerr << "Error: Number of stairs must be a positive integer." << endl;
    return 1;
}
wSize = (int)get_ways(num_stairs).size();
//had to print out for separate conditions
if(wSize == 1){
    cout << "1 way to climb " << num_stairs << " stair." << endl;
} else{
    cout << wSize << " ways to climb " << num_stairs << " stairs." << endl;
}
display_ways(get_ways(num_stairs));
return 0;
}
