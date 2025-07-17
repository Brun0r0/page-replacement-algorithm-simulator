# 🧠 Simulador de Gerência de Memória: LRU e Segunda Chance

Este projeto em C++ simula dois algoritmos clássicos de gerência de memória utilizados por sistemas operacionais: **LRU (Least Recently Used)** e **Segunda Chance**. O programa lê arquivos `.trace` contendo referências a páginas de memória e analisa como cada algoritmo gerencia essas referências com uso de TLB (Translation Lookaside Buffer) e Tabela de Páginas.

## 🚀 Como usar

1. 📁 Coloque seu arquivo `.trace` na pasta `arquivos/` (ex: `arquivos/exemplo.trace`)
2. ▶️ Compile e execute o código
3. 🧾 Quando solicitado:
   - Digite **apenas o nome do arquivo**, sem a extensão `.trace`
   - Informe o número de **frames da TLB**

Exemplo:
```
Nome do arquivo: exemplo  
Qnt. Frames de TLB: 4
```

## 🧩 Estrutura do Projeto

- `main()` é o ponto de entrada, onde:
  - Um menu interativo coleta as informações iniciais
  - O arquivo `.trace` é lido linha a linha
  - Cada acesso é tratado simultaneamente pelos dois algoritmos

- **LRU (Least Recently Used)** usa:
  - `queue<string>` para simular TLB e Tabela
  - Funções:
    - `buscaPagina_LRU`
    - `atualiza_LRU`
    - `subs_LRU`

- **Segunda Chance** usa:
  - `vector<string>` para simular TLB e Tabela
  - Vetores de bits (`vector<bool>`) para marcar segunda chance
  - Funções:
    - `buscaPagina_seg_chance`
    - `subs_seg_chance`

## 📊 Saída gerada

Ao final da simulação, o programa exibe:

- ✅ Quantidade de **hits e misses** na TLB
- 🔁 Taxa de **acertos/erros**
- 💾 Número de **acessos ao disco** (page faults)

Exemplo de saída:
```
Algoritmo LRU:
    TLB Hit: 245 / TLB Miss: 119
    Taxa de acertos/erros: 2.0588
    Falha de pagina: 75

Algoritmo Segunda Chance:
    TLB Hit: 232 / TLB Miss: 132
    Taxa de acertos/erros: 1.7575
    Falha de pagina: 84
```

## 🛠️ Compilação

Compile com `g++`:

```bash
g++ simulador.cpp -o simulador
./simulador
```

## 📎 Exemplo de arquivo `.trace`

Cada linha deve conter um endereço lógico (os 5 primeiros caracteres representam a página):

```
04A2R
0135R
0223W
...
```

> Apenas os 5 primeiros caracteres são utilizados. O restante (modo ou deslocamento) é ignorado na simulação.

## 📚 Conceitos usados

- **LRU (Least Recently Used):** remove a página que não é usada há mais tempo
- **Segunda Chance:** dá uma chance extra às páginas antes de removê-las, utilizando um bit de uso

## ⚙️ Constantes

- Tamanho da **Tabela de Páginas** (`tamTabelaP`) é fixado em `64`
- Tamanho da **TLB** (`tamTLB`) é definido pelo usuário na execução

## 🧑‍💻 Autor

Gabriel Brunoro  
📫 GitHub: [@Brun0r0](https://github.com/Brun0r0)

## 🪪 Licença

Este projeto está sob a licença MIT.  
Sinta-se livre para usar, modificar e compartilhar 🔓
