package zoo.web.controllers;

import jakarta.servlet.http.HttpServletRequest;
import zoo.dao.AnimalDao;
import zoo.web.Controller;
import zoo.web.ViewResult;

public class AnimalsController implements Controller {
    private final AnimalDao dao = new AnimalDao();

    @Override
    public ViewResult handle(HttpServletRequest request) {
        String kind = request.getParameter("kind");
        Integer minAge = parseOptionalInt(request.getParameter("minAge"));
        Integer maxAge = parseOptionalInt(request.getParameter("maxAge"));
        boolean filtering = (kind != null && !kind.isBlank()) || minAge != null || maxAge != null;
        return ViewResult.view("animals")
                .add("animals", filtering ? dao.search(kind, minAge, maxAge) : dao.findAll())
                .add("kind", kind == null ? "" : kind)
                .add("minAge", minAge == null ? "" : minAge)
                .add("maxAge", maxAge == null ? "" : maxAge)
                .add("message", request.getParameter("message"));
    }

    private Integer parseOptionalInt(String value) {
        try { return value == null || value.isBlank() ? null : Integer.valueOf(value); }
        catch (NumberFormatException e) { return null; }
    }
}
