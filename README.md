K-Means em C++
Implementação do algoritmo de agrupamento K-Means em C++, utilizando apenas bibliotecas padrão.

📌 Descrição
O K-Means é um algoritmo de aprendizado não supervisionado que divide um conjunto de dados em k clusters, com base na proximidade dos pontos aos centros dos grupos.

Etapas do Algoritmo:
Inicialização dos centros dos clusters.

Atribuição dos pontos ao cluster mais próximo.

Atualização dos centros com a média dos pontos atribuídos.

Repetição até convergência ou limite de iterações.

⚙️ Funcionalidades
Leitura de dados a partir de arquivos .txt.

Parâmetros de entrada: número de clusters (k) e número máximo de iterações (padrão: 100).

Testado com o conjunto de dados Iris:

Agrupamento com todas as 6 combinações de pares de variáveis.

Agrupamento com as 4 variáveis simultaneamente.

K-Means in C++
Implementation of the K-Means clustering algorithm in C++, using only standard libraries.

📌 Description
K-Means is an unsupervised learning algorithm that groups data into k clusters based on proximity to cluster centers.

Algorithm Steps:
Initialize cluster centers.

Assign each point to the nearest cluster (e.g., using Euclidean distance).

Update cluster centers as the mean of assigned points.

Repeat until convergence or max iterations.

⚙️ Features
Reads data from .txt files.

User-defined parameters: number of clusters (k) and max iterations (default: 100).

Evaluation using the Iris dataset:

All 6 pairwise combinations of the 4 variables.

All 4 variables together.
