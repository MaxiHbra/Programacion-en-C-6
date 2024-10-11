/*Ejercicio 2: Un banco mantiene la información de sus clientes en un array de registros (Lista de clientes).
De cada Cliente se almacena la siguiente información: “Número de cuenta, Apellido y Nombre del cliente,
Domicilio del cliente, Saldo de la cuenta. “
Se solicita escribir un programa que permita realizar la carga de las cuentas de N Clientes de un banco y
luego mediante un menú realizar las siguientes operaciones:
a) Permitir actualizar el domicilio de un cliente, dado su número de cuenta
b) Realizar un depósito (es decir, dado un monto a depositar y una cuenta, actualizar el saldo).
c) Realizar un retiro (es decir, dado un monto a retirar y una cuenta, actualizar el saldo si es que el saldo
es mayor o igual al importe a retirar).
d) Realizar una transferencia entre cuentas (es decir, dado un monto a transferir, una cuenta origen y
una cuenta destino, actualizar el saldo destino si es que el saldo origen es mayor o igual al importe a
transferir). */
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
	int i;
	do{
	printf("\nIngresar el valor de N: ");
	scanf("%d",n);
	if(*n<=max)
		for(i=1;i<=*n;i++)
			cliente[i]=agrega();
	else printf("\nEl valor ingresado supera el maximo.");
	}while(max<*n);
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
