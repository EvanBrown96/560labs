#include "QuickQueue.hpp"

template <typename T>
Levelorder<T>::Levelorder(const BinarySearchTree<T>& bst):
  Traversal<T>(bst){

  int index = 0;
  creationHelper(bst.root, index);
}

template <typename T>
void Levelorder<T>::creationHelper(BSTNode<T>* st, int& index){

  QuickQueue<Node<T>*> qq(this->size);
  qq.push(st);

  while(!qq.isEmpty()){
    BSTNode<T>* next = qq.pop();

    if(next != nullptr){
      this->values[index] = new T(next->getValue());
      index += 1;

      qq.push(next->getLeft());
      qq.push(next->getRight());
    }
  }

}
