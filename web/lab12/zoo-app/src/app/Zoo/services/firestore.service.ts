import { Injectable } from '@angular/core';
import { initializeApp } from 'firebase/app';
import {
  getFirestore,
  collection,
  getDocs,
  doc,
  getDoc,
  addDoc,
  updateDoc,
  deleteDoc,
  Firestore,
} from 'firebase/firestore';
import { firebaseConfig } from '../../firebase.config';
import { Animal } from '../animal';

@Injectable({
  providedIn: 'root',
})
export class FirestoreService {
  private db: Firestore;

  constructor() {
    const app = initializeApp(firebaseConfig);
    this.db = getFirestore(app);
  }

  // Получить всех животных
  async getAnimals(): Promise<Animal[]> {
    const ref = collection(this.db, 'animals');
    const snapshot = await getDocs(ref);
    return snapshot.docs.map((d) => {
      const data = d.data();
      return {
        id: d.id,
        animalkind: data['animalkind'],
        nikname: data['nikname'],
        age: data['age'],
        weight: data['weight'],
      } as Animal;
    });
  }

  // Получить одно животное по Firestore ID
  async getAnimalById(id: string): Promise<Animal | undefined> {
    const ref = doc(this.db, 'animals', id);
    const snapshot = await getDoc(ref);
    if (!snapshot.exists()) return undefined;
    const data = snapshot.data();
    return {
      id: snapshot.id,
      animalkind: data['animalkind'],
      nikname: data['nikname'],
      age: data['age'],
      weight: data['weight'],
    } as Animal;
  }

  // Добавить животное
  async addAnimal(animal: Animal): Promise<void> {
    const ref = collection(this.db, 'animals');
    await addDoc(ref, {
      animalkind: animal.animalkind,
      nikname: animal.nikname,
      age: animal.age,
      weight: animal.weight,
    });
  }

  // Обновить животное
  async updateAnimal(id: string, animal: Animal): Promise<void> {
    const ref = doc(this.db, 'animals', id);
    await updateDoc(ref, {
      animalkind: animal.animalkind,
      nikname: animal.nikname,
      age: animal.age,
      weight: animal.weight,
    });
  }

  // Удалить животное
  async deleteAnimal(id: string): Promise<void> {
    const ref = doc(this.db, 'animals', id);
    await deleteDoc(ref);
  }
}