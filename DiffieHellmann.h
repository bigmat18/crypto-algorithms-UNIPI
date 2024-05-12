#include "Utils.h"

/**
 * Il cifrario di Diffie Hellman è un cifrario ibrido, dove un cifrario a chiave pubblica
 * viene usato per scambiare la chiave segreta che viene poi utilizzata per la comunicazione
 * tramite cifrario simmetrico. In sintesi vengono scambiate le chiavi in questo formato:
 * <Crsa(k[session], k[pub]), Cars(m, k[session])>
*/

/**
 * - Si condivide fra utente A e B la coppia <p, g> da usare come chiave pubblica
 *   p: intero molto grande, almeno un migliaio di bit
 *   g: generatore Z*_p
 * - A seleziona x < p casualmente e calcola X = g^x mod p e spedisce X a B in chiaro
 * - B seleziona x < p casualmente e calcola Y = g^x mod p e spedisce Y a A in chiaro
 * - A riceve Y e calcola k[sessione] = Y^x mod p = g^{xy} mod p
 * - A riceve X e calcola k[sessione] = X^x mod p = g^{xy} mod p
 * 
 * In questo modo la chive di sessione sarà uguale e verrà usata per lo scambio 
 * con algoritmo simmetrico
 */

/**
 * Se si volesse forzare l'algoritmo bisognerebbe risolvere il logaritmo discreto
*/

/**
 * Un altrnativa è usare una attacco MAN-IN-THE-MIDDLE (esempio con utente C)
 * - C genera una Z = g^x mod p
 * - Si frappone fra A e B e ad A al posto di Y manda Z, mentre a B al posto di X manda Z
 * - A questo punto comunica con entrambi 
 * 
 * Questa cosa si risolve con il sistema di certificati virtuali
*/
