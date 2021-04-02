# Snippets

## Remarks
* contains the snippets used to create the code pictures

* pictures are created using [carbon.now.sh](https://carbon.now.sh)
    * Color-Template: **VSCode**

## Code Snippets
**Funktionen mit variablen Parametern:** 
* ```
    int argc; //Anzahl der Argumente
    va_list params; //Zugriffshandle für die Parameter
    va_start(params, argc); //Zugriff vorbereiten

    //Alle Parameter durchlaufen
    for(int i = 0; i < argc; i++) {
        //Parameter holen (hier für int)
        // params wird automatisch eins weiterbewegt
        int arg = va_arg(params, int)

        ... //verwerten
    }

    va_end(params); //Zugriff abschließen
    ```
* Picture: (iFrame)
    <iframe
  src="https://carbon.now.sh/embed?bg=rgba%28171%2C+184%2C+195%2C+1%29&t=vscode&wt=none&l=text%2Fx-c%2B%2Bsrc&ds=true&dsyoff=20px&dsblur=68px&wc=true&wa=true&pv=25px&ph=29px&ln=false&fl=1&fm=Hack&fs=14px&lh=133%25&si=false&es=2x&wm=false&code=void%2520fkt%28char*%2520arg1%252C%2520...%2520%29%2520%257B%250A%2509int%2520argc%253B%2520%252F%252FAnzahl%2520der%2520Argumente%250A%2520%2520%2520%2520va_list%2520params%253B%2520%252F%252FZugriffshandle%2520f%25C3%25BCr%2520die%2520Parameter%250A%2520%2520%2520%2520va_start%28params%252C%2520argc%29%253B%2520%252F%252FZugriff%2520vorbereiten%250A%250A%2520%2520%2520%2520%252F%252FAlle%2520Parameter%2520durchlaufen%250A%2520%2520%2520%2520for%28int%2520i%2520%253D%25200%253B%2520i%2520%253C%2520argc%253B%2520i%252B%252B%29%2520%257B%250A%2520%2520%2520%2520%2520%2520%2520%2520%252F%252FParameter%2520holen%2520%28hier%2520f%25C3%25BCr%2520int%29%250A%2520%2520%2520%2520%2520%2520%2520%2520%252F%252F%2520params%2520wird%2520automatisch%2520eins%2520weiterbewegt%250A%2520%2520%2520%2520%2520%2520%2520%2520int%2520arg%2520%253D%2520va_arg%28params%252C%2520int%29%250A%250A%2520%2520%2520%2520%2520%2520%2520%2520...%2520%252F%252Fverwerten%250A%2520%2520%2520%2520%257D%250A%250A%2520%2520%2520%2520va_end%28params%29%253B%2520%252F%252FZugriff%2520abschlie%25C3%259Fen%250A%257D"
  style="width: 551px; height: 422px; border:0; transform: scale(1); overflow:hidden;"
  sandbox="allow-scripts allow-same-origin">
</iframe>

