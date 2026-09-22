import { ComponentFixture, TestBed } from '@angular/core/testing';

import { AnimalList } from './animal-list';

describe('AnimalList', () => {
  let component: AnimalList;
  let fixture: ComponentFixture<AnimalList>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [AnimalList],
    }).compileComponents();

    fixture = TestBed.createComponent(AnimalList);
    component = fixture.componentInstance;
    await fixture.whenStable();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
