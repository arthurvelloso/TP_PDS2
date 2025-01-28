# TP_PDS2: Sistema de Jogos de Tabuleiro

Descrição do Projeto: 
Este sistema implementa três jogos de tabuleiro clássicos: Reversi, Lig 4 e Jogo da Velha. Ele permite o cadastro e gerenciamento de jogadores, execução de partidas e manutenção de estatísticas, utilizando princípios de orientação a objetos e boas práticas de desenvolvimento.


## Estrutura do Sistema
### Jogos Implementados:

  TicTacToe: Jogo da Velha.  
  Reversi: Reversi/Othello.  
  Connect4: Lig 4.  

### Cadastro de Jogadores
Os jogadores são armazenados no arquivo users.txt.

Funções Principais:

    instance_all: Carrega todos os jogadores cadastrados.  
    sign_up_player: Permite o cadastro de novos jogadores.  
    list_players: Lista jogadores e suas estatísticas (vitórias, empates, derrotas).  


### Execução de Partidas
Jogos Disponíveis:

    R para Reversi.  
    C para Connect4.  
    T para Jogo da Velha.  

Execução:

    Função execute_game: Inicia uma partida entre dois jogadores.


## Menu Principal
Comandos:

    SP: Cadastrar jogador.  
    RP: Remover jogador.  
    LP: Listar jogadores.  
    EG: Executar jogo.  
    END: Finalizar sistema.

## Ferramentas Utilizadas
 Linguagem: C++  
 Controle de Versão: Git e GitHub.  
 Testes: Testes unitários automatizados com a biblioteca Doctest (https://github.com/doctest/doctest)  
 Documentação: ReadMe e arquivo Doxyfile (https://doxygen.nl/)  
 
## Instruções para Execução
Clonar o Repositório:  

    git clone https://github.com/arthurvelloso/TP_PDS2.git

Compilar o programa:

    make

Apagar arquivos intermediários (arquivos .o e executáveis)

    make clean

Recompilar do início  

    make rebuild
    
Após compilar o programa com o comando make, um executável chamado "games" irá aparecer na pasta "bin". Basta executá-lo.

    ./games


# TP_PDS2: Board Games System

Project Description
This system implements three classic board games: Reversi, Connect 4, and Tic-Tac-Toe. It allows for player registration and management, game execution, and statistics tracking, utilizing object-oriented principles and development best practices.


## Structure
### Implemented Games:

TicTacToe  
Reversi   
Connect4.  

### Player Registration

Players are stored in the users.txt file.

Main Functions:

    instance_all: Loads all registered players.  
    sign_up_player: Allows new players to register.  
    list_players: Lists players and their statistics (victories, ties, defeats).   


### Game Execution
Available Games:

    R for Reversi.  
    C for Connect4.  
    T for Tic-Tac-Toe.   

Execution:

    execute_game function: Starts a match between two players.



## Main Menu
Commands:

    SP: Register a player.  
    RP: Remove a player.  
    LP: List players.  
    EG: Execute a game.  
    END: Exit the system.  
.

## Tools Used
Language: C++  
Version Control: Git and GitHub  
Testing: Automated unit tests using the Doctest library (https://github.com/doctest/doctest)  
Documentation: ReadMe and Doxyfile (https://doxygen.nl/)    
 
## Execution Instructions
Clone the Repository:  

    git clone https://github.com/arthurvelloso/TP_PDS2.git

Compile the Program:

    make

Remove Intermediate Files (e.g., .o files and executables):

    make clean

Rebuild the Program:
  
    make rebuild
    
After compiling the program with the make command, an executable named games will appear in the bin folder. To run it, execute:

    ./games

