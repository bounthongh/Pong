#include "menuGTK.h"
#include "gameSDL.h"

void on_copier_button(GtkWidget *pButton, gpointer data)
{
    GtkWidget *pTempEntry;
    GtkWidget *pTempEntry2;
    GtkWidget *pTempEntry3;
    GList *pList;
    const char *sTextIp;
    const char *sTextPort;
    const char *sTextStatus;

    s_menu *menuStruct;
    menuStruct = malloc(sizeof(s_menu));

    /* Recuperation de la liste des elements que contient la GtkVBox */
    pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)data));
    pList = g_list_next(pList);

    /* Recuperation adresse IP */
    pTempEntry = GTK_WIDGET(pList->data);

    pList = g_list_next(pList);
    pList = g_list_next(pList);

    /* Recuperation le Port */
    pTempEntry2 = GTK_WIDGET(pList->data);

    pList = g_list_next(pList);
    pList = g_list_next(pList);

    pTempEntry3 = GTK_WIDGET(pList->data);

    sTextIp = gtk_entry_get_text(GTK_ENTRY(pTempEntry));
    sTextPort = gtk_entry_get_text(GTK_ENTRY(pTempEntry2));
    sTextStatus = gtk_entry_get_text(GTK_ENTRY(pTempEntry3));

    /* Liberation de la memoire utilisee par la liste */
    g_list_free(pList);

    strcpy(menuStruct->ipPort,sTextIp);
    strcat(menuStruct->ipPort,":");
    strcat(menuStruct->ipPort,sTextPort);
    strcat(menuStruct->ipPort,":");
    strcat(menuStruct->ipPort,sTextStatus);
    printf("%s",menuStruct->ipPort);
    game(sTextIp, sTextPort, sTextStatus);

    /*Parametre non utilisé*/
    pButton = pButton;

    gtk_main_quit();
}

int main_menu_gtk(int argc, char **argv,s_menu *menuStruct)
{
    GtkWidget *p_window = NULL;
    GtkWidget *p_main_box = NULL;
    GtkWidget *pLabelIp = NULL;
    GtkWidget *pEntryIp = NULL;
    GtkWidget *pLabelPort = NULL;
    GtkWidget *pEntryPort = NULL;
    GtkWidget *pstatuslabel = NULL;
    GtkWidget *pstatusentry = NULL;
    GtkWidget *pbutton_connect = NULL;
    GtkWidget *p_button = NULL;

    menuStruct=menuStruct;
    /* Initialisation de GTK+ */
    gtk_init (&argc, &argv);

    /* Creation de la fenetre principale de notre application */
    p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(p_window), "Jeu Pong - Creation d'une partie");
    gtk_window_resize (GTK_WINDOW(p_window), 400, 500);
    gtk_window_set_position(GTK_WINDOW(p_window), GTK_WIN_POS_CENTER);
    g_signal_connect (G_OBJECT (p_window), "destroy", G_CALLBACK (gtk_main_quit), NULL);

    /* Creation du conteneur principal */
    p_main_box = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (p_window), p_main_box);

    /* Creation du texte + entré */
    pLabelIp = gtk_label_new(NULL);
    gtk_label_set_text(GTK_LABEL(pLabelIp), "Entrer l'adresse IP du serveur :");
    pEntryIp = gtk_entry_new_with_max_length(15);
    pLabelPort = gtk_label_new(NULL);
    gtk_label_set_text(GTK_LABEL(pLabelPort), "Entrer le port du serveur :");
    pEntryPort = gtk_entry_new_with_max_length(5);
    pstatuslabel = gtk_label_new(NULL);
    gtk_label_set_text(GTK_LABEL(pstatuslabel), "s = serveur c = client");
    pstatusentry = gtk_entry_new_with_max_length(1);

    /* Creation des boutons */
    pbutton_connect = gtk_button_new_with_label("Connexion");
    g_signal_connect (G_OBJECT (pbutton_connect), "clicked", G_CALLBACK (on_copier_button),p_main_box);
    p_button = gtk_button_new_from_stock (GTK_STOCK_QUIT);
    g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (gtk_main_quit), NULL);

    /* Insertion des élément dans la GtkBox */
    gtk_box_pack_start(GTK_BOX(p_main_box), pLabelIp, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(p_main_box), pEntryIp, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(p_main_box), pLabelPort, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(p_main_box), pEntryPort, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(p_main_box), pstatuslabel, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(p_main_box), pstatusentry, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(p_main_box), pbutton_connect, TRUE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (p_main_box), p_button, FALSE, FALSE, 0);

    /* Affichage de la fenetre principale */
    gtk_widget_show_all (p_window);
    /* Lancement de la boucle principale */
    gtk_main ();
    return EXIT_SUCCESS;
}
