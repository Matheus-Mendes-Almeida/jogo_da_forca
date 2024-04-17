#define TAMA_STR 100

void adicionarPalavra();
void abertura();
void escolherPalavraChave(char palavraChave[]);
void gerarPalvraOculta(char palavraChave[], char palavraChaveOculta[]);
char chutarLetra();
void revelarLetraOculta(char palavraChave[], char palavraChaveOculta[], char letra);
bool analizar(char letra, char palavraChave[], char palavraChaveOculta[]);
bool verificarVitoria(char palavraChaveOculta[]);
void finalizar(int analize, char palavraChave[]);
