package zoo.model;

public class Task {
    private int id;
    private int keeperId;
    private int animalId;
    private int careId;
    private String description;
    private String status;
    private String dateAssigned;
    private String result;

    public Task() {}

    public Task(int id, int keeperId, int animalId, int careId,
                String description, String status, String dateAssigned, String result) {
        this.id = id;
        this.keeperId = keeperId;
        this.animalId = animalId;
        this.careId = careId;
        this.description = description;
        this.status = status;
        this.dateAssigned = dateAssigned;
        this.result = result;
    }

    public int getId() { return id; }
    public void setId(int id) { this.id = id; }

    public int getKeeperId() { return keeperId; }
    public void setKeeperId(int keeperId) { this.keeperId = keeperId; }

    public int getAnimalId() { return animalId; }
    public void setAnimalId(int animalId) { this.animalId = animalId; }

    public int getCareId() { return careId; }
    public void setCareId(int careId) { this.careId = careId; }

    public String getDescription() { return description; }
    public void setDescription(String description) { this.description = description; }

    public String getStatus() { return status; }
    public void setStatus(String status) { this.status = status; }

    public String getDateAssigned() { return dateAssigned; }
    public void setDateAssigned(String dateAssigned) { this.dateAssigned = dateAssigned; }

    public String getResult() { return result; }
    public void setResult(String result) { this.result = result; }

    @Override
    public String toString() {
        return String.format("Task{id=%d, keeperId=%d, animalId=%d, status='%s', desc='%s'}",
                id, keeperId, animalId, status, description);
    }
}