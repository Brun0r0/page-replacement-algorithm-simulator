#ifndef SEC_CHANCE_H
#define SEC_CHANCE_H

#include <vector>
#include <string>

using namespace std;

int buscaPagina_seg_chance(vector<string> Tabela, string pagina);
void subs_seg_chance(vector<string> *Tabela, vector<bool> *tab_verificacao, string pagina, int tamMax);


#endif // SEC_CHANCE_H