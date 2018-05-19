#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

int* dijkstra(int arr[5][5], int arr_size, int node) {
  int *dist = new int[arr_size];
  for (int i = 0; i < arr_size; i++) {
    if (i == node) dist[i] = 0;
    else dist[i] = 100000;
  }
  
  int min, min_id, temp, position[5] = { 1,1,1,1,1 };
  do {
    min = 100000; min_id = 100000;
    for (int i = 0; i < arr_size; i++) {
      if ((position[i] == 1) && (dist[i] < 100000)) {
        min = dist[i];
        min_id = i;
      }
    }
    if (min_id != 100000) {
      for (int i = 0; i < arr_size; i++) {
        if (arr[min_id][i] > 0) {
          temp = min + arr[min_id][i];
          if (temp < dist[i]) dist[i] = temp;
        }
      }
      position[min_id] = 0;
    }
  } while (min_id < 100000);
  return dist;
}

//Function to solve travelling salesman problem;
int tsp_solver(int *a, int graph[5][5], int arr_size, int weight)
{
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (i == j) graph[i][j] = 0;
      else {
        if (graph[i][j] == 0) graph[i][j] = 100000;
  }  }  }
  
  int sum = 0, g = 0; 
  for (int i = 0; i <= arr_size - 1; i++) sum += graph[a[i % 5]][a[(i + 1) % 5]];
  if (weight > sum) weight = sum;
  while (g < 119) {
    sum = 0;
    int j = arr_size - 2;
    while (j != -1 && a[j] >= a[j + 1]) j--;
    if (j == -1) g = 119;
    int k = arr_size - 1;
    while (a[j] >= a[k]) k--; {
      swap(a[j], a[k]);
    }
    int l = j + 1, r = arr_size - 1;
    while (l < r) swap(a[l++], a[r--]);
    for (int i = 0; i <= arr_size - 1; i++) sum += graph[a[i % 5]][a[(i + 1) % 5]];
    if (weight > sum) weight = sum;
    g++;
  };
  return weight;
}

int main() {
  ofstream out; 
  out.open("746_Isakov_lab2.txt");
  const int V = 5;
  int graph[V][V];
  int arr[V] = { 0,1,2,3,4 };

//Manual input for edges' weight;
  cout << "Attention! Notice the lack of node to self's edge before typing. \n";
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
      if (i != j) {
        cout << "If node number " << i + 1 << " is connected with node number " << j + 1 << ", then enter edge's weight, otherwise enter 0: ";
        cin >> graph[i][j];
      }
      else graph[i][j] = 0;
    }
  }

// Adjacency matrix output;
  out << "\nAdjacency matrix is shown below:" << endl;
  cout << "\nAdjacency matrix is shown below:" << endl;
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
      out << graph[i][j] << " ";
      cout << graph[i][j] << " ";
    }
    out << endl;
    cout << endl;
  }

//Searching for the shortest ways;
  int start_node, dest_node = 1;
  cout << "\nPlease, type the desired starting node number: ";
  cin >> start_node;
  int *p = dijkstra(graph, V, start_node - 1);
  for (int i = 0; i < 5; i++) {
    if (p[i] >= 100000) {
      cout << "It is impossible to get from node number " << start_node << " to node number " << i + 1 << ";" << endl;
      out << "It is impossible to get from node number " << start_node << " to node number " << i + 1 << ";" << endl;
    }
    else {
      out << "Shortest way from node number " << start_node << " to node number " << dest_node << " equals " << p[i] << endl;
      cout << "Shortest way from node number " << start_node << " to node number " << dest_node << " equals " << p[i] << endl;
    }
    dest_node++;
  }

//Travelling salesman part of the code;  
  int sc_value = tsp_solver(arr, graph, V, 100000);
  if (sc_value >= 100000) {
    cout << "Attention! It is impossible to pass through all nodes! Check the data input." << endl;
    out << "Attention! It is impossible to pass through all nodes! Check the data input." << endl;
  }
  else {
    cout << "Shortest cycle equals: " << sc_value << endl;
    out << "Shortest cycle equals: " << sc_value << endl;
  }

//Closing part;
  delete[] p;
  out.close();
  _getch();
  return 0;
}