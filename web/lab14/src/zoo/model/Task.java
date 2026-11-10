package zoo.model;

import jakarta.persistence.*;

@Entity
@Table(name = "tasks")
@NamedQueries({
    @NamedQuery(name = "Task.findAll", query = "SELECT t FROM Task t"),
    // запрос для поиска по смотрителю
    @NamedQuery(name = "Task.findByKeeper", query = "SELECT t FROM Task t WHERE t.keeper.id = :keeperId")
})
public class Task {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    private String description;
    private String status;
    private String dateAssigned;
    private String result;

    @ManyToOne
    @JoinColumn(name = "keeper_id")
    private Keeper keeper;

    @ManyToOne
    @JoinColumn(name = "animal_id")
    private Animal animal;

    @ManyToOne
    @JoinColumn(name = "care_id")
    private Care care;

    public Task() {}

    // Геттеры и сеттеры
    public int getId() { return id; }
    public void setId(int id) { this.id = id; }
    public String getDescription() { return description; }
    public void setDescription(String description) { this.description = description; }
    public String getStatus() { return status; }
    public void setStatus(String status) { this.status = status; }
    public String getDateAssigned() { return dateAssigned; }
    public void setDateAssigned(String dateAssigned) { this.dateAssigned = dateAssigned; }
    public String getResult() { return result; }
    public void setResult(String result) { this.result = result; }
    public Keeper getKeeper() { return keeper; }
    public void setKeeper(Keeper keeper) { this.keeper = keeper; }
    public Animal getAnimal() { return animal; }
    public void setAnimal(Animal animal) { this.animal = animal; }
    public Care getCare() { return care; }
    public void setCare(Care care) { this.care = care; }

    @Override
    public String toString() {
        return String.format("Task{id=%d, status='%s', desc='%s'}",
                id, status, description);
    }
}