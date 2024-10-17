#include <stdio.h>
#include <string.h>
#define max 20

typedef char tcad[max];
typedef struct{
	int dia,mes,anio;
}fecha;
typedef struct{
	long dni,telefono;
	tcad nombre,direc;
}datos;
typedef struct{
	int id,tipo,mcuad,estado;
	datos cliente;
	fecha fechaE,fechaS;
}tped;
typedef tped tlis[20];
int menu(void);
void ingresar(tlis,int*);
tped agregar(void);
void leecad(tcad,int);
void ordenar(tlis,int);
void mostrar_todo(tlis,int);
void mostrar(tped);
void mostrar_cliente(tlis,int);
void modificar(tlis,int);
int buscar_sec(tlis,int,int);
void eliminar_fecha(tlis, int*);
void eliminar(tlis,int*,int);
int main(void){
	int n,opc;
	tlis pedidos;
	n=0;
	do{
		opc=menu();
		switch(opc){
		case 0 : printf("\nSaliste del programa."); break;
		case 1 : ingresar(pedidos,&n); break;
		case 2 : ordenar(pedidos,n); mostrar_todo(pedidos,n); break;
		case 3 : mostrar_cliente(pedidos,n); break;
		case 4 : modificar(pedidos,n); break;
		case 5 : eliminar_fecha(pedidos,&n);break;
		}
	}while(opc!=0);
	return 0;
}
int menu(void){
	int opc;
	printf("\nIngrese 0 para salir. ");
	printf("\nIngrese 1 para cargar un nuevo pedido. ");
	printf("\nIngrese 2 para ordenar y mostrar la lista de pedidos. ");
	printf("\nIngrese 3 para mostrar pedidos de un cliente en especifico por DNI. ");
	printf("\nIngrese 4 para modificar metros cuadrados por ID de pedido. ");
	printf("\nIngrese 5 para eliminar pedidos menores a una fecha. ");
	scanf("%d",&opc);
	return opc;
}
void ingresar(tlis pedidos,int *n){
	if(*n<max){
		*n=*n+1;
		pedidos[*n]=agregar();
	}
	else printf("\nTamaño maximo alcanzado.");
}
tped agregar(void){
	tped aux;
	printf("\nIngresar id del peddido: ");
	scanf("%d",&aux.id);
	printf("\nDNI del cliente: ");
	scanf("%ld",&aux.cliente.dni);
	printf("\nIngresar nombre del cliente: ");
	fflush(stdin);leecad(aux.cliente.nombre,max);
	printf("\nIngresar telefono del cliente: ");
	scanf("%ld",&aux.cliente.telefono);
	printf("\nIngresar direccion del cliente: ");
	fflush(stdin);leecad(aux.cliente.direc,max);
	printf("\nIngresar tipo de arido: 1 para arena, 2 para ripio, 3 para grava y 4 para piedra.");
	scanf("%d",&aux.tipo);
	printf("\nIngrese fecha de solicitud DDMMAAAA: ");
	scanf("%d %d %d",&aux.fechaS.dia,&aux.fechaS.mes,&aux.fechaS.anio);
	printf("\nIngrese fecha de entrega DDMMAAAA: ");
	scanf("%d %d %d",&aux.fechaE.dia,&aux.fechaE.mes,&aux.fechaE.anio);
	printf("\nIngrese cantidad de metros cuadrados del pedido: ");
	scanf("%d",&aux.mcuad);
	printf("\nIngrese estado del pedido: 0 para solicitado y 1 para entregado: ");
	scanf("\n%d",&aux.estado);
	return aux;
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
	while(c!=EOF && c!='\n')c=getchar();
}
void ordenar(tlis lis,int n){
	int i,j;
	tped aux;
	for(i=2;i<=n;i++){
		for(j=n;j>=i;j--)
			if(lis[j].id<lis[j-1].id){
			aux=lis[j];
			lis[j]=lis[j-1];
			lis[j-1]=aux;
		}
	}
}
void mostrar_todo(tlis lis,int n){
	int i;
	for(i=1;i<=n;i++)
		mostrar(lis[i]);
}
void mostrar(tped x){
	printf("\nID del pedido: %d",x.id);
	printf("\nDNI cliente: %ld Nombre: %s Telefono: %ld Direccion: %s ",x.cliente.dni,x.cliente.nombre,x.cliente.telefono,x.cliente.direc);
	printf("\nFecha de solicitud: %d/%d/%d \t Fecha de entrega: %d/%d/%d ",x.fechaE.dia,x.fechaE.mes,x.fechaE.anio,x.fechaS.dia,x.fechaS.mes,x.fechaS.anio);
	switch(x.tipo){
	case 1 : printf("\nTipo: Arena."); break;
	case 2 : printf("\nTipo: Ripio."); break;
	case 3 : printf("\nTipo: Grava."); break;
	case 4 : printf("\nTipo: Piedra."); break;
	default : printf("\nInvalido. "); break;
	}
	printf("\nMetros cuadrados: %d",x.mcuad);
	switch(x.estado){
	case 1 : printf("\nEstado: Solicitado"); break;
	case 2 : printf("\nEstado: Entregado"); break;
	default : printf("\nInvalido. "); break;
	}
	printf("\n----------\n");
}
void mostrar_cliente(tlis pedidos,int n){
	int i,b=0,aux;
	printf("\nIngresar DNI a buscar: ");
	scanf("%d",&aux);
	for(i=1;i<=n;i++){
		if(pedidos[i].cliente.dni==aux) mostrar(pedidos[i]);
	}
	if(b==0) printf("\nNo se encontro tal DNI. ");
}
void modificar(tlis pedidos, int n){
	int aux;
	printf("\nIngresar id del pedido a modificar: ");
	scanf("%d",&aux);
	aux=buscar_sec(pedidos,n,aux);
	if(aux!=0){
		printf("\nIngrese metros cuadrados para el pedido numero: %d",pedidos[aux].id);
		scanf("%d",&pedidos[aux].mcuad);
	}
}
int buscar_sec(tlis ped, int n, int busc){
	int i=1;
	while(i<=n && ped[i].id!=busc) i++;
	if(i>n) i=0;
	return i;
}
void eliminar_fecha(tlis ped, int *n){
	int d,m,a,i=1;
	printf("\nIngrese fecha para eliminar todos sus anteriores DDMMAAAA: ");
	scanf("%d %d %d",&d,&m,&a);
	while(i<=*n){
		if(ped[i].fechaS.anio < a) eliminar(ped,n,i);
		else if(ped[i].fechaS.anio==a){
			if(ped[i].fechaS.mes<m) eliminar(ped,n,i);
			else if(ped[i].fechaS.mes==m){
				if(ped[i].fechaS.dia<d) eliminar(ped,n,i);
			}
		}
		i++;
	}
}
void eliminar(tlis ped,int *n, int pos){
	int i;
	for(i=pos;i<*n;i++)
		ped[i]=ped[i+1];
	*n=*n-1;
}
