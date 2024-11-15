#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct User
{
    int userId;
    char userName[50];
    char email[50];
    struct User *next;
} User;

typedef struct Product
{
    int productId;
    char productName[50];
    float price;
    struct Product *next;
} Product;

typedef struct TreeNode
{
    int productId;
    char productName[50];
    int browseCount;
    int purchaseCount;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

void adduser(User **userList, int userId, char *userName, char *email);
void updateuser(User *userList, int userId, char *userName, char *email);
User *getuser(User *userList, int userId);
void freeuser(User *userList);

void adprod(Product **productList, int productId, char *productName, float price, TreeNode **historyRoot);
void updateprod(Product *productList, int productId, char *productName, float price, TreeNode *historyRoot);
Product *getprod(Product *productList, int productId);
void freeprod(Product *productList);

TreeNode *insertevent(TreeNode *root, int productId, char *productName, char *eventType);
void updatehistory(TreeNode *root, int productId, char *eventType);
void retrievehistory(TreeNode *root, int productId);
void recommendprod(TreeNode *root);
void recommendprodhelper(TreeNode *root, TreeNode **mostRecommended, int *highestScore);
void freetree(TreeNode *root);
TreeNode *getprodhistorynode(TreeNode *root, int productId);

int main()
{
    User *userList = NULL;
    Product *productList = NULL;
    TreeNode *historyRoot = NULL;

    int choice, userId, productId;
    char userName[40], email[55], productName[40], eventType[10];
    float productPrice;

    while (1)
    {
        printf("\nMain Menu\n");
        printf("1)User Management\n");
        printf("2)Product Management\n");
        printf("3)Browsing & Purchase History\n");
        printf("4)Retrieve Browsing/Purchase History\n");
        printf("5)Recommendation Engine\n");
        printf("6)Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (choice)
        {
        case 1:
            printf("\nUser Management:\n");
            printf("1)Add User\n");
            printf("2)Update User\n");
            printf("3)Retrieve User\n");
            printf("Enter your choice: ");
            if (scanf("%d", &choice) != 1)
            {
                printf("Invalid input.\n");
                continue;
            }
            switch (choice)
            {
            case 1:
                printf("Enter User ID: ");
                scanf("%d", &userId);
                printf("Enter User Name: ");
                scanf(" %[^\n]", userName);
                printf("Enter Email: ");
                scanf(" %[^\n]", email);
                adduser(&userList, userId, userName, email);
                break;
            case 2:
                printf("Enter User ID to update: ");
                scanf("%d", &userId);
                printf("Enter New User Name: ");
                scanf(" %[^\n]", userName);
                printf("Enter New Email: ");
                scanf(" %[^\n]", email);
                updateuser(userList, userId, userName, email);
                break;
            case 3:
                printf("Enter User ID to retrieve: ");
                scanf("%d", &userId);
                User *user = getuser(userList, userId);
                if (user)
                {
                    printf("User found: ID=%d, Name=%s, Email=%s\n", user->userId, user->userName, user->email);
                }
                else
                {
                    printf("User not found.\n");
                }
                break;

            default:
                printf("Invalid choice.\n");
                break;
            }
            break;

        case 2:
            printf("\nProduct Management:\n");
            printf("1)Add Product\n");
            printf("2)Update Product\n");
            printf("3)Retrieve Product\n");
            printf("Enter your choice: ");
            if (scanf("%d", &choice) != 1)
            {
                printf("Invalid input.\n");
                continue;
            }
            switch (choice)
            {
            case 1:
                printf("Enter Product ID: ");
                scanf("%d", &productId);
                printf("Enter Product Name: ");
                scanf(" %[^\n]", productName);
                printf("Enter Product Price: ");
                scanf("%f", &productPrice);
                adprod(&productList, productId, productName, productPrice, &historyRoot);
                break;
            case 2:
                printf("Enter Product ID to update: ");
                scanf("%d", &productId);
                printf("Enter the new product Name: ");
                scanf(" %[^\n]", productName);
                printf("Enter  the new product price: ");
                scanf("%f", &productPrice);
                updateprod(productList, productId, productName, productPrice, historyRoot);
                break;
            case 3:
                printf("Enter Product ID to retrieve: ");
                scanf("%d", &productId);
                Product *product = getprod(productList, productId);
                if (product)
                {
                    printf("Product found: ID=%d, Name=%s, Price=%.2f\n", product->productId, product->productName, product->price);
                }
                else
                {
                    printf("Product not found.\n");
                }
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
            break;

        case 3:
            printf("\nEnter Product ID: ");
            scanf("%d", &productId);

            if (productId <= 0)
            {
                printf("Invalid Product ID. Please try again.\n");
            }
            else
            {
                TreeNode *productNode = getprodhistorynode(historyRoot, productId);

                if (productNode == NULL)
                {
                    printf("Product ID %d not found in the Database.\n", productId);
                }
                else
                {
                    printf("Enter Event Type (browse/purchase): ");
                    scanf(" %[^\n]", eventType);
                    updatehistory(historyRoot, productId, eventType);
                    printf("History updated for Product ID %d.\n", productId);
                }
            }
            break;

        case 4:
            printf("Enter Product ID to retrieve history: ");
            scanf("%d", &productId);
            retrievehistory(historyRoot, productId);
            break;

        case 5:
            printf("Recommending most popular products...\n");
            recommendprod(historyRoot); // No need for thresholds now
            break;

        case 6:
            printf("Thank You!\n");
            freeuser(userList);
            freeprod(productList);
            freetree(historyRoot);
            exit(0);

        default:
            printf("Invalid choice.\n");
        }
    }
    return 0;
}

void adduser(User **userList, int userId, char *userName, char *email)
{
    User *newUser = (User *)malloc(sizeof(User));
    newUser->userId = userId;
    strcpy(newUser->userName, userName);
    strcpy(newUser->email, email);
    newUser->next = *userList;
    *userList = newUser;
}

void updateuser(User *userList, int userId, char *userName, char *email)
{
    User *user = getuser(userList, userId);
    if (user)
    {
        strcpy(user->userName, userName);
        strcpy(user->email, email);
        printf("User updated successfully.\n");
    }
    else
    {
        printf("User not found.\n");
    }
}

User *getuser(User *userList, int userId)
{
    User *current = userList;
    while (current)
    {
        if (current->userId == userId)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void freeuser(User *userList)
{
    User *temp;
    while (userList)
    {
        temp = userList;
        userList = userList->next;
        free(temp);
    }
}

void adprod(Product **productList, int productId, char *productName, float price, TreeNode **historyRoot)
{
    Product *newProduct = (Product *)malloc(sizeof(Product));
    newProduct->productId = productId;
    strcpy(newProduct->productName, productName);
    newProduct->price = price;
    newProduct->next = *productList;
    *productList = newProduct;

    *historyRoot = insertevent(*historyRoot, productId, productName, "browse");
}

void updateprod(Product *productList, int productId, char *productName, float price, TreeNode *historyRoot)
{
    Product *product = getprod(productList, productId);
    if (product)
    {
        strcpy(product->productName, productName);
        product->price = price;
        updatehistory(historyRoot, productId, "browse"); // Assuming browsing event on update
        printf("Product updated successfully.\n");
    }
    else
    {
        printf("Product not found.\n");
    }
}

Product *getprod(Product *productList, int productId)
{
    Product *current = productList;
    while (current)
    {
        if (current->productId == productId)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void freeprod(Product *productList)
{
    Product *temp;
    while (productList)
    {
        temp = productList;
        productList = productList->next;
        free(temp);
    }
}

TreeNode *insertevent(TreeNode *root, int productId, char *productName, char *eventType)
{
    if (!root)
    {
        root = (TreeNode *)malloc(sizeof(TreeNode));
        root->productId = productId;
        strcpy(root->productName, productName);
        root->browseCount = (strcmp(eventType, "browse") == 0) ? 1 : 0;
        root->purchaseCount = (strcmp(eventType, "purchase") == 0) ? 1 : 0;
        root->left = root->right = NULL;
        return root;
    }

    if (productId < root->productId)
    {
        root->left = insertevent(root->left, productId, productName, eventType);
    }
    else if (productId > root->productId)
    {
        root->right = insertevent(root->right, productId, productName, eventType);
    }
    else
    {
        if (strcmp(eventType, "browse") == 0)
        {
            root->browseCount++;
        }
        else if (strcmp(eventType, "purchase") == 0)
        {
            root->purchaseCount++;
        }
    }

    return root;
}

void updatehistory(TreeNode *root, int productId, char *eventType)
{
    if (!root)
    {
        return;
    }

    if (productId < root->productId)
    {
        updatehistory(root->left, productId, eventType);
    }
    else if (productId > root->productId)
    {
        updatehistory(root->right, productId, eventType);
    }
    else
    {
        if (strcmp(eventType, "browse") == 0)
        {
            root->browseCount++;
        }
        else if (strcmp(eventType, "purchase") == 0)
        {
            root->purchaseCount++;
        }
    }
}

void retrievehistory(TreeNode *root, int productId)
{
    if (!root)
    {
        printf("No history found.\n");
        return;
    }
    if (productId < root->productId)
    {
        retrievehistory(root->left, productId);
    }
    else if (productId > root->productId)
    {
        retrievehistory(root->right, productId);
    }
    else
    {
        printf("History for Product ID=%d (%s): Browsed=%d, Purchased=%d\n",
               root->productId, root->productName, root->browseCount, root->purchaseCount);
    }
}

void recommendprod(TreeNode *root)
{
    if (root == NULL)
    {
        printf("No products to recommend.\n");
        return;
    }

    TreeNode *mostRecommended = NULL;
    int highestScore = 0;

    recommendprodhelper(root, &mostRecommended, &highestScore);

    if (mostRecommended != NULL)
    {
        printf("Most Recommended Product: ID=%d, Name=%s (Browsed=%d, Purchased=%d)\n",
               mostRecommended->productId, mostRecommended->productName,
               mostRecommended->browseCount, mostRecommended->purchaseCount);
    }
}

void recommendprodhelper(TreeNode *root, TreeNode **mostRecommended, int *highestScore)
{
    if (root == NULL)
    {
        return;
    }

    int totalScore = root->browseCount + root->purchaseCount;

    if (totalScore > *highestScore)
    {
        *highestScore = totalScore;
        *mostRecommended = root;
    }

    recommendprodhelper(root->left, mostRecommended, highestScore);
    recommendprodhelper(root->right, mostRecommended, highestScore);
}

void freetree(TreeNode *root)
{
    if (root)
    {
        freetree(root->left);
        freetree(root->right);
        free(root);
    }
}

TreeNode *getprodhistorynode(TreeNode *root, int productId)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (productId < root->productId)
    {
        return getprodhistorynode(root->left, productId);
    }
    else if (productId > root->productId)
    {
        return getprodhistorynode(root->right, productId);
    }
    else
    {
        return root;
    }
}
