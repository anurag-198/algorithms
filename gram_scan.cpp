#include <iostream>
#include <stack>
#include <stdlib.h>
#include <cstdio>
#include <vector>
using namespace std;

struct node {
    struct node* next;
    struct node* prev;
    int data;
    int data2;
};

struct node *n1, *n2, *n3, *n4;

struct hull {
    vector<int> x_cord;
    vector<int> y_cord;
};

vector <int> xh;
vector <int> yh;

struct point
{
    int x;
    int y;
};

point p0;
point nextToTop(stack<point> &S);
int swap(point &p1, point &p2);
int dist(point p1, point p2);

class circular_list
{
	public:
    struct node* root;
    struct node* main_root;
    struct node* last_root;
    struct node* pointer;
    
    circular_list() 
    {
        pointer = NULL;
        root = NULL;
    }
	
	void print1() 
	{
        node* temp = main_root;
        while(temp != last_root) {
            cout << "(" << temp->data << ", " << temp->data2 << ")" << "->";
            temp = temp->next;
        }
        cout << "(" << temp->data << ", " << temp->data2 <<")";
        cout<<endl;
    }
	
	void insert(vector <int> x , vector <int> y)
	{
        int val, val2, i;
        val = x[0], val2 = y[0];
        root = (struct node *)malloc(sizeof(struct node));
        main_root = root;
        root->next = NULL;
        root->prev = NULL;
        root->data = val;
        root->data2 = val2;
        
        for (i = 1; i < x.size(); i++ ) {
            val = x[i];
            val2 = y[i];
            struct node *temp1 = (struct node *)malloc(sizeof(struct node));
            temp1->next=NULL;
            temp1->prev = root;
            temp1->data = val;
            temp1->data2 = val2;
            root->next = temp1;
            root = root->next;
        }
        
        root->next = main_root;
        last_root = root;
        main_root->prev = last_root;
        root=root->next;
    }
	
	int size() 
	{
        int cnt = 0;
        struct node* temp = main_root;
        while (temp != last_root) {
            cnt++;
            temp = temp->next;
        }
        
        cnt++;
        
        return cnt;
    }

    struct node* y_max() 
    {
        struct node* temp = main_root;
        struct node* temp2 = main_root;
        
        while (temp != last_root) {
            if(temp->data2 > temp2->data2) temp2 = temp;
            temp = temp->next;
        }
        
        if (temp->data2 > temp2->data2) temp2 = temp;
        
		return temp2;
    }

    struct node* y_min () 
	{
        struct node* temp = last_root;
        struct node* temp2 = last_root;
        
		while (temp != main_root) {
            if(temp->data2 < temp2->data2) temp2 = temp;
            temp = temp->prev;
        }
        
        if (temp->data2 < temp2->data2) temp2 = temp;
        
		return temp2;
    }	
};

int orientation(point p, point q, point r);
int compare(const void *vp1, const void *vp2);
void convexHull(point points[], int n);

class convex_hull
{
	int n, f;
    public:
	
	void sort_xcord(vector <int> &v1, vector <int> &v2) 
	{
		int i, j;
		
        for (i = 0; i < v1.size(); i++) {
            for (j = 0; j < i; j++) {
                if (v1[i] < v1[j]) {
                    int temp = v1[i];
                    v1[i] = v1[j] ;
                    v1[j] = temp;
                    int temp2 = v2[i];
                    v2[i] = v2[j];
                    v2[j] = temp2;
                }
            }
        }
    }
    
    void print(vector <int> v1, vector <int> v2) 
	{
    	int i;
    	
        for (i = 0; i < v1.size(); i++ ) {
            printf("(%d %d)\n", v1[i], v2[i]);
        }
    }

    void run() 
	{
        struct hull result;
        result = con_hull(xh, yh, 0, xh.size() - 1, xh.size());
		//print(result.x_cord, result.y_cord);
	}
	
