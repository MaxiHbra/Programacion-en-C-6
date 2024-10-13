/*Ejercicio 6: Dada una lista de Repuestos de autos con los siguientes datos: “Código del repuesto,
Nombre del repuesto, Nombre del Proveedor, Cantidad en Stock, Precio del repuesto”.
Se pide crear un programa que permita cargar la lista de N repuestos y que se ordene luego de su carga
por Código del repuesto. Además, realizar un menú que permita:
a) Agregar un nuevo repuesto.
b) Dado un Código de repuesto, eliminar de la lista sus datos.
c) Dada una lista precios nuevos con la siguiente información Código del repuesto y Nuevo precio.
Actualizar los precios.
d) Dado un Proveedor generar y mostrar una nueva lista con los repuestos provisto por él. e) Mostrar la
lista completa.
Nota: El ingreso y el alta no deben permitir Código de repuestos repetidos*/
#include <stdio.h>
#include <string.h>
#define max 60
typedef char tcad[max];
typedef struct{
	tcad nombreR,nombreP;
	int id,stock,precio;
}trepuesto;
typedef trepuesto tlis[max];

int menu();
void leecad(tcad,int);
void ordenarPS(tlis,int);
int busquedaBIN(tlis,int,int);
void ingresa(tlis,int*);
trepuesto agrega();
void listaPROV(tlis,int);
void actualizarPREC(tlis,int);
trepuesto agregarNP();
void eliminarREP(tlis,int*);
void muestra(trepuesto);
int main(){
	int opc,i,n;
	tlis xd;
	ingresa(xd,&n);
	do{
		opc=menu();
		switch(opc){
		case 0 : printf("\nSaliste del programa. "); break;
		case 1: n=n+1; xd[n]=agrega();
		ordenarPS(xd,n);break;
		case 2: eliminarREP(xd,&n);
		break;
		case 3: actualizarPREC(xd,n);
		break;
		case 4: listaPROV(xd,n);
		break;
		case 5 : for(i=1;i<=n;i++){
			muestra(xd[i]);}break;
		}
	}while(opc!=0);
	return 0;
}
	void leecad(tcad cade,int tam){
		char c;
		int i=0;
		c=getchar();
		while(c!=EOF && c!='\n' && i<tam) {
		cade[i]=c;
		i++;
		c=getchar();
	}
		cade[i]='\0';
		while(c!=EOF && c!='\n') c=getchar();
}
void ingresa(tlis reps,int *n){
	int i=1,aux;
	reps[i]=agrega();
	printf("\nPresiona 1 para seguir agregando, 0 para salir: ");
	scanf("%d",&aux);
	while(i<=*n && aux!=0){
		i++;
		reps[i]=agrega();
		printf("\nPresiona 1 para seguir agregando, 0 para salir: ");
		scanf("%d",&aux);
	}
	*n=i;
}
trepuesto agrega(){
	trepuesto xd;
	printf("\nIngresar codigo del repuesto: ");
	scanf("%d",&xd.id);
	printf("\nIngresar nombre del repuesto: ");
	fflush(stdin);
	leecad(xd.nombreR,max);
	printf("\nIngresar nombre del proveedor: ");
	fflush(stdin);
	leecad(xd.nombreP,max);
	printf("\nIngresar stock del repuesto: ");
	scanf("%d",&xd.stock);
	printf("\nIngresar precio del repuesto: ");
	scanf("%d",&xd.precio);
	return xd;
}
void muestra(trepuesto xd){
	printf("\nID: %d Nombre del repuesto : %s Nombre del Prov: %s Precio: %d Stock: %d",xd.id,xd.nombreR,xd.nombreP,xd.precio,xd.stock);
}
int menu(){
	int opc;
	printf("\nIngresar 0 para salir del programa: ");
	printf("\nIngresar 1 para agregar un nuevo repuesto. ");
	printf("\nIngresar 2 para dado un codigo de repuesto,eliminar uno de sus datos.");
	printf("\nIngresar 3 para dada una lista precios nuevos con la siguiente información Código del repuesto y Nuevo precios,actualizar");
	printf("\nIngresar 4 para dado un proveedor generar y mostrar una nueva lista con los repuestos provisto por el");
	printf("\ningresar 5 para Mostrar la lista completa.");
	scanf("%d",&opc);
	return opc;
}
void ordenarPS(tlis reps,int n){
	int i,j;
	trepuesto aux;
	for(i=1;i<=n-1;i++) 
		for(j=i+1;j<=n;j++)
			if(reps[i].id>reps[j].id){
			aux=reps[j];
			reps[j]=reps[i];
			reps[i]=aux;
		}
}
int busquedaBIN(tlis reps,int n, int buscado){
	int ini,med,fin,aux;
	ini=1;fin=n;med=(ini+fin)/2;
	while(ini<fin && reps[med].id!=buscado){
		if(reps[med].id>med) ini=med+1;
		else if(reps[med].id<med) fin=med-1;
		med=(ini+fin)/2;}
		if(reps[med].id==buscado) aux=med;
		else aux=0;
		return aux;
}
void eliminarREP(tlis reps,int *n){
	int i,aux;
	printf("\nIngrese codigo de repuesto a leiminar: ");
	scanf("%d",&aux);
	aux=busquedaBIN(reps,*n,aux);
	if(aux!=0){
		for(i=aux;i<*n;i++)
			reps[i]=reps[i+1];
		*n=*n-1;
	}
	else printf("\nNo se encontro el elemento");
}
void actualizarPREC(tlis reps,int n){
	tlis xd;
	int n2,i,aux,b=0;
	printf("\nIngresar numero de elementos a actualizar: ");
	scanf("%d",&n2);
	for(i=1;i<=n2;i++){
		xd[i]=agregarNP();
		aux=busquedaBIN(reps,n2,xd[i].id);
		if(aux!=0){
			reps[aux].precio=xd[i].precio;
			b=1;
		}
	}
	if(b!=0) printf("\nPrecios actualizados. ");
	else printf("\nEl/Los codigo/s no se encontraron en la lista. ");
}
trepuesto agregarNP(){
	trepuesto xd;
	printf("\nIngresar codigo del repuesto a actualizar.");
	scanf("%d",&xd.id);
	printf("\nIngresar nuevo precio del repuesto.");
	scanf("%d",&xd.precio);
return xd;
}
void listaPROV(tlis xd,int n){
	tlis provN;
	tcad nprov;
	int i,j=0,aux;
	printf("\nIngresar nombre del proveedor a evaluar");
	fflush(stdin);
	leecad(nprov,max);
	for(i=1;i<=n;i++){
		aux=strcmp(nprov,xd[i].nombreP);
		if(aux==0){
			j++;
			strcpy(provN[j].nombreP,xd[i].nombreP);
			strcpy(provN[j].nombreR,xd[i].nombreR);
			provN[j].id=xd[i].id;
			provN[j].stock=xd[i].stock;
			provN[j].precio=0;
		}
	}
	if(j!=0) for(i=1;i<=j;i++) muestra(provN[i]);
	else printf("\nEse proveedor no se encuentra en la lista.");
}
