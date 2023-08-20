/*Nomes: Beatriz Lopes Rizzo, Julia Gachido Schmidt, Joao Pedro Figols Neco e Isabella Rubio Venancio
Dom_JJIB_Controller.cpp*/

#include "Dom_JJIB_Controller.h"
#include "Dom_JJIB_View.cpp"

//funcao que gera pecas do domino
void geraPecas()
{
    int j, k, i;
    i = 0;

    for (j = 0; j <= 6; j++)
    {
        for (k = j; k <= 6; k++)
        {
            peca[i].lado1 = j;
            peca[i].lado2 = k;
            peca[i].status = 'b'; //as pecas, quando geradas, nao estao nem na mesa, nem com os jogadores (branco)
            i++;
        }
    }
}

//funcao que embaralha pecas do domino
void embaralhaPecas()
{
    int x;
    srand(time(NULL));

    for (int i = 0; i <= 27; i++)
    {
        x = rand()%28;
        aux = peca[i];
        peca[i] = peca[x];
        peca[x] = aux;
    }
}

//funcao que contem a parte logica do menu
void inicializaMenu()
{
    int op;

    do
    {
        op = menuGeral();

        switch (op)
        {
        	case 1: //iniciar novo jogo (2 jogadores)
			{
				jogComp = 0;
            	iniciaJogo();
            	jogar();
				break;
        	}
        	case 2: //iniciar novo jogo (contra o computador)
        	{
        		jogComp = 1;
        		iniciaJogo();
        		jogar();
            	break;
        	}
        	case 3: //retomar jogo interrompido
        	{
        	
        		if (jogComp == 1)
        		{
        			apresentaMesa();
        			jogar();
				}
				else
				{
					jogar();
				}
				break;
        	}
        	case 4: //regras do jogo
        	{
        		regrasJogo();
				break;
        	}
        	case 5: //salvar jogo
        	{
        		salvaJogo();
        		mensagem(23);
            	break;
        	}
        	case 6: //recuperar jogo salvo
        	{
        		recuperaJogo();
        		mensagem(24);
            	break;
        	}
        	case 7: //sair do programa
        	{
            	break;
        	}
        }
    }
    while(op != 7);
}

//funcao que distribui 7 pecas (embaralhadas) a cada jogador
void iniciaJogo()
{
    geraPecas();
    embaralhaPecas();
    zeraVariaveis();

    int prim_indice; //armazena o indice da maior peca para saber a quem ela pertencia (status 1 ou 2)

    aux.lado1 = -1;
    aux.lado2 = -1;

    for (int i = 0; i <= 6; i++)
    {
        peca[i].status = '1';
    }

    for (int i = 7; i <= 13; i++)
    {
        peca[i].status = '2';
    }

    for (int k = 0; k < 14; k++)
    {
        if (peca[k].lado1 == peca[k].lado2)
        {
            if (peca[k].lado1 > aux.lado1)
            {
                aux = peca[k];
                prim_indice = k;
            }
        }
    }

    if (aux.lado1 == -1)
    {
        for (int k = 0; k < 14; k++)
        {
            if (peca[k].lado1 + peca[k].lado2 > aux.lado1 + aux.lado2)
            {
                aux = peca[k];
                prim_indice = k;
            }
            else if (peca[k].lado1 + peca[k].lado2 == aux.lado1 + aux.lado2)
            {
                if (peca[k].lado1 > aux.lado1 || peca[k].lado2 > aux.lado2)
                {
                    aux = peca[k];
                    prim_indice = k;
                }
            }
        }
    }

    jogador = peca[prim_indice].status;
    peca[prim_indice].status = 'M';
    mesa[0] = aux;
    mesaE = mesa[0].lado1;
    mesaD = mesa[0].lado2;
    qtdMesa = 1;
    mensagem(1);
	
	if (jogComp == 0)
	{
		trocaTurno();
	}
	else
	{
		if (jogador == '1')
		{
			jogador = '2';
			contPecaBot();
			apresentaMesa();
			trocaTurno();
		}
		else 
		{
			jogador = '1';
			apresentaMesa();
		}
	}
    
}

