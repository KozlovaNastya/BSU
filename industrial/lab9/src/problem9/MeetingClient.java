package problem9;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.List;
import java.util.Scanner;

public class MeetingClient {
    private static final String SERVER_HOST = "10.41.130.164";
    private static final int RMI_PORT = 1098;
    
    private MeetingService meetingService;
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
            System.out.println("Подключение к RMI серверу " + SERVER_HOST + ":" + RMI_PORT);
            
            // Получаем реестр RMI
            Registry registry = LocateRegistry.getRegistry(SERVER_HOST, RMI_PORT);
            
            // Получаем ссылку на удаленный объект
            meetingService = (MeetingService) registry.lookup("MeetingService");
            
            System.out.println("✓ Успешно подключено к RMI серверу");
            return true;
            
        } catch (Exception e) {
            System.out.println("✗ Ошибка подключения к RMI серверу: " + e.getMessage());
            System.out.println("Убедитесь, что:");
            System.out.println("1. Сервер RMI запущен на " + SERVER_HOST + ":" + RMI_PORT);
            System.out.println("2. Служба 'MeetingService' зарегистрирована");
            return false;
        }
    }
    
    public void registerClient() {
        try {
            boolean success = meetingService.registerClient(clientName, clientData);
            if (success) {
                System.out.println("✓ Успешно зарегистрирован на сервере");
            } else {
                System.out.println("✗ Ошибка регистрации");
            }
        } catch (Exception e) {
            System.out.println("Ошибка при регистрации: " + e.getMessage());
        }
    }
    
    public void updateSchedule() {
        try {
            boolean success = meetingService.updateSchedule(clientName, clientData);
            if (success) {
                System.out.println("✓ Расписание успешно обновлено на сервере");
            } else {
                System.out.println("✗ Ошибка обновления расписания");
            }
        } catch (Exception e) {
            System.out.println("Ошибка при обновлении расписания: " + e.getMessage());
        }
    }
    
    public void requestMeeting() {
        try {
            // Получаем список доступных клиентов
            List<String> clients = meetingService.getAvailableClients(clientName);
            
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
            if (proposedTime == null) {
                System.out.println("Ошибка ввода времени");
                return;
            }
            
            // Отправляем запрос на встречу
            boolean success = meetingService.requestMeeting(clientName, targetClient, proposedTime);
            
            if (success) {
                System.out.println("✓ Запрос на встречу отправлен клиенту: " + targetClient);
            } else {
                System.out.println("✗ Не удалось отправить запрос на встречу");
            }
            
        } catch (Exception e) {
            System.out.println("Ошибка при запросе встречи: " + e.getMessage());
        }
    }
    
    public void confirmMeeting() {
        try {
            System.out.print("Введите время начала встречи для подтверждения: ");
            TimeSlot timeSlot = inputTimeSlot();
            
            if (timeSlot == null) {
                System.out.println("Ошибка ввода времени");
                return;
            }
            
            System.out.print("Подтвердить встречу? (yes/no): ");
            String response = scanner.nextLine();
            boolean confirmed = response.equalsIgnoreCase("yes");
            
            boolean success = meetingService.confirmMeeting(clientName, timeSlot, confirmed);
            
            if (success) {
                if (confirmed) {
                    System.out.println("✓ Встреча подтверждена");
                } else {
                    System.out.println("✓ Встреча отклонена");
                }
            } else {
                System.out.println("✗ Не удалось обработать подтверждение");
            }
            
        } catch (Exception e) {
            System.out.println("Ошибка при подтверждении встречи: " + e.getMessage());
        }
    }
    
    public void disconnect() {
        try {
            meetingService.disconnectClient(clientName);
            System.out.println("Отключено от сервера");
        } catch (Exception e) {
            System.out.println("Ошибка при отключении: " + e.getMessage());
        }
    }
    
    // Остальные методы остаются без изменений
    // (manageLocalSchedule, showLocalSchedule, addTimeSlot, removeTimeSlot, inputTimeSlot)
    
    private TimeSlot inputTimeSlot() {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd.MM.yyyy HH:mm");
        
        try {
            System.out.print("Введите дату и время начала (dd.MM.yyyy HH:mm): ");
            String startInput = scanner.nextLine();
            LocalDateTime startTime = LocalDateTime.parse(startInput, formatter);
            
            System.out.print("Введите дату и время окончания (dd.MM.yyyy HH:mm): ");
            String endInput = scanner.nextLine();
            LocalDateTime endTime = LocalDateTime.parse(endInput, formatter);
            
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
    
    public void startClient() {
        if (!connectToServer()) {
            return;
        }
        
        registerClient();
        
        while (true) {
            System.out.println("\n=== Клиент организации встреч (RMI) ===");
            System.out.println("1. Управление локальным расписанием");
            System.out.println("2. Обновить расписание на сервере");
            System.out.println("3. Запросить встречу с клиентом");
            System.out.println("4. Подтвердить встречу");
            System.out.println("5. Выйти");
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
                    confirmMeeting();
                    break;
                case 5:
                    disconnect();
                    return;
                default:
                    System.out.println("Неверный выбор");
            }
        }
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("=== Клиент организации встреч (RMI) ===");
        System.out.print("Введите ваше имя: ");
        String clientName = scanner.nextLine();
        
        MeetingClient client = new MeetingClient(clientName);
        client.startClient();
        
        scanner.close();
    }
}