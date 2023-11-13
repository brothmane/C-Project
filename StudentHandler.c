#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Etudiant Etudiant;
typedef struct nodeEtudiant nodeEtudiant;
typedef struct fileEtudiant fileEtudiant;

struct Etudiant
{
    char firstnm[20];
    char lastnm[20];
    char dtbirth[15];
    char position[20];
    char address[50];
};

struct nodeEtudiant
{
    Etudiant data;
    nodeEtudiant* next;
};

struct fileEtudiant
{
    nodeEtudiant* queue;
    nodeEtudiant* tet;
};

fileEtudiant* createfile()
{
    fileEtudiant *A= (fileEtudiant*) malloc(sizeof(fileEtudiant));
    A->queue = NULL;
    A->tet = NULL;
    return A;
}

void pushEtudiant (Etudiant Etud, fileEtudiant *file)
{
    nodeEtudiant *M = (nodeEtudiant*) malloc(sizeof(nodeEtudiant));
    M->data = Etud;
    if(file->queue == NULL)
    {
        file->queue = M;
        file->tet = M;
        M->next = NULL;
    }
    else
    {
        file->queue->next = M;
        file->queue = M;
        M->next = NULL;
    }

}

Etudiant *scanEtudiant()
{
    Etudiant *Etud = (Etudiant*) malloc(sizeof(Etudiant));
    getchar();
    printf("\n Firstname : ");
    scanf("%[^\n]s",Etud->firstnm);
    getchar();
    printf("\n Lastname : ");
    scanf("%[^\n]s",Etud->lastnm);
    getchar();
    printf("\n Date of birth : ");
    scanf("%[^\n]s",Etud->dtbirth);
    getchar();
    printf("\n Position : ");
    scanf("%[^\n]s",Etud->position);
    getchar();
    printf("\n Address : ");
    scanf("%[^\n]s",Etud->address);
    getchar();
    return Etud;
}

void printEtudiant(Etudiant *Etud)
{
    printf("%-20s|%-20s|%-15s|%-20s|%-50s\n", Etud->firstnm, Etud->lastnm, Etud->dtbirth, Etud->position, Etud->address);
    printf("--------------------|--------------------|---------------|--------------------|------------------------------------------------|\n");
}

nodeEtudiant *searchEtudiant(fileEtudiant *f_Etud, char *firstname)
{
    nodeEtudiant *N = f_Etud->tet;
    while (N != f_Etud->queue && strcmp(firstname, N->data.firstnm))
    {
        N = N->next;
    }
    if(N == f_Etud->queue && strcmp(firstname, N->data.firstnm))
    {
        return NULL;
    }
    else
        return N;
}

void printfileEtudiant(fileEtudiant *Etud)
{
    if(Etud->tet == NULL)
        printf("Nothing to display...\n");
    else
    {
        nodeEtudiant *N = Etud->tet;
        printf("%-20s|%-20s|%-15s|%-20s|%-50s\n", "Firstname","Lastname","Date of birth","Position","Address");
        printf("--------------------|--------------------|---------------|--------------------|------------------------------------------------|\n");
        do
        {

            printEtudiant(&N->data);
            if(N != NULL)
                N = N->next;
        } while (N != Etud->queue && N != NULL);
        if(N != NULL)
            printEtudiant(&N->data);
    }
}

void storeEtudiant(Etudiant *Etud, char *namefile)
{
    FILE *outfileforstor = fopen(namefile,"a");
    fprintf(outfileforstor,"%s,%s,%s,%s,%s,\n", Etud->firstnm, Etud->lastnm, Etud->dtbirth, Etud->position, Etud->address);
    fclose(outfileforstor);
}

void loadfileEtudiant(fileEtudiant *Etud, char* namefile)
{
    nodeEtudiant *N = (nodeEtudiant*) malloc(sizeof(nodeEtudiant));
    FILE *outfileforload = fopen(namefile, "r");
    if(outfileforload == NULL)
        printf("\nNothing to be display...\n");
    else
    {
        while(fscanf(outfileforload,"%[^,],%[^,],%[^,],%[^,],%[^,],\n", N->data.firstnm, N->data.lastnm, N->data.dtbirth,
        N->data.position, N->data.address) != EOF)
        {
            pushEtudiant(N->data, Etud);
        }
    }
    fclose(outfileforload);
}

void deleteEtudiant(fileEtudiant *f_Etud, char *namedelete)
{
    nodeEtudiant *N = f_Etud->tet;
    if(!strcmp(N->data.firstnm, namedelete))
    {
        if(N->next == NULL)
        {
            f_Etud->tet = NULL;
            f_Etud->queue = NULL;
            free(N);
        }
        else
        {
            f_Etud->tet = N->next;
            free(N);
        }
    }
    else if(N->next != NULL)
    {
        char *nametested;
        strcpy(nametested, N->next->data.firstnm);
        while (N != f_Etud->queue && strcmp(nametested, namedelete))
        {
            N = N->next;
            if(N->next != NULL)
            strcpy(nametested, N->next->data.firstnm);
        }
        if(N != f_Etud->queue)
        {
            if(N->next == f_Etud->queue)
            {
                nodeEtudiant *M = N->next;
                f_Etud->queue = N;
                N->next = NULL;
                free(M);
            }
            else
            {
                nodeEtudiant *M = N->next;
                N->next = M->next;
                free(M);
            }
        }
        else
            printf("\nFirstname not exist...");
    }
}

