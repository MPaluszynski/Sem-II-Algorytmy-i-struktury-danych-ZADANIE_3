# Sem-II-Algorytmy-i-struktury-danych-ZADANIE_3
Second semester University project:

Zadanie polega na zaimplementowaniu algorytmu który wczytuje zbiór n ukorzenionych drzew w formacie NEWICK, a następnie dla każdej z n(n-1)/2 pary drzew obliczy minimalną liczbę liści, których usunięcie z obydwu drzew spowoduje, że będą one izomorficzne. Problem znany jest w informatyce jako Maximum agreement subtree problem.

Do drzew widocznych powyżej nadajemy identyfikatory wierzchołkom wewnętrznym (nie muszą to być kombinacje litera-liczba jak w przykładzie, mogą to być po prostu kolejne liczby, większe od tych przypisanych liściom). Pamiętajmy, że te drzewa są reprezentowane cały czas za pomocą notacji drzew ogólnych - na rysunku poniżej zastosowano "zwykłe drzewa" jedynie w celu poprawienia czytelności.
Tworzymy tablicę kwadratową gdzie, każdy wymiar zawiera reprezentację wszystkich wierzchołków (zewnętrznych - liści oraz wewnętrznych) jednego drzewa. Taką tablicę najpierw wypełniamy wstawiając jedynki dla wszystkich liści jednego a następnie drugiego drzewa. Z danym liściem skojarzona jest tylko jedna etykieta. Jeśli w liściu bądź wierzchołku wewnętrznym drugiego drzewa znajduje się liść z odpowiadającą mu etykietą to wpisujemy 1 w innym przypadku 0. Najważniejsza część algorytmu zaczyna się podczas porównywania wierzchołków wewnętrznych jednego drzewa z drugim. Po pierwsze należy to robić w odpowiedniej kolejności: tzw. odwrotnym przeszukiwaniem wszerz lub Post-order. Dla każdej pary należy rozpatrzyć 3 przypadki i wybrać ten który daje największy wynik. Zakładamy, że porównujemy dwa wierzchołki wewnętrzne AX z Bx:

    jeden z synów węzła AX można utożsamić z węzłem BX
    węzeł AX można utożsamić jeden z synów węzła BX
    utożsamić synów węzła AX z synami węzła BX (niekoniecznie wszystkimi) tak aby wartość suma identycznych węzłów była jak największa

Podpunkt 3 można zaimplementować algorytmem brute force, przeglądając pełną przestrzeń możliwych rozwiązań i wybierając najlepszy wynik. Kończąc porównanie dwóch korzeni powinniśmy uzyskać końcowy wynik, który jest naszym |l|, należy pamiętać, że jako wynik wysyłamy wartość: n-|l|.



  10 8 9 5 4 6 2 3 7 1F2E2D2A2B2C2
--+--------------------------------
 4|0|0|0|0|1|0|0|0|0|0|1|1|1|1|0|0|
 8|0|1|0|0|0|0|0|0|0|0|1|1|0|0|0|0|
 1|0|0|0|0|0|0|0|0|0|1|1|0|0|0|0|1|
 5|0|0|0|1|0|0|0|0|0|0|1|1|1|1|0|0|
 3|0|0|0|0|0|0|0|1|0|0|1|1|0|0|1|0|
 9|0|0|1|0|0|0|0|0|0|0|1|1|1|0|0|0|
 2|0|0|0|0|0|0|1|0|0|0|1|1|0|0|1|0|
10|1|0|0|0|0|0|0|0|0|0|1|0|0|0|0|0|
 7|0|0|0|0|0|0|0|0|1|0|1|0|0|0|0|1|
 6|0|0|0|0|0|1|0|0|0|0|1|1|0|0|1|0|
F1|1|1|1|1|1|1|1|1|1|1|4|4|2|2|2|2|
E1|0|1|0|1|0|0|0|1|0|1|3|2|1|1|1|1|
B1|0|0|0|1|0|0|0|1|0|0|2|2|1|1|1|0|
D1|1|0|1|0|0|1|1|0|1|0|2|2|1|0|2|1|
C1|1|0|0|0|0|1|0|0|1|0|2|1|0|0|1|1|
A1|0|0|0|0|0|1|0|0|1|0|2|1|0|0|1|1|

W tabeli powyżej widzimy wypełnioną tablicę po przebiegu algorytmu. Jak widać F1 już po zmapowanu z E2 dał wynik optymalny |l| = 4. W kolejnym kroku mapując F1 z F2 wierzchołek E2 został wybrany jako najlepszy wybór z 3 powyższych warunków. Wynik to 6. Interpretujemy go w ten sposób, że jest to minimalna liczba liści wymaganych do usunięcia w każdym z porównywanych drzew aby były izomorficzne. Trzeba usunąć liście: 1,3,5,7,9,10. Po ich usunięciu otrzymujemy zgodne poddrzewo (agreement subtree)