	struct hull con_hull(vector <int> x, vector <int> y, int start, int end, int num) 
	{
    	if (start <= end ) {
            if (num == 1 || num == 2 || num == 3 || x[start] == x[end]) {
                hull hh1;
                if(x[start] == x[end]) {
                    hh1.x_cord.push_back(x[start]);
                    hh1.y_cord.push_back(y[start]);
                    hh1.x_cord.push_back(x[end]);
                    hh1.y_cord.push_back(y[end]);
                } else {
                    for(int i = start; i <= end; i++) {
                        hh1.x_cord.push_back (x[i]);
                        hh1.y_cord.push_back (y[i]);
                    }
                }
                
                return hh1;
            }
            
            int i, mid = (start + end) / 2; 
            i = 0;
            
            while(1) {
                if (mid + i <= end) {
                	if (x[mid] == x[mid + i + 1]) i++;
                	else break;
                }

            } 

            mid = (start + end)/2 + i;
            struct hull left_hull = con_hull(x, y, start, mid, mid - start + 1);
            struct hull right_hull = con_hull(x, y, mid + 1, end, end - mid);
            struct hull merge_hull = merge(left_hull, right_hull);
            return merge_hull;
        }
    }
    
    struct hull merge(hull left, hull right) 
    {
        circular_list l, r;
        int counter_l, counter_r;
        struct hull final1;
        bool b1;
        l.insert(left.x_cord, left.y_cord);
        r.insert(right.x_cord, right.y_cord);
		int flag = 0;
        point temp1, temp2;
        l.pointer = l.y_max();
        r.pointer = r.y_max();
            
