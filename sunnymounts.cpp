#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using Par = pair<int,int>;

//Problem: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=861

/*
	The sun shines from the right side of the hills, which are triangles. The strategy below simply takes a right hillside at a time and
	calculates the hypotenuse with the pitagorean theorem, though it must update from where the hypotenuse should start each time the 
	maximum peak is increased, so the base of the triangle will be calculated according to the equation of the right hillside of the mountain.
*/

int main() {
    int testcases, n, coordX, coordY, maxheight;
    double  litside, x, m, b, cathor, catver;
    vector<Par> coords;


    scanf("%d", &testcases);

    while(testcases>0) {
        scanf("%d", &n);

        coords.resize(n);

        for(int i=0; i<n; i++) {
            scanf("%d%d", &coordX, &coordY);
            coords.push_back(make_pair(coordX, coordY));
        }

        sort(coords.begin(), coords.end());

        litside = 0;
        maxheight = 0;

        while(coords.size() > 1) {
            Par col, peak;
            col = coords.back();
            coords.pop_back();
            peak = coords.back();
            coords.pop_back();

            if (peak.second > maxheight) {
                // printf("col %d %d ||| peak %d %d\n", col.first, col.second, peak.first, peak.second);

                m = (double)(col.second - peak.second) / (col.first - peak.first);
                b = col.second - m*col.first;
                x = (maxheight - b) / m;

                cathor = x - peak.first;
                catver = peak.second - maxheight;

                //printf("%.2f %.2f  %.2f\n", m, b, x);

                maxheight = peak.second;
                litside += sqrt(cathor*cathor + catver*catver);
            }


        }

        printf("%.2f\n", litside);
		testcases--;
    }

    return 0;
}
