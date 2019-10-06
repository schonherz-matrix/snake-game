# Mátrix Snake játék

## Előfeltételek
Qt: 5.12.4

OpenSSL: 1.1.1

## Fordítás
Amikor clone-ozzuk a repot, akkor azt az almodulokkal együtt tegyük a `git clone --recurse-submodules` parancs segítségével. Ha ezt valamiért elfelejtetted volna, akkor később a `git submodule update --init --recursive` parancs segítségével húzhatod le egyszerűen az almodulokat, mely parancsot a repo gyökerében adjuk ki.

### Játék
A játék fordításához két parancsot kell még kiadnunk: `qmake`, majd `make`. 

Mielőtt elindítjuk az emulátort, ne felejtsük el a gépünk loopback interfészére felvenni a 10.6.0.0/16-os hálóból egy tetszőleges nem broadcast címet, pl. az alábbi paranccsal:

`sudo ip a a 10.6.23.45/16 dev lo`

Hogy működjön a háttérzene, ahhoz a `matrix-snake-game/resources/` mappába kell belerakni a kívánt zenét `background.mp3` néven.

### Emulátor
Ha az emulátort szeretnénk használni, először azt is le kell fordítanunk. Ezt egyszerűen megtehetjük a QtCreator segítségével, de ha parancssorból szeretnénk csinálni, akkor itt is -- hasonlóan a játékhoz -- két parancs segítségével csinálhatjuk ezt meg: `qmake`, majd `make`.

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

## Köszönetnyílvánítás

Az alma evésekor lejátszódó hangeffektért köszönet Simon Craggs-nek.
A háttér zene: LukHash - Let's Play
