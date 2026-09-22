import { ComponentFixture, TestBed } from '@angular/core/testing';

import { AnimalDetails } from './animal-details';

describe('AnimalDetails', () => {
  let component: AnimalDetails;
  let fixture: ComponentFixture<AnimalDetails>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [AnimalDetails],
    }).compileComponents();

    fixture = TestBed.createComponent(AnimalDetails);
    component = fixture.componentInstance;
    await fixture.whenStable();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
