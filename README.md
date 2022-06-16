# life-sfml

John Conway's Game of Life using C++ and the SFML library

Date of last edit: 16/6/2022

---

# Run Instructions

- Clone into directory
```
cd life-sfml/cmake-build-debug/
```
- From there you can either run the .exe with ```./life_sfml.exe```


- Or compile the .exe from source. To do this you need to have downloaded SFML
(https://www.sfml-dev.org) and specified its directory in ```CMakeLists.txt```
(which is in ```life-sfml/```).
The parameters you need to edit in ```CMakeLists.txt``` are:
  - ```set(SFML_DIR C:/SFML/lib/cmake/SFML)``` to where you downloaded SFML.
  - ```include_directories(C:/SFML/include)``` to where you downloaded SFML.

  From there, you can then run ```make``` and then ```./life_sfml.exe```.

In JetBrains CLion, which I used to make the game, you can open ```life-sfml/``` and
then build / run. CLion uses the CMakeLists.txt to generate a Makefile and creates
the .exe from there.