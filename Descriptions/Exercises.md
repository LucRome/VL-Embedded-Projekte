# Exercise 1

## Description
Schreiben Sie einen generischen Kommandozeilenparser der Optionen in folgender Form parsen
kann:
* -x (Bool, wenn gesetzt wahr, sonst falsch. info ist in diesem Fall nullptr.)
* -xwert (Integer oder Zeichenkette)
* -x wert (Integer oder Zeichenkette)
* -x=wert (Integer oder Zeichenkette)
* Der auf x folgende Wert kann aus einem oder mehreren Zeichen inklusive Nummern bestehen.
* "x" ist nur ein beispielhafter Buchstabe

## Lexems
```
ID : '-'[A-Za-z]
Value : [A-Za-z0-9]+
Assign : '='|' '|''
```

### Automat
```
(0)--'-'-->(1)--[A-Za-z]-->(2)[ID]
 |
 |---[A-Za-z0-9]--(3)--else-->(4)[Value]
 | |_______________|
 |
 |---[=' ''']-----(5)[Assign]
```
## Grammar
```
cmds : assignment (' ' assignment)*
assignment
    : ID Assign Value
    | ID
    ;
```

* *Hier ist nur das Assignment wichtig
(Assignments werden bei der Übergabe schon getrennt)*
* *falls Leerzeichen in einem Argument vorkommen muss das nächste Argument betrachtet werden*
    * *-> Argumente so betrachten als wären sie ein String*