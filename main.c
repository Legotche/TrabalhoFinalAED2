#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

#define tam_prateleira 20//quantos livros cabem
#define tam_estante 10   //quantas prateleiras cabem em cada estante
#define qnt_estantes 2   //quantas estantes tem


typedef struct{
    char titulo[50];
    char autor[20];
    int num_copias;
    int num_dispo;
}livro;     //dados de cada livro

typedef struct{
    livro livros[tam_prateleira];
    int qtdePrat;
    char tema[35];
}prateleira;//dados de cada prateleira

typedef struct{
    prateleira prateleiras[tam_estante];
}estante;   //dados de cada estante

typedef struct{
    char nome[30];
    int id;
    char senha[15];
    livro emprestimos[3];
    int status;
}pessoa;


void inicializa_prateleira(prateleira *p){
    p->qtdePrat=0;//nenhum livro ainda
}

void inicializa_estante(estante *e){

    char temas[][50] = {
            "Ficção Científica", "Fantasia", "Romance", "Mistério e Suspense", "Literatura Clássica",
            "História e Biografias", "Autoajuda e Desenvolvimento Pessoal", "Ciência e Tecnologia",
            "Arte e Fotografia", "Literatura Infantojuvenil", "Poesia", "Filosofia", "Religião",
            "Educação", "Esportes", "Política", "Negócios e Economia", "Ficção Histórica", "Humor",
            "Saúde e Bem-Estar", "Tecnologia da Informação", "Viagens e Aventura", "Culinária", "Moda",
            "Artes Marciais", "Meio Ambiente", "Jardinagem", "Matemática", "Ciências Sociais",
            "Literatura Estrangeira", "Teatro", "Música", "Literatura Nacional", "Psicologia",
            "Astrologia", "História Antiga", "Biografias de Celebridades", "Marketing", "Fotografia",
            "Artes Plásticas", "Literatura Brasileira", "Cinema"
    };
    int count_temas=0;


    for(int i=0;i<qnt_estantes;i++){

        for(int j = 0; j < tam_estante; j++){
            inicializa_prateleira(&e[i].prateleiras[j]);
            strcpy(e[i].prateleiras[j].tema,temas[count_temas]);
            count_temas++;
        }

    }
}

void string_tolower(char *string) {
    int tam = strlen(string);
    for (int i = 0; i < tam; i++) {
        string[i] = tolower(string[i]);
    }
}

char *busca_genero(estante *e, char tema[]) {
    char tema_minusculo[35];
    string_tolower(tema);

    for (int i = 0; i < qnt_estantes; i++) {
        for (int j = 0; j < tam_estante; j++) {
            strcpy(tema_minusculo, e[i].prateleiras[j].tema);
            string_tolower(tema_minusculo);

            if (strstr(tema_minusculo, tema) != NULL) {
                return e[i].prateleiras[j].tema;
            }
        }
    }

    return NULL;
}

//função do processo de cadastro
prateleira *busca_prateleira(estante *e,char tema[]){

    for(int i=0;i<qnt_estantes;i++){
        for(int j=0;j<tam_estante;j++){
            if(strcmp(e[i].prateleiras[j].tema,tema)==0){
                return &e[i].prateleiras[j];
            }
        }
    }
    return NULL;
}


//função do processo de cadastro
void inserir_novoLivro(prateleira *p, livro dado) {
    if (p->qtdePrat == tam_prateleira) {
        printf("\nPrateleira cheia\n");
        return;
    }

    if (p->qtdePrat + dado.num_copias > tam_prateleira) {
        printf("\nNão cabem todos os livros\nOperação reiniciada\n");
        return;
    }

    printf("\nLivro '%s' inserido com sucesso\n", dado.titulo);
    for (int i = 0; i < dado.num_copias; i++) {
        if (p->qtdePrat < tam_prateleira) {
            p->livros[p->qtdePrat++] = dado;
        } else {
            printf("\nPrateleira cheia após a inserção de %d livros\n", i);
            break;
        }
    }
}


//função do processo de cadastro
void imprimir_prateleira(prateleira *p){

    printf("         Titulo         |         Autor         |Qnt Total|Qnt Disponível|\n");



    for(int i = 0; i < p->qtdePrat; i++){
        if(strcmp(p->livros[i].titulo,p->livros[i-1].titulo)==0){
            continue;
        }
        printf("%24s|%23s|%9d|%14d|\n", p->livros[i].titulo, p->livros[i].autor,p->livros[i].num_copias,p->livros[i].num_dispo);
    }



}


