#include <cstdio>
#include <vector>

using namespace std;


// This and other comment sections with an initial "UPDATE!" sign have been written post-delivery



/*	UPDATE!

	Finding the maximum matching on a bipartite graph with this kind of input required reading characters one by one (not mandatory, but it was the strategy here applied)
	
	It follows Hopcroft-Karp's algorithm to accomplish the goal, which requires a dfs over all vertices on one side of the bipartite graph,
		checking if a match is available, if it's replaceable, or if there is no match (this last case can interrupt any following dfs, since
		all workers (here referred as "app users") must have a computer to work for a combination to be considered possible
		
		
	app			-> vector that stores characters which correspond to the app's name
	appusers	-> appusers[i] stores the number of people using app[i]
	allocation	-> allocation to be used for the output of test cases
	apprunners	-> adjacency lists (e.g. apprunner[i] is a vector that saves all of the computers that can run app[i])
	visited		-> a boolean vector used during the DFS, so as to avoid making previously failed matches


*/

vector<char> app;
vector<int> appusers, allocation;
vector<vector<int>> apprunners;
vector<bool> visited;


bool dfs(int appid) {
    int pc;

    for(int i=0; i<apprunners[appid].size(); i++) {
        pc = apprunners[appid][i];

		//printf("%c wants pc %d\n", app[appid], pc);

        if (visited[pc])
            continue;

        visited[pc] = true;

        if (allocation[pc] < 0 || dfs(allocation[pc]) ) {
            allocation[pc] = appid;
            return true;
        }
    }

    return false;
}

void printResult() {
    allocation.assign(10, -1);

    for(int i=0; i<appusers.size(); i++) {

        while(appusers[i] > 0) {
            visited.clear();
            visited.resize(10);

			//printf("app %c\n", app[i]);

            if (!dfs(i)) {
                printf("!\n");
                return;
            }
            appusers[i]--;
        }
    }

    for(int i=0; i<allocation.size(); i++) {
        if (allocation[i] < 0)
            printf("_");
        else
            printf("%c", app[allocation[i]]);
    }
    printf("\n");
}



int main() {
    int scanoutput, temp;
    char c;

    scanoutput = scanf("%c", &c);   //read the first character of each line

    while(1) {
        if (scanoutput == EOF) {
            printResult();
            app.clear();
            appusers.clear();
            apprunners.clear();
            allocation.clear();
            break;
        }

        else if (c == '\n') {
            printResult();
            app.clear();
            appusers.clear();
            apprunners.clear();
            allocation.clear();
        }

        else {
            app.push_back(c);                           //App (A-Z)

            scanf("%c", &c);                            //Number of App users (0-9)


            appusers.push_back((int)(c - '0'));

            scanf(" %c", &c);                           //first computer available (0-9)

            apprunners.push_back(vector<int>());
            apprunners.back().push_back((int)(c - '0'));

            while(1) {
                scanf("%c", &c);

                if (c==';') {                           //if char is ';' then move on to the next line
                    scanf("%c", &c);
                    break;
                }
                apprunners.back().push_back((int)(c - '0'));
            }
        }

        scanoutput = scanf("%c", &c);                   //read the first character of each line
    }

    return 0;
}

