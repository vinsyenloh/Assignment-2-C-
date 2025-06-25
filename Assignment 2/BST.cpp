#include <iostream>
#include <fstream>
#include <algorithm>
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


void BST::preOrderPrint2(BTNode *cur) {

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


void BST::inOrderPrint2(BTNode *cur) {

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


void BST::postOrderPrint2(BTNode *cur) {
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


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}

void BST::topDownLevelTraversal() {
	BTNode			*cur;
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
	BTNode	*cur = new BTNode(newItem);
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


void BST::insert2(BTNode *cur, BTNode *newNode) {
	if (cur->item.compare1(newNode->item)){
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

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
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


void BST::case2(BTNode *pre, BTNode *cur) {

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


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

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

//(b)
bool BST::deepestNodes()
{
	if (root == NULL) {
		return false;
	}

	int deepestLevel = 0;
	findDeepestNode(root, 1, deepestLevel);  // Start from level 1
	cout << "\nThe deepest node: ";
	deepest(root, 1, deepestLevel);  // Start from level 1
	cout << endl;
	return true;
}

void BST::deepest(BTNode* cur, int level, int height)
{
	if (cur == NULL)
		return;
	if (level == height)  
		cout << cur->item.id << " ";

	deepest(cur->left, level + 1, height);
	deepest(cur->right, level + 1, height);
}

void BST::findDeepestNode(BTNode* node, int level, int& height)
{
	if (node == NULL)
		return;

	if (level > height) {
		height = level;
	}
	findDeepestNode(node->left, level + 1, height);
	findDeepestNode(node->right, level + 1, height);
}

//(c)
bool BST::display(int order, int source) {
	if (root == NULL) {
		cout << "\n\033[31mThe tree is empty. Nothing to display.\033[0m\n";
		return false;
	}

	// Validate 'order' and 'source' inputs
	if (order != 1 && order != 2) {
		cout << "\n\033[31mInvalid order option. Please choose 1 (ascending) or 2 (descending).\033[0m\n";
		return false;
	}
	if (source != 1 && source != 2) {
		cout << "\n\033[31mInvalid source option. Please choose 1 (screen) or 2 (file).\033[0m\n";
		return false;
	}

	if (source == 1) { // Print to screen
		if (order == 1) { // Ascending (in-order)
			inOrderPrint(root);
		}
		else { // Descending (reverse in-order)
			reverseInOrderTraversal(root);
		}
	}
	else { // Print to file
		ofstream file("student_info.txt");
		if (!file.is_open()) {
			cout << "\n\033[31mError: Could not open file for writing.\033[0m\n";
			return false;
		}

		if (order == 1) { // Ascending (in-order)
			inOrderPrintToFile(root, file);
		}
		else { // Descending (reverse in-order)
			reverseInOrderTraversalToFile(root, file);
		}
		file.close();
	}

	return true;
}

// Helper function for in-order traversal (ascending, prints to screen)
void BST::inOrderPrint(BTNode* cur) {
	if (cur == NULL) return;
	inOrderPrint(cur->left);
	cur->item.print(cout); // Assuming `print()` handles formatting
	inOrderPrint(cur->right);
}

// Helper function for in-order traversal (ascending, prints to file)
void BST::inOrderPrintToFile(BTNode* cur, ofstream& file) {
	if (cur == NULL) return;
	inOrderPrintToFile(cur->left, file);
	cur->item.print(file); // Assuming `print()` handles formatting
	inOrderPrintToFile(cur->right, file);
}

// Helper function for reverse in-order (descending, prints to screen)
void BST::reverseInOrderTraversal(BTNode* cur) {
	if (cur == NULL) return;
	reverseInOrderTraversal(cur->right);
	cur->item.print(cout);
	reverseInOrderTraversal(cur->left);
}

// Helper function for reverse in-order (descending, prints to file)
void BST::reverseInOrderTraversalToFile(BTNode* cur, ofstream& file) {
	if (cur == NULL) return;
	reverseInOrderTraversalToFile(cur->right, file);
	cur->item.print(file);
	reverseInOrderTraversalToFile(cur->left, file);
}

//(d)
bool BST::cloneSubtree(BST t1, type item) {
	// Check if source tree is empty
	if (t1.root == NULL) {
		cout << "\n\033[31mCannot clone subtree: Source tree is empty.\033[0m\n";
		return false;
	}

	//Clear the target tree T2 (this)
	clearTree(this->root);  
	this->root = NULL;      

	// Check if target tree is empty (should be empty before cloning)
	if (this->root != NULL) {
		cout << "\n\033[31mCannot clone subtree: Target tree must be empty.\033[0m\n";
		return false;
	}

	// Find the node with 'item' in source tree
	BTNode* sourceNode = findNode(t1.root, item);
	if (sourceNode == NULL) {
		cout << "\n\033[31mCannot clone subtree: Item not found in source tree.\033[0m\n";
		return false;
	}

	// Clone the subtree
	this->root = cloneNodeRecursive(sourceNode);

	// Print original and cloned trees
	cout << "\nOriginal Tree t1 (Pre-order):\n";
	t1.preOrderPrint();
	cout << "\n------------------------------------------------------------------\n";
	cout << "\nCloned Subtree t2 (Pre-order):\n";
	this->preOrderPrint();

	return true;
}

void BST::clearTree(BTNode* node) {
	if (node == NULL) return;  
	clearTree(node->left);     
	clearTree(node->right);    
	delete node;               
}

// Helper function to find a node with matching item
BTNode* BST::findNode(BTNode* node, type item) const {
	if (node == NULL) return NULL;
	if (node->item.compare2(item)) return node;
	BTNode* result = findNode(node->left, item);
	return result ? result : findNode(node->right, item);
}


// Helper function to recursively clone a subtree
BTNode* BST::cloneNodeRecursive(BTNode* sourceNode) {
	if (sourceNode == NULL) return NULL;

	BTNode* newNode = new BTNode(sourceNode->item);
	newNode->left = cloneNodeRecursive(sourceNode->left);
	newNode->right = cloneNodeRecursive(sourceNode->right);

	return newNode;
}

//(e)
bool BST::printLevelNodes() {
	if (empty()) {
		cout << "\033[31mTree is empty. No levels to print.\033[0m" << endl;
		return false;
	}

	Queue queue;
	queue.enqueue(root);
	int level = 1;

	while (!queue.empty()) {
		int nodesInCurrentLevel = queue.size();
		cout << "Level " << level << " nodes: ";

		for (int i = 0; i < nodesInCurrentLevel; ++i) {
			BTNode* currentNode;
			queue.dequeue(currentNode);

			cout << currentNode->item.id;

			// Add space after each ID except the last one
			if (i < nodesInCurrentLevel - 1) {
				cout << " ";
			}

			if (currentNode->left != nullptr) {
				queue.enqueue(currentNode->left);
			}
			if (currentNode->right != nullptr) {
				queue.enqueue(currentNode->right);
			}
		}

		cout << endl;
		++level;
	}

	return true;
}


//(f)
bool BST::printpath() {
	if (root == nullptr) {
		return false; // Empty tree
	}

	cout << "Below are all the external paths for the tree:\n\n";
	vector<int> path; // Dynamic path storage
	printPathHelper(root, path);
	return true;
}

void BST::printPathHelper(BTNode* cur, vector<int>& path) {
	if (cur == nullptr) {
		return;
	}

	path.push_back(cur->item.id); // Add current node to path

	// If leaf node, print the path
	if (cur->left == nullptr && cur->right == nullptr) {
		for (size_t i = 0; i < path.size(); i++) {
			cout << path[i];
			if (i < path.size() - 1) {
				cout << " "; // Space between IDs, no trailing space
			}
		}
		cout << endl;
	}
	else {
		// Recurse left and right subtrees
		printPathHelper(cur->left, path);
		printPathHelper(cur->right, path);
	}

	path.pop_back(); // Backtrack (remove current node)
}

bool BST::duplicate(BTNode* cur, const Student& item) {
	if (cur == NULL) return false;
	if (cur->item.id == item.id) return true;
	if (item.id < cur->item.id)
		return duplicate(cur->left, item);
	else
		return duplicate(cur->right, item);
}