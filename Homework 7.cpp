// Homework 7.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 
// 

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;
// Queue added in from Canvas submissions

struct Vertex {
    int key;
    // known will be important for backtracking later
    bool known = false;
    int parent = 0;
    // vector to store the neighbors
    vector<int> neighbors;
    int pathCost = 0;

    string neighborPrint() {
        string neighbor;
        for (auto& i : neighbors) {
            neighbor.append(to_string(i).append(" "));
        }// for
        return neighbor;
    }// neighborPrint

    // friend function for printing
    friend ostream& operator << (ostream& os, Vertex& data) {
        os << "Key: " << data.key << endl
            << "Known: " << data.known << endl
            << "Parent: " << data.parent << endl
            << "Neighbors: " << data.neighborPrint() << endl
            << "Path Cost: " << data.pathCost << endl << endl;
        return os;
    }// friend
};// Vertex Structure

vector<Vertex> fileRead(string file) {
    int count;
    fstream fin;
    fin.open(file, ios::in);
    vector<Vertex> vertices;
    string line;
    // while loop for Vertex key
    while (getline(fin, line)) {
        Vertex v;
        stringstream s(line);
        string tmp;
        getline(s, tmp, ' ');
        v.key = stoi(tmp);
        // while loop for Vertex neighbors
        while (getline(s, tmp, ' ')) {
            // conditional to weed out -1
            if (tmp != "-1") {
                v.neighbors.push_back(stoi(tmp));
            }// if 
        }// while
        vertices.push_back(v);
    }// while
    vertices[0].known = true;
    return vertices;
}// fileRead

/* pseudo code
    Print-Path (G, s, v)
    -- requires: BFS has been run on G with vertex s
    -- ensures: the shortest path from s to v is printed if it exists
    1	if v == s
    2	   print s
    3	   else if v.Π == NIL
    4	      print "no path from " s " to " v " exists"
              else
    5	         Print-Path (G, s, v.Πs)
    6	         print v

    */
void PrintPath(vector<Vertex> G, int s, int v) {
    if (v == s) {
        cout << s << endl;
    }// if
    else if (G[v-1].parent == 0){
        cout << "no path from " << s << v << "exists" << endl;
    }// else if
    else {
        PrintPath(G, s, G[v-1].parent);
        cout << v << endl;
    }
}// PrintPath

int main()
{
    // import that data from the file, 
    // checking for -1
    // parsing -1 means new line
    // don't insert it
    
    vector<Vertex> graph = fileRead("maze.txt");
    
    // implement the shortest path
    /* pseudo code
    q.enqueue(v_start)
    while (!q.isEmpty()) {
        v = q.dequeue();
        for each w adjacent to v {
            if (w is unknown){
                w.cost = v.cost + 1
                w.known = true
                w.parent = v
                q.enqueue(w);
            }
        }
    }
    */
    queue<Vertex> pathFinder;
    pathFinder.push(graph[0]);
    int parent;
    while (!pathFinder.empty()) {
        Vertex v = pathFinder.front();
        pathFinder.pop();
        parent = v.key;
        for (int i = 0; i < v.neighbors.size(); i++) {
            int location = v.neighbors.at(i)-1;
            Vertex *w = &graph[location];
            if (!w->known) {
                w->pathCost = v.pathCost + 1;
                w->known = true;
                w->parent = parent;
                pathFinder.push(graph[location]);
            }// if
        }// for 

    }// while

    for (int i = 0; i < graph.size(); i++) {
        cout << graph[i] << endl;
    }

    cout << "\n" << graph.size();

    PrintPath(graph, 1, 100);

    return 0;
}// main


