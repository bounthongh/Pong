#ifndef __MENUGTK_H__
#define __MENUGTK_H__

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

typedef struct t_menu{
    GtkWidget *p_main_box;
    char ipPort[21];
}s_menu;

void on_copier_button(GtkWidget *pButton, gpointer data);
int main_menu_gtk(int argc, char **argv,s_menu *menuStruct);
void send_client(const char *sTextIp, const char *sTextPort);
void recv_serveur(const char *sTextIp, const char *sTextPort);
#endif
