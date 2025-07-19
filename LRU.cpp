#include <iostream>
#include <vector>
#include <queue>
#include "LRU.h"

using namespace std;

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
queue<string> subs_LRU(queue<string> Tabela, string pagina, int tamMax){
    int tamTab = Tabela.size();

    //Se ja atingiu capacidade maxima precisa de pop e push
    if(tamTab == tamMax){
        Tabela.pop();
        Tabela.push(pagina);
    }
    //Se a tabela ainda nao atingiu capacidade maxima so dar push
    else
        Tabela.push(pagina);

    return Tabela;
}