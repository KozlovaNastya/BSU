import { ComponentFixture, TestBed } from '@angular/core/testing';

import { AnimalCenter } from './animal-center';

describe('AnimalCenter', () => {
  let component: AnimalCenter;
  let fixture: ComponentFixture<AnimalCenter>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [AnimalCenter],
    }).compileComponents();

    fixture = TestBed.createComponent(AnimalCenter);
    component = fixture.componentInstance;
    await fixture.whenStable();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
