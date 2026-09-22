# ASP.NET Core MVC with MS Access (OleDb / ADO.NET)

Educational project for the "Web Programming" course.
Demonstrates remote database access from an ASP.NET Core MVC application
using ADO.NET (OleDb provider) and **stored queries** (Access QueryDef)
with parameters.


## Task

> Preliminary step: create stored queries with parameters in the
> `critters.accdb` database — for selection, deletion, update, and insertion.
>
> Program: using remote database access, demonstrate calling stored
> queries with parameters.

The application must:
- connect to a Microsoft Access database (`.accdb`) remotely;
- create and invoke **stored queries** (QueryDef) with parameters;
- demonstrate all four CRUD operations: Select, Insert, Update, Delete.


## Tech stack

| Component | Version / Notes |
|---|---|
| .NET | 8.0 |
| ASP.NET Core | MVC |
| Data access | ADO.NET (`System.Data.OleDb`) |
| Database | Microsoft Access (`.accdb`) |
| OLE DB provider | `Microsoft.ACE.OLEDB.12.0` |
| ORM | none (raw ADO.NET on purpose) |

## Project structure
```
lab1/
├── Controllers/
│ ├── HomeController.cs # default (unused)
│ └── PlayerController.cs # main controller
├── Models/
│ ├── ErrorViewModel.cs # default
│ └── Player.cs # domain model mapped to [roster] table
├── Services/
│ └── PlayerService.cs # all DB access + stored query creation
├── Views/
│ ├── Home/ # default
│ ├── Player/
│ │ ├── Index.cshtml # list + filter by position
│ │ ├── Create.cshtml # add new player
│ │ ├── Edit.cshtml # rename player
│ │ ├── Delete.cshtml # confirm deletion
│ │ └── Details.cshtml # single player card
│ └── Shared/ # default layout
├── appsettings.json # connection string
├── Program.cs # DI registration + startup
└── lab1.csproj
```

## Database schema

Single table `roster`:

| Column | Type | Description |
|---|---|---|
| playerid | TEXT | Primary key |
| jersey | SHORT | Jersey number |
| fname | TEXT | First name |
| sname | TEXT | Surname |
| position | TEXT | Playing position (RW, LW, D, ...) |
| birthday | DATETIME | Date of birth |
| weight | SHORT | Weight, kg |
| height | SHORT | Height, cm |
| birthcity | TEXT | City of birth |
| birthstate | TEXT | State / country code |

> Note: `position` is a reserved word in Access, therefore all column
> names are wrapped in square brackets `[position]` in SQL queries.

## Stored queries

Four stored queries (Access QueryDef) are created **programmatically**
at application startup via `CREATE PROCEDURE` statements, executed by
`PlayerService.EnsureStoredQueries()`.

| Query name | Purpose | Parameters |
|---|---|---|
| `qrySelectAll` | Select all players | — |
| `qrySelectByPosition` | Select players by position | `pos TEXT` |
| `qryDeleteById` | Delete player by ID | `pid TEXT` |
| `qryUpdateFname` | Update player's first name | `newName TEXT, pid TEXT` |
| `qryInsertPlayer` | Insert new player | 10 parameters |

The queries are invoked from C# code through `OleDbCommand` with
`CommandType.StoredProcedure` and `AddWithValue(...)`.

Example:

```csharp
using var cmd = new OleDbCommand("qrySelectByPosition", conn);
cmd.CommandType = CommandType.StoredProcedure;
cmd.Parameters.AddWithValue("pos", position);
```

## How to run
1. Install the OLE DB provider (only once per machine):
  - Microsoft Access Database Engine 2016 Redistributable (x64).

2. Place the database file `CRITTERS.accdb` on your disk, e.g.
`D:\dp1\lab1\CRITTERS.accdb`. If you put it elsewhere, update the
AccessDb connection string in `appsettings.json`.

3. Build and run:

```bash
dotnet build
dotnet run
```
or just press *F5* in Visual Studio.

4. Open `https://localhost:7275/Player` in a browser.
