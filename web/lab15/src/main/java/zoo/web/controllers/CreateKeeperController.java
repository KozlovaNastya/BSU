package zoo.web.controllers;

import jakarta.servlet.http.HttpServletRequest;
import zoo.dao.KeeperDao;
import zoo.model.Keeper;
import zoo.web.Controller;
import zoo.web.ViewResult;

public class CreateKeeperController implements Controller {
    private final KeeperDao dao = new KeeperDao();
    @Override public ViewResult handle(HttpServletRequest request) {
        String name = request.getParameter("name");
        String phone = request.getParameter("phone");
        if (name == null || name.isBlank())
            return ViewResult.redirect("/keepers?message=Keeper+name+is+required");
        Keeper keeper = new Keeper();
        keeper.setName(name.trim());
        keeper.setPhone(phone == null || phone.isBlank() ? null : phone.trim());
        boolean saved = dao.insert(keeper);
        return ViewResult.redirect("/keepers?message=" + (saved ? "Keeper+added" : "Could+not+add+keeper"));
    }
}