void cadastro_livro(estante *e){

    livro aux_cadastro_livro;
    char aux_tema[35];

    prateleira *prateleira_atual;

    int confirmacao;



    while(1) {

        printf("Digite o gênero do livro: ");
        fgets(aux_tema, sizeof(aux_tema), stdin);
        aux_tema[strcspn(aux_tema, "\n")] = '\0';

        char *tema_resultado = busca_genero(e, aux_tema);

        if(tema_resultado==NULL){
            printf("\nTema não encontrado\n");
            continue;
        }

        printf("\nO tema encontrado foi %s, é esse que procurava?(sim=1,não=2)\n", tema_resultado);
        scanf("%d", &confirmacao);

        if (confirmacao == 1) {
            prateleira_atual = busca_prateleira(e, tema_resultado);
            break;
        } else {
            printf("\nReiniciando operação\n");
            if(getchar()=='\n'){}else{while(getchar()!='\n');}
            continue;
        }
    }
    if(getchar()=='\n'){
    }else{while(getchar()!='\n');}

    printf("Digite o título: ");
    fgets(aux_cadastro_livro.titulo,sizeof (aux_cadastro_livro),stdin);
    aux_cadastro_livro.titulo[strcspn(aux_cadastro_livro.titulo,"\n")]='\0';

    printf("\nDigite o autor: ");
    fgets(aux_cadastro_livro.autor,sizeof (aux_cadastro_livro.autor),stdin);
    aux_cadastro_livro.autor[strcspn(aux_cadastro_livro.autor,"\n")]='\0';

    printf("\nDigite o número de cópias: ");
    scanf("%d",&aux_cadastro_livro.num_copias);
    aux_cadastro_livro.num_dispo=aux_cadastro_livro.num_copias;

    inserir_novoLivro(prateleira_atual,aux_cadastro_livro);

    printf("\nImprimindo prateleira\n");
    imprimir_prateleira(prateleira_atual);

}


