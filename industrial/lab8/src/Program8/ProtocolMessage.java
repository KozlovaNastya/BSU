package Program8;

import java.io.Serializable;
import java.util.List;

public class ProtocolMessage implements Serializable {
    private static final long serialVersionUID = 1L;
    
    public enum MessageType {
        REGISTER,           // Регистрация клиента
        UPDATE_SCHEDULE,    // Обновление расписания
        REQUEST_MEETING,    // Запрос на встречу
        CONFIRM_MEETING,    // Подтверждение встречи
        GET_CLIENTS,        // Получить список клиентов
        MEETING_RESPONSE,   // Ответ на запрос встречи
        ERROR               // Ошибка
    }
    
    private MessageType type;
    private String clientName;
    private ClientData clientData;
    private String targetClient;
    private TimeSlot proposedTime;
    private List<String> availableClients;
    private String message;
    private boolean confirmed;
    
    // Конструкторы для разных типов сообщений
    public ProtocolMessage(MessageType type, String clientName) {
        this.type = type;
        this.clientName = clientName;
    }
    
    public ProtocolMessage(MessageType type, String clientName, ClientData clientData) {
        this.type = type;
        this.clientName = clientName;
        this.clientData = clientData;
    }
    
    // Геттеры и сеттеры
    public MessageType getType() {
        return type;
    }
    
    public void setType(MessageType type) {
        this.type = type;
    }
    
    public String getClientName() {
        return clientName;
    }
    
    public void setClientName(String clientName) {
        this.clientName = clientName;
    }
    
    public ClientData getClientData() {
        return clientData;
    }
    
    public void setClientData(ClientData clientData) {
        this.clientData = clientData;
    }
    
    public String getTargetClient() {
        return targetClient;
    }
    
    public void setTargetClient(String targetClient) {
        this.targetClient = targetClient;
    }
    
    public TimeSlot getProposedTime() {
        return proposedTime;
    }
    
    public void setProposedTime(TimeSlot proposedTime) {
        this.proposedTime = proposedTime;
    }
    
    public List<String> getAvailableClients() {
        return availableClients;
    }
    
    public void setAvailableClients(List<String> availableClients) {
        this.availableClients = availableClients;
    }
    
    public String getMessage() {
        return message;
    }
    
    public void setMessage(String message) {
        this.message = message;
    }
    
    public boolean isConfirmed() {
        return confirmed;
    }
    
    public void setConfirmed(boolean confirmed) {
        this.confirmed = confirmed;
    }
    
    @Override
    public String toString() {
        return "ProtocolMessage{" +
                "type=" + type +
                ", clientName='" + clientName + '\'' +
                ", message='" + message + '\'' +
                '}';
    }
}
