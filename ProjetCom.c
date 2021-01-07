#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define VMIN 5
#define VMAX 30

//création des types structures
typedef struct                  //création d'une structure permettant de définir les coordonnées d'une case de la grille
{int l;
 int c;
}T_Case;

typedef struct                 //création d'une structure qui permet d'enregistrer les paramètres du partie
{int nlig;
 int ncol;
 int niveau;
 int next;
 int nban;
}param_jeux;

T_Case T_Tab_Case[VMAX*VMAX]; //tableau permettant de stocker les cases bannies ou les cases voisines d'une case donnée
T_Case pion;                  //contient les coordonées du pion
T_Case ban[VMAX*VMAX]; 
int nim[VMAX][VMAX];          //tableau qui sera rempli avec la fonction calcul_nimbers qui détermine les nimbers de la grille



//FONCTIONS

/*fonctions permettant de saisir et de retourner un entier compris entre deux bornes donnes*/
int Lire_Entier(int min,int max)
{int nb;
 do
 {scanf("%d", &nb);
  if(nb<min || nb>max) printf("\nERREUR ! Le nombre doit etre compris entre %d et %d. Veuillez ressaisir le nombre: ", min, max);
 }
 while(nb<min || nb>max);
 return nb;
}

/*fonction max qui permet de retourner le maximum entre 2 nombres*/
int max(int nb1, int nb2) 
{int maximum;
 if(nb1<nb2) maximum=nb2;
 else maximum=nb1;
 return maximum;
}

/*Fonction hasard*/
int Hasard(int min,int max)
{return rand()%max+min+1;
}

/*Fonction qui teste quelle case peut être bannie ou non */
int bannissable(int i, param_jeux tab)
{int j;
 //Test des cases sur la bordure extérieure
 if ((T_Tab_Case[i].l==0) || (T_Tab_Case[i].c==0) || (T_Tab_Case[i].l==tab.nlig-1) || (T_Tab_Case[i].c==tab.ncol-1)) return (0);
 for (j=0; j<tab.nban; j++) //parcours du tableau de cases bannies
 {
  //si la case est déjà bannie, on retourne 0
  if ((T_Tab_Case[i].l == ban[j].l) && (T_Tab_Case[i].c == ban[j].c)) return (0);
  //Si la case en diagonale en haut à droite de celle actuelle est bannie, on retourne 0
  if ((T_Tab_Case[i-tab.ncol+1].l == ban[j].l) && (T_Tab_Case[i-tab.ncol+1].c == ban[j].c)) return (0);
  //si la case en diagonale en bas à gauche de celle actuelle est bannie, on retourne 0  
  if ((T_Tab_Case[i+tab.ncol-1].l == ban[j].l) && (T_Tab_Case[i+tab.ncol-1].c == ban[j].c)) return (0);
 }
 return (1);
}

/*Fonction qui définit au hasard quelles cases seront bannies en fonction des contraintes de la fonction bannissable*/
void hasard_ban(param_jeux tab)
{int i,j,i_tab_ban=0;
 srand((unsigned int)time(NULL));
 while (i_tab_ban < tab.nban)
 {
  // au hasard
  i = rand()%(tab.nlig*tab.ncol)+1;
  //si la case en diagonale en haut à droite de celle actuelle n'est pas bannie, alors on rajoute la case actuelle dans les bannies
  if (bannissable(i, tab) == 1)
  {ban[i_tab_ban].l=T_Tab_Case[i].l;
   ban[i_tab_ban].c=T_Tab_Case[i].c;
   i_tab_ban+=1;
  }
 }
}

/*Fonction qui lit les paramètres de jeu à l'aide de la fonction Lire_Entier*/
param_jeux Lire_Parametres() 
{param_jeux resultat;
 srand((unsigned int)time(NULL));
 printf("---Parametres du jeu:---\n");
 printf("  Nombre de lignes de la grille: "); resultat.nlig=Lire_Entier(VMIN,VMAX);     //lit le nombre de ligne choisit
 printf("  Nombre de colonnes de la grille: "); resultat.ncol=Lire_Entier(VMIN,VMAX);   //lit le nombre de colonnes choisit
 printf("   1.Niveau Debutant\n");
 printf("   2.Niveau Moyen\n");
 printf("   3.Niveau Expert\n");
 printf("   4.Niveau Virtuose\n");
 printf("Quel niveau de difficultes souhaitez-vous ? : ");
 resultat.niveau=Lire_Entier(1,4);                                      //lit le niveau de difficulté que le joueur a choisit
 printf("Qui commence ?\n L'Ordinateur (1) - Joueur (2): ");
 resultat.next=Lire_Entier(1,2);                                        //lit le choix de départ du jeu du joueur 
 printf("\n");
 resultat.nban=rand()%max(resultat.nlig,resultat.ncol)+1;               //définit au hasard le nombre de cases bannies
 return resultat;                                                //renvoie tous les choix effectués par le joueur
}

