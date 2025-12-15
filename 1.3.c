#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double getP(const double m,const double g);
double getvalue();
void check(const double value);
int main()
{
    const double g=9.8 ;
    printf("entrez la valeur de la masse :");
    const double m=getvalue();
    checkvalue(m);
    const double P=getP(double m,double g);
    printf("P=%lf,P");
    return 0;
}
double getP(const double m,const double g)
    {
    double P=m*g;
    return P;
    }
double getvalue()
    {
        double value=0;
        if(!scanf("lf",&value))
            {
                printf("erreur");
                abort();
            }
    return value ;
    }
void checkvalue (const double value)
{
    if(value<=0)
    {
        printf("ecrivez une valeur positive");
        abort ();
    }

}
