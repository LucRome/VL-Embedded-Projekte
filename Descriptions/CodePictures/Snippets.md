# Snippets

## Remarks
* contains the snippets used to create the code pictures

* pictures are created using [carbon.now.sh](https://carbon.now.sh)
    * Color-Template: **VSCode**

## Code Snippets
**Funktionen mit variablen Parametern:** 
* ```
    void fkt(char* arg1, int argc, ... ) {
        va_list params; //Zugriffshandle für die Parameter
        va_start(params, argc); //Zugriff vorbereiten
                        //^ letzter benannter parameter

        //Alle Parameter durchlaufen
        for(int i = 0; i < argc; i++) {
            //Parameter holen (hier für int)
            // params wird automatisch eins weiterbewegt
            int arg = va_arg(params, int)

            ... //verwerten
        }

        va_end(params); //Zugriff abschließen
    }
    ```
