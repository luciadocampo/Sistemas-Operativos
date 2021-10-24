// AUTOR: Daniel Rodriguez Sanchez
// AUTOR: Lucia Docampo Rodriguez

#ifndef __P1_H__
#define __P1_H__

struct delete_options;
struct listing_options;

int crear(char *[], int, list *);
int borrar(char *[], int, list *);
void walk_dir(char *, void(*)(char *, void *), void *, int, int);
void delete_entry(char *, struct delete_options *);
void cmd_delete(char *[], int, struct delete_options);
int borrarrec(char *[], int, list *);
void listing_long(char *, struct listing_options *);
void list_one(char *, struct listing_options *);
void check_command_fich(char *[], int *, struct listing_options *);
int listfich(char *[], int, list *);
void list_entry(char *, struct listing_options *);
int check_comand_dir(char *[], int, struct listing_options *);
void cmd_list(char *[], int, struct listing_options *);
int listdir(char *[], int, list *);

#endif
