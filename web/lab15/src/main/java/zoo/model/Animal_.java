package zoo.model;

import jakarta.persistence.metamodel.ListAttribute;
import jakarta.persistence.metamodel.SingularAttribute;
import jakarta.persistence.metamodel.StaticMetamodel;

/** Static JPA metamodel for type-safe Criteria API queries. */
@StaticMetamodel(Animal.class)
public abstract class Animal_ {
    public static volatile SingularAttribute<Animal, Integer> id;
    public static volatile SingularAttribute<Animal, String> name;
    public static volatile SingularAttribute<Animal, String> kind;
    public static volatile SingularAttribute<Animal, Integer> age;
    public static volatile SingularAttribute<Animal, Double> weight;
    public static volatile ListAttribute<Animal, Care> cares;
}
