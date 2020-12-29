import csv

class Product:

    def __init__(self, name, price=0):
        self.name = name
        self.price = price
    
    def __repr__(self): # The __repr__  function is used to return a printable representation of the object
        return f'\nPRODUCT NAME: {self.name} \nPRODUCT PRICE: €{self.price:.2f}  \n------------------------'

class ProductStock:
    
    def __init__(self, product, quantity):
        self.product = product
        self.quantity = quantity
    
    def name(self):
        return self.product.name;
    
    def unit_price(self):
        return self.product.price;
        
    def cost(self):
        return self.unit_price() * self.quantity
        
    def __repr__(self): # The __repr__  function is used to return a printable representation of the object
        return f"{self.product} \nThe shop  has {self.quantity:.0f} of the above"

class Customer:

    def __init__(self, path):
        self.shopping_list = []
        with open(path) as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=',')
            first_row = next(csv_reader)
            self.name = first_row[0]
            self.budget = float(first_row[1])
            for row in csv_reader:
                name = row[0]
                quantity = float(row[1])
                p = Product(name)
                ps = ProductStock(p, quantity)
                self.shopping_list.append(ps) 
    
    def __repr__(self): # The __repr__  function is used to return a printable representation of the object
        print("Test")
        str = f""
        Customer_order.calculate_costs(self, s.stock)
        Customer_order.check_stock(self)
        str += f"Customer name is {self.name} and they have €{self.budget:.2f} for their budget.\n"
        for item in self.shopping_list:
            cost = item.cost()
            #str += f"\n{item}"
            if (cost == 0):
                str += f"{self.name} doesn't know how much that costs :("
            else:
                str += f"\n{self.name} wants {item.quantity:.0f} of the product {item.product.name}.\n"
                str += f"The cost to {self.name} will be €{cost:.2f}\n"
                
        if Customer_order.order_cost(self) <=  self.budget:
            s.cash += Customer_order.order_cost(self)
            str += f"\nThe total price of the order for {self.name} is €{Customer_order.order_cost(self):.2f}. Transaction complete. {self.name} now has €{self.budget - Customer_order.order_cost(self):.2f} remaining in their budget. Shop cash is now €{s.cash:.2f}."
            for item in self.shopping_list: # Iterate through individual items in shopping list
                for prod in s.stock:        # Iterate the item pulled from shopping list through the shop stock 
                    if item.product.name == prod.product.name:          # If names are equal then adjust quantities outlined below
                        prod.quantity = prod.quantity - item.quantity   # Update shop quantities to reflect purchased goods taken from shop stock
        else:
            str += f"\nThe total price of the order for {self.name} is €{Customer_order.order_cost(self):.2f}. {self.name} has insufficient fund to complete the transaction.\n"

        return str

class Customer_order:

    def order_cost(self):
        total_order = 0
        
        for list_item in self.shopping_list:
            total_order += list_item.cost()
        
        return total_order

    def check_stock(self):
        str = f""
        for item in self.shopping_list:
            for prod in s.stock:
                    if item.product.name == prod.product.name and item.quantity > prod.quantity:
                        print(f"We do not have enough stock of {item.product.name}, please re-select products to continue with your purchase.\n")
                        Menu().main()

    def calculate_costs(self, price_list):
        for shop_item in price_list:
            for list_item in self.shopping_list:
                if (list_item.name() == shop_item.name()):
                    list_item.product.price = shop_item.unit_price()

class Live_mode:
    
    def __init__(self):
        self.name = input("What is your name? ")
        self.budget= float(input(f"And what is your budget today {self.name}: "))
        print("That's great! The available products are listed below with quantities and prices noted.")
        print(s)
        self.shopping_list=[]
        additional_items = "Y"
        while (additional_items == "Y"):
            name = input("What would you like to purchase? Please note product description must match exactly: ")
            quantity = int(input("And how many would you like? "))
            p = Product(name)
            ps = ProductStock(p, quantity)
            self.shopping_list.append(ps)
            additional_items = input("Would you like to order additional items? Y/N \n")
    
    def __repr__(self):    
        return Customer.__repr__(self)

class Shop:
    
    def __init__(self, path):
        self.stock = []
        with open(path) as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=',')
            first_row = next(csv_reader)
            self.cash = float(first_row[0])
            for row in csv_reader:
                p = Product(row[0], float(row[1]))
                ps = ProductStock(p, float(row[2]))
                self.stock.append(ps)
    
    def __repr__(self):
        str = ""
        str += f'\nShop has €{self.cash:.2f} in cash\n'
        for item in self.stock:
            str += f"{item}\n"
        return str

class Menu:
    def display_menu(self):
        print("MENU")
        print("====")
        print("1- Choose pre loaded baskets")
        print("2- Live mode")
        print("3- Check shop cash")
        print("4- Check shop cash & stock")
        print("5- Exit")

    def display_custmenu(self):
            print("1- Standard")
            print("2- Not enough in budget")
            print("3- Quantities selected too great")
            print("4- Back")
            print("5- Exit")

    def main(self):
        while True:
            self.display_menu()
            choice = input("Choice: ")

            if (choice == "1"):
                while True:
                    print("\nCustomer test csv files available-")
                    self.display_custmenu()
                    customer_type = input("Choice: ")

                    if (customer_type == "1"):
                        c = Customer("../Standard.csv")
                        print(c)

                    elif (customer_type == "2"):
                        c = Customer("../Budget.csv")
                        print(c)

                    elif (customer_type == "3"):
                        c = Customer("../Quantity.csv")
                        print(c)

                    elif (customer_type ==  "4"):
                        Menu().main()

                    elif (customer_type == "5"):
                        exit()

                    else:
                        print("This is not a valid selection. Please re-select.\n")

            elif (choice == "2"):
                c = Live_mode()
                print(c)

            elif (choice == "3"):
                print(f'\nThe shop has €{s.cash:.2f}\n')
                
            elif (choice == "4"):
                print(s)  

            elif (choice == "5"):
                exit()

            else:
                print("This is not a valid selection\n")

s = Shop("../stock.csv")
print(s)

Menu().main()