#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;


//Problem: https://www.spoj.com/problems/PPATH/

// This and other comment sections with an initial "UPDATE!" sign have been written post-delivery

/*	UPDATE!

	This solution relies on Erastosthenes Sieve to generate an array of prime numbers (as suggested in "Competitive Programmer's Handbook"
	
	After making the sieve, a graph with (only) prime numbers as vertices can be built. This graph is built once and never changed,
		since the testcases only require a BFS to find the shortest path between two vertices (if there is one)

*/


/*	UPDATE!

	The struct 'Node' represents a vertex of the graph, whose vertices are all prime numbers with four digits,
		hence n1, n2, n3 and n4, which represent each digit, in descending order of decimal power
	
	All Nodes are kept in an array named 'primes', which is later for a BFS that finds the shortest path between two prime numbers
*/

struct Node {
    int num,
        n1,
        n2,
        n3,
        n4;
    vector<int> adjlist;
};


bool sieve[10000];
Node* primes[10000];


/*	UPDATE!

	'hasPath' is an auxiliary function which returns true if the two prime numbers passed differ in one and only one digit
	
	This function is later used while making the actual graph, as there can only be an edge between two Nodes a and b
		if a call to hasPath(a, b) returns true
*/

bool hasPath(Node *a, Node *b) {
    if (a->n1 == b->n1 && a->n2 == b->n2 && a->n3 == b->n3 && a->n4 != b->n4)
        return true;
    else if (a->n1 == b->n1 && a->n2 == b->n2 && a->n3 != b->n3 && a->n4 == b->n4)
        return true;
    else if (a->n1 == b->n1 && a->n2 != b->n2 && a->n3 == b->n3 && a->n4 == b->n4)
        return true;
    else if (a->n1 != b->n1 && a->n2 == b->n2 && a->n3 == b->n3 && a->n4 == b->n4)
        return true;

    return false;
}



void makeSieve() {
    for(int i=2; i<9999; i++) {
        if (sieve[i])
            continue;
        for(int j=i*2; j<9999; j+=i)
            sieve[j] = true;
    }
}


/*	UPDATE!

	The 'makeGraph' function uses the information stored in 'sieve' (i.e. Erastosthenes' Sieve array representation) to build a Node
		whenever a number is prime.
	
	The edges are made using another cycle which iterates over all existing, "smaller" (numerically speaking) Nodes of prime numbers,
		in case 'hasPath' returns true
*/

void makeGraph() {
    for(int i=1001; i<9999; i++) {
        if (!sieve[i]) {
            Node *node = new Node();

            node->num = i;
            node->n1 = ceil(i/1000);
            node->n2 = ceil(i%1000/100);
            node->n3 = ceil(i%100/10);
            node->n4 = ceil(i%10);

            primes[i] = node;

            for(int j=1001; j<i; j++) {
                if (primes[j] != nullptr && hasPath(node, primes[j])) {
                    node->adjlist.push_back(j);
                    primes[j]->adjlist.push_back(i);
                }
            }
        }
    }
}



int main() {
    int testcases, orig, dest;

    vector<int> distance;
    vector<bool> visited;


    makeSieve();
    makeGraph();

    scanf("%d", &testcases);

    while(testcases>0) {
        scanf("%d%d", &orig, &dest);

        if (orig==dest) {
            printf("0\n");
            testcases--;
            continue;
        }

        visited.clear();
        distance.clear();

        queue<int> q;

        visited.resize(10000);
        distance.resize(10000);

        int cost = -1;

        visited[orig] = true;
        q.push(orig);
        distance[orig] = 0;

        while(!q.empty()){
            int s = q.front();
            q.pop();

            for(auto x: primes[s]->adjlist) {
                if (!visited[x]) {
                    visited[x] = true;
                    q.push(x);
                    distance[x] = distance[s]+1;
                    if (x==dest) {
                        cost = distance[x];
                        break;
                    }
                }
            }
            if(cost>-1)
                break;
        }

        if(cost<0)
            printf("Impossible\n");
        else
            printf("%d\n", cost);

        testcases--;
    }

    return 0;
}
