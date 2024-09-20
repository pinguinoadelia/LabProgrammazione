# LabProgrammazione Gianmarco De Laurentiis 

# Tipo di elaborato

Lista della spesa

# Panoramica del Progetto

L'applicazione "Shopping List" è un programma scritto
in C++ che permette agli utenti di creare e gestire
una lista della spesa in maniera semplice ed efficace.
Gli utenti possono inserire nuovi articoli,
contrassegnarli come acquistati o ancora da comprare
e rimuoverli dalla lista quando non più necessari.

# Caratteristiche Essenziali

Inserimento di articoli nella lista della spesa 
con possibilità di specificare la quantità e la categoria
(es. alimentari, pulizia, ecc.).

Contrassegno degli articoli come "acquistati" o  
"da acquistare" per monitorare lo stato di ogni oggetto.

Rimozione degli articoli completati o non più necessari dalla lista.

Visualizzazione dei soli articoli ancora da acquistare per facilitare lo shopping.

Stampa della lista completa con informazioni su articoli
già acquistati e su quelli mancanti.

# Struttura del Sistema

Classe Item: Modella un singolo articolo della lista 
della spesa. Ogni articolo è caratterizzato da attributi 
come nome, categoria, quantità e stato di acquisto 
(completato o non acquistato). Questo consente una gestione 
accurata degli oggetti nella lista.

Interfaccia Observer: Definisce le modalità con cui gli osservatori
monitorano le modifiche nella lista della spesa. 
Grazie a questa interfaccia, ogni volta che ci sono cambiamenti, 
gli osservatori vengono informati tempestivamente.

Interfaccia Subject: Stabilisce il meccanismo per la 
gestione degli osservatori. Include i metodi per aggiungere 
(addObserver), rimuovere (removeObserver) e notificare gli osservatori in caso di 
modifiche alla lista. (notifyObservers).

Classe ShoppingList: Questa classe implementa l’interfaccia Subject
e rappresenta una vera e propria lista della spesa. 
Contiene gli articoli (istanze di Item), le categorie e 
gestisce gli osservatori. Offre metodi per aggiungere, 
rimuovere e aggiornare lo stato degli articoli, 
e per visualizzare o stampare la lista degli articoli rimanenti.

Classe User: Rappresenta l’utente che gestisce
una o più liste della spesa, implementando l’interfaccia 
Observer. Consente di aggiungere e rimuovere liste e 
ricevere notifiche quando una lista viene modificata, come l’aggiunta 
di nuovi articoli o il cambiamento dello stato di un oggetto.

# Design Pattern

l design pattern utilizzato per l'implementazione 
dell'applicazione è l'Observer Pattern. Questo pattern 
permette di stabilire una relazione tra oggetti in modo che, 
quando un oggetto osservato subisce un cambiamento, 
tutti gli osservatori registrati vengono automaticamente notificati. 
In questo caso, consente agli utenti di ricevere aggiornamenti in tempo reale 
su eventuali modifiche alle liste della spesa, 
migliorando l'interazione e la reattività del sistema.

