#include <bits/stdc++.h>

using namespace std;

struct ll
{
	int x;
	int y;
	struct ll *next;
	struct ll *prev;
};

typedef struct ll node;

node *insert(node *head,int x,int y)
{
	node *tmp = NULL;
	tmp = (node *)malloc(sizeof(node));
	tmp->x = x;
	tmp->y = y;

	if(head!=NULL) {

		tmp->prev = head->prev;
		tmp->next = head;
		head->prev->next = tmp;
		head->prev = tmp;

	} else {
		head = tmp;
		head->next = head;
		head->prev = head;
	}
	return head;
}

void display(node *head)
{
	node *p = NULL;
	p = head;
	while(p->next!=head) {
		cout<<p->x<<" "<<p->y<<endl;
		p = p->next;
	}
	cout<<p->x<<" "<<p->y<<endl;
	p = p->next;
	cout<<p->x<<" "<<p->y<<endl;

}

node *convexhull(pair<int,int> coor[],int l,int h)
{
	if(h-l+1 == 2) {
//		cout<<"l : "<<l<<" h: "<<h<<endl;
		node *head = NULL;
		head = insert(head,coor[l].first,coor[l].second);
		head = insert(head,coor[h].first,coor[h].second);

		return head;
	} else if(h-l+1 == 3) {
//		cout<<"l : "<<l<<" h: "<<h<<endl;
		node *head = NULL;
		head = insert(head,coor[l].first,coor[l].second);
		double s1,s2;

		if(coor[l+1].first - coor[l].first != 0) {
			s1 = ((double)(coor[l+1].second - coor[l].second))/((double)(coor[l+1].first - coor[l].first));
		} else s1 = INT_MAX;

		if(coor[h].first - coor[l].first != 0) {
			s2 = ((double)(coor[h].second - coor[l].second))/((double)(coor[h].first - coor[l].first));
		} else s2 = INT_MAX;

		if(s1 >= s2) {
			head = insert(head,coor[l+1].first,coor[l+1].second);
			head = insert(head,coor[h].first,coor[h].second);
		} else if(s2 > s1) {
			head = insert(head,coor[h].first,coor[h].second);
			head = insert(head,coor[l+1].first,coor[l+1].second);
		}

		return head;
	} else {
		node *lh = NULL;
		node *rh = NULL;
		node *p1 = NULL;
		node *p2 = NULL;
		node *p3 = NULL;
		node *p4 = NULL;
		node *rm = NULL;
		node *lm = NULL;
		node *utl = NULL;
		node *utr = NULL;
		node *ltl = NULL;
		node *ltr = NULL;

		int x,y,mid = (l+h)/2;

//		cout<<"mid: "<<mid<<endl;

		double slope,cur_slope;

		lh = convexhull(coor,l,mid);
		rh = convexhull(coor,mid+1,h);

//		cout<<"left hull: "<<endl;
//		display(lh);

//		cout<<"right hull: "<<endl;
//		display(rh);

		// rightmost in left hull

		p1 = lh;
		x = p1->x;
		p1 = p1->next;
		p2 = lh;

		while(p1!=lh) {
			if(p1->x > x) {
				x = p1->x;
				p2 = p1;
			}
			p1 = p1->next;
		}

		rm = p2;

//		cout<<"rightmost : "<<p2->x<<" "<<p2->y<<endl;

		// leftmost in right hull

		p3 = rh;
		x = p3->x;
		p3 = p3->next;
		p4 = rh;

		while(p3!=rh) {
			if(p3->x < x) {
				x = p3->x;
				p4 = p3;
			}
			p3 = p3->next;
		}

		lm = p4;

//		cout<<"leftmost : "<<p4->x<<" "<<p4->y<<endl;


		// upper tangent

//		cout<<"finding upper tangent "	<<endl;

		if(p4->x - p2->x != 0) {
			cur_slope = ((double)(p4->y - p2->y))/((double)(p4->x-p2->x));
		} else cur_slope = INT_MAX;

//		cout<<"cur slope: "<<cur_slope<<endl;

		p1 = p2;
		p3 = p4;

		int swap = 1;

		while(swap) {
			swap = 0;

			while(1) {
//				cout<<" moving p3 clockwise "<<endl;
				p3 = p4->next;

				if(p3->x - p2->x != 0) {
					slope = ((double)(p3->y - p2->y))/((double)(p3->x-p2->x));
				} else slope = INT_MAX;

//				cout<<" slope "<<slope<<endl;

				if(slope>cur_slope) {
					swap = 1;
					cur_slope = slope;
					p4  = p3;
				} else break;
			}

			while(1) {
//				cout<<" moving p1 anticlockwise "<<endl;

				p1 = p2->prev;

				if(p4->x - p1->x != 0) {
					slope = ((double)(p4->y - p1->y))/((double)(p4->x-p1->x));
				} else slope = INT_MAX;

//				cout<<" slope "<<slope<<endl;

				if(slope<cur_slope) {
					swap = 1;
					cur_slope = slope;
					p2  = p1;
				} else break;
			}
		}

		utl = p2;
		utr = p4;

		cout<<"utl : "<<utl->x<<" "<<utl->y<<"\n"<<" utr: "<<utr->x<<" "<<utr->y<<endl;

		// lower tangent

//	cout<<"finding lower tangent "<<endl;

		p4 = lm;
		p2 = rm;

		if(p4->x - p2->x != 0) {
			cur_slope = ((double)(p4->y - p2->y))/((double)(p4->x-p2->x));
		} else cur_slope = INT_MAX;

//		cout<<"cur slope: "<<cur_slope<<endl;

		p1 = p2;
		p3 = p4;

		swap = 1;

		while(swap) {
			swap = 0;

			while(1) {
//				cout<<" moving p3 anticlockwise "<<endl;
				p3 = p4->prev;

				if(p3->x - p2->x != 0) {
					slope = ((double)(p3->y - p2->y))/((double)(p3->x-p2->x));
				} else slope = INT_MAX;

//				cout<<"slope: "<<slope<<endl;
				if(slope<cur_slope) {
					swap = 1;
					cur_slope = slope;
					p4  = p3;
				} else break;
			}

			while(1) {
//				cout<<" moving p1 clockwise "<<endl;
				p1 = p2->next;

				if(p4->x - p1->x != 0) {
					slope = ((double)(p4->y - p1->y))/((double)(p4->x-p1->x));
				} else slope = INT_MAX;
//				cout<<"slope: "<<slope<<endl;

				if(slope>cur_slope) {
					swap = 1;
					cur_slope = slope;
					p2  = p1;
				} else break;
			}
		}

		ltl = p2;
		ltr = p4;

		cout<<"ltl : "<<ltl->x<<" "<<ltl->y<<"\n"<<" ltr: "<<ltr->x<<" "<<ltr->y<<endl;

		utl -> next = utr;
		utr -> prev = utl;

		if(utl==ltl && utr==ltr) {
			p1 = utr;
			while(p1->next!=utr) {
				p1 = p1->next;
			}
			p2 = utl;
			while(p2->prev!=utl) {
				p2 = p2->prev;
			}
			p1->next = p2;
			p2->prev = p1;
		} else {
			ltl -> prev = ltr;
			ltr->next = ltl;
		}

		return lh;
	}
}

int main()
{
	node *head = NULL;
	node *p = NULL;
	int i,n,x,y;

//	cout<<"enter n:";
	cin>>n;

	pair<int,int> coor[n];
//	cout<<"enter points:"<<endl;
	for(i=1;i<=n;i++) {
		cin>>x>>y;
		coor[i-1] = make_pair(x,y);
	}
	sort(coor,coor+n);

	head = convexhull(coor,0,n-1);

//	cout<<"hull: "<<endl;
	display(head);

	return 0;
}
