package problem9;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;

public interface MeetingService extends Remote {
    
    // Регистрация клиента
    boolean registerClient(String clientName, ClientData clientData) throws RemoteException;
    
    // Обновление расписания
    boolean updateSchedule(String clientName, ClientData clientData) throws RemoteException;
    
    // Получение списка доступных клиентов
    List<String> getAvailableClients(String currentClient) throws RemoteException;
    
    // Запрос на организацию встречи
    boolean requestMeeting(String fromClient, String toClient, TimeSlot proposedTime) throws RemoteException;
    
    // Подтверждение встречи
    boolean confirmMeeting(String clientName, TimeSlot timeSlot, boolean confirmed) throws RemoteException;
    
    // Отключение клиента
    void disconnectClient(String clientName) throws RemoteException;
}