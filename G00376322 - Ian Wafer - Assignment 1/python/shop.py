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
    print(f'\nPRODUCT NAME: {p.name} \nPRODUCT PRICE: {p.price}')

def print_customer(c, s): # load in stock list s for price?
    for item in c.shopping_list:
        print(f'{c.name} wants {item.quantity} of the product {item.product.name}')


        cost = item.quantity * s.stock.ProductStock.product.name.price
        print(f'The cost to {c.name} will be €{cost}\n')

    print(f'\nCustomer name is {c.name} and they have {c.budget} for their budget')
        
def print_shop(s):
    print(f'\nShop has {s.cash} in cash')
    for item in s.stock:
        print_product(item.product)
        print(f'The Shop has {item.quantity} of the above\n')

def display_menu():
    print("MENU")
    print("====")
    print("1- Choose pre loaded baskets")
    print("2- Live mode")
    print("3- Exit")

def main():
    while True:
        display_menu()
        choice = input("Choice: ")
        if (choice == "1"):
            s = create_and_stock_shop()
            print_shop(s)

            c = read_customer("../customer.csv")
            print_customer(c, s)
            print(s.stock)

            print(c.shopping_list)

        elif (choice == "2"):
            item = input("What would you like to buy?")
            quantity = input("And how many?")
            live_shopping_basket[item] = quantity

if __name__ == "__main__":
    main()