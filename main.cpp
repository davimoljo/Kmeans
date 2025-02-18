#include <iostream>
using namespace std;

#define N 6
#define M 2

void k_means(double x[][M], int k){
    
}

int main()
{
    double x[N][M] = { {1, 2}, {2, 3}, {3, 4}, {6, 5}, {7, 6}, {8, 7}};
    int k = 2;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++)
            cout << x[i][j] << ' ';
        cout << endl;
    }
            
    k_means(x, k);
    
    return 0;
}