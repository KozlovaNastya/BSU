package zoo.model;

import jakarta.persistence.*;
import java.util.List;

@Entity
@Table(name = "keepers")
public class Keeper {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    private String name;
    private String phone;

    // Связь: у смотрителя много заданий
    @OneToMany(mappedBy = "keeper", cascade = CascadeType.ALL)
    private List<Task> tasks;

    public Keeper() {}

    public Keeper(int id, String name, String phone) {
        this.id = id;
        this.name = name;
        this.phone = phone;
    }

    public int getId() { return id; }
    public void setId(int id) { this.id = id; }
    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public String getPhone() { return phone; }
    public void setPhone(String phone) { this.phone = phone; }
    public List<Task> getTasks() { return tasks; }
    public void setTasks(List<Task> tasks) { this.tasks = tasks; }
}