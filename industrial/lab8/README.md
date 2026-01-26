# Meeting Organization Client (TCP)

## Overview
This project is a **Java console client application** for a meeting organization system.  
The client connects to a remote server, manages a user’s free time schedule, and allows requesting meetings with other registered clients.

> ⚠️ The server side is implemented separately by another developer.

## Features
- Client registration on the server
- Local management of free time slots
- Synchronization of schedule with the server
- Requesting meetings with other clients
- Console-based interactive menu
- Object-based communication using Java serialization

## Project Structure

### Main Classes
- **ClientMain**  
  Entry point of the application. Reads the client name and starts the client interface.

- **MeetingClient**  
  Handles:
  - Server connection (TCP socket)
  - Sending and receiving protocol messages
  - User interaction via console
  - Schedule management and meeting requests

- **ClientData**  
  Stores client information:
  - Client name
  - List of available `TimeSlot` objects

- **TimeSlot**  
  Represents a free time interval using `LocalDateTime`:
  - Start time
  - End time

- **ProtocolMessage**  
  Serializable message sent from client to server.  
  Supports multiple message types:
  - `REGISTER`
  - `UPDATE_SCHEDULE`
  - `REQUEST_MEETING`
  - `GET_CLIENTS`
  - `CONFIRM_MEETING`
  - `MEETING_RESPONSE`
  - `ERROR`

- **ProtocolResponse**  
  Serializable response sent from server to client.  
  Contains:
  - Success flag
  - Message text
  - Available clients list
  - Proposed meeting time

## Communication
- Uses **TCP sockets**
- Data exchange via **ObjectInputStream / ObjectOutputStream**
- All transmitted objects implement `Serializable`

## Date and Time Format
User input format:
``dd.MM.yyyy HH:mm``
Example: ``25.12.2024 14:30``


## How It Works
1. Client starts and connects to the server
2. Client registers with a unique name
3. User manages free time slots locally
4. Schedule can be uploaded to the server
5. User can request a meeting with another client
6. Server processes and responds to requests

## Requirements
- Java 8 or higher
- Running server with matching protocol
- Network access to the server IP and port

## Notes
- This project contains **client-side code only**
- Server logic, validation, and meeting coordination are handled externally
- Error handling is focused on connection and input validation

## Technologies Used
- Java SE
- TCP/IP Sockets
- Java Serialization
- `LocalDateTime`
- Console-based UI

