
#include<iostream>
using namespace std;


struct StdNode{
	int data;
	int height;
	StdNode* lChild;
	StdNode* rChild;
	StdNode() 
                    {
		data = 0;
		lChild = NULL;
		rChild = NULL;
		height = 0;
	}
	int Gheight(StdNode* n) {      // height getter function
		return n->height;
	}
};

class AVL {

private:
	StdNode* root;
public:

	AVL() {
		root = NULL;
	}

	void insert(StdNode*& t, int d) {
		if (t == nullptr)
			t->data = d;
		else if (d < t->data)
			insert(t->lChild, d);
		else if (t->data < d)
			insert(t->rChild, d);
		balance(t);
	}

	void insert(int x) {   //wrapper
		insert(root, x);
	}

	void balance(StdNode*& t)
	{
		if (t == nullptr)
			return;
		if (t->Gheight(t->lChild) - t->Gheight(t->rChild) > -2 && t->Gheight(t->lChild) - t->Gheight(t->rChild) < 2)
		{
			if (t->Gheight(t->lChild->lChild) >= t->Gheight(t->lChild->rChild))
				rightrotate(t);
			else
				doubleLeftRightRotation(t);
		}
		else if (t->Gheight(t->rChild) - t->Gheight(t->lChild) > -2 && t->Gheight(t->rChild) - t->Gheight(t->lChild) < 2)
		{
			if (t->Gheight(t->rChild->rChild) >= t->Gheight(t->rChild->lChild))
				leftrotate(t);
			else
				doubleRightLeftRotation(t);
			t->height = maximum(t->Gheight(t->lChild), t->Gheight(t->rChild)) + 1;
		}
	}

	void leftrotate(StdNode* n)
	{
		StdNode* x = n->rChild;
		StdNode* t = x->lChild;
		x->lChild = n;
		n->rChild = t;
		n->height = maximum(n->Gheight(n->rChild), n->Gheight(n->lChild)) + 1;
		x->height = maximum(x->Gheight(x->rChild), x->Gheight(x->lChild)) + 1;
	}

	void rightrotate(StdNode* n)
	{
		StdNode* y = n->lChild;
		StdNode* t = y->rChild;
		y->rChild = n;
		n->lChild = t;
		n->height = maximum(n->Gheight(n->rChild), n->Gheight(n->lChild)) + 1;
		y->height = maximum(y->Gheight(y->rChild), y->Gheight(y->lChild)) + 1;
	}

	void doubleLeftRightRotation(StdNode*& n) {
		leftrotate(n->lChild);
		rightrotate(n);
	}

	void doubleRightLeftRotation(StdNode*& n) {
		rightrotate(n->rChild);
		leftrotate(n);
	}

	int maximum(int a, int b){
		if (a > b)
			return a;
		return b;
	}

	bool search(StdNode *node, int d)
	{
		if (node) {
			if (node->data > d)
				search(node->lChild, d);
			else if (node->data < d)
				search(node->rChild, d);
			else
				return true;
		}
		else
			return false;
	}
	bool search(int d)    // wrapper funtion.
	{
		return search(root, d);
	}

	void deletedata(const int& d, StdNode*& n) {
		if (n == nullptr)
			return;
		if (d < n->data)
			deletedata(d, n->lChild);
		else if (n->data < d)
			deletedata(d, n->rChild);
		else if (n->lChild != nullptr && n->rChild != nullptr) {
			n->data = Min(n->rChild)->data;
			deletedata(n->data, n->rChild);
		}
		else {
			StdNode* oldNode = n;
			if (n->lChild != nullptr)
				n = n->lChild;
			else
				n = n->rChild;
			delete oldNode;
		}
		balance(n);
	}
	void deletedata(const int& x) // wrapper funtion
	{
		deletedata(x, root);
	}

	StdNode* Min(StdNode* n) {
		if (n->rChild->data < n->lChild->data)
			return n->rChild;
		return
			n->lChild;
	}

	void Printintreeform(StdNode* n){
		if (root != NULL){
			Printintreeform(n->lChild);
			cout << n->data << " ";
			Printintreeform(n->rChild);
		}
	}
	void Printintreeform()  // wrapper funtion
	{
		Printintreeform(root);
	}

	int NoofNodes(StdNode* n, int count) {
		if (n != NULL){
			NoofNodes(n->lChild, count);
			++count;
			NoofNodes(n->rChild, count);
		}
		return count;
	}
	int NoofNodes() //wrapper funtion
	{
		int count = 0;
		return NoofNodes(root, count);
	}


	void flipClockwise() {
		rightrotate(root);
	}

	void AVLdelete(StdNode* root) {
		if (root != NULL) {
			AVLdelete(root->lChild);
			AVLdelete(root->rChild);
			delete root;
		}
	}
	~AVL() {
		AVLdelete(root);
	}
};

int main()
{
	AVL stdTree;

	stdTree.insert(14);
	stdTree.insert(17);
	stdTree.insert(11);
	stdTree.insert(7);
	stdTree.insert(53);
	stdTree.insert(4);
	stdTree.insert(13);
	stdTree.Printintreeform();
	stdTree.insert(12);
	stdTree.Printintreeform();
	stdTree.insert(8);
	stdTree.Printintreeform();
	stdTree.deletedata(53);
	cout << endl << endl << "Tree after Deletion: " << endl;
	stdTree.Printintreeform();
	stdTree.deletedata(11);
	cout << endl << endl << "Tree after Deletion: " << endl;
	stdTree.Printintreeform();
	stdTree.deletedata(8);
	cout << endl << endl << "Tree after Deletion: " << endl;
	stdTree.Printintreeform();
	cout << stdTree.NoofNodes(); //returns 6
	cout << stdTree.search(17); //returns true;
	stdTree.flipClockwise();
	cout << endl << endl << "Tree after flipping: " << endl;
	stdTree.Printintreeform();
	/*
	sample output of flipping
	4
	\
	7
	/ \
	14 12
	/ \
	13 17

	*/
}