//funcao que contem a parte logica do menu do jogador
void iniciaMenuJog()
{
	int op1;

    do
    {
    	if (jogComp == 1 && jogador == '2')
    	{
    		jogar();
    		trocaTurno();
		}
		else
		{
			op1 = menuJogador();

        	switch(op1)
       		{
        		case 1: //jogar
        		{
            		fcase1_Jogar();
            		break;
       	 		}
        		case 2: //comprar
        		{
        			fcase2_Comprar();
           			break;
        		}
        		case 3: //passar
        		{
					fcase3_Passar(pecasCompradas);		
            		break;
        		}
        		case 4: //sair
        		{
            		break;
        		}
        	}
		}
    }
    while(op1 != 4 &&  vencedorLouvor != 1 && vencedorIgual != 1 && vencedorLouvor != 2 && vencedorIgual != 2);
}

//permite o funcionamento do jogo
void jogar()
{
	if (jogComp == 1)
	{
		jogarBot();
	}
	else
	{
		apresentaMesa();
    	apresentaPecas();
		iniciaMenuJog();
	}
	
}

//funcao que executa comandos do case 1 (jogar) do menu do jogador
void fcase1_Jogar()
{
    int aux, aux4, aux3, count, i, k;
    count = 0;
    pecasCompradas = 0;
    struct stPc pcAux;

	aux = escolherPeca();

	if (aux == 0) //jogador desistiu da jogada
	{
		apresentaMesa();
		apresentaPecas();
		iniciaMenuJog();
	}
	else
	{
		if (naux != 0) //se o jogador ainda tiver pecas na mao
		{
			for (i = 0; i < 28; i++)
    		{
        		if (peca[i].status == jogador) //escolhe a peca que o jogador deseja colocar na mesa
        		{
            		count++;
            		pcAux = peca[i];
					aux3 = i;
        		}
        		if (count == aux)
       	 		{
           	 		pcEscolhida = pcAux;
            		aux4 = aux3;
        		}
    		}

			verificaPeca();

			if (pecaJogavel == 1) 	//se der para jogar, muda status para M
			{
				if (jogComp == 0)
				{
					peca[aux4].status = 'M';
					ganhador();	//verifica se tem algum ganhador
				}
				else
				{
					peca[aux4].status = 'M';
					contPecaBot();
					apresentaMesa();	
					ganhador();
					if (vencedorLouvor != 1 && vencedorIgual != 1 && vencedorLouvor != 2 && vencedorIgual != 2)
					{
						apresentaPecas();	
					}
				}
			}
			else
			{
				mensagem(2); //peca nao encaixa na mesa
			}
		}
	}
}

//funcao que joga a peca (apos ser verificada) na mesa
void jogadamesaDir()
{
	mesa[qtdMesa] = pcEscolhida;
	qtdMesa++;
	mesaD = pcEscolhida.lado2;
	if (jogComp == 0)
	{
		apresentaMesa();
	}
}

//funcao que inverte lado da peca
void mudaLado()
{
    int aux;
    aux = pcEscolhida.lado1;
    pcEscolhida.lado1 = pcEscolhida.lado2;
    pcEscolhida.lado2 = aux;
}

//funcao que joga a peca (apos ser verificada) na extremidade esquerda da mesa
void jogadamesaEsq()
{
    qtdMesa++;

    aux = mesa[0];

    for (int i = 0; i < qtdMesa; i++)
    {
        aux2 = mesa[i+1];
        mesa[i+1] = aux;
        aux = aux2;
    }
    mesa[0] = pcEscolhida;
	mesa[qtdMesa] = aux;
	mesaE = pcEscolhida.lado1;
	if (jogComp == 0)
	{
		apresentaMesa();
	} 
}

//funcao que verifica se a peca escolhida pelo jogador pode ser jogada
void verificaPeca()
{
	pecaJogavel = -1; //se pecaJogavel = -1, entao o status da peca se mantem (status = jogador)
	char esq;

	if ((pcEscolhida.lado1 == mesaE || pcEscolhida.lado1 == mesaD) || (pcEscolhida.lado2 == mesaE || pcEscolhida.lado2 == mesaD))
    {
    	pecaJogavel = 1;
    	if ((pcEscolhida.lado1 == mesaE || pcEscolhida.lado2 == mesaE) && (pcEscolhida.lado1 == mesaD || pcEscolhida.lado2 == mesaD))
    	{
    		esq = escolhaLadoMesa();
            if ((esq == 'E') || (esq == 'e'))
			{
				if (pcEscolhida.lado2 == mesaE) //pcEscolhida.lado1 < mesaE
            	{
                	jogadamesaEsq();
            	}
            	else 						//pcEscolhida.lado1 == mesaE
            	{
                	mudaLado();
                	jogadamesaEsq();
            	}
			}
			else
			{
				if (pcEscolhida.lado2 == mesaD) //pcEscolhida.lado1 < mesaE
            	{
            		mudaLado();
            		jogadamesaDir();
        		}
        		else						  //pcEscolhida.lado1 == mesaD
            	{
            		jogadamesaDir();
            	}
			}
		}
    	else //quando so tem uma unica possibilidade de jogar
    	{
        	if (pcEscolhida.lado2 == mesaD)
			{
        		mudaLado();
        		jogadamesaDir();
			}
			else if (pcEscolhida.lado2 == mesaE)
			{
				jogadamesaEsq();
			}
			else if (pcEscolhida.lado1 == mesaE)
			{
				mudaLado();
				jogadamesaEsq();
			}
			else //lado1 == mesaD
			{
        		jogadamesaDir();
			}
		}
	}
}

