#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define fSize 9
#define vSize 5

//Estrutura dos dados
typedef struct {    
    int codigo;
    char tipo[50]; 
    float custo;
    int autonomia;
} Veiculo;

typedef struct{
    int num_ord;
    int NIF;
    int veiculo;
    int tempo;
    int distancia;
}  Fatura;

//assinaturas
int menu();
int insVeiculo(Veiculo V[vSize],int tamanho,int cod, char tp[50], float ct, int autono);
int insFatura(Fatura F[fSize],int tamanhof ,int n_ord ,int nif , Veiculo V[vSize], int codVeiculo ,int tamanhov,int temp, int dist);
void listv(Veiculo V[vSize],int tamanho);
int rmVeiculo(Veiculo V[vSize],int tamanho, int cod);

//remover veiculo eletricos do array
int rmVeiculo(Veiculo V[vSize],int tamanho, int cod){
    if(cod <= tamanho){
        // cod-1 e tamanho-1 para diminuir o tamanho do array 
        for(int i = cod-1; i<tamanho-1 ;i++){
            V[i].codigo = V[i+1].codigo;
            strcpy(V[i].tipo, V[i+1].tipo);
            V[i].custo = V[i+1].custo;
            V[i].autonomia = V[i+1].autonomia ;
        }
        return(1);
    }else return(0);
    
}

// lista todos os veiculos eletricos 
void listv(Veiculo V[vSize],int tamanho){
    printf("####Veiculos Eletricos####\n");
    for(int i=0; i<tamanho;i++){
        printf("Codigo:%d\n",V[i].codigo);
        printf("Tipo:%s\n",V[i].tipo);
        printf("Custo:%.2f\n",V[i].custo);
        printf("Autonomia:%d\n",V[i].autonomia);
        printf("######################\n");
    }
}

void listf(Fatura F[fSize],int tamanhof){
    printf("####Faturas####\n");
    for(int i=0; i<tamanhof;i++){
        printf("Numero ordem:%d\n",F[i].num_ord);
        printf("NIF:%d\n",F[i].NIF);
        printf("Veiculo:%d\n",F[i].veiculo);
        printf("Tempo:%d\n",F[i].tempo);
        printf("Distancia:%d\n",F[i].distancia);
        printf("######################\n");
    }
}

//função para inserir veiculo eletrico
int insVeiculo(Veiculo V[fSize],int tamanho,int cod, char tp[50], float ct, int autono){
    if(tamanho<vSize){
        V[tamanho].codigo = cod;
        strcpy(V[tamanho].tipo, tp);
        V[tamanho].custo = ct;
        V[tamanho].autonomia = autono;
        return(1);
    }else return(0);
}

//Funçãi inserir fatura 
int insFatura(Fatura F[fSize],int tamanhof ,int n_ord ,int nif , Veiculo V[vSize], int codVeiculo ,int tamanhov,int temp, int dist){

    if(tamanhof<fSize){
        
        F[tamanhof].num_ord = n_ord;
        F[tamanhof].NIF = nif;
        F[tamanhof].veiculo = codVeiculo;
        F[tamanhof].tempo = temp;
        F[tamanhof].distancia = dist;
        return(1);
    }else return(0);
}
 
//MENU
int menu(){
    int opcao;
    do{
        printf("---------MENU-------\n");
        printf("1 - Inserção de um novo meio de mobilidade elétrica\n");
        printf("2 - Remoção de um meio de mobilidade elétrica a partir do seu código\n");
        printf("3 - Inserção de um novo pedido de utilização\n");
        printf("4 - Remoção de um pedido de utilização a partir do seu código\n");
        printf("5 - Listagem dos dados de todos os meios de mobilidade elétrica\n");
        printf("6 - Listagem de todo os pedidos de utilização\n");
        printf("7 - Cálculo do custo associado a um pedido de utilização a partir da indicação do seu número de ordem\n");
        printf("0 - Sair\n");
        printf("Opcao?");
        scanf("%d",&opcao); 
    }
    while ((opcao>7)||(opcao<0));
    return(opcao);
}


int main(){
    Fatura fatura[fSize];
    Veiculo veiculo[vSize];
    int opcao;
    int codigov,codV,resV, res3;
    char tipov[50];
    float custov;
    int autonomiav = 0;
    int nif,cod,temp,dist = 0;
    int nord=0;
    int tamanhov,tamanhof = 0;

    do{
        opcao = menu();
        switch(opcao){
            case 1: 
                printf("##Inserir veiculo##\n");
                rollback:       //ponto de retorno se o if for verdadeiro!!
                printf("Inserir codigo:\n");
                scanf("%d", &codigov);

                //validação de input
                if(codigov<0){
                    printf("codigo tem de ser a cima de 0!\n");
                    goto rollback; 
                };
                printf("Inserir tipo:\n");
                scanf("%s", tipov);        
                printf("Inserir custo:\n");
                scanf("%f", &custov);
                if(custov<0){
                    printf("Custo tem de ser a cima de 0!\n");
                    goto rollback;
                };
                printf("Inserir Autonomia:\n");
                scanf("%d", &autonomiav);
                if(autonomiav<0){ 
                    printf("Autonomia tem de ser a cima de 0!\n");
                    goto rollback;
                };

                insVeiculo(veiculo ,tamanhov ,codigov, tipov, custov, autonomiav);
                tamanhov++;

                break;
            case 2: 
                printf("Insira o codigo do Veiculo eletrico que deseja remover:");
                scanf("%d", &codV);
                resV = rmVeiculo(veiculo,tamanhov,codV);
                if(resV==1){
                    printf("Veiculo eletrico removido com sucesso!\n");
                    tamanhov--;
                } else printf("Veiculo eletrico não removido!\n");
                
                break;
            case 3: 
                printf("##Inserir Fatura##\n");
                printf("NIF:");
                scanf("%d", &nif);

                againcodveiculo:
                printf("Codigo:");
                scanf("%d", &cod);
                //verificação se codigo existe 
                for(int i = 0; i<tamanhov ;i++){
                if(cod == veiculo[i].codigo){
                    fatura[tamanhof].veiculo = veiculo[i].codigo;
                }else {
                    printf("Não existe este codigo de veiculo eletrico\n");
                    goto againcodveiculo;
                } 
                }
                printf("tempo:");
                scanf("%d", &temp);
                printf("Distância:");
                scanf("%d", &dist);
                printf("%dnumord", nord);

                res3 = insFatura(fatura, tamanhof, nord, nif, veiculo, cod, tamanhov, temp, dist);
                if(res3==1) printf("Inserido com sucesso!\n");
                    else printf("Fatura não inserida!\n");
                nord++;
                tamanhof++;
                printf("%dnumord", nord);
                break;
            case 4: 
            
                break;
            case 5: 
            listv(veiculo,tamanhov);
                break;
            case 6: 
            listf(fatura,tamanhof);
                break;
            case 7: 
                
                break;
        }   
    }while(opcao != 0);

    return(0);

}