package zoo.model;

import jakarta.persistence.*;

@Entity
@Table(name = "cares")
public class Care {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    private String description;
    private String type;

    // Связь: много записей об уходе относятся к одному животному
    @ManyToOne
    @JoinColumn(name = "animal_id")
    private Animal animal;

    public Care() {}

    public Care(String description, String type, Animal animal) {
        this.description = description;
        this.type = type;
        this.animal = animal;
    }

    public Care(int id, String description, String type, Animal animal) {
        this.id = id;
        this.description = description;
        this.type = type;
        this.animal = animal;
    }

    public int getId() { return id; }
    public void setId(int id) { this.id = id; }
    public String getDescription() { return description; }
    public void setDescription(String description) { this.description = description; }
    public String getType() { return type; }
    public void setType(String type) { this.type = type; }
    public Animal getAnimal() { return animal; }
    public void setAnimal(Animal animal) { this.animal = animal; }

    @Override
    public String toString() {
        return String.format("Care{id=%d, type='%s', description='%s'}",
                id, type, description);
    }
}