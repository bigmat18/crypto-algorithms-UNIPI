#include "Utils.h"

/**
 * CARATTERISTICHE:
 * 1. Il mittente non deve poter negare di aver inviato un messaggio.
 * 2. Il destinatario deve accertare l'identità del mittente.
 * 3. Il destinatario non deve poter sostenere che un messaggio m' != m è quello invatogli
 *    dal mittente.
 * Tutto questo verificato da una terza parte.
*/

/////////////////////////////////////////////
// PROTOCOLLO 1 (messaggio in chiaro e firma)
int Signature1(int msg, int k_priv) {
    int f; // = D(m, k_priv)
    int m = msg; // Messaggio
    return; // <U, m, f> 
}

bool Verify1(int msg, int U, int f, int k_pub) {
    int value; // = C(f, k_pub)
    if(value == msg) {
        return true; // utente verificato
    } else {
        return false; // utente non verificato
    }
}
/**
 * Con questo protoccolo usiamo la chiave privata per firmare un messaggio
 * e poi il destinatario usa la chiave pubblica per verificare la firma visto che è
 * legata al messaggio. 
*/

/**
 * Altra nota importante, il dest non deve sapere nessuna informazioni privata
 * del mittente, quindi può anche essere un terzo a verificare l'autenticità della firma
*/

/**
 * Nonostante sia sicuro ed afidabile con questo protoccolo base m deve essere in chiaro
 * inoltre f sarà sicurò lungo >= di m quindi almeno il doppio della lungezza da spedire
*/

///////////////////////////////////////////////
// PROTOCOLLO 2 (messaggio m cifrato e firmato)
int Signature2(int m, int k_mitt_priv, int k_dest_pub) { // + CIFRATURA
    int f; // = D(m, k_mitt_priv)
    int crt; // = C(f, k_dest_pub)
    return; // <U, c>
}

int Verify2(int crt) { // + DECIFRATURA
    int f; // D(crt, k_dest_priv)
    int m; // C(f, k_mitt_pub)
    // Se si riesce ad ottenere m oltre che decifrare il messaggio
    // si verifica l'indentià dell'utente
    return;
}

/**
 * Se andiamo ad utilizzare l'RSA con <d> chiave privata e <e,n> chiave pubblica, nel caso di un U mittente
 * e V destinatario dobbiamo fare che nu <= nv perché risulti che f < nv e la firma possa essere cifrata correttamente.
 * 
 * Questo però fa si che se invece V diventa il mittente verso U non funzioni più con le stesse chiavi. Bisogna quindi
 * tenere delle coppie di chiavi separate per firma e cifratura.
 * 
 * Si stabilisce un H molto grande H = 2^{1024} con n < H per firma e n > H per cifratura
*/

/**
 * Supponiamo di avere un sistema dove un utente quando riceve un messaggio invia un ack di conferma messaggio ricevuto
 * Possibile attacco su questo protocollo: (utente V invia a U e X si mette in mezzo)
 * - V invia un crittogramma c = C(f, k_u_pub) a U
 * - X intercetta c e lo rispedisce a U, ma in questo momento U crede che ad inviare sia X
 * - U decifram f = D(c, k_u_priv) e verifica firma con chiave pubblica di X che darà un m' != m,
 *   il sistema invia un ack con f' = D(m', K_u_priv) e c' = C(f', k_x_pub) 
 * - X riceve ack, decifra c' ed ottiene f', verifica f' e trova m' a questo punto esegue
 *   D(m', k_x_priv) = D(C(f, k_x[pub]), k_x[priv]) = f
 *   verifica f con chiave pubblica di V e trova m
 * 
 * Per evitare ciò occorre che U blocchi l'ack automatico in caso di firma sbagliata
 * operazione molto costosta, quindi si mette la firma digitiale su un immagine del messaggio
 * ottenuta con hash
*/

///////////////////////////////////////////////////////
// PROTOCOLLO 3 (messaggio m cifrato e firmato in hash)
int Signature3(int m, int k_mitt_priv, int k_dest_pub) { // + CIFRATURA
    int h_m; // = h(m) hash del messaggio
    int f; // = D(h_m, k_mitt_priv)
    int c; // = C(m, k_dest_pub)

    return; //<U, c, f>
}

int Verify3(int c, int f, int k_mitt_pub, int k_dest_priv) { // + DECIFRATURA
    int m; // = D(c, k_dest_priv)
    int h_m; // = h(m)
    int f; // C(f, k_mitt_pub)

    if(f == h_m) {
        // utente autenticato
        return true;
    } else {
        // utente falso
        return false;
    }
}
/**
 * Richiede uno scambio di dati maggiore, ma l'incremento è trascurabile
*/

//////////////////////////
// CERTIFICATION AUTORITY
/**
 * Uno dei problemi dei sistemi tipo RSA è anche la sua forza, ovvero quello di avere una chiave pubblica che  debba prima 
 * essere chiesta all'utente (per esempio un sito web), questa operazione potrebbe essere soggetta ad attacchi
 * man-in-the-middle, dove te richiedi la key_pub ad un sito, qualcuno si mette in mezzo e ti manda la sua key_pub, a questo
 * punto la comunicazione è interrotta.
 * 
 * I sistemi di CA servono per evitare questo, infatti sono enti specializzati ed affidabili che garantiscono le chiavi pubbliche
 * appartengano effettivamente a chi dovrebbe essere. <utente, chiave pubblica>
 * 
 * La comunicazione a questo punto funziona che, un utente U prima di comunicare con V chiede la chiave pubblica alla CA, che gli risponde
 * con il certificato di V, visto che U conosce la key_pub di CA può verificare l'autenticità.
 * 
 * Questa operazione è costsa, quindi viene fatta solamente una prima volta, poi i vari utenti mantengono salvate le info delle varie
 * chiavi private in locale, in modo da non dover ogni volta richiederle.
*/

// PROTOCOLLO 4
int Signature_Enc_CA(int m, int k_mitt_priv, int k_dest_pub) {
    int h_m; // = h(m) cioè calcolo l'hash del messaggio
    int f; // = D(h_m, h_mitt_priv) calcolo la firma
    int c; // = C(m, k_dest_pub)
    return; // <cert_mitt, c, f>
}

int VerifyCA(int cert_mitt) {
    // Verifica del certificato cert_mitt
    // utilizzando la copia della chiave pubblica
}

int VerifySignature_Dec(int c, int f, int k_dest_priv, int k_mitt_pub) {
    int m; // D(c, k_dest_priv)
    int value; /// = C(f, k_mitt_pub)
    int h_m; // = h(m)
    if(value == h_m) {
        // verficata la firma
        return true;
    } else {
        // firma sbagliata
        return false;
    }
}