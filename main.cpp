#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

#define DIMENSION 4
#define FILE_NAME "C:/Users/ryalv/Kmeans cpp/iris.txt"

struct Point
{
    double dimensions[DIMENSION];
};

struct Cluster
{
    Point centroid;
};


int count_lines()
{
    string line;
    ifstream data_file(FILE_NAME);
    int cont = 0;

    while(getline(data_file, line))
    {
        cont++;
    }

    return cont;
}

Point process_line(string line)
{
    Point coords;
    int index = 0;
    string coord;
    char c = ' ';

    for (size_t i = 0; i < line.size(); ++i) { // Mais correto usar size_t 

        c = line[i];

        if (c == ',') 
        {
            try 
            {
                coords.dimensions[index] = stod(coord);
                index++;
            } 
            catch (...) 
            {
                break;  
            }

            coord = "";  
        } 

        else 
        {
            coord += c;  
        }
    }

    return coords;
}

void read_file(Point point_data[])
{
    string line;
    ifstream data_file(FILE_NAME);

    if(!data_file.is_open())
    {
        cout << "Couldn't find the file";
        return;
    }

    int index = 0;

    while(getline(data_file, line))
    {
        point_data[index] = process_line(line);
        index++;
    }
    
    data_file.close();
}

int main()
{
    int lines, k, max_iter = 100;

    cout << "How many groups would you like ?: ";
    cin >> k;
    cout << endl << "How many iterations ?: ";
    cin >> max_iter;
    cout << endl;
    
    for(int i = 0; i < k; i++)
    {
    }

    lines = count_lines();

    Point point_data[lines];

    read_file(point_data);

    for(int j = 0; j < lines; j++)
    {
        cout << fixed << setprecision(1) << point_data[j].dimensions[0] << " ";
        cout << fixed << setprecision(1) << point_data[j].dimensions[1] << " ";
        cout << fixed << setprecision(1) << point_data[j].dimensions[2] << " ";
        cout << fixed << setprecision(1) << point_data[j].dimensions[3] << endl;
    }
    
    return 0;
}