package zoo.web;

import java.util.LinkedHashMap;
import java.util.Map;

public final class ViewResult {
    private final String template;
    private final String redirect;
    private final Map<String, Object> model = new LinkedHashMap<>();

    private ViewResult(String template, String redirect) {
        this.template = template;
        this.redirect = redirect;
    }

    public static ViewResult view(String template) { return new ViewResult(template, null); }
    public static ViewResult redirect(String path) { return new ViewResult(null, path); }
    public ViewResult add(String key, Object value) { model.put(key, value); return this; }
    public String getTemplate() { return template; }
    public String getRedirect() { return redirect; }
    public Map<String, Object> getModel() { return model; }
}