        if (l.y_max()->data2 > r.y_max()->data2) {
            counter_l = 0;
            while (counter_l != l.size()) {
					counter_l++;
                    counter_r = 0;
                    r.pointer = r.y_max();
                    while (counter_r != r.size()) {
                        	counter_r++;
                            temp1.x = l.pointer->data;
                            temp1.y = l.pointer->data2;
                            temp2.x = r.pointer->data;
                            temp2.y = r.pointer->data2;
                            b1 = test(temp1 , temp2 , left , right);
                                    
							if(b1 == true) {
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
            counter_r = 0;
            while (counter_r != r.size()) {
            	counter_r++;
                counter_l=0;
                l.pointer = l.y_max();
                        
                while (counter_l != l.size()) {
                    counter_l++;
                    temp1.x = l.pointer->data;
                    temp1.y = l.pointer->data2;
                    temp2.x = r.pointer->data;
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
        
    	l.pointer = l.y_min() ;
    	r.pointer = r.y_min() ;
    	flag = 0;
    
        if (l.y_min()->data2 < r.y_min()->data2) {
        	counter_l = 0;
        	
        	while (counter_l != l.size()) {
            counter_l++;
            counter_r=0;
            r.pointer = r.y_max();
            
            while (counter_r != r.size()) {
                counter_r++;
                temp1.x = l.pointer->data;
                temp1.y = l.pointer->data2;
                temp2.x = r.pointer->data;
                temp2.y = r.pointer->data2;
                bool b1 = test(temp1, temp2, left, right);
                if(b1 == true) {
                        n3 = l.pointer;
                        n4 = r.pointer;
                        flag = 1;
                        break;
                } else r.pointer = r.pointer->next;
            }
            	if(flag == 1) break;
            	l.pointer = l.pointer->prev;
        	}
        } else {
            counter_r = 0;
            
            while (counter_r != r.size()) {
              counter_r++;
              counter_l=0;
              l.pointer = l.y_max();
              
              while (counter_l != l.size()) {
                	counter_l++;
                    point temp1, temp2;
                    temp1.x = r.pointer->data;
                    temp1.y = r.pointer->data2;
                    temp2.x = l.pointer->data;
                    temp2.y = l.pointer->data2;
                    bool b1 = test(temp1, temp2, left, right);
                    
					if(b1 == true) {
                        n3 = l.pointer;
                        n4 = r.pointer;
                        flag = 1;
                        break;
                    } else l.pointer = l.pointer->prev;
                }
                
                if(flag == 1) break;
                r.pointer = r.pointer->next;
            }
        }
    	node* tempr1 = n2;
    
    	while (tempr1 != n4) {
        	final1.x_cord.push_back(tempr1->data);
        	final1.y_cord.push_back(tempr1->data2);
			tempr1 = tempr1->next;
    	}
    
    	final1.x_cord.push_back(tempr1->data);
    	final1.y_cord.push_back(tempr1->data2);
    	node*  tempr2 = n3;
    
    	while(tempr2 != n1) {
        	final1.x_cord.push_back(tempr2->data);
        	final1.y_cord.push_back(tempr2->data2);
    		tempr2 = tempr2->next;
    	}
        
    	final1.x_cord.push_back(tempr2->data);
    	final1.y_cord.push_back(tempr2->data2);
    
    	return final1;
    }
    
    int equation(int x1, int x2, int y1, int y2, int x, int y)
    {
        return ((y-y1) * (x1-x2)) - ((y1-y2)*(x-x1));
    }

    bool test(point l, point r, hull lef, hull rig)
    {
		int i;
        bool f;
        int tempo1 = lef.x_cord[0];
        int tempo2 = lef.y_cord[0];
        
        for (i = 0; i < lef.x_cord.size(); i++) {
            if(tempo1 == l.x && tempo2 == l.y) {
                    tempo1 = lef.x_cord[i];
                    tempo2 = lef.y_cord[i];
            } else break;
        }
        
        if (equation(l.x, r.x, l.y, r.y, tempo1, tempo2) < 0) f = false;
        else f = true;
           
        for (i = 0; i < lef.x_cord.size(); i++) 
        {
            if (equation(l.x, r.x, l.y, r.y, lef.x_cord[i], lef.y_cord[i]) > 0 && f == false) return false;
            else if (equation(l.x, r.x, l.y, r.y, lef.x_cord[i], lef.y_cord[i]) < 0 && f == true) return false;
        }
        
        for(i = 0; i < rig.x_cord.size(); i++ ) 
        {
               if (equation(l.x, r.x, l.y, r.y, rig.x_cord[i], rig.y_cord[i]) > 0 && f == false) return false;
               else if (equation(l.x, r.x, l.y, r.y, rig.x_cord[i], rig.y_cord[i]) < 0 && f == true) return false;
        }
        
        return true;
    }		
};

int main()
{
	int n, i;
	scanf("%d", &n);
	point p[n];
	
    for (i = 0; i < n; i++ ) {
        int tmpx, tmpy;
        scanf("%d%d", &tmpx, &tmpy);
        xh.push_back(tmpx);
        yh.push_back(tmpy);
        p[i].x = tmpx;
        p[i].y = tmpy;
    }
    
    convex_hull h1;
    h1.sort_xcord(xh, yh);
    h1.run();
    convexHull(p, n);
    
    printf("Upper Tangent Points : (%d %d) (%d %d)\n", n1->data, n1->data2, n2->data, n2->data2);
    printf("Lower Tangent Points : (%d %d) (%d %d)\n", n3->data, n3->data2, n4->data, n4->data2);
    
    return 0;
}

point nextToTop(stack<point> &S)
{
    point p = S.top();
    S.pop();
    point res = S.top();
    S.push(p);
    return res;
}
 
int swap(point &p1, point &p2)
{
    point temp = p1;
    p1 = p2;
    p2 = temp;
}
 
int dist(point p1, point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

int orientation(point p, point q, point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0;
    return (val > 0)? 1: 2;
}

int compare(const void *vp1, const void *vp2)
{
   point *p1 = (point *)vp1;
   point *p2 = (point *)vp2;
   int o = orientation(p0, *p1, *p2);
   if (o == 0)
     return (dist(p0, *p2) >= dist(p0, *p1))? -1 : 1;
 
   return (o == 2)? -1: 1;
}

void convexHull(point points[], int n)
{
   int ymin = points[0].y, min = 0;
   for (int i = 1; i < n; i++)
   {
     int y = points[i].y;
     if ((y < ymin) || (ymin == y && points[i].x < points[min].x))
        ymin = points[i].y, min = i;
   }
   
   swap(points[0], points[min]);
   p0 = points[0];
   qsort(&points[1], n-1, sizeof(point), compare);
 
   stack<point> S;
   S.push(points[0]);
   S.push(points[1]);
   S.push(points[2]);
 
   for (int i = 3; i < n; i++)
   {
      while (orientation(nextToTop(S), S.top(), points[i]) != 2)
         S.pop();
      S.push(points[i]);
   }
 
   while (!S.empty())
   {
       point p = S.top();
       cout << "(" << p.x << ", " << p.y <<")" << endl;
       S.pop();
   }
}
