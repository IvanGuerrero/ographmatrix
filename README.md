# ographmatrix
Oriented Graph via Adjacency Matrix

Il progetto prevede la creazione di una classe templata che implementa un grafo orientato, costituito da un insieme di nodi e archi orientati. 
Le classi presenti nel nostro progetto sono le seguenti:
•	graph.h : sarebbe la nostra classe templata (principale)
•	main.cpp : contiene i vari test di tutti i metodi della clase graph.h 
•	voce.h  e voce.cpp : di supporto per  testare la classe templata con tipi più complessi.
Struttura di progettazione
È stata presa in considerazione la restrizione di non poter usare liste o strutture a lista.
La struttura prevista è suddivisa in due parti:
1.	Array 1-D allocati dinamicamente :  contiene l’insieme dei nodi rappresentati da un generico identificativo. Questa struttura non mantiene l’ordine e ogni nodo inserito avrà il suo corrispettivo indice.
2.	Array 2-D allocati dinamicamente: è una struttura dati che rappresenta la matrice di adiacenza del grafo. 

•	La matrice di adiacenza è del tipo booleana ovvero gli archi mettono in relazione due nodi creando un collegamento tra loro. Tale matrice sarà presa in considerazione per la verifica dell’esistenza di un arco tra due nodi;

•	Si appoggia all’array dinamico dei nodi, ogni volta che si inserisce l’n-esimo nodo viene “automaticamente” creata la matrice di adiacenza con dimensione n, mentendo gli stessi dati della matrice n-1 e aggiungendo una riga e una colonna (riga e colonna in fondo) inizializzata di default a false ovvero che non contiene archi;

•	Per l’aggiunta di un arco si prevede l’utilizzo dell’array dinamico dei nodi che servirà per ottenere gli indici riga e colonna sulla quale si andrà a settare il valore , nella matrice, in true.

Descrizione classe graph.h

La claasse graph è implementata sul tipo T in quanto deve avere la possibilità di contenere un qualsiasi dato di tipo generico(int, char, float, string, ecc), e sul funtore E che permette di stabilire l’uguaglianza fra due elementi generici.
Metodi

Oltre ai metodi essenziali della classe é stato richiesto di implementare altre funzionalità per l'utilizzo della classe:

•	I metodi void addNode(T node) e void removeNode(T node), che prendono in input un nodo generico, prima che eseguano tali richieste verificano l’esistenza del nodo con il metodo exists che solleverà le eccezioni, “graph_node_already_existing_exception“ e “graph_node_not_existing_exception”, per avvisare che non si può aggiungere un nodo esistente o rimuovere un nodo inesistente.

I due metodi prevedono una nuova allocazione di memoria dinamica di dimensione n+1 per l’aggiunta di un nodo e di dimensione n-1 per la rimozione di un nodo. Viene fatta tale considerazione anche per la nostra matrice di adiacenza. Ricopiando la stessa struttura dati aggiungendo/togliendo lo specifico nodo.

•	I metodi void addArc(T node1, T node2) e void removeArc(T node1, T node2), che prendono in input due nodi generici, prima che eseguano tali richieste verificano l’esistenza dell’arco con il metodo hasEdge che solleverà le eccezioni, “graph_arc_already_exist_exception” e “graph_arc_not_exist_exception”, per avvisare non si può aggiungere un arco già esistente o rimuovere un arco non esistente. I due metodi agiscono sulla matrice di adiacenza booleana settando a true/false i corrispettivi archi. Per avere gli indici riga e colonna si appoggiano sulla struttura dati dell’array dinamico di nodi facendo una richiesta tramite il metodo indexNode che ritorna l’indice del corrispettivo nodo;

•	I metodi bool exists(T node) e bool hasEdge(T node) servono per interrogare il grafo per sapere se esiste un nodo oppure se una coppia di nodi è connessa il loro ritorno è booleano perché ritorno true/false in base all’esito della richiesta;

•	È stato implementato un const_iterator di tipo forward è stata fatta perché, oltre ad essere richiesta dalla specifica, permette di accedere ai nodi contenuti all’interno della classe evitando che vengano modificati. Inoltre tali nodi vengono visitati in ordine di inserimento.
