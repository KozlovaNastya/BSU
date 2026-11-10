package zoo.web.controllers;

import jakarta.servlet.http.HttpServletRequest;
import zoo.dao.AnimalDao;
import zoo.dao.KeeperDao;
import zoo.web.Controller;
import zoo.web.ViewResult;

public class DashboardController implements Controller {
    private final AnimalDao animals = new AnimalDao();
    private final KeeperDao keepers = new KeeperDao();

    @Override
    public ViewResult handle(HttpServletRequest request) {
        return ViewResult.view("index")
                .add("animalCount", animals.findAll().size())
                .add("keeperCount", keepers.findAll().size());
    }
}
