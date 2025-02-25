#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;
//Definindo as constantes
#define DIMENSION 4
#define FILE_NAME "C:/Users/ryalv/Kmeans cpp/iris.txt"
//Estrutura para armazenar os pontos
struct Point
{
    double dimensions[DIMENSION];
};

//Função para criar os clusters
void create_clusters(Point cluster_data[], int k)
{
    //Criando uma estrutura para o centroide
    Point centroid;
    //Randomizando o ponto do centroide
    random_device number;  
    mt19937 gen(number()); 
    //Utilizando a distribuição uniforme para gerar os pontos
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
//Função para calcular a distancia entre os pontos
double points_distance(Point centroid, Point a)
{
    //Declarando a variável soma=0
    double sum = 0;
    //Calculando a distancia euclidiana
    for(int i = 0; i < DIMENSION; i++)
    {
        sum += pow(centroid.dimensions[i] - a.dimensions[i], 2);
    }
    //Retornando a raiz quadrada da soma
    return sqrt(sum);
}
//Função para atrelar os pontos aos clusters
void linking_point_clusters(int closer_cluster[], Point cluster_data[], Point point_data[], int k, int points)
{
    int index = 0;
    //Calculando a distancia entre os pontos e os clusters
    for(int i=0; i < points; i++)
    {
        //Definindo o primeiro cluster como o mais proximo, ou seja, a menor distancia entre o respectivo ponto e o cluster
        double menor= points_distance(cluster_data[0], point_data[i]);
        //Definindo o indice do cluster mais proximo
        for(int j=0; j < k; j++)
        {
            if(points_distance(cluster_data[j], point_data[i]) < menor)
            {
                menor = points_distance(cluster_data[j], point_data[i]);
                index = j;
            }
        //Definindo o cluster mais proximo
        }
        closer_cluster[i] = index;
    }
}
//Função para recalcular o cluster
void recalculating_cluster(int closer_cluster[], Point point_data[], Point cluster_data[], int k, int points)
{
    //Declarando as variáveis
    int cont = 0;
    double sum[DIMENSION] = {0};
    //Recalculando o cluster com base nos pontos atrelados em cada cluster
    for(int i = 0; i < k; i++)
    {
        //Percorrendo cada ponto
        for(int j = 0; j < points; j++)
        {
            //Se o ponto estiver atrelado ao cluster, a soma do ponto é adicionada à soma que será dividida pelo total de pontos
            if(closer_cluster[j] == i)
            {
                for(int l = 0; l < DIMENSION; l++)
                {
                    sum[l] += point_data[j].dimensions[l];
                }
                cont++;
            }
        }
        //Recalculando o centroide
        for(int l = 0; l < DIMENSION; l++)
        {
            cluster_data[i].dimensions[l] = sum[l] / cont;
            sum[l] = 0;
        }
    }
}
    //Função para recalcular o centroide N vezes citada pelo usuario por meio da variavel max_iter
void kmeans(int closer_cluster[], Point cluster_data[], Point point_data[], int k, int points, int max_iter)
{
    //Recalculando o cluster N vezes
    for(int i = 0; i < max_iter; i++)
    {
        //Chamando a função recalculating_cluster
        recalculating_cluster(closer_cluster, point_data, cluster_data, k, points);
        //Chamando a função linking_point_clusters
        linking_point_clusters(closer_cluster, cluster_data, point_data, k, points);
    }
}
//Função para contar as linhas do arquivo
int count_lines()
{
    string line;
    ifstream data_file(FILE_NAME);
    int cont = 0;
    //Enquanto for possivel ler uma llha do arquivo, o contador aumenta
    while(getline(data_file, line))
    {
        cont++;
    }

    return cont;
}
//Função para processar as linhas do arquivo
Point process_line(string line)
{
    //Declarando as variáveis
    Point coords;
    int index = 0;
    string coord;
    char c = ' ';
    //Percorrendo a linha
    for (size_t i = 0; i < line.size(); ++i) { // Mais correto usar size_t 

        c = line[i];
        //Se o caractere for uma virgula, o que vem antes dela é armazenado e a string coord é esvaziada
        if (c == ',') 
        {
            try 
            {
                //Convertendo a string para double
                coords.dimensions[index] = stod(coord);
                index++;
            } 
            catch (...) 
            {
                break;  
            }

            coord = "";  
        } 
        //Adiciona o caractere a string coord
        else 
        {
            coord += c;  
        }
    }
    //Retorna as coordenadas
    return coords;
}
    //Função para ler o arquivo
void read_file(Point point_data[])
{
    string line;
    ifstream data_file(FILE_NAME);
    //Se o arquivo não for encontrado, exibe a mensagem
    if(!data_file.is_open())
    {
        cout << "Couldn't find the file";
        return;
    }

    int index = 0;
    //Enquanto for possivel ler uma linha do arquivo, a linha é processada
    while(getline(data_file, line))
    {
        point_data[index] = process_line(line);
        index++;
    }
    //Fechando o arquivo
    data_file.close();
}

int main()
{
    //Declarando as variáveis
    int lines, k, max_iter = 100;
    //Entrada e saida de dados
    cout << "How many groups would you like ?: ";
    cin >> k;
    cout << endl << "How many iterations ?: ";
    cin >> max_iter;
    cout << endl;
    //Utilizando a estrutura Point para criar um vetor de clusters
    Point cluster_data[k];
    //Chamando a função create_clusters
    create_clusters(cluster_data, k);
    //Chamando a função count_lines
    lines = count_lines();
    //Utilizando a estrutura Point para criar um vetor de pontos
    Point point_data[lines];
    //Chamando a função read_file
    read_file(point_data);
    //Utilizando um vetor de inteiros para armazenar qual ponto esta mais proximo de qual cluster
    int closer_cluster[lines];
    //Chamando a função linking_point_clusters
    linking_point_clusters(closer_cluster, cluster_data, point_data, k, lines);
    //Chamando a função kmeans
    kmeans(closer_cluster, cluster_data, point_data, k, lines, max_iter);
    //Exibindo os resultados   
    for(int i=0; i<lines; i++)
    {
        cout << "The point "<< i << " is linked to the  " << closer_cluster[i] << " cluster. " << endl;
    }         
    return 0;
}