package Program8;

import java.io.Serializable;
import java.time.LocalDateTime;

public class TimeSlot implements Serializable {
    private static final long serialVersionUID = 1L;
    
    private LocalDateTime startTime;
    private LocalDateTime endTime;
    
    public TimeSlot(LocalDateTime startTime, LocalDateTime endTime) {
        this.startTime = startTime;
        this.endTime = endTime;
    }
    
    // Геттеры и сеттеры
    public LocalDateTime getStartTime() {
        return startTime;
    }
    
    public void setStartTime(LocalDateTime startTime) {
        this.startTime = startTime;
    }
    
    public LocalDateTime getEndTime() {
        return endTime;
    }
    
    public void setEndTime(LocalDateTime endTime) {
        this.endTime = endTime;
    }
    
    @Override
    public String toString() {
        return startTime + " - " + endTime;
    }
}
