package Program8;

import java.io.*;
import java.net.Socket;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.List;
import java.util.Scanner;

public class MeetingClient {
    private static final String SERVER_HOST = "10.41.130.164";
    private static final int SERVER_PORT = 12345;
    
    private Socket socket;
    private ObjectOutputStream output;
    private ObjectInputStream input;
    private String clientName;
    private ClientData clientData;
    private Scanner scanner;
    
    public MeetingClient(String clientName) {
        this.clientName = clientName;
        this.clientData = new ClientData(clientName);
        this.scanner = new Scanner(System.in);
    }
    
    public boolean connectToServer() {
        try {
            System.out.println("Попытка подключения к " + SERVER_HOST + ":" + SERVER_PORT);
            socket = new Socket(SERVER_HOST, SERVER_PORT);
            output = new ObjectOutputStream(socket.getOutputStream());
            input = new ObjectInputStream(socket.getInputStream());
            System.out.println("Успешно подключено к серверу");
            return true;
        } catch (IOException e) {
            System.out.println("Ошибка подключения к серверу: " + e.getMessage());
            System.out.println("Убедитесь, что:");
            System.out.println("1. Сервер запущен на " + SERVER_HOST + ":" + SERVER_PORT);
            System.out.println("2. Фаервол не блокирует порт " + SERVER_PORT);
            System.out.println("3. Для разных компьютеров используйте реальный IP сервера");
            return false;
        }
    }
    
    public void disconnect() {
        try {
            if (output != null) output.close();
            if (input != null) input.close();
            if (socket != null) socket.close();
            System.out.println("Отключено от сервера");
        } catch (IOException e) {
            System.out.println("Ошибка при отключении: " + e.getMessage());
        }
    }
    
    public void registerClient() {
        try {
            ProtocolMessage message = new ProtocolMessage(
                ProtocolMessage.MessageType.REGISTER, 
                clientName, 
                clientData
            );
            output.writeObject(message);
            output.flush();
            
            ProtocolResponse response = receiveResponse();
            if (response.isSuccess()) {
                System.out.println("Успешно зарегистрирован на сервере");
            } else {
                System.out.println("Ошибка регистрации: " + response.getMessage());
            }
        } catch (IOException e) {
            System.out.println("Ошибка при регистрации: " + e.getMessage());
        }
    }
    
    public void updateSchedule() {
        try {
            ProtocolMessage message = new ProtocolMessage(
                ProtocolMessage.MessageType.UPDATE_SCHEDULE, 
                clientName, 
                clientData
            );
            output.writeObject(message);
            output.flush();
            
            ProtocolResponse response = receiveResponse();
            if (response.isSuccess()) {
                System.out.println("Расписание успешно обновлено на сервере");
            } else {
                System.out.println("Ошибка обновления расписания: " + response.getMessage());
            }
        } catch (IOException e) {
            System.out.println("Ошибка при обновлении расписания: " + e.getMessage());
        }
    }
    
    public void requestMeeting() {
        try {
            // Получаем список доступных клиентов
            List<String> clients = getAvailableClients();
            if (clients.isEmpty()) {
                System.out.println("Нет доступных клиентов для встречи");
                return;
            }
            
            System.out.println("Доступные клиенты:");
            for (int i = 0; i < clients.size(); i++) {
                System.out.println((i + 1) + ". " + clients.get(i));
            }
            
            System.out.print("Выберите номер клиента: ");
            int choice = scanner.nextInt();
            scanner.nextLine(); // consume newline
            
            if (choice < 1 || choice > clients.size()) {
                System.out.println("Неверный выбор");
                return;
            }
            
            String targetClient = clients.get(choice - 1);
            
            // Запрашиваем предложенное время
            TimeSlot proposedTime = inputTimeSlot();
            
            ProtocolMessage message = new ProtocolMessage(
                ProtocolMessage.MessageType.REQUEST_MEETING, 
                clientName
            );
            message.setTargetClient(targetClient);
            message.setProposedTime(proposedTime);
            
            output.writeObject(message);
            output.flush();
            
            ProtocolResponse response = receiveResponse();
            if (response.isSuccess()) {
                System.out.println("Запрос на встречу отправлен: " + response.getMessage());
            } else {
                System.out.println("Ошибка запроса встречи: " + response.getMessage());
            }
            
        } catch (Exception e) {
            System.out.println("Ошибка при запросе встречи: " + e.getMessage());
        }
    }
    
    private List<String> getAvailableClients() {
        try {
            ProtocolMessage message = new ProtocolMessage(
                ProtocolMessage.MessageType.GET_CLIENTS, 
                clientName
            );
            output.writeObject(message);
            output.flush();
            
            ProtocolResponse response = receiveResponse();
            if (response.isSuccess() && response.getAvailableClients() != null) {
                return response.getAvailableClients();
            }
        } catch (IOException e) {
            System.out.println("Ошибка при получении списка клиентов: " + e.getMessage());
        }
        return List.of();
    }
    
