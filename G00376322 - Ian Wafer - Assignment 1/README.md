# Multi Paradigm Programming Assignment 1

Lecturer: Dr. Dominic Carr
Due Date: 31/12/20

Student: Ian Wafer
Student ID: G00376322
Student Email: G00376322@gmit.ie
Alternative Email: ianwafer@gmail.com

### Introduction-
We have been tasked with building on the shop  program received from our lecturer to give it additional functionality. We have been specifically requested to include the below features-
- The shop CSV should hold the initial cash value for the shop.
- Read in customer orders from a CSV file.
    - That file should include all the products they wish to buy and in what quantity.
    - It should also include their name and their budget.
- The shop must be able to process the orders of the customer.
    - Update the cash in the shop based on money received.
        - It is important that the state of the shop be consistent.
        - You should create customer test files (CSVs) which cannot be completed by the shop e.g. customer wants 400
          loaves of bread but the shop only has 20, or the customer wants 2 cans of coke but can only afford 1.
        - If these files don’t exist marks penalties will be applied.
    - Know whether or not the shop can fill an order.
        - Thrown an appropriate error.
- Operate in a live mode, where the user can enter a product by name, specify a quantity, and pay for it. The user should
  be able to buy many products in this way.

### Shop
The shop simulation program was completed in the below functionalities-
1. Procedural C
2. Procedural Python
3. Object Oriented Programming Python

### How to download this repository
1. Go to Github profile located here- [link](https://github.com/IanWafer)
2. Click repository labeled IanWafer/Multi-Paradigm-Programming-Project.
3. Click the download button or clone the repository to your own Github account.

### How to run the python code.
1. Install a python code client (Anaconda recommended. See here for installer- [link](https://www.anaconda.com/distribution/)
2. Run a command line client (cmder recommended. See here for installer- [link](https://github.com/cmderdev/cmder/releases/download/v1.3.11/cmder.zip)
3. Ensure you are in the correct directory where each python script is located using the cd command to navigate.
4. Run the python script by typing "python shop.py" and "python shop_oop.py".

### How to run the C code.
1. Install a C code client (Cygwin recommended. See here for installer- [link]https://www.cygwin.com/)
2. Open the client and navigate to the C folder using the cd command. 
3. Compile the code with the command "gcc shop.c".
4. Run the output file created using the command "./a.exe".
