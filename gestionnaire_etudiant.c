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
int comparerClasses(const void *a, const void *b) {
    Etudiant *e1 = (Etudiant *)a;
    Etudiant *e2 = (Etudiant *)b;
    return strcmp(e1->classe, e2->classe);
}

int comparerClasse(const void *a, const void *b) {
    const Etudiant *e1 = (const Etudiant *)a;
    const Etudiant *e2 = (const Etudiant *)b;
    return strcmp(e1->classe, e2->classe);
}

void trierEtudiants() {
    FILE *f = fopen(FICHIER, "r");
    if (!f) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }

    // Lecture dynamique dans un tableau
    Etudiant etudiants[1000]; // On suppose un max de 1000 étudiants
    int count = 0;

    while (fscanf(f, "%d;%49[^;];%49[^;];%49[^\n]\n",
                  &etudiants[count].id,
                  etudiants[count].nom,
                  etudiants[count].prenom,
                  etudiants[count].classe) == 4) {
        count++;
    }
    fclose(f);

    if (count == 0) {
        printf("Aucun étudiant trouvé.\n");
        return;
    }

    // Tri par classe
    qsort(etudiants, count, sizeof(Etudiant), comparerClasse);

    // Affichage
    printf("\n=== Étudiants triés par classe ===\n");
    printf("ID\tNom\t\tPrenom\t\tClasse\n");
    printf("--------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t\t%s\t\t%s\n",
               etudiants[i].id,
               etudiants[i].nom,
               etudiants[i].prenom,
               etudiants[i].classe);
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
