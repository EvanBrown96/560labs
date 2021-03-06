/**
 * @author: Evan Brown
 * @file: main.cpp
 * @date: 4/8/19
 * @brief: entrypoint to lab program
 */

#include "MinHeap.hpp"
#include "MaxHeap.hpp"
#include "QuickQueue.hpp"
#include "String.hpp"
#include "ParseError.hpp"
#include "InputParser.hpp"
#include <fstream>
#include "UserInput.hpp"

bool compare(const int& v1, const int& v2){
  return (v1 < v2);
}

int main(int argc, char** argv){

  if(argc <= 2){
    std::cout << "Expected usage: ./lab [m/M] input_file.txt\n";
    return -1;
  }

  QuickQueue<String> input_data(10);

  std::ifstream f;
  f.open(argv[2]);

  try{
    InputParser::parse(f, input_data);
  }
  catch(ParseError& err){
    f.close();
    std::cout << "Data could not be imported from " << argv[1] << "; error at position " << err.getErrPos() << "\n";
    return -1;
  }

  f.close();

  // create list of ints
  QuickQueue<int> int_data(input_data.getSize());

  while(!input_data.isEmpty()){
    int_data.push(input_data.pop().getInt());
  }

  Heap<5, int>* h;

  if(argv[1][0] == 'm'){
    std::cout << "Using min-heap...\n\n";
    h = new MinHeap<5, int>(int_data);
  }
  else if(argv[1][0] == 'M'){
    std::cout << "Using max-heap...\n\n";
    h = new MaxHeap<5, int>(int_data);
  }
  else{
    std::cout << "Expected usage: ./lab [m/M] input_file.txt\n";
    return -1;
  }

  UserInput ui(h);

  ui.start();

  delete h;

  return 0;

}
