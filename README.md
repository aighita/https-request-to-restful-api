README - Client pentru Interacțiunea cu API-ul Bibliotecii

Un client C pentru interacțiunea cu un API al unei biblioteci online.
Clientul permite utilizatorilor să se înregistreze, să se autentifice, să acceseze biblioteca, să vizualizeze cărți, să adauge cărți, să șteargă cărți și să se delogheze.

Structura Fișierului
    - client.c: Codul sursă principal al clientului.
    - helpers.h: Fișier header pentru funcții ajutătoare.
    - requests.h: Fișier header pentru funcții de gestionare a cererilor HTTP.

Dependențe
    - Standard C Libraries: stdio.h, stdlib.h, unistd.h, string.h
    - Biblioteca de socket-uri: sys/socket.h, netinet/in.h, netdb.h, arpa/inet.h
    - Bibliotecă proprie: helpers.h, requests.h

Configurație
Adresa și portul serverului sunt configurate prin următoarele variabile globale:
char HOST[14] = "34.246.184.49";
int PORT = 8080;

requests.c conține implementările funcțiilor pentru generarea cererilor HTTP de tip POST, GET și DELETE.
Aceste funcții sunt utilizate pentru a crea și trimite cereri HTTP către server-ul specificat.
Structura Fișierului
    - compute_message: Funcție auxiliară pentru concatenarea liniilor într-un mesaj HTTP.
    - compute_post_request: Funcție pentru generarea unei cereri HTTP POST.
        Parametri:
            host: Adresa serverului.
            url: URL-ul resursei.
            content_type: Tipul conținutului (e.g., application/json).
            body_data: Datele care se trimit în corpul cererii.
            cookie: Cookie-uri (opțional).
            token: Token de autorizare (opțional).
    - compute_get_request: Funcție pentru generarea unei cereri HTTP GET.
        Parametri:
            host: Adresa serverului.
            url: URL-ul resursei.
            cookie: Cookie-uri (opțional).
            token: Token de autorizare (opțional).
    - compute_delete_request: Funcție pentru generarea unei cereri HTTP DELETE.
        Parametri:
            host: Adresa serverului.
            url: URL-ul resursei.
            body_data: Datele care se trimit în corpul cererii (opțional).
            cookie: Cookie-uri (opțional).
            token: Token de autorizare (opțional).

Codul client.c implementează un client pentru interacțiunea cu un API al unei biblioteci online,
oferind funcționalități precum înregistrare, autentificare, acces la biblioteca, gestionarea cărților și delogare.

Structura Generală
    Include Files:
        Biblioteci standard și de rețea necesare pentru manipularea socket-urilor și comunicarea cu serverul.
        Fișierele header helpers.h și requests.h pentru funcții auxiliare și gestionarea cererilor HTTP.
    Variabile Globale:
        HOST și PORT: Adresa IP și portul serverului.
    Funcția main:
        Diverse variabile pentru stocarea mesajelor, răspunsurilor și datelor utilizatorului.
        Deschide o conexiune la server.
        Un loop principal pentru gestionarea comenzilor utilizatorului.
        În funcție de comanda introdusă, execută acțiuni specifice, cum ar fi înregistrarea sau autentificarea.

Funcționalități Detaliate:

    Înregistrare Utilizator
    Utilizatorul este invitat să introducă un nume de utilizator și o parolă, care sunt trimise către server pentru înregistrare. Se construiește o cerere POST și se trimite serverului.

    Autentificare Utilizator
    Utilizatorul introduce un nume de utilizator și o parolă, care sunt trimise către server pentru autentificare. Se construiește o cerere POST și se trimite serverului.

    Acces Biblioteca
    După autentificare, utilizatorul poate cere accesul la biblioteca online prin trimiterea unei cereri GET către server.

    Vizualizare Cărți
    Utilizatorul poate vizualiza toate cărțile disponibile în bibliotecă prin trimiterea unei cereri GET.

    Vizualizare Detalii Carte
    Utilizatorul poate introduce un ID de carte pentru a vizualiza detalii specifice despre acea carte. Se trimite o cerere GET cu ID-ul specificat.

    Adăugare Carte
    Utilizatorul poate adăuga o carte nouă în bibliotecă, furnizând detaliile necesare (titlu, autor, gen, număr de pagini și editură). Se construiește și trimite o cerere POST cu aceste informații.

    Ștergere Carte
    Utilizatorul poate șterge o carte din bibliotecă furnizând ID-ul acesteia. Se construiește și trimite o cerere DELETE cu ID-ul specificat.

    Delogare
    Utilizatorul se poate deloga din sesiunea curentă prin trimiterea unei cereri GET. Token-ul și cookie-ul utilizatorului sunt eliberate.

    Închidere Conexiune și Eliberare Resurse
    Conexiunea socket este închisă și memoria alocată pentru diverse variabile este eliberată pentru a preveni scurgerile de memorie.
