package zoo.web.controllers;

import jakarta.servlet.http.HttpServletRequest;
import zoo.dao.AnimalDao;
import zoo.model.Animal;
import zoo.web.Controller;
import zoo.web.ViewResult;

public class CreateAnimalController implements Controller {
    private final AnimalDao dao = new AnimalDao();
    @Override public ViewResult handle(HttpServletRequest request) {
        String name = request.getParameter("name");
        String kind = request.getParameter("kind");
        int age = parseInt(request.getParameter("age"));
        double weight = parseDouble(request.getParameter("weight"));
        if (name == null || name.isBlank() || kind == null || kind.isBlank() || age < 0 || weight <= 0)
            return ViewResult.redirect("/animals?message=Check+the+animal+details");
        boolean saved = dao.insert(new Animal(name.trim(), kind.trim(), age, weight));
        return ViewResult.redirect("/animals?message=" + (saved ? "Animal+added" : "Could+not+add+animal"));
    }
    private int parseInt(String v) { try { return Integer.parseInt(v); } catch (Exception e) { return -1; } }
    private double parseDouble(String v) { try { return Double.parseDouble(v); } catch (Exception e) { return -1; } }
}
