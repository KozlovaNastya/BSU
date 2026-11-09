# Library Service Client (Java, Spring Boot + Thymeleaf)

A web application for library users. It provides a book catalog with search functionality, book ordering, and order management (collect, return, extend, cancel, and edit orders).

The application also includes an administrator page (`/admin`) that allows librarians to view, add, edit, and delete books directly from the catalog table.

The client is a separate Spring Boot application. The browser opens its web pages, while the application communicates with the external Library Service via HTTP using the `X-Token` header. The user is identified by the `orders` method token.

## Running the Application

1. Open the project folder (the one containing `pom.xml`) in IntelliJ IDEA. Maven will automatically download the required dependencies.
2. Check the `library.api.base-url` property in `src/main/resources/application.properties`. Set it to the IP address of the computer running the Library Service and port `8081`. You can also change this address directly on the application's web page in the "Service Connection" section.
3. Run `LibraryClientApplication` by clicking the green run button next to the `main` method.

   Alternatively, if Maven is installed, execute the following command in the project directory:

   ```bash
   mvn spring-boot:run
   ```

4. Open the application in your browser:

   ```text
   http://<computer-IP>:3000
   ```

   Use HTTP, not HTTPS. The client listens on all network interfaces.

## Testing

1. Use the test tokens by clicking `Catalog: test-token-catalog` and `Reader 1: test-token-orders`.
2. Find a book in the catalog, click "Order", enter the reader's name, and confirm the order. The new order will appear in the "My Orders" section.
3. Select "Reader 2" to see a different set of orders. Different tokens provide access to different user orders.

## Project Structure

```text
api/LibraryApiClient      Handles API requests using RestClient
                          and provides readable error messages

config/ApiSettings        Stores the service URL
                          (can be changed without restarting)

dto/                      Data transfer objects:
                          BookDto, OrderDto, LibraryDto,
                          and request objects

web/HomeController        Handles the home page, tokens,
                          and service connection

web/OrderController       Handles orders, editing, status
                          changes, extensions, and deletion

web/AdminController       Manages the book catalog (CRUD)

templates/                HTML templates:
                          index, order-form, admin, fragments
```

