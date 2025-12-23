#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
/**
 * @brief Вычисляет значение математической функции Y(x)
 * 
 * Вычисляет значение функции: Y(x) = 0.29 * x³ + x - 1.2502
 * 
 * @param x - аргумент функции
 * @return double - значение функции Y в точке x
 * 
 * @formula Y = 0.29 * x³ + x - 1.2502
 * @domain Все действительные числа (x ∈ ℝ)
 */
double getY(double x);
/* 
 * @file: program.c
 * @brief: Программа вычисления значений математической функции Y(x)
 *         в заданном диапазоне с заданным шагом
 */
 /**
 * @brief Получает числовое значение от пользователя
 * 
 * Функция считывает число типа double из стандартного ввода.
 * В случае ошибки ввода завершает программу с сообщением об ошибке.
 * 
 * @return double - считанное значение
 * @note Программа завершается через abort() при ошибке ввода
 */
double getvalue ();

/**
 * @brief Проверяет корректность значения шага (вариации)
 * 
 * Проверяет, что шаг вычислений является положительным числом.
 * Использует DBL_EPSILON для сравнения с нулем с учетом погрешности
 * представления чисел с плавающей точкой.
 * 
 * @param x_variation - значение шага для проверки
 * @note Программа завершается через abort() если шаг <= DBL_EPSILON
 */
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

