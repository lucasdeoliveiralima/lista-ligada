/*********************************************************
* Nome: Lista com vetores
* Descrição: Implementação de lista com uso de vetores e funções para manipulação da estrutura e dos dados
* Funções Implementadas:
*   - criar_lista
*   - inserir_elemento
*   - inserir_elemento_id
*   - inserir_elemento_inicio
*   - listar_elementos
*   - remover_elementos
*   - atualizar
*   - buscar_elemento
*   - tamanho
*   - excluir_lista
*   - carregar_dados
*   - salvar_dados
* Autor: Lucas de Oliveira Lima
* Ultima alteração: 29/09/2024
***********************************************************/

/*Import das libs*/
#include <stdio.h>
#include <stdlib.h>

/*Definição de constante para controle do tamanho do array de itens*/
#define TAMANHO 5

/*Definição da estrutura Processador*/
typedef struct{
    char modelo[20];
    int numero_cores;
    int numero_threads;
    int litografia_nm;
    float clock_basico_ghz;
    float clock_maximo_ghz;
    int tdp_watts;
    char video_integrado;
}Processador;

/*Definição da estrutura Lista*/
typedef struct{
    int id;
    Processador *itens;
}Lista;

/* Nome: criar_lista
 * Parametros: void
 * Retorno:
 *    - NULL: caso a alocação de memória falhe;
 *    - Lista *lista: retorna um ponteiro para a lista criada.
 * Descrição: Função responsável por alocar memória para a criação de uma lista de processadores e inicializar o contador de itens.
 */
Lista* criar_lista(){

    // Requisita alocação de memória para a lista
    Lista *lista = (Lista*) malloc(sizeof(Lista));

    // Aborta a função caso a alocação de memória falhe
    if(lista == NULL){
        printf("Não existe espaço suficiente para alocação\n");
        return NULL;
    }

    // Requisita alocação de memória para o vetor de itens
    lista->itens = (Processador*) malloc(sizeof(Processador) * TAMANHO);

    // Aborta a função caso a alocação de memória falhe
    if(lista->itens == NULL){
        printf("Não existe espaço suficiente para alocação\n");
        return NULL;
    }

    // Inicializa o contador de itens
    lista->id = 0;

    return lista;
}

/* Nome: inserir_elemento
 * Parametros:
 *    - Lista *lista: o ponteiro que contém o endereço para a lista
 *    - Processador *processador: o ponteiro que contém o endereço do processador
 * Retorno:
 *    - 0: caso a lista não exista ou não exista espaço disponível no vetor de itens;
 *    - 1: caso a inserção seja bem-sucedida.
 * Descrição: Função responsável inserir um processador na lista.
 */
int inserir_elemento(Lista *lista, Processador *processador){

    // Aborta a função caso a lista não exista
    if(lista == NULL){
        printf("\nLista nao inicializada\n");
        return 0;
    }

    // Aborta a função caso não exista espaço disponível no vetor de itens
    if(lista->id > TAMANHO){
        printf("\nLista cheia\n");
        return 0;
    }

    // Insere o processador no vetor de itens
    lista->itens[lista->id] = *processador;

    // Atualiza o contador de itens
    lista->id++;

    printf("\nItem inserido!\n");
    return 1;
}

/* Nome: inserir_elemento_id
 * Parametros:
 *    - Lista *lista: o ponteiro que contém o endereço para a lista
 *    - Processador *processador: o ponteiro que contém o endereço do processador
 *    - int pos: a posição no vetor de itens em que queremos inserir o processador
 * Retorno:
 *    - 0: caso a lista não exista,não exista espaço disponível no vetor de itens ou a posicao para inserir o item seja inválida;
 *    - 1: caso a inserção seja bem-sucedida.
 * Descrição: Função responsável inserir um processador na lista em uma posicao indicada.
 */
int inserir_elemento_id(Lista *lista, Processador *processador, int pos){

    int i, j;

    // Aborta a função caso a lista não exista
    if(lista == NULL){
        printf("\nLista nao inicializada\n");
        return 0;
    }

    // Aborta a função caso não exista espaço disponível no vetor de itens
    if(lista->id > TAMANHO){
        printf("\nLista cheia\n");
        return 0;
    }

    // Aborta a função caso a posição para inserir o item seja inválida
    if(pos < 1 || pos > lista->id){
        printf("\nPosicao invalida\n");
        return 0;
    }


    for(i = 0; i < lista->id; i++){
        if(i == pos - 1){
            for(j = lista->id; j > i; j--){

                // Empurra todos os elementos para a direita a no vetor de itens partir da posição indicada
                lista->itens[j] = lista->itens[j - 1];
            }

            // Insere o item na posição indicada
            lista->itens[i] = *processador;

            // Atualiza o contador de itens
            lista->id++;
        }
    }

    printf("\nItem inserido!\n");
    return 1;
}

