#include <iostream>


int main()
{
    unsigned int i, liczba=0;
    i=7;
    liczba=i;
    liczba &= ~(1UL<<0);
    if(liczba!=i)
        std::cout<<liczba<<std::endl;   
}