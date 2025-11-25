# 🧠 K-Means Clustering Implementation in C++

This project implements the **K-Means clustering algorithm** from scratch in C++. K-Means is a popular unsupervised machine learning algorithm used to partition $n$ observations into $k$ clusters, where each observation belongs to the cluster with the nearest mean (centroid).

***

## 📊 English README

### Project Overview

This is a **C++ implementation of the K-Means clustering algorithm** designed to process multi-dimensional datasets (specifically 4 dimensions, compatible with the Iris dataset). The code demonstrates fundamental concepts of data structure manipulation, mathematical calculation (Euclidean distance), and basic file I/O within a standard C++ environment.

The core objective is to iteratively refine the grouping of data points until the clusters are stable or a maximum number of iterations is reached.



### 🚀 Features & Structure

* **Unsupervised Learning:** Partitions data points into $K$ clusters based solely on spatial proximity.
* **Euclidean Distance:** Uses the standard Euclidean distance formula for measuring proximity between points and centroids.
* **Data Handling:** Includes robust functions for reading external data files (`iris.txt` format assumed) and parsing coordinate values.
* **Dynamic Clustering:** The user defines $K$ (the number of clusters) and the maximum number of optimization steps (`max_iter`) at runtime.

### ⚙️ Key Data Structures

The solution relies on the following key definitions:

| Structure | Description |
| :--- | :--- |
| `Point` (`struct`) | Represents a data point or a cluster centroid. Contains a fixed-size array (`dimensions[DIMENSION]`) to hold the coordinates. **DIMENSION** is set to **4**. |
| `point_data[]` | Array storing all input points read from the file. |
| `cluster_data[]` | Array storing the current coordinates of the $K$ cluster centroids. |
| `closer_cluster[]` | Array of integers storing the index of the assigned cluster for each point. |

### 🛠️ Compilation and Execution

To run this project, follow these steps:

1.  **Prerequisites:** Ensure you have a C++ compiler (like `g++`) and a file named `iris.txt` in the same directory containing the data points (comma-separated values).
2.  **Compile:**
    ```bash
    g++ main.cpp -o kmeans
    ```
    *(Note: On some Linux systems, you might need to add `-lm` to link the math library: `g++ main.cpp -o kmeans -lm`)*

3.  **Execute:**
    ```bash
    ./kmeans
    ```

4.  **Input:** The program will prompt you for:
    * The number of groups ($K$) you want.
    * The maximum number of iterations.

### 📐 Complexity Analysis

The algorithm is structured around these core steps:

| Function | Complexity | Description |
| :--- | :--- | :--- |
| `points_distance()` | $O(D)$ | Calculates Euclidean distance $\left(\sqrt{\sum_{i=1}^{D} (c_i - x_i)^2}\right)$ between two points. |
| `linking_point_clusters()` | $O(N \cdot K \cdot D)$ | **Assignment Step:** Assigns every point to the nearest of the $K$ centroids. |
| `recalculating_cluster()` | $O(N \cdot D)$ | **Update Step:** Recalculates the centroid's coordinates by finding the mean of all points assigned to it. |
| `kmeans()` | $O(I \cdot N \cdot K \cdot D)$ | The main loop ($I$ = iterations) orchestrating the assignment and update steps. |

---

## 🇧🇷 Português README

### Visão Geral do Projeto

Este é uma **implementação do algoritmo K-Means em C++**, desenvolvido do zero para processar conjuntos de dados multidimensionais (4 dimensões). O código demonstra conceitos fundamentais de manipulação de estruturas de dados, cálculo matemático (distância Euclidiana) e entrada/saída de arquivos (`fstream`).

O objetivo principal é refinar iterativamente o agrupamento de pontos de dados até que os clusters estejam estáveis ou um número máximo de iterações seja atingido.

### 🚀 Funcionalidades

* **Aprendizado Não Supervisionado:** Particiona os pontos de dados em $K$ clusters com base apenas na proximidade espacial.
* **Distância Euclidiana:** Utiliza a fórmula padrão da distância Euclidiana para medir a proximidade entre pontos e centróides.
* **Tratamento de Dados:** Inclui funções para leitura de arquivos de dados externos (assumindo o formato `iris.txt`) e análise dos valores de coordenadas.
* **Clusterização Dinâmica:** O $K$ (o número de clusters) e o número de iterações são definidos pelo usuário em tempo de execução.

### ⚙️ Estruturas de Dados Principais

A solução depende das seguintes definições:

| Estrutura | Descrição |
| :--- | :--- |
| `Point` (`struct`) | Representa um ponto de dado ou um centróide. Contém um array (`dimensions[4]`) para armazenar as coordenadas. |
| `point_data[]` | Array que armazena todos os pontos de entrada lidos do arquivo. |
| `cluster_data[]` | Array que armazena as coordenadas atuais dos $K$ centróides. |
| `closer_cluster[]` | Array de inteiros que armazena o índice do cluster atribuído a cada ponto. |

### 🛠️ Compilação e Execução

Para rodar este projeto:

1.  **Pré-requisitos:** Certifique-se de ter um compilador C++ e o arquivo `iris.txt` no diretório raiz com os dados (valores separados por vírgula).
2.  **Compilar:**
    ```bash
    g++ main.cpp -o kmeans
    ```
3.  **Executar:**
    ```bash
    ./kmeans
    ```
4.  **Entrada:** O programa solicitará:
    * O número de grupos ($K$).
    * O número máximo de iterações.

### 📐 Complexidade e Fluxo

O algoritmo é estruturado em torno destas etapas principais:

| Função | Complexidade | Descrição |
| :--- | :--- | :--- |
| `points_distance()` | $O(D)$ | Calcula a distância Euclidiana entre dois pontos. |
| `linking_point_clusters()` | $O(N \cdot K \cdot D)$ | **Passo de Atribuição:** Atribui cada ponto ao centróide mais próximo. |
| `recalculating_cluster()` | $O(N \cdot D)$ | **Passo de Atualização:** Recalcula as coordenadas do centróide (média dos pontos). |
| `kmeans()` | $O(I \cdot N \cdot K \cdot D)$ | O loop principal ($I$ = iterações) que orquestra os passos de atribuição e atualização. |
