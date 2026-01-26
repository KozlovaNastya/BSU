package Program4;

public class MatrixTest {
    
    public static void swapMinMaxRowsInColumn(Matrix[] matrices, int k) {
        for (int i = 0; i < matrices.length; i++) {
            System.out.println("Marix " + (i + 1) + " before process :");
            matrices[i].print();
            
            try {
                int[] minMaxRows = matrices[i].findMinMaxRowsInColumn(k);
                int minRow = minMaxRows[0];
                int maxRow = minMaxRows[1];
                
                System.out.println("In col " + k + ":");
                System.out.println("Min : " + matrices[i].getElement(minRow, k) + " in row " + minRow);
                System.out.println("Max : " + matrices[i].getElement(maxRow, k) + " in row " + maxRow);
                
                if (minRow != maxRow) {
                    matrices[i].swapRows(minRow, maxRow);
                    System.out.println("Rows " + minRow + " and " + maxRow + " were swaped");
                } else {
                    System.out.println("Min and Max in one row - no need to make swap");
                }
                
                System.out.println("Matrix " + (i + 1) + " after processed :");
                matrices[i].print();
                
            } catch (IllegalArgumentException e) {
                System.out.println("Error while processed matrix " + (i + 1) + " : " + e.getMessage());
            }
        }
    }
    
    public static void main(String[] args) {
        System.out.println("Constructors :");
        
        try {
            Matrix m1 = new Matrix();
            System.out.println("Constructor without parameteres :");
            m1.print();
            
            Matrix m2 = new Matrix(3);
            System.out.println("Constructor with 1 parameter :");
            m2.print();
            
            Matrix m3 = new Matrix(2, 4);
            System.out.println("Constructor with 2 parameteres :");
            m3.print();
            
            Matrix m4 = new Matrix(m3);
            System.out.println("Copy Constructor : ");
            m4.print();
            
            
        } catch (Exception e) {
            System.out.println("Error with creating matrix : " + e.getMessage());
        }
        
        System.out.println("Set Elements : ");
        
        Matrix testMatrix = new Matrix(3, 3);
        testMatrix.setElement(0, 0, 1.0);
        testMatrix.setElement(1, 1, 2.0);
        testMatrix.setElement(2, 2, 3.0);
        
        testMatrix.print();
        
        System.out.println("Element [1,1] = " + testMatrix.getElement(1, 1));
        
        try {
            testMatrix.setElement(5, 5, 10.0);
        } catch (IllegalArgumentException e) {
            System.out.println("Expected exception : " + e.getMessage());
        }
        
        System.out.println("\n Resize :");
        Matrix resizeMatrix = new Matrix(2, 2);
        resizeMatrix.setElement(0, 0, 1.0);
        resizeMatrix.setElement(0, 1, 2.0);
        resizeMatrix.setElement(1, 0, 3.0);
        resizeMatrix.setElement(1, 1, 4.0);
        
        System.out.println("Sourse matrix 2x2:");
        resizeMatrix.print();
        
        resizeMatrix.resize(3, 3);
        System.out.println("Resize matrix 3x3:");
        resizeMatrix.print();
        
        System.out.println("Sub Matrix [1:2, 1:2]:");
        resizeMatrix.printSubmatrix(1, 2, 1, 2);
        
        System.out.println("\n TASK");
        
        Matrix[] matrices = new Matrix[3];
        
        matrices[0] = new Matrix(3, 3);
        matrices[0].fillRandom(-3, 4);
        
        matrices[1] = new Matrix(4, 4);
        matrices[1].fillRandom(1.0, 10.0);
        
        matrices[2] = new Matrix(2, 3);
        matrices[2].fillRandom(10, 20);
        
        swapMinMaxRowsInColumn(matrices, 1);
    }
}