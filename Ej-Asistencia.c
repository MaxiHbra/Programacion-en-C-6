/*Un consultorio de mascotas presetna las siguientes actividades, clinica, peluqueria, ecogrefia y rayos X
Este tiene una lista de atencion de mascotas por dia con la siguiente informacion:
Nombre de la mascota, nombre del dueño, codigo de identificacion de la mascota(numerico),
horas de atencion(horas y minutos que pueden ser represetnados por un real), y especialidad
Crear un programa que permita: Iniciar el proceso con una lista vacia de atenciones. Y luego presente un menu con las siguientes opcioens:
1- Agregar una atencion de mascota a la lista, manteniendo la lista ordenada por codigo de identificacion.
2- Dado un codigo de identificacion eliminar todos los registros vinculados a ese codigo.
3- Dada una hora atencion mostra todas las mascotas que estan anoptadas en ese horario y la especialidad de atencion reservada, considerar
que los turnos se dan cada media hora y que en un mismo horario pueden haber reservados diferentes turnos para diferentes especialidades.*/
#include <stdio.h>
#include <string.h>
#define max 20
typedef char tcad[max];
typedef struct{
	tcad nombreM,nombreD;
	int especialidad,id;
	float hora,minuto;
}tvete;
typedef tvete tlis[max];
void leecad(tcad,int);
tvete agregar();
void ingreso(tlis,int*);
void ordenar(tlis,int);
void eliminar(tlis,int*);
int menu();
void mostrar_horario(tlis,int);
void mostrar(tvete);
int main() {
	tlis lista;
	int n,opc,i;
	n=0;
	do{
		opc=menu();
		switch(opc){
		case 0 : printf("\nSaliste del programa. ");break;
		case 1 : ingreso(lista,&n);break;
		case 2 : eliminar(lista,&n);break;
		case 3 : mostrar_horario(lista,n);break;
		}
	}while(opc!=0);
	for(i=1;i<=n;i++){
		mostrar(lista[i]);
	}
	return 0;
}
int menu(){
	int opc;
	printf("\nIngrese 0 para salir.");
	printf("\nIngrese 1 para agregar el registro de una mascota.");
	printf("\nIngrese 2 para eliminar todas las atenciones de una mascota en particular.");
	printf("\nIngrese 3 para mostrar mascotas por hora determinada.");
	scanf("%d",&opc);
	return opc;
}
tvete agregar(){
	tvete aux;
	printf("\nIngresar nombre de mascota: ");
	fflush(stdin);leecad(aux.nombreM,max);
	printf("\nIngresar nombre del dueño: ");
	fflush(stdin);leecad(aux.nombreD,max);
	printf("\nIngresar identificador de mascota: ");
	scanf("%d",&aux.id);
	printf("\nIngresar hora de ingreso en tipo HH.MM: ");
	scanf("%f",&aux.hora);
	printf("\nIngrese atención requerida para %s ",aux.nombreM);
	printf("\n1 para clinica. \t2 para peluqueria. \t3 para ecografia. \t4 para rayos x \n ");
	scanf("%d",&aux.especialidad);
	return aux;
}
void ingreso(tlis lis,int *n){
	if(*n<max){
		*n=*n+1;
		lis[*n]=agregar();
		ordenar(lis,*n);
	}
}
void ordenar(tlis lis,int n){
	int i,j;
	tvete aux;
	for(i=2;i<=n;i++){
		aux=lis[i];
		lis[0]=aux;
		j=i-1;
		while(aux.id<lis[j].id){
			lis[j+1]=lis[j];
			j=j-1;
		}
		lis[j+1]=aux;
	}
}
void eliminar(tlis lis,int *n){
	int i=1,aux,b=0,j;
	printf("\nIngrese el id de la mascota a borrar: ");
	scanf("%d",&aux);
	while(i<=*n){
		if(lis[i].id==aux){
			b=1;
			for(j=i;j<*n;j++)
				lis[j]=lis[j+1];
			*n=*n-1;
		}
		else i++;
	}
	if(b==0){
		printf("\nNo se encontro tal id en la lista.");
	}
	else printf("\nSe completo la eliminación.");
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
void mostrar_horario(tlis lis,int n){
	int i,b=0;
	float aux;
	printf("\nIngrese hora en tipo HH.MM para mostrar mascotas atendidas en ese horario: ");
	scanf("%f",&aux);
	for(i=1;i<=n;i++){
		if(lis[i].hora==aux){
			mostrar(lis[i]);
			b=1;
		}
	}
	if(b==0) printf("\nNinguna mascota atendida en esa hora. ");
}
void mostrar(tvete mascot){
	printf("\nNombre de la mascota: %s",mascot.nombreM);
	printf("\nNombre del dueño: %s",mascot.nombreD);
	printf("\nIdentificador de la mascota: %d",mascot.id);
	printf("\nHora de atencion: %f",mascot.hora);
	switch(mascot.especialidad){
	case 1 : printf("\nEspecialidad: CLINICA. "); break;
	case 2 : printf("\nEspecialidad: PELUQUERIA. "); break;
	case 3 : printf("\nEspecialidad: ECOGRAFIA. "); break;
	case 4 : printf("\nEspecialidad: RAYOS X. "); break;
	default : printf("\nEspecialidad: INVALIDA. "); break;
	}
}