void insere_pessoa(pessoa **p, int *tamanho){
    pessoa *aux = *p;

    // Realoca a memória para acomodar um novo elemento
    aux = (pessoa *)realloc(aux, (*tamanho + 1) * sizeof(pessoa));

    if (aux == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    int tam=*tamanho;

    printf("\nDigite o nome do usuário: ");
    fgets(aux[tam].nome, sizeof(aux[tam].nome), stdin);
    aux[tam].nome[strcspn(aux[tam].nome, "\n")] = '\0';

    printf("Digite o ID do usuário: ");
    scanf("%d", &aux[tam].id);

    if (getchar() == '\n') {} else { while (getchar() != '\n'); }

    printf("Digite a senha: ");
    fgets(aux[tam].senha, sizeof(aux[tam].senha), stdin);
    aux[tam].senha[strcspn(aux[tam].senha, "\n")] = '\0';

    *p=aux;
    tam++;

    *tamanho=tam;

}


void imprime_pessoas(pessoa **p, int *tam) {
    printf("\nLista de pessoas:\n");
    for (int i = 0; i < *tam; i++) {
        printf("Nome: %s, ID: %d, Senha: %s\n", (*p)[i].nome, (*p)[i].id, (*p)[i].senha);
    }
}


void buscaPessoa(pessoa **p, int *tam){
    int id;
    char senha[15];

    pessoa *aux=*p;

    int pos;

    printf("Digite seu ID: ");
    scanf("%d", &id);

    if(getchar()=='\n'){}else{while(getchar()!='\n');}

    printf("Digite sua senha: ");
    fgets(senha,sizeof (senha),stdin);
    senha[strcspn(senha,"\n")]='\0';

    for(int i = 0; i < *tam; i++){
        if(aux[i].id == id && strcmp(aux[i].senha,senha)==0){
            printf("%s", aux[i].nome);

            break;
        }
    }

}

void busca_livro(estante *e){

    char nome_livro[50];
    int confirmacao;

    reinicia:


    printf("Digite o nome do livro: ");
    fgets(nome_livro,sizeof (nome_livro),stdin);
    nome_livro[strcspn(nome_livro,"\n")]='\0';

    for(int i=0;i<qnt_estantes;i++){
        for(int j=0;j<tam_estante;j++){
            for(int k=0;k<tam_prateleira;k++){
                if(strstr(e[i].prateleiras[j].livros[k].titulo,nome_livro)==NULL){
                    continue;
                }

                printf("\nO livro encontrado foi %s, é esse que procurava?(sim=1,não=2)\n",e[i].prateleiras[j].livros[k].titulo);
                scanf("%d", &confirmacao);

                if (confirmacao == 1) {
                    printf("Estante: %d \t", i);
                    printf("Prateleira: %d - %s", j, e[i].prateleiras[j].tema);
                    return;
                }
                else {
                    printf("\nReiniciando operação\n");
                    confirmacao=0;
                    if(getchar()=='\n'){}else{while(getchar()!='\n');}
                    goto reinicia;// eu sei q eu cometi um crime, mas foi por uma boa causa
                }
            }
        }
    }

    printf("\nLivro não encontrado\n");
    return;
}

void imprimir_estante(estante *e) {  //tem q arrumar ainda
    printf("┌───────────────────────────────────────────────────────────┐\n");
    for (int i = 0; i < qnt_estantes; i++) {
        printf("│                     Estante %d                            │\n", i+1);
        printf("├───────────────────────────────────────────────────────────┤\n");
        for (int j = 0; j < tam_estante; j++) {
            printf("│ Prateleira %d - %s\n", j+1, e[i].prateleiras[j].tema);
            printf("│   Titulo         |         Autor         |Qnt Total|Qnt Disponível|\n");
            printf("├───────────────────────────────────────────────────────────┤\n");
            for (int k = 0; k < e[i].prateleiras[j].qtdePrat; k++) {
                if(strcmp(e[i].prateleiras[j].livros[k].titulo,e[i].prateleiras[j].livros[k].titulo)==0){
                    continue;
                }
                printf("│   %-15s | %-20s | %8d | %13d |\n",
                       e[i].prateleiras[j].livros[k].titulo,
                       e[i].prateleiras[j].livros[k].autor,
                       e[i].prateleiras[j].livros[k].num_copias,
                       e[i].prateleiras[j].livros[k].num_dispo);
            }
        }
        printf("├───────────────────────────────────────────────────────────┤\n");
    }
    printf("└───────────────────────────────────────────────────────────┘\n");
}



/*
void remover_livro(prateleira *p,livro dado){


    int pos= buscar(p,dado);
    if (pos >= 0) {
        for (int i = pos; i < p->qtdePrat - 1; i++) {
            p->livros[i] = p->livros[i+1];
        }
        p->qtdePrat--;
    }
}

 */


void menu(){

    //declaração das estruturas
    estante e[qnt_estantes];
    pessoa *p=NULL;

    //declaração de variaveis
    int qnt_pessoas=0;
    char decisao;

    //inicialização das estruturas
    inicializa_estante(e);


    printf("\n\n-------   SISTEMA DA BIBLIOTECA   -------");

    do{
        printf("\n\n\t[1] - Cadastrar usuário;");
        printf("\n\t[2] - Listar usuários;");
        printf("\n\t[3] - Buscar usuário;");
        printf("\n\t[4] - Excluir usuários;\n");

        printf("\n\t[5] - Cadastrar livro;");
        printf("\n\t[6] - Listar livros;");
        printf("\n\t[7] - Buscar livro;");
        printf("\n\t[8] - Excluir livro;\n");

        printf("\n\t[-2] Salvar dados;");
        printf("\t[-1] - Carregar dados;");
        printf("\t[0] - Fechar sistema;\n\t");

        //if(getchar()=='\n'){}else{while(getchar()!='\n');}

        printf("\n\n\tDigite a opção desejada:");
        scanf(" %c",&decisao);
        //if(getchar()=='\n'){}else{while(getchar()!='\n');}

        switch (decisao) {

            case '1':     //Cadastrar usuário
                insere_pessoa(&p,&qnt_pessoas);
                break;

            case '2':     //Listar usuários
                imprime_pessoas(&p,&qnt_pessoas);
                break;

            case '3':     //Buscar usuário
                buscaPessoa(&p, &qnt_pessoas);
                break;

            case '4':     //Excluir usuários
                break;

            case '5':     //Cadastrar livro
                cadastro_livro(e);
                break;

            case '6':     //Imprimir tudo
                imprimir_estante(e);
                break;

            case '7':     //Buscar livro
                busca_livro(e);
                break;
            case '8':     //Excluir livro
                break;
            case '0':
                exit(0);
            default:
                printf("\nCódigo inválido\n");
                break;
        }
    }while(1);
}

int main(){

    setlocale(LC_ALL,"Portuguese");

    menu();

}