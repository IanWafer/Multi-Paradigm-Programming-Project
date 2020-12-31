#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Create inital structs to hold information on products, orders and shop stock levels
struct Product {
	char* name;
	double price;
};

struct ProductStock {
	struct Product product;
	int quantity;
};

struct CustQuant {
	struct Product product;
	int quantity;
};

struct Shop {
	double cash;
	struct ProductStock stock[20];
	int index;
};

// Declared to use in structs below to avoid implicit declaration as an integer type file
void display_menu(struct Shop *shop);  
void display_custmenu(struct Shop *shop);

struct Customer {
	char* name;
	double budget;
	struct CustQuant shoppingBasket[20];
	int index;
	double totalCost;

};

struct Customer custOrder(struct Shop *shop, char *file_path)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

	// Read csv file. If it fails to load exit program
	fp = fopen(file_path, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

	read = getline(&line, &len, fp); // Function to read lines of csv file
	char *c_name = strtok(line, ","); // Customer name between start and delimiter (,) using strtok function
	char *c_bud = strtok(NULL, ","); // Customer budget between previous delimiter and next delimiter (,) using strtok function
	char *custName = malloc(sizeof(char) * 50); // Assign memory space for customer name to max 50 characters
	double custBudget = atof(c_bud); // Convert budget to float from string using atof function
	strcpy(custName, c_name); // Convert price to float from string using atof function
	struct  Customer customer = {custName, custBudget}; // Enter customer details into customer struct
	printf("Customer name is %s and they have €%.2f for their budget\n\n", customer.name, customer.budget);
	while ((read = getline(&line,  &len, fp)) != -1) {
		char *c_prod = strtok(line, ","); // Shopping list item name between start and delimiter (,) using strtok function
		char *c_quant = strtok(NULL, ","); // Shopping list quantity between previous delimiter and next delimiter (,) using strtok function
		int quantity = atoi(c_quant); // Convert quantity to integer from string using atoi function
		char *name = malloc(sizeof(char)* 50); // Assign memory space for shopping list item to max 50 characters
		strcpy(name, c_prod); // Copy string customer item c to name using strcpy function
		struct Product product = {name}; // Assign name variable to Product struct. Price currently unknown
		struct CustQuant basket = {product, quantity}; // Assign product and quantity variables to CustQuant struct called basket
		customer.shoppingBasket[customer.index++] = basket; // Copy to customers shopping basket and move on to next iterate of arrray
	}

	// for loop to iterate customer shopping list items through the shop stock items 
	for (int i = 0; i < customer.index; i++)  
	{
		// nested for loop for checking item pulled f rom customer shopping list against all items in the shop to find a match
		for (int j = 0; j < shop->index; j++)
		{
			// If names match on lists then take price value from shop list and add to customer products for  prices calcs
			if  (strcmp(customer.shoppingBasket[i].product.name, shop->stock[j].product.name)== 0){ 
				customer.shoppingBasket[i].product.price = shop->stock[j].product.price;

				// Check customers order  hasn't gone over what shop has available. If it has inform the customer and re display the selection menu
				if (customer.shoppingBasket[i].quantity > shop->stock[j].quantity){ 
					printf("We do not have enough stock of %s, please re-select products to continue with your purchase.\n\n", customer.shoppingBasket[i].product.name);
					display_custmenu(&(*shop));
				} 
			}
		}
		
		// Print off what customer wants and how much it will cost
		printf("%s wants %i of the product %s\n", customer.name, customer.shoppingBasket[i].quantity, customer.shoppingBasket[i].product.name);
		double cost = customer.shoppingBasket[i].product.price * customer.shoppingBasket[i].quantity;

		//Adjust total cost of new order for each item added. Display the cost of the individual item in a summary fashion
		customer.totalCost += cost;
		printf("The cost to %s will be €%.2f\n\n", customer.name, cost);	 
		}

		// Check customer has enough in their budget to afford the purchase
		if (customer.budget < customer.totalCost){
			printf("The total price of the order for %s is €%.2f. %s has insufficient funds to complete the transaction.\n\n", customer.name, customer.totalCost, customer.name);
			return customer;
		}

		// Adjust shop quantities for items purchased
		for (int i = 0; i < customer.index; i++){
				shop->stock[i].quantity -= customer.shoppingBasket[i].quantity;
		}

		// Add customer purchase price to shop cash and reduce customers budget
		shop->cash +=  customer.totalCost;
		customer.budget -= customer.totalCost;

		printf("The total price for the order for %s will be €%.2f. Transaction complete. %s now has €%.2f remaining in their budget. Shop cash is now €%.2f\n", customer.name, customer.totalCost, customer.name, customer.budget, shop->cash);
	return customer;
}

