/*Nomes: Beatriz Lopes Rizzo, Julia Gachido Schmidt, Joao Pedro Figols Neco e Isabella Rubio Venancio
Dom_JJIB_Model.cpp*/

//estrutura das pecas
struct stPc
{
	int lado1;
	int lado2;
	char status;
};

//variaveis globais
struct stPc peca[28];
struct stPc mesa[28];

struct stPc aux; //usada para embaralhar as pecas e descobrir a maior peca
struct stPc aux2; //guarda a peca da posicao 1 da mesa que depois sera substituida
struct stPc pcEscolhida; //peca que foi escolhida pelo jogador para ser jogada
char jogador; //quem eh a vez de jogar
int aux4, jogComp;  //aux4: indice da peca q o jog escolheu; jogComp: significa q esta jogando contra o computador
int indComp, pcBot;	//indComp: indice da primeira peca compativel com mesa comprada pelo computador; pcBot: sinaliza q tem peca compativel c/ a mesa								
int qtdMesa; //qtdMesa: quantidade de pecas na mesa
int mesaE, mesaD; //extremidades da mesa
int pecaJogavel, vencedorIgual; //pecaJogavel: sinaliza que a peca eh jogavel; vencedorIgual: sinaliza q o jogador venceu com a mesa fechada
int vencedorLouvor, pecasCompradas; //vencedorLouvor: sinaliza q o jogador ganhou jogando a sua ultima peca; pecasCompradas: verifica se o bolo esta vazio
int cont1, cont2, soma_total1, soma_total2; //cont1 e cont2: verifica quantas pecas cada jogador tem; soma: verifica a soma de todos os lados das pecas
int naux; //quantidade de pecas apresentadas 

struct sJogo //struct para salvar as variaveis do jogo
{
	char Sjogador;
	int SqtdMesa;
	int SmesaD;
	int SmesaE;
	int SpecasCompradas;
	int SjogComp;
	
} sGlobal;



