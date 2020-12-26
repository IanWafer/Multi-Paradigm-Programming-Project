#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//int check_equal

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

struct Customer {
	char* name;
	double budget;
	struct CustQuant shoppingBasket[20];
	int index;
	double totalCost;

};

struct Customer custOrder(struct Shop s)// <----- shop in brackets 
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("../Standard.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

	read = getline(&line, &len, fp);
	char *a = strtok(line, ","); // Customer name between start and delimiter (,) using strtok function
	char *b = strtok(NULL, ","); // Customer budget between previous delimiter and next delimiter (,) using strtok function
	char *custName = malloc(sizeof(char) * 50); // Assign memory space for customer name to max 50 characters
	double custBudget = atof(b); // Convert budget to float from string using atof function
	strcpy(custName, a); // Convert price to float from string using atof function
	struct  Customer customer = { custName, custBudget};
	while ((read = getline(&line,  &len, fp)) != -1) {
		char *c = strtok(line, ","); // Shopping list item name between start and delimiter (,) using strtok function
		char *d = strtok(NULL, ","); // Shopping list quantity between previous delimiter and next delimiter (,) using strtok function
		int quantity = atoi(d); // Convert quantity to integer from string using atoi function
		char *name = malloc(sizeof(char)* 50); // Assign memory space for shopping list item to max 50 characters
		strcpy(name, c); // Copy string customer item c to name using strcpy function
		struct Product product = { name }; // Assign name variable to Product struct. Price currently unknown
		struct CustQuant basket = { product, quantity };
		customer.shoppingBasket[customer.index++] = basket; // [0]=coke can, 0, 10.  [1] bread, 0, 3. [2] spag, 0, 5

		//struct Shop newshop = createAndStockShop();
	}
		/////////////////////////////////////////////////////////////
		for (int i = 0; i < customer.index; i++)
		{
			char* x;
			char* z;
			
			//why does s.stock list 6 of each item in position 0, 1 and 2.
			//printf("%s", s.stock[i].product.name);
			//printf("%f \n", s.stock[i].product.price);
			//printf("%s", s.stock[0].product.price);
			printf("\nPosition %i \n", i);
			//printf("%s \n", customer.shoppingBasket[i].product.price);
			//printf("%f \n",	 s.stock[i].product.price);
			x = customer.shoppingBasket[i].product.name; // this to be customer list
			z = s.stock[i].product.name; // this is shop list. 
			printf("%s \n", x);
			printf("%s \n", z);
			if  (z = x)
				customer.shoppingBasket[i].product.price = s.stock[i].product.price;
			printf("Customer wants %i \n", customer.shoppingBasket[i].quantity);
			printf("Shop has %i \n", s.stock[i].quantity);

			if (customer.shoppingBasket[i].quantity < s.stock[i].quantity){
				printf("OK\n");
			}

			if (customer.shoppingBasket[i].quantity >= s.stock[i].quantity){
				printf("Not enough stock\n");
			}
	
			double cost = customer.shoppingBasket[i].product.price * customer.shoppingBasket[i].quantity;
			customer.totalCost += cost ;
			printf("Total cost is %f\n", customer.totalCost);
			//printf("%f  \n", customer.shoppingBasket[i].product.price);

		}


		//printf("%f", customer.shoppingBasket[1].product.price);
		//double cost = customer.shoppingBasket[i].product.price * quantity;
		//double cost = quantity * customer.shoppingBasket[i]product.price;
		//printf("\n%s wants %d of the product %s\n", customer.name, quantity, name);
		//printf("The cost to %s will be %d\n", customer.name, cost);
	return customer;
}

//int check_equal(struct node *customer, struct node *Shop) {
//    
  //  if (customer == NULL && Shop == NULL) return 1;
    //
    //if(customer != NULL && Shop != NULL) {
	  //  if(customer->val != Shop->val) return 0;
	    
	   // return check_equal(Customer->next, Shop->next);
	//}
    //
    //return 0;
//}

//struct Product product = { name, price };

//struct ProductStock shoppingList = { product, quantity };
//customer.shoppingList[customer.index++] = shoppingList;
//printf("NAME OF PRODUCT  %s PRICE %.2f QUANTITY %d\n", name, price, quantity)

//void
//    for (item=0 ; item < length; item++):
//        for prod in s.stock:
//                if item.product.name == prod.product.name and item.quantity <= prod.quantity:
//                    print(item, item.quantity, prod.quantity)
//                    print("OK")
//                
//                elif item.product.name == prod.product.name and item.quantity > prod.quantity:
//                    printf("We do not have enough stock of %s, please re-select products to continue with your purchase.", item.product.name)
                    

void printProduct(struct Product p)
{
	printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", p.name, p.price);
	printf("-------------\n");

}

// void willsIdea(struct Product p)
// {
// 	// printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", p.name, p.price);
// 	// printf("-------------\n");


// 	// struct ProductStock stockItem = { product, quantity };
// 	// double will_var = atof(will_var);
// 	// double will_var = p.price
// 	//guyorder = p.price * quantity

// 	return p.price

// }

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
	// printf("cash in shop is %.2f\n", cash);
	
	struct Shop shop = { cash };

    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        // printf("%s IS A LINE", line);
		char *n = strtok(line, ","); // Product name between start and delimiter (,) using strtok function
		char *p = strtok(NULL, ","); // Product price between previous delimiter and next delimiter (,) using strtok function
		char *q = strtok(NULL, ","); // Product quantity between previous delimiter and next elimiter (,) using strtok function
		int quantity = atoi(q); // Convert quantity to integer from string using atoi function
		double price = atof(p); // Convert price to float from string using atof function
		char *name = malloc(sizeof(char) * 50);
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
	printf("Shop has %.2f in cash\n", s.cash);
	for (int i = 0; i < s.index; i++)
	{
		printProduct(s.stock[i].product);
		printf("The shop has %d of the above\n\n", s.stock[i].quantity);
	}
}

double find(struct Shop s, char* name)
{
	for  (int i = 0; i < s.index; i++)
	{
		if (strcmp(name, s.stock[i].product.name) == 0){
			return s.stock[i].product.price;
		}
	}
	return -1;
}

int main(void)

{
	struct Shop shop = createAndStockShop();
	printShop(shop);
	

	struct  Customer customer = custOrder(shop);// <----- shop in brackets 
	printf("Customer name is %s and they have %.2f for their budget\n", customer.name, customer.budget);
    return 0;
}