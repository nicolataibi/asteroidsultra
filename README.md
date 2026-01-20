# Asteroids (Clone)

Questo progetto è un'implementazione del classico videogioco arcade "Asteroids", sviluppato in C utilizzando OpenGL per la grafica e `cglm` per le operazioni matematiche.

## 1. Storiografia del Gioco Originale

"Asteroids" è un videogioco arcade sviluppato da Atari Inc. e rilasciato nel novembre 1979. Progettato da Lyle Rains e Ed Logg, il gioco è diventato rapidamente uno dei titoli più popolari e influenti dell'età d'oro dei videogiochi arcade.

Sebbene il suo gameplay e il sistema di controllo siano stati influenzati da giochi precedenti come *Spacewar!* (sviluppato su macchine PDP), *Asteroids* stesso è stato un prodotto Atari. Il gioco si basava su un progetto incompiuto di Atari chiamato *Cosmos*, a volte riferito anche come *Planet Grab*.

Il concetto di gioco è semplice ma avvincente: il giocatore controlla una piccola astronave in un campo di asteroidi, con l'obiettivo di distruggere tutti gli asteroidi e i dischi volanti nemici che appaiono periodicamente. Gli asteroidi si rompono in pezzi più piccoli quando vengono colpiti, aumentando la sfida. La grafica vettoriale monocromatica, l'innovativo sistema di controllo (rotazione, propulsione, fuoco e iperspazio) e il gameplay frenetico hanno contribuito al suo enorme successo e alla sua duratura eredità.

"Asteroids" ha influenzato innumerevoli giochi successivi e rimane un punto di riferimento nella storia dei videogiochi, celebrato per la sua pura giocabilità e il suo design elegante.

## 2. Documentazione Teorica del Gioco

Questa implementazione mira a replicare l'esperienza di gioco originale, mantenendo i principi fondamentali:

*   **Gameplay Basato sulla Fisica:** L'astronave si muove con inerzia, richiedendo al giocatore di anticipare i movimenti e di gestire la propulsione e la rotazione. I proiettili viaggiano in linea retta.
*   **Distruzione Progressiva:** Gli asteroidi si dividono in frammenti più piccoli, aumentando il numero di bersagli e la densità del campo di gioco.
*   **Nemici Aggiuntivi:** I dischi volanti (UFO) introducono una minaccia aggiuntiva e un elemento di precisione nel tiro.
*   **Sistema di Punteggio:** Distruggere asteroidi e UFO conferisce punti, incoraggiando il miglioramento delle prestazioni.
*   **Vite e Iperspazio:** Il giocatore ha un numero limitato di vite e una funzione di "iperspazio" (teletrasporto casuale) che può essere usata per sfuggire a situazioni pericolose, ma con il rischio di apparire in un punto ancora più pericoloso.

L'obiettivo è fornire un'esperienza fedele all'originale, concentrandosi sulla reattività dei controlli e sulla chiarezza visiva degli elementi di gioco.

## 3. Documentazione Tecnica

Il progetto è strutturato per essere modulare e facile da comprendere, utilizzando librerie standard e pratiche di programmazione C.

### 3.1. Architettura del Progetto

*   **`src/`**: Contiene i file sorgente `.c` del gioco.
    *   `main.c`: Il punto di ingresso principale del programma, gestisce il ciclo di gioco e l'inizializzazione.
    *   `game.c`: Logica di gioco principale, gestione dello stato del gioco, aggiornamento delle entità.
    *   `entities.c`: Implementazione delle entità di gioco (astronave, asteroidi, proiettili, UFO) e della loro logica specifica.
    *   `input.c`: Gestione degli input da tastiera.
    *   `glad.c`: Implementazione del caricatore di funzioni OpenGL.
    *   `text.c`: Gestione del rendering del testo (es. punteggio, vite).
*   **`include/`**: Contiene i file header `.h` per le definizioni delle funzioni e delle strutture dati.
    *   `game.h`, `entities.h`, `input.h`, `text.h`: Header corrispondenti ai file `.c` in `src/`.
    *   `glad/glad.h`, `KHR/khrplatform.h`: Header generati da GLAD per OpenGL.
*   **`shaders/`**: Contiene i file degli shader GLSL.
    *   `shader.vs`: Vertex Shader.
    *   `shader.fs`: Fragment Shader.
*   **`vendor/`**: Contiene librerie di terze parti.
    *   `cglm/`: La libreria `cglm` per le operazioni matematiche vettoriali e matriciali (essenziale per la grafica 3D e le trasformazioni).
    *   `stb_truetype.h`: Libreria single-file per il caricamento e il rendering dei font TrueType.
    *   `PressStart2P-Regular.ttf`: Un font in stile pixel art, adatto al tema del gioco.
*   **`Makefile`**: Script per la compilazione e il linking del progetto.

### 3.2. Tecnologie Utilizzate

*   **Linguaggio di Programmazione:** C
*   **Grafica:** OpenGL (tramite GLAD per il caricamento delle funzioni)
*   **Matematica:** `cglm` (una libreria C per la matematica vettoriale/matriciale, ottimizzata per OpenGL)
*   **Gestione Font:** `stb_truetype`

### 3.3. Compilazione ed Esecuzione

Per compilare ed eseguire il gioco, assicurati di avere un compilatore C (come GCC) e le librerie OpenGL/GLU/GLUT (o equivalenti) installate sul tuo sistema.

1.  **Naviga nella directory principale del progetto:**
    ```bash
    cd /home/nick/dev/c/asteroids
    ```
2.  **Compila il progetto usando `make`:**
    ```bash
    make
    ```
    Questo creerà un eseguibile chiamato `game` (o simile) nella directory principale.
3.  **Esegui il gioco:**
    ```bash
    ./game
    ```

---
*Nota: Questo README è stato generato automaticamente.*