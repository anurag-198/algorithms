#include <bits/stdc++.h>

using namespace std;

typedef struct node {
	int key;
	node *parent;
	node *right;
	node *left;
}node;

int coun;

node *create_node(int k) {
	node *temp = new node;
	temp->key = k;
	temp->parent = NULL;
	temp->right = NULL;
	temp->left = NULL;
	return temp;
}

node *create_heap(node *root,int key) {
	coun++;
	int len = log2(coun);
	int i;
	node *temp = root;

	if (root == NULL) {
		return create_node(key);
	}
	else {
		for (i = len - 1; i > 0; i--) {
			if ((1 << i) & coun) {
				temp = temp->right;	
			}
			else {
				temp = temp->left;
			}
		}
		if (1 & coun) {
			temp->right = create_node(key);
			temp->right->parent = temp;
		}
		else {
			temp->left = create_node(key);
			temp->left->parent = temp;
		}
	}				
	return root;
}

void heapify(node *root) {

	if (root) {
	
	int pos1 = root->key;
	int pos2 = INT_MIN;
	int pos3 = INT_MIN;
	int temp,maxi;
	if (root->left)
	  pos2 = root->left->key;
	if (root->right)
		pos3 = root->right->key;
	
	maxi = max(max(pos1,pos2),pos3);
	
	if (maxi == pos1) {
		return;
	}
	
	if (root->left) {
		if (maxi == pos2) {
			temp = root->key;
			root->key = root->left->key;
			root->left->key = temp;
			heapify(root->left);
		}
 	}
 	
	if (root->right) {
		if (maxi == pos3) {
			temp = root->key;
			root->key = root->right->key;
			root->right->key = temp;
			heapify(root->right);
		}
	}
}
	
	return;
}

void maxheapify(node *root, int no) {
//		cout <<"no is " << no << endl;
		node *temp = root;
		int i;
		int len = log2(no);
		for (i = len - 1; i >= 0; i--) {
			if ((1 << i) & no) {
				temp = temp->right;
			}
			else {
				temp = temp->left;
			}
		}
		heapify(temp);
}

void buildmaxheap(node *root) {
	node *temp = root;
	int i,no = coun;
	
	for (i = coun / 2; i >= 1; i--) {
		maxheapify(root, i);
	}
}

void heapsort(node *root) {
	node *temp = root;
	node *temp1 = root;
	
	int j,i = coun;
	int pos;
	int len = log2(i);
	
	cout <<"elements in sorted decreasing order \n";
	while (coun > 0) {
		pos = -1;
		buildmaxheap(temp);
		cout << root->key << " ";
		for (j = len - 1; j >= 0; j--) {
			if ((1 << j) & i) {
				temp1 = temp1->right;
				pos = 1;
			}
			else {
				temp1= temp1->left;
				pos = 0;
			}
		}
		
		int t = root->key;

		root->key = temp1->key;
		temp1->key = t;
		temp = root;
		if ((pos == 0) && (temp1->parent != NULL)) {
			temp1->parent->left = NULL;
		}
		else if (temp1->parent != NULL) {
			temp1->parent->right = NULL;
		}
		
		coun--;
		i = coun;
		len = log2(coun);
		temp1 = root;
	}
	cout << endl;
}

void inorder (node *temp) {
	if (temp != NULL) {
		inorder(temp->left);
		printf ("%d ", temp->key);
		inorder(temp->right);
	}
}

int main() {
	
	int n, k;
	printf ("enter the no of elements\n");
	scanf ("%d", &n);

	node *root = NULL;
	cout << "enter the elements \n";

	while (n--) {
		scanf ("%d", &k);
		root = create_heap(root, k);
	}
	
	node *temp2 = root;
//	inorder(temp2);
	heapsort(root);
	
	node *temp1 = root;
	//inorder (temp1);

	return 0;
}
