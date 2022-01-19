/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Julien Carr, Robert Miller
 * Version     : 1.0
 * Date        : 12/4/21
 * Description : Solve the all pairs shortest paths problem with Floyd’s algorithm.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <queue>
#include <stack>
#include <climits>
#include <fstream>

using namespace std;
int num_vertices = 0;
long INF = LONG_MAX /2;

string splitter(string line, size_t &lastindex) {
    size_t splitat = line.find(" ",lastindex);
    size_t splitsize = splitat - lastindex;
    string returnedstr = line.substr(lastindex, splitsize);
    lastindex = splitat + 1;
    return returnedstr;
}
//finds errors
int lineChecker(string line, int line_number, int maxvertices) {
    if (line.length() < 4) {
        cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
        return 1;
    }
    char MaxLetter = (maxvertices + 64);
    size_t lastindex = 0;
    int difference;
    string firstVert = splitter(line, lastindex);
    difference = firstVert[0] - 65;
    if ((firstVert.length() != 1) || (difference < 0 || difference > maxvertices)) {
        cerr << "Error: Starting vertex '" << firstVert << "' on line " << line_number <<" is not among valid values A-" << MaxLetter << "." << endl;
        return 1;
    }
    string secondVert = splitter(line, lastindex);
    difference = secondVert[0] - 65;
    if ((secondVert.length() != 1) || (difference < 0 || difference > maxvertices)) {
        cerr << "Error: Ending vertex '" << secondVert << "' on line " << line_number <<" is not among valid values A-" << MaxLetter << "." << endl;
        return 1;
    }
    int weightcheck;
    string weight = splitter(line, lastindex);
    stringstream is(weight);
    if((!(is >> weightcheck)) || (weightcheck <= 0)) {
        cerr << "Error: Invalid edge weight '" << weight << "' on line " << line_number << "." << endl;
        return 1;
    }
    return 0;
}

/*
* returns number of digits
*/
int len(long num) {
    int counter = 0;
    long longNum = num;
    if(num == 0){
        return 1;
    }
    while(longNum >= 1) {
        longNum = longNum / 10;
        counter++;
    }
    return counter;
}

 //actual project part
/**
* Displays the matrix on the screen formatted as a table.
*/
void display_table(long** const matrix, const string &label, const bool use_letters = false) {
 cout << label << endl;
 long max_val = 0;
 for (int i = 0; i < num_vertices; i++) {
    for (int j = 0; j < num_vertices; j++) {
        long cell = matrix[i][j];
        if (cell != INF && cell > max_val) {
        max_val = matrix[i][j];
            }
        }
    }

 int max_cell_width = use_letters ? len(max_val) :
 len(max(static_cast<long>(num_vertices), max_val));
 cout << ' ';
 for (int j = 0; j < num_vertices; j++) {
 cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
 }
 cout << endl;
 for (int i = 0; i < num_vertices; i++) {
 cout << static_cast<char>(i + 'A');
 for (int j = 0; j < num_vertices; j++) {
 cout << " " << setw(max_cell_width);
 if (matrix[i][j] == INF) {
 cout << "-";
 } else if (use_letters) {
 cout << static_cast<char>(matrix[i][j] + 'A');
 } else {
    cout << matrix[i][j];
    }
 }
 cout << endl;
 }
 cout << endl;
}

void floyds(long **&D, long **&I){
    for(int k = 0; k < num_vertices; k++){
        for(int i = 0; i < num_vertices; i++){
            for(int j = 0; j < num_vertices; j++){
                if(D[i][j] > (D[i][k] + D[k][j])){
                    I[i][j] = k;
                }
                D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
            }
        }
    }
}

queue<int> pathMaker(long **&I, int i, int j) {
    if (I[i][j] != INF) { //if intermediate
        int step = I[i][j];
        queue<int> path1 = pathMaker(I, i, step);
        queue<int> path2 = pathMaker(I, step, j);
        path1.pop();
        while(path1.empty() != true){
            int temp = path1.front();
            path2.push(temp);
            path1.pop();
        }
        return path2; //finished end path
    } else {
        queue<int> path;
        path.push(j);
        if(i==j){
            return path;
        }else{
            path.push(i);
            return path;
        }
    }

}
void fixDumbQueue(queue<int> &path){ //queue is for some god forsaken reason in reverse, fix it here
    stack<int> Stack;
    while (path.empty() != true) {
        Stack.push(path.front());
        path.pop();
    }
    while (Stack.empty() != true) { //tried using a stack instead of a queue when actually getting the values, ended up with duplicates so used a queue instead
        path.push(Stack.top());
        Stack.pop();
    }
}

void readMatrix(long **&D, long **&I){
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            char output = i + 65;
            char outputj = j + 65;
            if(I[i][j] == INF && D[i][j] == INF){
                cout << output << " -> " << outputj << ", distance: infinity, path: none" << endl;
            } else {
                cout << output << " -> " << outputj << ", distance: " << D[i][j] << ", path: ";
                if (i == j) {
                    cout << output << endl;
                } else {
                    queue<int> path = pathMaker(I, i, j);
                    fixDumbQueue(path); //now its in correct order
                    output = path.front() + 65;
                    cout << output;
                    path.pop();
                    while(path.empty() != true){
                        int temp = path.front();
                        output = temp + 65;
                        cout << " -> " << output;
                        path.pop();
                    }
                    cout << endl;
                }
        }
    }
}
}
//removes array pointers
void deleteMatrix(long **&D){
    for(int i = 0; i < num_vertices; i++){
        delete[] D[i];
    }
    delete[] D;
}

int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    string line;
    unsigned int line_number = 1;
    int maxvertices;
    getline(input_file, line);
    stringstream ss(line);
    if((!(ss >> maxvertices)) || (maxvertices < 1 || maxvertices > 26)) {
        cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
        return 1;
    }
    num_vertices = maxvertices;
    line_number++;


    //make matrix here D0
    long **matrix = new long*[maxvertices];
    for(int i = 0; i < maxvertices; i++) {
        matrix[i] = new long[maxvertices];
    }
    for(int i = 0; i < maxvertices; i++){
        for(int j = 0; j < maxvertices; j++){
            matrix[i][j] = INF;
        }
    }

    for(int i = 0; i < maxvertices; i++){
        matrix[i][i] = 0;
    }

    //blank for intermediate matrix
    long **matrix1 = new long*[maxvertices];
    for(int i = 0; i < maxvertices; i++) {
        matrix1[i] = new long[maxvertices];
    }
    for(int i = 0; i < maxvertices; i++){
        for(int j = 0; j < maxvertices; j++){
            matrix1[i][j] = INF;
        }
    }


    while (getline(input_file, line)) {
        if (lineChecker(line, line_number, maxvertices) == 1) {
            return 1;
        }
        size_t lastindex = 0;
        int i, j, k;
        string firstVert = splitter(line, lastindex);
        i = firstVert[0] - 65;
        string secondVert = splitter(line, lastindex);
        j = secondVert[0] - 65;
        string weight = splitter(line, lastindex);
        stringstream css(weight);
        css >> k;
        matrix[i][j] = k;
        css.clear();
        line_number++;
    }
    //display
    // Don't forget to close the file.
    display_table(matrix, "Distance matrix:");
    floyds(matrix, matrix1);
    display_table(matrix, "Path lengths:");
    display_table(matrix1, "Intermediate vertices:", true);
    readMatrix(matrix, matrix1);
    //clear up leaks
    deleteMatrix(matrix);
    deleteMatrix(matrix1);
    //delete matrix;
    //delete matrix1;
    //read function

    input_file.close();
    return 0;
}