/*Fonction qui remplit la table des paramètres*/
void remplit(param_jeux tab)
{int i,j;
 for(i=0;i<tab.nlig;i++)
 {for(j=i*tab.ncol;j<tab.ncol*(i+1);j++)
  {T_Tab_Case[j].l=i;
   T_Tab_Case[j].c=j%tab.ncol;
  }
 }
}

/*Fonction qui crée la grille dans laquelle le jeu va se dérouler */
void afficher(param_jeux tab,T_Case pion)
{int i,j,k,bannie;
 printf("  ");
 //affichage du numéro de colonne
 for (i=0; i<tab.ncol; i++)
 {if(i<=9) printf("   %d",i+1);
  else printf("  %d",i+1);
 }
 printf("\n");
 //affichage du numéro de la ligne
 for (i=0; i<tab.nlig; i++)
 {printf("%2d |",i+1);
 //définit ce qui sera affiché dans chaque case de chaque ligne
  for(j=i*tab.ncol; j<tab.ncol*(i+1);j++) 
  {bannie=0;
   for (k=0; k<tab.nban; k++)
     if (T_Tab_Case[j].l==ban[k].l && T_Tab_Case[j].c==ban[k].c) bannie=1;
   if (T_Tab_Case[j].l==pion.l && T_Tab_Case[j].c==pion.c) printf(" O |");  //définit le symbole du pion
   else if (bannie) printf(" X |");   //définit le symbole d'une case bannie
   else printf(" - |"); //définit une case simple
   }
  printf("\n"); //pour sauter une ligne entre chaque case
 }
}

/*Fonction qui remplit la table nim en début de partie*/
void calcul_nimbers(param_jeux tab)
{int i=tab.nlig-1, j=tab.ncol-1, k, bannie, compt=1, full=1, vois;
 nim[i][j]=0;                           //on commence par numéroter la case en bas à gauche : le puit
 while (full<=tab.nlig*tab.ncol)        //tant que toutes les cases ne sont pas numérotées
 {vois=0;
  for (k=1; k<=2; k++)
  {if ((i+k)<tab.nlig)                  //si la case est à l'intérieur du tableau
   if (nim[i+k][j]!=1) vois=1;          //si la case en dessous possède la valeur 0 (différent de 1)
   if ((j+k)<tab.ncol)
   if (nim[i][j+k]!=1) vois=1;          //si la case à droite possède la valeur 0 (différent de 1)
  }
 }
}

/*Fonction qui définit les coups, les déplacements possibles*/
int coup_pos(param_jeux par, T_Case pion, T_Case *tab)
{
 int mouv=1, i_coup_pos=0;
 int i,j;
 printf("Vous pouvez vous deplacer aux cases :\n");
 //on cherche les cases sur la même colonne pour lesquelles le mouvement est possible
 for (j=1; j<=2; j++)
 {i=0;
  //on vérifie toutes les cases du tableau des cases bannies
  while (i<par.nban && mouv==1)
  {if (pion.l+j==ban[i].l && pion.c==ban[i].c) mouv=0;   //si la case en dessous est bannie le mouvement n'est pas possible      
   else if (pion.l+j >= par.nlig) mouv=0;                //si la case en dessous est en dehors du tableau, le mouvement n'est pas possible
   else mouv=1;                                          //sinon le mouvement est possible
   i+=1;
  }
  if (mouv==1)                                           //si le mouvement est possible
  {printf("(%d:%d)", pion.l+j+1, pion.c+1);              //on affiche la case sur laquelle le mouvement est possible
   tab[i_coup_pos].l=pion.l+j;                           //et on rajoute cette case dans le tableau des coups possibles
   tab[i_coup_pos].c=pion.c;
   i_coup_pos+=1;
  }
 }
 //on refait la même opération pour les cases en lignes
 mouv=1;
 for (j=1; j<=2; j++)
 {i=0;
  while (i<par.nban && mouv==1)                        //on vérifie les cases du tableau des cases bannies
  {if (pion.l==ban[i].l && pion.c+j==ban[i].c) mouv=0; //si la case en dessous est bannie
   else if (pion.c+j >= par.ncol) mouv=0;              //si la case est en dehors du tableau
   else mouv=1;                                        //sinon le mouvement est possible
   i+=1;
  }
  if (mouv==1)                                         //Mouvement possible
  {printf("(%d:%d)", pion.l+1, pion.c+j+1);            //on affiche la case sur laquelle le mouvement est possible
   tab[i_coup_pos].l=pion.l;
   tab[i_coup_pos].c=pion.c+j;
   i_coup_pos+=1;
  }
 }
 printf("\n\n");
 return i_coup_pos;
}


