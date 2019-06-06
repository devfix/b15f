# B15F Benutzerhandbuch
*Hinweis*: Terminal-Befehle sind **fett** gedruckt 

## Installation

### 1. Abhängigkeiten installieren
 (a) **sudo apt-get update**  
 (b) **sudo apt-get install git avr-libc avrdude libncurses5-dev g++**  

### 2. Das Repository klonen
 (a) **cd /tmp**  
 (b) **git clone "https://github.com/devfix/b15f.git"**  

### 3. Die Firmware installieren
 (a) **cd "/tmp/b15f/firmware"**  
 
 (b) Passen Sie in der Datei *Makefile* die Option "MCU = ..." an die MCU des vorliegenden Boards an  
 (*atmega1284* und *atmega1284p* sind nicht identisch!)  
 
 (c) **make**  

 Wenn udev richtig konfiguriert wurde:  
 (d I) **make upload**  
 Sonst:  
 (d II) **sudo make upload**  

### 4. Die Steuersoftware (Bibliothek & CLI) installieren
 (a) **cd "/tmp/b15f/control/src"**  
 (b) **make**  
 (Die Warnungen durch doxygen können ignoriert werden.)

 (c) **sudo make install**  

## Einführung
Die wichtigste Klasse für die Steuerung des Board 15 ist [B15F](classB15F.html).  
Dort befindet sich auch eine Übersicht der verfügbaren Befehle.
