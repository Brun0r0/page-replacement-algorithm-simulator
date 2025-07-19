#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

#include "sec_chance.h"
#include "LRU.h"

using namespace std;

//Define a capacidade da TLB
#define tamTabelaP 64

//Variavel global
int tamTLB;

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
    vector<bool> tab_verif_seg_chance_tabela;

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
        
        //-----------------------Comeco Algoritmo LRU-----------------------

        if(buscaPagina_LRU(TLB_LRU, pagina)){
            //Atualizacao da TLB
            TLB_LRU = atualiza_LRU(TLB_LRU, pagina);
            hitTLB_LRU++;
        }
        else if(buscaPagina_LRU(Tabela_LRU, pagina)){
            //Substituicao na TLB
            TLB_LRU = subs_LRU(TLB_LRU, pagina, tamTLB);

            //Atualizacao da Tabela de Paginas
            Tabela_LRU = atualiza_LRU(Tabela_LRU, pagina);
            missTLB_LRU++;
        }
        else{
            //Substituicao na TLB
            TLB_LRU = subs_LRU(TLB_LRU, pagina, tamTLB);

            //Substituicao na Tabela de Paginas
            Tabela_LRU = subs_LRU(Tabela_LRU, pagina, tamTabelaP);
            discAcess_LRU++;
        }

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
            subs_seg_chance(&TLB_seg_chance, &tab_verif_seg_chance_TLB, pagina, tamTLB);

            //Seta o bit da pagina da Tabela de Paginas como "true"
            tab_verif_seg_chance_tabela[auxTabela] = true;
            missTLB_seg_chance++;
        }
        else{
            //Substituição de pagina na TLB
            subs_seg_chance(&TLB_seg_chance, &tab_verif_seg_chance_TLB, pagina, tamTLB);

            //Substituicao de pagina na Tabela de Paginas
            subs_seg_chance(&Tabela_seg_chance, &tab_verif_seg_chance_tabela, pagina, tamTabelaP);
            discAcess_seg_chance++;
        }
    }

    //-----------------------Fim Algoritmo Segunda Chance-----------------------

    cout << fixed << setprecision(4);

    double taxa_LRU = double(hitTLB_LRU)/double(hitTLB_LRU + missTLB_LRU);

    double taxa_seg_chance = double(hitTLB_seg_chance)/double(hitTLB_seg_chance + missTLB_seg_chance);

    cout << "Algoritmo LRU: " << endl;
    cout << "     TLB Hit: " << hitTLB_LRU << " / TLB Miss: " << missTLB_LRU << endl;
    cout << "     Taxa de acertos/erros: " << taxa_LRU * 100 << endl;
    cout << "     Falha de pagina: " << discAcess_LRU << "\n\n";

    cout << "Algoritmo Segunda Chance" << endl;
    cout << "     TLB Hit: " << hitTLB_seg_chance << " / TLB Miss: " << missTLB_seg_chance << endl;
    cout << "     Taxa de acertos/erros: " << taxa_seg_chance * 100 << endl;
    cout << "     Falha de pagina: " << discAcess_seg_chance << endl;

    arquivo.close(); //Fechando arquivo
    
    return 0;
}