package zoo.model;

import jakarta.persistence.metamodel.SingularAttribute;
import jakarta.persistence.metamodel.StaticMetamodel;

/** Static JPA metamodel for type-safe Criteria API queries. */
@StaticMetamodel(Care.class)
public abstract class Care_ {
    public static volatile SingularAttribute<Care, Integer> id;
    public static volatile SingularAttribute<Care, String> description;
    public static volatile SingularAttribute<Care, String> type;
    public static volatile SingularAttribute<Care, Animal> animal;
}
