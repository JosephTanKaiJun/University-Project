#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode* cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode* cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode* cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode* cur, int& count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode* cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)) {

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode* cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode* cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode* cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode* cur, BTNode* newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)) {
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode* pre, BTNode* cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)) {
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode* pre, BTNode* cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode* cur) {
	BTNode* is, * isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}

// ======================================= Start of - bool BST::deepestNodes =======================================

// This method retrieves the deepest nodes from the Binary Search Tree (BST).
bool BST::deepestNodes()
{
	// Check if the BST is empty.
	if (empty())
	{
		cout << "\nBinary Tree is empty... \n\n";
		return false;
	}

	// Calculate the height of the BST.
	int dob = heightOfTree(root);
	cout << "Deepest Nodes is : ";

	// Print the deepest nodes of the BST.
	coutDeepestNodes(root, 1, dob);
	return true;
}

// This method calculates the height of the given binary tree node.
int BST::heightOfTree(BTNode* root)
{
	// If the node is NULL, then it's height is 0.
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		// Calculate the height of the left subtree.
		int leftTotalHeight = heightOfTree(root->left);

		// Calculate the height of the right subtree.
		int rightTotalHeight = heightOfTree(root->right);

		// Return the greater height between the left and right subtrees, incremented by 1 to account for the current node.
		if (leftTotalHeight > rightTotalHeight)
		{
			return(leftTotalHeight + 1);
		}
		else
		{
			return(rightTotalHeight + 1);
		}
	}
}

// This method prints the deepest nodes from the binary tree.
void BST::coutDeepestNodes(BTNode* node, int lvl, int heightOfTree)
{
	// If the node is NULL, then return immediately.
	if (node == NULL)
	{
		return;
	}

	// If the current level matches the height of the tree, print the node's ID.
	if (lvl == heightOfTree)
	{
		cout << node->item.id;
		cout << "\n\n";
	}

	// Recursively traverse the left subtree.
	coutDeepestNodes(node->left, lvl + 1, heightOfTree);

	// Recursively traverse the right subtree.
	coutDeepestNodes(node->right, lvl + 1, heightOfTree);
}
// ======================================= End of - bool BST::deepestNodes =======================================

// ======================================= Start of - bool BST::display ======================================= 


bool BST::display(int order, int source) {

	if (empty()) { //checking if the bst is empty
		cout << "\nError: The BST is empty. Nothing to display.\n" << endl;
		return false;
	}

	ofstream outFile;
	ostream* output;

	if (source == 2) {
		outFile.open("student-info.txt");
		if (!outFile.is_open()) {
			cout << "\nError: Unable to open the output file.\n" << endl;
			return false;
		}
		output = &outFile;
	}
	else {
		output = &cout;
	}

	if (order == 1) {   //to print in ascending order
		displayAscending(root, *output);
	}
	else if (order == 2) {   //to print in descending order
		displayDescending(root, *output);
	}

	if (source == 2) {
		outFile.close();
		if (!outFile.good()) {
			cout << "Error: Error occurred while closing the output file." << endl;
			return false;
		}
	}

	return true;
}

//======================================== Start of void displayAscending ===================================

void BST::displayAscending(BTNode* currentNode, ostream& output) {
	if (currentNode == nullptr) { //check if the current node is a leaf or an empty subtree
		return;
	}

	// print left subtree recursively 
	displayAscending(currentNode->left, output);

	//printing student information
	currentNode->item.print(output);

	/*
	output << "Student Id    : " << currentNode->item.id << endl;
	output << "Name          : " << currentNode->item.name << endl;
	output << "Address       : " << currentNode->item.address << endl;
	output << "Date of Birth : " << currentNode->item.DOB << endl;
	output << "Phone Number  : " << currentNode->item.phone_no << endl;
	output << "Course        : " << currentNode->item.course << endl;
	output << "CGPA          : " << currentNode->item.cgpa << endl;
	*/

	// Recursively print right subtree
	displayAscending(currentNode->right, output);
}

//======================================== End of void displayAscending ===================================


//======================================== Start of void displayDescending ================================

