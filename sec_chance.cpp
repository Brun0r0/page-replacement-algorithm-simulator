#include <iostream>
#include <vector>
#include <string>
#include "sec_chance.h"

using namespace std;

//Realiza a busca da pagina
int buscaPagina_seg_chance(vector<string> Tabela, string pagina){
    int tam = Tabela.size();

    for(int i = 0 ; tam > i ; i++){
        if(Tabela[i] == pagina){
            return i;
        }
    }
    
    return -1;  //Nao encontrou a pagina
}

//Algoritmo para substituicao com segunda chance
void subs_seg_chance(vector<string> *Tabela, vector<bool> *tab_verificacao,  string pagina, int tamMax){
    int tamTab = Tabela->size();

    //Se ha espaco apenas adiciona pagina na tabela
    if(tamTab < tamMax){
        Tabela->push_back(pagina);
        tab_verificacao->push_back(true);
        return;
    }

    int posInicio = 0;

    for(int i = 0; tamMax > i ; i++){
        //Verifica se ja foi dada uma segunda chance
        if(!(*tab_verificacao)[i]){
            //Substituindo pagina do frame e atualizando o bit
            (*Tabela)[i] = pagina;
            (*tab_verificacao)[i] = true;
            return;
        }
        //Se nao, seta o bit como false e continua procurando
        else{
            (*tab_verificacao)[i] = false;
        }
    }
    
    //caso nao tenha substituido nada, substitui o primeiro pois todos jao estao com bit 0
    (*Tabela)[0] = pagina;
    (*tab_verificacao)[0] = true;
}