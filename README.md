### Zależności
- CMake
- Make
- Boost z modułem serialization
```
sudo apt-get install libboost-all-dev
```
- spdlog
```
sudo apt-get install libspdlog-dev
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

Wszystkie programy uruchamiane są z głównego katalogu projektu

#### Eksperymenty
```bash
make experiment_hsevo
make experiment
```

#### Gui
```bash
make gui_hsevo
make gui
```

#### Testy
```bash
make test_hsevo
make test
```

#### Profilowanie
```bash
make profile
```
Wyniki profilowania znajdują się w `./build/bin/profiling/hsevo_analysis.txt`
