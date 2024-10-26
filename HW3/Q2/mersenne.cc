#include <iostream>
#include <random>

int main()
{
    // Using Mersenne Twister without seeding
    std::mt19937 engine1;
    std::uniform_real_distribution<> u(0,1);
    for (int n = 0; n < 10; ++n) {
      std:: cout << u(engine1) << "\n";
    }
    std:: cout << "\n";

    std::random_device r; // Seed with a real random device
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937 engine2(seed);
    for (int n = 0; n < 10; ++n) {
      std:: cout << u(engine2) << "\n";
    }
}
