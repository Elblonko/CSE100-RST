#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <utility> // for std::pair

/*
 * Name: Matthew Schwegler
 * Login: cs100way
 * Student ID: A09293823
 * Assignment PA1
 */


template<typename Data>
class BST {

    protected:

        /** Pointer to the root of this BST, or nullptr if the BST is empty */
        BSTNode<Data>* root;

        /** Number of Data items stored in this BST. */
        unsigned int isize;


    public:

        /** iterator is an aliased typename for BSTIterator<Data>. */
        typedef BSTIterator<Data> iterator;

        /** Default constructor.
          Initialize an empty BST.
          */
        BST() : root(nullptr), isize(0)  {
        }


        /** Default destructor.
         *  It is virtual, to allow appropriate destruction of subclass objects.
         *  Delete every node in this BST.
         */ // 
        virtual ~BST() {

            //Call to deleteTree 
            deleteTree(root);

            //set root equal to nullptr
            root = nullptr;

        }

        /** Insert a Data item in the BST.
         *  Return a pair, with the pair's first member set to an
         *  iterator pointing to either the newly inserted element
         *  or to the equivalent element already in the set.
         *  The pair's second element is set to true
         *  if a new element was inserted or false if an
         *  equivalent element already existed.
         */ // 
        virtual std::pair<iterator,bool> insert(const Data& item) {
            /* Variable Declarations */

            /* Body of Functions */

            //Compare the node to root and recurse down the tree
            //if root is null
            if (root == nullptr ){
                //create node to be inserted
                BSTNode<Data>* insertNode = new BSTNode<Data>(item); 
                isize++;
                root = insertNode;
                return std::make_pair(BST<Data>::iterator(root), true );
            }


            //Create pair and return the iterator
            return recurseInsert(item, root);

        }


        /** Find a Data item in the BST.
         *  Return an iterator pointing to the item, or the end
         *  iterator if the item is not in the BST.
         */ //
        iterator find(const Data& item) const {

            /*Variable Declarations*/
            BSTNode<Data>* tempNode = root;

            //If node being searched for is the root
            /*
               if ( !(tempNode->data < item) && !(item < tempNode->data) ){
               return typename BST<Data>::iterator(tempNode);
               }
               */

            //Searches through the tree until match is found
            while ( tempNode ){

                //Checks if curr node is greater than item
                if ( item < tempNode->data ){

                    //Recurse left if less than
                    if(tempNode->left)
                        tempNode = tempNode->left;

                    //else item not found
                    else
                        return end(); 
                }

                //move right if items is larger than curr node
                else if (tempNode->data < item ){

                    if( tempNode->right )
                        tempNode = tempNode->right;

                    //else item not found
                    else
                        return end();
                }
                else{
                    return typename BST<Data>::iterator(tempNode);
                }
            }

            //item not found
            return end(); 
        }


        /** Return the number of items currently in the BST.
        */ // 
        unsigned int size() const {

            //return isize
            return isize;

        }

        /** Remove all elements from this BST, and destroy them,
         *  leaving this BST with a size of 0.
         */ //
        void clear() {

            if( root != nullptr ){
                //Delete the tree Post Order Traversal
                deleteTree(root);

                //Set root to nullptr
                root = nullptr;
            }            

        }

        /** Return true if the BST is empty, else false.
        */ // 
        bool empty() const {

            //Check if root is null
            if(root == nullptr)
                return true;

            return false;
        }

        /** Return an iterator pointing to the first item in the BST.
        */ // 
        iterator begin() const {

            //Given the root go left return iterator
            BSTNode<Data>* tempNode = root;
            if (tempNode == nullptr){
                return end();
            }

            //while loop to iterate to leftmost node
            while(tempNode->left){
                tempNode = tempNode->left;
            }

            //return the left most node as an iterator
            return typename BST<Data>::iterator(tempNode); 

        }

        /** Return an iterator pointing past the last item in the BST.
        */
        iterator end() const {

            //return nullptr for the end
            return typename BST<Data>::iterator(nullptr);

        }

        /*Private section for helper functions
         *
         * Function: recurseInsert
         * Recurses through the list to insert according to BST Rules
         * Input: Node to inset, Node of current position
         *
         * */
    private:
        virtual std::pair<iterator,bool> recurseInsert
            (const Data& item, BSTNode<Data>* tempNode){

                /*function body */


                //if item passsed in in less than current Node move left
                if ( item  < tempNode->data ){
                    if (tempNode->left == nullptr ){
                        //create Node to insert
                        BSTNode<Data>* insert = new BSTNode<Data>(item); 
                        tempNode->left = insert;
                        insert->parent = tempNode;
                        ++isize;
                        return std::make_pair(BST<Data>::iterator(insert), true );
                    }
                    else{
                        tempNode = tempNode->left;
                        return recurseInsert(item, tempNode);
                    }
                }

                //if item is greater than  current node move right
                else if ( tempNode->data < item ){
                    if (tempNode->right == nullptr ){
                        //create Node to insert
                        BSTNode<Data>* insert = new BSTNode<Data>(item); 
                        tempNode->right = insert;
                        insert->parent = tempNode;
                        ++isize;
                        return std::make_pair(BST<Data>::iterator(insert), true );
                    }
                    else{
                        tempNode = tempNode->right;
                        return recurseInsert(item, tempNode);
                    } 
                }

                //item found in the tree already return last node visisted
                return std::make_pair(BST<Data>::iterator(tempNode), false );
            }

        /*Function to delete the tree recursively given the root
         *Parameters: takes a pointer to the root node
         *Returns: Void but when returns tree has been delete
         * */
        void deleteTree(BSTNode<Data>* start){

            //check if start is null
            if(start){
                //if Left exists
                if(start->left){
                    deleteTree(start->left);
                }

                //If right exists
                if(start->right){
                    deleteTree(start->right);
                }

                //delete the current leaf node
                delete start;

                //decriments the size of the tree
                isize--;
            }
        }
};


#endif //BST_HPP
