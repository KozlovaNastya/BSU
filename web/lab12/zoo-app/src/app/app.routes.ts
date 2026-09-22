import { Routes } from '@angular/router';
import { ZOO_ROUTES } from './Zoo/zoo.routes';

export const routes: Routes = [
  {
    path: 'zoo',
    children: ZOO_ROUTES,
  },
  { path: '', redirectTo: '/zoo', pathMatch: 'full' },
  { path: '**', redirectTo: '/zoo' },
];