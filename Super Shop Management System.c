#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Product {
    int id;
    char name[50];
    float price;
};

struct CartItem {
    struct Product product;
    int quantity;
};

// Check if cart has all 5 products
bool hasAllProducts(struct CartItem cart[], int cartCount) {
    int flags[5] = {0};
    for (int i = 0; i < cartCount; i++) {
        int id = cart[i].product.id;
        if (id >= 1 && id <= 5)
            flags[id - 1] = 1;
    }
    for (int i = 0; i < 5; i++)
        if (flags[i] == 0)
            return false;
    return true;
}

// Count total quantity across cart
int countTotalQuantity(struct CartItem cart[], int cartCount) {
    int totalQty = 0;
    for (int i = 0; i < cartCount; i++)
        totalQty += cart[i].quantity;
    return totalQty;
}

// Calculate discount
float calculateDiscount(struct CartItem cart[], int cartCount, bool isSuperOffer) {
    float discount = 0;
    if (isSuperOffer) {
        float original = 0;
        for (int i = 0; i < cartCount; i++)
            original += cart[i].product.price * cart[i].quantity;
        discount = original * 0.20;
    } else {
        for (int i = 0; i < cartCount; i++) {
            if (cart[i].quantity >= 10) {
                float original = cart[i].product.price * cart[i].quantity;
                discount += original * 0.10;
            }
        }
    }
    return discount;
}

// Calculate final price
float calculateTotal(struct CartItem cart[], int cartCount, bool isSuperOffer) {
    float total = 0;
    for (int i = 0; i < cartCount; i++) {
        float price = cart[i].product.price;
        int qty = cart[i].quantity;
        float itemTotal = price * qty;
        if (!isSuperOffer && qty >= 10)
            itemTotal *= 0.90;
        total += itemTotal;
    }
    return total;
}

void displayCart(struct CartItem cart[], int cartCount) {
    if (cartCount == 0) {
        printf("🛒 Your cart is empty.\n");
        return;
    }
    printf("\n🛒 Your Cart:\n");
    for (int i = 0; i < cartCount; i++) {
        printf("%d. %s x %d\n", cart[i].product.id, cart[i].product.name, cart[i].quantity);
    }
}

int findInCart(struct CartItem cart[], int cartCount, int productId) {
    for (int i = 0; i < cartCount; i++) {
        if (cart[i].product.id == productId)
            return i;
    }
    return -1;
}

int main() {
    struct Product products[5] = {
        {1, "Milk", 2.0}, {2, "Bread", 1.0}, {3, "Eggs", 3.0}, {4, "Apple", 5.0}, {5, "Coconut", 2.0}
    };
    struct CartItem cart[100];
    int cartCount = 0;

    printf("🏪 Welcome to Super Shop!\n");

    while (1) {
        printf("\n🛍 Available Products:\n");
        for (int i = 0; i < 5; i++) {
            printf("%d. %s - $%.2f 🎁 (10%% off on 10+ units)\n", products[i].id, products[i].name, products[i].price);
        }
        printf("\n🌟 Special Offer: Buy ALL 5 items and 15+ total units to unlock 20%% OFF on the whole cart!\n");

        int choice, qty;
        printf("\nEnter Product ID to buy (0 to checkout): ");
        scanf("%d", &choice);
        if (choice == 0) break;

        if (choice >= 1 && choice <= 5) {
            printf("Enter quantity: ");
            scanf("%d", &qty);

            int index = findInCart(cart, cartCount, products[choice - 1].id);
            if (index >= 0)
                cart[index].quantity += qty;
            else {
                cart[cartCount].product = products[choice - 1];
                cart[cartCount].quantity = qty;
                cartCount++;
            }
            displayCart(cart, cartCount);
        } else {
            printf("⚠️ Invalid product ID.\n");
        }
    }

    // Optional cart editing
    char editChoice;
    printf("\nWould you like to edit your cart before final Checkout? (y/n): ");
    scanf(" %c", &editChoice);
    while (editChoice == 'y' || editChoice == 'Y') {
        displayCart(cart, cartCount);
        int choice, qty;
        printf("Enter Product ID to update your product (0 to Checkout): ");
        scanf("%d", &choice);
        if (choice == 0) break;

        int index = findInCart(cart, cartCount, choice);
        if (index >= 0) {
            printf("Current quantity of %s: %d\n", cart[index].product.name, cart[index].quantity);
            printf("Enter quantity to adjust (+/-): ");
            scanf("%d", &qty);
            cart[index].quantity += qty;
            if (cart[index].quantity <= 0) {
                for (int j = index; j < cartCount - 1; j++)
                    cart[j] = cart[j + 1];
                cartCount--;
            }else {
                printf ("Update quantity of %s to %d\n",cart[index].product.name, cart[index].quantity);
            }
        } else {
            printf("Product not found in cart.\n");
        }
        printf("Edit another items? (y/n): ");
        scanf(" %c", &editChoice);
    }

    // Choose payment
    char paymentOption[20];
    int paymentChoice;
    printf("\n💳 Choose a payment method:\n");
    printf("1. Bkash\n2. Nagad\n3. Rocket\n4. BankCard\n5. Google Pay\n");
    printf("Enter option: ");
    scanf("%d", &paymentChoice);

    switch (paymentChoice) {
        
        case 1: strcpy(paymentOption, "Bkash"); break;
        case 2: strcpy(paymentOption, "Nagad"); break;
        case 3: strcpy(paymentOption, "Rocket"); break;
        case 4: strcpy(paymentOption, "BankCard"); break;
        case 5: strcpy(paymentOption, "Google Pay"); break;
        default: strcpy(paymentOption, "Unknown"); break;
    }

    // Check discount eligibility
    bool allItems = hasAllProducts(cart, cartCount);
    int totalQty = countTotalQuantity(cart, cartCount);
    bool useSuperOffer = (allItems && totalQty >= 15);

    float discount = calculateDiscount(cart, cartCount, useSuperOffer);
    float total = calculateTotal(cart, cartCount, useSuperOffer);

    // Final summary
    printf("\n✅ Payment method selected: %s\n", paymentOption);
    printf("\n📋 Final review of your Cart :\n");
    displayCart(cart, cartCount);
    if (useSuperOffer)
        printf("🌟 You qualified for 20%% OFF on your full cart!\n");
    else
        printf("🎁 Per-item discounts applied where eligible (10%% off on 10+ units)\n");
    printf("💸 Total Discount Appleid  : $%.2f\n", discount);
    printf("💰 Total Amount to Pay     : $%.2f\n", total);

    // Confirm payment
    printf("\n🔐 Processing Your payment...\n");
    printf("✅ Payment of $%.2f confirmed via %s!\n", total, paymentOption);
    //printf("✅ $%.2f paid successfully via %s\n", total, paymentOption);
    printf("🎉 You saved $%.2f in discounts today!\n", discount);
    printf("🙏 Thank you for shopping with Super Shop!\n");

    return 0;
}
