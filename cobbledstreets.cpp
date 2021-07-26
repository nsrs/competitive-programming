#include <cstdio>
#include <climits>
#include <queue>
#include <vector>

using namespace std;

/*
	Problem:
		https://www.spoj.com/problems/CSTREET/
		
	A simple graph build, followed by Prim's algorithm to find the minimum spanning tree.
	Time complexity is O(E*log(V))
*/



vector<vector<pair<int,long long int>>> adjlist;
vector<long long int> dist;
vector<bool> visited;

int main() {
    long long int cost, length;
    int testcases, price, n, edges, p1, p2;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > pqueue;
    pair<int,int> ipair;

    scanf("%d", &testcases);

    while(testcases>0) {
        scanf("%d%d%d", &price, &n, &edges);

        adjlist.resize(n+1);
        dist.resize(n+1);
        visited.resize(n+1);

        for(int i=0; i<edges; i++) {
            scanf("%d%d%lld", &p1, &p2, &length);
            adjlist[p1].push_back({p2, length});
            adjlist[p2].push_back({p1, length});
        }

        for(int i=1; i<=n; i++) {
            dist[i] = LLONG_MAX;
        }

        dist[1] = 0;
        pqueue.push({0,1});

        while(!pqueue.empty()) {
            p1 = pqueue.top().second;
            pqueue.pop();
            visited[p1] = true;

            for(int i=0; i<adjlist[p1].size(); i++) {
                p2 = adjlist[p1][i].first;
                length = adjlist[p1][i].second;

                if (!visited[p2] && dist[p2] > length) {
                    dist[p2] = length;
                    pqueue.push({dist[p2], p2});
                }
            }
        }

        cost = 0;

        for(int i=2; i<=n; i++) {
            cost += dist[i]*price;
        }

        printf("%lld\n", cost);

        visited.clear();
        adjlist.clear();
        dist.clear();
        testcases--;
    }

    return 0;
}
