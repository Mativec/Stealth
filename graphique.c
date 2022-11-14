#include "graphique.h"
#include "Plateau.h"




void boutons(){
  /* bouton commencer partie , options , */
}


void init_fenetre(){
  MLV_image *image;
  MLV_create_window();
  image = MLV_load_image("image.png");
	MLV_resize_image_with_proportions( image, TAILLE_X, TAILLE_Y);


  MLV_actualise_window();
  /*boucle et affichage de boutons*/
}



void fenetre_de_jeu(){

}


void affiche_joueur(Plateau P){

}


void affiche_murs(Plateau P){

}


void affiche_gardiens(Plateau P){

}


void affiche_reliques(Plateau P){

}