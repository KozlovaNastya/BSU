package zoo.model;

public class Animal {
    private int id;
    private String name;
    private String kind;
    private int age;
    private double weight;

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

    @Override
    public String toString() {
        return String.format("Animal{id=%d, name='%s', kind='%s', age=%d, weight=%.2f}",
                id, name, kind, age, weight);
    }
}