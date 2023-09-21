#include <stdio.h>
#include <string.h>

int main()
{
    // Declaração de variáveis para armazenar os valores individuais dos dígitos
    long long int numero;
    
    int vet[16], i, qtdN;
	int primeiraSoma, segundaSoma, somaTotal;
	int dobro, n;

    // Solicita um número longo até que seja inserido um valor maior ou igual a 1
    do {
    	printf("Numero: ");
    	scanf("%lld", &numero);
    } while (numero < 1);
    
    i = 0;
    qtdN = 0;
    
    /*trocando por um array, para armazenar cada uma dos numeros eh so fazer um loop
    no qual, conta tambem os numeros de elementos
    */
    while(numero != 0){
    	vet[i] = numero % 10;	//amazena no array cada numero, desde o fim
    	numero = numero/10;		//diminui o numero de 10 em 10
    	qtdN++;
    	i++;					//indice do array
	}
	
	primeiraSoma = 0;
	segundaSoma = 0;
	dobro = 0;
	n = 0;
	
	/*agora para fazer a conta necessaria eh so fazer um for que percorre todo array
	  e a partir disso podemos fazer as contas de primeiraSoma e segundaSoma.
	*/
	for(int i = 0; i < qtdN; i++){
		
		if(i % 2 != 0){				//verica se o indice eh a parir do antepenultimo, sempre pulando um
			dobro = vet[i] * 2;	
				
			if(dobro/10 != 0){		//verifica se o dobro do numero eh um decimal
				n = dobro/10;
				primeiraSoma = n + primeiraSoma;
				
				n = dobro%10;
				primeiraSoma = n + primeiraSoma;
				
			}else{
				primeiraSoma = (vet[i] * 2) + primeiraSoma;
			}
		}else{
			segundaSoma = vet[i] + segundaSoma;
		}
		
	}
	
	somaTotal = primeiraSoma + segundaSoma;
	
	if(somaTotal%10 != 0){
		printf("\n\n INVALIDO \n\n");
	}else{
		/*como apresentamos a quantidade de elementos, em vez de usarmos como foi feito anteriormente eh so pergamos os 2 ultimos itens do array
		a partir dessa quantidade, nao precisando mudar dependendo do tamanho.
		*/
		if((qtdN == 16) && (vet[qtdN-1] == 5 && (vet[qtdN-2] >= 1 && vet[qtdN-2] <= 5))){		
			printf("MASTERCARD\n");
		}else if((qtdN == 15) && (vet[qtdN-1] == 3 && (vet[qtdN-2] == 4 || vet[qtdN-2] == 7))){
			printf("AMERICAN EXPRESS\n");
		}else if((qtdN == 13 || qtdN == 16) && (vet[qtdN-1] == 4)){
			printf("VISA\n");
		}
	}
	
    return 0;
}
