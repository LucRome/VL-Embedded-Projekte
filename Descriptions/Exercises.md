# Notes
* kein new/malloc
* aber: 
    * **Placement-new erlaubt**
    * [Erklärung von GeeksForGeeks](https://www.geeksforgeeks.org/placement-new-operator-cpp/#:~:text=Placement%20new%20is%20a%20variation%20new%20operator%20in,and%20construct%20an%20object%20in%20the%20passed%20memory.)
    

# Exercise 1
Schreiben Sie einen generischen Kommandozeilenparser der Optionen in folgender Form parsen
kann:
* -x (Bool, wenn gesetzt wahr, sonst falsch. info ist in diesem Fall nullptr.)
* -xwert (Integer oder Zeichenkette)
* -x wert (Integer oder Zeichenkette)
* -x=wert (Integer oder Zeichenkette)
* Der auf x folgende Wert kann aus einem oder mehreren Zeichen inklusive Nummern bestehen.
* "x" ist nur ein beispielhafter Buchstabe

## Literale/"Konstrukte":
```
Letter: [A-Za-z]
Number: [0-9]
Variable: '-'Letter
Equals: '=' | ' ' //' ' can also occur in an arg (although it shouldn't)
Value: (Letter | Number)*
```

## Grammatik/Aufbau:
```
correct 
    : arg_Var
    | arg_Var arg_Val
    ;

arg_Var
    : Variable
    | Variable Value
    | Variable Equals Value
    ;

arg_Val : Value;
```

## Other Notes:
* **Needs to catch when there are Spaces inside an arg!!!** 
* Problems when there is a char* created behind the last arg but not used for the args (segmentation fault)
* TODO: Unittests


# Exercise 2

## REMOVE printf()!!!

Schreiben Sie eine eigene minimale printf Implementierung. Sie soll folgende Ausgabefunktionen erfüllen:
- [x] %d für signed int
- [x] %u für unsigned int
- [x] %c für ein einzelnes Zeichen
- [x] %s für eine Zeichenkette
- [x] %x für die Ausgabe in Hexadezimalform (0xaf)
- [x] %b für die Ausgabe in Binärform (0b10101).
- [x] %% für die Ausgabe des Prozentzeichens

Für x und b gilt, dass beide keine führenden Nullen darstellen und negative Zahlen nutzen das Zweierkomplement.
Signatur:
```char* Printf(char* dst, const void* end, const char* fmt, ...);```
Als Rückgabe erfolgt das nächste schreibbare Zeichen in **dst**. Der String ist an der Stelle **dst** null-terminiert. **end** ist das letzte beschreibbare Zeichen im Buffer.

* **Verhalten bei zu falschen Arugumenten**
    * zu wenig:
        * keine Ausgabe an der Stelle wo die Argumente fehlen
    * Falscher Typ:
        * wird zu dem richtigen Typ gecastet -> eventuell segmentation fault

## Zweierkomplemente:
* **Berechnung/Kontrolle mit Windows Rechner:**
    * Bitzahl auf "DWORD" einstellen *(mittig über Bedienfeld)*
* **bei Binär:**
    * basierend auf dem Zahlenkreis [(siehe)]](http://informatik-stoffsammlung.de/index.php?page=zweierkomplementdarstellung)
    * umwandlung einer negativen Zahl in die zugehörige positive Zahl
        * Im Bild bspw. -1 -> 15; -4 -> 12; *(x -> y)*
    * Rechenregel: 
        ```
        y = Max_unsigned + 1 - |x|    (für x < 0)
        y = x                       (für x >= 0)
        ```
    * Umwandlung in binär: (hier nicht nötig, einfache maskierung genügt)
        * Bsp.:
        ```
        13 / 2 = 6 R=1 ▲
        6 / 2 = 3 R=0  |
        3 / 2 = 1 R=1  |
        1 / 2 = 0 R=1  |
        ```
* **Hexadezimal:**
    * Negative Zahl in zug. pos. Zahl umwandeln (sh. bei Binär)
    * Ausgabe mit Maskierung
        * aber 4 Bitzahlen für eine Hex-Zahl

## Funktionen mit variablen Argumenten:
* Bsp.:
    * ```void fkt(const char* arg1, ...)```
    * hier wichtig: **´´´...´´´**
* Erklärungen:
    * Vorlesungsfolien:
        * Vorlesung 4 (es-04.pdf)
        * Folie 57 (Pdf S. 29)
    * Web:
        * [willemer.de](http://www.willemer.de/informatik/cpp/parameter.htm)
            * unter: "Variable Anzahl von Parametern"
        * [wikibooks.org](https://de.wikibooks.org/wiki/C%2B%2B-Programmierung/_Weitere_Grundelemente/_Prozeduren_und_Funktionen)
            * unter: "Funktionen mit beliebig vielen Argumenten"

* Zugriff:
<iframe
src="https://carbon.now.sh/embed?bg=rgba%28171%2C+184%2C+195%2C+1%29&t=vscode&wt=none&l=text%2Fx-c%2B%2Bsrc&ds=true&dsyoff=20px&dsblur=68px&wc=true&wa=true&pv=25px&ph=29px&ln=false&fl=1&fm=Hack&fs=14px&lh=133%25&si=false&es=1x&wm=false&code=void%2520fkt%28char*%2520arg1%252C%2520int%2520argc%252C%2520...%2520%29%2520%257B%250A%2520%2520%2520%2520va_list%2520params%253B%2520%252F%252FZugriffshandle%2520f%25C3%25BCr%2520die%2520Parameter%250A%2520%2520%2520%2520va_start%28params%252C%2520argc%29%253B%2520%252F%252FZugriff%2520vorbereiten%250A%2520%2520%2509%2509%2509%2509%2509%252F%252F%255E%2520letzter%2520benannter%2520parameter%250A%250A%2520%2520%2520%2520%252F%252FAlle%2520Parameter%2520durchlaufen%250A%2520%2520%2520%2520for%28int%2520i%2520%253D%25200%253B%2520i%2520%253C%2520argc%253B%2520i%252B%252B%29%2520%257B%250A%2520%2520%2520%2520%2520%2520%2520%2520%252F%252FParameter%2520holen%2520%28hier%2520f%25C3%25BCr%2520int%29%250A%2520%2520%2520%2520%2520%2520%2520%2520%252F%252F%2520params%2520wird%2520automatisch%2520eins%2520weiterbewegt%250A%2520%2520%2520%2520%2520%2520%2520%2520int%2520arg%2520%253D%2520va_arg%28params%252C%2520int%29%250A%250A%2520%2520%2520%2520%2520%2520%2520%2520...%2520%252F%252Fverwerten%250A%2520%2520%2520%2520%257D%250A%250A%2520%2520%2520%2520va_end%28params%29%253B%2520%252F%252FZugriff%2520abschlie%25C3%259Fen%250A%257D"
style="width: 551px; height: 422px; border:0; transform: scale(1); overflow:hidden;"
sandbox="allow-scripts allow-same-origin">
</iframe>

## Notes
* **TODO:**
    * [ ] catch SEGFAULT (see: main)
    * [x] bei Funktionen Funktionen wo die zwei Specifier chars durch mehr chars ersetzt werden:
        * wenn die Ersetzung aus Platzgründen nicht komplett durchgeführt werden kann, die Ersetzung auch nicht durchführen und die zugrunde liegenden Specifier Strings noch in dem zurückzugebenen char* lassen

