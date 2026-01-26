package Program5;

public abstract class Triangle implements Comparable<Triangle> {
    protected double a;
    protected double b;
    protected int edge;
    
    public Triangle(double a, double b, int edge) {
    	if(a <= 0) {
    		throw new IllegalArgumentException("a must be > 0");
    	}
    	if(b <= 0) {
    		throw new IllegalArgumentException("b must be > 0");
    	}
    	if(edge <= 0 || edge >= 180) {
    		throw new IllegalArgumentException("edge must be > 0 and < 180");
    	}
    	
        this.a = a;
        this.b = b;
        this.edge = edge;
        
    	if(!IsTriangle()) {
    		throw new IllegalArgumentException("this is not a triangle");
    	}
    }

    public abstract double area();
    public abstract double perimeter();
    
    public double getA() { return a; }
    public double getB() { return b; }
    public int getEdge() { return edge; }
    
	private boolean IsTriangle() {
		double c = Math.sqrt(getA()*getA() + getB()*getB() - 2*getA()*getB()*Math.cos(Math.toRadians(getEdge())));
		if(a + b > c && a + c > b && b + c > a) {
			return true;			
		}
		return false;
	}
	
	public void print() {
		System.out.print("Triangle : a = " + a + "; b = " + b + "; edge = " + edge);
	}
	
    @Override
    public int compareTo(Triangle other) {
        return Double.compare(this.area(), other.area());
    }
}