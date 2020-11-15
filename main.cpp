#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>

using namespace std;

struct node {
	int data;
	node * parent;
	node * brother;
	node * son;
};

class generator {
    public:
        bool * usedNumbers;
        int * currentNumbers;
        int ** allVariations;
        int n, k, numberOfVariations;
        int nextPlace = 0;

        // funkcja generujaca liczbe mozliwych wariacji bez powtorzen

        int factorial(int x){
            if(x <= 1){
                return 1;
            } else {
                return x*factorial(x-1);
            }
        }

        // konstruktor, tablica usedNumbers przechowuje jakie liczby byly juz wykorzystane, a jakie jeszcze nie, currentNumbers przechowuje liczbe na jakiej pracujemy obecnie
        // wywolywana jest tez pierwsza iteracja funkcji gen

        ~generator(){
            delete [] usedNumbers;
            delete [] currentNumbers;
            for(int i = 0 ; i < numberOfVariations ; i++){
                delete [] allVariations[i];
            }
            delete [] allVariations;
        }

        generator(int n, int k){
            this -> n = n;
            this -> k = k;

            usedNumbers = new bool[n];
            currentNumbers = new int[k];

            numberOfVariations = (factorial(n)/factorial(n-k));
            allVariations = new int * [numberOfVariations];

            for(int i = 0 ; i < numberOfVariations ; i++){
                allVariations[i] = new int[k];
            }

            for(int j = 0 ; j < n ; j++){
                usedNumbers[j] = 0;
            }
            gen(0);
        }

        // funkcja gen generuje wariacje - czyli drzewa wywolan

        void gen(int place){
            if(place == k){
                for(int i = 0 ; i < k ; i++){
                    allVariations[nextPlace][i] = currentNumbers[i];
                }
                nextPlace++;
            } else {
                for(int i = 0 ; i < n ; i++){
                    if(usedNumbers[i] == 0){
                        usedNumbers[i] = 1;
                        currentNumbers[place] = i;
                        gen(place+1);
                        usedNumbers[i] = 0;
                    }
                }
            }
        }
};


void renumberInternalNodes(node * node, int * numberOfNode) {
	if (node->data == 0) {
		node->data = *numberOfNode;
		(*numberOfNode)--;
	}
	struct node * currentNode = node->son;
	while (currentNode != NULL) {
		renumberInternalNodes(currentNode, numberOfNode);
		currentNode = currentNode->brother;
	}
}

struct node *  findNode(node * node, int numberOfNode) {
	if (node->data == numberOfNode) {
		return node;
	}
	else {
		struct node * currentNode = node->son;
		while (currentNode != NULL) {
			struct node * tmp = findNode(currentNode, numberOfNode);
			if (tmp != NULL) {
				return tmp;
			}
			currentNode = currentNode->brother;
		}
	}
	return NULL;
}


