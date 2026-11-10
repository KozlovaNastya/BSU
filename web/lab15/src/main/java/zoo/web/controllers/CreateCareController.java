package zoo.web.controllers;

import jakarta.servlet.http.HttpServletRequest;
import zoo.dao.AnimalDao;
import zoo.dao.CareDao;
import zoo.model.Animal;
import zoo.model.Care;
import zoo.web.Controller;
import zoo.web.ViewResult;

public class CreateCareController implements Controller {
    private final CareDao dao = new CareDao();
    private final AnimalDao animals = new AnimalDao();
    @Override public ViewResult handle(HttpServletRequest request) {
        int animalId;
        try { animalId = Integer.parseInt(request.getParameter("animalId")); }
        catch (Exception e) { animalId = -1; }
        String description = request.getParameter("description");
        String type = request.getParameter("type");
        Animal animal = animals.findById(animalId);
        if (animal == null || description == null || description.isBlank() || type == null || type.isBlank())
            return ViewResult.redirect("/cares?message=Check+the+care+activity+details");
        boolean saved = dao.insert(new Care(description.trim(), type.trim(), animal));
        return ViewResult.redirect("/cares?message=" + (saved ? "Care+activity+added" : "Could+not+add+care+activity"));
    }
}
