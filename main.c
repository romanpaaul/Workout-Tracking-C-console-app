#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

typedef struct optiuni {
  char nume[35];
  bool active;
};

typedef struct activitati {
  char nume[35];
  int nr_calorii_arse;
  float durata_executie;
};

struct activitati activitate[100];
char nume_activitati[100][35];
int n, cnt_nume_activitati;
int frecventa_calorii[5000], calorii_MAX = 0;

void citire_date() {
  cnt_nume_activitati = 0;
  calorii_MAX = 0;

  for(int i = 0; i < 100; i++) {
    for(int j = 0; j < 35; j++) {
      nume_activitati[i][j] = '\0';
    }
  }

  FILE *fin = fopen("date.txt", "r");
  if (fin == NULL) {
      printf("Error opening input file!\n");
      return;
  }
  fscanf(fin, "%d", &n);
  
  for (int i = 0; i < n; i++) {
      fgets(activitate[i].nume, 35, fin);
      fgets(activitate[i].nume, 35, fin);
      activitate[i].nume[strlen(activitate[i].nume)-1] = '\0';

      bool sameName = false;
      for(int j = 0; j < cnt_nume_activitati; j++) {
        if(strcmp(activitate[i].nume, nume_activitati[j]) == 0)
          sameName = true;
      }
      if(sameName == false) {
        strcpy(nume_activitati[cnt_nume_activitati], activitate[i].nume);
        cnt_nume_activitati++;
      }

      fscanf(fin, "%d", &activitate[i].nr_calorii_arse);
      frecventa_calorii[(int)activitate[i].nr_calorii_arse] += 1;

      if((int)activitate[i].nr_calorii_arse > calorii_MAX) {
        calorii_MAX = (int)activitate[i].nr_calorii_arse;
      }

      fscanf(fin, "%f", &activitate[i].durata_executie);
  }
  fclose(fin);
}


void scriere_in_fisier() {
  FILE *fp = fopen("date.txt", "w");

  fprintf(fp, "%d", n);
  fprintf(fp, "%c", '\n');

  for(int i = 0; i < n; i++) {
    fprintf(fp, "%s", activitate[i].nume);
    fprintf(fp, "%c", '\n');
    fprintf(fp, "%d", activitate[i].nr_calorii_arse);
    fprintf(fp, "%c", '\n');
    fprintf(fp, "%.2f", activitate[i].durata_executie);
    fprintf(fp, "%c", '\n');
  }

  fclose(fp);

  citire_date();
}

void Window1() {
  for(int i = 0; i < n; i++) {
    printf("--------------------------------------------\n");
    printf("Activitate: %s\n", activitate[i].nume);
    printf("Nr calorii arse: %d\n", activitate[i].nr_calorii_arse);
    printf("Durata activitate(in minute): %.2f\n", activitate[i].durata_executie);
    printf("--------------------------------------------\n");
  }

  system("pause");
}

void Window2() {
  char nume[35] = {};
  int nr_calorii_arse;
  float durata_executiei;
  n++;
  printf("Introdu numele activitatii: ");
  scanf("%s", &activitate[n-1].nume);

  printf("Introdu cate calorii ai ars: ");
  scanf("%d", &activitate[n-1].nr_calorii_arse);

  printf("Introdu cat a durat toata activitatea: ");
  scanf("%f", &activitate[n-1].durata_executie);

  scriere_in_fisier();

  printf("Apasa orice tasta pentru a te intoarce la meniul principal\n");
  system("pause");
}

void Window3() {
  printf("Tipuri diferite de activitati\n");
  for(int i = 0; i < cnt_nume_activitati; i++) {
    printf("%d. %s\n", i+1, nume_activitati[i]);
  }
  printf("\n");

  printf("Scrie aici numele activitatii la care vrei sa vezi raporturile : ");
  char optiune[35];
  scanf("%s", &optiune);
  printf("\n\n");

  bool ActivitateGasita = false;
  int cnt = 0;
  for(int i = 0; i < n; i++) {
    if(strcmp(activitate[i].nume, optiune) == 0) {
      cnt += 1;
      printf("--------------------------------------------\n");
      printf("Activitate: %s\n", activitate[i].nume);
      printf("Nr calorii arse: %d\n", activitate[i].nr_calorii_arse);
      printf("Durata activitate(in minute): %.2f\n", activitate[i].durata_executie);
      printf("--------------------------------------------\n");

      ActivitateGasita = true;
    }
  }

  if(ActivitateGasita == false) {
    printf("Nu exista aceasta activitate!\n");
  }
  else {
    if(cnt > 1) printf("Ai executat aceasta activitate de %d ori! \n", cnt);
    else printf("Ai executat aceasta activitate odata! \n");
    printf("Apasa orice tasta ca sa te intorci la meniul principal\n");
  }
  system("pause");
}

void Window4() {
  for(int i = calorii_MAX; i >= 0; i--) {
    for(int j = 0; j < n; j++) {
      if((int)activitate[j].nr_calorii_arse == i) {
        printf("--------------------------------------------\n");
        printf("Activitate: %s\n", activitate[j].nume);
        printf("Nr calorii arse: %d\n", activitate[j].nr_calorii_arse);
        printf("Durata activitate(in minute): %.2f\n", activitate[j].durata_executie);
        printf("--------------------------------------------\n");
      }
    }
  }
  system("pause");
}

int main() {
  citire_date();
  bool appIsRunning = true;
  struct optiuni optiuni_meniu[10];
  strcpy(optiuni_meniu[0].nume, "1. Vizualizeaza raport activitati");
  strcpy(optiuni_meniu[1].nume, "2. Inregistreaza activitate noua"); 
  strcpy(optiuni_meniu[2].nume, "3. Filtreaza dupa tipul de activitate"); 
  strcpy(optiuni_meniu[3].nume, "4. Filtreaza dupa numarul de calorii arse(crescator, max 5000 calorii)"); 
  strcpy(optiuni_meniu[4].nume, "5. Iesi din aplicatie"); 
  optiuni_meniu[0].active = false;
  optiuni_meniu[1].active = false;
  optiuni_meniu[2].active = false;
  optiuni_meniu[3].active = false;
  optiuni_meniu[4].active = false;

  int selected = 0;

  while(appIsRunning) {
    printf("----- MENU -----\n");
    for(int i = 0; i < 5; i++) {
      if(selected == i) {
        printf("%s <<\n", optiuni_meniu[i].nume);
      }
      else {
        printf("%s\n", optiuni_meniu[i].nume);
      }
    }
    printf("Apasa W si S pentru a naviga sus-jos prin optiunile selectate\n");
    printf("Apasa E pentru a selecta optiunea aleasa\n");

    int key = getch();
    if(key == 'w' || key == 's' || key == 'e') {
      if(key == 'w') {
        if(selected == 0)
          selected = 4;
        else
          selected -= 1;
      }
      if(key == 's') {
        if(selected == 4)
          selected = 0;
        else
          selected += 1;
      }

      if(key == 'e') {
        if(selected == 0) {
          system("cls");
          Window1();
          system("cls");
        }
        if(selected == 1) {
          system("cls");
          Window2();
          system("cls");
        }
        if(selected == 2) {
          system("cls");
          Window3();
          system("cls");
        }
        if(selected == 3) {
          system("cls");
          Window4();
          system("cls");
        }
        if(selected == 4) {
          system("cls");
          printf("cam atata\n");
          appIsRunning = false;
          break;
        }
      }
    } 
    system("cls");
  }
  return 0;
}