/*Fonction qui gère le choix des coups possibles pour le joueur*/
T_Case coup_joueur(param_jeux par, T_Case pion)
{int i, l=0, c=0, bon;
 int nb_coup_pos;
 T_Case tab_coup_pos[4];                          //tableau des coups possible
 nb_coup_pos=coup_pos(par, pion, tab_coup_pos);   //nombre de coups possible
 while (l==0 && c==0)
 {i=0;
  printf("Choisir la case ou vous voulez deplacer votre pion :\n");
  scanf("%d%d",&l,&c);
  printf("\n");
  while((l > par.nlig)||(c > par.ncol)||((l > pion.l+3)&&(c > pion.c+3))||((l <= pion.l+3)&&(c > pion.c+3))||((c > pion.c+3)&&(l > pion.l+3))||((c <= pion.c+3)&&(l > pion.l+3))||(l <= pion.l)||(c <= pion.c))
      {
        printf("Impossible case indisponible \n");
        printf("Choisir case disponible==>");
        scanf("%d%d",&l,&c);
        printf("\n");
      }
  while (i<nb_coup_pos && ((l-1) != tab_coup_pos[i].l || (c-1) != tab_coup_pos[i].c)) i+=1;
  if ((l-1) == tab_coup_pos[i].l && (c-1) == tab_coup_pos[i].c) bon=1;
 }
 pion.l=l-1;
 pion.c=c-1;
 afficher(par, pion);                                                      //affiche la grille avec la nouvelle position choisit
 printf("Vous avez deplace le pion a la case (%d:%d)\n", pion.l+1, pion.c+1);    //affiche où on a déplacé le pion
 return (pion);
}

/*Fonction qui définit les coups gagnant pour l'ordinateur*/
T_Case coup_ordi_gagnant(param_jeux par, T_Case *tab_gagnant, T_Case pion)
{int i, j, k, nb_coup_pos, pos=0;
 T_Case tab_coup_pos[4];
 nb_coup_pos=coup_pos(par, pion, tab_coup_pos);
 for (i=0; i<nb_coup_pos; i++)
  for (j=0; j<par.nlig; j++)
   for (k=0; k<par.ncol; k++)
    if (tab_coup_pos[i].l==j && tab_coup_pos[i].c==k && nim[j][k]==0)
    {tab_gagnant[pos].l = tab_coup_pos[i].l;
     tab_gagnant[pos].c = tab_coup_pos[i].c;
     pos+=1;
    }
 if (pos==0)
 {i=rand()%nb_coup_pos;
  pion.l=tab_coup_pos[i].l;
  pion.c=tab_coup_pos[i].c;
  printf("Pas de coup gagnant possible, donc coup au hasard\n");
 }
 else
 {i=rand()%pos;
  pion.l = tab_gagnant[pos-1].l;
  pion.c = tab_gagnant[pos-1].c;
  printf("coup gagnant effectue\n");
 }
 afficher(par, pion);
 printf("L'ordinateur a deplace le pion a la case (%d:%d)\n\n", pion.l+1, pion.c+1);
 return (pion);
}

/*Fonction qui défnit les coups possibles au hasard pour l'ordinateur*/
T_Case coup_ordi_hasard(param_jeux par, T_Case pion)
{int i, nb_coup_pos;
 T_Case tab_coup_pos[4];
 nb_coup_pos=coup_pos(par, pion, tab_coup_pos);
 i=rand()%nb_coup_pos;
 pion.l=tab_coup_pos[i].l;
 pion.c=tab_coup_pos[i].c;
 afficher(par, pion);                                                           //on affiche la grille avec la nouvelle position du pion
 printf("L'ordinateur a deplace le pion a la case (%d:%d)\n\n", pion.l+1, pion.c+1);  //affiche où l'ordinateur a choisit de déplacer son pion
 return (pion);
}



