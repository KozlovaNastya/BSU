package zoo.web.controllers;

import jakarta.servlet.http.HttpServletRequest;
import zoo.dao.KeeperDao;
import zoo.web.Controller;
import zoo.web.ViewResult;

public class KeepersController implements Controller {
    private final KeeperDao dao = new KeeperDao();
    @Override public ViewResult handle(HttpServletRequest request) {
        return ViewResult.view("keepers").add("keepers", dao.findAll())
                .add("message", request.getParameter("message"));
    }
}
