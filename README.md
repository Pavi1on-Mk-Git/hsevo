### Zależności
- CMake
```
sudo apt install cmake
```
- Make
```
sudo apt install make
```
- Boost z modułem serialization
```
sudo apt install libboost-all-dev
```
- spdlog
```
sudo apt install libspdlog-dev
```
- zależności biblioteki raylib
https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux

### Przygotowanie do uruchomienia programu:
```bash
mkdir -p build
cd build
cmake ..
cd ..
```

### Uruchamianie głównych programów:

Wszystkie programy uruchamiane są z głównego katalogu projektu.

#### Zawartość pliku `./src/main.cc` (używane do ręcznego debugowania fragmentów kodu)

Sama kompilacja:
```bash
make hsevo
```
Uruchomienie:
```bash
make run
```
Debugowanie z użyciem gdb:
```bash
make debug
```

#### Eksperymenty z pliku

Sama kompilacja:
```bash
make experiment_hsevo
```
Uruchomienie:
```bash
make experiment
```
Debugowanie z użyciem gdb:
```bash
make debug_exp
```

#### Aplikacja z interfejsem graficznym

Sama kompilacja:
```bash
make gui_hsevo
```
Uruchomienie:
```bash
make gui
```
Debugowanie z użyciem gdb:
```bash
make debug_gui
```

#### Testy jednostkowe

Sama kompilacja:
```bash
make test_hsevo
```
Uruchomienie:
```bash
make test
```
Debugowanie z użyciem gdb:
```bash
make debug_test
```
Pomiar pokrycia testów:
```bash
make coverage
```

#### Profilowanie
Profilowany jest kod zawarty w pliku `./src/main.cc`
```bash
make profile
```
Wyniki profilowania znajdują się w `./build/bin/profiling/hsevo_analysis.txt`

#### Eksport kodu do archiwum
```bash
make zip
```

#### Wygenerowanie wykresów
```bash
make plots
```
