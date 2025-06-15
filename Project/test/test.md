# Administrator 

```sql

    1. Login as Administrator
    2. Login as User
    3. Register
    4. Exit

    Choice: 

```

```sql
When View Table
```
```C++
Table Name: AdminProductList() // Sok Leap
```
```sql
-------------------------------------------------------------------------------------------------
| ID    | MODEL     | IN STOCK | SOLD |        DESCRIPTION            | Price($) | STATUS       | 
-------------------------------------------------------------------------------------------------
| 1000  | Phone     | 45       | 76   | OS: IOS, Ram 24GB, Storage 1T | 100.0    | Available    |
addEnd(...)
-- | 2  | MacBook Air M2     | Laptop       | 20     | 15      | Available    |
-- | 3  | Galaxy S23 Ultra   | Phone        | 60     | 50      | Available    | 
-- | 4  | Dell XPS 13        | Laptop       | 18     | 12      | Low Stock    |
-- | 5  | AirPods Pro        | Accessories  | 80     | 70      | Available    |
-- | 6  | Canon EOS R7       | Camera       | 10     | 8       | Available    |
-- | 7  | Logitech MX Master | Accessories  | 25     | 20      | Available    |
-- | 8  | Redmi Note 12      | Phone        | 40     | 42      | Available    |
-- | 9  | Asus ROG Strix     | Laptop       | 8      | 6       | Low Stock    |
-- | 10 | Samsung T7 SSD     | Storage      | 50     | 50      | Out of Stock |
-- ----------------------------------------------------------------------------
```

# Admin
same features like user
extra: add, edit, delete, generate report
When view monthly report
```C++
Table Name: monthlyReport() // Davin
```
| ID | Model | TOTAL STOCK | SOLD | TOTAL PURCHASE COST | TOTAL EARN | PROFIT | ESTIMATE PROFIT |


When view transaction report
```C++
Table Name: transactionReport() // Val, Using Stack()
```
| ID | MODEL | CATEGORY | QUANTITY | TYPE | PRICE | Transaction Time |
# User
```sql
    1. View Product List
    2. Search 
    0. Back
```

```sql
    Categories
    1. Phone            >      
    2. Laptop           >
    3. Camera           >
    4. Accessories      >
    0. Back
```

```sql
    ID|MODEL|CHIP|RAM|STORAGE|PRICE|
    1000|iPhone 17 Pro Max|Apple A19 Bionic chip|12GB|256G|1499.99
```

When view product list
```C++
Table Name: userProductList() // Kheang ann
```
| ID    | MODEL     |        DESCRIPTION            | Price($) | STATUS       | 