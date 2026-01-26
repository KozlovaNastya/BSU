package Program5;

import java.util.*;

class RavnTriangle extends Triangle implements Iterable<Object> {
	private String contur;
	private String zalivka;
	
	public RavnTriangle(double a, double b, int edge, String contur, String zalivka) {
		super(a, b, edge);
		
	    if (contur == null || contur.trim().isEmpty()) {
	        throw new IllegalArgumentException("Contur == null or empty!!!");
	    }
	    if (zalivka == null || zalivka.trim().isEmpty()) {
	        throw new IllegalArgumentException("Zalivka == null or empty!!!");
	    }
		
		this.contur = contur.trim();
		this.zalivka = zalivka.trim();
	}
	
	public RavnTriangle(double a, int edge, String contur, String zalivka) {
		this(a, a, edge, contur, zalivka);
	}
	
	public RavnTriangle(String data) {
	    this(1, 1, 1, "temp", "temp");
	    
	    try {
	        String[] parts = data.split("; ");
	        
	        if (parts.length != 5 || !parts[0].startsWith("RavnTriangle : a = ")) {
	            throw new IllegalArgumentException("Incorrect format of line");
	        }
	        
	        java.text.NumberFormat format = java.text.NumberFormat.getInstance(java.util.Locale.FRENCH);
	        
	        double parsedA = format.parse(parts[0].replace("RavnTriangle : a = ", "")).doubleValue();
	        double parsedB = format.parse(parts[1].replace("b = ", "")).doubleValue();
	        int parsedEdge = Integer.parseInt(parts[2].replace("edge = ", ""));
	        String parsedZalivka = parts[3].replace("zalivka = ", "");
	        String parsedContur = parts[4].replace("contur = ", "");
	        
	        this.a = parsedA;
	        this.b = parsedB;
	        this.edge = parsedEdge;
	        this.contur = parsedContur;
	        this.zalivka = parsedZalivka;
	        
	        if (a <= 0 || b <= 0 || edge <= 0 || edge >= 180) {
	            throw new IllegalArgumentException("Incorrect triangle parameters: a=" + a + ", b=" + b + ", edge=" + edge);
	        }
	        if (contur == null || contur.trim().isEmpty() || zalivka == null || zalivka.trim().isEmpty()) {
	            throw new IllegalArgumentException("Colors cannot be empty");
	        }
	        
	    } catch (Exception e) {
	        throw new IllegalArgumentException("Error parsing: " + e.getMessage());
	    }
	}
	
	public String getContur() {
	    return contur;
	}

	public String getZalivka() {
	    return zalivka;
	}
	
	@Override
	public double area() {
		return 0.5 * getA() * getB() * Math.sin(Math.toRadians(getEdge()));
	}
	
	@Override
    public double perimeter() {
		double c = Math.sqrt(getA()*getA() + getB()*getB() - 2*getA()*getB()*Math.cos(Math.toRadians(getEdge())));
		return getA() + getB() + c;
	}
	
	public void print() {
		super.print();
		System.out.println("; zalivka = " + zalivka + "; contur = " + contur);
	}
	
	public static final Comparator<RavnTriangle> BY_AREA =
	        Comparator.comparingDouble(RavnTriangle::area);
	    
	public static final Comparator<RavnTriangle> BY_PERIMETER =
	        Comparator.comparingDouble(RavnTriangle::perimeter);
	    
	public static final Comparator<RavnTriangle> BY_CONTUR =
	        Comparator.comparing(RavnTriangle::getContur);
	    
	public static final Comparator<RavnTriangle> BY_ZALIVKA =
	        Comparator.comparing(RavnTriangle::getZalivka);
	    
	public static final Comparator<RavnTriangle> BY_SIDE_A =
	        Comparator.comparingDouble(RavnTriangle::getA);
	    
	public static final Comparator<RavnTriangle> BY_SIDE_B =
	        Comparator.comparingDouble(RavnTriangle::getB);
	    
	public static final Comparator<RavnTriangle> BY_ANGLE =
	        Comparator.comparingInt(RavnTriangle::getEdge);
	
	@Override
	public String toString() {
	    return String.format("RavnTriangle : a = %.2f; b = %.2f; edge = %d; zalivka = %s; contur = %s", 
	        getA(),
	        getB(),
	        getEdge(),
	        zalivka,
	        contur
	    );
	}
	
	@Override
    public Iterator<Object> iterator() {
        List<Object> fields = Arrays.asList(a, b, edge, contur, zalivka);
        return fields.iterator();
    }
	
	public Object getField(int index) {
	    switch (index) {
	        case 0: return a;
	        case 1: return b;
	        case 2: return edge;
	        case 3: return contur;
	        case 4: return zalivka;
	        default: throw new IndexOutOfBoundsException("index must be 0-4");
	    }
	}

	public int getFieldCount() {
	    return 5;
	}
}
