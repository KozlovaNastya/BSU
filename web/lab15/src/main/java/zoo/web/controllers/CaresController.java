package zoo.web.controllers;

import jakarta.servlet.http.HttpServletRequest;
import zoo.dao.CareDao;
import zoo.web.Controller;
import zoo.web.ViewResult;

public class CaresController implements Controller {
    private final CareDao dao = new CareDao();
    @Override public ViewResult handle(HttpServletRequest request) {
        return ViewResult.view("cares").add("cares", dao.findAll())
                .add("animals", new zoo.dao.AnimalDao().findAll())
                .add("message", request.getParameter("message"));
    }
}
