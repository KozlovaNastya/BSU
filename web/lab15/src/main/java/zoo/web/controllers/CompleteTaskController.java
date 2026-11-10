package zoo.web.controllers;

import jakarta.servlet.http.HttpServletRequest;
import zoo.dao.TaskDao;
import zoo.web.Controller;
import zoo.web.ViewResult;

public class CompleteTaskController implements Controller {
    private final TaskDao dao = new TaskDao();
    @Override
    public ViewResult handle(HttpServletRequest request) {
        int taskId = parseInt(request.getParameter("taskId"));
        int keeperId = parseInt(request.getParameter("keeperId"));
        String result = request.getParameter("result");
        if (taskId <= 0 || result == null || result.isBlank())
            return ViewResult.redirect("/tasks?keeperId=" + keeperId + "&message=Enter+the+completion+result");
        boolean updated = dao.updateResult(taskId, result.trim());
        return ViewResult.redirect("/tasks?keeperId=" + keeperId + "&message=" +
                (updated ? "Task+completed" : "Could+not+update+task"));
    }
    private int parseInt(String value) {
        try { return value == null ? -1 : Integer.parseInt(value); }
        catch (NumberFormatException e) { return -1; }
    }
}
