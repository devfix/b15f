# B15F Benutzerhandbuch
*Hinweise*:  
 - Terminal-Befehle sind **fett** gedruckt  
 - Als Student/Studentin können Sie davon ausgehen, dass die Steuersoftware auf Ihrem Arbeitsplatz bereits installiert ist  
 - D.h. Sie müssen zu Beginn jeder Übung nur die Firmware neu aufspielen (Installation Abschnitt 3)  

## Einführung
Das gesamte Softwareprojekt besteht aus zwei Teilen:  
Die ***Firmware*** ist die Software auf dem Mikrocontroller (MCU) des Board 15. Der Mikrocontroller steuert die Peripherie (ADCs, DACs, ...) über einen SPI-BUS.  

Der zweite Teil von B15F ist die ***Steuersoftware***, die auf dem PC ausgeführt wird. Diese sendet über eine USART-Schnittstelle (RS-232) Befehle an den Mikrocontroller.  
Die Steuersoftware besitzt ein *CLI* (command line interface) mit einer Benutzerschnittstelle für die einfache Fernsteuerung des B15F.  
Außerdem wird eine Bibliothek (*b15fdrv*) installiert, die eine einfache Entwicklung kleiner Steuerprogramme erlaubt.

## Installation

### Installation mit Installationsscript (empfohlen)

 (a) Laden Sie das [Installationsscript](https://raw.githubusercontent.com/devfix/b15f/master/install) herunter  
 (b) Setzen Sie die Ausführungsberechtigung  
 (c) Schalten Sie die Stromversorgung von B15 an und schließen Sie den ISP Programmer an  
 (d) Starten Sie das Installationsscript  

### Installation von Hand (falls Installationsscript mit Fehler abbricht)

#### 1. Abhängigkeiten installieren
 (a) APT-Pakete aktualisieren: **sudo apt-get update**  
 (b) Notwendige Pakete installieren bzw. aktualisieren: **sudo apt-get install git avr-libc avrdude libncurses5-dev g++ astyle**  

#### 2. Das Repository klonen
 (a) Home-Verzeichnis betreten: **cd /home/famulus/**  
 (b) B15F-Repository klonen (herunterladen): **git clone "https://github.com/devfix/b15f.git"**  

#### 3. Die Firmware installieren
 (a) Installations-Verzeichnis betreten: **cd "/home/famulus/b15f/firmware"**  
 (b) Passen Sie in der Datei *Makefile* (im aktuellen Verzeichnis) die Option "MCU = ..." an die MCU des vorliegenden Boards an.  
      **Achtung**: *atmega1284* und *atmega1284p* sind nicht identisch!  
 (c) Fügen Sie den Nutzer *famulus* zu Gruppe *dialout* hinzu: **sudo adduser famulus dialout**  
 (d) Schreiben Sie (mit root-Rechten) Folgendes in die Datei "*/etc/udev/rules.d/60-olimex.rules*":  
```
ATTR{idVendor}=="03eb", ATTR{idProduct}=="2104", MODE="660", GROUP="dialout"
```
 Damit wird per udev-rule der Zugriff auf das ISP-Programmiergerät ohne root-Rechte erlaubt.  
 (e) Laden Sie die udev-Regeln neu ein: **sudo udevadm control --reload-rules**  
 (f) Stoße Verarbeitung der udev-Regeln an: **sudo udevadm trigger**  
 (g) Programmiergerät rausziehen, drei Sekunden warten, wieder hineinstecken  
 (h) Kompiliere Firmware: **make**  
 (i) Lade Firmware auf das B15: **make upload**  

#### 4. Die Steuersoftware (Bibliothek & CLI) installieren
 (a) Installations-Verzeichnis betreten: **cd "/home/famulus/b15f/control/src"**  
 (b) Kompiliere Steuersoftware: **make**  
 (c) Installiere die Bibliothek und CLI (global): **sudo make install**  

## Aktualisierung

### Aktualisierung mit Installationsscript (empfohlen)
Wiederholen Sie den Schritt "Installation mit Installationsscript". Das Script erkennt die bereits installierte Version und aktualisiert diese.

### Aktualisierung von Hand (falls Installationsscript mit Fehler abbricht)
 (a) Installations-Verzeichnis betreten: **cd /home/famulus/b15f/**  
 (b) Neuste Software-Version vom GitHub-Server ziehen: **git pull && git pull --prune**  
 (c) Betrete Firmware-Verzeichnis: **cd "/home/famulus/b15f/firmware"**  
 (d) Lösche altes Kompilat der Firmware: **make clean**  
 (e) Betrete Steuersoftware-Verzeichnis: **cd "/home/famulus/b15f/control/src"**  
 (f) Lösche altes Kompilat der Steuersoftware: **make clean**  
 (g) "Installation von Hand" ab Schritt 3 (h) durchführen
 
## Die CommandLineInterface (CLI) benutzen
 (a) Öffnen Sie ein Terminal und maximieren Sie das Fenster  
 (b) Start des CLI erfolgt durch den Befehl **b15fcli**  
 (c) Die Navigation erfolgt durch &lt;Tab&gt;, die Pfeiltasten und &lt;Enter&gt; oder die Maus  
 (d) Mit &lt;Strg + c&gt; kann das Programm sofort verlassen werden

## Eigene Programme mit der B15F-Bibliothek schreiben

### Grundsätzliches
Verwendet wird die Bibliothekt *b15fdrv*.
Die wichtigste Klasse für die Steuerung des Board 15 ist [B15F](https://devfix.github.io/b15f/html/classB15F.html).  
Dort befindet sich auch eine Übersicht der verfügbaren Befehle.  

Hinweise zur Struktur (sind für die Verwendung nicht weiter wichtig):  
Die Header-Dateien sind global unter */usr/include/b15f/* installiert. Die *b15fdrv*-Bibliothekt befindet sich in dem Verzeichnis */usr/lib/* und die ausführbaren Programme (plotty, b15fcli) */usr/bin/*.

### Beispiele
In dem Verzeichnis [b15f/control/examples](https://github.com/devfix/b15f/tree/master/control/examples) (des Repositories) sind einige Beispiele für die Verwendung einzelner B15F Funktionen.  
Zu jedem Beispiel gehört eine *main.cpp* mit dem Quellcode und eine *Makefile*-Datei. Durch das Makefile wird beim Kompilieren und Linken die Bibliothek *b15fdrv* automatisch einbezogen.  
Das Beispiel muss durch Sie also nur mit **make** kompiliert und mit .**/main.elf** gestartet werden.

### Den B15F Treiber verwenden
Benötigt wird der B15F-Header:  
`#include <b15f/b15f.h>`  
und der Header für die plottyfile-Generierung, falls mit Kennlinien gearbeitet werden soll:  
`#include <b15f/plottyfile.h>` 

Für die Interaktion wird eine Referenz auf die aktuelle Treiberinstanz benötigt:  
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
*Wichtig*: Die Werte für `x` und `y` sind *uint16_t*, also keine Gleitkommazahlen. Stattdessen sind sie auf RefX und RefY bezogen.
