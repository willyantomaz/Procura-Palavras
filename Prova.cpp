#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define tamM 25
#define maxPal 112
/*AVALIAÇÃO PRÁTICA - Valor 3,0

- sortear uma matriz 25 X 25 contendo letras do alfabeto
- ler o arquivo de palavras e sortear uma palavra
- inserir palavra aleatoriamente na tabela (a ordem também deve ser aleatoria)
- apresentar a matriz
- solicitar ao usuário uma palavra
- informar ao usuário caso a palavra digitada esteja na matriz (independente de ter sido a sorteada e inserida na tabela ou não)

obs. A proporção para sorteio dos caracteres na matriz deverá ser 2:3, ou seja, 
para cada 3 caracteres sorteados, 2 deles deverão ser vogais 1 consoante.

.

*/

FILE *bd; //ponterio para o arquivo texto bd("banco de dados")

char cons[22]="BCDFGHJKLMNPQRSTVWXYZ";
char vog[6]="AEIOU";//\0 por isso 6 e 22 no vetor
char matriz[tamM][tamM];
char palavras[maxPal][tamM];//quatidade de palavras e tamanho.
char sorteada[tamM],palavraDig[tamM];
int vez=0,cont=0;


void sorteio();
void mostra();
void lerArquivo();
void colocaPalavra();
void procuraPalavra();

////////////////////////////////////////////////////////////////////////////////

int main(){
   srand(time(NULL));//impedir repetição,muda o valor da semente com o timer.
   sorteio();
   char continua;
   lerArquivo();
   strcpy(sorteada,palavras[rand()%maxPal]);
   colocaPalavra();
   mostra();
   printf("\no tamanho da palavra e de %i caracteres\n",strlen(sorteada));
   
   //printf("%s\n",sorteada); //para teste
   do{//laço para repetir caso queira procurar outra palavra
   
   printf("digite uma palavra: \n");
   gets(palavraDig);
   strupr(palavraDig);
   procuraPalavra();
   printf("quer procurar outra palavra ?(digite S)\n");
   scanf("%c",&continua);
   fflush(stdin);
   }while (continua=='s');
   system("pause");
   return 0;
    }
    
////////////////////////////////////////////////////////////////////////////////
//quis fazer um jeito diferente do professor!!
void sorteio(){
     for (int x=0;x<tamM;x++){
       for (int y=0;y<tamM;y++){
      switch(vez){
       case 0://tive que fazer trez pq em numeros pares ele saia do modelo 2:3
        matriz[x][y]=vog[rand()%5];
        vez=vez+1;
       break;
       case 1:
        matriz[x][y]=cons[rand()%21];
        vez=vez+1;
       break;
       case 2:
         matriz[x][y]=vog[rand()%5];
         vez=0;
       break; }
       }
      }
     }

////////////////////////////////////////////////////////////////////////////////

void mostra(){
     for (int x=0;x<tamM;x++){
       for (int y=0;y<tamM;y++){
          printf("%c ",matriz[x][y]);  
       }
      printf("\n");
     }
    }

////////////////////////////////////////////////////////////////////////////////

void lerArquivo(){
     bd = fopen("palavras.txt","r");
     cont=0;
     while (!feof(bd)){
         fgets(palavras[cont],20,bd);
         palavras[cont][strlen(palavras[cont])-1]='\0';
         cont++;  
     } 
           fclose(bd);
}

////////////////////////////////////////////////////////////////////////////////

 void colocaPalavra(){
      int qPosi=0,x,passa=0,contrario=0/*,y=19*/;
      int linha=0,coluna=0;
      contrario=rand()%2;
      qPosi=rand()%2;
      switch (qPosi){
        case 0://horizontal
         do{ 
              //comentarios para teste.
              passa=0;
              linha=rand()%25;//1
              coluna=rand()%21;//y;
              //printf("%i %i\n",coluna,contrario);
              // y--;
              if (strlen(sorteada)<=(25-coluna)){
                if (contrario==0){
                 for (x=0;x<=strlen(sorteada)-1;x++){
                   matriz[linha][coluna]=sorteada[x];
                   coluna++;
                 }
                }
                else{
                   for (x=strlen(sorteada)-1;x>=0;x--){
                     matriz[linha][coluna]=sorteada[x];
                     coluna++;
                   }
                 }
              }
               else
                passa=1;

         }while (passa!=0);
        break;     
        case 1://vertical
             do{ 
              //comentarios para teste.
              passa=0;
              linha=rand()%21;//1
              coluna=1;//rand()%21;//y;
              //printf("%i %i\n",linha,contrario);
              // y--;
              if (strlen(sorteada)<=(25-linha)){
                if (contrario==0){                                
                  for (x=0;x<=strlen(sorteada)-1;x++){//usei o laço por conta do \0.
                    matriz[linha][coluna]=sorteada[x];
                    linha++;
                  }
                }
                else{
                   for (x=strlen(sorteada)-1;x>=0;x--){
                     matriz[linha][coluna]=sorteada[x];
                     linha++;
                   }
                 }
                
              }
              else
                passa=1;
           }while (passa!=0);
        break;     
             }
}
 
////////////////////////////////////////////////////////////////////////////////

void procuraPalavra(){
     int y=0,z=0;
     char *tem;//ponteiro, mostra onde está o primeiro caracter da string
     char inverte[25],matrizPstr[626];  
     //strstr(): Esta função é usada para encontrar a primeira ocorrência de uma string em outra string
     //inverte a palavra para verificar.
     for (int x=strlen(palavraDig)-1; x>=0;x--){
          inverte[x]=palavraDig[y];
          y++;
          }
          inverte[strlen(palavraDig)]='\0';
          //printf("%s\n",inverte); //teste 
     
         tem = strstr(matriz[0],palavraDig);  
         if (tem!=0)
           printf("a palavra existe na matriz\n");
           else
           {
              tem = strstr(matriz[0],inverte);
              if (tem!=0)  
                printf("a palavra existe na matriz\n");
              else{
                   tem=0;
               for (int x=0;x<25;x++)//transforma a matriz em uma string para verificar se a palavra está na vertical
                for (int y=0;y<25;y++){
                    matrizPstr[z]=matriz[y][x];
                    z++;
                     }
                  matrizPstr[strlen(matrizPstr)]='\0';
                  tem = strstr(matrizPstr,palavraDig);
                  if (tem!=0)
                   printf("a palavra existe na matriz\n");
                  else{
                   tem = strstr(matrizPstr,inverte);
                   if (tem!=0)
                     printf("a palavra existe na matriz\n");
                   else
                     printf("a palavra nao existe na matriz\n");       
                   }
              }
               
                         
           }
     //printf("\n %s \n",matrizPstr);
     //printf("%i",tem); //teste
     }

////////////////////////////////////////////////////////////////////////////////
