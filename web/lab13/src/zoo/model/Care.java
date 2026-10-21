package zoo.model;

public class Care {
    private int id;
    private int animalId;
    private String description;
    private String type;

    public Care() {}

    public Care(int id, int animalId, String description, String type) {
        this.id = id;
        this.animalId = animalId;
        this.description = description;
        this.type = type;
    }

    public int getId() { return id; }
    public void setId(int id) { this.id = id; }

    public int getAnimalId() { return animalId; }
    public void setAnimalId(int animalId) { this.animalId = animalId; }

    public String getDescription() { return description; }
    public void setDescription(String description) { this.description = description; }

    public String getType() { return type; }
    public void setType(String type) { this.type = type; }

    @Override
    public String toString() {
        return String.format("Care{id=%d, animalId=%d, type='%s', description='%s'}",
                id, animalId, type, description);
    }
}