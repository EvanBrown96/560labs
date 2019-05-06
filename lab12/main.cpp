#include "Graph.hpp"
#include "Edge.hpp"
#include "InputParser.hpp"
#include "ParseError.hpp"
#include <fstream>

int main(int argc, char** argv){

  // int* thing = new int*[3];
  // thing[0] = {0, 1, 4};
  // thing[1] = {-1, 0, 10};
  // thing[2] = {14, 2, 0};
  //
  // Graph(3, thing);

  if(argc <= 1){
    std::cout << "No input file provided, exiting.\n";
    return -1;
  }

  QuickQueue<int> input_data(10);

  std::ifstream f;
  f.open(argv[1]);

  int num_nodes;

  try{
    InputParser::parse(f, num_nodes, input_data);
  }
  catch(ParseError& err){
    f.close();
    std::cout << "Data could not be imported from " << argv[1] << "; error at position " << err.getErrPos() << "\n";
    return -1;
  }

  f.close();

  int** vals = new int*[num_nodes];
  for(int i = 0; i < num_nodes; i++){
    vals[i] = new int[num_nodes];
    for(int j = 0; j < num_nodes; j++){
      vals[i][j] = input_data.pop();
    }
  }

  // return 0;
  //
  // int** vals = new int*[5];
  // vals[0] = new int[5];
  // vals[0][0] = 0;
  // vals[0][1] = 5;
  // vals[0][2] = 7;
  // vals[0][3] = 11;
  // vals[0][4] = 8;
  // vals[1] = new int[5];
  // vals[1][0] = 5;
  // vals[1][1] = 0;
  // vals[1][2] = 6;
  // vals[1][3] = -1;
  // vals[1][4] = 12;
  // vals[2] = new int[5];
  // vals[2][0] = 7;
  // vals[2][1] = 6;
  // vals[2][2] = 0;
  // vals[2][3] = 9;
  // vals[2][4] = -1;
  // vals[3] = new int[5];
  // vals[3][0] = 11;
  // vals[3][1] = -1;
  // vals[3][2] = 9;
  // vals[3][3] = 0;
  // vals[3][4] = 7;
  // vals[4] = new int[5];
  // vals[4][0] = 8;
  // vals[4][1] = 12;
  // vals[4][2] = -1;
  // vals[4][3] = 7;
  // vals[4][4] = 0;

  Graph g(num_nodes, vals);
  // Edge*** dfs_res = g.bfs();
  //
  //
  // int iter = 0;
  // while(dfs_res[0][iter] != nullptr){
  //   std::cout << *dfs_res[0][iter] << ", ";
  //   iter++;
  // }
  // std::cout << "\n";
  //
  // iter = 0;
  // while(dfs_res[1][iter] != nullptr){
  //   std::cout << *dfs_res[1][iter] << ", ";
  //   iter++;
  // }
  // std::cout << "\n";
  //
  // Graph::cleanup_search(dfs_res);

  Edge** krusk = g.kruskal();

  int iter = 0;
  int total_cost = 0;
  while(krusk[iter] != nullptr){
    std::cout << *krusk[iter] << ", ";
    total_cost += krusk[iter]->cost;
    iter++;
  }
  std::cout << "\ncost: " << total_cost << "\n";

  Graph::cleanup_mst(krusk);

  for(int i = 0; i < 5; i++){
    delete[] vals[i];
  }
  delete[] vals;
  // DJS<int> x;
  // x.makeSet(12);
  // x.makeSet(19);
  // x.makeSet(45);
  // x.makeSet(2);
  // x.makeSet(99);
  // x.makeSet(43);
  // x.setUnion(19, 45);
  // std::cout << x.find(19)->getRootItem() << "\n";

  return 0;
}