int main()
{
	int n;
	scanf("%d", &n);

	node * tablica = new node[n];
	int * arrayOfNodes = new int[n];
	int numberOfLeaves;
	int dummyInteger = 0;
	for (int a = 0; a < n; a++) {

		tablica[a].data = 0;

		// address wskazuje mi na miejsce w pamieci, a przesuwa o wielokrotnosc rozmiaru danego elementu, & "ampersant" zastêpuje "tablica +a";

		node * address = &tablica[a];
		int number, numberOfNodes = 1;
		char sign = ' ';
		numberOfLeaves = 0;

		while (sign != ';') {
			// jezli w stringu przechowujacym drzewo w formacie newick dany znak bedzie liczba to scanf zwróci 1, jezli nie to zwróci 0
			if (scanf("%d", &number) == 1) {
				address->data = number;
				numberOfLeaves++;
			}
			else {
				scanf("%c", &sign);
				if (sign == '(') {
					address->son = new node;
					address->son->parent = address;
					address = address->son;
					address->data = 0;
					address->brother = NULL;
					address->son = NULL;
					numberOfNodes++;
				}
				if (sign == ',') {
					address->brother = new node;
					address->brother->parent = address->parent;
					address = address->brother;
					address->data = 0;
					address->brother = NULL;
					address->son = NULL;
					numberOfNodes++;
				}
				if (sign == ')') {
					address = address->parent;
				}
			}
		}

		// Numeracja wierzchołkow wewnętrznych, algorytm DFS

		arrayOfNodes[dummyInteger] = numberOfNodes;
		dummyInteger++;

		int tmp = arrayOfNodes[a];
		renumberInternalNodes(&tablica[a], &tmp);

	}

	//Deklarujemy rozmiary tablicy kwadratowej oraz nia sama

    int ** littleArray = new int * [numberOfLeaves];
	for(int i = 0 ; i < numberOfLeaves ; i++){
        littleArray[i] = new int [numberOfLeaves];
        }

for(int aa = 0 ; aa < n ; aa++){
    for(int bb = aa+1 ; bb < n ; bb++){

	int size1 = arrayOfNodes[aa];
	int size2 = arrayOfNodes[bb];

	node * root1 = &tablica[aa];
	node * root2 = &tablica[bb];


	int ** matchArray = new int*[size1 + 1];

	for (int b = 0; b <= size1; b++) {
		matchArray[b] = new int[size2 + 1];
		for (int c = 1; c <= size2; c++) {
			matchArray[b][c] = 0;
		}
	}

	//Wypelniamy pierwsza czesc tablicy - po diagonali beda jedynki

	for (int d = 1; d <= numberOfLeaves; d++) {
		matchArray[d][d] = 1;
	}

	//Wypełniamy drugą cześć tablicy

	for (int e = numberOfLeaves + 1; e <= size1; e++) {
		node * currentNode1 = findNode(root1, e);
		node * sonOfCurrentNode1 = currentNode1->son;

		while (sonOfCurrentNode1 != NULL) {
			for (int f = 1; f <= numberOfLeaves; f++) {
				if (matchArray[sonOfCurrentNode1->data][f] == 1) {
					matchArray[e][f] = 1;
				}
			}
			sonOfCurrentNode1 = sonOfCurrentNode1->brother;
		}

	}

	//Wypełniamy trzecia cześć tablicy

	for (int g = numberOfLeaves + 1; g <= size2; g++) {
		node * currentNode2 = findNode(root2, g);
		node * sonOfCurrentNode2 = currentNode2->son;

		while (sonOfCurrentNode2 != NULL) {
			for (int h = 1; h <= numberOfLeaves; h++) {
				if (matchArray[h][sonOfCurrentNode2->data] == 1) {
					matchArray[h][g] = 1;
				}
			}
			sonOfCurrentNode2 = sonOfCurrentNode2-> brother;
		}

	}

    //Trzeci etap

	for(int i = numberOfLeaves+1 ; i <= size1 ; i++){
        for(int j = numberOfLeaves+1 ; j <= size2 ; j++){
            node * first = findNode(root1, i);
            node * second = findNode(root2, j);

            int x = 0, y = 0;

            node * firstSon = first -> son;
            while(firstSon != NULL){
                node * secondSon = second -> son;
                y = 0;
                while(secondSon != NULL){
                    littleArray[x][y] = matchArray[firstSon -> data][secondSon -> data];
                    secondSon = secondSon -> brother;
                    y++;
                }
                firstSon = firstSon -> brother;
                x++;
            }

            int lesser = x;
            int bigger = y;
            if (lesser > y){
                lesser = y;
                bigger = x;
            }

            generator Variations(bigger, lesser);

            int bestValue = 0;

            if(lesser == x){
                for(int k = 0 ; k < Variations.numberOfVariations ; k++){
                    int sum = 0;
                    for(int l = 0 ; l < x ; l++){
                        sum += littleArray[l][Variations.allVariations[k][l]];
                    }
                    if(sum > bestValue){
                        bestValue = sum;
                    }
                }
            } else {
                for(int k = 0 ; k < Variations.numberOfVariations ; k++){
                    int sum = 0;
                    for(int l = 0 ; l < y ; l++){
                        sum += littleArray[Variations.allVariations[k][l]][l];
                    }
                    if(sum > bestValue){
                        bestValue = sum;
                    }
                }
            }

            node * secondSon = second -> son;
            while(secondSon != NULL){
                if(matchArray[i][secondSon -> data] > bestValue){
                    bestValue = matchArray[i][secondSon -> data];
                }
                secondSon = secondSon -> brother;
            }

            firstSon = first -> son;

            while(firstSon != NULL){
                if(matchArray[firstSon -> data][j] > bestValue){
                    bestValue = matchArray[firstSon -> data][j];
                }
                firstSon = firstSon -> brother;
            }
            matchArray[i][j] = bestValue;

        }
	}

        cout << (numberOfLeaves - matchArray[size1][size2]) << '\n';

		for (int b = 0; b <= size1; b++) {
            delete [] matchArray[b];
            }
        delete [] matchArray;

    }
}

	for(int i = 0 ; i < numberOfLeaves ; i++){
       delete [] littleArray[i];
    }

    delete [] littleArray;

//	for (int i = 1; i <= size1; i++) {
//		cout << endl;
//		for (int j = 1; j <= size2; j++) {
//			cout << matchArray[i][j] << " ";
//		}
//	}
}
