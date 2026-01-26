package problem9;

import java.util.Scanner;

public class ClientMain {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("=== Клиент организации встреч ===");
        System.out.print("Введите ваше имя: ");
        String clientName = scanner.nextLine();
        
        MeetingClient client = new MeetingClient(clientName);
        client.startClient();
        
        scanner.close();
    }
}