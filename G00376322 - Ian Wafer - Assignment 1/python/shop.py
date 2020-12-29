from dataclasses import dataclass, field
from typing import List
import csv

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

def create_and_stock_shop():
    s = Shop()
    with open('../stock.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        first_row = next(csv_reader)
        s.cash = float(first_row[0])
        for row in csv_reader:
            p = Product(row[0], float(row[1]))
            ps = ProductStock(p, float(row[2]))
            s.stock.append(ps)
            #print(ps)
    return s
    
def read_customer(file_path):
    with open(file_path) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        first_row = next(csv_reader)
        c = Customer(first_row[0], float(first_row[1]))
        for row in csv_reader:
            name = row[0]
            quantity = float(row[1])
            p = Product(name)
            ps = ProductStock(p, quantity)
            c.shopping_list.append(ps)
        return c 

def print_product(p):
    print(f'\nPRODUCT NAME: {p.name} \nPRODUCT PRICE: €{p.price:.2f} \n------------------------')

def print_customer(c, s):
    check_stock(c, s)
    calculate_costs(c, s)
    total_order = 0
    print(f'Customer name is {c.name} and they have €{c.budget:.2f} for their budget.\n')
    for item in c.shopping_list:
        print(f'{c.name} wants {item.quantity:.0f} of the product {item.product.name}.')
        cost = item.quantity * item.product.price
        total_order += cost
        print(f'The cost to {c.name} will be €{cost:.2f}.\n')

    if total_order <= c.budget:
        s.cash += total_order
        print(f'The total price of the order for {c.name} is €{total_order:.2f}. Transaction complete.  {c.name} now  has €{c.budget-total_order:.2f} remaining in their budget. Shop cash is now €{s.cash}.\n')
        for item in c.shopping_list:    # Iterate through individual items in shopping list
            for prod in s.stock:        # Iterate the item pulled from shopping list through the shop stock 
                if item.product.name == prod.product.name:          # If names are equal then adjust quantities outlined below
                    prod.quantity = prod.quantity - item.quantity   # Update shop quantities to reflect purchased goods taken from shop stock
    else:
        print(f'The total price of the order for {c.name} is €{total_order:.2f}. {c.name} has insufficient fund to complete the transaction.\n')
        
def print_shop(s):
    print(f'\nShop has €{s.cash} in cash.')
    for item in s.stock:
        print_product(item.product)
        print(f'The Shop has {item.quantity:.0f} of the above.\n')

def check_stock(c, s):
    for item in c.shopping_list:
        for prod in s.stock:
                if item.product.name == prod.product.name and item.quantity > prod.quantity:
                    print(f"We do not have enough stock of {item.product.name}, please re-select products to continue with your purchase.")
                    main()

def calculate_costs(c, s):
    for shop_item in s.stock:
        for list_item in c.shopping_list:
            if (list_item.product.name == shop_item.product.name):
                list_item.product.price = shop_item.product.price

def display_menu():
    print("MENU")
    print("====")
    print("1- Choose pre loaded baskets")
    print("2- Live mode")
    print("3- Check shop cash")
    print("4- Check shop cash & stock")
    print("5- Exit")

def display_custmenu():
    print("1- Standard")
    print("2- Not enough in budget")
    print("3- Quantities selected too great")
    print("4- Back")
    print("5- Exit")

def live_mode():
    cust_name = input("What is your name? ")
    budget= float(input(f"And what is your budget today {cust_name}: "))
    c = Customer(cust_name, budget)
    print("That's great! The available products are listed below with quantities and prices noted.")
    print_shop(s)
    shopping_list=[]
    additional_items = "Y"
    while (additional_items == "Y"):
        name = input("What would you like to purchase? Please note product description must match exactly: ")
        quantity = int(input("And how many would you like? "))
        p = Product(name)
        ps = ProductStock(p, quantity)
        c.shopping_list.append(ps)
        additional_items = input("Would you like to order additional items? Y/N \n")

    return c

def main():
    while True:
        display_menu()
        choice = input("Choice: ")

        if (choice == "1"):
            while True:
                print("\nCustomer test csv files available-")
                display_custmenu()
                customer_type = input("Choice: ")

                if (customer_type == "1"):
                    c = read_customer("../Standard.csv")
                    print_customer(c, s)

                elif (customer_type == "2"):
                    c = read_customer("../Budget.csv")
                    print_customer(c, s)

                elif (customer_type == "3"):
                    c = read_customer("../Quantity.csv")
                    print_customer(c, s)

                elif (customer_type ==  "4"):
                    main()

                elif (customer_type == "5"):
                    exit()

                else:
                    print("This is not a valid selection. Please re-select.\n")

        elif (choice == "2"):
            c = live_mode()
            print_customer(c, s)

        elif (choice == "3"):
            print(f'\nThe shop has €{s.cash:.2f}\n')
            
        elif (choice == "4"):
            print_shop(s)  

        elif (choice == "5"):
            exit()

        else:
            print("This is not a valid selection\n")

if __name__ == "__main__":
    s = create_and_stock_shop()
    print_shop(s)
    main()