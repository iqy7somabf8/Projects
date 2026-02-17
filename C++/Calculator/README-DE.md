# Calculator.cpp Dokumentation
  Diese README dient als Dokumentation dafür, wie der Taschenrechner funktioniert. Sie enthält Beispiel-Eingaben, damit du verstehst, wie man Aufgaben richtig eingibt, und zeigt außerdem die Änderungen der vorherigen Versionen.

## Tutorial
  Schlüsselwörter: '^' steht für Potenzrechnung | 's' steht für die Berechnung der Quadratwurzel

  Beispiel-Eingabe:
  213*5+23 (funktioniert auch mit Leerzeichen)
  Beispiel-Ausgabe:
  Result: 1088
  
  Du kannst auch „1“ oder „2“ eingeben. „Help“ zeigt ein kleines Tutorial zur Nutzung des Taschenrechners an. Mit „Debug“ kannst du zusätzliche Informationen anzeigen lassen, die zeigen, wie das Programm die Eingabe verarbeitet.

## Patch Notes
  28/01/25 | V1
  -Erste Version. Unterstützt mehrere Operationen in einer Eingabe sowie einfache Operatoren (+, -, /, *)

  30/01/25 | V1.1
  -Unterstützung für Potenzrechnung hinzugefügt (z.B. quadrieren, hoch drei und höher)
  -Menü optisch verbessert
  -Umschaltbare Option für komplexere Berechnungen hinzugefügt (z.B. Potenzen und Quadratwurzel)
  -Quadratwurzel wird bald hinzugefügt

  03/02/25 | V1.2
  -Unterstützung für Quadratwurzel hinzugefügt (Beispiel: s144 | Ergebnis: 12), wobei 's' das Schlüsselwort ist
  -Code etwas aufgeräumt und leicht optimiert. Es gibt immer noch zu viele for-Schleifen, daher macht es wahrscheinlich keinen großen Unterschied
  -Die Funktion validateInput im for-Schleifen-Bereich überarbeitet, damit sie keine unnötigen oder merkwürdigen Prüfungen mehr durchführt

  28/05/25 | V1.3
  -Angefangen, die komplette Berechnungspipeline zu überarbeiten, um sie effizienter und leichter anpassbar zu machen. Aktuell kann noch nichts berechnet werden

  17/02/26 | V1.4
  -Berechnungspipeline komplett überarbeitet
  -Die 5+ verschiedenen for-Schleifen entfernt und durch eine zentrale Schleife ersetzt
  -evaluateInput und alle Berechnungsfunktionen an das neue Pipeline-Design angepasst
  -Die complexCalculations-Bool-Option im Menü entfernt, da das neue Design komplexe Berechnungen nur ausführt, wenn sie tatsächlich vorkommen. Alle Hinweise auf complexCalculation wurden archiviert und werden wahrscheinlich in V1.4 vollständig entfernt
  -Eine umschaltbare Debug-Option hinzugefügt. Wenn sie aktiviert ist, werden hilfreiche Daten ausgegeben, die zeigen, wie das Programm die Aufgabe verarbeitet

## Persönliche Anmerkung
  Mir ist bewusst, dass der große Zeitabstand zwischen 1.3 und 1.4, fast ein Jahr, etwas seltsam wirkt. Das Leben kam dazwischen und ich hatte einfach keine Zeit mehr, an meinen persönlichen Projekten weiterzuarbeiten. Außerdem war ich mit einem Projekt für meinen IT-Unterricht beschäftigt. Dabei sollte ich eine Android-App mit einem älteren App-Framework erstellen, nämlich MIT App Inventor.