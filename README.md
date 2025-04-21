Hotel Room Management System
  This is a Hotel Room Management System written in C that allows customers to book, modify, and delete room reservations. The system handles different room types, adjusts     prices based on packages and discounts, and offers functionalities for managing room occupancy and customer bookings.

Features
1. Display Room Information
  The system displays a list of all available rooms and their details, including room price, occupancy status, and customer information. If the room is occupied, the       
  customer's name and ID are shown, along with any business discounts applied.

2. Delete Room
  Customers can delete a room reservation. If multiple rooms have been booked, the system prompts the user to select which room to delete. The price is adjusted based on the   room type and the package selected.

3. Delete Customer
  Deletes all rooms booked by a specific customer, resets room information (such as price and occupancy), and removes any packages associated with the booking.

4. Change Room
  Allows customers to change their current room. The program verifies if the selected room is available, and updates the customer's total fee accordingly. Business customers 
  receive a discount when changing to an eligible room.

5. Change Package
  Customers can change the package associated with their room, such as "breakfast only", "half board", or "all-inclusive". The price of the room is updated based on the     
  selected package, and the customer's total price is adjusted.

Pricing Logic:

Room Types and Prices:
  Single Room: $100
  Double Room: $150
  Triple Room: $200
  Suite: $250

Business Discount:
  Business customers receive a 20% discount on room prices.

Package Prices:
  Breakfast Only: $5
  Half Board: $10
  All-Inclusive: $15

Price Adjustments:
  When changing rooms or packages, the total customer price is recalculated based on the new room and package selections.

Error Handling
  Input validation is performed for room selections, package choices, and customer IDs.
  The system ensures that rooms are available before confirming any booking or modification.
  If the user attempts to book or modify an already occupied room, the system will provide an error message.

Usage:
  Clone the repository:
    git clone https://github.com/AhmedAdelMohamedAbouhussein/Hotel_Mangment_System.git

  Compile the program:
    gcc -o hotel_management hotel_management.c
    
  Run the program:
  ./hotel_management
  
Follow the on-screen prompts to book, change, or delete rooms, as well as to modify packages.
