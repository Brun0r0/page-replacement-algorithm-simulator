# 🧠 Memory Management Simulator: LRU and Second Chance

This C++ project simulates two classic memory management algorithms used by operating systems: **LRU (Least Recently Used)** and **Second Chance**. The program reads `.trace` files containing memory page references and simulates how each algorithm handles them using a TLB (Translation Lookaside Buffer) and a Page Table.

## 🚀 How to Use

1. 📁 Place your `.trace` file in the `arquivos/` folder (e.g., `arquivos/example.trace`)
2. ▶️ Compile and run the code
3. 🧾 When prompted:
   - Enter **only the file name**, without the `.trace` extension
   - Enter the number of **TLB frames**

Example:
```
File name: example  
TLB Frame Count: 4
```

## 🧩 Project Structure

- `main()` is the entry point where:
  - A simple menu gathers initial input
  - The `.trace` file is read line by line
  - Each access is processed by both algorithms

- **LRU (Least Recently Used)** uses:
  - `queue<string>` for TLB and Page Table
  - Functions:
    - `buscaPagina_LRU`
    - `atualiza_LRU`
    - `subs_LRU`

- **Second Chance** uses:
  - `vector<string>` for TLB and Page Table
  - `vector<bool>` for tracking the second-chance bits
  - Functions:
    - `buscaPagina_seg_chance`
    - `subs_seg_chance`

## 📊 Output Example

At the end of the simulation, the program displays:

- ✅ Number of **TLB hits and misses**
- 🔁 **Hit/Miss ratio**
- 💾 Number of **disk accesses** (page faults)

Example output:
```
LRU Algorithm:
    TLB Hit: 245 / TLB Miss: 119
    Hit/Miss Ratio: 2.0588
    Page Faults: 75

Second Chance Algorithm:
    TLB Hit: 232 / TLB Miss: 132
    Hit/Miss Ratio: 1.7575
    Page Faults: 84
```

## 🛠️ Compilation

Compile using `g++`:

```bash
g++ simulador.cpp -o simulador
./simulador
```

## 📎 Sample `.trace` File Format

Each line should contain a logical address (only the first 5 characters represent the page):

```
04A2R
0135R
0223W
...
```

> Only the first 5 characters are used. The rest (access mode or offset) is ignored in the simulation.

## 📚 Concepts Used

- **LRU (Least Recently Used):** removes the least recently accessed page
- **Second Chance:** gives pages a second chance before replacing them, using a reference bit

## ⚙️ Constants

- The **Page Table** size (`tamTabelaP`) is fixed at `64`
- The **TLB** size (`tamTLB`) is defined by the user during runtime

## 🪪 License

This project is licensed under the MIT License.  
Feel free to use, modify, and share it 🔓
