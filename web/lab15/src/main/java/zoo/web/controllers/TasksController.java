package zoo.web.controllers;

import jakarta.servlet.http.HttpServletRequest;
import zoo.dao.AnimalDao;
import zoo.dao.CareDao;
import zoo.dao.KeeperDao;
import zoo.dao.TaskDao;
import zoo.model.Keeper;
import zoo.web.Controller;
import zoo.web.ViewResult;

import java.util.List;

public class TasksController implements Controller {
    private final TaskDao tasks = new TaskDao();
    private final KeeperDao keepers = new KeeperDao();
    private final AnimalDao animals = new AnimalDao();
    private final CareDao cares = new CareDao();

    @Override
    public ViewResult handle(HttpServletRequest request) {
        List<Keeper> allKeepers = keepers.findAll();
        int keeperId = parseInt(request.getParameter("keeperId"),
                allKeepers.isEmpty() ? -1 : allKeepers.get(0).getId());
        String status = request.getParameter("status");
        return ViewResult.view("tasks")
                .add("keepers", allKeepers)
                .add("selectedKeeperId", keeperId)
                .add("selectedStatus", status == null ? "" : status)
                .add("tasks", keeperId > 0 ? tasks.findByKeeperAndStatus(keeperId, status) : List.of())
                .add("animals", animals.findAll())
                .add("cares", cares.findAll())
                .add("message", request.getParameter("message"));
    }

    private int parseInt(String value, int fallback) {
        try { return value == null ? fallback : Integer.parseInt(value); }
        catch (NumberFormatException e) { return fallback; }
    }
}
