#include <bits/stdc++.h>
using namespace std;

struct node
{
	struct node *prev;
	struct node *next;
	int data1;
	int data2;
};
struct hull
{
	vector <int> xc;
	vector <int> yc;
};

struct point
{
	int x;
	int y;
};
class circular_list
{
	public:
	struct node *root, *main_root, *last_root;
	public: struct node *pointer;

	circular_list() {
		pointer = NULL;
		root = NULL;
	}

	void insert(vector <int> x, vector <int> y)
	{
		int val1, val2, i;
		val1 = x[0], val2 = y[0];
		root = (struct node *) malloc(sizeof(struct node));
		main_root = root;
		root->prev = NULL;
		root->next = NULL;
		root->data1 = val1;
		root->data2 = val2;

		for (i = 1; i < x.size(); i++) {
			val1 = x[i];
			val2 = y[i];
			struct node *temp = (struct node *) malloc(sizeof(struct node));
			temp->next = NULL;
			temp->prev = root;
			temp->data1 = val1;
			temp->data2 = val2;
			root->next = temp;
			root = root->next;
		}

		root->next = main_root;
		last_root = root;
		main_root->prev = last_root;
		root = root->next;
	}

	int size()
	{
		int cnt = 0;
		struct node *temp = main_root;

		while (temp != last_root) {
			cnt++;
			temp = temp->next;
		}
		cnt++;

		return cnt;
	}

	struct node * y_max()
	{
		struct node *temp1 = main_root;
		struct node *temp2 = main_root;

		while (temp1 != last_root) {
			if (temp1->data2 > temp2->data2) temp2 = temp1;
			temp1 = temp1->next;
		}

		if (temp1->data2 > temp2->data2) temp2 = temp1;

		return temp2;
	}

	struct node * y_min()
	{
		struct node *temp1 = last_root;
		struct node *temp2 = last_root;

		while (temp1 != main_root) {
			if (temp1->data2 < temp2->data2) temp2 = temp1;
			temp1 = temp1->prev;
		}

		if (temp1->data2 < temp2->data2) temp2 = temp1;

		return temp2;
	}


int n, f;
vector <int> xh;
vector <int> yh;



void sort_xcord(vector <int> &v1, vector <int> &v2)
{
	int i, j;

	for (i = 0; i < v1.size(); i++) {
		for (j = 0; j < i; j++) {
			if (v1[i] < v1[j]) {
				int temp1 = v1[i];
				v1[i] = v1[j];
				v1[j] = temp1;
				int temp2 = v2[i];
				v2[i] = v2[j];
				v2[j] = temp2;
			}
		}
	}
}

void input()
{
	int i, tempx, tempy;
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		scanf("%d%d", &tempx, &tempy);
		xh.push_back(tempx);
		yh.push_back(tempy);
	}

	sort_xcord(xh, yh);
}

int equation(int x1, int x2, int y1, int y2, int x, int y)
{
	return ((y - y1) * (x1 - x2)) - ((y1 - y2) * (x - x1));
}

bool test(point l, point r, hull lft, hull rgt)
{
	bool f;
	int tmpo1 = lft.xc[0];
	int tmpo2 = lft.yc[0];
	int i;

	for (i = 0; i < lft.xc.size(); i++) {
		if (tmpo1 == l.x && tmpo2 == l.y) {
			tmpo1 = lft.xc[i];
			tmpo2 = lft.yc[i];
		} else break;
	}

	if (equation(l.x, r.x, l.y, r.y, tmpo1, tmpo2) < 0) f = false;
	else f = true;

	for (i = 0; i < lft.xc.size(); i++) {
		if (equation(l.x, r.x, l.y, r.y, lft.xc[i], lft.yc[i]) > 0 && f == false) return false;
		else if (equation(l.x, r.x, l.y, r.y, lft.xc[i], lft.yc[i]) < 0 && f == true) return false;
	}

	for (i = 0; i < rgt.xc.size(); i++) {
		if (equation(l.x, r.x, l.y, r.y, rgt.xc[i], rgt.yc[i]) > 0 && f == false) return false;
		else if (equation(l.x, r.x, l.y, r.y, rgt.xc[i], rgt.yc[i]) < 0 && f == true) return false;
	}

	return true;
}

