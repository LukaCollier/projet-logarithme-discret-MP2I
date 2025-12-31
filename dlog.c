#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* Tous les calculs sont effectues modulo 2**31 - 1 */
/* Les nombres sont representes par leur ecriture en binaire, en tant que chaine de caracteres de taille  */

static char zero[] = "0000000000000000000000000000000";
static char un[] = "0000000000000000000000000000001";
static char sept[] = "0000000000000000000000000000111"; // A completer !
static char q[] = "1111111111111111111111111111111"; //2^31-1
static char sqrtq[] = "0000000000000001011010100000101"; //46341

void print_endline(char s[])
{
  printf("%s\n",s);
}

void print_bool(bool b)
{
  if (b)
    {
      printf("true\n");
    }
  else
    {
      printf("false\n");
    }
}
bool is_zerowithonly1(char a[]){ // complexité: O(n)
  bool v=true;
  int i =0;
  while(a[i]!='\0'){ //Pour tout i de a[0] à a[i-1] le caractère est différent de '\0'
    if (a[i]=='0'){
      v=false;
    }
    i++;
  }
  if (v==true) { //remplace la chaine de caractère par que des 0 si la liste est composé uniquement de 1
    strcpy(a,zero);
  }
}

bool is_equal(char a[], char b[]) // a == b complexité O(n)
{
  assert (31 == strlen(a));
  assert (31 == strlen(b));
  int i =0 ;
  is_zerowithonly1(a);
  is_zerowithonly1(b);
  while (a[i]!='\0' && b[i]!='\0'){ // Pour tout i<len(a) a[0]...a[i-1] et b[0]...b[i-1] différents du caractère '\0'
    if (a[i]!=b[i]){
      return false;
      }
    i=i+1;
  }
  return true;
}

bool is_greater(char a[], char b[]) // a > b complexité O(n)
{
  assert (31 == strlen(a));
  assert (31 == strlen(b));
  is_zerowithonly1(a);
  is_zerowithonly1(b);
  int i = 0;
  while (a[i]!='\0' && b[i]!='\0'){ //Pour tout i<len(a) a[0]...a[i-1] et b[0]...b[i-1] différents du caractère '\0'
    if(a[i]>b[i]){
      return true ;
    }
    i=i+1;
    }
  return false;
}


void negate(char a[]) // a = -a complexité O(n) chaine à n 0 et k 1
{
  assert (31 == strlen(a));
  int i=0;
  while (a[i]!='\0'){
    if (a[i]=='1'){
      a[i]='0';
    }
    else{
      a[i]='1';
    }
    i++;
  }
  // à la fin de la boucle on a maintenant k 0 et n 1

}

void add_to(char a[], char b[]) // a = a + b
{
  assert (31 == strlen(a));
  assert (31 == strlen(b));
  is_zerowithonly1(b);
  is_zerowithonly1(a);
  char c = '0';
  char vai=a[30];
  char vbi=b[30];
  for (int i = 30 ; i>=0;i--){
    vai=a[i];
    vbi=b[i];
    if (vai=='1' && vbi=='1' && c=='1'){
      a[i]='1';
      c='1';
    }
    else if ((vai=='1' && vbi =='1')|| (vai=='1' && c=='1') || (vbi=='1' && c=='1')){
      a[i]='0';
      c='1';
    }
    else if (vai=='0' && vbi=='0' && c=='0'){
      a[i]='0';
      c='0';
    }
    else{ // si uniquement une seule valeur possède '1' 
      a[i]='1';
      c='0';
    }
  }
  if (c=='1'){ //nécessite un nouveau passage si on a encore une retenue supérieur à '0'
    add_to(a,un);
  }

}

void d_gauche(char a[]){ //a=a*2 complexité O(n); réalise un décalage vers la gauche des valeurs dans la chaine de caractère
  assert (31 == strlen(a));
  int i = 0;
  char temp = a[0];
  while (i<30){
    a[i]=a[i+1];
    i++;
  }
  a[30]=temp;
}




void d_droite(char a[] ) { //b=b/2  complexité O(n); réalise un décalage vers la droite des valeurs dans la chaine de caractère et le bit de poids le plus fort devient 0
  assert (31 == strlen(a));
  int i = 30;
  while (i>0){
    a[i]=a[(i-1)];
    i--;
  }
  a[0]='0';
}

