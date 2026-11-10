package zoo.web.controllers;

import jakarta.servlet.http.HttpServletRequest;
import zoo.dao.AnimalDao;
import zoo.dao.CareDao;
import zoo.dao.KeeperDao;
import zoo.dao.TaskDao;
import zoo.model.Animal;
import zoo.model.Care;
import zoo.model.Keeper;
import zoo.model.Task;
import zoo.web.Controller;
import zoo.web.ViewResult;

import java.time.LocalDate;

public class AssignTaskController implements Controller {
    private final TaskDao tasks = new TaskDao();
    private final KeeperDao keepers = new KeeperDao();
    private final AnimalDao animals = new AnimalDao();
    private final CareDao cares = new CareDao();

    @Override
    public ViewResult handle(HttpServletRequest request) {
        int keeperId = parseInt(request.getParameter("keeperId"));
        int animalId = parseInt(request.getParameter("animalId"));
        int careId = parseInt(request.getParameter("careId"));
        String description = request.getParameter("description");

        if (keeperId <= 0 || animalId <= 0 || careId <= 0 || description == null || description.isBlank())
            return ViewResult.redirect("/tasks?message=Please+fill+in+all+fields");

        Keeper keeper = keepers.findAll().stream().filter(k -> k.getId() == keeperId).findFirst().orElse(null);
        Animal animal = animals.findById(animalId);
        Care care = cares.findById(careId);
        if (keeper == null || animal == null || care == null || care.getAnimal() == null
                || care.getAnimal().getId() != animalId)
            return ViewResult.redirect("/tasks?message=Choose+a+care+activity+for+the+selected+animal");

        Task task = new Task();
        task.setKeeper(keeper);
        task.setAnimal(animal);
        task.setCare(care);
        task.setDescription(description.trim());
        task.setStatus("assigned");
        task.setDateAssigned(LocalDate.now().toString());
        boolean saved = tasks.insert(task);
        return ViewResult.redirect("/tasks?keeperId=" + keeperId + "&message=" +
                (saved ? "Task+assigned" : "Could+not+assign+task"));
    }

    private int parseInt(String value) {
        try { return value == null ? -1 : Integer.parseInt(value); }
        catch (NumberFormatException e) { return -1; }
    }
}
