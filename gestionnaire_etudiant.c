/* Inclusion des bibliothèques standard */
#include<stdio.h>   // Pour les entrées/sorties (printf, scanf, fopen, etc.)
#include<stdlib.h>  // Pour les fonctions standard (malloc, free, qsort)
#include<string.h>  // Pour les fonctions de manipulation de chaînes (strcmp)
#include<locale.h>  // Pour affiché correctement les accents
//pour afficher les accents
#include<locale.h>
//le mot FICHIER remplace etudiant.txt dans les ligne à suivre
#define FICHIER "etudiant.txt"
#define TAILLE_CHAMP 50 
//notre dictionaire
typedef struct {
	int id;
	char nom[50];
	char prenom[50];
	char classe[50];
} Etudiant;
//Ajouter les étudiant et les stocker dans le fichier "etudiant.txt"
void ajouterEtudiant() {
    FILE *f = fopen(FICHIER, "a");
    if (!f) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
	printf("\n--- AJOUTER UN ETUDIANT ---\n\n");
    Etudiant e;
    printf("ID : ");
    scanf("%d", &e.id);
    printf("Nom : ");
    scanf(" %s", &e.nom);
    printf("Prenom : ");
    scanf(" %s", &e.prenom);
    printf("Classe : ");
    scanf(" %s", &e.classe);

    fprintf(f, "%d;%s;%s;%s\n", e.id, e.nom, e.prenom, e.classe);
    fclose(f);
    printf("Étudiant ajouté.\n");
}
// Fonction pour afficher tous les étudiants du fichier
void afficherEtudiants() {
    // 1. Ouvrir le fichier en mode lecture ("r" = read)
    FILE *f = fopen(FICHIER, "r");
    // 2. Vérifier si le fichier s'est bien ouvert
    if (!f) {
        printf("Erreur: Impossible d'ouvrir le fichier.\n");
        return;
    }

    printf("\n=== LISTE DES ÉTUDIANTS ===\n");
    
    // 3. Créer une variable pour stocker chaque étudiant lu
    Etudiant e;
    
    // 4. Lire le fichier ligne par ligne
    // fscanf retourne le nombre d'éléments lus avec succès
    // On lit 4 éléments (id, nom, prenom, classe) séparés par des ;
    while (fscanf(f, "%d;%49[^;];%49[^;];%49[^\n]\n", 
                 &e.id, e.nom, e.prenom, e.classe) == 4) {
        
        // 5. Afficher les informations de l'étudiant
        printf("ID: %d\n", e.id);
        printf("Nom: %s\n", e.nom);
        printf("Prenom: %s\n", e.prenom);
        printf("Classe: %s\n", e.classe);
        printf("----------------------------\n");
    }

    // 6. Fermer le fichier
    fclose(f);
}
/* Fonction pour trier et afficher les étudiants par classe */
void trierEtudiants() {
    /* Ouverture du fichier en mode lecture */
    FILE *f = fopen(FICHIER, "r");
    
    /* Vérification si le fichier s'est ouvert correctement */
    if (!f) {
        printf("Aucun etudiant enregistre.\n");
        return;
    }

    /* Comptage du nombre d'étudiants dans le fichier */
    int count = 0;
    char buffer[256];  // Buffer pour lire chaque ligne
    while (fgets(buffer, sizeof(buffer), f)) {
        count++;
    }
    
    /* Retour au début du fichier pour relire les données */
    rewind(f);

    /* Allocation dynamique de mémoire pour le tableau d'étudiants */
    Etudiant *etudiants = malloc(count * sizeof(Etudiant));
    
    /* Lecture des données depuis le fichier */
    for (int i = 0; i < count; i++) {
        /* Format d'entrée : ID;Nom;Prénom;Classe */
        fscanf(f, "%d;%49[^;];%49[^;];%49[^\n]\n", 
               &etudiants[i].id,      // Lecture de l'ID
               etudiants[i].nom,      // Lecture du nom
               etudiants[i].prenom,   // Lecture du prénom
               etudiants[i].classe);   // Lecture de la classe
    }
    
    /* Fermeture du fichier */
    fclose(f);

    /* Tri du tableau avec qsort */
    qsort(etudiants,          // Pointeur vers le tableau
          count,              // Nombre d'éléments
          sizeof(Etudiant),   // Taille d'un élément
          comparerClasses);   // Fonction de comparaison

    /* Affichage des résultats triés */
    printf("\nEtudiants tries par classe:\n");
    printf("ID\tNom\t\tPrenom\t\tClasse\n");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t\t%s\t\t%s\n", 
               etudiants[i].id, 
               etudiants[i].nom, 
               etudiants[i].prenom, 
               etudiants[i].classe);
    }

    /* Libération de la mémoire allouée */
    free(etudiants);
}
//menu
void menu(){
    int choix;
    do {
        printf("\n--- GESTIONNAIRE DES ETUDIANTS ---\n\n");
        printf("1. Ajouter un étudiant\n");
        printf("2. Afficher les étudiants\n");
        printf("3. Trier les étudiants\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: 
				ajouterEtudiant(); 
				break;
            case 2: 
				afficherEtudiants(); 
				break;
            case 3: 
				trierEtudiants(); 
				break;
            case 0: printf("Au revoir !\n"); break;
            default: printf("Choix invalide.\n");
        }
    } while (choix != 0);
}
//fonction principale
int main() {
	setlocale(LC_ALL, "");
    int nbEtudiants = 0;
    menu();
    return 0;
}