//funcao que troca os turnos da jogada
void trocaTurno()
{
	if (jogador == '1')
    {
        jogador = '2';
    }
    else //jogador = '2' 
    {
        jogador = '1';
    }
}

//funcao que verifica se ainda ha pecas no bolo
int verificaBolo()
{
	int cont = 0;
	for (int i = 0; i < 28; i++)
	{
		if (peca[i].status != 'b')
		{
			cont++;
		}
		if (cont == 28)
		{
			pecasCompradas = 2; //nao ha mais pecas para comprar
		}
	}
	return pecasCompradas;
}

//funcao que as compras de pecas
void compraPecas()
{
	int cont = 0;
	for (int i = 0; i < 28 ; i++)
	{
		if (peca[i].status == 'b' && cont == 0) //ainda ha peca para comprar no bolo
		{
			peca[i].status = jogador;
			cont++;							//permite que o jogador compre uma peca por vez
			apresentaMesa();
			apresentaPecas();
		}
	}
}

//funcao que permite a compra de pecas
void fcase2_Comprar()
{
	verificaBolo();
	if (pecasCompradas == 2) //bolo esta vazio
	{
		if (naux == 0) //mao do jogador esta vazia
		{
			mensagem(3);
			apresentaMesa();
			ganhador();
		}
		else
		{
			mensagem(3);
			apresentaMesa();
			apresentaPecas();
		}
	}
	else
	{
		compraPecas();
	}
}

//funcao que permite ao jogador passar a sua vez se as pecas a serem compradas se esgotaram
void fcase3_Passar(int pecasCompradas)
{
	int contPeca = 0;

	if (verificaBolo() == 2)	//o bolo esta vazio
	{
		for (int i = 0; i < 28; i++)
		{
			if (peca[i].status == jogador)
			{
				if ((peca[i].lado1 == mesaE || peca[i].lado1 == mesaD) || (peca[i].lado2 == mesaE || peca[i].lado2 == mesaD))
				{
					contPeca++;
				}
			}
		}

		if (contPeca == 0)	//Pessoa nn tem peca compativel com as extremidades, entao pode passar a vez
		{
			if(jogComp == 1 && jogador == '1')
			{
				
				apresentaMesa();
				ganhador();
				if (vencedorLouvor != 1 && vencedorIgual != 1 && vencedorLouvor != 2 && vencedorIgual != 2)
				{
					contPecaBot();
					apresentaPecas();
				}	
			}
			else
			{
				apresentaMesa();
				ganhador();
			}
		}
		else
		{
			mensagem(9);		//A pessoa ainda tem a peca para jogar
			apresentaMesa();
			apresentaPecas();
		}
	}
	else
	{
		mensagem(4);
		apresentaMesa();
		apresentaPecas();
	}
}

//funcao de teste para ver se ganhou com louvor
int ganhaJogoLouvor()
{
	int count1 = 0;
	int count2 = 0;
	vencedorLouvor = 0;

	//pecas do vetor na mesa ou comprar
	for (int i = 0; i < 28; i++)
	{
		if (peca[i].status == '1')
		{
			count1++;
		}
		if (peca[i].status == '2')
		{
			count2++;
		}
	}

	if (count1 == 0 && count2 != 0)
	{
		vencedorLouvor = 1;
	}
	else if (count2 == 0 && count1 != 0)
	{
		vencedorLouvor = 2;
	}

	return vencedorLouvor;
}

