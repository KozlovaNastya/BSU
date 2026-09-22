import { Injectable } from '@angular/core';
import { Animal } from '../animal';
import { ANIMALS } from '../mock-animal-list';

@Injectable({
  providedIn: 'root',
})
export class AnimalService {
  private animals: Animal[] = [...ANIMALS];

  getAnimals(): Animal[] {
    return this.animals;
  }

  getAnimalById(id: string): Animal | undefined {
    return this.animals.find((a) => a.id === id);
  }

  addAnimal(animal: Animal): void {
    const newId = String(
      Math.max(...this.animals.map((a) => Number(a.id) || 0), 0) + 1
    );
    this.animals.push({ ...animal, id: newId });
  }

  updateAnimal(animal: Animal): void {
    const index = this.animals.findIndex((a) => a.id === animal.id);
    if (index !== -1) {
      this.animals[index] = { ...animal };
    }
  }

  deleteAnimal(id: string): void {
    this.animals = this.animals.filter((a) => a.id !== id);
  }
}