#Implementation of StreamBase

##Explanations

###Environment

This project has been created using Visual Studio 2019 compiler and embedded build system of Visual Studio.

###Project Structure

Solution has three projects:
1. Client (exe). Contains client logic.
2. Server (exe). Contains server logic.
3. Common (lib). Contains shared structures and functions used by both projects.

###Solution Design

Client communicates with server using NamedPipe API. Server has a loop which supports processing only one client at a time. Server always listen for client actions. Server stores data sent from a client in its local storage. Server constructs a custom class instance after a request from the client. Client can receive objects after a corresponding request has been sent to a server. Client prints received data constructed by server. If client closes server will stays wait for another client.

###Common

NamedPipe API is wrapped in a class **Pipe**. Structure **Packet** is presented as a transfer unit. It consists of _action_ and _data_ fields. The Common also contains functions of a general handling of this classes. In case when a trivial data tranfers **Packet** contains 'Data' action in the first field and _raw bytes of data_ in the second field. In case when a non-trivial data tranfers **Packet** contains 'Data' action in the first field and _size for the next transfer unit_ in the second field. Second transfer unit is not a **Packet**. It is a raw data of non-trivial object of size brought previously in **Packet**. In case when a client sends request to create a custom object **Packet** contains 'Request' action in the first field and _type of object_ in the second field. Non-trivial objects are serializable.

###Client

Client connects to a server using **Pipe** class. Client demonstrates a transfer of trivial and custom types to a server in _sync_ and _async_ ways. Client is able send a request to server for creating a custom class instance and send it back ot the client. Connection looses and application finishes if any error has occured.

###Server

Server uses **Pipe** class to create a base for future connection. Server starts a loop for catching packets from a client. Server starts waiting for another client if the current client has been disconnected. If any other error occures server stops and closes. Server has a **Storage** for all known kind of data. **Storage** can construct and store non-trivial object on demand.


