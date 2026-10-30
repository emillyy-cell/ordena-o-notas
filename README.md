# Ordenação de Notas da Turma

Trabalho da disciplina de **Algoritmos e Pensamento Computacional** (UDF) sobre aplicação prática dos algoritmos de ordenação **Bubble Sort** e **Quick Sort** em linguagem C.

## Objetivo

Criar um programa em C que organize as notas de uma turma da menor para a maior, usando dois algoritmos diferentes sobre os mesmos dados, e comparar quanto trabalho cada um faz.

## Situação-problema

No fim do bimestre o professor tem as notas anotadas na ordem da chamada (por nome). Nessa ordem é difícil responder perguntas simples, como:

- quem ficou abaixo da média e vai para a recuperação?
- qual foi a menor e a maior nota da turma?
- como está a distribuição das notas?

Com a lista ordenada por nota, isso fica visível na hora: os alunos de recuperação aparecem todos juntos no começo e as maiores notas ficam no final. Em uma turma pequena dá até para fazer na mão, mas em um sistema da faculdade com milhares de alunos a ordenação precisa ser feita pelo computador, e de forma eficiente.

## Como funciona o programa

- A turma tem **12 alunos**. Cada aluno tem um nome e uma nota.
- Os nomes e as notas ficam em **dois vetores paralelos**: a posição `i` do vetor `nomes` corresponde à posição `i` do vetor `notas`. Por isso, quando uma nota troca de lugar, o nome troca junto.
- O programa mostra a turma **antes** de ordenar (ordem da chamada) e depois deixa o usuário escolher:
  - `1` ordenar com Bubble Sort
  - `2` ordenar com Quick Sort
  - `3` rodar os dois e comparar
  - `0` sair
- Cada algoritmo trabalha em uma **cópia** dos dados, então os dois ordenam exatamente a mesma lista original.
- No final aparece a quantidade de **comparações** e **trocas** de cada algoritmo.
- Alunos com nota abaixo de 6,0 aparecem marcados como `(recuperacao)`.

## Como executar

### Online (sem instalar nada)

1. Acesse o [OnlineGDB](https://www.onlinegdb.com/) e selecione a linguagem **C**.
2. Cole o conteúdo de `ordena_notas.c` e clique em **Run**.
3. Digite a opção do menu no terminal que aparece embaixo.

### No computador (com GCC)

```bash
gcc ordena_notas.c -o ordena_notas
./ordena_notas
```

No Windows, o executável é `ordena_notas.exe`.

## Os algoritmos

### Bubble Sort

O Bubble Sort percorre o vetor comparando cada elemento com o **vizinho da direita**. Se o da esquerda for maior, os dois trocam de lugar.

A cada passada completa, a maior nota que ainda estava fora do lugar vai "subindo" até o final do vetor, como uma bolha. Por isso, a cada nova passada dá para olhar uma posição a menos.

Exemplo com `[7.5, 4.0, 9.0]`:

| Comparação | Troca? | Vetor |
|---|---|---|
| 7.5 e 4.0 | sim | `[4.0, 7.5, 9.0]` |
| 7.5 e 9.0 | não | `[4.0, 7.5, 9.0]` |

É simples de entender e de programar, mas faz muitas comparações: sempre faz todas as passadas, mesmo que o vetor já esteja ordenado antes.

**Complexidade:** O(n²) no caso médio e no pior caso.

### Quick Sort

O Quick Sort usa a estratégia de **dividir para conquistar**:

1. Escolhe um **pivô** (neste programa, sempre o último elemento do trecho).
2. Passa todas as notas menores ou iguais ao pivô para a esquerda.
3. Coloca o pivô logo depois delas. Essa já é a posição final dele.
4. Repete o mesmo processo no pedaço da esquerda e no da direita.

O passo 4 é feito com **recursividade**: a função `quickSort` chama a si mesma para os dois pedaços. A recursão para quando o pedaço tem 0 ou 1 elemento (`inicio >= fim`).

O particionamento usado é o de **Lomuto**, o mesmo visto em aula: a variável `i` marca até onde vão as notas menores que o pivô e a variável `j` percorre o trecho.

Exemplo com `[7.5, 4.0, 9.0, 6.5]` e pivô `6.5`:

- menores que 6.5: `4.0`
- maiores que 6.5: `7.5`, `9.0`
- depois da partição: `[4.0, 6.5, 9.0, 7.5]` → o 6.5 já está no lugar certo, falta ordenar `[9.0, 7.5]`

**Complexidade:** O(n log n) no caso médio. No pior caso (pivô sempre o menor ou o maior) cai para O(n²).

## Resultado com os dados do programa

| Algoritmo | Comparações | Trocas |
|---|---|---|
| Bubble Sort | 66 | 33 |
| Quick Sort | 32 | 13 |

Com só 12 alunos o Quick Sort já fez menos da metade das comparações. Quanto maior a lista, maior fica essa diferença, porque o Bubble Sort cresce na ordem de n² e o Quick Sort, em média, na ordem de n log n.

## Estrutura do projeto

```
ordena-o-notas/
├── ordena_notas.c   # código-fonte com os dois algoritmos
├── README.md        # este arquivo
└── .gitignore       # ignora os executáveis gerados
```

## Autora

Emilly Lorrany Alves dos Santos, Análise e Desenvolvimento de Sistemas, UDF
