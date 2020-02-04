/************************************************************************
 *                       CSCB63 Winter 2020
 *                  Assignment 1 - Reb-Black Trees
 *                  (c) Mustafa Quraish, Jan. 2020
 *
 * This code imports and tests your solution to the assignment. This is
 * NOT comprehensive, passing these tests does not mean your program is
 * fully correct. You need to ensure this yourself. Feel free to add more
 * test cases here (it is strongly encouraged), but do not submit this 
 * file. You can compile and run these tests as follows:
 * 
 *  $> gcc testClosest.c -o testClosest
 *  $> ./testClosest         (or .\testClosest.exe if on Windows)
 *
 ************************************************************************/

#include "closest.c"    // Imports your code

// Frees the memory for the tree. You don't need to worry
// about this for the sake of the assignment, but it is 
// good practice to always free all the allocated memory
// before a function exits.
void RBfree(RBNode *root) {
    if (root == NULL) {
        return;
    }

    RBfree(root->left);
    RBfree(root->right);
    free(root);
    return;
}

int main(int argc, char *argv[]) {
    int a, b;

    RBNode *root = NULL;
    root = insert(root, 100);
    root = insert(root, 200);
    
    // Test one, two values in the tree
    closestPair(root, &a, &b);
    if (a != 100 || b != 200) {
        printf("Test one failed.\n");
    } else {
        printf("Passed test 1.\n");
    }

    /////////////////////////////////////////////////////////////////

    root = insert(root, 140);
    
    // Test two, checking if augmented values are updated
    //      properly after one more insert.
    closestPair(root, &a, &b);
    if (a != 100 || b != 140) {
        printf("Test 2 failed.\n");
    } else {
        printf("Passed test 2.\n");
    }

    /////////////////////////////////////////////////////////////////

    root = insert(root, 130);
    root = insert(root, 195);
    root = insert(root, 154);
    root = insert(root, 102);
    root = insert(root, 155);


    // Test three, after many inserts, checking if the closest
    //      pair found is still correct.
    closestPair(root, &a, &b);
    if (a != 154 || b != 155) {
        printf("Test 3 failed.\n");
    } else {
        printf("Passed test 3.\n");
    }

    /////////////////////////////////////////////////////////////////

    // There will be more test cases here when you are being marked...
    // Also, you need to make sure you meet the compelxity bounds! Half
    // the marks for this coding section will be for meeting the complexity
    // bound and having the right idea for implementation, the other half 
    // will be for passing all the test-cases.

    RBfree(root);   // `root` is unusable after this point. Set it to
                    // NULL first before making a new tree for testing.
    return 0;
}
