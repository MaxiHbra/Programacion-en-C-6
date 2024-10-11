/*Ejercicio 1: Crear un programa que permita el ingreso de una lista de N países, de cada País se guarda
la siguiente información: “Código del País, Nombre del país, Capital del país y Continente al que
pertenece.”
Se debe realizar la carga de la lista de países y posteriormente ordenar la lista por Código del país, luego
utilizando un menú poder realizar las siguientes operaciones:
a) Añadir un nuevo País preservando el orden.
b) Dado un Código de un país, modificar la Capital que se tiene registrada.
c) Dado un Código de un país, eliminar dicho registro.
d) Dada una Capital, mostrar el País al que pertenece. */
#include <stdio.h>
#include <string.h>
#define max 20
typedef char tcad[max];
typedef struct{
	tcad nombre,capital,continente;
	int cod;
}tpaises;
typedef tpaises tlis[max];

int menu();
void ingreso(tlis,int*);
tpaises agregar();
void ordena(tlis,int);
void mostrar(tpaises);
void agrega_ord(tlis, int*);
void modificar(tlis,int);
void eliminar(tlis,int*);
void mostrar_cap(tlis,int);
void leecad(tcad,int);
int buscar(tlis,int,int);
int main() {
	tlis pais;
	int n,opc;
	ingreso(pais,&n);
	ordena(pais,n);
	do{
		opc=menu();
		switch(opc){
			case 0 : printf("\nSaliste del programa. ");break;
			case 1 : 
				if(n<=max)
					agrega_ord(pais,&n);
				else printf("\nNo e permite agregar mas elementos."); 
				break;
			case 2 : modificar(pais,n);break;
			case 3 : eliminar(pais,&n);break;
			case 4 : mostrar_cap(pais,n);break;
		}
	}while(opc!=0);
	return 0;
}
int menu(){
	int opc;
	printf("\nIngrese 0 para salir: ");
	printf("\nIngrese 1 para añadir un nuevo pais en el orden correcto. ");
	printf("\nIngrese 2 para modificar información de un pais.");
	printf("\nIngrese 3 para eliminar un pais de la lista. ");
	printf("\nIngrese 4 para mostrar un pais en especifico. ");
	scanf("%d",&opc);
	return opc;
}
void leecad(tcad cad,int tam){
	char c;
	int i=0;
	c=getchar();
	while(i<tam && c!=EOF && c!='\n'){
	cad[i]=c;
	i++;
	c=getchar();
	}
	cad[i]='\0';
	while(c!=EOF && c!='\n') c=getchar();
}
void ingreso(tlis pais,int *n){
	int i;
	printf("\nIngresar un valor para el tamaño: ");
	scanf("%d",n);
	if(*n<=max)
		for(i=1;i<=*n;i++)
			pais[i]=agregar();
}
tpaises agregar(){
	tpaises pais;
	printf("\n----------\n");
	printf("\nIngrese codigo del pais: ");
	scanf("%d",&pais.cod);
	printf("\nIngrese nombre del pais: ");
	fflush(stdin);
	leecad(pais.nombre,max);
	printf("\nIngrese capital del pais: ");
	fflush(stdin);
	leecad(pais.capital,max);
	printf("\nIngrese continente del pais: ");
	fflush(stdin);
	leecad(pais.continente,max);
	printf("\n----------\n");
	return pais;
}
void ordena(tlis pais,int n){
	tpaises aux;
	int i,j;
	for(i=1;i<=n-1;i++)
		for(j=i+1;j<=n;j++)
			if(pais[i].cod > pais[j].cod){
				aux=pais[j];
				pais[j]=pais[i];
				pais[i]=aux;
			}
}
void mostrar(tpaises pais){
	printf("\nCodigo del pais: %d",pais.cod);
	printf("\nNombre del pais: %s",pais.nombre);
	printf("\nCapital del pais: %s",pais.capital);
	printf("\nContinente del pais: %s",pais.continente);
}
void agrega_ord(tlis pais, int *n){
	int i=1,j;
	tpaises aux;
	aux=agregar();
	while(i<=*n && aux.cod < pais[i].cod) i++;
	if(i<=*n){
		*n=*n+1;
		for(j=i;j<=*n-1;j++)
			pais[j+1]=pais[j];
		pais[i]=aux;
	}
	else printf("\nNo se encontro el codigo del registro ingresado. ");
}
void modificar(tlis pais,int n){
	int codeaux,pos;
	printf("\nIngresar codigo del pais a modificar: ");
	scanf("%d",&codeaux);
	pos=buscar(pais,n,codeaux);
	if(pos!=0){
		printf("\nIngresar nombre del pais: ");
		fflush(stdin);
		leecad(pais[pos].nombre,max);
		printf("\nIngresar capital del pais: ");
		fflush(stdin);
		leecad(pais[pos].capital,max);
		printf("\nIngresar continente del pais: ");
		fflush(stdin);
		leecad(pais[pos].continente,max);
	}
	else printf("\nNo se encontro tal codigo. ");
}
void eliminar(tlis pais,int *n){
	int codeaux,pos,i;
	printf("\nIngresar codigo del pais a eliminar: ");
	scanf("%d",&codeaux);
	pos=buscar(pais,*n,codeaux);
	if(codeaux!=0){
		printf("\nSe eliminara %s de la lista.",pais[pos].nombre);
		for(i=pos;i<=*n-1;i++)
			pais[i]=pais[i+1];
	} else printf("\nNo se encontro tal codigo");
}
void mostrar_cap(tlis pais,int n){
	tcad capaux;
	int i=1,aux;
	printf("\nIngresar capital del pais: ");
	fflush(stdin);
	leecad(capaux,max);
	aux=strcmp(capaux,pais[i].capital);
	while(i<=n && aux!=0){ 
	i++;
	aux=strcmp(capaux,pais[i].capital);
	}
	if(i<=n) mostrar(pais[i]);
	else printf("\nNo se encontro tal capital. ");
}
int buscar(tlis pais,int n,int codeaux){
	int ini,med,fin;
	ini=1;
	fin=n;
	med=(ini+fin)/2;
	while(ini<fin && pais[med].cod!=codeaux){
	if(pais[med].cod < codeaux) 
		ini=med+1;
	else fin=med-1;
	med=(ini+fin)/2;
	}
	if(fin<ini) med=0;
	return med;
}
