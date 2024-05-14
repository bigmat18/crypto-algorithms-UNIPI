#include "Utils.h"

/**
 * SSL:
 * Utilizzato per garantire sicurezza nell'HTTP. Utente U vuole accedere via internet al servizio S
 * SSL garantisce condidenzialità, usa cifrario asimmetrico per scambio di chiavi + cifrarsio simmetrico
 * per scambio messaggi + garantisce autenticazione con CA e MAC.
 * Organizzato come
 * - SSL Record: livello più basso connesso al livello di trasposto, organizzazione di come si spediscono i pacchetti
 * - SSL Handshake: interfaccia all'alpplicazione sovrastante e con CA, negoziare algoritmi e stabilire chiavi per algoritmi e MAC
 *
 * In sintesi handshake crea canale sicuro e record fa stransitare i messaggi.
 * Client ==> Server / Client <== Server
 *
 * Steps:
 * 1. (Client hello)            ==> richiesta di creazione di connessione, si specifica:
 *                                  - versione protoccolo SSL usata da U
 *                                  - elenco di algoritmi di compressione supportati da U
 *                                  - lista dei cifrari e meccanismi di autenticazione supportati da U
 * 2. (Server hello)            <== Il server seleziona versione, algorimi e cifrari ed invia tutto ad U
 * 3. (Invio certificato)       <== S si autentica mandato il suo CA e può richiedere, nel caso servisse
 *                                  il CA del utente. Se U ed S non si affidano alla stessa CA (causa gestione ad albero)
 *                                  S invia seq. di caratteri in accordo con CA che li ha firmati.
 * 4. (Servver hello done)      <== Manda il messaggio che scandisce la fine degli accordi sui parametri crittografici
 * 5. (Auth del sistema)        ==> U verifica che il certificato non sia scatudo, che la CA sia fra quelle "fidate"
 *                                  e che la firma sia autentica
 * 6. (invio pre-master secret  ==> U costruisce un pre-master secret, costituita da seq. di bit casuali. la seq. viene cifrate con
 *    e costruz master secret)      i sistemi accordati e viene spedita ad S. U poi calcoleà il master secret che sarà combinato con stringhe note
 *                                  e byte casuali presenti sia in client hello che server hello, dove gli viene applicata una hash one-way
 * 7. (recez. pre-master secret --- Il sistema decifra il messaggio con pre-master secret e calcola il master secret
 *     e costruz. master secret)    come ha fatto l'utente nel passo prima
 * 8. (invio certificato opz.)  ==> Se all'utente viene richiesto invia il certificato (richiesto nel punto 3) insieme ad altre info
 *                                  firmate con la chiave privata e che contengono anche master-secret. S verificherà il certificato.
 * 9. (messaggio fine)          <=> Primo messaggio ad essere protetto con master secret, messaggio prima costrutito da U e spedito da S
 *                                  e poi viceversa. Si concatena master, tutti i messaggi scambiati, l'handshake, e l'identita del mittente
 *                                  stringa poi gli veiene applicata SHA e MD5
 * 
 * Nei punti 6 e 7 abbiamo che sia U che S hanno le seq. casuali di U e S + il pre-master con cui costruiscono
 * lo stesso master secret da usare poi.
 * 
 * Tutto questo verrà poi utilizzato da SSL record che divide i dati in blocchi, li numera, li comprime, li autentica con il MAC
 * cifrati simmetricamente e poi trasmessi con protocolli sottostanti.
 * Destinatation verifica integrità con MAC, decomprime e riassembra i blocchi in chiaro.
 * 
 * 
 * Tutta questa comunicazione è sicura per diversi motivi:
 * - durante i messaggi di "hello" vengono create due seq. casuali che poi si usano durante la creazione
 *   del master secret che risulta così diverso per ogni connessione SSL. Questo impedisce ad un crittoanalista
 *   di riutilizzare i messaggi di handshake catturati sul canale
 * - SSL record numera in modo incrementale i blocchi auenticati con MAC. Questo consente di prevenire la modifica
 *   del blocco da parte di un crittoanalista attivo grazie al fatto che il MAC viene calcolato con immagine hash one-way
 *   di stringa ottennuta con: contenuto blocchi, numero del bocco nella seq. chiave del MAC, alcune stringhe note e fissate a priori.
 *   Tutto ciò cifrato insieme al messaggio, attacco difficile perché richiede chiave simmetrica.
 * - Canale immune a man-in-the-middle poiché il sistem S viene autentica e usa CA
 * - Anche l'utente viene autenticato, ciò garantisce che un utente sia effettivamente lui
 * - Le sequenze generate sono casuali e non prevedibile, ciò è cruciale per la sicurezza del canale SSL.
 */


/**
 * TLS:
 * - Protocollo Handshake: protocollo di scambio chiavi per stabile le chiami simmetriche condivise
 * - Protoccolo Record-layer: utilizza le chiavi condivise per cifrare ed autenticare la comunicazione.
 * 
 * Abbiamo: 
 * - Client C che possiede chiavi pubbliche pk1, pk2 ...
 * - Server S possiede coppia di chiave pubblica e pirvata x firma digitale pks, sks
 *   ed un Certificato digitale cert_s per pks
 * 
 * Passo 1: C invia ad S (con primo messaggio DH)
 *  - speficia gruppo G (Z*p o curva ellittica)
 *  - generatore g, oppure punto B e ordine
 *  - valore g^x, oppure punto xB calcolato con x intero random
 *  - un Nc (seq. casuale di bit)
 *  - info su cosa può sopportare
 *       
 * Passo 2: 
 *  - S completa protoccolo DH ed invia g^y o yB
 *  - S invia Ns
 *  - S calcola K = g^{xy} (oppure roba di curve ellittiche) ed estre le chiavi K (K's, K'c, K's, K'c)
 *    per cifrature autenticata
 *  - S invia propria chiave pubblica pks, cert_s, firma calcolata con sk_s
 * tutti i dati cifrati con K's
 * 
 * Passo 3:
 *  - C calcola K = g^{xy} (o corrispettivo curve ellittiche) e deriva chiavi K (K's, K'c, Ks, Kc)
 *  - Usa K's per recuperare pk_s, cert_s e firma
 *  - Verifica cert_s
 *  - Verififca firma
 *  - Calcola il MAC dei messaggi di handshake scmabiati e lo inva
 * 
 * Se tutto va a buon fine si passa al Record Layer dove:
 * - C usa Kc per cifrare messaggi per S
 * - S usa Ks per cifrare i messaggi per C
*/