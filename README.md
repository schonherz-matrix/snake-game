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

### Emulátor
Ha az emulátort szeretnénk használni, először azt is le kell fordítanunk. Ezt egyszerűen megtehetjük a QtCreator segítségével, de ha parancssorból szeretnénk csinálni, akkor itt is -- hasonlóan a játékhoz -- két parancs segítségével csinálhatjuk ezt meg: `qmake`, majd `make`.

### SFML
Bővebben az SFML-ről a GitHub oldalukon olvashatsz, itt: [SFML](https://github.com/SFML/SFML)

Nagyon röviden, ami nekünk kell: kizárólag a zene és hangeffektek lejátszása miatt van szükségünk erre a projektre. Ha nem szeretnéd ezt is parancssorból fordítani, a legegyszerűbb, ha az egyik tutorialjuk segítségével telepíted a gépedre. Ha mégis inkább maradnál a parancssoros fordítás mellett, azt legeslegegyszerűbben két parancs kiadásával teheted meg: `cmake .`, majd ezt követően `make`.

(TODO: Windowson is tesztelni)

!!!FONTOS!!!: egyelőre nem teljesen értem miért, de a wav fájlok lejátszása esetén hiába a default valami csatlakoztatott eszköz, nem ott akarja lejátszani a hangokat, hanem a beépített hangszórón keresztül. Ennek még utána kell nézni, hogy miért!


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
