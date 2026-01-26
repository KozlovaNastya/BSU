package Program5;

import java.util.*;

public class TriangleTest {

	public static void main(String[] args) {
		Triangle tr1 = new RavnTriangle(1, 2, 30, "red", "blue");
		tr1.print();
		double area1 = tr1.area();
		double per1 = tr1.perimeter();
		System.out.printf("Area of tr1 : %.2f%n", area1);
		System.out.printf("Perimeter of tr1 : %.2f%n", per1);
		
		Triangle tr2 = new RavnTriangle(4, 60, "green", "pink");
		tr2.print();
		
		List<RavnTriangle> triangles = Arrays.asList(
	            new RavnTriangle(5, 6, 30, "red", "blue"),
	            new RavnTriangle(3, 4, 45, "green", "yellow"),
	            new RavnTriangle(7, 7, 60, "black", "white")
	        );
		System.out.println("\n Sourse triangles : ");
		triangles.forEach(t -> {
			t.print();
			System.out.printf("Area: %.2f; Perimeter: %.2f%n", t.area(), t.perimeter());
		});
		
		Collections.sort(triangles);
        System.out.println("\n BY .sort() :");
        triangles.forEach(t -> System.out.printf("%.2f%n", t.area()));
        
        System.out.println("\n BY sort(RavnTriangle.BY_PERIMETER) :");
        triangles.sort(RavnTriangle.BY_PERIMETER);
        triangles.forEach(t -> System.out.printf("%.2f%n", t.perimeter()));
        
        System.out.println("\n BY .sort(BY_CONTUR) :");
        triangles.sort(RavnTriangle.BY_CONTUR);
        triangles.forEach(t -> System.out.println(t.getContur()));
        
        System.out.println("\n BY .sort(BY_ZALIVKA) :");
        triangles.sort(RavnTriangle.BY_ZALIVKA);
        triangles.forEach(t -> System.out.println(t.getZalivka()));
        
        System.out.println("\nBY sort(RavnTriangle.BY_SIDE_A) :");
        triangles.sort(RavnTriangle.BY_SIDE_A);
        triangles.forEach(t -> System.out.println(t.getA()));
        
        System.out.println("\nBY sort(RavnTriangle.BY_SIDE_B) :");
        triangles.sort(RavnTriangle.BY_SIDE_B);
        triangles.forEach(t -> System.out.println(t.getB()));
        
        System.out.println("\nBY sort(RavnTriangle.BY_ANGLE) :");
        triangles.sort(RavnTriangle.BY_ANGLE);
        triangles.forEach(t -> System.out.println(t.getEdge()));
        
        System.out.println("\n BY sort(RavnTriangle.BY_AREA.reversed() :");
        triangles.sort(RavnTriangle.BY_AREA.reversed());
        triangles.forEach(t -> System.out.printf("%.2f%n", t.area()));
        
        System.out.println("\n Testing Iterable :");
        RavnTriangle testTriangle = new RavnTriangle(5, 6, 30, "red", "blue");
        int fieldIndex = 0;
        for (Object field : testTriangle) {
            System.out.println("Field " + fieldIndex++ + ": " + field);
        }

        System.out.println("\n Testing Indexer :");
        for (int i = 0; i < testTriangle.getFieldCount(); i++) {
            System.out.println("Field " + i + ": " + testTriangle.getField(i));
        }

        System.out.println("\n Testing toString() :");
        String saved = testTriangle.toString();
        System.out.println(saved);
        System.out.println("\n String Constructor :");
        RavnTriangle restored = new RavnTriangle(saved);
        restored.print();
	}
	
}
