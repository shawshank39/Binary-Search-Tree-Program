/**********************************************************************************
 * Code FileName: Shaw-Assn5-Prog.cpp
 * Description: Program creates a empty binary tree, reads in integer data from a 
 *              text file the user specifies. Then the program displays a menu of 5
 *              choices to the user and prompts for user input. The program will then 
 *              perform the action the user chooses. The program will continue looping
 *              to display the menu and running the action the user specifies until 
 *              the user select to exit the program.
 * Class/Term: CS372 Spring 8 Week 1
 * Designer: Kevin Shaw
 * Functions: 
 *      UserMenu - Display a menu of choices to the screen.
 *      DoesFileOpen - Determines if a file opens.
 *      GetFileName - Prompts the user for the name of the file and validates.
 *      CreateTree - Initializes an empty Binary Tree.
 *      FindNode - Searches the Binary Tree for a value.
 *      CreateNode - Dynamically allocates memory and creates a Binary Tree Node.
 *      InsertNode - Inserts a new node into the Binary Tree.
 *      DeleteFromTree - Deletes a current node from the Binary Tree.
 *      DeleteNode - Searches the tree and if node is found the location is determined.
 *      IsEmpty - Determines if a Binary Tree is empty or not.
 *      InOrderDisplay - Displays the values in the Binary Tree in order.
 *      FreeNodes - Deallocates the memory used for the tree.
 *      DestroyTree - Used to delete the Binary Search tree.
 *      ReadIntFile - Reads data from text file and inserts into the tree.
 *      GetUserInput - Prompts for and returns a users choice.
 *      MenuManager - Runs the users chosen option.
 *      DisplaySubTree - Displays the subtree of a given node.
 *      GetInteger - Prompts for a validates an integer value from the user.
 **********************************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

//Structures
struct BTNode {
    int value;
    BTNode* left;
    BTNode* right;
};
struct treeTop{
    int count;
    BTNode* root;
};

//constants
const int MAX_NUM = 9999;
const int MIN_NUM = 1;

// Prototypes
void UserMenu();
bool DoesFileOpen(string);
string GetFileName ();
void CreateTree (treeTop& tree);
bool FindNode(treeTop& tree, int searchItem, BTNode* &current);
BTNode* CreateNode (int insertItem);
void InsertNode(treeTop& tree, BTNode* newNode);
void DeleteFromTree (treeTop& tree, BTNode* &deleteNode);
void DeleteNode (treeTop& tree, int deleteItem);
bool IsEmpty (treeTop& tree);
void InOrderDisplay(BTNode* currentNode, int& count);
void FreeNodes(BTNode* &currentNode);
void DestroyTree(treeTop& tree);
void ReadIntFile(treeTop& tree);
char GetUserInput();
void MenuManager (treeTop& tree, char userChoice);
void DisplaySubTree(BTNode* &item);
int GetInteger ();

/**********************************************************************************
 * Function:    main
 * Description: Function displays the program title to the screen, then creates a 
 *              new binary search tree. Next the function calls ReadIntFile to read
 *              integer data from a text file. The function then loops, calling
 *              GetUserInput to display a message to the user and get their choice, 
 *              and calls MenuManager to run the users selected option. Once the user
 *              selects to exit the program the loop terminates and the program exits.
 * Input:       N/A
 * Output:
 *      Returns: 0 if the program ran correctly.
 * Calls to:    CreateTree, ReadIntFile, GetUserInput, MenuManager
 **********************************************************************************/
int main() {

    treeTop binaryTree;
    
    char userChoice;
    
    cout << "Binary Tree Program" << endl;
    
    CreateTree(binaryTree);
    
    ReadIntFile(binaryTree);
    
    cout << endl << "Total Number of integers stored in the Binary Tree: " 
         << binaryTree.count << endl << endl;
    
    do
    {
        // Display Menu and validate user input
        userChoice = GetUserInput();
        cout << endl;
        
        MenuManager(binaryTree, userChoice);
        cout << endl;
        
    } while(userChoice != 'E');
    
    return 0;
}