void printProduct(struct Product prod)
{
	// Display product name and price from Product struct
	printf("PRODUCT NAME: %s \nPRODUCT PRICE: €%.2f\n", prod.name, prod.price);
	printf("---------------------\n");

}

struct Shop createAndStockShop()
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("../stock.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

	read = getline(&line, &len, fp);
	float cash = atof(line);
	
	struct Shop shop = {cash}; // Store cashh value from csv file into Shopo struct

    while ((read = getline(&line, &len, fp)) != -1) {
		char *nam = strtok(line, ","); // Product name between start and delimiter (,) using strtok function
		char *pri = strtok(NULL, ","); // Product price between previous delimiter and next delimiter (,) using strtok function
		char *qua = strtok(NULL, ","); // Product quantity between previous delimiter and next elimiter (,) using strtok function
		int quantity = atoi(qua); // Convert quantity to integer from string using atoi function
		double price = atof(pri); // Convert price to float from string using atof function
		char *name = malloc(sizeof(char) * 50);// Assign memory slot of  50 characters to name
		strcpy(name, nam); // Copy string n to name using strcpy function
		struct Product product = {name, price}; // Assign name and price to Product struct variables 
		struct ProductStock stockItem = {product, quantity}; // Assign the product created in the line above and the quantity to ProductStock struct
		shop.stock[shop.index++] = stockItem; // Add each item to the stock array with the position incrementing for each additional item added
    }
	return shop;
}

void printShop(struct Shop *shop)
{
	// Print shop cash and stock levels by iterating through the stock list
	printf("\nShop has €%.2f in cash\n\n", shop->cash);
	for (int i = 0; i < shop->index; i++)
	{
		printProduct(shop->stock[i].product);
		printf("The shop has %d of the above\n\n", shop->stock[i].quantity);
	}
}

void liveMode(struct Shop *shop)
{
	char *custName;
	double custBudget;
	char additional_items[] = "Y"; // Create starting condition to open while loop
	char *prod;
	int quantity;

	// Customer to enter details. Details to be stored under customer struct
	printf("What is your name? ");
	fflush(stdin); // Clear output buffer
	scanf("\n%[^\n]%*c", &custName);
	
	printf("And what is your budget today %s: €", &custName);
	scanf("%lf", &custBudget);

	struct Customer customer = {custName, custBudget};

	printf("That's great! The available products are listed below with quantities and prices noted.");
	printShop(&(*shop));

	// System to loop  through adding additional items to the order unless customer types N to indicate they have  no more items to add
	while (strcmp(additional_items, "N") != 0)
	{
		printf("What would you like to purchase? Please note product description must match exactly: ");
		fflush(stdin); // Clear output buffer
		scanf("\n%[^\n]%*c", &prod); // \n%[^\n]%*c used to have spaces in input

		printf("And how many would you like? ");
		fflush(stdin); // Clear output buffer
		scanf("%i", &quantity);

		//char *name = malloc(sizeof(char)* 50);
		//strcpy(name, nam);
		
		struct Product product = {prod};
		struct CustQuant basket = {product, quantity};
		customer.shoppingBasket[customer.index++] = basket;
		
		printf("Would you like to order additional items? Y/N\n");
		fflush(stdin); // Clear output buffer
		scanf("\n%[^\n]%*c", additional_items);
	}	

	// for loop to iterate customer shopping list items through the shop stock items 
	for (int i = 0; i < customer.index; i++)  
	{
		// nested for loop for checking item pulled f rom customer shopping list against all items in the shop to find a match
		for (int j = 0; j < shop->index; j++)
		{
			// If names match on lists then take price value from shop list and add to customer products for  prices calcs
			if  (strcmp(customer.shoppingBasket[i].product.name, shop->stock[j].product.name)== 0){ 
				customer.shoppingBasket[i].product.price = shop->stock[j].product.price;

				// Check customers order  hasn't gone over what shop has available. If it has inform the customer and re display the selection menu
				if (customer.shoppingBasket[i].quantity > shop->stock[j].quantity){ 
					printf("We do not have enough stock of %s, please re-select products to continue with your purchase.\n\n", customer.shoppingBasket[i].product.name);
					display_custmenu(&(*shop));
				} 
			}
		}
		// Print off what customer wants and how much it will cost
		printf("%s wants %i of the product %s\n", customer.name, customer.shoppingBasket[i].quantity, customer.shoppingBasket[i].product.name);
		double cost = customer.shoppingBasket[i].product.price * customer.shoppingBasket[i].quantity;
		
		//Adjust total cost of new order for each item added. Display the cost of the individual item in a summary fashion
		customer.totalCost += cost;
		printf("The cost to %s will be €%.2f\n\n", customer.name, cost);

		// Adjust shop quantities for items purchased
		shop->stock[i].quantity -= customer.shoppingBasket[i].quantity; 
		}

		// Check customer has enough in their budget to afford the purchase
		if (customer.budget < customer.totalCost){
			printf("The total price of the order for %s is €%.2f. %s has insufficient funds to complete the transaction.\n\n", &customer.name, customer.totalCost, &customer.name);
			display_custmenu(&(*shop));
	}

		// Add customer purchase price to shop cash and reduce customers budget
		shop->cash +=  customer.totalCost;
		customer.budget -= customer.totalCost;
		printf("The total price for the order for %s will be €%.2f. Transaction complete. %s now has €%.2f remaining in their budget. Shop cash is now €%.2f\n", &customer.name, customer.totalCost, &customer.name, customer.budget, shop->cash);
}

// Sub menu for displaying customer pre loaded baskets
void display_custmenu(struct Shop *shop)
{
	int choice2;
	char * file_path;

	while(1)
	{
		puts("1- Standard");
		puts("2- Not enough in budget");
		puts("3- Quantities selected too great");
		puts("4- Back");
		puts("5- Exit");
		printf("Choice: ");
		fflush(stdin);
		scanf("%i", &choice2);

		switch(choice2){
			case 1:			 
				file_path = "../Standard.csv";
				custOrder(&(*shop), file_path);
				break;
			case 2:
				file_path = "../Budget.csv";
				custOrder(&(*shop), file_path);
				break;
			case 3:
				file_path = "../Quantity.csv";
				custOrder(&(*shop), file_path);
				break;
			case 4:
				display_menu(&(*shop));
				break;
			case 5:
				exit(1);
				break;
		}
	}
}

// Main menu for customer actions
void display_menu(struct Shop *shop)
{
	int choice;

	while(1)
	{
		puts("\nMENU");
		puts("====");
		puts("1- Choose pre loaded baskets");
		puts("2- Live mode");
		puts("3- Check shop cash");
		puts("4- Check shop cash & stock");
		puts("5- Exit");
		printf("Choice: ");
		fflush(stdin);
		scanf("%i", &choice);

		switch(choice){
			case 1: 
				puts("\nCustomer test csv files available-");
				display_custmenu(&(*shop));
				break;
			case 2:
				liveMode(&(*shop));
				break;
			case 3:
				printf("The shop has €%.2f\n", shop->cash);
				break;
			case 4:
				printShop(&(*shop));
				break;
			case 5:
				exit(1);
			default:
				puts("This is not a valid selection. Please re-select\n");
				
		}
	} 
}
	
int main(void)
{
	struct Shop shop = createAndStockShop();
	printShop(&shop);
	display_menu(&shop);

    return 0;
}