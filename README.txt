               _/  _/
              /   /
             /   /
  __________/___/______________________________________ 
 /          |                                          \
|           |                                           |
|           |                                           |
|___________|                                           |___
 \                 _____               _____           /____
  \               |     |             |     |         /
   \______________|_____|_____________|_____|________/

                        Gara din Hogsmeade
    Tema pentru care am lucrat reprezinta o programa de optimizare 
a unei gari din Hogsmeade prin implementarea unor cerinte date 
de autoritatile garii.
    Pentru a functionarea corecta a subprogramelor la prima etapa 
am implementat 3 functii precum: open_train_station prin care am 
deschis o gara alocandui memorie structurei de date TrainStation, 
dupa care am alocat memorie unei serii de platforme pozitionandule 
fiecaruia pointerul catre NULL. Funtia secundara este close_train_station 
care dezaloca memoria pentru fiecare vagon, locomotiva, platforma si 
in final si pentru statie. A treia functie este show_existing_trains 
care la randul sau verifica corectitudinea implementarii tuturor 
funtiilor prin afisarea lor intr-un fisier printr-un format special.

    Dupa implementarea celor 3 funtii de mai sus am trecut la cerintele 
principale ale codului. In primul rand in funtia arrive_train verificam 
daca instatie exista sau nu locomotiva, si daca aceasta nu exista eu o 
adaugam.

    In continuare, in functia leave_train verificam daca exista o 
locomotiva, si daca aceasta exista verificam totodata si prezenta vagoanelor.
Dupa care vagon cu vagon eliberam meoria ocupata de aceste si intr-un final 
si memoria locomotivei.

    Conform functiei add_train_car am verificat daca intr-o statie exista 
sau nu locomotiva dupa care parcurgeam trenul pana la ultimul vagon 
si cand ajungeam la acesta inseram un nou vagon cu o greutate oferita de 
functia pe care o primeam.

    Funtia remove_train_cars avea ca cerinta eliminarea tuturor vagoanelor 
cu o anumita greutate, deci, parcurgand trenul vagon cu vagon, 
verificam daca vagonul din fata mea este cel pe care trebuie sa-l 
sterg sau nu, si daca il gaseam, cream o copie pe el, uneam vagonul 
la care sunt cu vagonul cu 2 pozitii mai in fata dupa care eliberam 
memoria vagonului salvat in copie.

    Funtia move_train_cars avea ca obiectiv mutarea a unui numar de 
vagoane de pe o pozitie anume dintr-o statie in alta pe o alta pozitie 
anume. Astfel, in primul rand am verificat daca numarul de vagoane pe 
care vreau sa le iau plus pozitia de inceput de unde trebuia sa iau 
depaseste sau nu limita numarului de vagoane existente. Desigur 
daca puteam face acest lucru verificam imediat daca le voi putea 
adauga in cealalata statie pe o pozitie anume. Daca ambele conditii 
erau indeplinite atunci pointam catre primul vagon pe care imi doaream 
sa-l mut un start pointer si desigur un alt finish pointer catre ultimul 
vagon de sectiune, dupa care uneam vagonul din fata pointerului de start 
cu vagonul de dupa pointerul de finish. Dupa care toate aceste-a le-am 
adaugat in statia secundara conform uor conditii: daca vreau sa le pun 
pe pozitia 1 sau pe oricare alta.

    In subprogramul find_express_train am implementat un cod care are 
cea mai mare diferenta dintre puterea locomotivei si greutatea trenului, 
rezultatul fiind cel mai rapid tren dintr-o statie.

    Deoarece funtia find_overload_train imi garanta unicitatea solutie, 
asta insemna ca in toata statia exista un singur tren incarcarea caruia 
depasea puterea locomotivei, deci eu calculam masa la toata trenul 
dupa care verificam daca aceasta este sau nu mai mare decat puterea 
locomotivei. Daca greutatea depasea limita inseamna ca trenul a fost 
gaisit si returnam peronul pe care acesta se afla;

    Pentru functia find_optimal_train am trebuit sa caut treul in care 
diferenta dintre puterea locomotivei si greutatea trenului este cea mai mica, 
astfel salvand de fiecare data cand gaseam o diferenta mai mica 
peronul pe care acest tren se afla.

    In functia find_heaviest_sequence_train puneam un pointer catre 
primul vagon dupa care din acel punct calculam greutatea unei secvente 
de vagoane. Daca aceasta secventa avea o masa mai mare decat secventa 
precedenta salvam primul vagon intr-un pointer special. 
Dupa ce calculam masa secventei mutat acel prim ponter cu un vagon in fata 
si incepeam iarasi calculul a unui nr dat de vagoane cu aceeasi conditie 
de mai sus.

    Funtia order_train presupue in sine sa aranjez vagoanele unui tren 
intr-o ordine descrescatoare insa nu prin schimbarea valorii greutatii 
a 2 vagoane, ci prin schimbarea cu locul a pointerilor catre aceste 
vagoane. Din acest motiv am folosit un wile care verifica prin varibila 
ok daca s-au facut sau nu modificari in aranjarea trenului. 
Pentru a-l ordona am folosit bubble-sort si desigur un vagon precedent 
pentru a putea apela vagoanele din fata lui. O exceptie era cazul in 
care vagonul care trebia schimbat era vagonul de dupa locomotiva, 
deaceea in acest caz special mereu updatam pointerul lui catre vagonul 
cu greutatea mai mare cu care efectuam modificarea.
    Din momentul in care dupa parcurgea trenlui nu s-a m-ai eectuat nici 
o modificare insemna ca ok-ul a ramas pe 0 si ca trenul este corect 
ordonat descrescator.

    Funtia fix_overload_train presupune sa scot un vagon astfel incat 
masa totala a trenului in lipsa acestuia sa fie mai mica sau egala cu 
puterea locomotivei, astfel trenul va transporta o greutate maxima posibila.
    De aceea am folosit o variabila in care salvam cea mai mica diferenta 
dintre masa totala si masa vagonului daca aceasta diferenta era desigur mai 
mica sau egala cu puterea locomotivei si salvam si o pozitie la care ma 
aflam. Dupa ce terminam sa verific tot trenul, cu ajutorul variabilei de 
pozitie ma duceam catre acle vagon si ii eliberam memoria.

    In urma acestor funtii gara din Hogsmeade a fost cu succes dezvoltata 
din punct de vedere tehnologic astfel informatia a fost usor digitalizata 
si este mult mai usor acum sa o gestionam.







Nume Prenume: BUtcan Vlad
Email: butcanvlad10@gmail.com
Telefon: +40763834822