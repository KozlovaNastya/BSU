package zoo.model;

import jakarta.persistence.*;
import java.util.List;

@Entity
@Table(name = "animals")
@NamedQueries({
    @NamedQuery(name = "Animal.findAll", query = "SELECT a FROM Animal a"),
    @NamedQuery(name = "Animal.findById", query = "SELECT a FROM Animal a WHERE a.id = :id")
})
public class Animal {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    private String name;
    private String kind;
    private int age;
    private double weight;

    // Связь: у одного животного много записей об уходе
    @OneToMany(mappedBy = "animal", cascade = CascadeType.ALL)
    private List<Care> cares;

    public Animal() {}

    public Animal(int id, String name, String kind, int age, double weight) {
        this.id = id;
        this.name = name;
        this.kind = kind;
        this.age = age;
        this.weight = weight;
    }

    public Animal(String name, String kind, int age, double weight) {
        this.name = name;
        this.kind = kind;
        this.age = age;
        this.weight = weight;
    }

    public int getId() { return id; }
    public void setId(int id) { this.id = id; }
    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public String getKind() { return kind; }
    public void setKind(String kind) { this.kind = kind; }
    public int getAge() { return age; }
    public void setAge(int age) { this.age = age; }
    public double getWeight() { return weight; }
    public void setWeight(double weight) { this.weight = weight; }
    public List<Care> getCares() { return cares; }
    public void setCares(List<Care> cares) { this.cares = cares; }

    @Override
    public String toString() {
        return String.format("Animal{id=%d, name='%s', kind='%s', age=%d, weight=%.2f}",
                id, name, kind, age, weight);
    }
}