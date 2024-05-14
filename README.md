# **Order Fulfillment System**

The Order Fulfillment System is a comprehensive application developed in C++ to manage customer orders, inventory, and order processing efficiently. This system utilizes various classes and functionalities to streamline the order fulfillment process.

## **Features**

**Dynamic Order Processing**

Dynamic memory allocation and move semantics are used to efficiently manage order processing within the system. This means that memory is allocated dynamically as needed during runtime, allowing for more flexible memory management compared to static allocation. Move semantics are employed to efficiently transfer resources (such as memory) from one object to another, reducing unnecessary copying and improving overall performance.

```cpp
// Example code demonstrating dynamic memory allocation and move semantics
// CustomerOrder constructor
CustomerOrder::CustomerOrder(const string& line) {
    // ...
    while (more) {
        // Allocate memory dynamically for new Item objects
        // ...
    }
}

// Move constructor for CustomerOrder
CustomerOrder::CustomerOrder(CustomerOrder&& RO) noexcept {
    *this = move(RO)
}
```

### **Customer Order Handling**

The **`CustomerOrder`** class is responsible for representing and managing customer orders within the system. It stores information about each order, including item details and order status. This class encapsulates the logic for handling customer orders, such as filling items and checking order status.

```cpp
// Example code demonstrating CustomerOrder class
class CustomerOrder {
public:
    // Constructor
    CustomerOrder(const string& line);

    // Method to fill items in the order
    void fillItem(Station& station, std::ostream& os);

    // Method to check if the order is filled
    bool isOrderFilled() const;

    // Method to check if a specific item in the order is filled
    bool isItemFilled(const std::string& itemName) const;
};
```

### **Line Management**

The **`LineManager`** class is designed to manage the flow of orders through various workstations in the assembly line. It ensures that orders are processed efficiently and delivered smoothly by coordinating the movement of orders between workstations. This class facilitates the organization and coordination of the assembly line, optimizing the order fulfillment process.

```cpp
// Example code demonstrating LineManager class
class LineManager {
public:
    // Constructor
    LineManager(const std::string& file, const std::vector<Workstation*>& stations);

    // Method to reorder stations based on configuration
    void reorderStations();

    // Method to run the assembly line and process orders
    bool run(ostream& os);

    // Method to display the status of stations in the assembly line
    void display(std::ostream& os) const;
};
```

### **Workstation Functionality**

The **`Workstation`** class represents individual workstations responsible for processing orders and updating inventory. It encapsulates the functionality required for processing orders at each workstation, including filling items and moving orders to the next station in the assembly line.

```cpp
// Example code demonstrating Workstation class
class Workstation {
public:
    // Method to fill items at the workstation
    void fill(std::ostream& os);

    // Method to attempt to move an order to the next station
    bool attemptToMoveOrder();

    // Method to set the next station in the assembly line
    void setNextStation(Workstation* station);

    // Method to display the status of the workstation
    void display(std::ostream& os) const;
};
```

### **Example Input Files**

- **AssemblyLine.txt**: Specifies the configuration of the assembly line, indicating the order in which stations are connected.
- **CustomerOrders.txt**: Contains customer orders to be processed by the system.
- **Stations1.txt** and **Stations2.txt**: Provide information about the stations involved in the fulfillment process, including item names, serial numbers, quantities, and descriptions.

### **Example Output**

After running the Order Fulfillment System, the program will display the processed orders, inventory status, and any relevant information.

### **Dependencies**

- C++ compiler
- Input files in CSV and text formats