/**********************************************************************************
 * Function:        UserMenu
 * Description:     Function UserMenudisplays a menu to the user.
 * Input:           N/A
 * Output:          N/A
 * Calls to:        N/A
 **********************************************************************************/
void UserMenu()
{
    cout << endl << "Choose from one of the below options;" << endl;
    cout << setw(6) << "A" << ") Display all integers in the binary tree." << endl;
    cout << setw(6) << "B" << ") Add a value to the tree." << endl;
    cout << setw(6) << "C" << ") Delete a value from the tree." << endl;
    cout << setw(6) << "D" << ") Find a value within the binary tree, and display subtree." << endl;
    cout << setw(6) << "E" << ") Exit the program." << endl;
    
}

/*********************************************************************************
 *  Function:       DoesFileOpen
 *  Description:    Function DoesFileOpen gets a string file name as an input 
 *                  parameter and then tests to see if the file opens or not. 
 *                  Lastly, the function returns true or false depending if the 
 *                  file opened or not.  
 *  Input:
 *      Parameter:  fileName - string containing the file name to be tested.
 *  Output: 
 *      Returns:    fileOpened - bool value for if the file opened or not.
*********************************************************************************/
bool DoesFileOpen(string fileName)
{
    bool fileOpened;   // Does the file open?
    ifstream testOpen; // ifstream variable for the file. 
    
    // Attempts to open the file
    testOpen.open(fileName);
    
    // If file opens...
    if (testOpen)
        fileOpened = true;
    else // Else... file doesn't open.
        fileOpened = false;
    
    // Closes the file before returning
    testOpen.close();
    
    return fileOpened;
}

/**********************************************************************************
 * Function:    GetFileName
 * Description: Function prompts for the filename of the text file to be used in the
 *              program, calls DoesFileOpen to validate the file exists and will open,
 *              and returns the validated filename.
 * Input:       N/A
 * Output:
 *      Returns: fileName - Validated string filename to be opened
 * Calls to:    DoesFileOpen
 **********************************************************************************/
string GetFileName ()
{
    bool fileOpens = false;
    string fileName;
    
    do 
    {
        
        cout << "Enter the name of the file you wish to open." << endl;
        cin >> fileName;
        
        fileOpens = DoesFileOpen(fileName);
        
        if (!fileOpens)
            cout << endl << "Error: File does not open, try again."<< endl << endl;
        
    } while (!fileOpens);
    
    
    
    return fileName;
}

/**********************************************************************************
 * Function:    CreateTree
 * Description: Function initializes a binary search tree to null.   
 * Input:           
 * 	Parameter: tree - unintialized binary tree
 * Output:
 *      Parameter: tree - initialized binary tree by reference.
 * Calls to:    N/A
 **********************************************************************************/
void CreateTree (treeTop& tree)
{
    tree.count = 0;
    tree.root = NULL;
    
}

/**********************************************************************************
 * Function:    FindNode
 * Description: Function takes a Binary Tree of integers, integer to search for and
 *              a Binary Tree node as input parameters. The function then traverses
 *              the tree until the item has been found or the end of the tree has
 *              been reached. The function then returns a bool value for if the value
 *              has been found or not and the location of the value in the tree.
 * Input:      
 * 	Parameters:
 *          tree - Binary tree of integers.
 *          searchItem - integer value to search for.
 *          current - Binary Tree node to return if found.
 * Output:
 *      Parameters:
 *          tree - by reference
 *          current - by reference
 * Calls to:    N/A
 **********************************************************************************/
bool FindNode(treeTop& tree, int searchItem, BTNode* &current)
{
    bool found = false;
    
    // If tree is empty
    if (tree.root == NULL)
        cout << endl << "Cannot search Empty Tree" << endl << endl;
    else // Else.. search the tree.
    {
        current = tree.root;
        
        while ((current != NULL) && !found)
        {
            if (current->value == searchItem)
                found = true;
            else if (current->value > searchItem)
                current = current->left;
            else
                current = current->right;
        }// end while
    }// end else
    
    return found;
    
}

