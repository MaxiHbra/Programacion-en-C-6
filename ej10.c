/*Ejercicio 10: Una entrenadora de ciclismo lleva un registro con información de N entrenamientos
realizados por un ciclista. Para cada entrenamiento, se registra la Velocidad del ciclista, el Tiempo
transcurrido (en segundos), La fecha de realización (Dia/Mes/Año), y un Número de identificación para
cada sesión. Se pide crear un programa que permita cargar la lista de N entrenamientos, además realizar
un menú que permita:
a) Agregar un nuevo entrenamiento.
b) Eliminar un entrenamiento: Dado un Número de identificación, eliminar de la lista la información
correspondiente a ese entrenamiento.
c) Dado un mes y un año eliminar todas las actividades realizadas.
d) Dado un día y un número de identificación. Mostar su actividad mostrar las actividades
correspondientes.
e) Filtrar entrenamientos por rango de tiempo: Dado un tiempo T, generar y mostrar una nueva lista con
los entrenamientos cuyo tiempo transcurrido se encuentre en el intervalo [T-30 segundos y T+30
segundos].
f) Mostrar las listas:
1. Dado un rango de dos Fecha 1 y Fecha 2, mostrar todas las actividades realizadas en ese rango.
2. Mostrar toda la información registrada de los entrenamientos realizados.*/
#include <stdio.h>
#include <string.h>
#define max 20
typedef char tcad[max];
typedef struct{
	int dia,mes,anio;
}fecha;
typedef struct{
	int velocidad,tiempo,id;
	fecha fech;
}entrenamiento;
typedef entrenamiento tlis[max];
void ingresa(tlis,int*);
void muestra(entrenamiento);
entrenamiento agrega(void);
void eliminar(tlis,int*);
int menu(void);
void muestraMENU(tlis,int);
void mostrarRango(tlis,int);
void eliminarPFecha(tlis,int*);
void mostrarPID(tlis,int);
void muestraTiempo(tlis,int);
int main() {
	tlis treino;
	int n,opc;
	ingresa(treino,&n);
	do{
		opc=menu();
		switch(opc){
		case 0 : printf("\nSaliste del programa.");break;
		case 1 : if(n<=max){
				n++;
				treino[n]=agrega();
			}break;
		case 2: eliminar(treino,&n);break;
		case 3 : eliminarPFecha(treino,&n);break;
		case 4 : mostrarPID(treino,n); break;
		case 5 : muestraTiempo(treino,n);break;
		case 6 : muestraMENU(treino,n);break;
		}
	}while(opc!=0);
	return 0;
}
void ingresa(tlis entreino,int *n){
	int i;
	do{
		printf("\nPor favor ingresar valor de tamaño de la lista: ");
		scanf("%d",n);
		if(*n>max || *n<=0) printf("\nIngresar un valor dentro del rango (0 , %d]",max);
	}while(*n>max && *n<=0);
	for(i=1;i<=*n;i++){
		printf("\n ---Nuevo ingreso--- \n");
		entreino[i]=agrega();
		printf("\n ---Fin de ingreso--- \n");
	}
}
entrenamiento agrega(void){
	entrenamiento aux;
	printf("\nIngresar velocidad del ciclista: ");
	scanf("%d",&aux.velocidad);
	printf("\nIngresar tiempo del ciclista (en segundos): ");
	scanf("%d",&aux.tiempo);
	printf("\nIngresar identificador del entrenamiento: ");
	scanf("%d",&aux.id);
	printf("\nIngresar fecha: en formato DD MM AAAA");
	scanf("%d %d %d",&aux.fech.dia,&aux.fech.mes,&aux.fech.anio);
	return aux;
}
void muestra(entrenamiento entreino){
	printf("\n----------\n");
	printf("\nIdentificador de entrenamiento : %d",entreino.id);
	printf("\nVelocidad del ciclista: %d",entreino.velocidad);
	printf("\nTiempo en segundos: %d",entreino.tiempo);
	printf("\nFecha del entrenamiento: %d / %d / %d",entreino.fech.dia,entreino.fech.mes,entreino.fech.anio);
	printf("\n----------\n");
}
int menu(void){
	int opc;
	printf("\nIngresa 0 para salir.");
	printf("\nIngresa 1 para agregar nuevo entrenamiento.");
	printf("\nIngresa 2 para eliminar un entrenamiento.");
	printf("\nIngresa 3 para eliminar actividades de tal fecha.");
	printf("\nIngresa 4 para mostrar entrenamiento especifico.");
	printf("\nIngresa 5 para mostrar entrenamientos dentro de un rango de tiempo.");
	printf("\nIngresa 6 para mostrar la lista de entrenamientos. ");
	scanf("%d",&opc);
	return opc;
}
void eliminar(tlis treino,int *n){
	int code,i=1,pos;
	printf("\nIngresar codigo de identificacion del entrenamiento a eliminar: ");
	scanf("%d",&code);
	while(i<=*n && treino[i].id != code){
		i++;
	}
	if(i<=*n){
		printf("\nSe eliminara el entrenamiento de la fecha: %d/%d/%d",treino[i].fech.dia,treino[i].fech.mes,treino[i].fech.anio);
		for(pos=i;pos<*n;pos++){
			treino[pos]=treino[pos+1];
		}
		*n=*n-1;
	}
	else printf("\nNo se encontro entrenamiento con esa identificacion. ");
}
void muestraMENU(tlis treino,int n){
	int opc,i;
	printf("\nPresiona 1 para mostrar actividades dentro de un rango de fechas. ");
	printf("\nPresiona 2 para mostrar toda los entrenamientos. ");
	scanf("%d",&opc);
	if(opc==1) mostrarRango(treino,n);
	else if(opc==2){
		for(i=1;i<=n;i++)
			muestra(treino[i]);
	}
	else printf("\nOpcion invalida, saliendo de este menu. ");
}
void eliminarPFecha(tlis treino,int *n){
	int i=1,j,m,a,b=0;
	printf("\nPor favor ingresar mes y año para eliminar actividades: ");
	scanf("%d %d",&m,&a);
	while(i<=*n){
		if(treino[i].fech.mes==m && treino[i].fech.anio==a){
			for(j=i;j<*n;j++)
				treino[j]=treino[j+1];
			*n=*n-1;
			b=1;
		}
		else i++;
	}
	if(b==1)printf("\nSe elimino correctamente la/s actividad/es");
	else printf("\nNo se encontraron actividades de la fecha acordada.");
}
void mostrarPID(tlis treino, int n){
	int i=1,d,cod,b=0;
	printf("\nPor favor ingresar dia para buscar actividades: ");
	scanf("%d",&d);
	printf("\nPor favor ingresar id para buscar actividades: ");
	scanf("%d",&cod);
	while(i<=n){
		if(treino[i].fech.dia==d && treino[i].id==cod){
			muestra(treino[i]);
			b=1;
		}
		i++;
	}
	if(b==0) printf("\nNo se encontraron actividades.");
}
void muestraTiempo(tlis treino,int n){
	int i,j=0,tiem,b=0;
	tlis treinoTiempo;
	printf("\nIngresar tiempo en segundos para mostrar actividades dentro del rango determerninado por el: ");
	scanf("%d",&tiem);
	for(i=1;i<=n;i++){
		if(treino[i].tiempo >= tiem-30 && tiem+30>=treino[i].tiempo){
			j++;
			treinoTiempo[j]=treino[i];
			b=1;
		}
	}
	if(b==0) printf("\nNo existe entrenamiento dentro del rango de tiempo indicado.");
	else for(i=0;i<=j;i++) muestra(treinoTiempo[i]);
}
void mostrarRango(tlis treino, int n){
	int dia1,dia2,mes1,mes2,anio1,anio2,i;
	printf("\nIngresa primera fecha para el rango DD MM AAAA: ");
	scanf("%d %d %d",&dia1,&mes1,&anio1);
	printf("\nIngresa segunda fecha para el rango DD MM AAAA: ");
	scanf("%d %d %d",&dia2,&mes2,&anio2);
	for(i=1;i<=n;i++){
		if(treino[i].fech.anio>= anio1 && treino[i].fech.anio<=anio2 && anio1!=anio2){
			muestra(treino[i]);}
		else if(anio1==anio2){
			if(treino[i].fech.mes >=mes1 && treino[i].fech.mes<=mes2 && mes1!=mes2){
				muestra(treino[i]);}
			else if(mes1==mes2){
				if(treino[i].fech.dia >=dia1 && treino[i].fech.dia<=dia2)
					muestra(treino[i]);}
		}
	}
}
