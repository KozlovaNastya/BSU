package zoo.web;

import jakarta.servlet.ServletContextEvent;
import jakarta.servlet.ServletContextListener;
import jakarta.servlet.annotation.WebListener;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import zoo.DatabaseInitializer;
import zoo.JpaManager;

@WebListener
public class WebApplicationListener implements ServletContextListener {
    private static final Logger logger = LoggerFactory.getLogger(WebApplicationListener.class);

    @Override
    public void contextInitialized(ServletContextEvent event) {
        logger.info("Starting ZooWeb");
        DatabaseInitializer.initialize();
    }

    @Override
    public void contextDestroyed(ServletContextEvent event) {
        JpaManager.close();
        logger.info("ZooWeb stopped");
    }
}
