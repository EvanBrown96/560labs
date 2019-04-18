// 4/17

#ifndef SKEWHEAP_HPP
#define SKEWHEAP_HPP

#include "SkewNode.hpp"
#include "QuickQueue.hpp"
#include "EmptyStructure.hpp"

template <typename T>
class SkewHeap{

public:

  SkewHeap();

  SkewHeap(const QuickQueue<T>& initial_data);

  ~SkewHeap();

  SkewHeap(const SkewHeap<T>& copy);

  SkewHeap<T>& operator=(const SkewHeap<T>& copy);

  static SkewHeap<T> merge(const SkewHeap<T>& h1, const SkewHeap<T>& h2);

  void insert(const T& item);

  void deleteMax();

  T findMax() const;

  bool isEmpty() const;

  QuickQueue<T> inorder() const;

  QuickQueue<T> preorder() const;

  QuickQueue<T> postorder() const;

  QuickQueue<QuickQueue<T>> levelorder() const;

private:

  SkewNode<T>* root;

  void destroyHeap(SkewNode<T>* subtree);

  SkewNode<T>* copyHeap(SkewNode<T>* subtree);

  static SkewNode<T>* baseMerge(SkewNode<T>* st1, SkewNode<T>* st2);

  void preorderHelper(SkewNode<T>* subtree, QuickQueue<T>& qq);

  void inorderHelper(SkewNode<T>* subtree, QuickQueue<T>& qq);

  void postorderHelper(SkewNode<T>* subtree, QuickQueue<T>& qq);



};

#include "SkewHeap.cpp"

#endif // SKEWHEAP_HPP