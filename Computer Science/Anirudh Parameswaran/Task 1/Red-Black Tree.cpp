/*Red Black Tree*/
#include <iostream>
using namespace std;

//struct which defines any leaf in the tree

struct node {
	int key;
	char color;
	node *left;
	node *right;
	node *parent;
};

//class tree which takes care of operations like searching, insertions and deletion of tree

class tree {
	
	//Private recursive functions
	
	void destroy (node *leaf);
	node *search(int key, node *leaf);
	void display(node *leaf);
	node *minimum(node *leaf);
	void insert_fixup(node *leaf);
	void left_rotate(node *leaf);
	void right_rotate(node *leaf);
	void insert(node *leaf);
	
	node *root;
		
	public :
		tree();
		~tree();
		
		//Easy to use, simplified functions. Public access.
		   
		node *search(int key);
		void insert(int key);
		void display();
		void minimum();
};

void tree :: destroy(node *leaf) {
	if (leaf != NIL) {
		destroy(leaf->left);
		destroy(leaf->right);
		delete leaf;
	}
}

tree :: ~tree() {
	destroy(root);
}

void tree :: insert(int key) {
	node *temp;
	temp->key = key;
	insert(temp);
}

void tree :: insert(node *leaf) {
	node *y = NIL;
	node *x = root;
	
	while (x != NIL) {
		y = x;
		if (leaf->key < x->key) 
		x = x->left;
		else 
		x = x->right;
	}
	
	leaf->parent = y;
	if (y == NIL)
		root = leaf;
	else if (leaf->key < y->key) 
		y->left = leaf;
	else 
		y->right = leaf;
	
	leaf->left = NIL;
	leaf->right = NIL;
	leaf->color = 'r';
	insert_fixup(leaf);
}

void tree :: left_rotate(node *leaf) {
	if (leaf->right != NIL) {
		node *y = leaf->right;
		leaf->right = y->left;
		
		if (y->left != NIL) 
		y->left->parent = leaf;
		
		y->parent = leaf->parent;
		
		if (leaf->parent == NIL) 
		root = y;
		else if (leaf == leaf->parent->left) 
		leaf->parent->left = y;
		else
		leaf->parent->right = y;
		
		y->left = leaf;
		leaf->parent = y;
	}
	else 
	cout << "Right child is NULL. Rotation npt possible.\n";
}

void tree :: right_rotate(node *leaf) {
	if (leaf->left != NIL) {
		node *x = leaf->left;
		leaf->left = x->right;
		
		if (x->right != NIL) 
		x->right->parent = leaf;
		
		x->parent = leaf->parent;
		
		if (leaf->parent == NIL) 
		root = x;
		else if (leaf == leaf->parent->right) 
		leaf->parent->right = x;
		else
		leaf->parent->left = x;
		
		x->right = leaf;
		leaf->parent = x;
	}
	else 
	cout << "Left child is NULL. Rotation npt possible.\n";
}

void tree :: insert_fixup(node *leaf) {
	node *y = NIL;
	
	while (leaf->parent->color == 'r') {
		if (leaf->parent == leaf->parent->parent->left) {
			y = leaf->parent->parent->right;
			if (y->color == 'r') {
				leaf->parent->color = 'b';
				y->color = 'b';
				leaf->parent->parent->color = 'r';
				leaf = leaf->parent->parent;
			}
			else if (leaf == leaf->parent->right) {
				leaf = leaf->parent;
				left_rotate(leaf);
			}
			leaf->parent->color = 'b';
			leaf->parent->parent->color = 'r';
			right_rotate(leaf->parent->parent);
		}
		else {
			y = leaf->parent->parent->left;
			if (y->color == 'r') {
				leaf->parent->color = 'b';
				y->color = 'b';
				leaf->parent->parent->color = 'r';
				leaf = leaf->parent->parent;
			}
			else if (leaf == leaf->parent->left) {
				leaf = leaf->parent;
				left_rotate(leaf);
			}
			leaf->parent->color = 'b';
			leaf->parent->parent->color = 'r';
			left_rotate(leaf->parent->parent);
		}
	}
	root->color = 'b';
}

//Constructor to initialise root to NULL
tree :: tree() {
	node *NIL;
	NIL->left = NIL->right = NIL->parent = NULL;
	NIL->color = 'b';
	root = NIL;
}

/*Recursive function that determines the position of a 
certain node given its key and the root node*/

node *tree :: search(int key, node *leaf) {
	if (leaf != NIL) {
		if (key == leaf->key) {
			cout << leaf->key << '\t' << endl;
			return leaf;
		}
		
		if (key < leaf->key) 
		return search(key, leaf->left);
		else 
		return search(key, leaf->right);
	}
	else {
		cout << "NULL" << endl;
		return NIL;
	}
}

node* tree :: minimum(node *leaf) {
	node *temp = leaf;
	if (temp != NIL) {
		while (temp->left != NIL)
			temp = temp->left;
		cout << temp->key << '\t' << endl;
		return temp;
	}
	else {
		cout << "NULL\n";
		return NIL;
	}
}

void tree :: display(node *leaf) {
	if (leaf != NIL) {
		display(leaf->left);
		cout << leaf->key << '\t' << leaf->color << endl;
		display(leaf->right);
	}
}

node *tree :: search (int key) {
	return search(key, root);
}

void tree :: display() {
	display(root);
}

void tree :: minimum() {
	minimum(root);
}

int main() {
	tree rbtree;
	rbtree.insert(1);
	rbtree.insert(2);
	rbtree.insert(3);
	rbtree.insert(4);
	
	rbtree.display();
			
	return 0;
}
