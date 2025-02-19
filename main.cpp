#include <iostream>
#include <random>
#include <cmath>
#include <fstream>

using namespace std;

#define N 6
#define M 2

struct point
{
    float vector[4];
};


void read_file()
{
    char line[200];
    ifstream data_file("C:/Users/ryalv/Kmeans cpp/irisdata.txt");

    if(!data_file.is_open())
    {
        cout << "Error";
        return;
    }
    
    while(data_file.getline(line, 200))
    {
        cout << line << endl;
    }
    
    data_file.close();
}

void k_means(double x[][M], int k)
{
    for(int i = 0; i < k; i++)
    {

    }    
}

int main()
{
    int k, max_iter = 100;

    cout << "How many groups would you like ?: ";
    cin >> k;
    cout << endl << "How many iterations ?: ";
    cin >> max_iter;
    cout << endl;
    
    read_file();

    return 0;

}