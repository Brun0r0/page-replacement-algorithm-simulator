/* 
Implementação de simulador de gerência de memória utilizando algoritmos de busca
    LRU e Segunda chance.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string.h>
#include <queue>

using namespace std;

//Define a capacidade da TLB
#define tamTabelaP 64

//Variavel global
int tamTLB;


//------------Funcoes do algoritmo LRU------------

//Faz a busca da pagina na tabela do LRU
bool buscaPagina_LRU(queue<string> Tabela, string pagina){
    int tamTab = Tabela.size();

    while(tamTab--){
        if(pagina == Tabela.front())
            return true; 
        
        Tabela.pop();
    }

    return false; //Nao encontrou pagina
}

//Atualiza a fila da tabela LRU
queue<string> atualiza_LRU(queue<string> Tabela, string pagina){

    queue<string> fila_aux;
    int tamTab = Tabela.size();
    
    string aux;

    while(tamTab--){
        aux = Tabela.front();
        if(pagina != aux){
            fila_aux.push(aux);
        }
        Tabela.pop();
    }

    fila_aux.push(pagina);

    return fila_aux;
}

//Remove a pagina menos usada e coloca a pagina nova
queue<string> subs_LRU(queue<string> Tabela, string pagina, int tabelaEscol){
    int max;

    if(tabelaEscol == 1) max = tamTLB;
    else if(tabelaEscol == 2) max = tamTabelaP;

    int tamTab = Tabela.size();

    //Se ja atingiu capacidade maxima precisa de pop e push
    if(tamTab == max){
        Tabela.pop();
        Tabela.push(pagina);
    }
    //Se a tabela ainda nao atingiu capacidade maxima so dar push
    else
        Tabela.push(pagina);

    return Tabela;
}

//------------Fim funcoes do algoritmo LRU------------

//------------Funcoes do algoritmo Segunda Chance------------

//Realiza a busca da pagina
int buscaPagina_seg_chance(vector<string> Tabela, string pagina){
    string aux;
    int tam = Tabela.size();

    for(int i = 0 ; tam > i ; i++){
        aux = Tabela[i];
        if(aux == pagina){
            return i;
        }
    }
    
    return -1;  //Nao encontrou a pagina
}

//Algoritmo para substituicao com segunda chance
void subs_seg_chance(vector<string> *Tabela, vector<bool> *tab_verificacao,  string pagina, int tabelaEscol){
    //a variavel tabela, se tabela == 1 -> TLB ; se tabela == 2 -> tabela de paginas
    int max;
    if(tabelaEscol == 1) max = tamTLB;
    else if(tabelaEscol == 2) max = tamTabelaP;

    int tamTab = Tabela->size();

    //Se ha espaco apenas adiciona pagina na tabela
    if(tamTab < max){
        Tabela->push_back(pagina);
        tab_verificacao->push_back(true);
    }
    else{
        for(int i = 0 ; max > i ; i++){
            //Verifica se ja foi dada uma segunda chance
            if((*tab_verificacao)[i]){
                (*tab_verificacao)[i] = false;
            }
            //Caso ja tenha recebido uma segunda chance, pagina é substituida
            else{
                //Substituindo pagina do frame e atualizando o bit
                (*Tabela)[i] = pagina;
                (*tab_verificacao)[i] = true;
                return;
            }
        }
    }
    //caso nao tenha substituido nada, substitui o primeiro pois todos jao estao com bit 0
    (*Tabela)[0] = pagina;
    (*tab_verificacao)[0] = true;
}

//------------Fim funcoes do algoritmo Segunda Chance------------

int main(){

    string line; //string auxiliar

    string nomeArquivo;

    //Para alg. LRU usa-se filas como TLB e Tabela
    queue<string> TLB_LRU;
    queue<string> Tabela_LRU;

    //Para alg. Segunda Chance usa-se vetores como TLB e Tabela
    vector<string> TLB_seg_chance;
    vector<string> Tabela_seg_chance;

    //Vetores de verificacao para alg. Segunda Chance
    vector<bool> tab_verif_seg_chance_TLB;
    vector<bool> tab_verif_sef_chance_tabela;

    //Inicializacao de variaveis de contagem
    int hitTLB_LRU = 0, missTLB_LRU = 0, discAcess_LRU = 0;
    int hitTLB_seg_chance = 0, missTLB_seg_chance = 0, discAcess_seg_chance = 0;  

    //---------------Menu principal---------------

    cout << "Como usar o simulador" << endl;
    cout << "     -Coloque o arquivo .trace na pasta \"arquivos\"" << endl;
    cout << "     -Em \"Nome do arquivo\" basta colocar o nome, sem o .trace no fim" << endl;
    cout << "     -Escolha quantos Frames o TLB tera" << endl;

    cout << "\nNome do arquivo: ";
    cin >> nomeArquivo;
    cout << "\nQnt. Frames de TLB: ";
    cin >> tamTLB;

    cout << "\nGerando resultados...\n\n";

    string nomeCompleto = "arquivos/" + nomeArquivo + ".trace";

    //---------------FIM Menu principal---------------

    //Abrindo arquivo .trace
    ifstream arquivo(nomeCompleto); //caminho para .trace

    //Verifica se arquivo foi aberto corretamente
    if(!arquivo.is_open()){
        cerr << "\nErro para abrir arquivo" << endl;
        return 1;
    }

    //Loop principal
    while(getline(arquivo, line)){

        //Separando as informacoes
        string pagina, desloc, modo;
        pagina = line.substr(0,5);

        //Como so eh usada a pagina nas tabelas, vamos evitar informacoes extras
        //desloc = line.substr(5, 3);
        //modo = line.substr(9, 1);

        
        //-----------------------Comeco Algoritmo LRU-----------------------

        if(buscaPagina_LRU(TLB_LRU, pagina)){

            //Atualizacao da TLB
            TLB_LRU = atualiza_LRU(TLB_LRU, pagina);

            hitTLB_LRU++;
        }
        else if(buscaPagina_LRU(Tabela_LRU, pagina)){
            
            //Substituicao na TLB
            TLB_LRU = subs_LRU(TLB_LRU, pagina, 1);

            //Atualizacao da Tabela de Paginas
            Tabela_LRU = atualiza_LRU(Tabela_LRU, pagina);
            
            missTLB_LRU++;
        }
        else{

            //Substituicao na TLB
            TLB_LRU = subs_LRU(TLB_LRU, pagina, 1);

            //Substituicao na Tabela de Paginas
            Tabela_LRU = subs_LRU(Tabela_LRU, pagina, 2);

            discAcess_LRU++;
        }

        //-----------------------Fim Algoritmo LRU-----------------------

        //-----------------------Comeco Algoritmo Segunda Chance-----------------------

        //Utiliza-se o aux para caso encontre pagina, possa retornar a posicao e setar o bit 1 novamente
        int auxTLB = buscaPagina_seg_chance(TLB_seg_chance, pagina);
        int auxTabela = buscaPagina_seg_chance(Tabela_seg_chance, pagina);

        //Primeira verificacao: a pagina esta na TLB?
        if(auxTLB >= 0){

            //Seta o bit da pagina da TLB como "true"
            tab_verif_seg_chance_TLB[auxTLB] = true;

            hitTLB_seg_chance++;
        }
        else if(auxTabela >= 0){

            //Substituicao de pagina na TLB
            subs_seg_chance(&TLB_seg_chance, &tab_verif_seg_chance_TLB, pagina, 1);

            //Seta o bit da pagina da Tabela de Paginas como "true"
            tab_verif_sef_chance_tabela[auxTabela] = true;

            missTLB_seg_chance++;

        }
        else{

            //Substituição de pagina na TLB
            subs_seg_chance(&TLB_seg_chance, &tab_verif_seg_chance_TLB, pagina, 1);

            //Substituicao de pagina na Tabela de Paginas
            subs_seg_chance(&Tabela_seg_chance, &tab_verif_sef_chance_tabela, pagina, 2);

            discAcess_seg_chance++;
        }
    }

    //-----------------------Fim Algoritmo Segunda Chance-----------------------

    cout << fixed << setprecision(4);

    double taxa_LRU = double(hitTLB_LRU)/double(missTLB_LRU);

    double taxa_seg_chance = double(hitTLB_seg_chance)/double(missTLB_seg_chance);


    cout << "Algoritmo LRU: " << endl;
    cout << "     TLB Hit: " << hitTLB_LRU << " / TLB Miss: " << missTLB_LRU << endl;
    cout << "     Taxa de acertos/erros: " << taxa_LRU << endl;
    cout << "     Falha de pagina: " << discAcess_LRU << "\n\n";

    cout << "Algoritmo Segunda Chance" << endl;
    cout << "     TLB Hit: " << hitTLB_seg_chance << " / TLB Miss: " << missTLB_seg_chance << endl;
    cout << "     Taxa de acertos/erros: " << taxa_seg_chance << endl;
    cout << "     Falha de pagina: " << discAcess_seg_chance << endl;

    arquivo.close(); //Fechando arquivo
    
    return 0;
}