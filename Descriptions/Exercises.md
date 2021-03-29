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