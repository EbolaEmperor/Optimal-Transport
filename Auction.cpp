// Auction Algorithm for Optimal Assignment Problem.

#include <iostream>
#include <cstring>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;

int n;
double *costmempool, **cost, maxcost;
// cost[i][j]: The cost for assigning i-th person doing j-th work.

int *xi;
// partial assignment vector

double *g;
// dual vector

double eps;
// complementary slackness, usually take 1.0/n^2

void initialize(){
    cout << "The number of persons (also works):" << endl;
    cin >> n;
    cost = new double* [n];
    costmempool = new double [n*n];
    for(int i = 0; i < n; i++)
        cost[i] = costmempool + i*n;
    cout << "The cost matrix:" << endl;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            cin >> cost[i][j];
            maxcost = std::max(maxcost, fabs(cost[i][j]));
        }
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cost[i][j] /= maxcost;
    cout << "The complementary slackness:" << endl;
    cin >> eps;
}

int auction(){
    xi = new int [n];
    g = new double [n];
    memset(xi, -1, sizeof(int)*n);
    memset(g, 0, sizeof(double)*n);
    int assignedNum = 0;
    int iteration = 0;

    while(assignedNum < n){
        int i = 0;
        while(xi[i]!=-1) i++;
        int j1 = -1, j2 = -1;
        for(int j = 0; j < n; j++)
            if(j1==-1 || cost[i][j]-g[j]<cost[i][j1]-g[j1])
                j2=j1, j1 = j;
            else if(j2==-1 || cost[i][j]-g[j]<cost[i][j2]-g[j2])
                j2 = j;
        g[j1] = cost[i][j1]-(cost[i][j2]-g[j2])-eps;
        for(int k = 0; k < n; k++)
            if(xi[k]==j1) xi[k] = -1, assignedNum--;
        xi[i] = j1;
        assignedNum++;
        iteration++;
    }
    cout << "Iterations: " << iteration << endl;

    int ans = 0;
    for(int i = 0; i < n; i++)
        ans += cost[i][xi[i]]*maxcost;
    return ans;
}

int main(){
    initialize();
    double ans = auction();
    cout << "Optimal Cost: " << ans << endl;
    cout << "Optimal Assignment: ";
    for(int i = 0; i < n; i++)
        cout << xi[i] << ' ';
    cout << endl;
    return 0;
}