    private ProtocolResponse receiveResponse() {
        try {
            return (ProtocolResponse) input.readObject();
        } catch (IOException | ClassNotFoundException e) {
            System.out.println("Ошибка при получении ответа от сервера: " + e.getMessage());
            return new ProtocolResponse(false, "Ошибка связи с сервером");
        }
    }
    
    public void manageLocalSchedule() {
        while (true) {
            System.out.println("\n=== Управление локальным расписанием ===");
            System.out.println("1. Показать свободное время");
            System.out.println("2. Добавить свободное время");
            System.out.println("3. Удалить свободное время");
            System.out.println("4. Назад в главное меню");
            System.out.print("Выберите действие: ");
            
            int choice = scanner.nextInt();
            scanner.nextLine(); // consume newline
            
            switch (choice) {
                case 1:
                    showLocalSchedule();
                    break;
                case 2:
                    addTimeSlot();
                    break;
                case 3:
                    removeTimeSlot();
                    break;
                case 4:
                    return;
                default:
                    System.out.println("Неверный выбор");
            }
        }
    }
    
    private void showLocalSchedule() {
        List<TimeSlot> slots = clientData.getFreeTimeSlots();
        if (slots.isEmpty()) {
            System.out.println("Свободное время не добавлено");
            return;
        }
        
        System.out.println("Ваше свободное время:");
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd.MM.yyyy HH:mm");
        for (int i = 0; i < slots.size(); i++) {
            TimeSlot slot = slots.get(i);
            System.out.println((i + 1) + ". " + 
                slot.getStartTime().format(formatter) + " - " + 
                slot.getEndTime().format(formatter));
        }
    }
    
    private void addTimeSlot() {
        TimeSlot timeSlot = inputTimeSlot();
        if (timeSlot != null) {
            clientData.addTimeSlot(timeSlot);
            System.out.println("Временной интервал добавлен");
        } else {
            System.out.println("Не удалось добавить временной интервал");
        }
    }
    
    private void removeTimeSlot() {
        showLocalSchedule();
        List<TimeSlot> slots = clientData.getFreeTimeSlots();
        if (slots.isEmpty()) {
            return;
        }
        
        System.out.print("Выберите номер интервала для удаления: ");
        int choice = scanner.nextInt();
        scanner.nextLine(); // consume newline
        
        if (choice < 1 || choice > slots.size()) {
            System.out.println("Неверный выбор");
            return;
        }
        
        TimeSlot slotToRemove = slots.get(choice - 1);
        clientData.removeTimeSlot(slotToRemove);
        System.out.println("Временной интервал удален");
    }
    
    private TimeSlot inputTimeSlot() {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd.MM.yyyy HH:mm");
        
        try {
            System.out.print("Введите дату и время начала (dd.MM.yyyy HH:mm): ");
            String startInput = scanner.nextLine();
            LocalDateTime startTime = LocalDateTime.parse(startInput, formatter);
            
            System.out.print("Введите дату и время окончания (dd.MM.yyyy HH:mm): ");
            String endInput = scanner.nextLine();
            LocalDateTime endTime = LocalDateTime.parse(endInput, formatter);
            
            // Проверка, что конец после начала
            if (endTime.isBefore(startTime) || endTime.isEqual(startTime)) {
                System.out.println("Ошибка: время окончания должно быть позже времени начала");
                return null;
            }
            
            return new TimeSlot(startTime, endTime);
        } catch (DateTimeParseException e) {
            System.out.println("Ошибка формата даты. Используйте формат: дд.мм.гггг чч:мм");
            System.out.println("Пример: 25.12.2024 14:30");
            return null;
        }
    }
    
    public void startClient() {
        if (!connectToServer()) {
            return;
        }
        
        registerClient();
        
        while (true) {
            System.out.println("\n=== Клиент организации встреч ===");
            System.out.println("1. Управление локальным расписанием");
            System.out.println("2. Обновить расписание на сервере");
            System.out.println("3. Запросить встречу с клиентом");
            System.out.println("4. Выйти");
            System.out.print("Выберите действие: ");
            
            int choice = scanner.nextInt();
            scanner.nextLine(); // consume newline
            
            switch (choice) {
                case 1:
                    manageLocalSchedule();
                    break;
                case 2:
                    updateSchedule();
                    break;
                case 3:
                    requestMeeting();
                    break;
                case 4:
                    disconnect();
                    return;
                default:
                    System.out.println("Неверный выбор");
            }
        }
    }
}