/* Nome: inserir_elemento_inicio
 * Parametros:
 *    - Lista *lista: o ponteiro que contém o endereço para a lista;
 *    - Processador *processador: o ponteiro que contém o endereço do processador.
 * Retorno:
 *    - 0: caso a lista não exista ou não exista espaço disponível no vetor de itens;
 *    - 1: caso a inserção seja bem-sucedida.
 * Descrição: Função responsável inserir um processador nao inicio da lista.
 */
int inserir_elemento_inicio(Lista *lista, Processador *processador){

    int i;

    // Aborta a função caso a lista não exista
    if(lista == NULL){
        printf("\nLista nao inicializada\n");
        return 0;
    }

    // Verifica se há espaço disponível no vetor de itens
    if(lista->id < TAMANHO){
        for(i = lista->id; i > 0; i--){
        // Empurra todos os itens para a direita
        lista->itens[i] = lista->itens[i-1];
    }

    // Insere o processador na primeira posição do vetor
    lista->itens[0] = *processador;

    // Atualiza o contador de itens
    lista->id++;

    // Aborta a função caso o vetor de itens esteja cheio
    } else {
        printf("\nLista cheia\n");
        return 0;
    }

    printf("\nItem inserido!\n");
    return 1;
}

/* Nome: listar_elementos
 * Parametros: Lista *lista: o ponteiro que contém o endereço do processador
 * Retorno: void
 * Descrição: Função responsável por formatar e exibir os itens da lista
 */
void listar_elementos(Lista *lista){

    int i;

    // Alerta caso a lista não exista e aborta a função
    if(lista == NULL){
        printf("Lista nao inicializada\n");
        return;
    }

    // Alerta caso a lista esteja vazia e aborta a função
    if(lista->id == 0){
        printf("Lista vazia\n");
        return;
    }

    // Exibe todos os processadores cadastrados até o momento
    for(i = 0; i < lista->id; i++){
        printf("\nModelo %d: %s\n", i + 1, lista->itens[i].modelo);
        printf("  Cores: %d\n", lista->itens[i].numero_cores);
        printf("  Threads: %d\n", lista->itens[i].numero_threads);
        printf("  Litografia: %d nm\n", lista->itens[i].litografia_nm);
        printf("  Clock basico: %.2f GHz\n", lista->itens[i].clock_basico_ghz);
        printf("  Clock Max.: %.2f GHz\n", lista->itens[i].clock_maximo_ghz);
        printf("  TDP: %dW\n", lista->itens[i].tdp_watts);
        printf("  Video Integrado: %c\n", lista->itens[i].video_integrado);
        printf("- - - - - - - - - - - - - - -\n\n");
    }

    return;
}

/* Nome: remover_elemento
 * Parametros:
 *    - Lista *lista: o ponteiro que contém o endereço do processador
 *    - int pos: a posição no vetor de itens em que queremos remover o processador
 * Retorno:
 *    - 0: caso a lista não exista ou caso a posição informada seja superior ao numero de elementos no vetor de itens;
 *    - 1: caso a remoção seja bem-sucedida.
 * Descrição: Função responsável remover um processador da lista em uma posicao indicada.
 */
int remover_elemento(Lista *lista, int pos){

    int i, j;

    // Aborta a função caso a lista não exista
    if(lista == NULL){
        printf("Lista nao inicializada\n");
        return 0;
    }

    //Verifica se a posição é válida
    if(pos > 0 && pos <= lista->id){
        for(i = 0; i < lista->id; i++){

            // Verifica se a posição no vetor corresponde ao item a ser excluido
            if(i == pos - 1){
                for(j = i; j < lista->id; j++){

                    // Empurra todos os itens para a esquerda, sobrescrevendo o item a ser removido
                    lista->itens[j] = lista->itens[j+1];
                }
            }
        }

    // Aborta a função caso a posição seja menor que zero ou superior a quantidade de itens no vetor
    } else {
        printf("Posicao invalida\n");
        return 0;
    }

    // Atualiza o contador de itens
    lista->id--;

    printf("Item removido!\n");

    return 1;
}

