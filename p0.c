
// AUTOR: Daniel Rodriguez Sanchez
// AUTOR: Lucia Docampo Rodriguez

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include "list.h"
#include "p1.h"

#define MAX_LINE 1024
#define MAX_TOKENS 100

int processCmd(char *tokens[], int ntokens, list *history);

int parseString(char * cadena, char * trozos[]) {
    int i=1;
    if ((trozos[0]=strtok(cadena," \n\t"))==NULL)
        return 0;
    while ((trozos[i]=strtok(NULL," \n\t"))!=NULL)
        i++;

    return i;
}

int autores(char *tokens[], int ntokens, list *history){
     if(tokens[1]==NULL){
          printf("Daniel Rodriguez Sanchez: daniel.rodriguez.sanchez1\n");
          printf("Lucia Docampo Rodriguez: lucia.docampo\n");
     }else{
     if (!strcmp(tokens[1],"-n")) {
          printf("Daniel Rodriguez Sanchez\n");
          printf("Lucia Docampo Rodriguez\n");
     }
     if(!strcmp(tokens[1],"-l")){
          printf("daniel.rodriguez.sanchez1\n");
          printf("lucia.docampo\n");
     }
     }
     return 0;
}

int pid(char *tokens[], int ntokens, list *history){
     if (tokens[1]==NULL){
          printf("Pid de shell: %d\n", getpid());
     }else {
          if(!strcmp(tokens[1], "-p")){
               printf("Pid del padre del shell:  %d\n", getppid());
          }
     }
    return 0;
}

int carpeta(char *tokens[], int ntokens, list *history){
     char direccion [100];
     if (tokens[1]==NULL){
          printf("%s\n", getcwd(direccion, 100));
     } else{
          if (chdir(tokens[1])!=0){
               printf("Imposible cambiar directorio: No such file or directory\n");
          }
     }
     return 0;
}

int fecha(char *tokens[], int ntokens, list *history){
     time_t t = time(NULL);
     struct tm *tm = localtime(&t);
     char fecha[100];
     if ((tokens[1]==NULL)||!strcmp(tokens[1],"-h")) {
          strftime(fecha, 100, "%H:%M:%S",tm);
          printf("%s\n", fecha);
     }
     if ((tokens[1]==NULL)||!strcmp(tokens[1],"-d")){
          strftime(fecha, 100, "%d/%m/%Y",tm);
          printf("%s\n", fecha);
     }
     return 0;
}

int hist(char *tokens[], int ntokens, list *history){

     if(tokens[1]==NULL){
     int i=0;

     for(pos p = first(*history); !end(*history, p); p = next(*history, p)) {
          char *command = get(*history, p);
          printf("%d-> %s\n", i, command);
          i++;
     }
     }else if(!strcmp(tokens[1], "-c")){
          clear(history); //Borra la lista
     }else if(atoi(tokens[1]) != 0){ // en caso de hist -N
          int n = -atoi(tokens[1]);
          pos p = first(*history);
          for(int i=0 ; i<=n; i++){
               char *command = get(*history, p);
               printf("%d-> %s\n", i, command);
               p = next(*history, p);
          }
     }
     return 0;
}

int comando(char *tokens[], int ntokens, list *history){
     char *comp;
     strtol(tokens[1], &comp, 10);
     if((comp == tokens[1]) || (tokens[1]==NULL)){
          printf("Error, despues de 'comando' introduce un numero incluido en 'hist'\n");
          return 0;
     } else{
          int n = atoi(tokens[1]);
          pos p = first(*history);
          int i=0;
          while(!end(*history, p)){ // sumamos i++ hasta que llega al final de la lista
           p=next(*history, p);
           i++; //cuando salga del bucle i=cantidad de comandos en la lista
          }
          if(n>i){
               printf("No hay elemento %d en el historico\n", n);
          }else{

               int n = atoi(tokens[1]);
               pos p = first(*history); //creamos p que apunta al primer nodo de la lista
               for(int i=0; i<n; i++){
                    p = next(*history, p); //avanzamos hasta la posicion donde esta el comando
               }
               char* command = get(*history, p); // command es el comando que queremos repetir
               printf("Ejecutando hist (%d): %s\n", n, command);
               char* command2 = strdup(command);
               int numtokens = parseString(command2, tokens);
               processCmd(tokens, numtokens, history);
               free(command2);
          }
     }
          return 0;
}

