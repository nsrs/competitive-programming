#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

//Problem: https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=2261

//The number of courses per student
static const int C = 5;

/*  n       -> Number of students
    crsset  -> Set of courses
    crsmap  -> Map of each crsset (keeps a string key that represents the set of courses and the frequency of said set)
    key     -> String representation of crsset (to be used as a key for 'crsmap')
    cmax    -> Maximum value read in crsmap (if there is no "most popular set of courses" case, it should be '0')
    temp    -> A string to save each course ID before it goes into 'crsset'
    reps    -> This number represents the frequency of the most popular sets of courses
*/



int main() {
    int n, cmax, reps;
    std::vector<int> sols;

    std::cin >> n;
    while(n>0) {
        cmax = 0;
        reps = 0;
        std::map<std::string, int> crsmap;

        for(int i=0; i<n; i++) {
            std::set<std::string> crsset;
            std::string key, temp;

            for(int j=0; j<C; j++) {
                std::cin >> temp;
                crsset.insert(temp);
            }

            for(std::set<std::string>::iterator it=crsset.begin(); it!=crsset.end(); it++)
                key += *it;

            std::map<std::string, int>::iterator it = crsmap.find(key);
            if (it == crsmap.end())
                crsmap.insert(it, std::pair<std::string, int>(key, 1));
            else {
                it->second += 1;
                if (it->second == cmax)
                    reps++;
                else if (it->second > cmax){
                    cmax = it->second;
                    reps = 1;
                }
            }
        }

        if (reps == n)
            std::cout << n << std::endl;
        else
            std::cout << cmax*reps << std::endl;

        std::cin >> n;
    }

    return 0;
}

