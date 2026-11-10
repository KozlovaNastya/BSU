package zoo.web;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.thymeleaf.TemplateEngine;
import org.thymeleaf.context.WebContext;
import org.thymeleaf.web.servlet.JakartaServletWebApplication;

import zoo.web.controllers.*;

import java.io.IOException;
import java.time.Instant;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.util.LinkedHashMap;
import java.util.Map;

/** Central dispatcher: resolves the URL and delegates work to a dedicated controller. */
@WebServlet(name = "FrontController", urlPatterns = "/*")
public class FrontControllerServlet extends HttpServlet {
    private static final Logger logger = LoggerFactory.getLogger(FrontControllerServlet.class);
    private static final DateTimeFormatter DATE_FORMAT = DateTimeFormatter
            .ofPattern("dd.MM.yyyy HH:mm:ss").withZone(ZoneId.systemDefault());

    private TemplateEngine templateEngine;
    private Map<String, Controller> controllers;

    @Override
    public void init() throws ServletException {
        templateEngine = TemplateConfig.create(getServletContext());
        controllers = new LinkedHashMap<>();
        controllers.put("/", new DashboardController());
        controllers.put("/animals", new AnimalsController());
        controllers.put("/animals/create", new CreateAnimalController());
        controllers.put("/cares", new CaresController());
        controllers.put("/cares/create", new CreateCareController());
        controllers.put("/keepers", new KeepersController());
        controllers.put("/keepers/create", new CreateKeeperController());
        controllers.put("/tasks", new TasksController());
        controllers.put("/tasks/assign", new AssignTaskController());
        controllers.put("/tasks/complete", new CompleteTaskController());
        logger.info("Front controller initialized with {} routes", controllers.size());
    }

    @Override protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException { dispatch(request, response); }

    @Override protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException { dispatch(request, response); }

    private void dispatch(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        request.setCharacterEncoding("UTF-8");
        response.setCharacterEncoding("UTF-8");
        response.setContentType("text/html;charset=UTF-8");
        updateUserVisit(request, response);

        String path = request.getRequestURI().substring(request.getContextPath().length());
        if (path.isBlank()) path = "/";
        Controller controller = controllers.get(path);
        if (controller == null) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Page not found: " + path);
            return;
        }

        try {
            ViewResult result = controller.handle(request);
            if (result.getRedirect() != null) {
                response.sendRedirect(request.getContextPath() + result.getRedirect());
                return;
            }
            WebContext context = new WebContext(JakartaServletWebApplication.buildApplication(getServletContext()).buildExchange(request, response),request.getLocale());
            result.getModel().forEach(context::setVariable);
            context.setVariable("lastSession", request.getAttribute("lastSession"));
            context.setVariable("visitCount", request.getAttribute("visitCount"));
            context.setVariable("sessionRequestCount", request.getAttribute("sessionRequestCount"));
            context.setVariable("sessionId", request.getAttribute("sessionId"));
            context.setVariable("contextPath", request.getContextPath());
            templateEngine.process(result.getTemplate(), context, response.getWriter());
        } catch (Exception e) {
            logger.error("Request processing failed for {} {}", request.getMethod(), path, e);
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            WebContext context = new WebContext(JakartaServletWebApplication.buildApplication(getServletContext()).buildExchange(request, response),request.getLocale());
            context.setVariable("errorMessage", "The request could not be processed. Check the application log.");
            templateEngine.process("error", context, response.getWriter());
        }
    }

    /** Cookies persist the previous session time and total number of browser visits. */
    private void updateUserVisit(HttpServletRequest request, HttpServletResponse response) {
        HttpSession session = request.getSession(true);
        UserSession userSession = (UserSession) session.getAttribute("userSession");
        if (userSession == null) {
            userSession = new UserSession();
            session.setAttribute("userSession", userSession);
        }
        userSession.registerRequest();

        String oldTimestamp = readCookie(request, "lastSession");
        Integer visitsInSession = (Integer) session.getAttribute("visitCount");
        if (session.isNew()) {
            int visits = parseInt(readCookie(request, "visitCount"), 0) + 1;
            session.setAttribute("visitCount", visits);
            session.setAttribute("lastSessionDisplay", oldTimestamp == null ? "This is your first visit" :
                    DATE_FORMAT.format(Instant.ofEpochMilli(parseLong(oldTimestamp, 0L))));
            addCookie(response, "lastSession", Long.toString(System.currentTimeMillis()), request);
            addCookie(response, "visitCount", Integer.toString(visits), request);
            visitsInSession = visits;
        }

        request.setAttribute("lastSession", session.getAttribute("lastSessionDisplay"));
        request.setAttribute("visitCount", visitsInSession == null ? 1 : visitsInSession);
        request.setAttribute("sessionRequestCount", userSession.getRequestCount());
        request.setAttribute("sessionId", session.getId());
    }

    private void addCookie(HttpServletResponse response, String name, String value,
                           HttpServletRequest request) {
        Cookie cookie = new Cookie(name, value);
        cookie.setPath(request.getContextPath().isEmpty() ? "/" : request.getContextPath());
        cookie.setMaxAge(60 * 60 * 24 * 365);
        cookie.setHttpOnly(true);
        cookie.setSecure(request.isSecure());
        response.addCookie(cookie);
    }

    private String readCookie(HttpServletRequest request, String name) {
        Cookie[] cookies = request.getCookies();
        if (cookies != null) for (Cookie cookie : cookies)
            if (name.equals(cookie.getName())) return cookie.getValue();
        return null;
    }

    private int parseInt(String value, int fallback) {
        try { return value == null ? fallback : Integer.parseInt(value); }
        catch (NumberFormatException e) { return fallback; }
    }

    private long parseLong(String value, long fallback) {
        try { return value == null ? fallback : Long.parseLong(value); }
        catch (NumberFormatException e) { return fallback; }
    }
}
