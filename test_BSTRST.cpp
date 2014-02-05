#include "BST.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include "RST.hpp"

using namespace std;

/**
 * A simple test driver for the BST class template.
 * P1 CSE 100 2013
 * Author: P. Kube (c) 2013
 */
int main() {

  /* Create an STL vector of some ints */
  vector<int> v;
  /*
  v.push_back(3);
  v.push_back(4);
  v.push_back(1);
  v.push_back(100);
  v.push_back(-33);
  v.push_back(-20);
  v.push_back(6);
  v.push_back(0);
  v.push_back(-1);
  v.push_back(-2);
  v.push_back(-3);
  v.push_back(-4);
  */

  /* Create an instance of BST holding int */
  BST<int> b;

  /* Insert a few data items. */
  vector<int>::iterator vit = v.begin();
  vector<int>::iterator ven = v.end();
  for(; vit != ven; ++vit) {
    // all these inserts are unique, so should return a std::pair
    // with second part true
    std::pair<BST<int>::iterator,bool> pr = b.insert(*vit);
    if(! pr.second ) {
      cout << "Incorrect bool return value when inserting " << *vit << endl;
      return -1;
    }
    if(*(pr.first) != *vit) {
      cout << "Incorrect iterator return value when inserting " << *vit << endl;
      return -1;
    }  
  }

  /* Test size. */
  cout << "Size is: " << b.size() << endl;
  if(b.size() != v.size()) {
    cout << "... which is incorrect." << endl;
    return -1;
  }

  /* Test find return value. */
  vit = v.begin();
  for(; vit != ven; ++vit) { 
    if(*(b.find(*vit)) != *vit) {
      cout << "Incorrect return value when finding " << *vit << endl;
      return -1;
    }
  }
  
  /* Sort the vector, to compare with inorder iteration on the BST */
  sort(v.begin(),v.end());

  /* Test BST iterator; should iterate inorder */
  cout << "traversal using iterator:" << endl;
  vit = v.begin();
  BST<int>::iterator en = b.end();
  BST<int>::iterator it = b.begin();
  for(; vit < ven; ++vit) {
    if(! (it != en) ) {
      cout << *it << "," << *vit << ": Early termination of BST iteration." << endl;
      return -1;
    }
    cout << *it << endl;
    if(*it != *vit) {
      cout << *it << "," << *vit << ": Incorrect inorder iteration of BST." << endl;
      return -1;
    }
    ++it;
  }
  /** Added a basic clear tests that checks for correct size after delete */
  cout << "OK." << endl;
  b.clear();
  cout << ((b.size() == 0) 
          ? "PASS: clear() size of tree: "
          : "FAIL: clear() Size of tree: ") << b.size()  << endl;
  

  /** ================================ Added test Cases =====================*/ 

  /* Test fixtures */
  vector<int> v2;
  srand(unsigned(time(NULL)));
  BST<int> b2;
  BST<int>* treeDestructorTest = new BST<int>();
  unsigned int numInspected = 0;
  unsigned int sizeOfInput = 0;

  for(int i = 1000; i >= -1000; i--){
    v2.push_back(i);
    sizeOfInput++;
  }

  /* randomize the ordering of -1000 - 1000 before inserting 
   * so we don't just test a linked list
   */
  std::random_shuffle(v2.begin(), v2.end());

  vector<int>::iterator vit2 = v2.begin();
  vector<int>::iterator ven2 = v2.end();

  /* insert all the items in the randomized vector into the bst 
   * and check the boolean return
   */
  while( vit2 != ven2 ){
    if( !(b2.insert(*vit2)).second ){
      cout << "incorrect boolean return value of insert for: "<< *vit2 <<endl;
      return -1;
    }
    ++vit2;    
  }

  cout << "PASS: insert() unique value, boolean return. " << endl;

  /* try to insert the values again. checking for correct return 
   * boolean on duplicate insertion.
   */
  for( vit2 = v2.begin(); vit2 != ven2; ++vit2 ){
    if( (b2.insert(*vit2)).second ){
      cout << "incorrect boolean return value of duplicate " 
           << "insert for: "<< *vit2 << endl;
      return -1;
    }
  } 

  cout << "PASS: insert() duplicate value, boolean return. " << endl;

  /** sort the vector for inorder traversal */
  sort(v2.begin(), v2.end());

  vector<int>::iterator vit3 = v2.begin();
  vector<int>::iterator ven3 = v2.end();
  
  BST<int>::iterator front = b2.begin();
  BST<int>::iterator back = b2.end();

  /* check that each returned element is the correct successor */
  for( ; vit3 != ven3; ++front, ++vit3 ){
    if( *front !=  *vit3 ){
      cout << "FAIL: inorder traversal failed on : " << *front 
           << " " << *vit3 << endl;
      return -1;
    }
    ++numInspected;
  }

  cout << "PASS: iterator correct element ordering in traversal. " << endl;

  /* check we traversed all the elements in the tree */
  if( numInspected != sizeOfInput ){
    cout << "FAIL: incomplete tree traversal. Read " << numInspected
         << " of " << sizeOfInput << " elements." << endl;
    return -1;
  }else{
    cout << "PASS: iterator number of elements read Expected: " 
         << sizeOfInput << " Result: " 
         << numInspected << endl;
  }

  /* randomize the vector again */
  std::random_shuffle(v2.begin(), v2.end());

  /* test find on all the items in the vector & bst */
  for(vit3 = v2.begin(); vit3 != ven3; ++vit3){
    if( *(b2.find(*vit3)) != *vit3 ){
      cout << "FAIL: find return value did not match: " << *vit3 << endl;  
      return -1;
    }
  }

  cout << "PASS: find() returned all correct values." << endl;
  cout << ( (b2.size() == sizeOfInput) 
            ? "PASS: size() returned expected tree size. " 
            : "FAIL: size() returned non-matching tree size. " ) << endl;
  cout << ( (b2.empty() == false)
            ? "PASS: empty() returned false when not empty. "
            : "FAIL: empty() returned true when not empty. " ) << endl;
  b2.clear();
  cout << ( (b2.empty() == true)
            ? "PASS: empty() returned true when empty. "
            : "FAIL: empty() returned false when empty. " ) << endl;
  
  /** Test for memory leaks when allocating a tree on the heap 
   *  using valgrind will tell you if this passes or not
   */
  treeDestructorTest->insert(1);
  treeDestructorTest->insert(2);
  treeDestructorTest->insert(0);

  treeDestructorTest->clear();

  treeDestructorTest->insert(3);
  treeDestructorTest->insert(5);
  treeDestructorTest->insert(0);
  delete treeDestructorTest;

  cout << "PASS: No errors when calling destructor after clear(). i" << endl;
  cout << "      Run valgrind for memory leak analysis. " << endl;


/*****************************START Testing for RST***********************/
    RST<int> r;

  /* Insert a few data items. */
  vit = v.begin();
  //vector<int>::iterator ven = v.end();
  for(; vit != ven; ++vit) {
    // all these inserts are unique, so should return a std::pair
    // with second part true
    std::pair<RST<int>::iterator,bool> pr = r.insert(*vit);
    if(! pr.second ) {
      cout << "Incorrect bool return value when inserting into RST " << *vit << endl;
      return -1;
    }
    if(*(pr.first) != *vit) {
      cout << "Incorrect iterator return value when inserting into RST " << *vit << endl;
      return -1;
    }  
  }

  //PASS insert rst test
  cout << "PASS Insert into RST" << endl;

   /* Test size. */
  cout << "Size is: " << r.size() << endl;
  if(r.size() != v.size()) {
    cout << "... which is incorrect." << endl;
    return -1;
  }

  /* Test find return value. */
  vit = v.begin();
  for(; vit != ven; ++vit) { 
    if(*(r.find(*vit)) != *vit) {
      cout << "Incorrect return value when finding " << *vit << endl;
      return -1;
    }
  }
  
  /* Sort the vector, to compare with inorder iteration on the BST */
  sort(v.begin(),v.end());

  /* Test BST iterator; should iterate inorder */
  cout << "traversal using iterator:" << endl;
  vit = v.begin();
  //BST<int>::iterator en = r.end();
  //BST<int>::iterator it = r.begin();
  for(; vit < ven; ++vit) {
    if(! (it != en) ) {
      cout << *it << "," << *vit << ": Early termination of BST iteration." << endl;
      return -1;
    }
    cout << *it << endl;
    if(*it != *vit) {
      cout << *it << "," << *vit << ": Incorrect inorder iteration of BST." << endl;
      return -1;
    }
    ++it;
  }
  /** Added a basic clear tests that checks for correct size after delete */
  cout << "OK." << endl;
  r.clear();
  cout << ((r.size() == 0) 
          ? "PASS: clear() size of tree: "
          : "FAIL: clear() Size of tree: ") << r.size()  << endl;
  




//END OF FILE
}


