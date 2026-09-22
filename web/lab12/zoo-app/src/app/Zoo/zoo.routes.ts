import { Routes } from '@angular/router';
import { AnimalCenter } from './animal-center/animal-center';
import { AnimalList } from './animal-list/animal-list';
import { AnimalDetails } from './animal-details/animal-details';
//import { AnimalForm } from './animal-form/animal-form';

export const ZOO_ROUTES: Routes = [
  {
    path: '',
    component: AnimalCenter,
    children: [
      { path: '', component: AnimalList },
      //{ path: 'new', component: AnimalForm },
      //{ path: 'edit/:id', component: AnimalForm },
      { path: ':id', component: AnimalDetails },
    ],
  },
];