void mult_by(char a[], char b[]) // a = a * b
{
  assert (31 == strlen(a));
  assert (31 == strlen(b));
  char temp[31]="0000000000000000000000000000000";
  while(!is_equal(b,zero)){
    if (b[30]=='1'){
      add_to(temp,a); // ajoute a dans temp
    }
    d_gauche(a);// multiplie par 2 a
    d_droite(b);// divise par 2 b
  }
  strcpy(a,temp); // remplace les valeur du tableau par ceux de temp


}

void expo(char a[], char b[]) // a = a ** b
{
  assert (31 == strlen(a));
  assert (31 == strlen(b));
  char temp[31]="0000000000000000000000000000001";
  char valatemp[31]="0000000000000000000000000000000";
  char valatemps[31]="0000000000000000000000000000000";
  char buff[32];
  strcpy(buff,b);//copie de b
  while(!is_equal(b,zero)){
    if (b[30]=='1'){
      strcpy(valatemps,a); //sécurité pour évité de perde les valeurs du tableau a
      mult_by(temp,valatemps); //multiplie temp par a 
    }
    strcpy(valatemp,a); //sécurité pour évité de perde les valeurs du tableau a
    mult_by(a,valatemp); //a**2
    d_droite(b);
  }
  strcpy(a,temp);// remplace les valeur du tableau par ceux de temp//
  strcpy(b,buff);// remet les valeur de b initiale
  //printf("%s\n",a);


}

void naif_dlog(char a[], char b[]) // a = dlog_b(a)
{
  assert (31 == strlen(a));
  assert (31 == strlen(b));
  char x[31]="0000000000000000000000000000000";
  char temp[31]="0000000000000000000000000000001";
  char gigtemp[31]="0000000000000000000000000000000";
  while(!is_equal(temp,a)){
    strcpy(gigtemp,b);
    mult_by(temp,gigtemp);
    add_to(x,un);

  }
  printf("%s\n",x);
  strcpy(a,x);


}

void dlog(char a[], char b[]) // baby step - giant step
{
  assert (31 == strlen(a));
  assert (31 == strlen(b));
  char res[32];
  char tab[46341][32]; // tableau contenant les valeur de 7^k avec k compris entre 0 et 46341 compris
  char n[32];
  char temp[]="0000000000000000000000000000001";
  char gigtemp[]="0000000000000000000000000000000";
  bool val=false;
  char septexp_giantstep[32];
  strcpy(septexp_giantstep,b);
  expo(septexp_giantstep,sqrtq);
  strcpy(tab[0],temp);
  for(int i=1;i<=46341;i++){
    strcpy(gigtemp,septexp_giantstep);
    mult_by(temp,gigtemp);
    strcpy(tab[i],temp);
    //printf("%s\n",tab[i]);
  }
  strcpy(n,zero);
  char l[32];
  strcpy(l,zero);
  char btemp[32];
  while (!val){
    for(int k=0;k<=46341;k++){
      if (is_equal(a,tab[k])){
        val=true;
        negate(n);
        strcpy(temp,sqrtq);
        mult_by(l,temp);
        add_to(n,l);
        printf("%s\n",n);
        return ;
      }
      add_to(l,un);
    }
    strcpy(l,zero);
    strcpy(btemp,b);
    mult_by(a,btemp);
    add_to(n,un);
  }

}

int main(int argc, char *argv[])
{
  char target0[] = "1111111111111111111111111111110";
  char target1[] = "0011111111001000010000000100110";
  char target2[] = "1011010001101011101011001100111";
  char x[] = "0111111111111111111111111111111";
  /*print_bool(is_greater( target0 , target1)),print_newline();
  print_bool(is_greater( target1 , target0)),print_newline();
  print_bool(is_greater( target1 , target1)),print_newline();
  print_bool(is_equal( target1 , target0)),print_newline();
  print_bool(is_equal( target1 , target1)),print_newline();
  char z[] = "0000000000000000000000000000000";
  char sept[] = "0000000000000000000000000000111";
  negate (z);*/
  /*negate (sept);*/
  //add_to (zero,sept);
  //add_to(target2 , target1);
  /*d_droite(target0);*/
  /*d_gauche(target0);*/
  char unn[] = "0000000000000000000000000000010";
  //d_droite(target1);
  //mult_by(target1,unn);
  //expo(sept,x);
  char a[] ="1111111111111111111111111111111";
  //is_zerowithonly1(a);
  //printf("%s\n",a);
  //expo(sept,x);
  //naif_dlog(target2,sept);
  //expo(sept,target1);
  char val[]="0101010101010101010101010101010";
  //expo(sept,val);
  dlog(target2,sept);
  //faux char b[]="1111111111111111001001101100011";
  //expo(sept,b);

  //expo(sept,sqrtq);
  return 0;
}
