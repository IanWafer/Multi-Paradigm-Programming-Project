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

struct Shop {
	double cash;
	struct ProductStock stock[20];
	int index;
};

struct Customer {
	char* name;
	double budget;
};

struct Customer custOrder()
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("../customer.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

	read = getline(&line, &len, fp);
	char *a = strtok(line, ",");
	char *b = strtok(NULL, ",");
	char *custName = malloc(sizeof(char) * 50);
	double custBudget = atof(b);
	strcpy(custName, a);
	struct  Customer customer = { custName, custBudget};

	while ((read = getline(&line,  &len, fp)) != -1) {
		char *c = strtok(line, ",");
		char *d = strtok(NULL, ",");
		int quantity = atoi(d);
		char *name = malloc(sizeof(char)* 50);
		strcpy(name, c);
		struct Product product = { name };
		struct ProductStock stockItem = { product, quantity };
		printf("%s wants %d of the product %s\n", customer.name, quantity, name);
	}
	return customer;
}

void printProduct(struct Product p)
{
	printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", p.name, p.price);
	printf("-------------\n");
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
	// printf("cash in shop is %.2f\n", cash);
	
	struct Shop shop = { cash };

    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        // printf("%s IS A LINE", line);
		char *n = strtok(line, ",");
		char *p = strtok(NULL, ",");
		char *q = strtok(NULL, ",");
		int quantity = atoi(q);
		double price = atof(p);
		char *name = malloc(sizeof(char) * 50);
		strcpy(name, n);
		struct Product product = { name, price };
		struct ProductStock stockItem = { product, quantity };
		shop.stock[shop.index++] = stockItem;
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
//{
//
//	struct  Customer customer = custOrder();
//	printf("Customer name is %s and they have %.2f for their budget\n", customer.name, customer.budget);
//	
//	struct Product productA = { "Coke Can", 0.0 };
//	struct Product productB = { "Big Bags", 0.0 };
//	struct Product productC = { "Spaghetti", 0.0 };
//	struct ProductStock StockA = { productA, 12 };
//	struct ProductStock StockB = { productB, 5 };
//	struct ProductStock StockC = { productC, 2 };
//	
//	struct ProductStock array[] = { StockA, StockB, StockC }; 
//	
//	struct Shop shop = createAndStockShop();
//	
//	double totalCostForCustomer = 0;
//	for(int i=0; i < 3; i++){
//		struct Product p = array[i].product;
//		double price = find(shop, p.name);
//		printf("The price of %s in the shop is %.2f\n", p.name, price);
//		double totalCostOfItem = array[i].quantity * price;
//		printf("You want %d of %s, that will cost you %.2f\n", array[i].quantity, p.name, totalCostOfItem);
//		totalCostForCustomer += totalCostOfItem;
//	}
//	printf("The total cost for the customer will be %.2f\n", totalCostForCustomer);
//	
//    return 0;
//} 
{
	struct Shop shop = createAndStockShop();
	printShop(shop);

	struct  Customer customer = custOrder();
	printf("Customer name is %s and they have %.2f for their budget\n", customer.name, customer.budget);

	//struct ProductStock array[] = {shop.stock}; //Need to convert this to read CSV file somehow

	//double totalCostForCustomer =  0;
	//for(int i=1; i < 2; i++){

	//	double price = find(shop, p.name);
	//	printf("The price of %s in the shop is %.2f\n", p.name, price);
	//	double totalCostOfItem = array[i].quantity * price;
	//	printf("%s wants %d of %s, that will cost them %.2f\n", customer.name, array[i].quantity, p.name, totalCostOfItem);
	//	totalCostForCustomer += totalCostOfItem;
	//}
	//printf("The total cost for the customer will be %.2f\n", totalCostForCustomer);

    return 0;
}