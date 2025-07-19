# 🧠 Page Replacement Algorithm Simulator

<div align="center">

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Memory Management](https://img.shields.io/badge/Memory-Management-blue?style=for-the-badge)
![Operating Systems](https://img.shields.io/badge/Operating-Systems-green?style=for-the-badge)

*A comprehensive simulator for comparing LRU and Second Chance page replacement algorithms*

</div>

## 📋 Table of Contents
- [Overview](#-overview)
- [Why Algorithm Choice Matters](#-why-algorithm-choice-matters)
- [Features](#-features)
- [Code Structure](#-code-structure)
- [Getting Started](#-getting-started)
- [Usage](#-usage)
- [Sample Output](#-sample-output)
- [Understanding the Results](#-understanding-the-results)
- [Future Improvements](#-future-improvements)
- [Contributing](#-contributing)

## 🎯 Overview

This simulator implements and compares two fundamental **page replacement algorithms** used in operating systems:

- **🔄 LRU (Least Recently Used)**: Replaces the page that hasn't been used for the longest time
- **⚡ Second Chance**: Enhanced FIFO algorithm that gives pages a "second chance" before replacement

The simulator processes memory access traces and provides detailed statistics about:
- **TLB (Translation Lookaside Buffer) performance**
- **Page table hits and misses**
- **Disk access frequency (page faults)**
- **Hit rate comparisons**

## ⚖️ Why Algorithm Choice Matters

Choosing the right page replacement algorithm can dramatically impact system performance:

| Scenario | LRU Performance | Second Chance Performance |
|----------|----------------|---------------------------|
| 🎮 **Gaming Applications** | ⭐⭐⭐⭐⭐ Excellent locality | ⭐⭐⭐ Good, less overhead |
| 🌐 **Web Servers** | ⭐⭐⭐ Good but expensive | ⭐⭐⭐⭐ Great balance |
| 📊 **Database Systems** | ⭐⭐⭐⭐ Very good for queries | ⭐⭐⭐ Decent performance |
| 🚀 **Real-time Systems** | ⭐⭐ Unpredictable overhead | ⭐⭐⭐⭐ Consistent timing |

> 💡 **Pro Tip**: LRU typically provides better hit rates but with higher computational overhead. Second Chance offers a good balance between performance and simplicity.

## ✨ Features

- 🔍 **Dual Algorithm Simulation**: Compare LRU and Second Chance side-by-side
- 📈 **Comprehensive Statistics**: Hit rates, miss counts, page faults
- ⚙️ **Configurable TLB Size**: Test different memory configurations
- 📁 **Trace File Support**: Process real memory access patterns
- 🎨 **Clean Output Format**: Easy-to-read results with precision formatting

## 🏗️ Code Structure

```
📦 Page Replacement Simulator
├── 📄 main.cpp              # Main program logic and user interface
├── 📄 LRU.cpp               # LRU algorithm implementation
├── 📄 LRU.h                 # LRU header file
├── 📄 sec_chance.cpp        # Second Chance algorithm implementation
├── 📄 sec_chance.h          # Second Chance header file
└── 📁 arquivos/             # Directory for trace files
    └── 📄 *.trace           # Memory access trace files
```

### 🔧 Core Components

#### `main.cpp`
- **User Interface**: Interactive menu for file selection and TLB configuration
- **Simulation Controller**: Orchestrates both algorithms simultaneously
- **Statistics Reporter**: Formats and displays comparative results

#### `LRU.cpp` & `LRU.h`
- **`buscaPagina_LRU()`**: Searches for pages in LRU queue
- **`atualiza_LRU()`**: Updates page position to most recently used
- **`subs_LRU()`**: Handles page replacement using LRU policy

#### `sec_chance.cpp` & `sec_chance.h`
- **`buscaPagina_seg_chance()`**: Locates pages in Second Chance table
- **`subs_seg_chance()`**: Implements Second Chance replacement with reference bits

## 🚀 Getting Started

### Prerequisites
- **C++ Compiler** (g++, clang++, or Visual Studio)
- **Standard C++ Libraries** (iostream, queue, vector, fstream)

### Compilation

```bash
# Using g++
g++ -o simulator main.cpp LRU.cpp sec_chance.cpp

# Using clang++
clang++ -o simulator main.cpp LRU.cpp sec_chance.cpp

# Using make (if you create a Makefile)
make
```

### Setting Up Trace Files

1. Create an `arquivos` directory in your project folder
2. Place your `.trace` files in this directory
3. Each line in a trace file should contain memory access information

**Trace File Format:**
```
12ABC 1000 R
34DEF 2000 W
12ABC 3000 R
...
```
*Format: `[5-char page] [offset] [R/W mode]`*

## 📖 Usage

### Running the Simulator

```bash
./simulator
```

### Interactive Setup

```
Como usar o simulador
     -Coloque o arquivo .trace na pasta "arquivos"
     -Em "Nome do arquivo" basta colocar o nome, sem o .trace no fim
     -Escolha quantos Frames o TLB tera

Nome do arquivo: example
Qnt. Frames de TLB: 8
```

### Parameters

- **📁 File Name**: Name of trace file (without .trace extension)
- **🔢 TLB Frames**: Number of frames in Translation Lookaside Buffer (recommended: 4-32)

## 📊 Sample Output

```
Gerando resultados...

Algoritmo LRU: 
     TLB Hit: 1247 / TLB Miss: 753
     Taxa de acertos: 0.6235
     Falha de pagina: 234

Algoritmo Segunda Chance
     TLB Hit: 1198 / TLB Miss: 802
     Taxa de acertos: 0.5990
     Falha de pagina: 298
```

## 🧮 Understanding the Results

| Metric | Description | Impact |
|--------|-------------|---------|
| **TLB Hit** | Page found in TLB cache | ⚡ Fastest access (1 cycle) |
| **TLB Miss** | Page found in page table | 🐌 Slower access (10-100 cycles) |
| **Taxa de acertos** | Hit rate (hits/total) | 📈 Higher is better |
| **Falha de pagina** | Page faults (disk access) | 💾 Slowest access (1000+ cycles) |

## 🔮 Future Improvements

### 🛠️ Immediate Enhancements
- [ ] **Add input validation** for TLB size and file names  
- [ ] **Implement FIFO algorithm** for three-way comparison
- [ ] **Add command-line arguments** for batch processing

### 🚀 Advanced Features
- [ ] **Graphical visualization** of page replacement patterns
- [ ] **Memory access pattern analysis** (temporal/spatial locality)
- [ ] **Multi-threaded simulation** for large trace files
- [ ] **JSON/CSV output format** for data analysis
- [ ] **Working set size analysis**
- [ ] **Cache-aware optimizations**

### 📈 Performance Optimizations
- [ ] **Optimized Second Chance** with circular buffer
- [ ] **LRU approximation algorithms** (Clock, NRU)
- [ ] **Adaptive replacement policies**

### Contribution Ideas
- 🐛 Bug fixes and optimizations
- 📊 Additional algorithms (FIFO, Optimal, Clock)
- 🎨 Output formatting improvements
- 📚 Documentation enhancements
- 🧪 Unit tests implementation

## 📜 License

This project is open source and available under the [MIT License](LICENSE).

---

<div align="center">

**🎓 Educational Project** | **💻 Operating Systems** | **🧠 Memory Management**

*Built with ❤️ for learning and understanding page replacement algorithms*

</div>