void updateEtudiant(fileEtudiant *f_Etud, char* firstname, char *field_to_change)
{
    nodeEtudiant *N = searchEtudiant(f_Etud, firstname);
    if(N == NULL)
    {
        printf("\nFirstname you entred not exist...");
    }
    else
    {
        if(!strcmp(field_to_change, "Firstname"))
        {
            printf("\nFirstname : %s", N->data.firstnm);
            printf("\nEnter new Firstname : ");
            getchar();
            scanf("%[^\n]s", N->data.firstnm);
        }
        else if (!strcmp(field_to_change, "Lastname"))
        {
            printf("\nLastname : %s", N->data.lastnm);
            printf("\nEnter new Lastname : ");
            getchar();
            scanf("%[^\n]s", N->data.lastnm);
        }
        else if (!strcmp(field_to_change, "Date of birth"))
        {
            printf("\nDate of birth : %s", N->data.dtbirth);
            printf("\nEnter new Date of birth : ");
            getchar();
            scanf("%[^\n]s", N->data.dtbirth);
        }
        else if (!strcmp(field_to_change, "Position"))
        {
            printf("\nPosition : %s", N->data.position);
            printf("\nEnter new Position : ");
            getchar();
            scanf("%[^\n]s", N->data.position);
        }
        else if (!strcmp(field_to_change, "Address"))
        {
            printf("\nAddress : %s", N->data.address);
            printf("\nEnter new Address : ");
            getchar();
            scanf("%[^\n]s", N->data.address);
        }
        else
        {
            printf("\nField not exist...");
        }
    }
}

void storefileEtudiant(fileEtudiant* f_Etud, char *namefile)
{
    nodeEtudiant *N = f_Etud->tet;
    FILE *outfileforstor = fopen(namefile,"w");
    if(N == f_Etud->queue && N == NULL)
        printf("Nothing to be stored...\n");
    else if(N == f_Etud->queue)
    {
        fprintf(outfileforstor,"%s,%s,%s,%s,%s,\n", N->data.firstnm, N->data.lastnm, N->data.dtbirth, N->data.position, N->data.address);
    }
    else
    {
        while(N != f_Etud->queue)
        {
            fprintf(outfileforstor,"%s,%s,%s,%s,%s,\n", N->data.firstnm, N->data.lastnm, N->data.dtbirth, N->data.position, N->data.address);
            N = N->next;
        }
        fprintf(outfileforstor,"%s,%s,%s,%s,%s,\n", N->data.firstnm, N->data.lastnm, N->data.dtbirth, N->data.position, N->data.address);
    }
    fclose(outfileforstor);
}

int main()
{
    char choice[1];
    fileEtudiant *listetud = createfile();
    Etudiant Etud;
    loadfileEtudiant(listetud, "Etudiantlist.csv");
    do
    {
        system("clear");
        printf("             Etudiant Handler Menu           \n");
        printf( "1- Insert Etudiant\n"
                "2- Update Etudiant\n"
                "3- Delete Etudiant\n"
                "4- Search Etudiant\n"
                "5- Display list Etudiant\n"
                "6- Exit\n"
                "-------------------------\n"
                "Enter your choice : ");
        scanf("%s", &choice[0]);
        switch (choice[0])
        {
            case '1' :
            {
                Etud = *scanEtudiant();
                pushEtudiant(Etud, listetud);
                storeEtudiant(&Etud, "Etudiantlist.csv");
                break;
            }
            case '2' :
            {
                char namesearch[20];
                char field[20];
                printf("\nEnter Firstname to be updated : ");
                getchar();
                scanf("%[^\n]s", namesearch);
                printf("\nField : ");
                getchar();
                scanf("%[^\n]s", field);
                updateEtudiant(listetud, namesearch, field);
                storefileEtudiant(listetud, "Etudiantlist.csv");
                break;
            }
            case '3' :
            {
                char namedelete[20];
                printf("\nEnter Firstname to be deleted : ");
                getchar();
                scanf("%[^\n]s", namedelete);
                deleteEtudiant(listetud, namedelete);
                storefileEtudiant(listetud, "Etudiantlist.csv");
                break;
            }
            case '4' :
            {
                char namesearch[20];
                printf("\nEnter Firstname to be search : ");
                getchar();
                scanf("%[^\n]s", namesearch);
                nodeEtudiant *M = searchEtudiant(listetud, namesearch);
                if(M == NULL)
                    printf("Firstname not exist...");
                else
                    printEtudiant(&M->data);
                scanf("%s", &choice[0]);
                break;
            }
            case '5' :
            {
                printfileEtudiant(listetud);
                scanf("%s", &choice[0]);
                break;
            }

            default:
                break;
        }
    }while(strcmp(choice, "6"));
return 0;
}
