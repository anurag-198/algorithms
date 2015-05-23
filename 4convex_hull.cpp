#include <bits/stdc++.h>

using namespace std;

struct point
{
    double x, y;
    point *prev, *next;
};

struct point *create(struct point *head, double x1, double x2)
{
    struct point *new_point = NULL;
    new_point = new(struct point);
    new_point->x = x1;
    new_point->y = x2;

    if (head == NULL)
    {
        new_point->next = new_point;
        new_point->prev = new_point;;
        return new_point;
    }

    struct point *temp = head;

    while (temp->next != head)
        temp = temp->next;
    temp->next = new_point;
    head->prev = new_point;
    new_point->next = head;
    new_point->prev = temp;

    return head;
};

void printlist(struct point *head)
{
    cout<<"Points in Convex Hull :"<<endl;
    point *p = head;

    cout << p -> x << " " << p -> y << endl;
    p = p -> next;

    while (p != head)
    {
        cout << p -> x << " " << p -> y << endl;
        p = p -> next;
    }
}

bool test(struct point *pl, struct point *pr)
{
    double yy, xx, c;

    yy = pr->y - pl->y;
    xx = pr->x - pl->x;
    c = (pr->x * pl->y) - (pl->x * pr->y);

    double p1, p2, p3, p4;

    p1 = (pl->next->x * yy) - (pl->next->y * xx) + c;
    p2 = (pl->prev->x * yy) - (pl->prev->y * xx) + c;
    p3 = (pr->next->x * yy) - (pr->next->y * xx) + c;
    p4 = (pr->prev->x * yy) - (pr->prev->y * xx) + c;

    if ((p1 > 0 && p2 >= 0 && p3 > 0 && p4 >= 0) || (p1 < 0 && p2 <= 0 && p3 < 0 && p4 <= 0)) {
        return true;
    }
    else return false;
}

struct point *merge(struct point *left_hull, struct point *right_hull, int nl, int nr)
{
    int i, j;
    struct point *pl, *pr, *final_hull = NULL;
    bool flag = 0;

    pl = left_hull;
    pr = right_hull;

    for (i = 0; i < nl; i++, pl = pl -> next)
    {
        for (j = 0; j < nr; j++, pr = pr -> next)
        {
            if (test(pl, pr))
            {
                flag = 1;
                break;
            }
        }
        if (flag)
            break;
        pr = right_hull;
    }

    point *utpl, *utpr, *ltpl, *ltpr, *p;

    utpl = pl;
    utpr = pr;
    flag = 0;
    pl = left_hull;
    pr = right_hull;

    for (i = 0; i < nl; i++, pl = pl -> next)
    {
        for (j = 0; j < nr; j++, pr = pr -> next)
        {
            if (utpl != pl && utpr != pr && test(pl, pr))
            {
                flag = 1;
                break;
            }
        }
        if (flag)
            break;
        pr = right_hull;
    }

    ltpl = pl;
    ltpr = pr;

    struct point *temp = NULL;

    if (utpl->y < ltpl->y)
    {
        temp = utpl;
        utpl = ltpl;
        ltpl = temp;
        temp = utpr;
        utpr = ltpr;
        ltpr = temp;
    }
    else if (utpl->y == utpr->y)
    {
        if (utpr->y < ltpr->y)
        {
            temp = utpl;
            utpl = ltpl;
            ltpl = temp;
            temp = utpr;
            utpr = ltpr;
            ltpr = temp;
        }
    }

    p = utpr;

    while (p != ltpr)
    {
        final_hull = create(final_hull, p->x, p->y);
        p = p->next;
    }

    final_hull = create(final_hull, ltpr->x, ltpr->y);

    p = ltpl;
    while (p != utpl)
    {
        final_hull = create(final_hull, p->x, p->y);
        p = p->next;
    }

    final_hull = create(final_hull, utpl->x, utpl->y);

    return final_hull;
}

struct point *triangle(vector<pair<double,double> > v, int l, int u)
{
    struct point *head = NULL;
    double yy, xx, c;

    yy = v[l+1].second - v[l].second;
    xx = v[l+1].first - v[l].first;
    c = (v[l+1].first * v[l].second) - (v[l].first * v[l+1].second);

    double p = (v[l+2].first * yy) - (v[l+2].second * xx) + c;
    if (p == 0) {
        head = create(head, v[l].first, v[l].second);
        head = create(head, v[l+2].first, v[l+2].second);
    } else if(xx == 0) {
        if (p > 0) {
            head = create(head, v[l].first, v[l].second);
            head = create(head, v[l+1].first, v[l+1].second);
            head = create(head, v[l+2].first, v[l+2].second);
        } else {
            head = create(head, v[l].first, v[l].second);
            head = create(head, v[l+2].first, v[l+2].second);
            head = create(head, v[l+1].first, v[l+1].second);
        }
    } else {
        if (p < 0) {
            head = create(head, v[l].first, v[l].second);
            head = create(head, v[l+1].first, v[l+1].second);
            head = create(head, v[l+2].first, v[l+2].second);
        } else {
            head = create(head, v[l].first, v[l].second);
            head = create(head, v[l+2].first, v[l+2].second);
            head = create(head, v[l+1].first, v[l+1].second);
        }
    }
    return head;
}

struct point *c_hull(vector < pair<double, double> > v, int l, int u)
{
    struct point *p, *head = NULL, *left_hull, *right_hull, *final_hull;
    int nl = 1, nr = 1;

    if (u - l == 2)
    {
        head = create(head, v[l].first, v[l].second);
        head = create(head, v[l+1].first, v[l+1].second);

        return head;
    }

    if (u - l == 3)
        return triangle(v, l, u);

    left_hull = c_hull(v, l, (l+u) / 2);
    right_hull = c_hull(v, (l+u) / 2, u);

    p = left_hull->next;

    while (p != left_hull)
    {
        p = p->next;
        nl++;
    }

    p = right_hull->next;

    while (p != right_hull)
    {
        p = p->next;
        nr++;
    }

    final_hull = merge(left_hull, right_hull, nl, nr);

    return final_hull;
}

int main()
{
    int n, i;
    double a, b;
    cin>>n;

    vector < pair<double,double> > v;

    for (i = 0; i < n; i++)
    {
        cin>>a>>b;
        v.push_back(make_pair(a,b));
    }

    sort(v.begin(), v.end());

    struct point *final_hull = NULL;

    final_hull = c_hull(v, 0, n);
    printlist(final_hull);

    return 0;
}
