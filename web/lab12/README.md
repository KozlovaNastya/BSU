# Angular Zoo App

Lab work #2: Angular, TypeScript, Firebase.

## Features
- SPA with Angular Router
- Animal list with details view
- Template-driven form (add / edit / delete)
- Firestore service for Cloud Firestore

## Tech Stack
- Angular 21
- TypeScript
- Bootstrap 5
- Firebase + Cloud Firestore

## Run
```bash
npm install
ng serve
```

## Project Structure
```
src/app/
├── Zoo/
│   ├── animal-center/       # Parent component
│   ├── animal-list/         # List of animals
│   ├── animal-details/      # Animal details
│   ├── animal-form/         # Add/edit form
│   ├── services/
│   │   ├── animal.service.ts
│   │   └── firestore.service.ts
│   ├── animal.ts            # Model
│   ├── mock-animal-list.ts  # Mock data
│   └── zoo.routes.ts        # Child routes
├── app.routes.ts            # Main routes
├── app.ts                   # Root component
└── firebase.config.ts       # Firebase config (not committed)
```

## Firebase Setup
1. Create a project in Firebase Console

2. Enable Cloud Firestore (test mode)

3. Create collection animals with documents

4. Copy `firebase.config.example.ts` → `firebase.config.ts` and fill in your data
