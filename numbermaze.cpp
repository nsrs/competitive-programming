


#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;


// This and other comment sections with an initial "UPDATE!" sign have been written post-delivery


/*	UPDATE!

	Despite needing only to apply a simple Dijkstra algorithm to find the shortest path out of the number maze,
		the challenge (for me) here was to find out how to use STL's priority queue to work like a minheap,
		which was required to apply the algorithm in linearithmic time, so below is the source I used to
		effectively learn how to use priority queue with a pair and change how it "sorted" the elements
		to work like a minheap
	
	//https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
	
	
	As for the rest of program, the creation of the graph is identical to the "Rank the Languages" problem,
		and one application of Dijkstra's algorithm immediately provides the answer

*/

using node = pair<int, int>;

int MAXDIST = 1000000;

vector<int> weights, dist;
vector<vector<int>> adjlist;
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > pqueue;

bool comp(pair<int,int> left, pair<int,int> right) {
    if (left.first==right.first) return left.second > right.second;
    else return left.first < right.first;
}

int main() {
    int mazes, lines, columns, cost, cellcounter, cellabove, cellbehind, n, mincell;

    scanf("%d", &mazes);

    while (mazes>0) {
        scanf("%d%d", &lines, &columns);

        n = lines*columns;  //the number of nodes is the number of cells in the matrix
        cellcounter = 0;

        dist.resize(n);
        adjlist.resize(n);
        weights.resize(n);

        for(int i=0; i<lines; i++) {
            for(int j=0; j<columns; j++) {
                scanf("%d", &cost);
                weights[cellcounter] = cost;
                dist[cellcounter] = MAXDIST;

                if (i!=0) {
                    cellabove = cellcounter-columns;
                    adjlist[cellcounter].push_back(cellabove);
                    adjlist[cellabove].push_back(cellcounter);
                }

                if (j!=0) {
                    cellbehind = cellcounter-1;
                    adjlist[cellcounter].push_back(cellbehind);
                    adjlist[cellbehind].push_back(cellcounter);
                }

                cellcounter++;
            }
        }

        pqueue.push(make_pair(weights[0], 0));
        dist[0] = weights[0];

        while(!pqueue.empty()) {
            mincell = pqueue.top().second;
            /*
            if (mincell == n-1) {
                break;
            }
            */
            //printf("pop: %d\n", dist[mincell]);
            pqueue.pop();

            for(int i=0; i<adjlist[mincell].size(); i++) {
                int x = adjlist[mincell][i];
                if (dist[x] > dist[mincell] + weights[x]) {
                    dist[x] = dist[mincell] + weights[x];
                    pqueue.push(make_pair(dist[x], x));
                }
            }
        }


        printf("%d\n", dist[n-1]);

        dist.clear();
        weights.clear();
        adjlist.clear();
        mazes--;
    }

    return 0;
}
