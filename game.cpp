#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <speechapi_cxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

auto autenticacao = SpeechConfig::FromSubscription("9285a712574c4660a8fe16f34485f3be", "southcentralus"); // DECLARAÇÃO DA AUTENTICAÇÃO DO RECURSO
auto requisicao_textofala = SpeechSynthesizer::FromConfig(autenticacao); // DECLARAÇÃO DO OBJETO DE REQUISIÇÃO DE TEXTO EM FALA DO RECURSO
auto audio_config = AudioConfig::FromDefaultMicrophoneInput(); // DECLARAÇÃO DA ENTRADA DO MICROFONE
auto requisicao_falatexto = SpeechRecognizer::FromConfig(autenticacao, audio_config); // DECLARAÇÃO DO OBJETO DE REQUISIÇÃO DE FALA EM TEXTO DO RECURSO

// PROCEDIMENTO QUE REQUISITA DA API A TRANSFORMAÇÃO DE UM TEXTO EM FALA
void texto_em_fala(string Texto)
{
    cout << Texto + "\n";
    requisicao_textofala->SpeakTextAsync(Texto).get(); // REQUISIÇÃO DA SINTETIZAÇÃO DE TEXTO EM FALA
}
// FUNÇÃO QUE REQUISITA DA API O RECONHECIMENTO DE UMA FALA E A TRANSFORMAÇÃO DESSA FALA EM UM TEXTO
string fala_em_texto() {
    auto resultado = requisicao_falatexto->RecognizeOnceAsync().get(); // REQUISIÇÃO DO RECONHEIMENTO DE FALA EM TEXTO
    cout << resultado->Text + "\n";
    return resultado->Text; //CONVERSÃO DO RESULTADO DO RECONHECIMENTO EM TEXTO
}


void tabuleiro(char casa2[9])
{
    system("cls"); //SEMRA LIMPADO A TELA QUANDO USUARIO DESEJAR JOGAR NOVAMENTE
    cout << "\n \t JOGO DA VELHA \n";
    cout << "\t " << casa2[0] << " | " << casa2[1] << " | " << casa2[2] << "\n"; //IMPRESSAO DAS CASAS 0,1,2
    cout << "\t ------------\n";
    cout << "\t " << casa2[3] << " | " << casa2[4] << " | " << casa2[5] << "\n"; // IMPRESSAO DAS CASAS 3,4,5
    cout << "\t ------------\n";
    cout << "\t " << casa2[6] << " | " << casa2[7] << " | " << casa2[8] << "\n"; // IMPRESSAO DAS CASAS 6,7,8

}

