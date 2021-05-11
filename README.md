# Hinweise zu LightbeamToGdi

Im Folgenden wird die Bedienung des Programms LightbeamToGdi erläutert. Das Programm wurde im Sommersemester 2020 des Moduls GdI 2 an der Fachhochschule Südwestfalen erstellt. Es kann unter folgendem Link heruntergeladen werden: [https://github.com/Jomibe/LightbeamToGdi](https://github.com/Jomibe/LightbeamToGdi)

## Bedienung
In diesem Verzeichnis findest Du zwei Unterordner. Der Ordner `Testdaten (JSON)` enthält vorbereitete Rohdaten, welche im JSON Format vorliegen. Weiter unten wird die Erstellung eigener Rohdaten erläutert. Kopiere eine der Dateien `lightbeamData.json` in das Projektverzeichnis `LightbeamToGdi`, ersetze dabei ggf. vorhandene Daten. Im Anschluss muss das Programm kompiliert werden, sodass es ausgeführt werden kann. Unter Linux, bzw. macOS lautet das Kommando dafür beispielsweise `g++ main.cpp -o main`. Nachdem die Binärdatei des kompilierten Programms vorliegt, kann es ohne weitere Kommandozeilenparameter ausgeführt werden. Das Programm beendet sich nach kurzer Zeit und hinterlässt eine Datei `ausgabe.gdi`, welche die Graphen aus der JSON-Eingabedatei im GDI Format enthält. Das kann mit einem Texteditor geprüft und mit einem entsprechenden Darstellungsprogramm weiter untersucht werden.

### Erstellung eigener Testdaten
Lade Dir dazu das Firefox Add-On [Lightbeam](https://addons.mozilla.org/de/firefox/addon/lightbeam-3-0/) (Version 3) herunter. Nach der Installation findest Du das Icon oben rechts. Rufe die Statusseite über das Icon auf und besuche einige Seiten. Für jede Seite wird in der Statusansicht ein Kreis erstellt, für jede externe Ressource wird ein Dreieck erstellt. Nutzen zwei Webseiten dieselbe Ressource, werden beide Kreise mit demselben Dreieck verknüpft. Besuche ggf. noch ein paar Seiten und exportiere die Daten im Anschluss über den Button `Save Data`. Kopiere die Datei `lightbeamData.json` aus deinem Downloads Ordner in das Projektverzeichnis. 

## Erweiterte Features: Ausgaben für die Fehlersuche einschalten
Das Programm besitzt Funktionen zur Fehlersuche, mit welchen die Vorgänge genauer analysiert werden können. Diese können mit den Konstanten in den Zeilen 6 bis 9 der `main.cpp` aktiviert (1) und deaktiviert (0) werden.
