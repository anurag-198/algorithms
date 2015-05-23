#include<iostream>
#include "cdll.h"
#include<vector>
#include<algorithm>
#include<functional>
#include<numeric>
#include <cmath>

using namespace std;

struct hull {
    vector<int> x_cord;
    vector<int> y_cord;
};

struct point {
    int x;
    int y;
};

class convex_hull {
    int n, f;
    vector<int> xh; //Entering x coordinates
    vector<int> yh;
    public:
    void getData() {
        cout << "Enter the number of points:" <<endl;
        cin >> n;
        cout << "Enter x and y coordinates of the points:" << endl;
        for(int i = 0;i < n; i++ ) {
            int tmp_x, tmp_y;
            cin >> tmp_x >> tmp_y;
            xh.push_back(tmp_x);
            yh.push_back(tmp_y);
        }
        sort_first(xh, yh); //Sorting according to x-coodt
    }

    void sort_first(vector<int> &v1, vector<int> &v2) {
        for(int i = 0; i < v1.size(); i++) {
            for(int j = 0; j < i; j++) {
                if(v1[i] < v1[j] ) {
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
    
    void print(vector<int> v) {
    //    cout<<endl<<"Printing"<<endl;
        for(int i = 0; i < v.size(); i++ ) {
            cout << v[i] << " ";
        }
        cout<<endl;
    }

    void run() {
        hull res;
        res = con_hull(xh, yh, 0, xh.size() - 1, xh.size());
        cout << "\nAnswer:" << endl;
        cout << "\nX Co-ordinates:" << endl;
        print(res.x_cord);
        cout << "\nY Co-ordinates:" << endl;
        print(res.y_cord);
        int area;
        int temp_down,temp_up;
        temp_down = 0;
        temp_up = 0;

        for (int i = 0;i < res.x_cord.size()-1; i++) {

                temp_down = temp_down + res.x_cord[i]*res.y_cord[i+1];
        }

        for (int i = res.y_cord.size()-1; i >= 0; i--) {

                temp_up = temp_up + res.x_cord[i]*res.y_cord[i-1];
        }

        cout << "The Area of the Convex Hull is : \n" << (double)(0.5)*fabs(temp_down-temp_up) << endl;
}

    hull con_hull(vector<int> x, vector<int> y, int start, int end, int num) {
    if (start < end )
        {
        //Base case for between 1 to 3 points
            if(num == 1 || num == 2 || num == 3 || x[start] == x[end]) {
                hull hh1;
                if(x[start] == x[end]) 
                {
                    hh1.x_cord.push_back(x[start]);
                    hh1.y_cord.push_back(y[start]);
                    hh1.x_cord.push_back(x[end]);
                    hh1.y_cord.push_back(y[end]);
                } 
                else 
                {
                    for(int i = start; i <= end; i++) 
                    {
                        hh1.x_cord.push_back (x[i]);
                        hh1.y_cord.push_back (y[i]);
                    }
                }
                return hh1;
            }
            int mid = (start + end)/2;
            hull h_left;
            hull h_right;
            h_left = con_hull(x, y, start, mid, mid - start + 1);
            h_right = con_hull(x, y, mid + 1, end, end - mid);
            hull m_hull = merge(h_left, h_right);
            return m_hull;
        }
    }
    hull merge(hull left, hull right) 
    {
        cdll l, r;
        int counter_l, counter_r;
        node *n1, *n2, *n3, *n4;
        hull final;
        bool b1;
        l.insert(left.x_cord, left.y_cord);
        r.insert(right.x_cord, right.y_cord);
        int flag = 0;
            point temp1, temp2;
            l.pointer = l.y_max();
            r.pointer = r.y_max();
            if(l.y_max()->data2 > r.y_max()->data2) 
            {
                    counter_l = 0;
                        while (counter_l != l.size()) 
                        {
                            counter_l++;
                            counter_r=0;
                            r.pointer = r.y_max();
                            while (counter_r != r.size()) {
                                    counter_r++;
                                    temp1.x = l.pointer->data;
                                    temp1.y = l.pointer->data2;
                                    temp2.x = r.pointer->data;
                                    temp2.y = r.pointer->data2;
                                    bool b1 = check(temp1 , temp2 , left , right );
                                    if(b1) 
                                    {
                                        n1 = l.pointer;
                                        n2 = r.pointer;
                                        flag = 1;
                                        break;
                                    } 
                                    else 
                                        r.pointer = r.pointer->prev;
                            }
                        if(flag == 1) 
                            break;
                        l.pointer = l.pointer->next;
                        }
                } 
                else 
                {
                    counter_r = 0;
                    while (counter_r != r.size()) {
                        counter_r++;
                        counter_l=0;
                        l.pointer = l.y_max();
                        while (counter_l != l.size()) 
                        {
                            counter_l++;
                            temp1.x = l.pointer->data;
                            temp1.y = l.pointer->data2;
                            temp2.x = r.pointer->data;
                            temp2.y = r.pointer->data2;
                            bool b1 = check(temp1, temp2, left, right);
                            if(b1) 
                            {
                                n1 = l.pointer;
                                n2 = r.pointer;
                                flag = 1;
                                break;
                            } 
                            else 
                                l.pointer = l.pointer->next;
                        }
                        if(flag == 1) 
                            break;
                        r.pointer = r.pointer->prev;
                    }
                }
        //Finding Lower Tangent
    l.pointer = l.y_min() ;
    r.pointer = r.y_min() ;
    flag = 0;
        if(l.y_min()->data2 < r.y_min()->data2) 
        {
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
                bool b1 = check(temp1, temp2, left, right);
                    if(b1) 
                    {
                        n3 = l.pointer;
                        n4 = r.pointer;
                        flag = 1;
                        break;
                    } 
                    else 
                        r.pointer = r.pointer->next;
            }
            if(flag == 1) 
                break;
            l.pointer = l.pointer->prev;
        }
        } 
        else 
        {
            counter_r = 0;
            while (counter_r != r.size()) 
            {
                counter_r++;
              counter_l=0;
              l.pointer = l.y_max();
              while (counter_l != l.size()) 
              {
                    counter_l++;
                    point temp1, temp2;
                    temp1.x = r.pointer->data;
                    temp1.y = r.pointer->data2;
                    temp2.x = l.pointer->data;
                    temp2.y = l.pointer->data2;
                    bool b1 = check(temp1, temp2, left, right);
                    if(b1) 
                    {
                        n3 = l.pointer;
                        n4 = r.pointer;
                        flag = 1;
                        break;
                    } 
                    else 
                        l.pointer = l.pointer->prev;
                }
                if(flag == 1) 
                    break;
                r.pointer = r.pointer->next;
            }
        }

//Combination
    node* tempr1 = n2;
    while (tempr1 != n4) 
    {
        final.x_cord.push_back(tempr1->data);
         final.y_cord.push_back(tempr1->data2);
        tempr1 = tempr1->next;
    }
    final.x_cord.push_back(tempr1->data);
    final.y_cord.push_back(tempr1->data2);
    node*  tempr2 = n3;
    while(tempr2 != n1) 
    {
              final.x_cord.push_back(tempr2->data);
            final.y_cord.push_back(tempr2->data2);
               tempr2 = tempr2->next;
    }
        
    final.x_cord.push_back(tempr2->data);
    final.y_cord.push_back(tempr2->data2);
    return final;
    }
    int equation(int x1, int x2, int y1, int y2, int x, int y)
    {
        return ((y-y1) * (x1-x2)) - ((y1-y2)*(x-x1));
    }

    bool check(point l, point r, hull lef, hull rig)
    {
        bool f;
        int tempo1 = lef.x_cord[0];
        int tempo2 = lef.y_cord[0];
        for (int i = 0; i < lef.x_cord.size(); i++) 
        {
            if(tempo1 == l.x && tempo2 == l.y) 
            {
                    tempo1 = lef.x_cord[i];
                    tempo2 = lef.y_cord[i];
               }
            else 
                    break;
        }
        if (equation(l.x, r.x, l.y, r.y, tempo1, tempo2) < 0)
            f = false;
        else 
            f = true;
           
        for (int i = 0; i < lef.x_cord.size(); i++) 
        {
            if (equation(l.x, r.x, l.y, r.y, lef.x_cord[i], lef.y_cord[i]) > 0 && f == false)
                return false;
            else if (equation(l.x, r.x, l.y, r.y, lef.x_cord[i], lef.y_cord[i]) < 0 && f == true)
                return false;
        }
        for(int i = 0; i < rig.x_cord.size(); i++ ) 
        {
               if (equation(l.x, r.x, l.y, r.y, rig.x_cord[i], rig.y_cord[i]) > 0 && f == false)
                return false;
             else if (equation(l.x, r.x, l.y, r.y, rig.x_cord[i], rig.y_cord[i]) < 0 && f == true)
                return false;
        }
        return true;
    }
};

int main()
{
    convex_hull h1;
    h1.getData();
    h1.run();
    
    return EXIT_SUCCESS;
}