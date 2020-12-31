import csv

# Create class blueprints to be used for constructing objects
class Product:

    def __init__(self, name, price=0):
        self.name = name
        self.price = price
    
    def __repr__(self): # The __repr__  function is used to return a printable representation of the object
        return f"\nPRODUCT NAME: {self.name} \nPRODUCT PRICE: €{self.price:.2f}  \n------------------------"

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
        
    def __repr__(self): 
        return f"{self.product} \nThe shop  has {self.quantity:.0f} of the above"

class Customer:
    
    # Extract data from csv file and apply to classes above to create customer object
    def __init__(self, file_path):
        self.shopping_list = []
        with open(file_path) as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=",")
            first_row = next(csv_reader)
            self.name = first_row[0]
            self.budget = float(first_row[1])
            for row in csv_reader:
                name = row[0]
                quantity = float(row[1])
                prod = Product(name)
                prod_st = ProductStock(prod, quantity)
                self.shopping_list.append(prod_st) 
    
    def __repr__(self): 
        str = f""
        Customer.check_stock(self)                  # Check stock levels are adequate to cover customers order
        Customer.calculate_costs(self, shop.stock)  # Determine the cost of the item from the matching name in the shop
        str += f"Customer name is {self.name} and they have €{self.budget:.2f} for their budget.\n"

        # Iterate through items in shopping list to determine price
        for item in self.shopping_list: 
            cost = item.cost()
            #str += f"\n{item}"

            # Check item exists within shop
            if (cost == 0): 
                print(f"The product {item.product.name} cannot be found. Please enter a name matching the shop stock shown above.")
                Menu().main()
            else:
                str += f"\n{self.name} wants {item.quantity:.0f} of the product {item.product.name}.\n"
                str += f"The cost to {self.name} will be €{cost:.2f}\n"
        
        # Check if customer has enough in budget to fulfill the order. Adjust shop cash and stock levels accordingly
        if Customer.order_cost(self) <=  self.budget:
            shop.cash += Customer.order_cost(self)
            str += f"\nThe total price of the order for {self.name} is €{Customer.order_cost(self):.2f}. Transaction complete. {self.name} now has €{self.budget - Customer.order_cost(self):.2f} remaining in their budget. Shop cash is now €{shop.cash:.2f}."
            for item in self.shopping_list:    # Iterate through individual items in shopping list
                for prod in shop.stock:        # Iterate the item pulled from shopping list through the shop stock 
                    if item.product.name == prod.product.name:          # If names are equal then adjust quantities outlined below
                        prod.quantity = prod.quantity - item.quantity   # Update shop quantities to reflect purchased goods taken from shop stock
        else:
            str += f"\nThe total price of the order for {self.name} is €{Customer.order_cost(self):.2f}. {self.name} has insufficient funds to complete the transaction.\n"

        return str


    # Calculate total order cost
    def order_cost(self):
        total_order = 0
        
        for list_item in self.shopping_list:
            total_order += list_item.cost()
        
        return total_order

    # Calculate each items price from the shop list
    def calculate_costs(self, price_list):
        for shop_item in price_list:                # Iterate through individual items in shop stock 
            for list_item in self.shopping_list:    # Iterate the item pulled from shop stock list through the customer shopping list 
                if (list_item.name() == shop_item.name()):              # If names are equal then adjust price in the shopping list outlined below
                    list_item.product.price = shop_item.unit_price()    # Update shopping list price to match shop price

    # Check shop has adequate stocks to fulfill order
    def check_stock(self):
        for item in self.shopping_list:
            for prod in shop.stock:
                    if item.product.name == prod.product.name and item.quantity > prod.quantity:
                        print(f"\nWe do not have enough stock of {item.product.name}, please re-select products to continue with your purchase.\n")
                        Menu().custmenu()

class Live_mode:
    
    # Live mode for customer to enter their own orders
    def __init__(self):
        self.name = input("What is your name? ")

        # Check for input error by user
        try:
            self.budget= float(input(f"And what is your budget today {self.name}: €"))
        except ValueError:
            print("\nPlease enter a float value for the budget. Restarting order process...\n")
            Live_mode()

        print("That's great! The available products are listed below with quantities and prices noted.")
        print(shop)
        self.shopping_list=[]   # Create empty array for input
        additional_items = "Y"  # Create starting condition to open while loop
        while (additional_items == "Y"):
            name = input("What would you like to purchase? Please note product description must match exactly: ")
            
            # Check for input error by user
            try:
                quantity = int(input("And how many would you like? "))
            except ValueError:
                print("\nPlease enter an integer value for the quantity. Restarting order process...\n")
                Live_mode()

            prod = Product(name)
            prod_st = ProductStock(prod, quantity)
            self.shopping_list.append(prod_st)
            additional_items = input("Would you like to order additional items? Y/N \n")
    
    def __repr__(self):    
        return Customer.__repr__(self)

class Shop:
    
    def __init__(self, file_path):
        # Stock shop from csv file received
        self.stock = []
        with open(file_path) as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=",")
            first_row = next(csv_reader)
            self.cash = float(first_row[0])
            for row in csv_reader: 
                prod = Product(row[0], float(row[1])) 
                prod_st = ProductStock(prod, float(row[2]))
                self.stock.append(prod_st)
    
    # Display shop stock levels and cash
    def __repr__(self):
        str = ""
        str += f"\nShop has €{self.cash:.2f} in cash\n"
        for item in self.stock:
            str += f"{item}\n"
        return str

class Menu:

    # Main menu displayed when shop is run
    def display_menu(self):
        print("MENU")
        print("====")
        print("1- Choose pre loaded baskets")
        print("2- Live mode")
        print("3- Check shop cash")
        print("4- Check shop cash & stock")
        print("5- Exit")

    # Main menu options
    def main(self):
        while True:
            self.display_menu()
            choice = input("Choice: ")

            if (choice == "1"):
                self.custmenu()
            elif (choice == "2"):
                cust= Live_mode()
                print(cust)

            elif (choice == "3"):
                print(f"\nThe shop has €{shop.cash:.2f}\n")
                
            elif (choice == "4"):
                print(shop)  

            elif (choice == "5"):
                exit()

            else:
                print("This is not a valid selection\n")

    # Sub menu for displaying customer pre loaded baskets 
    def display_custmenu(self):
            print("1- Standard")
            print("2- Not enough in budget")
            print("3- Quantities selected too great")
            print("4- Back")
            print("5- Exit")

    # Sub menu options
    def custmenu(self):
        while True:
                    print("\nCustomer test csv files available-")
                    self.display_custmenu()
                    customer_type = input("Choice: ")

                    if (customer_type == "1"):
                        cust= Customer("../Standard.csv")
                        print(cust)

                    elif (customer_type == "2"):
                        cust= Customer("../Budget.csv")
                        print(cust)

                    elif (customer_type == "3"):
                        cust= Customer("../Quantity.csv")
                        print(cust)

                    elif (customer_type ==  "4"):
                        Menu().main()

                    elif (customer_type == "5"):
                        exit()

                    else:
                        print("This is not a valid selection. Please re-select.\n")

if __name__=="__main__":
    shop = Shop("../stock.csv")
    print(shop)

    Menu().main()