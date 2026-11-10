package zoo.web;

import jakarta.servlet.http.HttpServletRequest;

public interface Controller {
    ViewResult handle(HttpServletRequest request);
}
