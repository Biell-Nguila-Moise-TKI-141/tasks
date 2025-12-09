#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/** * @brief рассчитывает периметр прямоугольника
 * @param L первая сторона прямоугольника
 * @param l вторая сторона прямоугольника
 * @return возвращает рассчитанный Периметр **/
double getP(const double L,const double  l);
/**
 * @brief считывает значение, 
 * введенное с клавиатуры с проверкой ввода
 * @return считанное значение **/
double getS(const double L,const double l);
/**считывает значение, 
 * введенное с клавиатуры с проверкой ввода
 * @return считанное значение **/
double getvalue();
/**  * @brief проверяет,что переменная положительная
 * @param value значение проверяемой переменной**/
void checkvalue(const double value);
/**  * @brief Точка входа в программу
 * @return возвращает 0, если программма выполнена корректно**/

int main(){
    printf("entrez les cotes du rectangles\n");
    const double L=getvalue();
    checkvalue(L);
    const double l=getvalue();
     checkvalue(l);
    const double P=getP(L,l);
    const double S=getS(L,l);
printf("P=%.2lf,S=%.2lf\n",P,S);

     return 0;
}
double getP(const double L,const double l){

    return(L+l)*2;
    
}
double getS(const double L,const double l){

    return L*l;
} 
double getvalue(){
    double value=0 ;
    if(!scanf("%lf",&value)){
        printf("erreur");
        abort();
    }
    return value;
}
void checkvalue(const double value){
    if(value<=0){
    printf("ecrivez une valeur positive\n");
    abort();
    }
}
    



