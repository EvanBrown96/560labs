/**
 * @author: Evan Brown
 * @file: Heap.cpp
 * @date: 4/6/19
 * @brief: implementation of general heap functions
 */

#include <math.h>
#include <iostream>

template <int ch, typename T>
Heap<ch, T>::Heap(bool (*compare)(const T& v1, const T& v2)):
  data(new T*[1]), size(1), count(0), compare(compare){}

template <int ch, typename T>
Heap<ch, T>::~Heap(){
  destroyHeap();
}

template <int ch, typename T>
void Heap<ch, T>::insert(const T& val){
  if(size == count) resizeHeap();

  data[count] = new T(val);

  int iter = count;
  count++;

  while(iter > 0 && indexCompare(iter, parent(iter))){
    swap(iter, parent(iter));
    iter = parent(iter);
  }
}

template <int ch, typename T>
void Heap<ch, T>::deleteRoot() throw(EmptyStructure){
  if(count == 0) throw EmptyStructure();

  safeRemove(0);
}

template <int ch, typename T>
void Heap<ch, T>::levelOrder() const{

  int line = 0;
  for(int i = 0; i < count; i++){
    std::cout << *data[i] << " ";
    if(i == line){
      std::cout << "\n";
      line = (line+1)*ch;
    }
    else if(i%ch == 0){
      std::cout << "- ";
    }
  }

  std::cout << "\n\n";

}

template <int ch, typename T>
void Heap<ch, T>::destroyHeap(){
  for(int i = 0; i < count; i++){
    delete data[i];
  }
  delete[] data;
}

template <int ch, typename T>
void Heap<ch, T>::resizeHeap(){
  T** old_data = data;
  data = new T*[(size*ch)+1];

  for(int i = 0; i < count; i++){
    data[i] = old_data[i];
  }

  delete[] old_data;
  size = (size*ch)+1;
}

template <int ch, typename T>
int Heap<ch, T>::parent(int child) const{
  return (child-1)/ch;
}

template <int ch, typename T>
void Heap<ch, T>::swap(int idx1, int idx2){
  T* store = data[idx1];
  data[idx1] = data[idx2];
  data[idx2] = store;
}

template <int ch, typename T>
void Heap<ch, T>::safeRemove(int index){

  count--;
  delete data[index];
  data[index] = data[count];

  pushDown(index);

}

template <int ch, typename T>
void Heap<ch, T>::pushDown(int index){

  if(index >= count) return;

  int worthy = index*5+1;

  // find most worthy child
  for(int child = worthy+1; child < worthy+5 && child < count; child++){
    if(indexCompare(child, worthy)) worthy = child;
  }

  // do a swap if necessary
  if(indexCompare(worthy, index)){
    swap(worthy, index);
    pushDown(worthy);
  }

}

template <int ch, typename T>
bool Heap<ch, T>::indexCompare(int idx1, int idx2) const{
  return compare(*data[idx1], *data[idx2]);
}