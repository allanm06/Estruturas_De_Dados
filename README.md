# Estruturas_De_Dados
Códigos desenvolvidos por mim na matéria Estrutura de Dados na UFMG, semestre 2024/2

**----------Trabalho Prático 1----------**

  Neste trabalho prático, foi pedido a implementação de pelo menos três
algoritmos de ordenação, sendo um deles o quicksort, para gerar diferentes
listas ordenadas, com base em um arquivo.xcsv fornecido. Este arquivo
fornecido tinha em seu conteúdo informações e registros de diversas pessoas,
como nome, CPF e endereço. Deveriam ser geradas várias listas diferentes e
independentes, baseada em chaves/algoritmos específicos. O sistema foi implementado na linguagem C, e processa registros de
um arquivo para realizar ordenações utilizando três algoritmos de ordenação:
Quicksort, Mergesort e Heapsort.
O código está organizado em 3 arquivos principais, registro.c, que faz
as operações de alocação de memória, leitura de dados, criação de índices e
entre outras, sort.c, que são os algoritmos de ordenação implementados, e o
main.c que é o arquivo principal do código, onde são passadas as entradas de
informações.

**----------Trabalho Prático 2----------**

  Neste trabalho prático, foi solicitado o desenvolvimento de uma aplicação para
simular o gerenciamento de atendimentos hospitalares, utilizando conceitos de
estruturas de dados e algoritmos de escalonamento. A aplicação deveria ser capaz de
processar informações fornecidas em um arquivo .csv, contendo registros de
pacientes, procedimentos e tempos médios de atendimento. Os principais objetivos
incluíram a implementação de estruturas como filas e min-heaps para organizar
eventos e gerenciar prioridades, além da simulação de eventos hospitalares, como
triagem, atendimento e alta. A saída esperada da aplicação seria uma lista detalhada
com o tempo total, de atendimento e de espera para cada paciente, garantindo
eficiência no processamento e ordenação correta dos eventos. A partir desses
requisitos, foram utilizadas técnicas de normalização de tempos, manipulação de
estruturas dinâmicas e integração de diferentes componentes para alcançar os
resultados esperados.
  O sistema foi organizado em módulos
específicos, distribuídos em vários arquivos principais:

-> leitor_de_csv.c: Responsável por realizar a leitura do arquivo de entrada,
processando as informações e estruturando os dados em listas de pacientes e
procedimentos.

-> escalonador.c: Implementa o min-heap, utilizado para gerenciar a ordem cronológica
dos eventos e processar os pacientes com base em critérios de prioridade.

-> fila.c: Contém as operações de gerenciamento de filas, utilizadas para organizar os
pacientes em diferentes níveis de urgência.

-> simulacao.c: Realiza a lógica de simulação, processando os eventos e calculando os
tempos de atendimento, espera e saída de cada paciente.

**----------Trabalho Prático 3----------**

  Este trabalho prático pedia a implementação de um sistema flexível para
filtragem e ordenação de voos, utilizando expressões de filtro fornecidas pelo
usuário. O sistema lê um vetor de estruturas, e, com base em uma expressão
de filtro, extrai as condições, filtra os voos que satisfazem essas condições, por
fim, ordena os resultados de acordo com um critério especificado. O objetivo
desta implementação é permitir a composição de filtros complexos, suportando
diferentes campos (origem, destino, preço, assentos, paradas e duração) e
operadores relacionais, de modo a atender a diversas consultas do usuário.
   Ele está organizado em módulos com as
seguintes responsabilidades:
-> Avl.c: Implementa árvore AVL para armazenar e gerenciar chaves associadas a lista
de índices.

-> Indices.c: Filtra, organiza e processa consultas de voos, permite as buscar por
diferentes critérios.

-> Quicksort.c: Implementação do Quicksort para ordenar os voos.

-> Vôo.c: Lê as informações dos voos, calcula a duração dos voos.

-> Main.c: É a alma do trabalho, chama e comanda as funções dos outros arquivos.

**Todos os códigos foram desenvolvidos usando compilador C GCC e em
um computador com processador Intel Celeron 1.5gHz com 4GB de RAM e HD de
512GB**
