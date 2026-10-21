# Service-Oriented Architecture (WCF + gRPC)

Educational project for the "Web Programming" course.
The application from Lab 1 is transformed into a **service-oriented architecture**:
the database access logic is moved to separate **web services**, and the clients
communicate with them over the network.

Two independent variants are implemented, as required by the assignment:

1. **WCF (Windows Communication Foundation)** — REST binding (`webHttpBinding`)
2. **gRPC** — HTTP/2 + Protobuf

---

## Solution structure
```
Lab2.sln
├── lab1/ # Original Lab 1 app (.NET 8, works with DB directly)
├── WcfService/ # WCF service (.NET Framework 4.8)
├── lab1.WcfClient/ # WCF client (.NET 8)
├── GrpcService/ # gRPC service (.NET 8)
└── lab1.GrpcClient/ # gRPC client (.NET 8)
```


---

## Variant 1.1 — WCF (REST)

* Service: `WcfService` (.NET Framework 4.8)
* Binding: `webHttpBinding` (REST, JSON)
* Contract: `IPlayerService` with `[ServiceContract]` / `[OperationContract]`
* Model: `Player` with `[DataContract]` / `[DataMember]`
* WSDL: auto-generated, available at `http://localhost:52073/PlayerService.svc?wsdl`
* Proxy class: `lab1.WcfClient/Services/PlayerService.cs`

### How to run

1. Set `WcfService` and `lab1.WcfClient` as startup projects
   (Solution → Configure Startup Projects → Multiple startup projects).
2. Press **F5**.
3. Open `http://localhost:7275/Player`.

### Endpoints

| Method | URL |
|---|---|
| GetAll | `GET /PlayerService.svc/players` |
| GetByPosition | `GET /PlayerService.svc/players/position/{pos}` |
| GetById | `GET /PlayerService.svc/players/{id}` |
| Insert | `POST /PlayerService.svc/players` |
| Update | `PUT /PlayerService.svc/players` |
| Delete | `DELETE /PlayerService.svc/players/{id}` |

---

## Variant 1.2 — gRPC

* Service: `GrpcService` (.NET 8)
* Protocol: HTTP/2, no TLS (h2c)
* Interface: `.proto` file (`Protos/player.proto`)
* Generated classes: `PlayerServiceBase` (server), `PlayerServiceClient` (client)
* Proxy class: `lab1.GrpcClient/Services/PlayerService.cs`

### How to run

1. Set `GrpcService` and `lab1.GrpcClient` as startup projects.
2. Press **F5**.
3. Open `http://localhost:7275/Player`.

### Server URL

`http://localhost:5006` — configured in `GrpcService/Program.cs` (Kestrel) and
`lab1.GrpcClient/Services/PlayerService.cs` (client).

---

## Database

Microsoft Access database `CRITTERS.accdb` with a single table `roster`.

The path to the database is hardcoded in:
* `WcfService/Services/PlayerDb.cs`
* `GrpcService/Services/PlayerDb.cs`

⚠️ **Change the path** if the file is not located at `D:\dp1\lab1\CRITTERS.accdb`.

---

## Key concepts covered

- Service-Oriented Architecture (SOA)
- WCF: ABC (Address, Binding, Contract), `webHttpBinding`, WSDL, proxy class
- gRPC: `.proto`, Protobuf, HTTP/2, generated `Base` and `Client` classes
- ADO.NET (OleDb) for MS Access access
- ASP.NET Core MVC (clients)

---

## License

Educational project. Free to use for learning purposes.