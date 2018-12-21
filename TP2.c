#include<stdio.h>
#include<string.h>
#include<conio.h>
FILE *f,*f2;
int getNbVar(){
	fseek(f,0,0);
	char i[20];
	int nb=0;
	if(!feof(f)){
		fscanf(f,"%s ",i);
		fscanf(f,"%s ",i);
		fscanf(f,"%s ",i);
		nb=atoi(i);
		printf("le nombre de variables = %d\n",nb);
	}
	return nb;
}
int getNbClauses(){
	fseek(f,0,0);
	char i[20];
	int nb=0;
	if(!feof(f)){
		fscanf(f,"%s ",i);
		fscanf(f,"%s ",i);
		fscanf(f,"%s ",i);
		fscanf(f,"%s ",i);
		nb=atoi(i);
		printf("le nombre de clauses = %d\n",nb);
	}
	return nb;
}
void remplirNew(int nbvar,int nbclauses){
	int pluses;
	printf("nombre de variables de la formule a inferer : ");scanf("%d",&pluses);
	fprintf(f2,"%s ","p cnf");fprintf(f2,"%d ",nbvar);fprintf(f2,"%d\n",nbclauses+pluses);
	//repositionner
	fseek(f,0,0);
	char s[30];
	strcpy(s,"");
	fscanf(f,"%s",s);
	fscanf(f,"%s ",s);
	fscanf(f,"%s ",s);
	fscanf(f,"%s",s);
	while(!feof(f)){
		fscanf(f,"%s ",s);
		fprintf(f2,"%s ",s);
		if(strcmp(s,"0")==0) fprintf(f2,"%s","\n");
	}
	strcpy(s,"");
	printf("donnez variable par variable le \"NON\" de la formule a inferer : \n");
	int i;
	getchar();
	for(i=1;i<=pluses;i++){
		printf("variable n°%d : ",i);
		gets(s);
		fprintf(f2,"%s 0\n",s);
		printf("la formule = %s\n",s);
	}
}
void main(){
	char nomF[40];
	char cmd[200],chemin[300];
	printf("**** Simulation d\'une inférence d\'une base de connaissances ****\n");
	//lecture du nom du fichier
	printf("donnez le nom du fichier .CNF contenant la base de connaissances :");
	scanf("%s",&nomF);
	// ouverture du fichier .cnf
	strcpy(chemin,"");
	strcat(chemin,nomF);
	f=fopen(chemin,"r");
	if(f==NULL){
		printf(" le fichier \"%s\" n\'existe pas !!!",nomF);goto end;
	}
	// affichage des valeurs
	int nbvar=getNbVar();
	int nbclauses=getNbClauses();
	// creation d un nouveau fichier .cnf
	strcpy(chemin,"");
	strcat(chemin,"new.cnf");
	f2=fopen(chemin,"w");
	remplirNew(nbvar,nbclauses);
	
	//fermeture et liberation
	fclose(f);
	fclose(f2);
	//////////////////////////
	strcpy(cmd,"ubcsat -alg saps -i new.cnf -solve");
	system(cmd);
    end:;
}
