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

/*struct Cluster
{
    Point centroid;
};
*/

void create_clusters(Point cluster_data[], int k)
{
    Point centroid;

    random_device number;  
    mt19937 gen(number()); 

    for(int i = 0; i < k; i++)
    {
        for(int j = 0; j < DIMENSION; j++)
        {
            uniform_real_distribution<double> distrib(0.0, 10.0);
            centroid.dimensions[j] = distrib(gen);
        }
        cluster_data[i] = centroid;
    }
}

double points_distance(Point centroid, Point a)
{
    double sum = 0;

    for(int i = 0; i < DIMENSION; i++)
    {
        sum += pow(centroid.dimensions[i] - a.dimensions[i], 2);
    }

    return sqrt(sum);
}

void linking_point_clusters(int closer_cluster[], Point cluster_data[], Point point_data[], int k, int points)
{
    int index = 0;
    for(int i=0; i < points; i++)
    {
        double menor= points_distance(cluster_data[0], point_data[i]);
        for(int j=0; j < k; j++)
        {
            if(points_distance(cluster_data[j], point_data[i]) < menor)
            {
                menor = points_distance(cluster_data[j], point_data[i]);
                index = j;
            }

        }
        closer_cluster[i] = index;
    }
}

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
    
    Point cluster_data[k];

    create_clusters(cluster_data, k);

    // for(int j = 0; j < k; j++)
    // {
    //     for(int i = 0; i < DIMENSION; i++)
    //     {
    //         cout << cluster_data[j].dimensions[i] << " ";
    //     }
    //     cout << endl;
    // }

    lines = count_lines();

    Point point_data[lines];

    read_file(point_data);

    // for(int j = 0; j < lines; j++)
    // {
    //     cout << fixed << setprecision(1) << point_data[j].dimensions[0] << " ";
    //     cout << fixed << setprecision(1) << point_data[j].dimensions[1] << " ";
    //     cout << fixed << setprecision(1) << point_data[j].dimensions[2] << " ";
    //     cout << fixed << setprecision(1) << point_data[j].dimensions[3] << endl;
    // }

    int closer_cluster[lines];

    return 0;
}