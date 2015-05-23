#include <bits/stdc++.h>
#define traverse(containe, it)  for(typeof(containe.begin()) it = containe.begin(); it != containe.end(); it++)

using namespace std;

typedef pair<int , int > pp;
vector < vector < pp > > graph;

void prim_algo(int v, int s) {
	vector < bool > visited(v, false);
	vector < int > key(v, INT_MAX);
	vector < int > parent (v, -1);

	set <pp> priq;
	int i;
	for (i = 0; i < v; i++)
		priq.insert(make_pair(key[i], i));

	priq.erase(priq.find(make_pair(key[s], s)));

	key[s] = 0;
	priq.insert(make_pair(key[s], s));

	while (!priq.empty()) {
		pp top = *priq.begin();
		priq.erase(priq.begin());
		s = top.second;
		visited[s] = true;

		traverse(graph[s], it) {
			if (!visited[it->first] && (it->second < key[it->first])) {
				priq.erase(priq.find(make_pair(key[it->first], it->first)));
				parent[it->first] = s;
				key[it->first] = it->second;

				priq.insert(make_pair(it->second, it->first));

			}
		}


	}


	for ( i = 0; i < v; i++) {
		cout << parent[i] << " ----- " << i  << " = " << key[i] << endl;
	}
}

int main() {
	int v, e;
	scanf ("%d%d", &v, &e);
    v = v + 1;
	graph.resize(v);
	int x, y, w, i;
	for (i = 0; i < e; i++) {
		scanf("%d%d%d", &x, &y, &w);
		graph[x].push_back(make_pair(y, w));
		graph[y].push_back(make_pair(x, w));
	}

	prim_algo(v, 0);

	return 0;
}

