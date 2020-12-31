from dataclasses import dataclass, field
from typing import List
import csv

# Data containers for variable information
@dataclass 
class Product:
    name: str
    price: float = 0.0

@dataclass 
class ProductStock:
    product: Product
    quantity: int

@dataclass 
class Shop:
    cash: float = 0.0
    stock: List[ProductStock] = field(default_factory=list)

@dataclass
class Customer:
    name: str = ""
    budget: float = 0.0
    shopping_list: List[ProductStock] = field(default_factory=list)

# Stock shop from csv file received
def create_and_stock_shop():
    shop = Shop() 
    with open("../stock.csv") as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=",")
        first_row = next(csv_reader)
        shop.cash = float(first_row[0])
        for row in csv_reader:
            prod = Product(row[0], float(row[1]))
            prod_st = ProductStock(prod, float(row[2]))
            shop.stock.append(prod_st)
    return shop

# Extract data from csv file to create customer shopping list
def read_customer(file_path):
    with open(file_path) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=",")
        first_row = next(csv_reader)
        cust= Customer(first_row[0], float(first_row[1]))
        for row in csv_reader:
            name = row[0]
            quantity = float(row[1])
            prod = Product(name)
            prod_st = ProductStock(prod, quantity)
            cust.shopping_list.append(prod_st)
        return cust

# Print product name and price
def print_product(prod):
    print(f"\nPRODUCT NAME: {prod.name} \nPRODUCT PRICE: €{prod.price:.2f} \n------------------------")

def print_customer(cust, shop):
    check_stock(cust, shop)     # Check stock levels are adequate to cover customers order
    calculate_costs(cust, shop) # Determine the cost of the item from the matching name in the shop
    total_order = 0             # Create initial value of variable for total order amount
    print(f"Customer name is {cust.name} and they have €{cust.budget:.2f} for their budget.\n")

    # Iterate through items in shopping list to determine price of the total order
    for item in cust.shopping_list:    
        print(f"{cust.name} wants {item.quantity:.0f} of the product {item.product.name}.")
        cost = item.quantity * item.product.price

        # Check item exists in the store
        if  (cost == 0):
            print(f"The product {item.product.name} cannot be found. Please enter a name matching the shop stock shown above.")
            main()

        total_order += cost
        print(f"The cost to {cust.name} will be €{cost:.2f}.\n")

    # Check if customer has enough in budget to fulfill the order. Adjust shop cash and stock levels accordingly
    if total_order <= cust.budget:
        shop.cash += total_order
        print(f"The total price of the order for {cust.name} is €{total_order:.2f}. Transaction complete.  {cust.name} now  has €{cust.budget-total_order:.2f} remaining in their budget. Shop cash is now €{shop.cash}.\n")
        for item in cust.shopping_list:    # Iterate through individual items in shopping list
            for prod in shop.stock:        # Iterate the item pulled from shopping list through the shop stock 
                if item.product.name == prod.product.name:          # If names are equal then adjust quantities outlined below
                    prod.quantity = prod.quantity - item.quantity   # Update shop quantities to reflect purchased goods taken from shop stock
    else:
        print(f"The total price of the order for {cust.name} is €{total_order:.2f}. {cust.name} has insufficient funds to complete the transaction.\n")

def print_shop(shop):
    print(f"\nShop has €{shop.cash} in cash.")

    # Iterate through objects in store to print off
    for item in shop.stock:
        print_product(item.product)
        print(f"The Shop has {item.quantity:.0f} of the above.\n")

# Check shop has adequate stocks to fulfill order
def check_stock(cust, shop):
    for item in cust.shopping_list:
        for prod in shop.stock:
                if item.product.name == prod.product.name and item.quantity > prod.quantity:
                    print(f"We do not have enough stock of {item.product.name}, please re-select products to continue with your purchase.")
                    custmenu()
                       
    # Calculate each items price from the shop list
def calculate_costs(cust, shop):
    for shop_item in shop.stock:                # Iterate through individual items in shop stock 
        for list_item in cust.shopping_list:    # Iterate the item pulled from shop stock list through the customer shopping list 
            if (list_item.product.name == shop_item.product.name):   # If names are equal then adjust price in the shopping list outlined below
                list_item.product.price = shop_item.product.price    # Update shopping list price to match shop price

# Live mode for customer to enter their own orders
def live_mode():
    cust_name = input("What is your name? ")

    # Check for input error by user
    try:
        budget= float(input(f"And what is your budget today {cust_name}: €"))
    except ValueError:
        print("\nPlease enter a float value for the budget.\n")
        live_mode()

    cust= Customer(cust_name, budget)
    print("That's great! The available products are listed below with quantities and prices noted.")
    print_shop(shop)
    shopping_list=[]        # Create empty array for input
    additional_items = "Y"  # Create starting condition to open while loop
    while (additional_items == "Y"):
        name = input("What would you like to purchase? Please note product description must match exactly: ")
        
        # Check for input error by user
        try:
            quantity = int(input("And how many would you like? "))
        except ValueError:
            print("\nPlease enter an integer value for the quantity. Restarting order process...\n")
            live_mode()

        prod = Product(name)
        prod_st = ProductStock(prod, quantity)
        cust.shopping_list.append(prod_st)
        additional_items = input("Would you like to order additional items? Y/N \n")

    return cust

# Main menu displayed when shop is run
def display_menu():
    print("MENU")
    print("====")
    print("1- Choose pre loaded baskets")
    print("2- Live mode")
    print("3- Check shop cash")
    print("4- Check shop cash & stock")
    print("5- Exit")

# Main menu options
def main():
    while True:
        display_menu()
        choice = input("Choice: ")

        if (choice == "1"):
            custmenu()

        elif (choice == "2"):
            cust= live_mode()
            print_customer(cust, shop)

        elif (choice == "3"):
            print(f"\nThe shop has €{shop.cash:.2f}\n")
            
        elif (choice == "4"):
            print_shop(shop)  

        elif (choice == "5"):
            exit()

        else:
            print("This is not a valid selection\n")

# Sub menu for displaying customer pre loaded baskets 
def display_custmenu():
    print("1- Standard")
    print("2- Not enough in budget")
    print("3- Quantities selected too great")
    print("4- Back")
    print("5- Exit")

# Sub menu options
def custmenu():
    while True:
        print("\nCustomer test csv files available-")
        display_custmenu()
        customer_type = input("Choice: ")
        if (customer_type == "1"):
            cust= read_customer("../Standard.csv")
            print_customer(cust, shop)
        elif (customer_type == "2"):
            cust= read_customer("../Budget.csv")
            print_customer(cust, shop)
        elif (customer_type == "3"):
            cust= read_customer("../Quantity.csv")
            print_customer(cust, shop)
        elif (customer_type ==  "4"):
            main()
        elif (customer_type == "5"):
            exit()
        else:
            print("This is not a valid selection. Please re-select.\n")

if __name__ == "__main__":
    shop = create_and_stock_shop()
    print_shop(shop)
    main()