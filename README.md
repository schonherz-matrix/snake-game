# Mátrix Snake játék

## Előfeltételek
Qt: 5.12.4

OpenSSL: 1.1.1

libmueb

CMake 3.16

## Fordítás
### Játék

A játékot az alábbi paranccsal vagy a Qt Creator segítségével fordíthatjuk le.

A játék fordításához a következő parancsot kell kiadni a gyökér mappában

```bash
cmake -B build && cmake -Dlibmueb_DIR=(libmueb cmake output) -DQt5_DIR=(qt telepítésének helye/lib/cmake/Qt5) --build build
```

Hogy működjön a háttérzene, ahhoz a `resources/` mappába kell belerakni a kívánt zenét `background.mp3` néven.

### Emulátor

A fentihez hasonlóképpen fordítható külön kell letölteni a forráskódját.

## Játék indítása
Mielőtt elindítjuk az emulátort, ne felejtsük el a gépünk loopback interfészére felvenni a 10.6.0.0/16-os hálóból egy tetszőleges nem broadcast címet, pl. az alábbi paranccsal:

`sudo ip a a 10.6.23.45/16 dev lo`

```bash
cd build
./matrix-snake-game
```

## Köszönetnyílvánítás

Az alma evésekor lejátszódó hangeffektért köszönet Simon Craggs-nek.
A háttér zene: LukHash - Let's Play