#include <iostream>
#include <cstring>

using namespace std;

/*
 * Author: Fiona Wang
 * Date: June 7th 2022
 * This is the main class for the graph creater program
 * The user can add or remove vertices and edges, and use Dijkstra's algorithms
 */

int main(){
  int graph[20][20];
  for(int i=0; i<20; i++){
    for(int j=0; j<20; j++){
      graph[i][j] = 0;
    }
  }
  
  return 0;
}
