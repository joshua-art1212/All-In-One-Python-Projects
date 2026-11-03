# FinanceApp

A lightweight personal finance dashboard built with **C++**, **Qt 6**, **Qt Charts**, and **SQLite**. The application provides a graphical dashboard for displaying financial information and organizing transactions by category and tag.

## Description

FinanceApp is a desktop personal finance dashboard created as a contribution for issue #93 of the `All-In-One-Python-Projects` repository.

The project uses Qt Widgets for the graphical user interface and Qt Charts for financial visualization. SQLite is used through Qt's SQL module to provide local database storage.

The application includes:

- A graphical finance dashboard
- Transaction information displayed in a table
- Category and tag information for transactions
- A spending/money-allocation pie chart
- Transaction and deposit interface windows
- Local SQLite database support
- Database functions for recording transactions, managing category balances, and calculating financial totals

The dashboard was designed to provide a lightweight alternative to larger personal finance applications while keeping the interface simple and easy to understand.

## Prerequisites

The following software is required to build and run FinanceApp:

- C++ compiler
- Qt 6.5 or later
- Qt Widgets
- Qt Charts
- Qt SQL
- SQLite
- CMake 3.19 or later
- Qt Creator (recommended)

## Installing Instructions

1. Clone the repository:

```bash
git clone https://github.com/king04aman/All-In-One-Python-Projects.git
```

2. Open the `FinanceApp` directory in Qt Creator.

3. Configure the project with a Qt 6 kit and CMake.

4. Build the project.

5. Run `FinanceApp`.

The application uses an SQLite database named `finance.db` for local financial data.

## Database Structure and Behavior

The database layer is implemented in [`database.h`](./database.h) and [`database.cpp`](./database.cpp) using Qt's SQL module with the SQLite driver. When the `Database` object is created, it opens `finance.db` in the application's current working directory and creates the database tables.

The database contains two tables:

| Table | Columns | Purpose |
|---|---|---|
| `containers` | `id` (auto-incrementing primary key), `category`, `tag`, `amount` | Stores the user's category balances. A category is the named container, while the tag classifies it as `Spending`, `Giving`, or `Saving`. |
| `transactions` | `id` (auto-incrementing primary key), `category`, `tag`, `amount` | Keeps a record of transaction entries, including their category, tag, and amount. |

The `Database` class provides the following operations:

- `create_Container_Table()` and `create_Transaction_Table()` define the tables when the database is initialized.
- `addContainer(category, tag, amount)` adds a starting balance or allocation to `containers`.
- `addTransaction(category, tag, amount)` records a transaction in `transactions` and subtracts its amount from the matching container (the same category and tag).
- `deleteContainer()` removes all rows from `containers`. It does not delete the transaction history.
- `getTotal()` returns the sum of the current amounts in all containers.
- `totalSpending()`, `totalGiving()`, and `totalSaving()` return the sum of container amounts for the corresponding tag.
- `getDatabase()` exposes the Qt database connection so other parts of the application can run queries.

The add-container and transaction windows validate their input before calling the database methods. After a successful save, the main window reads the container rows again to refresh the category table and updates the balance and pie chart using the total functions. Transaction records are stored separately from container balances; the displayed totals are calculated from the current `containers` amounts.

## Technologies Used

- **C++** — application logic
- **Qt Widgets** — graphical user interface
- **Qt Charts** — financial data visualization
- **Qt SQL** — database interface
- **SQLite** — local data storage
- **CMake** — project configuration and build system

## Screenshot

"...\All-In-One-Python-Projects\FinanceApp\QT_Design.png"
"...\All-In-One-Python-Projects\FinanceApp\QT_Environmentpng.png"
"...\All-In-One-Python-Projects\FinanceApp\Dashboard.png"



## Author

Joshua Wilson
