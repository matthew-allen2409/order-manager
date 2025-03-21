# Order Manager

The **Order Manager** is a C++-based application that listens for incoming Financial Information Exchange (FIX) tag value messages over TCP, validates them, and forwards them to subscribed services. The system works with a custom, reduced version of the FIX protocol called **FIX.REDUCED**, which only requires the 40, 44, and 38 tags for order processing.

## Features

- **TCP-based Communication**: The application listens for incoming messages over a TCP socket.
- **FIX.REDUCED Protocol**: Implements a reduced version of the FIX protocol (using only tags 40, 44, and 38).
- **Message Validation**: Validates the FIX messages based on the **FIX.REDUCED** specification.
- **Message Forwarding**: Forwards validated messages to subscribed services over the created socket.
- **Simple Deployment**: Easy to run using a provided Makefile.

## Requirements

- C++11 or higher
- A TCP-capable environment (Linux, macOS, or Windows with appropriate network support)

## Setup

1. Clone the repository:
    ```bash
    git clone https://github.com/your-username/order-manager.git
    cd order-manager
    ```

2. Build the project using the provided `Makefile`:
    ```bash
    make
    ```

3. Run the application:
    ```bash
    ./order_manager
    ```

4. Optionally ingest documents:
    ```bash
    make ingest
    ```

    The application will start listening for incoming TCP connections on the default port (specified in the source code). Once a valid FIX.REDUCED message is received, it will be validated and forwarded to any subscribed services.

## Configuration

The application is configured via the source code and can be customized by modifying the port or the list of subscribed services. Refer to the code for details on how to modify configurations.

## Supported FIX Tags

The **FIX.REDUCED** specification supports the following tags:
- **Tag 40**: OrdType (Order Type)
- **Tag 44**: Price (Order Price)
- **Tag 38**: OrderQty (Order Quantity)
- Delimited using the byte value 0x01

These are the only required tags in the messages, making the specification much lighter compared to full FIX protocol implementations.

## Example Message

A sample **FIX.REDUCED** message could look like this:

"8=FIX.REDUCED""\x01""9=251""\x01""35=D""\x01""49=AFUNDMGR""\x01""56=ABROKER""\x01""34=2""\x01""52=2003061501:14:49""\x01""11=12345""\x01""1=111111""\x01""63=0""\x01""64=20030621""\x01""21=3""\x01""110=1000""\x01""111=50000""\x01""55=IBM""\x01""48=459200101""\x01""22=1""\x01""54=1""\x01""60=2003061501:14:49""\x01""38=5000""\x01""40=1""\x01""44=15.75""\x01""15=USD""\x01""59=0""\x01""10=127""\x01";

Where:
- **8=FIX.REDUCED**: Indicates the FIX version (for compatibility).
- **35=G**: Message type (New Order).
- **40=1**: Order Type (Bid).
- **44=123.45**: Price of the order.
- **38=1000**: Order Quantity.