int main()
{

    string key = "9285a712574c4660a8fe16f34485f3be", region = "southcentralus";


    autenticacao = SpeechConfig::FromSubscription(key, region);         //  AUTENTICAÇÃO DO RECURSO COM A CHAVE E REGIÃO INFORMADOS PELO USUÁRIO 
    autenticacao->SetSpeechRecognitionLanguage("pt-BR");                //  CONFIGURAÇÃO DA AUTENTICAÇÃO PARA O RECONHECIMENTO DE FALA EM PORTUGUÊS 
    autenticacao->SetSpeechSynthesisLanguage("pt-BR");                  //  CONFIGURAÇÃO DA AUTENTICAÇÃO PARA A SINTETIZAÇÃO DE FALA EM PORTUGUÊS 
    autenticacao->SetSpeechSynthesisVoiceName("pt-BR-HeloisaRUS"); //pt-BR-Daniel  // CONFIGURAÇÃO DA AUTENTICAÇÃO COM UMA VOZ ESPECÍFICA 
    requisicao_textofala = SpeechSynthesizer::FromConfig(autenticacao); //  REDEFINIÇÃO DO OBJETO REQUISICAO_TEXTOFALA COM AS NOVAS CONFIGURAÇÕES 
    requisicao_falatexto = SpeechRecognizer::FromConfig(autenticacao, audio_config); //  REDEFINIÇÃO DO OBJETO REQUISICAO_FALATEXTO COM AS NOVAS CONFIGURAÇÕES


    try {
        char casas[9] = { '1','2','3','4','5','6','7','8','9' };//VARIAVEL TIPO CHAR QUE ARMAZENA AS CASAS A SEREM PREENCHIDAS
        char res; // VARIAVEL DO TIPO RESPOSTA
        int conta_jogos, vez = 0; // DECLARAÇÃO DA VARIAVEL DE CONTAR OS JOGOS E A VEZ DO JOGADOR OU MAQUINA
        int jogada = 1; //DECLARAÇÃO DA VARIAVEL RELACIONADA AS JOGADAS A SEREM FEITAS 
        texto_em_fala(" \n \t JOGO DA VELHA \n"); // COMANDO DE FALA "JOGO DA VELHA"

        do {

            conta_jogos = 1;
            for (int i = 0; i <= 8; i++) { // SERA CONTADO AS CASAS DO TABULEIRO E DESIGNADO UM VALOR A CADA TENDO INICIO COM NADA PREENCHIDO
                casas[i] = ' '; // CADA POSIÇAO DO TABULEIRO SERA PREENCHIDO POR ESPAÇO VAZIO
            }

            do {

                tabuleiro(casas);

                if (vez % 2 == 0) {
                    texto_em_fala("\nJogador X: \n"); //SERA ARMAZENADO A JOGADA DO JOGADOR 1
                    texto_em_fala("\n Fale a casa para marcar[1 a 9]: ");  // SERA PEDIDO AO USUARIO FALAR UMA CASA DE 1 A 9
                    string jogadax = fala_em_texto(); //STRING JOGADAX ARMAZENARA O NUMERO DITO DE 1 A 9 PELO USUARIO
                    if (jogadax == "Um.") { //CASO USUARIO DIGA UM JOGADAX TER UM NOVO VALOR
                        vez = 1; //VEZ IRA ENTRAR COM O VALOR 1
                        casas[0] = 'X'; //SERA ADICIONADO UM X NA CASA DE POSIÇÃO 0


                    }
                    else if (jogadax != "Um.") { //CASO O USUARIO NAO DIGA UM SERA EXECUTADO ABAIXO

                        jogada = stoi(jogadax); //SERA ARMAZENADO O VALOR STRING DITO PELO USUARIO E CONVERTIDO EM NUMERO INTEIRO PARA QUE SEJA POSICIONADO NA CASA DO TABULEIRO
                    }
                }
                else {
                    if (casas[0] == 'O' && casas[1] == '0' && casas[2] == ' ') { jogada = 3; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[3] == 'O' && casas[4] == '0' && casas[5] == ' ') { jogada = 6; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[6] == 'O' && casas[7] == '0' && casas[8] == ' ') { jogada = 9; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[0] == 'O' && casas[1] == ' ' && casas[2] == 'O') { jogada = 2; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[3] == 'O' && casas[4] == ' ' && casas[5] == 'O') { jogada = 5; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[6] == 'O' && casas[7] == ' ' && casas[8] == 'O') { jogada = 8; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[0] == ' ' && casas[1] == 'O' && casas[2] == 'O') { jogada = 1; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[3] == ' ' && casas[4] == 'O' && casas[5] == 'O') { jogada = 4; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[6] == ' ' && casas[7] == 'O' && casas[8] == 'O') { jogada = 7; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[0] == 'O' && casas[3] == 'O' && casas[6] == ' ') { jogada = 7; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[1] == 'O' && casas[4] == 'O' && casas[7] == ' ') { jogada = 8; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[2] == 'O' && casas[5] == 'O' && casas[8] == ' ') { jogada = 9; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[0] == 'O' && casas[3] == ' ' && casas[6] == 'O') { jogada = 4; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[1] == 'O' && casas[4] == ' ' && casas[7] == 'O') { jogada = 5; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[2] == 'O' && casas[5] == ' ' && casas[8] == 'O') { jogada = 6; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[0] == ' ' && casas[3] == 'O' && casas[6] == 'O') { jogada = 1; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[1] == ' ' && casas[4] == 'O' && casas[7] == 'O') { jogada = 2; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[2] == ' ' && casas[5] == 'O' && casas[8] == 'O') { jogada = 3; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[0] == 'O' && casas[4] == 'O' && casas[8] == ' ') { jogada = 9; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[0] == 'O' && casas[4] == ' ' && casas[8] == 'O') { jogada = 5; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[0] == ' ' && casas[4] == 'O' && casas[8] == 'O') { jogada = 1; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[2] == 'O' && casas[4] == 'O' && casas[6] == ' ') { jogada = 7; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[2] == 'O' && casas[4] == ' ' && casas[6] == 'O') { jogada = 5; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA
                    else if (casas[2] == ' ' && casas[4] == 'O' && casas[6] == 'O') { jogada = 3; } //JOGADAS DA MAQUINA PARA OBTER A VITORIA

                    if (casas[0] == 'X' && casas[1] == 'X' && casas[2] == ' ') { jogada = 3; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[3] == 'X' && casas[4] == 'X' && casas[5] == ' ') { jogada = 6; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[6] == 'X' && casas[7] == 'X' && casas[8] == ' ') { jogada = 9; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[0] == 'X' && casas[1] == ' ' && casas[2] == 'X') { jogada = 2; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[3] == 'X' && casas[4] == ' ' && casas[5] == 'X') { jogada = 5; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[6] == 'X' && casas[7] == ' ' && casas[8] == 'X') { jogada = 8; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[0] == ' ' && casas[1] == 'X' && casas[2] == 'X') { jogada = 1; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[3] == ' ' && casas[4] == 'X' && casas[5] == 'X') { jogada = 4; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[6] == ' ' && casas[7] == 'X' && casas[8] == 'X') { jogada = 7; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[0] == 'X' && casas[3] == 'X' && casas[6] == ' ') { jogada = 7; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[1] == 'X' && casas[4] == 'X' && casas[7] == ' ') { jogada = 8; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[2] == 'X' && casas[5] == 'X' && casas[8] == ' ') { jogada = 9; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[0] == 'X' && casas[3] == ' ' && casas[6] == 'X') { jogada = 4; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[1] == 'X' && casas[4] == ' ' && casas[7] == 'X') { jogada = 5; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[2] == 'X' && casas[5] == ' ' && casas[8] == 'X') { jogada = 6; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[0] == ' ' && casas[3] == 'X' && casas[6] == 'X') { jogada = 1; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[1] == ' ' && casas[4] == 'X' && casas[7] == 'X') { jogada = 2; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[2] == ' ' && casas[5] == 'X' && casas[8] == 'X') { jogada = 3; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[0] == 'X' && casas[4] == 'X' && casas[8] == ' ') { jogada = 9; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[0] == 'X' && casas[4] == ' ' && casas[8] == 'X') { jogada = 5; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[0] == ' ' && casas[4] == 'X' && casas[8] == 'X') { jogada = 1; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[2] == 'X' && casas[4] == 'X' && casas[6] == ' ') { jogada = 7; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[2] == 'X' && casas[4] == ' ' && casas[6] == 'X') { jogada = 5; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else if (casas[2] == ' ' && casas[4] == 'X' && casas[6] == 'X') { jogada = 3; } //JOGADAS DA MAQUINA PARA QUE O JOGADOR NÃO OBTENHA VITORIA
                    else {
                        do {
                            srand((unsigned)time(NULL)); //MAQUINA TERA JOGOS ALEATORIOS SEGUINDO AS CONDIÇÕES IMPOSTAS A ELA
                            jogada = 1 + rand() % 9; //CRIANDO NUMEROS ALEATORIOS DE 1 A 9 PARA SEREM A JOGADA DA MAQUINA
                        } while (casas[jogada - 1] != ' ');
                    }
                }

                if (jogada < 1 || jogada > 9) { // CONTROLE DE JOGADAS INVALIDAS MENORES QUE 1 E MAIORES QUE 9
                    jogada = 0; // JOGADA VALERA 0 SENDO ASSIM NAO SERA MARCADA EM NENHUMA PARTE DO TABULEIRO
                }
                else if (casas[jogada - 1] != ' ') { // VERIFICAR SE A CASA DESEJADA ESTA OCUPADA OU NAO
                    jogada = 0; //SE ESTIVER JOGADA TERA VALOR ZERO
                }
                else {
                    if (vez % 2 == 0) { // SERA VERIFICADO SE A VARIAEVL VEZ É UM NUMERO PAR
                        casas[jogada - 1] = 'X'; //CASO SEJA UM NUMERO PAR SERA ADICIONADO X
                    }
                    else { // CASO SEJA UM NUMERO IMPAR
                        casas[jogada - 1] = 'O';// SERA ADICIONADO O
                    }
                    conta_jogos++; //CONTADOR PARA AS JOGADAS
                    vez++; // CONTA A VEZ DE 
                }
                if (casas[0] == 'X' && casas[1] == 'X' && casas[2] == 'X') { conta_jogos = 11; } //JOGADAS DO JOGADOR X
                if (casas[3] == 'X' && casas[4] == 'X' && casas[5] == 'X') { conta_jogos = 11; } //JOGADAS DO JOGADOR X
                if (casas[6] == 'X' && casas[7] == 'X' && casas[8] == 'X') { conta_jogos = 11; } //JOGADAS DO JOGADOR X
                if (casas[0] == 'X' && casas[3] == 'X' && casas[6] == 'X') { conta_jogos = 11; } //JOGADAS DO JOGADOR X
                if (casas[1] == 'X' && casas[4] == 'X' && casas[7] == 'X') { conta_jogos = 11; } //JOGADAS DO JOGADOR X
                if (casas[2] == 'X' && casas[5] == 'X' && casas[8] == 'X') { conta_jogos = 11; } //JOGADAS DO JOGADOR X
                if (casas[0] == 'X' && casas[4] == 'X' && casas[8] == 'X') { conta_jogos = 11; } //JOGADAS DO JOGADOR X
                if (casas[2] == 'X' && casas[4] == 'X' && casas[6] == 'X') { conta_jogos = 11; } //JOGADAS DO JOGADOR X

                if (casas[0] == 'O' && casas[1] == 'O' && casas[2] == 'O') { conta_jogos = 12; } //JOGADAS DO JOGADOR O
                if (casas[3] == 'O' && casas[4] == 'O' && casas[5] == 'O') { conta_jogos = 12; } //JOGADAS DO JOGADOR O
                if (casas[6] == 'O' && casas[7] == 'O' && casas[8] == 'O') { conta_jogos = 12; } //JOGADAS DO JOGADOR O
                if (casas[0] == 'O' && casas[3] == 'O' && casas[6] == 'O') { conta_jogos = 12; } //JOGADAS DO JOGADOR O
                if (casas[1] == 'O' && casas[4] == 'O' && casas[7] == 'O') { conta_jogos = 12; } //JOGADAS DO JOGADOR O
                if (casas[2] == 'O' && casas[5] == 'O' && casas[8] == 'O') { conta_jogos = 12; } //JOGADAS DO JOGADOR O
                if (casas[0] == 'O' && casas[4] == 'O' && casas[8] == 'O') { conta_jogos = 12; } //JOGADAS DO JOGADOR O
                if (casas[2] == 'O' && casas[4] == 'O' && casas[6] == 'O') { conta_jogos = 12; } //JOGADAS DO JOGADOR O


            } while (conta_jogos <= 9); // SERA CONTADO ATE 9 JOGADAS
            tabuleiro(casas);
            if (conta_jogos == 10) {
                texto_em_fala("\nJOGO EMPATADO\n"); // AMBOS OS DOIS EMPATARAM
            }
            else if (conta_jogos == 11) {
                texto_em_fala("\nVENCEDOR X\n"); // VENCEDOR SERA JOGADOR X
            }
            else {
                texto_em_fala("\nVENCEDOR O\n"); // VENCEDOR SERA JOGADOR O
            }
            texto_em_fala("Deseja jogar novamente?[S/N]: "); // OPÇÃO CASO JOGADOR DESEJE JOGAR NOVAMENTE
            cin >> res;
        } while (res == 'S'); //CASO DIGITE S O PROGRAMA LIMPA O JOGO ANTERIOR E COMEÇA NO ZERO
        if (res == 'N') { // CASO DIGITE N O JOGO SERA FECHADO RETORNANDO A MENSSAGEM ABAIXO
            texto_em_fala("\n\tOBRIGADO POR USAR O PROGRAMA\n");
        }
        return 0;
    }
    catch (exception e)
    {
        cout << e.what();
    }
}
