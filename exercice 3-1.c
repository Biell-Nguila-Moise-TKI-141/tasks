#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
/* @brief calul de la fonction Y 
avec x comme parametre de la fonction */
double getY(double x);
double getvalue ();
void checkvariation(double x_variation);
int main(){
   printf("ecrivez la valeur du debut:");
double x_start=getvalue() ;
printf("ecrivez la valeur de la fin:");
double x_end=getvalue();
printf("ecrivez la valeur de la variation :");
double x_variation=getvalue();
checkvariation(x_variation);
 double x;
 double Y=getY(x);
    for(x=x_start ;x<=x_end + DBL_EPSILON;x=x+x_variation){//c'est une boucle 
        printf("Y=%.2lf\n",getY(x));
    }
    
    return 0;
}
double getvalue (){
    double value=0 ;
    if(!scanf("%lf",&value)){
        printf("error");
        abort();
    }
}
void check(double x_variation){
    if(x_variation <=DBL_EPSILON){
        printf("erreur,ecrivez une valeur positive");
        abort();
    }
}
double getY(double x){
double Y;//c'est la variable resulat de la fonction
 Y=0.29*pow(x,3)+x-1.2502 ;
    return Y;
}


