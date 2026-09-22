import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { ActivatedRoute, RouterLink } from '@angular/router';
import { Animal } from '../animal';
import { AnimalService } from '../services/animal.service';

@Component({
  selector: 'app-animal-details',
  standalone: true,
  imports: [CommonModule, RouterLink],
  templateUrl: './animal-details.html',
  styleUrl: './animal-details.css',
})
export class AnimalDetails implements OnInit {
  animal: Animal | undefined;

  constructor(
    private route: ActivatedRoute,
    private animalService: AnimalService
  ) {}

  ngOnInit(): void {
    const id = this.route.snapshot.paramMap.get('id');  // ← без Number()
    if (id) {
      this.animal = this.animalService.getAnimalById(id);
    }
  }
}