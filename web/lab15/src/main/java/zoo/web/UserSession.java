package zoo.web;

import java.io.Serializable;
import java.time.Instant;

/** Per-user information kept by the HTTP session. */
public class UserSession implements Serializable {
    private final Instant createdAt = Instant.now();
    private int requestCount;

    public Instant getCreatedAt() { return createdAt; }
    public int getRequestCount() { return requestCount; }
    public void registerRequest() { requestCount++; }
}
