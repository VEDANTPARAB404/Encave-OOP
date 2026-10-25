Encave

A small restaurant ordering website made with HTML, CSS, and OOP.

## Features

- Choose meals and sides from the menu.
- Add multiple quantities to an order.
- Remove items or reduce their quantity.
- See the subtotal, 5% GST, and total while ordering.
- Choose classroom delivery or counter pickup and see the option on the receipt.
- Generate a receipt after selecting the food.
- Start a new order without refreshing the page.

## How to run

1. Open `index.html` in a web browser.
2. Choose classroom delivery or counter pickup. For classroom delivery, select a classroom.
3. Click the `+` button beside meals and sides.
4. Check the order summary.
5. Click **Generate Bill**.

## OOP used

- `MenuItem` stores the name, price, and type of each menu item.
- `RestaurantOrder` stores the selected items and delivery option, and calculates quantities and totals.
- The website and `resto.cpp` both offer classroom delivery and counter pickup.
- In `resto.cpp`, `DeliveryOption` is an abstract base class. `ClassroomDelivery` and `CounterPickup` inherit from it and override `getDescription()`.
- `Order` stores a `DeliveryOption` through a base-class pointer, and the bill calls the overridden method to display the selected option at runtime (runtime polymorphism).
- Private data members and public methods demonstrate encapsulation; order and bill operations provide abstraction.

The C++ file, `resto.cpp`, contains the console version of the same restaurant billing idea, including classroom delivery and counter pickup.
