# B15F Benutzerhandbuch
*Hinweis*: Terminal-Befehle sind **fett** gedruckt 

## Installation

### 1. Abhängigkeiten installieren
 (a) **sudo apt-get update**  
 (b) **sudo apt-get install git avr-libc avrdude libncurses5-dev g++**  

### 2. Das Repository klonen
 (a) **cd /home/famulus/**  
 (b) **git clone "https://github.com/devfix/b15f.git"**  

### 3. Die Firmware installieren
 (a) **cd "/home/famulus/b15f/firmware"**  

 (b) Passen Sie in der Datei *Makefile* die Option "MCU = ..." an die MCU des vorliegenden Boards an  
 (*atmega1284* und *atmega1284p* sind nicht identisch!)  

 (c) **make**  

 Wenn udev richtig konfiguriert wurde:  
 (d I) **make upload**  
 Sonst:  
 (d II) **sudo make upload**  

### 4. Die Steuersoftware (Bibliothek & CLI) installieren
 (a) **cd "/home/famulus/b15f/control/src"**  
 (b) **make**  
 (Die Warnungen durch doxygen können ignoriert werden.)

 (c) **sudo make install**  

## Aktualisierung
 (a) **cd /home/famulus/b15f/**  
 (b) **git pull --prune**  
 (c) **cd "/home/famulus/b15f/firmware"**  
 (d) **make clean**  
 (e) **cd "/home/famulus/b15f/control/src"**  
 (f) **make clean**  
 (g) Installation ab Schritt 3 wiederholen
 
## Das CommandLineInterface (CLI) benutzen
 (a) Öffnen Sie ein Terminal und maximieren Sie das Fenster  
 (b) Start des CLI erfolgt durch **b15fcli**  
 (c) Die Navigation erfolgt durch &lt;Tab&gt;, die Pfeiltasten und &lt;Enter&gt; oder die Maus  
 (d) Mit &lt;Strg + c&gt; kann das Programm sofort verlassen werden

## Eigene Programme mit B15F schreiben

### Grundsätzliches
Die wichtigste Klasse für die Steuerung des Board 15 ist [B15F](https://devfix.github.io/b15f/html/classB15F.html).  
Dort befindet sich auch eine Übersicht der verfügbaren Befehle.  

### Beispiele
In dem Verzeichnis [b15f/control/examples](https://github.com/devfix/b15f/tree/master/control/examples) sind einige Beispiele für die Verwendung einzelner B15F Funktionen.  
Zu jedem Beispiel gehört eine *main.cpp* mit dem Quellcode und eine *Makefile*-Datei.  
Das Beispiel kann mit **make** kompiliert und mit ** \./main.elf** gestartet werden.

### Den B15F Treiber verwenden
Benötigt wird der B15F-Header:  
`#include <b15f/b15f.h>`  
und der Header für die plottyfile-Generierung, falls mit Kennlinien gearbeitet werden soll:  
`#include <b15f/plottyfile.h>` 

Für die Interaktion wird eine Referenz auf die aktuelle Treiberinstanz gespeichert:  
`B15F& drv = B15F::getInstance();`  
Falls noch keine existiert, wird automatisch eine erzeugt und Verbindung zum Board hergestellt.  

Ab jetzt können auf dem Object `drv` verschiedene Methoden angewand werden, siehe [B15F](https://devfix.github.io/b15f/html/classB15F.html).  

### Kennlinien mit plottyfile generieren
Die Beschreibung zu Plottyfile befindet sich [hier](https://devfix.github.io/b15f/html/classPlottyFile.html).  
Nach dem Include von plottyfile kann ein neues Objekt erzeugt und konfiguriert werden:  
```C++
PlottyFile pf;  
pf.setUnitX("V");  
pf.setUnitY("V");  
pf.setUnitPara("V");  
pf.setDescX("U_{OUT}"); // Markdown wird unterstuetzt  
pf.setDescY("U_{IN}");  
pf.setDescPara("");  
pf.setRefX(5);  
pf.setRefY(5);  
pf.setParaFirstCurve(0);  
pf.setParaStepWidth(0);
```
Messpunkte können anschließend hinzugefügt werden.  
Dabei gehören Punkte mit dem gleichen Index für `curve` (*uint8_t*) zur selben Kurve und erhalten durch Plotty automatisch die gleiche Farbe.  
```C++
pf.addDot(Dot(x, y, curve));
```
`x` und `y` sind *uint16_t*, also keine Gleitkommazahlen.