/* Nome: atualizar
 * Parametros:
 *    - Lista *lista: o ponteiro que contém o endereço do processador;
 *    - Processador *processador: o ponteiro que contém o endereço do processador;
 *    - int pos: a posição no vetor de itens em que queremos atualizar o processador.
 * Retorno:
 *    - 0: caso a lista não exista ou caso a posição informada seja superior ao numero de elementos no vetor de itens ou menor que zero;
 *    - 1: caso a atualização seja bem-sucedida.
 * Descrição: Função responsável alterar um processador da lista em uma posicao indicada.
 */
int atualizar(Lista *lista, Processador *processador, int pos){

    int i;

    // Aborta a função caso a lista não exista
    if(lista == NULL){
        printf("Lista nao inicializada\n");
        return 0;
    }

    // Verifica se a posição indicada é válida
    if(pos > 0 && pos <= lista->id){
        for(i = 0; i < lista->id; i++){
            if(i == pos - 1){

                // Atualiza o processador na posição indicada
                lista->itens[i] = *processador;
                break;
            }
        }

    // Aborta a função caso a posição seja menor que zero ou superior a quantidade de itens no vetor
    } else {
        printf("Posicao invalida\n");
        return 0;
    }

    printf("Item atualizado!\n");
    return 1;
}

/* Nome: buscar_elemento
 * Parametros:
 *    - Lista *lista: o ponteiro que contém o endereço do processador;
 *    - int pos: a posição no vetor de itens em que queremos buscar o processador.
 * Retorno:
 *    - 0: caso a lista não exista ou caso a posição informada seja superior ao numero de elementos no vetor de itens ou menor que zero;
 *    - 1: caso o item seja encontrado.
 * Descrição: Função responsável buscar um processador da lista em uma posicao indicada.
 */
int buscar_elemento(Lista *lista, int pos){
    int i;

    // Aborta a função caso a lista não exista
    if(lista == NULL){
        printf("Lista nao inicializada\n");
        return 0;
    }

    // Verifica se a posição indicada é válida
    if(pos > 0 && pos <= lista->id){

        // Percorre o vetor de itens
        for(i = 0; i < lista->id; i++){

            // Retorna o processador referente a posição indicada
            if(i == pos - 1){
                printf("\nModelo %d: %s\n", pos, lista->itens[i].modelo);
                printf("  Cores: %d\n", lista->itens[i].numero_cores);
                printf("  Threads: %d\n", lista->itens[i].numero_threads);
                printf("  Litografia: %d nm\n", lista->itens[i].litografia_nm);
                printf("  Clock basico: %.2f GHz\n", lista->itens[i].clock_basico_ghz);
                printf("  Clock Max.: %.2f GHz\n", lista->itens[i].clock_maximo_ghz);
                printf("  TDP: %dW\n", lista->itens[i].tdp_watts);
                printf("  Video Integrado: %c\n", lista->itens[i].video_integrado);
            }
        }
    // Aborta a função caso a posição seja menor que zero ou superior a quantidade de itens no vetor
    }else{
        printf("Posicao invalida\n");
        return 0;
    }
    return 1;
}

/* Nome: tamanho
 * Parametro: Lista *lista: o ponteiro que contém o endereço da lista.
 * Retorno:
 *    - 0: caso a lista não exista;
 *    - lista->id: retorna o número de itens da lista.
 * Descrição: Função responsável por retornar a quantidade de itens na lista.
 */
int tamanho(Lista *lista){

    // Aborta a função caso a lista não exista
    if(lista == NULL){
        printf("Lista nao inicializada\n");
        return 0;
    }

    // Retorna o tamanho do vetor de itens
    return lista->id;
}

/* Nome: excluir_lista
 * Parametro: Lista *lista: o ponteiro que contém o endereço da lista;
 * Retorno:
 *    - NULL: caso a lista não exista ou caso a lista seja excluida com sucesso.
 * Descrição: Função responsável por excluir a lista e liberar a memória alocada para ela.
 */
Lista* excluir_lista(Lista *lista){

    // Aborta a função caso a lista não exista
    if(lista == NULL){
        printf("Lista nao inicializada\n");
        return NULL;
    }

    // Libera a memória alocada para o vetor de itens
    free(lista->itens);

    // Libera a memória alocada para a lista
    free(lista);

    printf("Lista excluida com sucesso!\n");
    return NULL;
}

/* Nome: carregar_dados
 * Parametro: Lista *lista: o ponteiro que contém o endereço da lista;
 * Retorno: void
 * Descrição: Função responsável por carregar os dados do arquivo e exibir no terminal
 */
