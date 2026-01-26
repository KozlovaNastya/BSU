# Meeting Organization Client (RMI)

## Overview
This project is a **Java console-based client application** for a meeting organization system implemented using **Java RMI (Remote Method Invocation)**.

The client allows users to manage their free time schedule, register on a remote server, request meetings with other clients, and confirm or reject meeting requests.

> ⚠️ The **server side is implemented by another developer** and is not included in this project.

## Key Features
- RMI-based client–server communication
- Client registration on the server
- Local management of free time slots
- Synchronization of schedules with the server
- Viewing available clients
- Sending meeting requests
- Confirming or rejecting meetings
- Console-based interactive menu

## Technologies Used
- Java SE
- Java RMI
- Serializable objects
- `LocalDateTime`
- Console I/O (`Scanner`)

## Project Structure

### Main Classes

#### ClientMain
- Entry point of the application
- Reads client name from console
- Starts the meeting client

#### MeetingClient
Core client logic:
- Connects to RMI registry
- Looks up remote `MeetingService`
- Handles user interaction
- Manages local schedule
- Sends meeting requests and confirmations
- Disconnects gracefully from the server

#### ClientData
Serializable class that stores:
- Client name
- List of available `TimeSlot` objects

#### TimeSlot
Serializable representation of a free time interval:
- Start time (`LocalDateTime`)
- End time (`LocalDateTime`)

#### MeetingService (RMI Interface)
Defines remote methods:
- `registerClient`
- `updateSchedule`
- `getAvailableClients`
- `requestMeeting`
- `confirmMeeting`
- `disconnectClient`

#### ProtocolMessage
Serializable helper class describing message structure and types.
Included for compatibility and extensibility, although RMI methods are used directly.

## Date and Time Format
User input must follow the format: ``dd.MM.yyyy HH:mm``
Example: ``25.12.2024 14:30``


## Application Workflow
1. Client starts and connects to the RMI server
2. Client registers with a unique name
3. User manages local free time slots
4. Schedule is uploaded to the server
5. User requests meetings with other clients
6. User confirms or rejects meeting requests
7. Client disconnects from the server

## Requirements
- Java 8 or higher
- Running RMI server
- RMI registry available on the specified host and port
- Matching server-side implementation of `MeetingService`

## Notes
- This project contains **client-side code only**
- All business logic and meeting coordination are handled by the server
- Error handling focuses on input validation and RMI connection issues

