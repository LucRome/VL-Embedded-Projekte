# Exercise 1
Schreiben Sie einen generischen Kommandozeilenparser der Optionen in folgender Form parsen
kann:
* -x (Bool, wenn gesetzt wahr, sonst falsch. info ist in diesem Fall nullptr.)
* -xwert (Integer oder Zeichenkette)
* -x wert (Integer oder Zeichenkette)
* -x=wert (Integer oder Zeichenkette)
* Der auf x folgende Wert kann aus einem oder mehreren Zeichen inklusive Nummern bestehen.
* "x" ist nur ein beispielhafter Buchstabe