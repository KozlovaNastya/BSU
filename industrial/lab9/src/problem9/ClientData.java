package problem9;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class ClientData implements Serializable {
    private static final long serialVersionUID = 1L;
    
    private String clientName;
    private List<TimeSlot> freeTimeSlots;
    
    public ClientData(String clientName) {
        this.clientName = clientName;
        this.freeTimeSlots = new ArrayList<>();
    }
    
    // Геттеры и сеттеры
    public String getClientName() {
        return clientName;
    }
    
    public void setClientName(String clientName) {
        this.clientName = clientName;
    }
    
    public List<TimeSlot> getFreeTimeSlots() {
        return freeTimeSlots;
    }
    
    public void setFreeTimeSlots(List<TimeSlot> freeTimeSlots) {
        this.freeTimeSlots = freeTimeSlots;
    }
    
    public void addTimeSlot(TimeSlot timeSlot) {
        this.freeTimeSlots.add(timeSlot);
    }
    
    public void removeTimeSlot(TimeSlot timeSlot) {
        this.freeTimeSlots.remove(timeSlot);
    }
    
    @Override
    public String toString() {
        return "ClientData{" +
                "clientName='" + clientName + '\'' +
                ", freeTimeSlots=" + freeTimeSlots +
                '}';
    }
}