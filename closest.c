/************************************************************************
 *                       CSCB63 Winter 2020
 *                  Assignment 1 - Reb-Black Trees
 *                  (c) Mustafa Quraish, Jan. 2020
 *
 * This is the file which should be completed and submitted by you
 * for the assignment. Make sure you have read all the comments
 * and understood what exactly you are supposed to do before you
 * begin. A few test cases are provided in `testClosest.c`, which
 * can be run on the command line as follows:
 *
 *  $> gcc testClosest.c -o testClosest
 *  $> ./testClosest         (or .\testClosest.exe if on Windows)
 *
 * I strongly advise that you write more test cases yourself to see
 * if you have expected behaviour, especially on the edge cases for
 * insert(). You are free to make any reasonable design choices for
 * the implementation of the data structure as long as (1) the outputs
 * are consistent with the expected results, and (2) you meet the
 * complexity requirement. Your closestPair() function will only
 * be tested with cases where there are unique solutions.
 *
 * All code implemented should be your own. You are allowed to look
 * up anything related to the C-programming aspect, however you should
 * not be using any code you found online, and implement this yourself.
 * It is in your best interest to do so, since we have fairly
 * sophisticated plagiarism detection software.
 *
 * If you have any questions regarding this assignment, you can ask them
 * on Piazza. However, it is NOT acceptible to be posting any part of the
 * solution code publicly. If you need to show your code to explain the
 * problem, you should be coming to office hours (TBA shortly on Piazza).
 * 
 * Mark Breakdown (out of 10):
 *  - 0 marks if the code does not pass at least 1 test case.
 *  - If the code passes at least one test case, then:
 *    - Up to 6 marks for successfully passing all the test cases
 *    - Up to 4 marks for meeting the complexity requirements for 
 *      the functions as described in the comments below.
 *
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/*
 * This defines the struct(ure) used to define the nodes
 * for the Reb-Black tree we are going to use for this
 * assignment. You need to add some more fields here to be
 * able to complete the functions in order to meet the
 * complexity requirements
 */
typedef struct rb_node {
  // Stores the value (key) of this node
  int value;

  // This character is either 'R' or 'B'
  // depending on the colour of the node.
  char colour;

  // Pointers to the children
  struct rb_node *left;
  struct rb_node *right;

  // TODO: Add the other fields you need
  // here to complete the assignment!


} RBNode;

RBNode *newNode(int value) {
  /*
   * This function dynamically allocates memory for a new node,
   * initializes it and returns a pointer to it. This is already
   * completed for you, so you don't have to worry about allocating
   * the memory if you haven't used C before.
   * 
   *  - Returns NULL if there was an error with memory allocation
   *    (you can just exit if this is the case)
   *  - The default colour for the node is set to Black
   *
   * TODO: Initialize the values of the new fields in the struct you
   *         have defined above to some default value. (If you don't,
   *         they will be assigned to 0).
   */

  RBNode *node = calloc(sizeof(RBNode), 1);

  if (node == NULL) {  // In case there's an error
    return NULL;
  }

  node->value = value;
  node->colour = 'R';
  node->left = NULL;
  node->right = NULL;

  // Initialize values of the new fields here...


  return node;
}

bool query(RBNode *root, int value) {
  RBNode *p = NULL;

  p = root;

  while (p != NULL) {
    if (p->value > value) {
      p = p->left;
    }
    else if (p->value < value) {
      p = p->right
    }
    else
    {
      return true;
    }
    
  }

  return false;
}

void recolour_nodes(RBNode *grand_parent) {
  if (grand_parent->colour == 'B') {
    grand_parent->colour == 'R';

    if (grand_parent->left->colour == 'B' && grand_parent->left != NULL) {
      grand_parent->left->colour == 'R';
    }
    else
    {
      grand_parent->left->colour == 'B';
    }

    if (grand_parent->right->colour == 'B' && grand_parent->right != NULL) {
      grand_parent->right->colour == 'R';
    }
    else
    {
      grand_parent->right->colour == 'B';
    }
        
  }
  else
  {
    grand_parent->colour == 'B';

    if (grand_parent->left->colour == 'B' && grand_parent->left != NULL) {
      grand_parent->left->colour == 'R';
    }
    else
    {
      grand_parent->left->colour == 'B';
    }

    if (grand_parent->right->colour == 'B' && grand_parent->right != NULL) {
      grand_parent->right->colour == 'R';
    }
    else
    {
      grand_parent->right->colour == 'B';
    }
  }
  
}

void rotation(RBNode *grand_parent, RBNode *parent, RBNode *new_node) {
  RBNode *temp = NULL;

  temp = grand_parent;

  if (grand_parent->left == parent && parent->left == new_node || grand_parent->right == parent && parent->left == new_node) {
    // right rotation
  }
  else if (grand_parent->right == parent && parent->right == new_node || grand_parent->left == parent && parent->right == new_node) {
    // left rotation
  }

}

