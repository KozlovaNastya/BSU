import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { ActivatedRoute, Router, RouterLink } from '@angular/router';
import { Animal } from '../animal';
import { AnimalService } from '../services/animal.service';

@Component({
  selector: 'app-animal-form',
  standalone: true,
  imports: [CommonModule, FormsModule, RouterLink],
  templateUrl: './animal-form.html',
  styleUrl: './animal-form.css',
})
export class AnimalForm implements OnInit {
  animal: Animal = {
    id: '',                 
    animalkind: '',
    nikname: '',
    age: '',
    weight: '',
  };

  isEditMode = false;

  constructor(
    private route: ActivatedRoute,
    private router: Router,
    private animalService: AnimalService
  ) {}

  ngOnInit(): void {
    const id = this.route.snapshot.paramMap.get('id');
    if (id) {
      this.isEditMode = true;
      const existing = this.animalService.getAnimalById(id);
      if (existing) {
        this.animal = { ...existing };
      }
    }
  }

  save(): void {
    if (this.isEditMode) {
      this.animalService.updateAnimal(this.animal);
    } else {
      this.animalService.addAnimal(this.animal);
    }
    this.router.navigate(['/zoo']);
  }

  delete(): void {
    if (confirm('Удалить это животное?') && this.animal.id) {
      this.animalService.deleteAnimal(this.animal.id);
      this.router.navigate(['/zoo']);
    }
  }

  cancel(): void {
    this.router.navigate(['/zoo']);
  }
}