//funcao de teste para ver se ganhou caso nao de mais para jogar
int ganhaJogo2()
{
	int soma1 = 0;
	int soma2 = 0;
	cont1 = 0;
	cont2 = 0;
	vencedorIgual = 0;

	if (verificaMao() == 2) //mesa fechou
	{
		for (int i = 0; i < 28; i++)
			{
				if (peca[i].status == '1')
				{
					cont1++;
					soma1 = peca[i].lado1 + peca[i].lado2;
					soma_total1 = soma1 + soma_total1;
				}
				if (peca[i].status == '2')
				{
					cont2++;
					soma2 = peca[i].lado1 + peca[i].lado2;
					soma_total2 = soma2 + soma_total2;
				}
			}

		if ((cont1 == cont2) || (cont1 > cont2) || (cont1 < cont2))
		{
			vencedorIgual = 1;
		}
	}
	return vencedorIgual;
}

//funcao que verifica se ha um ganhador no jogo
void ganhador()
{
	if (verificaBolo() == 2) //o bolo esta vazia
	{
		ganhaJogoLouvor();

		if ((vencedorLouvor == 1) || (vencedorLouvor == 2))
		{
			if (vencedorLouvor == 1)
			{
				mensagem(5);
			}
			else
			{
				mensagem(6);
			}
		}
		else if (ganhaJogo2() == 1)
		{
			if ((cont1 == cont2))
			{
				if (soma_total1 > soma_total2)
				{
					mensagem(8);
				}
				else
				{
					mensagem(7);
				}
			}
			else if (cont1 > cont2)
			{
				mensagem(8);
			}
			else  //cont1 < cont2
			{
				mensagem(7);
			}
		}
		else //nao tem nenhum vencedor, o jogo continua
		{
			if (jogComp == 0) 
			{
			trocaTurno();
			apresentaPecas();
			}
			else
			{
				if (jogador == '2')
				{
					contPecaBot();
					trocaTurno();
					apresentaPecas();
				}
			}
		}
	}
	else 	//ainda da para comprar pecas
	{
		if (jogComp == 0)
		{
			trocaTurno();
			apresentaPecas();
		}
		else
		{
			if (jogador == '2')
			{
				contPecaBot();
				trocaTurno();
				apresentaPecas();
			}
		}
		
	}
}

//funcao a quantidade de pecas com o msm numero na mesa, ate somar sete
int verificaMao()
{
	int cont = 0;

	if (verificaBolo() == 2) //nao tem mais pecas para comprar
	{
		for (int i = 0; i < 28; i++)
		{
			if ((peca[i].status == '1') || (peca[i].status == '2'))
			{
				if ((peca[i].lado1 == mesaE || peca[i].lado1 == mesaD) || (peca[i].lado2 == mesaE || peca[i].lado2 == mesaD))
				{
					cont++;
				}
			}
		}

		if (cont != 0) //quer dizer que ainda tem peca para jogar e a mesa nao fechou
		{
			return 1;
		}
		else
		{
			return 2;  //a mesa fechou e tem que ver quem eh o ganhador
		}
	}
}

//funcao que zera acumuladores para iniciar um novo jogo
void zeraVariaveis()
{
	vencedorLouvor = 0;
	vencedorIgual = 0;
	pecasCompradas = 0;
	cont1 = 0;
	cont2 = 0;
	soma_total1 = 0;
	soma_total2 = 0;
}

//funcao que salva o jogo 
void salvaJogo()
{
	FILE *fp;

	if ((fp = fopen("dominoPeca", "w")) == NULL)
	{
		mensagem(11);
		exit(0);
	}

	for (int i = 0; i < 28; i++)
	{
		if(fwrite(&peca[i], sizeof(struct stPc), 1, fp) != 1)
		{
			mensagem(13);
			break;
		}
	}

	fclose(fp);

	sGlobal.Sjogador = jogador;
	sGlobal.SqtdMesa = qtdMesa;
	sGlobal.SmesaD = mesaD;
	sGlobal.SmesaE = mesaE;
	sGlobal.SpecasCompradas = pecasCompradas;
	sGlobal.SjogComp = jogComp;

	if ((fp = fopen("dominoVariaveis", "w")) == NULL)
	{
		mensagem(15);
		exit(0);
	}

	if(fwrite(&sGlobal, sizeof(struct sJogo), 1, fp) != 1)
	{
		mensagem(16);
		exit(0);
	}

	fclose(fp);

	if ((fp = fopen("dominoMesa", "w")) == NULL)
	{
		mensagem(12);
		exit(0);
	}

	for (int i = 0; i < qtdMesa; i++)
	{
		if(fwrite(&mesa[i], sizeof(struct stPc), 1, fp) != 1)
		{
			mensagem(14);
			break;
		}
	}

	fclose(fp);

}

