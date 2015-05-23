#include <bits/stdc++.h>

using namespace std;

typedef struct node {
	int key;
	node *left;
	node *right;
} node;

node *create_node (int a) {
	node *temp = new node;
	temp->key = a;
	temp->right = NULL;
	temp->left = NULL;
	return temp;
}

void inorder(node *root) {
	if (root != NULL) {
		inorder (root->left);
		printf ("%d ",root->key);
		inorder(root->right);
	}
}

node *insert(node *root, int a) {
	if (root == NULL) {
		return create_node(a);
	}

	else {
		if (a < root->key) {
			root->left = insert(root->left, a);
		}
		else if (a > root->key) {
			root->right = insert(root->right, a);
		}
	}

	return root;
}

node *min(node *root) {
	node *cur = root;
	while (cur->left != NULL) {
		cur = cur->left;
	}
	return cur;
}

node *delete_node(node *root, int a) {
	if (root == NULL) {
		return root;
	}
	
        if (a < root->key) {
		root->left = delete_node(root->left, a);
	}
	else if (a > root->key) {
		root->right = delete_node(root->right, a);
	}
	else {
		if (root->left == NULL) {
			node *temp = root->left;
			free(root);
			return (temp);
		}

		else if (root->right == NULL) {
			node *temp = root->left;
			free(root);
			return (temp);
		}
		
			node *temp = min(root->right);
			root->key = temp->key;
			root->right = delete_node(root->right, temp->key);
	}
	return root;
}

int main() {
	int i, n;
	node *root = NULL;
	node *temp;
	scanf ("%d", &n);
	int a;
	for (i = 0; i < n; i++) {
		scanf ("%d", &a);
		root = insert(root, a);
	}
	temp = root;
	inorder(temp);
	scanf ("%d", &a);
	root = delete_node(root, a);
	inorder(root);
	cout << endl;
	return 0;
}