void Menu() //Affichage du menu avec le choix
{
    /*int choix;
    int regle();
    system("cls");//clear de la console*/
    printf(".-----..----..-. .-.   .----.  .----.   .-. .-..-..-.   .-.\n");
    printf("`-, ,-'| .--'| | | |   | ,-, \\ | .--'   |  \\| || ||  \\ /  |\n");
    printf("  | |  | |== | | | |   | | |  || |==    | .   || ||   .   |\n");
    printf(".-| |  | '--.| |_| |   | `-' / | '--.   | |\\  || || |\\ /| |\n");
    printf("`---'  `----'`-----'   `----'  `----'   `-' `-'`-'`-' ` `-'\n");
    printf("\n");
    printf("Groupe 3.2: Loic,Ines,Dorian\n");
    printf("\n");
}

/*int regle() //Regles du jeu (pas utiliser)
{   int choix_r;
    system("cls");//clear de la console
    printf("Les regles sont simple: \n\n");
    printf("  A tour de role, chaque joueur deplace le pion,\n");
    printf("  soit de une ou de deux cases vers la droite,\n");
    printf("  soit de une ou de deux cases vers le bas.\n");
    printf("  Les cases bannies sont infranchissables\n");
    printf("  (le chevauchement de ces cases est donc interdit).\n\n");
    printf("1.Retour Menu  2.Quitter le jeu\n\n");
    scanf("%d", &choix_r);
    if(choix_r!=1)exit(0);
}*/

/*CORPS DU PROGRAMME*/
int main()
{
//declarations des variables
 int nlig,ncol, Has;
 T_Case pion;
 int fin=0;
 T_Case *tab_gagnant;
 pion.l=0;
 pion.c=0;
 char *str1="-->GAME LOSE<--";
 char *str2="-->GAME WIN<--";
 char *str3;
 param_jeux params;
 Menu();
 params=Lire_Parametres();        //on affiche les questions pour les paramètres du jeu
 remplit(params);                 //on remplit le tableau des paramètres du jeu
 printf("C'est parti !\n");
 hasard_ban(params);              //on définit les cases bannies au hasard
 afficher(params,pion);     //on affiche la grille du jeu
 
 //On "démarre" la partie jusqu'a ce qu'elle soit gagnée ; début de la partie
 do
 {switch(params.next)
 //Si c'est à l'ordi de jouer
  {case 1:
   {Has=Hasard(1,100);
    switch(params.niveau)
    {case 1:                                                          //niveau 1 choisit, l'ordi joue au hasard
     {if(Has<=10) pion=coup_ordi_gagnant(params,tab_gagnant,pion);
      else if(Has>10) pion=coup_ordi_hasard(params,pion);
      break;
     }
     case 2:                                                          //niveau 2 choisit, l'ordi a 1/3 chance de faire un coup gagnant
     {if(Has<=50) pion=coup_ordi_gagnant(params,tab_gagnant,pion);                  
      else if(Has>50) pion=coup_ordi_hasard(params,pion);             //sinon coup au hasard
      break;
     }
     case 3:                                                          //niveau 3 choisit, l'ordi a 2/3 chance de faire un coup gagnant
     {if(Has<=90) pion=coup_ordi_gagnant(params,tab_gagnant,pion);
      else if(Has>90) pion=coup_ordi_hasard(params,pion);             //sinon coup au hasard
      break;
     }
     case 4:pion=coup_ordi_gagnant(params,tab_gagnant,pion);          //l'ordi joue un coup gagnant
    }
    params.next=2;
 
    if((pion.l==params.nlig-1)&&(pion.c==params.ncol-1))              //Si victoire de l'ordinateur
    {fin=1;
     str3=str1;                                                       //On affecte à str3 que le joueur a perdu
    }
    break;
   }
   //Si c'est au joueur de jouer
   case 2:
   {pion=coup_joueur(params,pion);                                    //Le pion prend la position que le joueur à choisit
    params.next=1;
    if((pion.l==params.nlig-1)&&(pion.c==params.ncol-1))              //Si victoire du joueur
    {fin=1;
     str3=str2;                                                       //on affecte à str3 que le joueur a gagné
    }
    break;
   }
  }
 }
 //Si on est à la fin du jeu
 while (fin!=1);
 printf("\nC'est termine,%s",str3); //On affiche si le joueur a gagné ou perdu
 printf("\n\n*--Merci d'avoir joue a notre jeu de nim--*\n");
 system("pause");
}