void BST::displayDescending(BTNode* currentNode, ostream& output) {
	if (currentNode == nullptr) { //check if the current node is a leaf or an empty subtree
		return;
	}

	// recursively print right subtree
	displayDescending(currentNode->right, output);

	//printing student information
	currentNode->item.print(output);

	/* printing student information
	output << "Student Id    : " << currentNode->item.id << endl;
	output << "Name          : " << currentNode->item.name << endl;
	output << "Address       : " << currentNode->item.address << endl;
	output << "Date of Birth : " << currentNode->item.DOB << endl;
	output << "Phone Number  : " << currentNode->item.phone_no << endl;
	output << "Course        : " << currentNode->item.course << endl;
	output << "CGPA          : " << currentNode->item.cgpa << endl;
	*/

	// recursively print left subtree
	displayDescending(currentNode->left, output);
}

//======================================== End of void displayDescending ==================================
// ======================================= End of - bool BST::display ======================================= 









// ======================================= Start of - bool BST::CloneSubtree ======================================= 

BTNode* BST::findNode(BTNode* currentNode, type item) {
	if (currentNode == nullptr || currentNode->item.compare3(22)) { // <- change the student Id here
		return currentNode;
	}

	if (currentNode->item.compare1(item)) {
		return findNode(currentNode->left, item);
	}
	else {
		return findNode(currentNode->right, item);
	}
}

void BST::cloneSubtree2(BTNode* sourceNode, BST* targetTree) {
	if (sourceNode == nullptr) {
		return;
	}

	targetTree->insert(sourceNode->item); // Insert the node into the target tree

	// Recursively clone left and right subtrees
	cloneSubtree2(sourceNode->left, targetTree);
	cloneSubtree2(sourceNode->right, targetTree);
}

bool BST::CloneSubtree(BST* t1, type item) {

	if (empty()) { // if BST is empty, return false
		return false;
	}

	BTNode* subTree = findNode(root, item); // create new pointer node to find for a node in BST

	t1->remove(item);

	cloneSubtree2(subTree, t1);

	cout << "** Successfully cloned subtree to t2!! **" << endl;

	cout << "\n** t1 after cloning:" << endl;
	preOrderPrint(); // Print the source tree after cloning

	cout << "\n** t2 after cloning:" << endl;
	t1->preOrderPrint(); // Print the cloned subtree

	return true;
}

// ======================================= End of - bool BST::CloneSubtree =======================================


// ======================================= Start of - bool BST::printLevelNodes =======================================

bool BST::printLevelNodes() {

	if (empty()) { // if BST is empty, return false
		return false;
	}

	Queue q;
	q.enqueue(root); // Enqueue the root node to start traversal
	int a = 1;
	// Continue traversal as long as the queue is not empty
	while (!q.empty()) {
		int nodesInCurrentLevel = q.size();
		cout << "Level " << a++ << " nodes: "; // Print the level number and the number of nodes

		// Traverse the nodes in the current level
		while (nodesInCurrentLevel > 0) {
			BTNode* cur;
			q.dequeue(cur); // Dequeue the current node

			cout << cur->item.id << "  "; // Print the student ID

			// Enqueue the left and right children of the current node, if they exist
			if (cur->left != nullptr) {
				q.enqueue(cur->left);
			}
			if (cur->right != nullptr) {
				q.enqueue(cur->right);
			}

			nodesInCurrentLevel--; // Decrement the count of nodes in the current level
		}

		cout << endl; // Move to the next line after printing all nodes in the current level
	}

	return true;
}

// ======================================= End of - bool BST::printLevelNodes ==========================================================================================

//================================== = Function 6 ============================================ =


void BST::printExternalPaths(BTNode* cur, string path) {
	if (cur == nullptr) {
		return;
	}

	path += to_string(cur->item.id);

	if (cur->left == nullptr && cur->right == nullptr) {
		cout << path << endl; // Print the external path
	}
	else {
		path += " ";
		printExternalPaths(cur->left, path);
		printExternalPaths(cur->right, path);
	}
}


bool BST::printPath()
{

	if (empty())
	{
		cout << "\nBinary Tree is empty... \n\n";
		return false;
	}
	else
		cout << "\n Below are all the external paths for the tree:\n\n";

	printExternalPaths(root, " ");
	return true;
}

//================================ End of Function 6 ========================================


