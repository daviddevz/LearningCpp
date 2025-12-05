/*
Write a program that takes two integers as input and calculates the area and 
perimeter of a rectangle formed by those side lengths.
    * Use appropriate data types for storing side lengths, area, and perimeter.
    * Validate user input to ensure positive integers are entered.
*/

#include <iostream>
#include <limits>

int main(){
    float side1, side2;

    std::cout<<"Enter length_1 ";

    do { 
        std::cin>>side1;

        if (std::cin.fail()){ // Validate input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout<<"Enter a Positive Integer ";
        }
    } while (std::cin.fail() || side1 <=0);

    std::cout<<"Enter length_2 ";

    do { 
        std::cin>>side2;

        if (std::cin.fail()){ // Validate input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout<<"Enter a Positive Integer ";
        }
    } while (std::cin.fail() || side2 <= 0);

    std::cout<<"Area of rectangle "<< (side1*side2) <<std::endl; // Area of rectangle
    std::cout<<"Perimeter of rectangle "<< 2*(side1 + side2); // Perimeter of rectangle

    return 0;
}