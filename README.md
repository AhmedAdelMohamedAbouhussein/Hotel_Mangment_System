# Hotel_Mangment_System
A simple hotel management system in C that tracks room availability, customer check-ins/outs, and calculates bills. The system reads and writes data to files, allowing it to store customer information and track total profits over time.

The code implements a hotel room management system where customers can book, modify, or delete rooms. The system handles different room types (single, double, triple, and suites) with varying prices and offers business discounts for eligible customers.

Main Features:
Display Room Information (Display_Rooms):

The function iterates over all rooms and prints details such as room price, occupancy, and customer information.

For occupied rooms, it displays the customer's name and ID, as well as the applicable business discount.

Delete Room (Delete_Room):

Allows a customer to delete a room reservation.

The function prompts for the room number if the customer has booked multiple rooms. The price is adjusted based on the room type and any packages selected (breakfast, half-board, or all-inclusive).

The system removes the room booking and adjusts the customer's total charges accordingly.

Delete Customer (Delete_Customer):

Deletes all rooms booked by a specific customer and resets the room and customer details.

The function resets room prices and occupancy statuses and removes any assigned packages.

Change Room (Change_Room):

Customers can switch rooms based on available room types and prices.

The program verifies if the room is available and updates the customer's total price accordingly.

Business customers get a discount when changing to eligible rooms.

Change Package (Change_Package):

Allows customers to change the package associated with their room (e.g., breakfast only, half-board, or all-inclusive).

The room price is updated based on the new package, and the customer's total price is adjusted accordingly.

Pricing Logic:
Room prices are based on the type: Single ($100), Double ($150), Triple ($200), and Suite ($250).

Business customers receive a 20% discount.

Package prices are deducted from the customer’s fee when changing:

Breakfast only: $5

Half board: $10

All-inclusive: $15

Error Handling:
The system validates user input when selecting room types, numbers, and packages.

The program checks for available rooms before confirming any changes and ensures the customer doesn't attempt to book or modify a room that's already occupied.

Key Considerations:
The system assumes a maximum of 100 rooms and 100 customers.

The room prices and packages can be modified based on user interaction, with clear feedback if invalid choices are made.

This system offers an intuitive interface for managing room bookings, providing flexibility in managing customer reservations and room assignments with real-time price adjustments.