int infosis(char *tokens[], int ntokens, list *history){
     struct utsname utsData;
     uname(&utsData);
     printf("%s %s %s %s %s\n", utsData.sysname, utsData.nodename, utsData.release, utsData.version, utsData.machine);
     return 0;
}

int ayuda (char *tokens[], int ntokens, list *history){
     //no se le puede pasar un string a un switch asi que hay que encadenar if elses
     if(tokens[1]==NULL){
          printf("'ayuda cmd' donde cmd es uno de los siguientes comandos:\n");
          printf("autores "); printf("pid "); printf("carpeta "); printf("fecha ");
          printf("hist "); printf("comando "); printf("infosis "); printf("ayuda ");
          printf("fin "); printf("salir "); printf("bye\n");
     }else if(!strcmp(tokens[1], "autores")){
          printf("autores [-n|-l] Muestra los nombres y logins de los autores\n");
     }else if(!strcmp(tokens[1], "pid")){
               printf("pid [-p]	Muestra el pid del shell o de su proceso padre\n");
          } else if(!strcmp(tokens[1], "carpeta")){
               printf("carpeta [dir]	Cambia (o muestra) el directorio actual del shell\n");
          } else if(!strcmp(tokens[1], "fecha")){
               printf("fecha [-d|.h	Muestra la fecha y o la hora actual\n");
          } else if(!strcmp(tokens[1], "hist")){
               printf("hist [-c|-N]	Muestra el historico de comandos, con -c lo borra\n");
          } else if(!strcmp(tokens[1], "comando")){
               printf("comando [-N]	Repite el comando N (del historico)\n");
          } else if(!strcmp(tokens[1], "infosis")){
               printf("infosis 	Muestra informacion de la maquina donde corre el shell\n");
          } else if(!strcmp(tokens[1], "ayuda")){
               printf("ayuda [cmd]	     Muestra ayuda sobre los comandos\n");
          } else if(!strcmp(tokens[1], "fin")){
               printf("fin    Termina la ejecucion del shell\n");
          } else if(!strcmp(tokens[1], "salir")){
               printf("salir  Termina la ejecucion del shell\n");
          } else if(!strcmp(tokens[1], "bye")){
               printf("bye    Termina la ejecucion del shell\n");
          } else printf("%s no encontrado\n", tokens[1]);
     return 0;
}

int fin(char *tokens[], int ntokens, list *history) {
    return 1;
}

struct cmd {
    char *cmd_name;
    int (*cmd_fun)(char *tokens[], int ntokens, list *history);
};

struct cmd cmds[] = {
    {"autores", autores},
    {"pid", pid},
    {"carpeta", carpeta},
    {"hist", hist},
    {"comando", comando},
    {"infosis", infosis},
    {"ayuda", ayuda},
    {"fecha", fecha},
    {"fin", fin},
    {"salir", fin},
    {"bye", fin},
    {"crear", crear},
    {"borrar", borrar},
    {"borrarrec", borrarrec},
    {"listfich", listfich},
    {"listdir", listdir},
    {NULL, NULL}
};

int processCmd(char *tokens[], int ntokens, list *history) {
    int i;
    for(i=0; cmds[i].cmd_name != NULL; i++) {
        if(strcmp(tokens[0], cmds[i].cmd_name) == 0)//si son iguales
            return cmds[i].cmd_fun(tokens, ntokens, history);
    }

    printf("%s no es un comando del shell\n", tokens[0]);
    return 0;
}

int GuardarCmd(list *history, char *line){
     insert(history, line);
     return 0;
}

int main() {
    char *line;
    char *tokens[MAX_TOKENS];
    int ntokens;
    int end = 0;
    list history;
    init_list(&history);

    while(!end) {
        line = readline("> ");
        char* linecpy = strdup(line);
        GuardarCmd(&history, linecpy);
        ntokens = parseString(line, tokens);
        end = processCmd(tokens, ntokens, &history);
        free(line);
    }
}
