#include <iostream>
#include <cmath>
#include <complex>

int main(){
    double a, b, c, discr;
    char userInput;

    std::cout<<"Based on the following formula ax^2 + bx + c = 0, enter a: ";
    std::cin>>a;
    std::cout<<"Based on the following formula ax^2 + bx + c = 0, enter b: ";
    std::cin>>b;
    std::cout<<"Based on the following formula ax^2 + bx + c = 0, enter c: ";
    std::cin>>c;

    discr = b*b - 4*a*c;
    //check for complex roots using (b^2 - 4ac) < 0
    if (discr < 0){
        std::complex<double> compNum(0.0, discr/(2*a)); // 0 + discr
        std::complex<double> compRoot = std::sqrt(compNum);

        std::cout<<"x = "<<-b/(2*a) <<" + "<<compRoot.real()<<"i"<<std::endl; //positive root
        std::cout<<"x = "<<-b/(2*a) <<" - "<<compRoot.real()<<"i"; //negative root
    }

    //check for two roots (b^2 - 4ac) > 0
    else if (discr > 0){
        std::cout<<"x = "<<-b/(2*a) + sqrt(discr)/(2*a)<<std::endl; //positive root
        std::cout<<"x = "<<-b/(2*a) - sqrt(discr)/(2*a); //negative root
    }

    //check for one root (b^2 - 4ac) = 0
    else{
        std::cout<<"x = "<<-b/(2*a); //one root
    }
    std::cout<<"\nDo you want to perform another calculation?(Y/N) ";
    std::cin>> userInput;

    if (userInput == 'Y' || userInput == 'y'){
        main();
    }
    else{
        return 0;
    }

}