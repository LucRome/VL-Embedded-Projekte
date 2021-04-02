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
Schreiben Sie eine eigene minimale printf Implementierung. Sie soll folgende Ausgabefunktionen erfüllen:
* %d für signed int
* %u für unsigned int
* %c für ein einzelnes Zeichen
* %s für eine Zeichenkette
* %x für die Ausgabe in Hexadezimalform (0xaf)
* %b für die Ausgabe in Binärform (0b10101).
* %% für die Ausgabe des Prozentzeichens
Für x und b gilt, dass beide keine führenden Nullen darstellen und negative Zahlen nutzen das Zweierkomplement.
Signatur:
´´´char* Printf(char* dst, const void* end, const char* fmt, ...);´´´
Als Rückgabe erfolgt das nächste schreibbare Zeichen in **dst**. Der String ist an der Stelle **dst** null-terminiert. **end** ist das letzte beschreibbare Zeichen im Buffer.