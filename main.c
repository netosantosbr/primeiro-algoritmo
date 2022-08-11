#include <pthread.h>
#include <stdio.h>

pthread_t p1, p2;

int agoraEh = 1; //Quando (agoraEh == 1), rodar� p01; quando (agoraEh == 2), rodar� p02.
int recComp; //Vari�vel global que armazena o recurso compartilhado.

void *p01 (){
	int i;
	
	//For do bug(infinito)
	//for(;;){ 
	
	for(i=0; i<10; i++){ // REPEAT
		while(agoraEh == 2) {} //Vari�vel global de bloqueio. Quando igual a 2, n�o faz nada.
			//Se a vari�vel for igual a 1, executa o c�digo abaixo.
		 	recComp += 50; //Recurso de compartilhamento representa o incremento de 50s.
		 	
			printf("Thread1: USEI O RECURSO COMPARTILHADO: TEMPO %d segundos \n", recComp);
			int b;
			for(b = 0; b < 10; b++){
				printf("O tempo esta passando (%d)... \n", b);
			} 		
			
			agoraEh = 2; //Comentar para simular o bug
			printf("Mudei a variavel global para %d \n", agoraEh); //Comentar para simular o bug
	} 
}

void *p02 (){
	int i ;
	for (i=0; i<10; i++){
	while(agoraEh == 1) {} //entra se turn = 1
		//Bug 02 - N�o precisa usar a �rea cr�tica(recComp).
		printf("Thread2: USEI O RECURSO COMPARTILHADO: TEMPO %d segundos \n", recComp); 
		int b;
		for(b = 0; b < 5; b++){
			printf("O tempo esta passando (%d)... \n", b);			
		} 
		
		agoraEh = 1;
		printf("Mudei a variavel global para %d \n", agoraEh);
	}
}

int main(){
	pthread_create(&p1, NULL, p01, NULL) ;
	pthread_create(&p2, NULL, p02, NULL) ;
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
}

