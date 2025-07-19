#ifndef LRU_H
#define LRU_H

#include <queue>
#include <string>

using namespace std;

bool buscaPagina_LRU(queue<string> Tabela, string pagina);
queue<string> atualiza_LRU(queue<string> Tabela, string pagina);
queue<string> subs_LRU(queue<string> Tabela, string pagina, int tamMax);

#endif // LRU_H