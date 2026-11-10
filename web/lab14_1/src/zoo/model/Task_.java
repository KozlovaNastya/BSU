package zoo.model;

import jakarta.persistence.metamodel.SingularAttribute;
import jakarta.persistence.metamodel.StaticMetamodel;

/** Static JPA metamodel for type-safe Criteria API queries. */
@StaticMetamodel(Task.class)
public abstract class Task_ {
    public static volatile SingularAttribute<Task, Integer> id;
    public static volatile SingularAttribute<Task, String> description;
    public static volatile SingularAttribute<Task, String> status;
    public static volatile SingularAttribute<Task, String> dateAssigned;
    public static volatile SingularAttribute<Task, String> result;
    public static volatile SingularAttribute<Task, Keeper> keeper;
    public static volatile SingularAttribute<Task, Animal> animal;
    public static volatile SingularAttribute<Task, Care> care;
}
