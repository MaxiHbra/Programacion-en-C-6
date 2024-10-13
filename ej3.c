/*Ejercicio 3: Realice los cambios apropiados en el Ejercicio 2, para impedir la carga de un número de
cuenta ya existente en la lista y que la lista de clientes se ordene por el número de cuenta a medida que
se ingresan los clientes.*/
#include <stdio.h>
#include <string.h>
#define max 20
typedef char tcad[max];
typedef struct {
	tcad provincia,barrio;
}domicilio;
typedef struct{
	tcad nombre;
	int saldo,id;
	domicilio dom;
}tclientes;
typedef tclientes tlis[max];

int menu();
void leecad(tcad,int);
void ingreso(tlis, int*);
tclientes agrega();
void inserta(tlis,int*);
void mostrar(tclientes);
void actualizar_dom(tlis,int);
void actualizar_saldo(tlis,int);
void retirar_saldo(tlis,int);
void transferir_saldo(tlis,int);
int buscar_id(tlis,int,int);
int main() {
	tlis clientes;
	int n,i,opc;
	ingreso(clientes,&n);
	do{
		opc=menu();
		switch(opc){
			case 0 : printf("\nSaliste del programa.");break;
			case 1 : actualizar_dom(clientes,n);break;
			case 2 : actualizar_saldo(clientes,n);break;
			case 3 : retirar_saldo(clientes,n);break;
			case 4 : transferir_saldo(clientes,n);break;
		}
	}while(opc!=0);
	for(i=1;i<=n;i++)
		mostrar(clientes[i]);
	return 0;
}
int menu(){
	int opc;
	printf("\nIngresa 0 para salir.");
	printf("\nIngresa 1 para actualizar el domicilio de un cliente.");
	printf("\nIngresa 2 para depositar saldo en una cuenta.");
	printf("\nIngresa 3 para retirar saldo de una cuenta.");
	printf("\nIngresa 4 para realizar una transferencia entre cuentas.");
	scanf("%d",&opc);
	return opc;
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
void ingreso(tlis cliente, int *n){
	int i,aux;
	do{
	printf("\nIngresar el valor de N: ");
	scanf("%d",&aux);
	*n=0;
	if(aux<=max)
		for(i=1;i<=aux;i++)
			inserta(cliente,n);
	else printf("\nEl valor ingresado supera el maximo.");
	}while(max<*n);
}
void inserta(tlis cliente,int *n){
	tclientes aux;
	int i,pos;
	aux=agrega();
	if(*n==0){
		*n=*n+1;
		cliente[*n]=aux;
	}
	else if(buscar_id(cliente,*n,aux.id)==0){
			*n=*n+1;
			i=1;
			while(i<=*n && cliente[i].id<aux.id) 
				i++;
			if(i<=*n){
				for(pos=i;pos<*n;pos++)
					cliente[pos+1]=cliente[pos];
				cliente[i]=aux;
			}
			else cliente[*n]=aux;
	}
	else printf("\nNo se ingreso el cliente, ya está en la lista.");
}
tclientes agrega(){
	tclientes aux;
	printf("\nIngresar id del cliente: ");
	scanf("%d",&aux.id);
	printf("\nIngresar nombre del cliente: ");
	fflush(stdin);
	leecad(aux.nombre,max);
	printf("\nIngresar saldo del cliente: ");
	scanf("%d",&aux.saldo);
	printf("\nIngresar provincia del cliente: ");
	fflush(stdin);
	leecad(aux.dom.provincia,max);
	printf("\nIngresar ciudad del cliente: ");
	fflush(stdin);
	leecad(aux.dom.barrio,max);
	return aux;
}
void mostrar(tclientes cliente){
	printf("\nID del cliente: %d",cliente.id);
	printf("\nNombre del cliente: %s",cliente.nombre);
	printf("\nDomicilio del cliente: %s, %s",cliente.dom.provincia,cliente.dom.barrio);
	printf("\nSaldo del cliente: %d",cliente.saldo);
}
void actualizar_dom(tlis cliente,int n){
int aux,i;
	printf("\nIngrese ID para actualizar domicilio: ");
	scanf("%d",&aux);
	i=buscar_id(cliente,n,aux);
	if(i!=0){
		printf("\nIngresar provincia del cliente: ");
		fflush(stdin);
		leecad(cliente[i].dom.provincia,max);
		printf("\nIngresar ciudad del cliente: ");
		fflush(stdin);
		leecad(cliente[i].dom.barrio,max);
	}
	else printf("\nNo se encontro el cliente");
}
void actualizar_saldo(tlis cliente, int n){
	int aux,i;
	printf("\nIngrese ID para actualizar saldo: ");
	scanf("%d",&aux);
	i=buscar_id(cliente,n,aux);
	if(i!=0){
		printf("\nNuevo saldo: ");
		scanf("%d",&cliente[i].saldo);
	}
	else printf("\nNo se encontro el cliente");
}
void retirar_saldo(tlis cliente,int n){
	int aux,i;
	printf("\nIngrese ID para actualizar domicilio: ");
	scanf("%d",&aux);
	i=buscar_id(cliente,n,aux);
	if(i!=0){
		printf("\n%s tiene $%d de saldo disponible en su cuenta.",cliente[i].nombre,cliente[i].saldo);
		printf("\nCuanto saldo desea retirar: ");
		scanf("%d",&aux);
		if(aux<=cliente[i].saldo) cliente[i].saldo=cliente[i].saldo-aux;
		else printf("\nNo tiene tanto dinero en su cuenta. No se realizo la operacion.");
	}
	else printf("\nNo se encontro el cliente");
}
void transferir_saldo(tlis cliente,int n){
	int aux1,aux2,i1,i2;
	printf("\nIngrese ID de la cuenta de la que quiere transferir: ");
	scanf("%d",&aux1);
	printf("\nIngrese ID de la cuenta a la que quiera transferirle: ");
	scanf("%d",&aux2);
	i1=buscar_id(cliente,n,aux1);
	i2=buscar_id(cliente,n,aux2);
	if(i1!=0 && i2!=0){
		printf("\nIngrese saldo a transferir desde la cuenta de %s ($%d disponibles: )",cliente[i1].nombre,cliente[i1].saldo);
		scanf("%d",&aux1);
		if(aux1<=cliente[i1].saldo){
		cliente[i1].saldo=cliente[i1].saldo - aux1;
		cliente[i2].saldo=cliente[i2].saldo + aux1;
		}
		else printf("\nNo tiene tanto dinero en la cuenta para transferir, no se realizo la operacion.");
	}
	else printf("\nLos IDs son invalidos. No se realizo la operacion. ");
}
int buscar_id(tlis cliente,int n,int buscado){
	int i=1;
	while(i<=n && cliente[i].id!=buscado) i++;
	if(!(i<=n)) i=0;
	return i;
}
