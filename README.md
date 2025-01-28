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
 
Instalar Dependências:

Executar o Sistema:
 
Executar Testes:

