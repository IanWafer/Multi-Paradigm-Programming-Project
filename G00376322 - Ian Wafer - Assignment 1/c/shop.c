#include <stdio.h>
#include <string.h>
#include <stdlib.h>



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

void display_menu(struct Shop s);  // Declared to use in structs below to avoid implicit declaration as a integer type file

struct Customer {
	char* name;
	double budget;
	struct CustQuant shoppingBasket[20];
	int index;
	double totalCost;

};

struct Customer custOrder(struct Shop s, char *csv)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;


	fp = fopen(csv, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

	read = getline(&line, &len, fp);
	char *a = strtok(line, ","); // Customer name between start and delimiter (,) using strtok function
	char *b = strtok(NULL, ","); // Customer budget between previous delimiter and next delimiter (,) using strtok function
	char *custName = malloc(sizeof(char) * 50); // Assign memory space for customer name to max 50 characters
	double custBudget = atof(b); // Convert budget to float from string using atof function
	strcpy(custName, a); // Convert price to float from string using atof function
	struct  Customer customer = {custName, custBudget};
	printf("Customer name is %s and they have €%.2f for their budget\n\n", customer.name, customer.budget);
	while ((read = getline(&line,  &len, fp)) != -1) {
		char *c = strtok(line, ","); // Shopping list item name between start and delimiter (,) using strtok function
		char *d = strtok(NULL, ","); // Shopping list quantity between previous delimiter and next delimiter (,) using strtok function
		int quantity = atoi(d); // Convert quantity to integer from string using atoi function
		char *name = malloc(sizeof(char)* 50); // Assign memory space for shopping list item to max 50 characters
		strcpy(name, c); // Copy string customer item c to name using strcpy function
		struct Product product = {name}; // Assign name variable to Product struct. Price currently unknown
		struct CustQuant basket = {product, quantity};
		customer.shoppingBasket[customer.index++] = basket;
	}
		for (int i = 0; i < customer.index; i++)  // for loop to iterate customer shopping list items through the shop stock items 
		{
			// If names match on lists then take price value from shop list and add to customer products for  prices calcs
			if  (s.stock[i].product.name = customer.shoppingBasket[i].product.name){ 
				customer.shoppingBasket[i].product.price = s.stock[i].product.price; 
			}
			// Check shop stock quantity for amount required by customer
			if (customer.shoppingBasket[i].quantity > s.stock[i].quantity){ 
				printf("We do not have enough stock of %s, please re-select products to continue with your purchase.\n", customer.shoppingBasket[i].product.name);
				display_menu(s);
			} 
			
			// Print off what customer wants and how much it will cost
			printf("%s wants %i of the product %s\n", customer.name, customer.shoppingBasket[i].quantity, customer.shoppingBasket[i].product.name);
			double cost = customer.shoppingBasket[i].product.price * customer.shoppingBasket[i].quantity;
			customer.totalCost += cost;
			printf("The cost to %s will be €%.2f\n\n", customer.name, cost);

			// Adjust shop quantities for items purchased
			s.stock[i].quantity -= customer.shoppingBasket[i].quantity; 

			}
			if (customer.budget < customer.totalCost){
				printf("The total price of the order for %s is €%.2f. %s has insufficient fund to complete the transaction.\n", customer.name, customer.totalCost, customer.name);
				display_menu(s);
		}

		s.cash +=  customer.totalCost;
		customer.budget -= customer.totalCost;

		printf("The total price for the order for %s will be €%.2f. Transaction complete. %s now has €%.2f remaining in their budget. Shop cash is now €%.2f\n", customer.name, customer.totalCost, customer.name, customer.budget, s.cash);
	return customer;
}

void printProduct(struct Product p)
{
	printf("PRODUCT NAME: %s \nPRODUCT PRICE: €%.2f\n", p.name, p.price);
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
	
	struct Shop shop = {cash};

    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        // printf("%s IS A LINE", line);
		char *n = strtok(line, ","); // Product name between start and delimiter (,) using strtok function
		char *p = strtok(NULL, ","); // Product price between previous delimiter and next delimiter (,) using strtok function
		char *q = strtok(NULL, ","); // Product quantity between previous delimiter and next elimiter (,) using strtok function
		int quantity = atoi(q); // Convert quantity to integer from string using atoi function
		double price = atof(p); // Convert price to float from string using atof function
		char *name = malloc(sizeof(char) * 50);// Assign memory slot of  50 characters to name
		strcpy(name, n); // Copy string n to name using strcpy function
		struct Product product = { name, price }; // Assign name and price to Product struct variables 
		struct ProductStock stockItem = { product, quantity }; // Assign the product created in the line above and the quantity to ProductStock struct
		shop.stock[shop.index++] = stockItem; // Add each item to the stock array with the position incrementing for each additional item added
		// printf("NAME OF PRODUCT %s PRICE %.2f QUANTITY %d\n", name, price, quantity);
    }
	
	return shop;
}

void printShop(struct Shop s)
{
	printf("\nShop has €%.2f in cash\n\n", s.cash);
	for (int i = 0; i < s.index; i++)
	{
		printProduct(s.stock[i].product);
		printf("The shop has %d of the above\n\n", s.stock[i].quantity);
	}
}


void liveMode(struct Shop s)
{
	char *custName;
	double custBudget;
	char additional_items[] = "Y";
	char *d;
	int quantity;

	printf("What is your name?");
	fflush(stdin);
	scanf("\n%[^\n]%*c", &custName);
	
	printf("And what is your budget today %s :", &custName);
	scanf("%lf", &custBudget);

	struct Customer customer = {custName, custBudget};

	printf("That's great! The available products are listed below with quantities and prices noted.");
	printShop(s);

	while (strcmp(additional_items, "N") != 0)
	{
		printf("What would you like to purchase? Please note product description must match exactly: ");
		fflush(stdin);
		scanf("\n%[^\n]%*c", d);

		printf("%s And how many would you like?", &d);
		fflush(stdin);
		scanf("%i", &quantity);

		char *name = malloc(sizeof(char)* 50);
		strcpy(name, d);// This is over writing the shop  list or some reason. To be fixed!
		struct Product product = {name};
		struct CustQuant basket = {product, quantity};
		customer.shoppingBasket[customer.index++] = basket;

		printf("Would you like to order additional items? Y/N\n");
		fflush(stdin);
		scanf("%s", &additional_items);
	}
	//for (int i = 0; i < customer.index; i++){
	//	printf("%s", customer.shoppingBasket[i]);
	//}
	
		for (int i = 0; i < customer.index; i++)  // for loop to iterate customer shopping list items through the shop stock items 
		{
			// If names match on lists then take price value from shop list and add to customer products for  prices calcs
			if  (s.stock[i].product.name = customer.shoppingBasket[i].product.name){ 
				customer.shoppingBasket[i].product.price = s.stock[i].product.price;
				//printf("Shop %s Customer %s", s.stock[i].product.name, customer.shoppingBasket[i].product.name) 
			}
			// Check shop stock quantity for amount required by customer
			if (customer.shoppingBasket[i].quantity > s.stock[i].quantity){ 
				printf("We do not have enough stock of %s, please re-select products to continue with your purchase.\n", customer.shoppingBasket[i].product.name);
				display_menu(s);
			}
			
			// Print off what customer wants and how much it will cost
			printf("%s wants %i of the product %s\n", &customer.name, customer.shoppingBasket[i].quantity, customer.shoppingBasket[i].product.name);
			double cost = customer.shoppingBasket[i].product.price * customer.shoppingBasket[i].quantity;
			customer.totalCost += cost;
			printf("The cost to %s will be €%.2f\n\n", &customer.name, cost);
			//printf("%s", &customer.name); // For testing product  name problems
			// Adjust shop quantities for items purchased
			s.stock[i].quantity -= customer.shoppingBasket[i].quantity; 
			printf("%i",  s.stock[i].quantity);
			printShop(s);
			}
			

	//		if (customer.budget < customer.totalCost){
	//			printf("The total price of the order for %s is €%.2f. %s has insufficient fund to complete the transaction.\n", customer.name, customer.totalCost, customer.name);
	//			display_menu(s);
	//	}
	//		
	//	s.cash +=  customer.totalCost;
	//	customer.budget -= customer.totalCost;
//
	//	printf("The total price for the order for %s will be €%.2f. Transaction complete. %s now has €%.2f remaining in their budget. Shop cash is now €%.2f\n", customer.name, customer.totalCost, customer.name, customer.budget, s.cash);
	//printf("TEST2");	
}

void display_custmenu(struct Shop s)
{
	int choice2;
	char * csv;

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
				csv = "../Standard.csv";
				custOrder(s, csv);
				break;
			case 2:
				csv = "../Budget.csv";
				custOrder(s, csv);
				break;
			case 3:
				csv = "../Quantity.csv";
				custOrder(s, csv);
				break;
			case 4:
				display_menu(s);
				break;
			case 5:
				exit(1);
				break;
		}
	}
}

void display_menu(struct Shop s)
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
				display_custmenu(s);
				break;
			case 2:
				liveMode(s);
				break;
			case 3:
				printf("The shop has €%.2f\n", s.cash);
				break;
			case 4:
				printShop(s);
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
	printShop(shop);
	display_menu(shop);

    return 0;
}