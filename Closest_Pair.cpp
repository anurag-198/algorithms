#include <bits/stdc++.h>

using namespace std;

struct point {
	double x, y;
};

point ans1, ans2;
double min_prev = 99999.0;

int compare_x(const void *a, const void *b)
{
	point *p1 = (point *)a;
	point *p2 = (point *)b;

	return (p1->x - p2->x);
}

int compare_y(const void *a, const void *b)
{
	point *p1 = (point *)a;
	point *p2 = (point *)b;

	return (p1->y - p2->y);
}

double distance_1(point p1, point p2)
{
	return sqrt(((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y)));
}

double divide_conquer(point sort_x[], point sort_y[], int n)
{	
	if (n <= 3) {
		double min = 99999999.0;
		int i, j;
		
		for (i = 0; i < n; i++) {
			for (j = i+1; j < n; j++) {
				if (distance_1(sort_x[i], sort_x[j]) < min) {
					 min = distance_1(sort_x[i], sort_x[j]);
					 if (min < min_prev) {
					 	ans1.x = sort_x[i].x;
					 	ans1.y = sort_x[i].y;
					 	ans2.x = sort_x[j].x;
					 	ans2.y = sort_x[j].y;
					 	min_prev = min;
					}
				}
			}
		}
		
		return min;
	} else {
		int mid = n/2, l_ind = 0, r_ind = 0, i, j;
		point mid_point = sort_x[mid];
		point p_l[mid+1], p_r[n-mid-1];

		for (i = 0; i < n; i++) {
			if (mid_point.x < sort_y[i].x) p_r[r_ind++] = sort_y[i];
			else p_l[l_ind++] = sort_y[i];
		}

		double left_dist = divide_conquer(sort_x, p_l, mid);
		double right_dist = divide_conquer(sort_x + mid, p_r, n - mid);
		double d = min(left_dist, right_dist);

		point strip[n];
		j = 0;

		for (i = 0; i < n; i++) {
			if (abs(mid_point.x - sort_y[i].x) < d) strip[j++] = sort_y[i];
		}

		double min_strip_dist = d;
		int size = j;

		for (i = 0; i < size; i++) {
			for (j = i+1; j < size; j++) {
				if (distance_1(strip[i], strip[j]) < min_strip_dist) {
					 min_strip_dist = distance_1(strip[i], strip[j]);
					 ans1.x = strip[i].x;
					 ans1.y = strip[i].y;
					 ans2.x = strip[j].x;
					 ans2.y = strip[j].y;
				}
			}
		}
		
		return min(d, min_strip_dist);
	}
}

double closest_pair(point p[], int n)
{
	int i;
	point sort_x[n], sort_y[n];

	for (i = 0; i < n; i++) {
		sort_x[i] = p[i];
		sort_y[i] = p[i];
	}

	qsort(sort_x, n, sizeof(point), compare_x);
	qsort(sort_y, n, sizeof(point), compare_y);

	return divide_conquer(sort_x, sort_y, n);
}

int main()
{
	int n, i;
	scanf("%d", &n);
	point p[n];

	for (i = 0; i < n; i++) scanf("%lf%lf", &p[i].x, &p[i].y);

	double min_dist = closest_pair(p, n);

	printf("%lf\n", min_dist);
	printf("%lf %lf\n%lf %lf\n", ans1.x, ans1.y, ans2.x, ans2.y);

	return 0;
}

