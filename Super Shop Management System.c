#include <stdio.h>

struct Product {
    int id;
    char name[50];
    float price;
};

int main() {
    struct Product products[5] = {
        {1, "Milk", 2.5},
        {2, "Bread", 1.2},
        {3, "Eggs", 3.0},
        {4, "Apple", 5.2},
        {5, "Coconut", 2.8}
    };

    int choice, qty;
    float total = 0;
    char continue_shopping;

    printf("Welcome to Super Shop!\nAvailable Products:\n");
    for (int i = 0; i < 5; i++) {
    printf("%d. %s - $%.2f\n", products[i].id, products[i].name, products[i].price);
    }

    while (1) {
        printf("\n Enter product ID: (0 to checkout): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice == 0) break;

        if (choice > 0 && choice <= 5) {
            printf("Enter quantity: ");
            scanf("%d", &qty);
            total += qty * products[choice - 1].price;
            printf("Added %d x %s. Subtotal: $%.2f\n", qty, products[choice - 1].name, total);

            printf("Do you want to buy more items? (y/n): ");
            scanf(" %c", &continue_shopping);

            if (continue_shopping == 'n' || continue_shopping == 'N') {
                break;
            }
        } else {
            printf("Invalid product ID!\n");
        }
    }

    printf("\nTotal: $%.2f\nThank you for shopping with us!\n", total);

    return 0;
}
