#include "Utils.h"

/**
 * Hash PROPRIETÀ:
 * - Computazionalmente facile: facile da calcolare per ogni elemento x in X f(x)
 * - One-way: difficile da ricavare x da y quindi difficile fare f(y) = x
 * - Collision resistence: computazionalmente difficile determinare una coppia x', x'' t.c f(x') = f(x'')
*/

/**
 * buffer: vengono caricati inizialmente valori fissi e pubblici
*/
void SHA1(u_int32_t* buffer, u_int64_t* msg) {
    int padding;
    msg += padding; // Il messaggio viene concatenano con seq. di padding per raggiungere multiplo di 512

    /**
     * Nel corso dei vari cicli si combinano il contenuto dei registri
     * con blocchi di 32bit provenienti dal msg 
    */
}

/**
 * Per estendere il numero di bit dell'immagine basta andare a concatenrare i valori
 * che si ottengono con h(D_{i-1})
*/

/**
 * IDENTIFICAZIONE:
 * Usiamo le funzioni hash, infatti quando un utente U cerca di entrare in un sistema vengono generati due
 * valori S e G, entrambi salvati nel file delle password, S(seme) è una seq casuale, Q è l'immagine di
 * S + password. Quando viene richista l'identificazione, si prende S dal file, si concatena alla password
 * inviate e se uguale a G bella per lui. Vediamo un protocollo simile a RSA:
 * 
 * 1. U chiede di accedere ad S. S generea r < n e lo invia ad U in chiaro.
 * 2. U calcola f = r^d mod n con chiave privata ed invia f a S.
 * 3. S verifica correttezza calcolando f^e mod n e verifica sia uguale ad r.
 * 
 * Questo è un RSA all'icontrario.
*/

/**
 * AUTENTICAZIONE:
 * Si basa sull'invio del MAC insieme al messaggio (o crittogramma), il MAC = A(m, k).
 * Quindi si invia la coppia <C(m,k'), A(m,k)> con m il messaggio e k' la chiave del cifrario, mentre k una chiave
 * usata soltanto per l'operazione di autenticazione.
 * Qaundo arriva il destinarario ha sia A che m che k (sapendo chi si aspetta di avere), quindi vede se i risulati coincidono
 * e nel caso autentica il dest, in caso contrario o k diversa o messaggio discordante.
 * 
 * Per A si usa spesso funzioni hash one-way A(m, k) = h(m*k) in questo modo k viaggia all'interno del mac ma non può 
 * essere ricavato data la natura "one-way" dell'hash
*/