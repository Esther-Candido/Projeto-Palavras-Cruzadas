# Projeto - Palavras Cruzadas Simples (UFCD 5089 - Algoritmos)
- [Projeto - Palavras Cruzadas Simples (UFCD 5089 - Algoritmos)](#projeto---palavras-cruzadas-simples-ufcd-5089---algoritmos)
  - [1. Introdução](#1-introdução)
  - [2. Descrição do Jogo](#2-descrição-do-jogo)
    - [2.1 Tabuleiro de Jogo](#21-tabuleiro-de-jogo)
      - [2.1.1 Casas do Tabuleiro](#211-casas-do-tabuleiro)
      - [2.1.2 Criação do tabuleiro de jogo](#212-criação-do-tabuleiro-de-jogo)
      - [2.1.3 Colocação de palavras no tabuleiro](#213-colocação-de-palavras-no-tabuleiro)
    - [2.2 Modos de Jogo](#22-modos-de-jogo)
    - [2.3 Sistema de Pontuação](#23-sistema-de-pontuação)
      - [2.3.1 Exemplo Pontuação: Jogada 1](#231-exemplo-pontuação-jogada-1)
      - [2.3.2 Exemplo Pontuação: Jogada 2](#232-exemplo-pontuação-jogada-2)
      - [2.3.3 Exemplo Pontuação: Jogada 3](#233-exemplo-pontuação-jogada-3)
    - [2.4 Interface de entrada/saída e parametrização do programa](#24-interface-de-entradasaída-e-parametrização-do-programa)
    - [2.5 Exemplos de jogos](#25-exemplos-de-jogos)
      - [2.5.1 Exemplo 1: jogo em modo 1](#251-exemplo-1-jogo-em-modo-1)
      - [2.5.2 Exemplo 2: jogo em modo 1](#252-exemplo-2-jogo-em-modo-1)
      - [2.5.3 Exemplo 3: jogo em modo 2](#253-exemplo-3-jogo-em-modo-2)
  - [3. Dicas úteis e algumas regras de jogon e implementação importantes](#3-dicas-úteis-e-algumas-regras-de-jogon-e-implementação-importantes)
    - [3.1 Regras](#31-regras)
    - [3.2 Dicas úteis](#32-dicas-úteis)
  - [4. Avaliação e entrega](#4-avaliação-e-entrega)
## 1. Introdução
O projeto a realizar corresponde à implementação de uma versão muito particular de um jogo de palavras cruzadas. O objetivo do projeto é promover e avaliar a prática dos conceitos e técnicas de programação estudadas no âmbito desta UFCD, nomeadamente o trabalho com arrays de caracteres e estruturas de dados dinâmica. 

## 2. Descrição do Jogo
O  jogo  a  implementar  deverá  irá, simplesmente e por simplificação, possuir 1 só modo de jogo.

### 2.1 Tabuleiro de Jogo
O tabuleiro de jogo deve ser bidimensional e com dimensão dos eixos horizontal (linhas) e vertical (colunas) parametrizável. As coordenadas, linhas e colunas.devem ser identificadas, respetivamente, por algarismos de 1 a 15 e de A a Z, conforme ilustrado (como exemplo) na figura abaixo, para um tabuleiro de dimensão 9x9 [linhas x colunas]. A dimensão mínima para as linhas e para as colunas é de 7, a dimensão máxima para as linhas  e para as colunas de 15. O número de linhas e colunas deve ser ímpar e igual.

![Tabuleiro](img/9x9.png)

#### 2.1.1 Casas do Tabuleiro
Algumas das casas do tabuleiro possuem um significado especial, os quais se descrevem:
- `.` casa vazia, onde pode ser colocada qualquer letra. Cada letra colocada nesta casa vale o número de pontos da letra lá colocada;
- `#` **casa proibida**, onde **não pode** ser colocada qualquer letra;
- `2` casa vazia, onde pode ser colocada qualquer letra. Cada letra colocada nesta casa vale o **dobro** dos pontos da letra lá colocada;
- `3` casa vazia, onde pode ser colocada qualquer letra. Cada letra colocada nesta casa vale o **triplo** dos pontos da letra lá colocada;
- `4` casa vazia, onde pode ser colocada qualquer letra. Cada letra colocada nesta casa vale o **quadruplo** dos pontos da letra lá colocada;
- `$` casa vazia, onde pode ser colocada qualquer letra. Palavras colocadas que utilizem uma casa destas valem o dobro. Ou seja, depois de se verificar os pontos de toda a palavra, estes são duplicados. Caso a palavra utilize dois símbolos destes, é duplicada duas vezes, caso use 3 é duplicada 3 vezes e assim por diante (Mais informação na secção pontuação);
- `!` casa vazia, onde pode ser colocada qualquer letra. Palavras colocadas que utilizem uma casa destas valem o triplo. Ou seja, depois de se verificar os pontos de toda a palavra, estes são triplicados. Caso a palavra utilize dois símbolos destes, é triplicada duas vezes, caso use 3 é triplicada 3 vezes e assim por diante (Mais informação na secção pontuação);

#### 2.1.2 Criação do tabuleiro de jogo
O tabuleiro pode ser lido de um ficheiro, caso em que a distribuição dos bónus é como estiver no ficheiro, isto é, as casas com significados especiais podem estar noutras posições. Se o tabuleiro não for lido de um ficheiro, é inicializado como apresentado na Figura anterior (9x9), de acordo com as seguintes regras:
- as casas nas diagonais do tabuleiro, exceto os cantos e o centro, são símbolo conta o dobro: `2` 
- as casas a meio de cada aresta do tabuleiro têm símbolo conta triplo: `3` 
- as casas 1ª posição na diagonal em relação às casas com o símbolo conta triplo são proibidas: `#`
- os cantos do tabuleiro têm palavra conta dobro: `$`
- o centro do tabuleiro, é o símbolo conta o quádruplo: `4` 
- as casas acima, abaixo e laterais do centro têm o simbolo palavra conta triplo: `!`

#### 2.1.3 Colocação de palavras no tabuleiro
Podem-se formar palavras no tabuleiro, tanto na horizontal da esquerda para a direita, como na vertical de cima para baixo, mas nunca se consideram palavras na diagonal ou em sentido oposto. 

### 2.2 Modos de Jogo
O jogo pode ser jogado usando dois níveis de dificuldade (modo 1 e 2):
1. No modo de jogo 1: (**A implementar neste projeto**)
   - Um jogador vai fazendo jogadas, sem validação por dicionário. Ou seja, não é verificado que a palavra inserida existe;
   - O modo de jogo 1 pode utilizar o tabuleiro default (9x9) ou outra qualquer dimensão aceitável (de 7 a 15), sendo o tabuleiro criado segundo as regras descritas acima;
   - O modo de jogo 1 pode também utilizar um tabuleiro criado a partir de um ficheiro (na pasta tabuleiros encontram-se alguns ficheiros com tabuleiros que pode utilizar para testar o seu programa). Assume-se que os ficheiros de tabuleiro estão bem construidos (não possuem outros símbolos exceto os descritos) e que a dimensão é correta (dimensão ímpar, maior ou igual a 7 e menor ou igual a 15 e mesmo número de linhas e colunas), logo não é necessário testar a validade do mesmo.
   - Por cada palavra inserida, é contabilizada a pontuação da mesma (sistema de pontuação explicado abaixo) e vai sendo adicionada à pontuação total do jogo;
   - Uma palavra (mesmo sem ser validada em dicionário) só pode ser inserida se:
     - Não ocupar uma casa com o símbolo de casa proibida (`#`);
     - Caso já existam letras (de outras palavras inseridas anteriormente) no tabuleiro, a palavra a inserir tem que corresponder a essas letras (não podem ser alteradas letras anteriormente colocadas)
     - Cada nova palavra tem que ocupar pelo menos uma casa livre. Quer isso dizer que quando não houver mais casas livres o jogo termina, sendo apresentada essa informação ao jogador;
     - O jogo também pode terminar por decisão do jogador, quando inserir o comando `end` ou o número máximo de jogadas tenha sido definido e se tenham esgotado as jogadas possíveis;


### 2.3 Sistema de Pontuação
Por cada letra de uma palavra inserida deve ser considerada a seguinte pontuação (igual no modo 1 ou 2)

| a | b | c | d | e | f | g | h | i | j | k | l | m | n | o | p | q | r | s | t | u | v | w | x | y | z |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 2 | 4 | 3 | 1 | 2 | 3 | 1 | 3 | 2 | 3 | 7 | 5 | 4 | 4 | 2 | 4 | 6 | 3 | 3 | 4 | 6 | 5 | 9 | 6 | 7 | 8 |

Além da pontuação da letra, conforme tabela acima é necessário considerar o seguinte:
- Se a letra for colocada numa casa com o símbolo `2`, `3` ou `4`, os pontos da letra serão, respetivamente x2, x3 ou x4;
- Se a palavra for colocada e ocupe uma casa com o símbolo `$` (duplica palavra) o valor total da palavra é duplicado por 2 (x2). O valor da palavra é duplicado o mesmo número de vezes que ocupar esse símbolo;
- Se a palavra for colocada e ocupe uma casa com o símbolo `!` (triplica palavra) o valor total da palavra é multiplicado por 3 (x3). O valor da palavra é triplicado o mesmo número de vezes que ocupar esse símbolo;
- Se uma letra for colocada numa casa com o símbolo `.` só conta o valor da letra
- Se uma letra for colocada onde já existe uma letra (de uma palavra anterior e só no caso da nova letra ser igual à anterior pois caso contrário não é possível) só é contabilizado o valor da letra (o símbolo que lá estava antes já foi utilizado por letra/palavra anterior).

Veja os seguintes exemplos da contabilização de pontuação (score):

#### 2.3.1 Exemplo Pontuação: Jogada 1
Utilizador insere palavra Horizontal (**H**) na coordenada **A5**

![Tabuleiro](img/9x9.png)
![Score 1](img/score1.png)

  1. Verificar a bonificação de cada símbolo: `b*3 + e*1 + n*1 + f*1 + i*4 + c*1 + a*1`
  2. Ver a pontuação de cada letra: `4*3 + 2*1 + 4*1 + 3*1 + 2*4 + 3*1 + 2*1 = 12 + 2 + 4 + 3 + 8 + 3 + 2 = 34 pontos`
  3. Ver a bonificação da palavra (símbolos `$`): como não usa nenhum destes simbolos a pontuação é: `34 * 1 = 34`
  4. Atualiza pontuação do jogo: `34 pontos`

#### 2.3.2 Exemplo Pontuação: Jogada 2
Utilizador insere palavra Vertical (**V**) na coordenada **A3**

![Score 1](img/score1.png)
![Score 2](img/score2.png)

  1. Verificar a bonificação de cada símbolo: `e*1 + s*1 + b*1 + e*1 + l*1 + t*1 + o*1`. Repare que a casa A5 agora não bonifica. É como se tivesse símbolo `.`
  2. Ver a pontuação de cada letra: `2*1 + 3*1 + 4*1 + 2*1 + 5*1 + 4*1 + 2*1 = 2+3+4+2+5+4+2 = 22 pontos`
  3. Ver a bonificação da palavra (símbolos `$`): Utiliza um símbolo (Casa A9): `22*2=44 pontos`
  4. Atualiza pontuação do jogo: `34 + 44 = 78 pontos`

#### 2.3.3 Exemplo Pontuação: Jogada 3
**Importante**: Estas imagens não contemplam todos os casos e caracteres de pontuação do tabuleiro. Servem só para demonstrar o sistema de pontuação.

![Score 2](img/score2.png)
![Score 3](img/score3.png)

  1. Verificar a bonificação de cada símbolo: `p*1 + e*1 + r*1 + s*1 + p*3 + i*1 + c*1 + a*1 + z*1`. Repare que o símbolo (`$`) na casa I1 e I9 não bonificam as letras. Irão sim bonificar a palavra como um todo
  2. Ver a pontuação de cada letra: `4*1 + 2*1 + 3*1 + 3*1 + 4*3 + 2*1 + 3*1 + 2*1 + 8*1= 4+2+3+3+12+2+3+2+8 = 39 pontos`
  3. Ver a bonificação da palavra (símbolos `$`): Utiliza dois símbolos: `39*2*2=156 pontos`
  4. Atualiza pontuação do jogo: `78 + 160 = 238 pontos`

### 2.4 Interface de entrada/saída e parametrização do programa
O programa deverá ser invocado na linha de comando da seguinte forma: `$ ./palavras [OPTIONS] `. `$` é a prompt do Linux e `./` representa a pasta corrente. `palavras` designa o nome do ficheiro executável contendo o programa desenvolvido e  `[OPTIONS]`  designa  a  possibilidade  de  o  programa  ser  invocado  com  diferentes  opções  de funcionamento. As opções de funcionamento são identificadas sempre como strings começadas com o caractere `-`, e podem aparecer por qualquer ordem. De seguida, descrevem-se as várias opções disponíveis: 
- **-h**: Mostra ajuda ao utilizador. Já se encontra implementado no código fornecido aos alunos
- **-t nn**: Dimensão do tabuleiro (n representa um inteiro ímpar entre 7 e 15);
- **-i filename**: Ficheiro onde está o tabuleiro a ser carregado para o jogo, em vez do tabuleiro padrão. Quando é carregado um tabuleiro, tem que ser calculada a sua dimensão e a dimensão do tabuleiro (opção -t) fica sem efeito, mesmo que inserida.
- **-n nn:** Número máximo de jogadas a jogar. Quando não definido joga-se até no ser possível inserir mais palavras (não há espaços livres sem letras) ou o utilizador inserir `end`. *Atenção!! caso o número máximo de jogadas esteja definido, o utilizador pode sempre acabar o jogo através do comando `end`*..

```text
 1 $ . . . 3 . . . p 
 2 . 2 . # . # . 2 e 
 3 e . 2 . . . 2 . r 
 4 s # . 2 ! 2 . # s 
 5 b e n f i c a . p 
 6 e # . 2 ! 2 . # i 
 7 l . 2 . . . 2 . c 
 8 t 2 . # . # . 2 a 
 9 o . . . 3 . . . z 
   A B C D E F G H I 
Pontuação final: 238 pontos
Jogadas efetuadas: 3
```
- Exemplos de comandos válidos para execução do jogo:
  - `./palavras -t 11` Tabuleiro de 11x11 (a ser gerado automaticamente), sem limite de jogadas e sem escrever tabuleiro final em ficheiro
  - `./palavras -t 7 -n 10` Tabuleiro de 7x7 (a ser gerado automaticamente), com limite de 10 jogadas e sem escrever tabuleiro final em ficheiro
  - `./palavras -n 5` Tabuleiro de 9x9 (tamanho default - a ser gerado automaticamente), sem limite de jogadas e sem escrever tabuleiro final em ficheiro
  - `./palavras -o ./outputs/final.txt` Tabuleiro 9x9 (a ser gerado automaticamente), sem limite de jogadas e escreve tabuleiro final em ficheiro chamado final.txt. 
  - `./palavras -i ./tabuleiros/7x7_custom.tab -n 5` Tabuleiro carregado de ficheiro, com limite de 5 jogadas e sem escrever tabuleiro final em ficheiro
  - `./palavras ./tabuleiros/7x7_custom.tab -n 25`: Tabuleiro carregado de ficheiro, com limite de 25 jogadas e não escreve tabuleiro final em ficheiro. 
  - Outras combinações de opções poderão haver. O programa não será testado inserido opções erradas e/ou incompatíveis (tipo inserir um tabuleiro custom e dar uma dimensão errada. Ou é dada a dimensão e o tabuleiro é gerado, ou é dado um ficheiro com o tabuleiro. Nunca as duas)

## 3. Dicas úteis e algumas regras de jogo e implementação importantes
### 3.1 Regras
- Não é possível inserir no tabuleiro palavras com dimensão < 2
- As coordenadas de uma palavra (ex. `A5H`) tanto podem ser escritas em minúsculas ou maiúsculas
- As palavras a escrever no tabuleiro são só aquelas sem caracteres especiais. Ou seja cada caracter (`c`) de uma palavra deve obedecer à seguinte condição `(c >= 'a' && c <= 'z')`. Caso contrária o comando não é válido
- O tabuleiro deve ser implementado com memória dinâmica (malloc)
- As palavras a jogar têm que ter uma dimensão maior ou igual a 3 (`>= 3`).
- O ficheiro `main.c` e a biblioteca `ui` não podem ser alterados.

### 3.2 Dicas úteis
- Utilize como base o código fornecido
- Vá sempre testando o código
- Criei funções para apoiar
- Planeie antes de executar
- Leia com atenção o enunciado e coloque as suas questões antes de iniciar o desenvolvimento
- Utilize para teste os tabuleiros fornecidos na pasta tabuleiros. Contudo tenha em atenção que na avaliação, outros tabuleiros poderão ser utilizados.

### 3.3 Exemplos
A sequência do jogo é a seguinte:
- Assim que todas as configurações iniciais forem carregadas, é impresso o tabuleiro e solicitado o comando ao jogador (obrigatório usar a ui);
- O jogador insere as coordenadas e o sentido da palavra (v-> vertical de cima para baixo) (H-> horizontal da esquerda para a direita)
- Após a jogada a palavra é escrita (caso seja impossível escrever dá erro através da macro definida na ui) é impresso o tabuleiro com a palavra e a pontuação da jogada
- Quando o jogo chega ao fim (por ordem do user com o comando `end`, por terminar o número de jogadas possíveis ou todas as casas ocupadas) é escrita a pontuação final e sai. Caso a opção gravar tabuleiro final em ficheiro seja passada, deve ser escrito no ficheiro (função já implementada na ui)
- O aluno não para escrever e ler só deve usar as funções da ui.

**Exemplo de jogo sem opções passadas `./palavras`**
```console
 1 $ . . . 3 . . . $
 2 . 2 . # . # . 2 .
 3 . . 2 . . . 2 . .
 4 . # . 2 ! 2 . # .
 5 3 . . ! 4 ! . . 3
 6 . # . 2 ! 2 . # .
 7 . . 2 . . . 2 . .
 8 . 2 . # . # . 2 .
 9 $ . . . 3 . . . $
   A B C D E F G H I
Insira comando-> A3H bacalhau
 1 $ . . . 3 . . . $
 2 . 2 . # . # . 2 .
 3 b a c a l h a u .
 4 . # . 2 ! 2 . # .
 5 3 . . ! 4 ! . . 3
 6 . # . 2 ! 2 . # .
 7 . . 2 . . . 2 . .
 8 . 2 . # . # . 2 .
 9 $ . . . 3 . . . $
   A B C D E F G H I
Jogada 1: [A3H] bacalhau -> 32 pontos
Insira comando-> A9H anabela
 1 $ . . . 3 . . . $
 2 . 2 . # . # . 2 .
 3 b a c a l h a u .
 4 . # . 2 ! 2 . # .
 5 3 . . ! 4 ! . . 3
 6 . # . 2 ! 2 . # .
 7 . . 2 . . . 2 . .
 8 . 2 . # . # . 2 .
 9 a n a b e l a . $
   A B C D E F G H I
Jogada 2: [A9H] anabela -> 50 pontos
Insira comando-> end
Fim do jogo. Total de pontos obtidos: 82
```

**Exemplo com opção -n 4 `./palavras -n 4`**
```console
 1 $ . . . 3 . . . $
 2 . 2 . # . # . 2 .
 3 . . 2 . . . 2 . .
 4 . # . 2 ! 2 . # .
 5 3 . . ! 4 ! . . 3
 6 . # . 2 ! 2 . # .
 7 . . 2 . . . 2 . .
 8 . 2 . # . # . 2 .
 9 $ . . . 3 . . . $
   A B C D E F G H I
Insira comando-> A1V ana
 1 a . . . 3 . . . $
 2 n 2 . # . # . 2 .
 3 a . 2 . . . 2 . .
 4 . # . 2 ! 2 . # .
 5 3 . . ! 4 ! . . 3
 6 . # . 2 ! 2 . # .
 7 . . 2 . . . 2 . .
 8 . 2 . # . # . 2 .
 9 $ . . . 3 . . . $
   A B C D E F G H I
Jogada 1: [A1V] ana -> 16 pontos
Insira comando-> A1H ana
 1 a n a . 3 . . . $
 2 n 2 . # . # . 2 .
 3 a . 2 . . . 2 . .
 4 . # . 2 ! 2 . # .
 5 3 . . ! 4 ! . . 3
 6 . # . 2 ! 2 . # .
 7 . . 2 . . . 2 . .
 8 . 2 . # . # . 2 .
 9 $ . . . 3 . . . $
   A B C D E F G H I
Jogada 2: [A1H] ana -> 8 pontos
Insira comando-> A1V setubal
ERRO! Comando incorreto
Insira comando-> A9V ana
ERRO! Comando incorreto
Insira comando-> A6V ana
 1 a n a . 3 . . . $
 2 n 2 . # . # . 2 .
 3 a . 2 . . . 2 . .
 4 . # . 2 ! 2 . # .
 5 3 . . ! 4 ! . . 3
 6 a # . 2 ! 2 . # .
 7 n . 2 . . . 2 . .
 8 a 2 . # . # . 2 .
 9 $ . . . 3 . . . $
   A B C D E F G H I
Jogada 3: [A6V] ana -> 8 pontos
Fim do jogo. Total de pontos obtidos: 32
```

## 4. Avaliação e entrega
O projeto será cotado para 20 valores, distribuídos da seguinte forma:
- Qualidade dos Comentários - 1 val
- Organização do código (bibliotecas/funções) - 2 val
- Qualidade do código e opções tomadas (algoritmos implementados) - 3 val
- Gestão da memória (malloc, free e erros no valgrind) - 2 val
- Testes automáticos (a ver com as saídas do programa) - 12 val, distribuídos da seguinte forma
- Apresentação oral (com direito a questões), individualmente para cada elemento do grupo, consoante o nível de conhecimento das soluções apresentadas: **Até -5 valores**. Nota 20 significa que o formador percebe e reconhece que o formando trabalhou ativamente e conhece o código efetuado e as soluções implementadas. 

