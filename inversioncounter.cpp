/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Robert Miller
 * Version     : 1.0
 * Date        : 10/25/2021
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string.h>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long count = 0;
    for(int i = 0; i < length; i++){
        for(int j = i + 1; j < length; j++){
            if(array[i] > array[j]){
                count++;
            }
        }
    }
    return count;
}


/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    int *scratch = new int[length];
	long count = mergesort(array, scratch, 0, length - 1);
    delete[] scratch;
    return count;

}
static long mergesort(int array[], int scratch[], int low, int high) {
	long count = 0;
	if(low < high){
		int mid = low + (high - low)/2;
		count += mergesort(array, scratch, low, mid);
		count+= mergesort(array, scratch, mid + 1, high);
		int L = low;
        int H = mid + 1; 
        int J = low;
		//watched Borowski's video on this first, tried his method and IT DID NOT WORK AT ALL, so keeping the variable names and transferring to the slides
        //I tried, so hard, to not use scratch, but it took me 3 hours to try and find any successful method, and even then it didnt work on 2 fringe cases so UGH fine
        //I will use the slides
		while(L <= mid && H <= high){
			if(scratch[L] <= scratch[H]) {
				array[J++] = scratch[L++];
			}
			else {
				count += mid - L + 1;
				array[J++] = scratch[H++];
			}
		}
	    while (L <= mid){
	        array[J++] = scratch[L++];
		}
	    while (H <= high){
	        array[J++] = scratch[H++];
        }
	}
    for(int i = low; i <= high; i++) {
		scratch[i] = array[i];
	}
	return count;
}

int main(int argc, char *argv[]) {
	bool slow = false;
	if(argc > 2){
		cerr << "Usage: " << argv[0] << " [slow]";
		return 1;
	}
	if((argv[1] != NULL) && (strcmp("slow",argv[1]) == 0)){
		slow = true;
	}
	else if(argv[1] != NULL){
		cerr << "Error: Unrecognized option '" << argv[1] << "'.";
		return 1;
	}
    
    cout << "Enter sequence of integers, each followed by a space: " << flush;
    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    if(index == 0){
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }
	if(slow == true){
		cout << "Number of inversions: " << count_inversions_slow(&values[0], index) << endl;
	} else {
		cout << "Number of inversions: " << count_inversions_fast(&values[0], index) << endl; 
    }
    return 0;
}