void carregar_dados(Lista *lista){

    // Aborta a função caso a lista não exista
    if(lista == NULL){
        printf("Lista nao inicializada\n");
        return;
    }

    // Tenta abrir o arquivo em modo leitura
    FILE *arquivo = fopen("arquivo.txt", "r");

    // Aborta a função caso o arquivo não exista
    if(arquivo == NULL){
        printf("O arquivo nao existe.\n");
        return;
    }

    // Buffer para armazenar a linha do arquivo
    char linha[256];

    // Imprime cada linha do arquivo, incluindo quebra de linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }

    // Fecha o arquivo
    fclose(arquivo);

    return;
}

/* Nome: salvar_dados
 * Parametro: Lista *lista: o ponteiro que contém o endereço da lista.
 * Retorno:
 *  - 0: caso a lista não exista ou caso o arquivo não seja encontrado;
 *  - 1: caso os dados sejam escritos no arquivo com sucesso.
 * Descrição: Função responsável por carregar os dados do arquivo e exibir no terminal
 */
int salvar_dados(Lista *lista){

    int i;

    // Aborta a função caso a lista não exista
    if(lista == NULL){
        printf("Lista nao inicializada\n");
        return 0;
    }

    // Tenta abrir o arquivo em modo escrita
    FILE *arquivo = fopen("arquivo.txt", "w");

    // Aborta a função caso o arquivo não exista
    if(arquivo == NULL){
        printf("O arquivo nao existe.\n");
        return 0;
    }

    // Percorre o vetor de itens e escreve cada item no arquivo
    for(i = 0; i < lista->id; i++){
        fprintf(arquivo, "Modelo %d: %s\n", i + 1, lista->itens[i].modelo);
        fprintf(arquivo, "  Cores: %d\n", lista->itens[i].numero_cores);
        fprintf(arquivo, "  Threads: %d\n", lista->itens[i].numero_threads);
        fprintf(arquivo, "  Litografia: %d nm\n", lista->itens[i].litografia_nm);
        fprintf(arquivo, "  Clock basico: %.2f\n", lista->itens[i].clock_basico_ghz);
        fprintf(arquivo, "  Clock maximo: %.2f\n", lista->itens[i].clock_maximo_ghz);
        fprintf(arquivo, "  TDP: %dW\n", lista->itens[i].tdp_watts);
        fprintf(arquivo, "  Video integrado: %c\n", lista->itens[i].video_integrado);
        fprintf(arquivo, "- - - - - - - - - - - - - - -\n");
    }

    // Fecha o arquivo
    fclose(arquivo);

    printf("Dados salvos com sucesso!\n");
    return 1;
}

