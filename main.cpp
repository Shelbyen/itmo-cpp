#include "genetical_algorithm.cpp"
// #include <iostream>


int main() {
    std::string target_string = "Hello World!";

    auto fitnessFunc = [&target_string](const GA::Carrier& c)
        {
            double value = 0;
            for (int i = 0; i < target_string.length(); i++)
            {
                value += static_cast<int>(target_string[i] == c.gens()[i]);
            }
            // std::cout << value << std::endl;s
            return target_string.length() / value;
        };

    auto population = GA::Population(600, 500);
    population.evo(fitnessFunc, 1000);
    return 0;
}
