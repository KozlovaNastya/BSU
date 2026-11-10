package zoo.model;

import jakarta.persistence.metamodel.ListAttribute;
import jakarta.persistence.metamodel.SingularAttribute;
import jakarta.persistence.metamodel.StaticMetamodel;

/** Static JPA metamodel for type-safe Criteria API queries. */
@StaticMetamodel(Keeper.class)
public abstract class Keeper_ {
    public static volatile SingularAttribute<Keeper, Integer> id;
    public static volatile SingularAttribute<Keeper, String> name;
    public static volatile SingularAttribute<Keeper, String> phone;
    public static volatile ListAttribute<Keeper, Task> tasks;
}
