# E-commerce
Overview:
This program provides a User Management System, Product Management System ,and an integrated Recommendation Engine. The application uses Linked Lists for user and product management and a Binary Search Tree (BST) for browsing and purchase history tracking. It includes features for managing users, products, and browsing/purchase history, as well as recommending the most popular products.

Key Features
1. User Management
   - Add a new user.
   - Update existing user information.
   - Retrieve user details.
   
2. Product Management
   - Add a new product.
   - Update existing product details.
   - Retrieve product details.

3. Browsing & Purchase History
   - Log browsing and purchase events for products.
   - View browsing and purchase history for specific products.

4. Recommendation Engine
   - Recommend the most popular product based on combined browsing and purchase activity.

5. Memory Management
   - Automatically frees dynamically allocated memory on program exit.


Data Structures
Linked List: Used to manage users and products dynamically.
Binary Search Tree (BST): Used to store and retrieve product browsing/purchase history efficiently.


1. main.c
   - The primary implementation file containing all functions and logic.
   - Includes user interaction, input handling, and menu-based navigation.

2.Data Structures
   - User: Linked list node structure for user data.
   - Product: Linked list node structure for product data.
   - TreeNode: BST node structure for browsing and purchase history.

---

Functions

User Management
1. adduser(User **userList, int userId, char *userName, char *email)
   - Adds a new user to the linked list.
   
2. updateuser(User *userList, int userId, char *userName, char *email)
   - Updates an existing user's information.
   
3. getuser(User *userList, int userId)
   - Retrieves user details by ID.
   
4. freeuser(User *userList)
   - Frees memory allocated for the user linked list.

Product Management
1. adprod(Product **productList, int productId, char *productName, float price, TreeNode **historyRoot)
   - Adds a new product to the linked list and initializes its browsing history in the BST.

2. updateprod(Product *productList, int productId, char *productName, float price, TreeNode *historyRoot)
   - Updates product details and logs a browsing event.
   
3. getprod(Product *productList, int productId)
   - Retrieves product details by ID.
   
4. freeprod(Product *productList)
   - Frees memory allocated for the product linked list.

Browsing & Purchase History
1. insertevent(TreeNode *root, int productId, char *productName, char *eventType)
   - Inserts a browsing or purchase event into the BST.

2. updatehistory(TreeNode *root, int productId, char *eventType)
   - Updates browsing or purchase history for a specific product.
   
3. retrievehistory(TreeNode *root, int productId)
   - Retrieves browsing and purchase history for a product.

4. getprodhistorynode(TreeNode *root, int productId)
   - Finds the BST node for a product ID.

5. freetree(TreeNode *root)
   - Frees memory allocated for the BST.

Recommendation Engine
1. recommendprod(TreeNode *root)
   - Finds and recommends the most popular product.

2. recommendprodhelper(TreeNode *root, TreeNode **mostRecommended, int *highestScore)
   - Recursive helper function for `recommendprod`.

How to Use
1. Compile the Code
   - Use a C compiler (e.g., GCC):
     
     gcc main.c -o program
     

2. Run the Program
   - Execute the compiled program:
     
     ./program
     

3. Follow the On-Screen Menu
   - The program provides a menu for user management, product management, browsing/purchase history, and recommendations.
   - Enter inputs as prompted to perform operations.

4. Exit the Program
   - Choose the "Exit" option from the main menu to free memory and terminate the program.


Example Workflow
1. Add a user:
   - Enter user ID, name, and email.
2. Add a product:
   - Enter product ID, name, and price.
3. Log a browsing event:
   - Enter product ID and event type ("browse").
4. View browsing history:
   - Retrieve browsing and purchase history for a product.
5. Get a recommendation:
   - View the most popular product.

Error Handling
- Validates user input for proper formats.
- Handles invalid product or user IDs gracefully.
- Ensures memory cleanup during program termination.

Future Enhancements
1. Add a database or file system integration for persistent storage.
2. Enhance recommendation logic to consider user-specific preferences.
3. Add functionality for removing users and products.
4. Generation of bill.

