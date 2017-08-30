#include<iostream>
using namespace std;
string Lista[10];
void AdicionaNaLista (string Adiciona, int IdNaLista) {
	Lista[IdNaLista] = Adiciona;
}
int ProcuraNaLista (string Palavra) {
	for (int i = 1; i < 10; i++) {
		if ( Palavra == Lista[i]) {
			Lista[i] = "0";
			return i;
		} 
	}
}

	