RBNode *rebalance_tree(RBNode *root, RBNode *new_node) {
  RBNode *grand_parent = NULL;
  RBNode *parent = NULL;
  RBNode *p = NULL;

  p = root;

  if (root->left == NULL && root->right == NULL) {
    if (root->colour == 'R') {
      root->colour == 'B';
      return root;
    }
  }
  else if (root->left->left == NULL or root->left->right == NULL) {
    return root;
  }
  else if (root->right->left == NULL or root->right->right == NULL) {
    return root;
  }

  while (p->value != new_node->value) {
    if (p->value > new_node->value) {
      grand_parent = parent;
      parent = p;
      p = p->left;
    }
    else if (p->value < new_node -> value) {
      grand_parent = parent;
      parent = p;
      p = p->right;
    }
    else
    {
      if (p->colour == 'R' && parent->colour == 'R') {
        if (grand_parent->left == parent) {
          if (grand_parent->right->colour == 'R') {
            recolour_nodes(&grand_parent);
            root = rebalance_tree(&root, &parent);
          }
          else
          {
            rotation(&grand_parent, &parent, &p);
            root = rebalance_tree(root, parent);
          }
        }
        else
        {
          if (grand_parent->left->colour == 'R') {
            recolour_nodes(grand_parent);
            root = rebalance_tree(root, parent);
          }
          else
          {
            rotation(&grand_parent, &parent, &p);
            root = rebalance_tree(root, parent);
          }
          
        }
        
      }
    }
    
  }

  return root;
  
}

RBNode *insert(RBNode *root, int value) {
  /*
   * This function is supposed to insert the new RB-tree node `node`
   * into the RB-tree rooted at `root`.
   *
   * Preconditions:
   *  - The tree rooted at `root` is a valid RB-Tree, or NULL.
   *  - `value` is a positive integer in the range [1...1e6]
   *      (1 to a million, inclusive).
   *          { The upper bound here only exists to potentially
   *            help make the implementation of edge cases easier. }
   *
   * Postconditions:
   *  - Make a new node with the given `value` using newNode() and
   *      insert it the tree at `root`, ensuring that the  conditions
   *      for RB-Trees are not violated.
   *  - Return the new root of the tree. (This will be usually be)
   *      the same unless you are inserting into an empty tree, or
   *      there is a rotation at the root level.
   *  - If the value is already in the tree, do nothing and just return
   *      the root. You do not need to print an error message.
   *
   * An example call to this function is given below. Note how the
   * caller is responsible for updating the root of the tree:
   *
   *  RBNode *root = (... some tree is initialized ...);
   *  root = insert(root, 5); // Update the root!
   *
   * TODO: Complete this function, and ensure that it runs in
   *          O(log(n)) time, where `n` is the number of nodes in
   *          the tree before the insert.
   */
  
  RBNode *new_node = NULL;
  new_node = newNode(value);

  if (root == NULL) {
    root = new_node;
  }
  else {
    if (root->value > new_node->value) {
      root->left = insert(root->left, new_node->value);
    }
    else if (root->value < new_node->value) {
      root->right = insert(root->right, new_node->value);
    }     
  }

  return rebalance_tree(root, new_node);  // Placeholder statement... replace this.
}

void closestPair(RBNode *root, int *a, int *b) {
  /*
   * This function returns the closest pair of points in the tree rooted
   * at `root`. You can assume there are at least 2 values already in the
   * tree. Since you cannot return multiple values in C, for this function
   * we will be using pointers to return the pair. In particular, you need
   * to set the values for the two closest points in the locations pointed
   * to by `a` and `b`. For example, if the closest pair of points is
   * `10` and `11`, your code should have something like this:
   *
   *   (*a) = 10 // This sets the value at the address `a` to 10
   *   (*b) = 11 // This sets the value at the address `b` to 11
   *
   * NOTE1: Make sure `(*a)` stores the smaller of the two values, and
   *       `(*b)` stores the greater of the two values.
   * NOTE2: If there are multiple closest pairs, you can return any of them,
   *         as long as the condition above is satisfied.
   *
   *
   * TODO: Complete this function to return the correct closest pair.
   *       Your function should run in O(1) [constant] time regardless of
   *       the size of the tree, and should not modify the original tree
   *       in any way.
   */

  (*a) = 0;  // Placeholder values for the closest pair,
  (*b) = 0;  // replace these with the actual ones.
  return;
}

// QUERY() and DELETE() here are left out here. RB-Delete is fairly involved,
// and while understanding it is important, implementing it is a bit of a pain.
// Query on the other hand is trivial, and you have done this numerous times
// in your first year courses.

// End of Assignment 1
