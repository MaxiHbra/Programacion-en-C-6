/*Ejercicio 5: Se necesita crear un programa que maneje una Agenda telefónica de amigos, que almacena
los siguientes datos de cada persona: “Apellidos, Nombres, Dirección, Celular, Fecha de nacimiento”.
Realizar un programa que permita cargar la lista de amigos y que la misma se ordene alfabéticamente
por Apellidos y Nombres a medida que cargan los registros. Utilizando un menú permita realizar las
siguientes operaciones:
a) Añadir un nuevo contacto, considerando que cada contacto es único. (Mantener ordenada la lista por
apellido y nombres).
b) Borrar un contacto. (Mantener ordenada la lista por apellido y nombres).
c) Dado el apellido y el nombre, modificar su dirección o su teléfono.
d) Dado un apellido y el nombre, mostrar sus datos.
e) Mostrar la agenda telefónica completa.
f) Dado un mes, mostrar todas las personas que cumplen años en ese mes.*/
#include <stdio.h>
#include <string.h>
#define max 20

typedef char tcad[max];
typedef struct{
	tcad nombre,direc;
	long celular;
	int dia,mes,anio;
}tagenda;
typedef tagenda tlis[max];
int menu(void);
void ingresar(tlis,int*);
void ordenar(tlis,int);
tagenda agregar(void);
void borrar_contacto(tlis,int*);
void borrar(tlis,int*,int);
int buscar(tlis,int,tcad);
void modificar(tlis,int);
void leecad(tcad,int);
void mostrar_nombre(tlis,int);
void mostrar(tagenda);
void mostrar_todo(tlis,int);
void mostrar_cumple(tlis,int);
int main(void) {
	tlis agenda;
	int n,opc;
	do{
		opc=menu();
		switch(opc){
			case 0 : printf("\nSaliste del programa."); break;
			case 1 : ingresar(agenda,&n); break;
			case 2 : borrar_contacto(agenda,&n);break;
			case 3 : modificar(agenda,n); break;
			case 4 : mostrar_nombre(agenda,n); break;
			case 5 : mostrar_todo(agenda,n); break;
			case 6 : mostrar_cumple(agenda,n); break;
		}
	}while(opc!=0);
	return 0;
}
int menu(void){
	int opc;
	printf("\nIngrese 0 para salir.");
	printf("\nIngrese 1 para añadir un nuevo contacto.");
	printf("\nIngrese 2 para borrar un contacto.");
	printf("\nIngrese 3 para modificar contacto.");
	printf("\nIngrese 4 para mostrar datos de un contacto.");
	printf("\nIngrese 5 para mostrar la agenda completa.");
	printf("\nIngrese 6 para mostrar personas que cumplen año en un mes en especifico.");
	scanf("%d",&opc);
	return opc;
}
void ingresar(tlis lis,int *n){
	if(*n<max){
		*n=*n+1;
		lis[*n]=agregar();
		ordenar(lis,*n);
	}
	else printf("\nTamaño maximo alcanzado.");
}
void ordenar(tlis lis,int n){
	int i,j;
	tagenda aux;
	for(i=2;i<=n;i++){
		aux=lis[i];
		lis[0]=aux;
		j=i-1;
		while(strcmp(aux.nombre,lis[j].nombre)<1){
			lis[j+1]=lis[j];
			j=j-1;
		}
		lis[j+1]=aux;
	}
}
tagenda agregar(void){
	tagenda aux;
	printf("\nIngrese nombre completo: ");
	fflush(stdin);
	leecad(aux.nombre,max);
	printf("\nIngrese direccion: ");
	fflush(stdin);
	leecad(aux.direc,max);
	printf("\nIngrese celular: ");
	scanf("%ld",&aux.celular);
	printf("\nIngrese fecha de nacimiento DDMMAAAA: ");
	scanf("%d %d %d",&aux.dia,&aux.mes,&aux.anio);
	return aux;
}
void borrar_contacto(tlis lis,int *n){
	int pos;
	tcad aux;
	printf("\nIngresar nombre del contacto a eliminar: ");
	printf("\nIngrese nombre completo: ");
	fflush(stdin);
	leecad(aux,max);
	pos=buscar(lis,*n,aux);
	if(pos!=0) borrar(lis,n,pos);
	else printf("\nNo se encontro el contacto.");
}
void borrar(tlis lis,int *n,int pos){
	int i;
	for(i=pos;i<*n;i++)
		lis[i]=lis[i+1];
	*n=*n-1;
}
int buscar(tlis lis,int n,tcad aux){
	int ini,med,fin;
	ini=1;fin=n;med=(ini+fin)/2;
	while(ini<fin && strcmp(aux,lis[med].nombre)!=0){
		if(strcmp(aux,lis[med].nombre)>1) ini=med+1;
		else fin=med-1;
		med=(ini+fin)/2;
	}
	if(ini>fin) med=0;
	return med;
}
void modificar(tlis lis,int n){
	tcad aux;
	int op,au;
	printf("\nIngresar nombre del contacto a modificar: ");
	fflush(stdin);
	leecad(aux,max);
	au=buscar(lis,n,aux);
	if(au!=0){
		printf("\nIngrese 1 para modificar direccion o 2 para telefono de %s: ",lis[au].nombre);
		scanf("%d",&op);
		switch(op){
		case 1 : printf("\nDireccion nueva: "); fflush(stdin); leecad(lis[au].direc,max);
		case 2 : printf("\nTelefono nuevo: "); scanf("%ld",&lis[au].celular);
		default : printf("\nInvalido. "); break;
		}
	}
	else printf("\nNo se encontro %s en la agenda.",aux);
}
void leecad(tcad cad,int tam){
	char c;
	int i=0;
	c=getchar();
	while(c!=EOF && c!='\n' && i<tam){
		cad[i]=c;
		i++;
		c=getchar();
	}
	cad[i]='\0';
	while(c!=EOF && c!='\n') c=getchar();
}
void mostrar_nombre(tlis lis,int n){
	tcad aux;
	int au;
	printf("\nIngresar nombre del contacto a mostrar: ");
	fflush(stdin);
	leecad(aux,max);
	au=buscar(lis,n,aux);
	if(au!=0) mostrar(lis[au]);
	else printf("\nNo se encontro a %s en la agenda. ",aux);
}
void mostrar(tagenda x){
	printf("\nNombre: %s",x.nombre);
	printf("\nTelefono: %ld",x.celular);
	printf("\nDireccion: %s",x.direc);
	printf("\nCumpleaños: %d/%d/%d",x.dia,x.mes,x.anio);
}
void mostrar_todo(tlis lis,int n){
	int i;
	for(i=1;i<=n;i++) mostrar(lis[i]);
}
void mostrar_cumple(tlis lis,int n){
	int mesh,i;
	printf("\nIngresar mes: ");
	scanf("%d",&mesh);
	for(i=1;i<=n;i++) if(lis[i].mes==mesh) mostrar(lis[i]);
}
