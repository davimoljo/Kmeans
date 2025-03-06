#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

#define DIMENSION 4
#define FILE_NAME "iris.txt"

struct Point
{
    double dimensions[DIMENSION];
};

// Conta o número de linhas no arquivo (número de pontos)
int count_lines() 
{
    string line;
    ifstream data_file(FILE_NAME);
    int cont = 0;
    while (getline(data_file, line))
        cont++;
    return cont;
}

// Processa uma linha do arquivo para extrair os valores e formar um ponto
Point process_line(string line) 
{
    Point coords;
    int index = 0;
    string coord;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
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

// Lê os pontos do arquivo e os armazena em point_data
void read_file(Point point_data[]) 
{
    string line;
    ifstream data_file(FILE_NAME);
    if (!data_file.is_open()) 
    {
        cout << "Couldn't find the file";
        return;
    }

    int index = 0;

    while (getline(data_file, line)) 
    {
        point_data[index] = process_line(line);
        index++;
    }

    data_file.close();
}

// Inicializa os clusters escolhendo valores aleatórios dos pontos existentes
void create_clusters(Point cluster_data[], Point points_data[], int k, int points) 
{
    Point centroid;
    random_device number;  
    mt19937 gen(number()); 
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < DIMENSION; j++) 
        {
            uniform_int_distribution<int> distrib(0, points - 1);
            centroid.dimensions[j] = points_data[distrib(gen)].dimensions[j];
        }
        cluster_data[i] = centroid;
    }
}

// Calcula a distância Euclidiana entre dois pontos
double points_distance(Point centroid, Point a)
{
    double sum = 0;
    for (int i = 0; i < DIMENSION; i++) 
    {
        sum += pow(centroid.dimensions[i] - a.dimensions[i], 2);
    }
    return sqrt(sum);
}

// Atribui cada ponto ao cluster cujo centróide está mais próximo
void linking_point_clusters(int closer_cluster[], Point cluster_data[], Point point_data[], int k, int points) 
{
    for (int i = 0; i < points; i++) 
    {
        double menor = points_distance(cluster_data[0], point_data[i]);
        int index = 0;
        for (int j = 1; j < k; j++) 
        {
            double dist = points_distance(cluster_data[j], point_data[i]);
            if (dist < menor) 
            {
                menor = dist;
                index = j;
            }
        }
        closer_cluster[i] = index;
    }

}

// Recalcula os centróides dos clusters com base nos pontos atribuídos
void recalculating_cluster(int closer_cluster[], Point point_data[], Point cluster_data[], int k, int points) 
{
    for (int i = 0; i < k; i++) 
    {
        int cont = 0;
        double sum[DIMENSION] = {0};
        for (int j = 0; j < points; j++) 
        {
            if (closer_cluster[j] == i) 
            {
                for (int l = 0; l < DIMENSION; l++) 
                {
                    sum[l] += point_data[j].dimensions[l];
                }
                cont++;
            }
        }

        if (cont > 0) 
        { // Atualiza o centróide somente se o cluster tiver pontos
            for (int l = 0; l < DIMENSION; l++) 
            {
                cluster_data[i].dimensions[l] = sum[l] / cont;
            }
        }
    }
}

// Executa o algoritmo k-means para um número máximo de iterações
void kmeans(int closer_cluster[], Point cluster_data[], Point point_data[], int k, int points, int max_iter) 
{
    for (int i = 0; i < max_iter; i++) {
        recalculating_cluster(closer_cluster, point_data, cluster_data, k, points);
        linking_point_clusters(closer_cluster, cluster_data, point_data, k, points);
    }

}

// Função que exibe os resultados encontrados pelo algoritmo
void show_results(int closer_cluster[], int points, int k)
{

    // Qual ponto pertence a qual cluster
    for (int i = 0; i < points; i++) 
    {
        cout << "The point " << i + 1 << " is linked to cluster " << closer_cluster[i] + 1 << "." << endl;
    }

    cout << endl;

    cout << "Cluster-Point percentage: " << endl << endl;

    // Porcentagem de pontos atrelados a cada cluster
    for(int i = 0; i < k; i++)
    {
        float cont=0;

        for(int j = 0; j < points; j++) 
        {
            if(i == closer_cluster[j])
                cont++;
        }
        cout << "Cluster " << i + 1 << ": " << (cont/points)*100 << "%" << endl;
    }
}


int main() 
{
    int lines, k, max_iter = 100;
    
    // Pergunta ao usuário quantos grupos (clusters) deseja formar
    cout << "How many groups would you like ?: ";
    cin >> k;
    
    // Pergunta quantas iterações o algoritmo deve executar
    cout << endl << "How many iterations ?: ";
    cin >> max_iter;
    cout << endl;
    
    // Conta quantos pontos (linhas) existem no arquivo
    lines = count_lines();
    
    // Cria um array para armazenar os pontos lidos do arquivo
    Point point_data[lines];
    read_file(point_data);
    
    // Cria um array para armazenar os centróides dos clusters
    Point cluster_data[k];
    create_clusters(cluster_data, point_data, k, lines);
    
    // Array para armazenar a associação de cada ponto ao cluster mais próximo
    int closer_cluster[lines];
    linking_point_clusters(closer_cluster, cluster_data, point_data, k, lines);
    
    // Executa o k-means, refinando as associações e centróides pelo número de iterações definido
    kmeans(closer_cluster, cluster_data, point_data, k, lines, max_iter);
    
    // Exibe o resultado
    show_results(closer_cluster, lines, k);

    return 0;
}
