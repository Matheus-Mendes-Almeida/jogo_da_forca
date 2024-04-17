#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "JogoDaForca.h"

void adicionarPalavra(){
    char addPalavra;

    printf("\n\nDeseja adicionar uma frase nova(s/n)?  ");
    scanf("%c", &addPalavra);

    if(addPalavra == 's' || addPalavra == 'S'){

        int quantidadeDeFrases;
        char frase[TAMA_STR];

        printf("Qual a frase sera adicionada?   ");
        getchar();
        gets(frase);

        FILE *arquivo = fopen("Frases.txt", "r+");

        if(arquivo == NULL){
            printf("Erro, nao foi possivel carregar o arquivo !!!!\n\n");

            exit(1);
        }

        fscanf(arquivo, "%d", &quantidadeDeFrases);
        quantidadeDeFrases ++;

        rewind(arquivo);
        fprintf(arquivo, "%d", quantidadeDeFrases);

        fseek(arquivo, 0, SEEK_END);
        fprintf(arquivo, "\n%s", frase);

        fclose(arquivo);
    }else{
        printf("\nEntendido.");
    }
}

void abertura(){
    printf("\t\t\t\t\t*************************\n");
    printf("\t\t\t\t\t***** Jogo Da Forca *****\n");
    printf("\t\t\t\t\t*************************\n\n");
}

void escolherPalavraChave(char palavraChave[]){
    int quantidadeDeFrases;
    int fraseAleatoria;
    FILE *file;                                 // Declarendo a variável 'file' como uma variável do tipo FILE e destacando para o sistema que em 'file' está sendo armazenado um ponteiro '*'

    file = fopen("Frases.txt", "r");            // Procurando no local de armazenamento do programa se existe um aquivo com nome "Frases.txt", se existir vai gerar um ponteiro para o primeiro caracter do arquivo e somente poderemos ler o conteudo do arquivo

    if(file == NULL){
        printf("Erro, nao foi possivel carregar o arquivo !!!!\n\n");

        exit(1);            // O exit(1);  ou qualquer valor maior que 0 fará que o programa seja finalizado;
    }

    fscanf(file, "%d", &quantidadeDeFrases);    // Foi definido que na primeira linha do arquivo ficaria um valor inteiro que indicaria quantas linha há no arquivo txt

    srand(time(NULL));
    fraseAleatoria = (rand() % quantidadeDeFrases + 1);

    for(int i = 0; i <= fraseAleatoria; i ++)
        fgets(palavraChave, TAMA_STR, file);

    palavraChave[strcspn(palavraChave, "\n")] = '\0';

    fclose(file);                               // Fechado o arquivo aberto pelo o 'fopen' caso ele ficasse aberto, poderia gerar erros caso outra função o tentasse abrir
}

void gerarPalvraOculta(char palavraChave[], char palavraChaveOculta[]){
    for(int i = 0; i < strlen(palavraChave); i ++){
        if(palavraChave[i] == ' ')
            palavraChaveOculta [i] = ' ';
        else
            palavraChaveOculta[i] = '-';
    }
    palavraChaveOculta[strlen(palavraChave)] = '\0';
}

char chutarLetra(){
    char letra;

    printf("Digite uma letra: ");

    scanf("%c", &letra);

    return letra;
}

void revelarLetraOculta(char palavraChave[], char palavraChaveOculta[], char letra){
    for(int i = 0; i < strlen(palavraChave); i ++){
        if(palavraChave[i] == letra){
            palavraChaveOculta[i] = letra;
        }
    }
}

bool analizar(char letra, char palavraChave[], char palavraChaveOculta[]){
    bool verificarChute = false;

    for(int i = 0; i <= strlen(palavraChave); i ++){
        if(palavraChave[i] == letra){
            verificarChute = true;
            break;
        }
    }

    if(verificarChute)
        revelarLetraOculta(palavraChave, palavraChaveOculta, letra);

    return verificarChute;
}

bool verificarVitoria(char palavraChaveOculta[]){
    bool finalizar = true;

    for(int i = 0; i <= strlen(palavraChaveOculta); i ++){
        if(palavraChaveOculta[i] == '-'){
            finalizar = false;
            break;
        }
    }

    return finalizar;
}

void finalizar(int analize, char palavraChave[]){
    if(analize == 0){
        printf("\n\n\t\t\t\t\t----------------------------------------------------------------");
        printf("\n\t\t\t\t\t---- Voce nao foi bom o suficiente, a palavra correta era:  ----");
        printf("\n\t\t\t\t\t----------------------------------------------------------------");
        printf("\n\t\t\t\t\t--> %s", palavraChave);
    }else{
        printf("\n\n\t\t\t\t\t-----------------------------------------------------");
        printf("\n\t\t\t\t\t---- Parabens!!! ganhou com %d chances sobrando. ----", analize);
        printf("\n\t\t\t\t\t-----------------------------------------------------");
    }
}

void main(){

    char palavraChave[TAMA_STR] , palavraChaveOculta[TAMA_STR];
    int chances = 5;
    bool chuteCorreto;

    abertura();

    escolherPalavraChave(palavraChave);

    gerarPalvraOculta(palavraChave, palavraChaveOculta);

    while(chances != 0){
        printf("\t\t\t\"%s\"\n", palavraChaveOculta);

        chuteCorreto = analizar(chutarLetra(), palavraChave, palavraChaveOculta);
        getchar();

        if(chuteCorreto){
            if(verificarVitoria(palavraChaveOculta))
                break;
        }else{
            chances --;

            printf("Errado. Faltam %d chances\n", chances);
        }
    }

    finalizar(chances, palavraChave);

    adicionarPalavra();
}
