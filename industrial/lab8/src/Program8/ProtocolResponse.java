package Program8;

import java.io.Serializable;
import java.util.List;

public class ProtocolResponse implements Serializable {
    private static final long serialVersionUID = 1L;
    
    private boolean success;
    private String message;
    private List<String> availableClients;
    private TimeSlot proposedMeetingTime;
    private String meetingWith;
    
    public ProtocolResponse(boolean success, String message) {
        this.success = success;
        this.message = message;
    }
    
    // Геттеры и сеттеры
    public boolean isSuccess() {
        return success;
    }
    
    public void setSuccess(boolean success) {
        this.success = success;
    }
    
    public String getMessage() {
        return message;
    }
    
    public void setMessage(String message) {
        this.message = message;
    }
    
    public List<String> getAvailableClients() {
        return availableClients;
    }
    
    public void setAvailableClients(List<String> availableClients) {
        this.availableClients = availableClients;
    }
    
    public TimeSlot getProposedMeetingTime() {
        return proposedMeetingTime;
    }
    
    public void setProposedMeetingTime(TimeSlot proposedMeetingTime) {
        this.proposedMeetingTime = proposedMeetingTime;
    }
    
    public String getMeetingWith() {
        return meetingWith;
    }
    
    public void setMeetingWith(String meetingWith) {
        this.meetingWith = meetingWith;
    }
    
    @Override
    public String toString() {
        return "ProtocolResponse{" +
                "success=" + success +
                ", message='" + message + '\'' +
                '}';
    }
}