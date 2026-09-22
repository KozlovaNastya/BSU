import { Component } from '@angular/core';
import { RouterOutlet } from '@angular/router';

@Component({
  selector: 'app-animal-center',
  standalone: true,
  imports: [RouterOutlet],
  templateUrl: './animal-center.html',
  styleUrl: './animal-center.css',
})
export class AnimalCenter {}