int main() {

    // Define um ponteiro do tipo Lista
    Lista *lista = NULL;

    // Define um ponteiro do tipo Processador
    Processador *p = (Processador*) malloc(sizeof(Processador));

    // opcao: captura a navegação no menu do usuario. posicao: recebe a posicao no vetor de itens para alterações
    int opcao, posicao;

    // Cria a lista, o vetor de itens e configura o contador interno
    lista = criar_lista();

    do{
        // MENU PRINCIPAL
        printf("------ CADASTRO DE ITENS -------\n");
        printf("\nEscolha uma opcao: \n");
        printf("  1 - Inserir um item no fim da lista\n");
        printf("  2 - Inserir um item na posicao desejada\n");
        printf("  3 - Inserir um item no inicio da lista\n");
        printf("  4 - Exibir todos os itens cadastrados\n");
        printf("  5 - Remover um item da lista\n");
        printf("  6 - Alterar um item da lista\n");
        printf("  7 - Pesquisar um item da lista\n");
        printf("  8 - Exibir a quantidade de itens cadastrados\n");
        printf("  9 - Excluir a lista\n");
        printf(" 10 - Ler os itens do arquivo de cadastro\n");
        printf(" 11 - Salvar os itens no arquivo de cadastro\n");
        printf("  0 - Sair do programa\n\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        // Captura a opção do usuário
        switch(opcao){
            case 1:
                printf("\n------ INSERIR ITEM NO FIM DA LISTA -------\n\n");
                printf("Digite o modelo do processador: ");
                scanf(" %[^\n]", p->modelo);
                printf("Digite o numero de cores: ");
                scanf("%d", &p->numero_cores);
                printf("Digite o numero de threads: ");
                scanf("%d", &p->numero_threads);
                printf("Digite a litografia: ");
                scanf("%d", &p->litografia_nm);
                printf("Digite o clock basico: ");
                scanf("%f", &p->clock_basico_ghz);
                printf("Digite o clock maximo: ");
                scanf("%f", &p->clock_maximo_ghz);
                printf("Digite a TDP: ");
                scanf("%d", &p->tdp_watts);
                printf("Digite se o processador possui video integrado( s para sim ou n para nao): ");
                scanf(" %c", &p->video_integrado);

                inserir_elemento(lista, p);
                break;
            case 2:
                printf("\n------ INSERIR ITEM NA POSICAO DESEJADA -------\n\n");
                printf("Digite o modelo do processador: ");
                scanf(" %[^\n]", p->modelo);
                printf("Digite o numero de cores: ");
                scanf("%d", &p->numero_cores);
                printf("Digite o numero de threads: ");
                scanf("%d", &p->numero_threads);
                printf("Digite a litografia: ");
                scanf("%d", &p->litografia_nm);
                printf("Digite o clock basico: ");
                scanf("%f", &p->clock_basico_ghz);
                printf("Digite o clock maximo: ");
                scanf("%f", &p->clock_maximo_ghz);
                printf("Digite a TDP: ");
                scanf("%d", &p->tdp_watts);
                printf("Digite se o processador possui video integrado( s para sim ou n para nao): ");
                scanf(" %c", &p->video_integrado);
                printf("Digite a posicao desejada: ");
                scanf("%d", &posicao);

                inserir_elemento_id(lista, p, posicao);
                break;
            case 3:
                printf("\n------ INSERIR ITEM NO INICIO DA LISTA -------\n\n");
                printf("Digite o modelo do processador: ");
                scanf(" %[^\n]", p->modelo);
                printf("Digite o numero de cores: ");
                scanf("%d", &p->numero_cores);
                printf("Digite o numero de threads: ");
                scanf("%d", &p->numero_threads);
                printf("Digite a litografia: ");
                scanf("%d", &p->litografia_nm);
                printf("Digite o clock basico: ");
                scanf("%f", &p->clock_basico_ghz);
                printf("Digite o clock maximo: ");
                scanf("%f", &p->clock_maximo_ghz);
                printf("Digite a TDP: ");
                scanf("%d", &p->tdp_watts);
                printf("Digite se o processador possui video integrado( s para sim ou n para nao): ");
                scanf(" %c", &p->video_integrado);

                inserir_elemento_inicio(lista, p);
                break;
            case 4:
                listar_elementos(lista);
                break;
            case 5:
                printf("\n------ REMOVER ITEM DA LISTA -------\n\n");
                printf("Digite a posicao do item a ser removido: ");
                scanf("%d", &posicao);
                remover_elemento(lista, posicao);
                break;
            case 6:
                printf("\n------ ALTERAR ITEM DA LISTA -------\n\n");
                printf("Digite o modelo do processador: ");
                scanf(" %[^\n]", p->modelo);
                printf("Digite o novo numero de cores: ");
                scanf("%d", &p->numero_cores);
                printf("Digite o novo numero de threads: ");
                scanf("%d", &p->numero_threads);
                printf("Digite a nova litografia: ");
                scanf("%d", &p->litografia_nm);
                printf("Digite o novo clock basico: ");
                scanf("%f", &p->clock_basico_ghz);
                printf("Digite o novo clock maximo: ");
                scanf("%f", &p->clock_maximo_ghz);
                printf("Digite a nova TDP: ");
                scanf("%d", &p->tdp_watts);
                printf("Digite se o processador possui video integrado( s para sim ou n para nao): ");
                scanf(" %c", &p->video_integrado);
                printf("Digite a posicao do item a ser alterado: ");
                scanf("%d", &posicao);

                atualizar(lista, p, posicao);
                break;
            case 7:
                printf("\n------ PESQUISAR ITEM -------\n\n");
                printf("Digite a posicao do item a ser pesquisado: ");
                scanf("%d", &posicao);

                buscar_elemento(lista, posicao);
                break;
            case 8:
                printf("Itens cadastrados: %d\n", tamanho(lista));
                break;
            case 9:
                excluir_lista(lista);
                break;
            case 10:
                carregar_dados(lista);
                break;
            case 11:
                salvar_dados(lista);
                break;
            case 0:
                printf("Programa encerrado!");

                // Libera a memória alocada para as estruturas
                free(p);
                free(lista->itens);
                free(lista);
                break;
            default:
                printf("\nOpcao invalida\n");
        }

    // Não encerra o programa até que o usuário solicite
    }while(opcao != 0);

    return 0;
}