hull merge(hull left, hull right)
{

	circular_list l, r;
	int ctr_l, ctr_r;
	hull final;
	struct node *n1, *n2, *n3, *n4;
	bool b1;
	l.insert(left.xc, left.yc);
	r.insert(right.xc, right.yc);
	int flag = 0;

	point temp1, temp2;
	l.pointer = l.y_max();
	r.pointer = r.y_max();

	if (l.y_max()->data2 > r.y_max()->data2) {
		ctr_l = 0;
		while (ctr_l != l.size()) {
			ctr_l++;
			ctr_r = 0;
			r.pointer = r.y_max();
			while (ctr_r != r.size()) {
				ctr_r++;
				temp1.x = l.pointer->data1;
				temp1.y = l.pointer->data2;
				temp2.x = r.pointer->data1;
				temp2.y = r.pointer->data2;
				b1 = test(temp1, temp2, left, right);
				if (b1 == true) {
					n1 = l.pointer;
					n2 = r.pointer;
					flag = 1;
					break;
				} else r.pointer = r.pointer->prev;
			}

			if (flag == 1) break;
			l.pointer = l.pointer->next;
		}
	} else {
		ctr_r = 0;
		while (ctr_r != r.size()) {
			ctr_r++;
			ctr_l = 0;
			l.pointer = l.y_max();
			while (ctr_l != l.size()) {
				ctr_l++;
				temp1.x = l.pointer->data1;
				temp2.y = l.pointer->data2;
				temp1.x = r.pointer->data1;
				temp2.y = r.pointer->data2;
				b1 = test(temp1, temp2, left, right);
				if (b1 == true) {
					n1 = l.pointer;
					n2 = r.pointer;
					flag = 1;
					break;
				} else l.pointer = l.pointer->next;
			}

			if (flag == 1) break;
			r.pointer = r.pointer->prev;
		}
	}

	l.pointer = l.y_min();
	r.pointer = r.y_min();
	flag = 0;

	if (l.y_min()->data2 < r.y_min()->data2) {
		ctr_l = 0;
		while (ctr_l != l.size()) {
			ctr_l++;
			ctr_r = 0;
			r.pointer = r.y_max();
			while (ctr_r != r.size()) {
				ctr_r++;
				temp1.x = pointer->data1;
				temp1.y = pointer->data2;
				temp2.x = pointer->data1;
				temp2.y = pointer->data2;
				b1 = test(temp1, temp2, left, right);
				if (b1 == true) {
					n3 = l.pointer;
					n4 = r.pointer;
					flag = 1;
					break;
				} else r.pointer = r.pointer->next;
			}

			if (flag == 1) break;
			l.pointer = l.pointer->prev;
		}
	} else {
		ctr_r = 0;
		while (ctr_r != r.size()) {
			ctr_r++;
			ctr_l = 0;
			l.pointer = l.y_max();
			while (ctr_l != l.size()) {
				ctr_l++;
				temp1.x = pointer->data1;
				temp1.y = pointer->data2;
				temp2.x = pointer->data1;
				temp2.y = pointer->data2;
				b1 = test(temp1, temp2, left, right);
				if (b1 == true) {
					n3 = l.pointer;
					n4 = r.pointer;
					flag = 1;
					break;
				} else l.pointer = l.pointer->prev;
			}

			if (flag == 1) break;
			r.pointer = r.pointer->next;
		}
	}

	struct node *tmpr1 = n2;
	while (tmpr1 != n4) {
		final.xc.push_back(tmpr1->data1);
		final.yc.push_back(tmpr1->data2);
		tmpr1 = tmpr1->next;
	}

	final.xc.push_back(tmpr1->data1);
	final.yc.push_back(tmpr1->data2);
	struct node *tmpr2 = n3;

	while (tmpr2 != n1) {
		final.xc.push_back(tmpr2->data1);
		final.yc.push_back(tmpr2->data2);
		tmpr2 = tmpr2->next;
	}

	final.xc.push_back(tmpr2->data1);
	final.yc.push_back(tmpr2->data2);

	return final;
}

hull convex_hull(vector <int> x, vector <int> y, int start, int end, int num)
{
	int i;

	if (start < end) {

		if (num == 1 || num == 2 || num == 3 || x[start] == x[end]) {
			hull hh1;
			if (x[start] == x[end]) {
				hh1.xc.push_back(x[start]);
				hh1.yc.push_back(y[start]);
				hh1.xc.push_back(x[end]);
				hh1.yc.push_back(y[end]);
			} else {
				for (i = start; i <= end; i++) {
					hh1.xc.push_back(x[i]);
					hh1.yc.push_back(y[i]);
				}
			}

			return hh1;
		}

		int mid = (start + end) / 2;
		hull left_hull = convex_hull(x, y, start, mid, mid - start + 1);
		hull right_hull = convex_hull(x, y, mid + 1, end, end - mid);
		hull full_hull = merge(left_hull, right_hull);

		return full_hull;
	}
}

void print(vector <int> v1, vector <int> v2)
{
	int i;

	for (i = 0; i < v1.size(); i++) printf("%d %d\n", v1[i], v2[i]);
	printf("\n");
}

void run()
{
	hull result;
	result = convex_hull(xh, yh, 0, xh.size() - 1, xh.size());

	print (result.xc, result.yc);
}

};
int main()
{
    circular_list c1;
	c1.input();
	c1.run();

	return 0;
}

