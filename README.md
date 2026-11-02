# Lotka-Volterra

## Compilazione ed esecuzione tramite Cmake

Verificare la presenza del ninja build system:
* installazione
```bash
$ sudo apt install ninja-build
```
* verifica della versione
```bash
$ ninja --version
```

### Build

Nella directory madre in cui sono presenti le directory ```source``` e ```test```:
```bash
$ cmake -S . -B build -G"Ninja Multi-Config"
```

Verranno creati dei file nella cartella ```build```.

### Compilazione

Per compilare in modalità *Debug* e *Release* eseguire rispettivamente:

```bash
$ cmake --build build --config Debug
```

e

```bash
$ cmake --build build --config Release
```

Dentro le cartelle ```./build/Debug``` e ```./build/Release``` saranno presenti gli eseguibili ```lotka_volterra``` e ```lotka_volterra.t```, relativo ai test.

### Esecuzione

Chiamare i seguenti comandi per l'esecuzione dei test sia in modalità *Debug* che *Release*:

```bash
$ cmake --build build --config Debug --target test
```

e

```bash
$ cmake --build build --config Release --target test
```
Chiamare i seguenti comandi per l'esecuzione del programma principale (sia in modalità *Debug* che *Release*):

```bash
$ ./build/Debug/lotka_volterra
```

e

```bash
$ ./build/Release/lotka_volterra
```

## Compilazione ed esecuzione tramite g++

Sempre nella cartella madre, la compilazione può essere eseguita tramite

```bash
g++ -std=c++20 -Wall -Wextra source/main.cpp source/simulation.cpp -o lotka_volterra
```

che genererà l'eseguibile ```lotka_volterra``` nella cartella madre.

Per compilare i test:

```bash
g++ -std=c++20 test/test_simulation.cpp source/simulation.cpp -o test_simulation
```

che, analogamente, produrrà l'eseguibile dei test ```test_simulation```.