/*Ejercicio 8:
Crear una estructura de datos de array de registros para almacenar los datos de los vehículos del
estacionamiento. Los datos a almacenar son: “Nro. de Patente, Tipo de Vehículo (auto, camioneta, moto),
Hora y Minutos de Ingreso, Hora y Minutos de Egreso, Importe Pagado”
Crear 2 listas de vehículos:
? La primer lista llamada INGRESOS, es para almacenar los vehículos que ingresan, en esta lista la
hora y minutos de egreso y el importe pagado no se debe cargar.
? La segunda lista llamada EGRESOS, es para almacenar los datos de los vehículos que se retiraron,
en donde se modificará la hora y minutos de egreso y el importe pagado.
Se pide realizar un programa que permita cargar la primer lista INGRESOS de N vehículos y luego a
través de un menú permita las siguientes operaciones:
a) Agregar un nuevo vehículo a la lista INGRESOS.
b) Retirar un vehículo (Para esta acción se solicita el Nro. de Patente del vehículo, se buscará el vehículo
en INGRESOS y se deben copiar los datos del vehículo a la lista EGRESOS, para cargar la
información de salida. Posteriormente se debe eliminar el vehículo de la lista INGRESOS.
c) Eliminar de la lista EGRESOS todos aquellos vehículos de un Tipo determinado por el usuario.*/
#include <stdio.h>
#include <string.h>
#define max 20

typedef char tcad[max];
typedef struct{
	int hora,minuto;
}thora;
typedef struct{
	tcad Tauto;
	int patente,importe;
	thora horas;
}testacionamiento;
typedef testacionamiento tlis[max];
void ingresar(tlis,int *);
testacionamiento agregar();
int menu();
testacionamiento agregar();
void retirar(tlis,tlis,int*,int*);
void eliminar_tipo(tlis,int*);
void eliminar(tlis,int*,int);
void leecad(tcad,int);
void mostrar_todo(tlis,int,tlis,int);
void mostrar(testacionamiento);
int main() {
	int op,n,n2;
	tlis Ingreso,Egreso;
	ingresar(Ingreso,&n);
	do{
	op=menu();
	switch(op){
	case 1: if(n<=max){
		n=n+1;
		Ingreso[n]=agregar();
	} else printf("\nSe alcanzo el tamaño maximo. ");
		break;
	case 2: retirar(Ingreso,Egreso,&n,&n2);
		break;
	case 3: eliminar_tipo(Egreso,&n2);
		break;
	case 4 : mostrar_todo(Ingreso,n,Egreso,n2); break;
	}} while(op!=0);
	return 0;
}

void ingresar(tlis ing,int *n){
	int i;
	printf("nIngresar el tamaño de la lista");
	scanf("%d",n);
	for(i=1;i<=*n;i++){
		ing[i]=agregar();
	}
}
testacionamiento agregar(){
	testacionamiento aux;
	printf("\nIngrese tipo de auto (Auto, camioneta o moto): ");
	fflush(stdin);
	leecad(aux.Tauto,max);
	printf("\nIngrese patente del auto: ");
	scanf("%d",&aux.patente);
	printf("\nIngrese hora de ingreso: ");
	printf("\nHora: ");scanf("%d",&aux.horas.hora); printf("\tMinutos: ");scanf("%d",&aux.horas.minuto);
	aux.importe=0;
	return aux;
	}
int menu(){
	int opc;
	printf("\nIngrese 0 para salir del programa. ");
	printf("\nIngrese 1 para agregar un nuevo vehiculo. ");
	printf("\nIngrese 2 para retirar un vehiculo. ");
	printf("\nIngrese 3 para eliminar vehiculos de un tipo determinado. ");
	printf("\nIngrese 4 para mostrar todo.");
	scanf("%d",&opc);
	return opc;
}
void retirar(tlis ingreso,tlis egreso,int *n,int *n2){
	int i=1;
	long aux;
	printf("\nIngrese patente del vehiculo: ");
	scanf("%ld",&aux);
	while(i<=*n && ingreso[i].patente!=aux) i++;
	if(i<=*n){
		*n2=*n2+1;
		egreso[*n2]=ingreso[i];
		printf("\nIngresar hora de salida del vehiculo: ");
		printf("\nHora: ");scanf("%d",&egreso[*n2].horas.hora);
		printf("\tMinuto: ");scanf("%d",&egreso[*n2].horas.minuto);
		eliminar(ingreso,n,i);
	}
	else printf("\nNo se encontro la patente. ");
}
void eliminar(tlis lis,int *n,int pos){
	int i;
	for(i=pos;i<=*n-1;i++){
		lis[pos]=lis[pos+1];
	}
	*n=*n-1;
}
void eliminar_tipo(tlis egreso, int *n){
	tcad eltipo;
	int aux=1,i=1;
	printf("\nIngrese el tipo de vehiculo que desea eliminar: ");
	fflush(stdin);leecad(eltipo,max);
	while(i<=*n){
		aux=strcmp(eltipo,egreso[i].Tauto);
		if(aux==0) eliminar(egreso,n,i);
		else i++;
	}
}
void mostrar_todo(tlis ingreso,int n,tlis egreso, int n2){
	int i;
	for(i=1;i<=n;i++) mostrar(ingreso[i]);
	for(i=1;i<=n2;i++) mostrar(egreso[i]);
}
void mostrar(testacionamiento x){
	printf("\nPatente: %d Tipo de auto: %s Importe: %d Hora: %d Minuto: %d",x.patente,x.Tauto,x.importe,x.horas.hora,x.horas.minuto);
}
void leecad(tcad cad,int tam){
	char c;
	int i=0;
	c=getchar();
	while(i<tam && c!=EOF && c!='\n'){
		cad[i]=c;
		c=getchar();
		i++;
	}
	cad[i]='\0';
	while(c!=EOF && c!='\n') c=getchar();
}
