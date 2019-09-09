# Mátrix Snake játék

## Fordítás
Amikor clone-ozzuk a repot, akkor azt az almodulokkal együtt tegyük a `git clone --recurse-submodules` parancs segítségével. Ha ezt valamiért elfelejtetted volna, akkor később a `git submodule update --init --recursive` parancs segítségével húzhatod le egyszerűen az almodulokat, mely parancsot a repo gyökerében adjuk ki.

Ezután két parancsot kell még kiadnunk: `qmake`, majd `make`. 

Mielőtt elindítjuk az emulátort, ne felejtsük el a gépünk loopback interfészére felvenni a 10.6.0.0/16-os hálóból egy tetszőleges nem broadcast címet, pl. az alábbi paranccsal:

`sudo ip a a 10.6.23.45/16 dev lo`

## Játék indítása
Navigáljunk át az `./emu/emu` mappába, ott indítsuk el az emulátort:
```
cd ./emu/emu
./Emu
```

...majd a játékot is:

```
cd ../../matrix-snake-game
./matrix-snake-game
```
