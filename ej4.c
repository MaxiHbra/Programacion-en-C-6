/*Ejercicio 4: Una academia de danzas tiene una lista de alumnos, registrando de cada alumno los
siguientes datos: “DNI del alumno, Apellido y Nombre del alumno, Código de curso de verano ([1] folclore,
[2] español, [3] contemporáneo)”.
Crear un programa que permita cargar la lista de alumnos, inicializando el campo Código de curso en 0.
Luego ordene la lista por DNI del alumno utilizando el método de la Burbuja. Posteriormente, a través de
un menú realizar las siguientes tareas:
a) Agregar un alumno a la lista.
b) Dado el DNI de un alumno inscribirlo a uno de los 3 cursos que se dictan, teniendo en cuenta que el
cupo es de 10 personas para cada curso. Un alumno sólo puede estar inscripto en un curso a la vez.
c) Permitir dar de baja a un alumno de un curso ingresando su DNI. (Cambiar Código a 0)
d) Eliminar de la lista todos los alumnos que no se encuentren inscriptos en algún curso.
e) Dado un Código de curso, mostrar la lista de inscriptos. */
#include <stdio.h>
#include <string.h>
#define max 30

typedef char tcad[max];
typedef struct{
	int dni,codigo;
	tcad nombre;
}alumnos;
typedef alumnos tvec[max];
void inicializar(tvec,int*);
void leecad(tcad,int);
void mostrar(alumnos);
void ordenar(tvec,int);
void inscribir(tvec,int,int*,int*,int*);
void baja(tvec,int,int*,int*,int*);
void eliminarAlu(tvec,int*);
void mostrarInscriptos(tvec,int);
int menu();
alumnos cargar();
int main(){
	tvec a;
	int n,opc,cont1=0,cont2=0,cont3=0;
	inicializar(a,&n);
	do{
		opc=menu();
		switch(opc){
		case 0 : printf("\nSaliste del programa. ");break;
		case 1 :
		if(n<=max){
			n=n+1;
			a[n]=cargar();}
		else printf("\nTamaño maximo alcanzado. ");
		break;
		case 2 : inscribir(a,n,&cont1,&cont2,&cont3);break;
		case 3 : baja(a,n,&cont1,&cont2,&cont3);break;
		
		case 4 : eliminarAlu(a,&n); break;
		case 5 : mostrarInscriptos(a,n);
		}
	}while(opc!=0);
}
void inicializar(tvec a, int *n){
	int i=1;
	char b='y';
	while(b=='y' && i<=max){
	a[i]=cargar();
	i++;
	printf("\nPara seguir ingresando presione 'y' para dejar de ingresar presione 'n'. ");
	fflush(stdin);
	scanf("%c",&b);
	}
	*n=i-1;
}
void leecad(tcad cad,int tam){
	char c;
	int i=0;
	c=getchar();
	while(c!=EOF && c!='\n' && i<=tam-1){
		cad[i]=c;
		i++;
		c=getchar();
	}
	cad[i]='\0';
	while(c!=EOF && c!='\n')c=getchar();
}
void mostrar(alumnos a){
	printf("\nDNI: %d",a.dni);
	printf("\nNombre del alumno: %s",a.nombre);
	printf("\nCodigo del curso: %d",a.codigo);
}
alumnos cargar(){
	alumnos a;
	printf("\nIngresar nombre y apellido: ");
	fflush(stdin);
	leecad(a.nombre,max);
	printf("\nIngresar DNI de %s: ",a.nombre);
	scanf("%d",&a.dni);
	a.codigo=0;
	return a;
}
void ordenar(tvec a,int n){
	int i,j;
	alumnos aux;
	for(i=2;i<=n;i++)
		for(j=n-1;j>=i;j--)
			if(a[j-1].dni>a[j].dni){
				aux=a[j];
				a[j]=a[j-1];
				a[j-1]=aux;
			}
}
int menu(){
	int opc;
	printf("\nIngresar 0 para salir. ");
	printf("\nIngresar 1 para agregar un alumno. ");
	printf("\nIngresar 2 para inscribir alumno en curso. ");
	printf("\nIngresar 3 para dar de baja a un alumno de un curso. ");
	printf("\nIngresar 4 para eliminar todos los alumnos no inscriptos a algun curso. ");
	printf("\nIngresar 5 para mostrar todos los alumnos de un curso. ");
	scanf("%d",&opc);
	return opc;
}
void inscribir(tvec a,int n,int *cont1,int *cont2,int *cont3){
	int cod,auxd ;
	int i=1,b=0;
	printf("nIngresar dni: ");
	scanf("%d",&auxd);
	while(i<=n && b==0){
		if(a[i].dni==auxd){
			b=1;
			}
		i++;
	}
	if(b==1){
		i=i-1;
		if(a[i].codigo==0){
			printf("\nIngresar el codigo del curso para %s",a[i].nombre);
			scanf("%d",&cod);
			if(cod==1 && *cont1<=10){
			*cont1=*cont1+1;
			a[i].codigo=cod;
			}
			if(cod==2 && *cont2<=10) {
			*cont2=*cont2+1;
			a[i].codigo=cod;
			}
			if(cod==3 && *cont3<=10){
			*cont3=*cont3+1;
			a[i].codigo=cod;
			}
		} else printf("\n%s ya se encuentra inscripto en un curso.",a[i].nombre);
		}
		else printf("\nNo se encuentra en la lista.");
}
void baja(tvec a, int n, int *cont1, int *cont2, int *cont3){
	int auxd ;
	int i=1,b=0;
	printf("nIngresar dni: ");
	scanf("%d",&auxd);
	while(i<=n && b==0){
		if(a[i].dni==auxd){
			b=1;
			}
		i++;
	}
	if(b==1){
		i=i-1;
		
		if(a[i].codigo==1) 
			*cont1=*cont1-1;
		else if(a[i].codigo==2) *cont2=*cont2-1;
			else *cont3=*cont3-1;
		a[i].codigo=0;
	}else printf("\nNo se encontro el dni en la lista.");
}
void eliminarAlu(tvec a, int *n){
	int i=1,j,cod;
	printf("\nIngresar codigo a buscar: ");
	scanf("%d",&cod);
	while(i<=*n){
		if(a[i].codigo==cod){
			for(j=i;j<=*n-1;j++)
				a[j]=a[j+1];
			*n=*n-1;
			}
		else i++;
	}
}
void mostrarInscriptos(tvec a,int n){
	int cod,i,b=0;
	printf("\nIngresar codigo a buscar: ");
	scanf("%d",&cod);
	for(i=1;i<=n;i++)
		if(a[i].codigo == cod){
			mostrar(a[i]);
			b=1;}
	if(b==0) printf("\nNingun alumno inscripto en el curso. ");
}
