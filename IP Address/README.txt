In cadrul sursei se gasesc 2 structuri folosit:
lista - fiind lista de ip-uri
ip_work - fiind structura ce contine ip_1 si ip_2 din problema
Amandoua structuri contin alte elemente in plus necesare rezolvarii
problemei cu ajutorul codului din sursa
Task-urile au fost organizate in functii pentru citirea mai usoara
a fiecarei rezolvari in parte

Task_0
Se foloseste functia printf pentru afisare

Task_1
Se afiseaza masca folosind tot printf

Task_2
Se afiseaza adresa de retea a lui ip_1
facandu-se si (&) pe bit intre masca si ip

Task_3
Se afiseaza adresa de broadcast a lui ip_1
facandu-se sau (|) pe bit intre masca si ip

Task_4
Am creat o functie separata ce intoarce
1 sau 0 pentru a verifica daca cele 2 ip-uri
fac parte din aceeasi retea
De asemenea functia e int pentru a returna 
o valoare 0 sau 1 pentru a rezolva task-ul 6
conform cerintei

Task_5
Se afiseaza ip1 in baza 16, resp ip2 in baza 8
folosindu-ne de proprietatile functiei printf (%x si %o)

Task_6
Folosindu-ne de valoarea returnata de task_4 
vom afisa raspunsul corespunzator, de asemenea
functia de verificare, daca 2 ip-uri fac parte din aceeasi
retea, este refolosita

Task_7
Din cauza modului cum e construit programul
se repeta afisarea celor 2 ip-uri, in consecinta
am creat o functie separata care e apelata de 2 ori
in loc sa avem 2 for-uri
Avem o functie ce creeaza si afiseaza cele 2 ip-uri 
in cod binar

Task_8
Acelasi lucru ca la task 7
Doar ca avem o alta functie care afiseaza
in baza 32
Toata ideea este de a imparti (/) numarul la 32
si de a face modulo (%) tot pe el