//funcao que recupera/le o jogo ja iniciado, para poder continua-lo
void recuperaJogo()
{
    FILE *fp;

	if ((fp = fopen("dominoPeca", "r")) == NULL)
	{
		mensagem(17);
		exit(0);
	}

	for (int i = 0; i < 28; i++)
	{
		if(fread(&peca[i], sizeof(struct stPc), 1, fp) != 1)
		{
			mensagem(20);
			break;
		}
	}

	fclose(fp);

	if ((fp = fopen("dominoVariaveis", "r")) == NULL)
	{
		mensagem(19);
		exit(0);
	}

	if(fread(&sGlobal, sizeof(struct sJogo), 1, fp) != 1)
	{
		mensagem(22);
		exit(0);
	}

	jogador = sGlobal.Sjogador;
	qtdMesa = sGlobal.SqtdMesa;
	mesaD = sGlobal.SmesaD;
	mesaE = sGlobal.SmesaE;
	pecasCompradas = sGlobal.SpecasCompradas;
	jogComp = sGlobal.SjogComp;

	fclose(fp);

	if ((fp = fopen("dominoMesa", "r")) == NULL)
	{
		mensagem(18);
		exit(0);
	}

	for (int i = 0; i < qtdMesa; i++)
	{
		if(fread(&mesa[i], sizeof(struct stPc), 1, fp) != 1)
		{
			mensagem(21);
			break;
		}
	}

	fclose(fp);
}

//funcao que faz com que o computador jogue
void contPecaBot()
{
	int qtdComp = 0;
	int	pcBot = 0;
	
	//verifica se o bot tem pecas compativeis com a mesa
	for (int i = 0; i < 28; i++)
	{
		if (peca[i].status == '2')
		{
			//ve se algum dos lados e compativel com a mesa
			if (((peca[i].lado1 == mesaE || peca[i].lado1 == mesaD) || (peca[i].lado2 == mesaE || peca[i].lado2 == mesaD) && (qtdComp == 0)))
			{
				qtdComp++;
				pcBot = 1;
				
				if (qtdComp == 1) // entra uma unica vez
				{
					indComp = i;
				}
			}	
		}
	}
	
	if (pcBot == 1)   //tem peca compativel c/ a mesa
	{
		pcEscolhida = peca[indComp];
		verificaBot();
		peca[indComp].status = 'M';
	}
	else //precisa comprar
	{
		compraBot();
	}
}

//verifica as pecas do computador para joga-las
int verificaBot()
{	 	
    if ((pcEscolhida.lado1 == mesaE || pcEscolhida.lado2 == mesaE) && (pcEscolhida.lado1 == mesaD || pcEscolhida.lado2 == mesaD))
    {
    	if (pcEscolhida.lado1 == mesaD)
    	{
    		jogadamesaDir();
		}
		else
		{
			mudaLado();
			jogadamesaDir();
		}
    }	
	else
    {
	    if (pcEscolhida.lado2 == mesaD)
		{
        	mudaLado();
        	jogadamesaDir();
		}
		else if (pcEscolhida.lado2 == mesaE)
		{
			jogadamesaEsq();
		}
		else if (pcEscolhida.lado1 == mesaE)
		{
			mudaLado();
			jogadamesaEsq();
		}
		else //lado1 == mesaD
		{
        	jogadamesaDir();
		}
	}
	
	return pcBot;
}

//faz compra automatica quando nn ha peca compativel na mesa
void compraBot()
{	
	int cont = 0;
	int i = 0;
	int indPc, pcBot;
	int aux = 0;
	
	verificaBolo();
	
	do
	{
		if (peca[i].status == 'b' && i < 28)
		{	
			peca[i].status = '2';
			if (peca[i].lado1 == mesaE || peca[i].lado1 == mesaD || peca[i].lado2 == mesaE || peca[i].lado2 == mesaD)
			{
				aux = 3;
				pcEscolhida = peca[i];
				verificaBot();
				peca[i].status = 'M';
			}
			else
			{
				i++;
			}
		}
		else
		{
			i++;
		}
	}
	while (aux != 3 && i < 28);		
}

//funcao que faz com que jogue contra o bot
void jogarBot()
{
	if (jogador == '1')
	{
    	apresentaPecas();
		iniciaMenuJog();
	}
	else
	{
		if (vencedorLouvor != 1 && vencedorIgual != 1 && vencedorLouvor != 2 && vencedorIgual != 2)
		{
			contPecaBot();
			trocaTurno();
		}
	}
}