/**********************************************************************************
 * Function:    CreateNode
 * Description: Function dynamically creates a new node. If memory allocation is 
 *              successful the function will assign the integer value to the 
 *              new node and assign the initalize the right and left values to NULL
 * Input:           
 * 	Parameter: insertItem - integer value to be inserted in the tree.
 * Output:
 *      Returns: newNode - newly created node.
 * Calls to:    N/A
 **********************************************************************************/
BTNode* CreateNode (int insertItem)
{
    BTNode* newNode;
    
    newNode = new BTNode;
    
    if (newNode != NULL)
    {
        newNode->value = insertItem;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    
    return newNode;
}

/**********************************************************************************
 * Function:    InsertNode
 * Description: Function takes a binary tree and a node to be inserted as input
 *              parameters and traverses the tree to find the correct location to
 *              insert the new node. Once the location is found, the function then 
 *              inserts the new node into the tree.
 * Input:           
 * 	Parameters:
 *          tree - Binary Tree
 *          newNode - Pointer to newly created node.
 * Output:
 *      Parameter: tree - by reference
 * Calls to:    
 **********************************************************************************/
void InsertNode(treeTop& tree, BTNode* newNode)
{
    BTNode *current; // Pointer to traverse the tree.
    BTNode *trailCurrent; // Pointer behind current.
    
    // if the tree is empty..
    if (tree.root == NULL)
        tree.root = newNode;
    else
    {
        // else begin traversing the tree. 
        current = tree.root; 
        
        // traverse the tree to find the correct location
        while (current != NULL)
        {
            trailCurrent = current;
            
            // If current value is greater the newnode go left
            if (current->value > newNode->value)
                current = current->left;
            else // else go right
                current = current->right;
            
        } // End While
        
        if (trailCurrent->value > newNode->value)
            trailCurrent->left = newNode;
        else
            trailCurrent->right = newNode;
        
    } // End Else
    
    tree.count++;
}

/**********************************************************************************
 * Function:    DeleteFromTree
 * Description: Function takes a Binary Tree and pointer as input parameters and then
 *              deletes the node from the tree.
 * Input:           
 * 	Parameters:
 *          tree - Binary Tree
 *          deleteNode - Pointer to the node to be deleted.
 * Output:
 *      Parameters:
 *          tree - by reference.
 *          deleteNode - by reference.
 * Calls to:        N/A
 **********************************************************************************/
void DeleteFromTree (treeTop& tree, BTNode* &deleteNode)
{
    BTNode* current; // Pointer to traverse the tree.
    BTNode* trailCurrent; // Pointer behind current
    BTNode* temp; // pointer to delete the node.
    
    if (deleteNode == NULL)
    {
        cout << "Error: The node to be deleted is NULL." << endl;
    }
    else if ((deleteNode->left == NULL) && (deleteNode->right == NULL))
    {
        temp = deleteNode;
        deleteNode = NULL;
        delete temp;
    }
    else if (deleteNode->left == NULL)
    {
        temp = deleteNode;
        deleteNode = temp->right;
        delete temp;
    }
    else if (deleteNode->right == NULL)
    {
        temp = deleteNode;
        deleteNode = temp->left;
        delete temp;
    }
    else
    {
        current = deleteNode->left;
        trailCurrent = NULL;
        
        while(current->right != NULL)
        {
            trailCurrent = current;
            current = current->right;
        }
        
        deleteNode->value = current->value;
        
        if (trailCurrent == NULL)
            deleteNode->left = current->left;
        else
            trailCurrent->right = current->left;
        
        delete current;
    } // End Else 
    
}

/**********************************************************************************
 * Function:    DeleteNode
 * Description: Function takes a binary tree and integer value as input parameters.
 *              The function than traverses the tree to determine if the value is 
 *              found. If not found, displays a message to the user stating so. If 
 *              found, the function then calls DeleteFromTree to have the delete the
 *              node from the tree.
 * Input:
 * 	Parameters:
 *          tree - Binary Tree
 *          deleteItem - integer value to search and delete.
 * Output:          N/A
 * Calls to: DeleteFromTree
 **********************************************************************************/
void DeleteNode (treeTop& tree, int deleteItem)
{
    BTNode* current; // pointer to traverse the tree.
    BTNode* trailCurrent; // Pointer behind current
    bool found = false;
    
    if (tree.root == NULL)
        cout << "Cannot Delete from the empty tree." << endl;
    else
    {
        current = tree.root;
        trailCurrent = tree.root;
        
        while (current != NULL && !found)
        {
            if (current->value == deleteItem)
                found = true;
            else
            {
                trailCurrent = current;
                
                if (current->value > deleteItem)
                    current = current->left;
                else
                    current = current->right;
            }//end else
        } // end while
        
        if (current == NULL)
            cout << deleteItem << " is not in the tree." << endl;
        else if (found)
        {
            if (current == tree.root)
                DeleteFromTree(tree, tree.root);
            else if (trailCurrent->value > deleteItem)
                DeleteFromTree(tree, trailCurrent->left);
            else
                DeleteFromTree(tree, trailCurrent->right);
            
            tree.count--;
        }
        
        
    }
}

/*********************************************************************************
 *  Function: emptyList
 *  Description: Function emptyList takes a list as a return parameter and returns
 *                  whether or not the list is empty by checking if the top of the
 *                  list is pointing to NULL or not.  
 *  Input:
 *      Parameter: list - list of nodes to be tested.
 *  Output: 
 *      Returns: bool value for if the list.top is equal to NULL or not.
*********************************************************************************/
bool IsEmpty (treeTop& tree)
{   
    return (tree.root == NULL);
}

/**********************************************************************************
 * Function:    InOrderDisplay
 * Description: Function takes a Binary Tree and integer count variable as input
 *              parameters. Function then recursively traverses the tree and displays
 *              all the integers in order in rows of 10.
 * Input:
 * 	Parameters:
 *          currentNode - pointer used to traverse the tree.
 *          count - count variable used to allow for newline characters after 10 ints
 * Output:
 *      Parameters:
 *          currentNode - by reference
 *          count - by reference
 * Calls to:    InOrderDisplay
 **********************************************************************************/
void InOrderDisplay(BTNode* currentNode, int& count)
{
    if (currentNode != NULL)
    {
        if (count % 10 == 0)
            cout << endl;
        count++;
                
        InOrderDisplay(currentNode->left,count);
        cout << setw(4) << currentNode->value << " ";
        InOrderDisplay(currentNode->right,count);
    }
        
}

/**********************************************************************************
 * Function:    FreeNodes
 * Description: Function FreeNodes takes a current node as an input parameter and 
 *              deletes all memory one node at a time.
 * Input:
 * 	Parameters: currentNode - current node to deallocate
 * Output:
 *      Parameters: currentNode - by reference.
 * Calls to:        N/A
 **********************************************************************************/
void FreeNodes(BTNode* &currentNode)
{
    if (currentNode != NULL)
    {
        FreeNodes(currentNode->left);
        FreeNodes(currentNode->right);
        delete currentNode;
        currentNode = NULL;
    }
}

/**********************************************************************************
 * Function:    DestroyTree
 * Description: Function calls FreeNodes to deallocate all memory currently used for
 *              the Binary Tree.
 * Input:           
 * 	Parameter: tree - Binary Tree
 * Output:
 *      Parameter: tree - by reference
 * Calls to:    FreeNodes
 **********************************************************************************/
void DestroyTree(treeTop& tree)
{
    FreeNodes(tree.root);
    
}

/**********************************************************************************
 * Function:    ReadIntFile
 * Description: Function ReadIntFile takes an empty binary tree as an input parameter.
 *              The function then calls GetFileName to prompt the user for the
 *              filename of the integer file. The function then reads one integer at
 *              a time, checks to see if the integer exists in the Binary Tree. If
 *              the integer doesn't exist, a new node is created and inserted into the
 *              tree. 
 * Input:           
 * 	Parameter: tree - Binary Tree
 * Output:
 *      Parameter: tree - by reference
 * Calls to:    FindNode, CreateNode, InsertNode, GetFileName
 **********************************************************************************/
void ReadIntFile(treeTop& tree)
{
    ifstream intFileIn;
    BTNode* newNode;
    bool foundInTree = false;
    bool insertSuccess = false;
    string fileName;
    int currentNum;
    BTNode* foundNode = NULL;
    
    fileName = GetFileName();
    
    intFileIn.open(fileName);
    
    cout << "Reading Input..." << endl;
    // priming read
    intFileIn >> currentNum;
    
    if (intFileIn)
    {
        
        // While there is data to be read in... Loop
        while (intFileIn || !intFileIn.eof())
        {
             foundInTree = FindNode(tree, currentNum, foundNode);
             
             if (foundInTree)
             {
                 cout << currentNum << " is already in the tree and will be ignored."
                      << endl;
             }
             else // Not found in tree
             {
                 // Allocate memory for new node.
                 newNode = CreateNode(currentNum);
                 
                 if (newNode == NULL)
                     cout << endl << "ERROR: Unable to allocated more memory." << endl;
                 else
                 {
                     // Insert number into tree
                     InsertNode(tree, newNode);
                 }
             }
            
            intFileIn >> currentNum; // grab next number and then evaluate.
           
        } // end While
    
    } // end if
    else
    {
        cout << endl << "No Data in Text File" << endl;
    }
    
    intFileIn.close(); // close the file
    
}

/**********************************************************************************
 * Function:        GetUserInput
 * Description: Function GetUserInput calls UserMenu to display the menu choices
 *              to the user and then prompts for user input. The input is then
 *              validated and the correct choice is returned.
 * Input:           
 * 	Parameters: N/A
 * Output:
 *      userChoice - char value for the users choice.
 * Calls to:    UserMenu
 **********************************************************************************/
char GetUserInput()
{
    char userChoice;
    
    do {
        UserMenu();
        cout << "Enter (A,B,C,D, or E): ";
        cin >> userChoice;
        userChoice = toupper(userChoice);
        
        
        if (((userChoice != 'A') && (userChoice != 'B') && (userChoice != 'C') 
            && (userChoice != 'D') && (userChoice != 'E')))
        {
            cout << endl << "ERROR: Incorrect Character Entered." << endl << endl;
        }
        
    } while ((userChoice != 'A') && (userChoice != 'B') && (userChoice != 'C') 
            && (userChoice != 'D') && (userChoice != 'E'));
    
    return userChoice;
}

/**********************************************************************************
 * Function:    MenuManager
 * Description: Function MenuManager takes a binary tree and char value as input
 *              parameters and runs the operation the user chose to run on the 
 *              binary tree.    
 * Input:           
 * 	Parameters:
 *          tree - Binary Tree
 *          userChoice - char value for the users Menu Choice
 * Output:
 *      Parameter:
 *          tree - by reference
 * Calls to:    IsEmpty, InOrderDisplay, GetInteger, FindNode, CreateNode, InsertNode,
 *              DeleteNode, DisplaySubTree, DestroyTree
 **********************************************************************************/
void MenuManager (treeTop& tree, char userChoice)
{
    int count = 0; // Counter for InOrderDisplay Function.
    int newNum; 
    bool foundInTree;
    BTNode* newNode;
    BTNode* foundNode = NULL;
    bool isTreeEmpty;
    
    switch(userChoice)
        {
            // Display Tree
            case 'A':
                
                isTreeEmpty = IsEmpty(tree);
                
                if (isTreeEmpty)
                {
                    cout << endl << "Binary Search Tree Empty" << endl;
                }
                else
                {
                    InOrderDisplay(tree.root, count);
                    
                    // resets count for next time InOrderDisplay is called.
                    //count = 0; 
                }
                
                break;
                
            // Insert into tree.
            case 'B':
                
                newNum = GetInteger();

                foundInTree = FindNode(tree,newNum, foundNode);

                if (foundInTree)
                {
                    cout << newNum << " is already in the tree and cannot be added."
                         << endl;
                }
                else // Not found in tree
                {
                    // Allocate memory for new node.
                    newNode = CreateNode(newNum);

                    if (newNode == NULL)
                        cout << endl << "ERROR: Unable to allocated more memory." << endl;
                    else
                    {
                        // Insert number into tree
                        InsertNode(tree, newNode);
                    }
                }
                break;
            
            // Delete from tree.    
            case 'C':
                
                newNum = GetInteger();

                DeleteNode(tree, newNum);
                    
                break;
            
            case 'D': // Display Sub Tree
                
                newNum = GetInteger();
                foundInTree = FindNode(tree, newNum , foundNode);
                
                 if (!foundInTree)
                {
                    cout << newNum << " is NOT in the tree."
                         << endl;
                }
                else // Found in tree
                {
                     DisplaySubTree(foundNode);
                }                  
                
                break;
            default: 
                cout << endl << "Exiting program..." << endl;
                DestroyTree(tree);
                
        }// End Switch
}

/**********************************************************************************
 * Function:        DisplaySubTree
 * Description:     Function DisplaySubTree takes a pointer variable to a node and 
 *                  displays the subtree of that node.
 * Input:           
 * 	Parameters  item - Pointer to the current item.
 * Output:
 *      Parameter:  item - by reference
 * Calls to:        N/A
 **********************************************************************************/
void DisplaySubTree(BTNode* &item)
{
    BTNode* leftTree;
    BTNode* rightTree;
    int leftValue, rightValue;
        
    leftTree = item->left;
    rightTree = item->right;
    
    if (leftTree != NULL)
        leftValue = leftTree->value;
    
    if (rightTree != NULL)
        rightValue = rightTree->value;
    
    cout << "Values stored in subtree with root " << item->value << " are:" << endl;
    
    if (leftTree == NULL && rightTree != NULL)
        cout << setw(5) << "Empty" << setw(5) << item->value << setw(5) << rightValue << endl;
    else if (leftTree != NULL && rightTree == NULL)
        cout << setw(5) << leftValue << setw(5) << item->value << setw(5) << " Empty" << endl;
    else if (leftTree != NULL && rightTree == NULL)
        cout << "Empty " << item->value << " Empty" << endl;
    else
        cout << setw(5) << leftValue << setw(5) << item->value << setw(5) << rightValue << endl;
    
}

/**********************************************************************************
 * Function:        GetInteger
 * Description:     Function prompts the user to enter a number between a minimum and
 *                  maximum value. The function than validates the number is within
 *                  the correct range, and returns the validated number. 
 * Input:           N/A
 * Output:
 *      Returns: newNum - Validated integer which falls in between min and max.
 * Calls to:        N/A
 **********************************************************************************/
int GetInteger ()
{
    int newNum; // number from the user to be validated.
    
    //do...while loops is user entry validation (1- 9999)
    do
    {
        cout << "Enter a number between " << MIN_NUM << " and "
             << MAX_NUM << "." << endl;
        cin >> newNum;

        if ((newNum < MIN_NUM || newNum > MAX_NUM))
            cout << endl << "ERROR: Number not allowed, try again"
                 << " (1 - 9999)." << endl;

    } while (newNum < MIN_NUM || newNum > MAX_NUM); // do...while
    
    return newNum;
}