#include <stdio.h>
#include <cs50.h>
#include <math.h>


int main (void)
{
    double round(double x);
    int quartercount;
    int quartermod;
    int dimecount;
    int dimemod;
    int nicklecount;
    int nicklemod;
    int pennycount;
    int converted;
    float input;

    do
    {
        printf ("How much change do you need in dollar form?\n");
        input = get_float ();
        if(input<0)
        printf("Number should be greater than zero.");
    }
    while (input<0);

        //convert into workable number
        converted =  round(input * 100);


    //quarters
    quartercount = converted / 25; //how many quarters
    quartermod = converted % 25;

   //dimes
    dimecount = quartermod / 10; //how many dimes from remaining change
    dimemod = quartermod % 10;

    //nickles
    nicklecount = dimemod / 5; //how many nickles from remaining change
    nicklemod = dimemod % 5;

    //pennies
    pennycount = nicklemod / 1;

   //print sum of all coin counts
   printf("Coin Count:%d\n",quartercount + dimecount + nicklecount + pennycount);

}





