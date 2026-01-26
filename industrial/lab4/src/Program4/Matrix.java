package Program4;

public class Matrix {
	private double data[][];
	private int rows;
	private int cols;
	
	public Matrix() {
        this(1, 1);
    }
    
    public Matrix(int size) {
        this(size, size);
    }
    
    public Matrix(int rows, int cols) {
    	if (rows <= 0) {
            throw new IllegalArgumentException("Rows must be > 0. Your input : " + rows);
        }
        if (cols <= 0) {
            throw new IllegalArgumentException("Cols must be > 0. Your input : " + cols);
        }
    	
    	this.rows = rows;
    	this.cols = cols;
    	this.data = new double[rows][cols];
    }
    
    public Matrix(Matrix other) {
    	if (other == null) {
            throw new IllegalArgumentException("Source matrix cannot be null");
        }
        
        this.rows = other.rows;
        this.cols = other.cols;
        this.data = new double[rows][cols];
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                this.data[i][j] = other.data[i][j];
            }
        }
    }
    
    public void setElement(int row, int col, double value) {
        if (row < 0 || row >= rows) {
            throw new IllegalArgumentException("Incorrect row index: " + row);
        }
        if (col < 0 || col >= cols) {
            throw new IllegalArgumentException("Incorrect col index: " + col);
        }
        
        data[row][col] = value;
    }
    
    public double getElement(int row, int col) {
        if (row < 0 || row >= rows) {
            throw new IllegalArgumentException("Incorrect row index: " + row);
        }
        if (col < 0 || col >= cols) {
            throw new IllegalArgumentException("Incorrect col index: " + col);
        }
        
        return data[row][col];
    }
    
    public void resize(int newRows, int newCols) {
    	if (rows <= 0) {
            throw new IllegalArgumentException("NEW Rows must be > 0. Your input : " + rows);
        }
        if (cols <= 0) {
            throw new IllegalArgumentException("NEW Cols must be > 0. Your input : " + cols);
        }
        
        double[][] newData = new double[newRows][newCols];
        
        int minRows = Math.min(rows, newRows);
        int minCols = Math.min(cols, newCols);
        
        for (int i = 0; i < minRows; i++) {
            for (int j = 0; j < minCols; j++) {
                newData[i][j] = data[i][j];
            }
        }
        
        this.data = newData;
        this.rows = newRows;
        this.cols = newCols;
    }
    
    public int getRows() {
        return rows;
    }
    
    public int getCols() {
        return cols;
    }
    
    public void print() {
        printSubmatrix(0, rows - 1, 0, cols - 1);
    }
    
    public void printSubmatrix(int startRow, int endRow, int startCol, int endCol) {
        if (startRow < 0 || endRow >= rows || startRow > endRow) {
            throw new IllegalArgumentException("Incorrect row bounds: " + startRow + "-" + endRow);
        }
        if (startCol < 0 || endCol >= cols || startCol > endCol) {
            throw new IllegalArgumentException("Incorrect cols bounds: " + startCol + "-" + endCol);
        }
        
        for (int i = startRow; i <= endRow; i++) {
            for (int j = startCol; j <= endCol; j++) {
                System.out.printf("%8.2f", data[i][j]);
            }
            System.out.println();
        }
        System.out.println();
    }
    
    public int[] findMinMaxRowsInColumn(int column) {
        if (column < 0 || column >= cols) {
            throw new IllegalArgumentException("Incorrect col index : " + column);
        }
        
        int minRow = 0;
        int maxRow = 0;
        double minValue = data[0][column];
        double maxValue = data[0][column];
        
        for (int i = 1; i < rows; i++) {
            if (data[i][column] < minValue) {
                minValue = data[i][column];
                minRow = i;
            }
            if (data[i][column] > maxValue) {
                maxValue = data[i][column];
                maxRow = i;
            }
        }
        
        return new int[]{minRow, maxRow};
    }
    
    public void swapRows(int row1, int row2) {
        if (row1 < 0 || row1 >= rows || row2 < 0 || row2 >= rows) {
            throw new IllegalArgumentException("Incorrect rows indexes: " + row1 + ", " + row2);
        }
        
        if (row1 != row2) {
            double[] temp = data[row1];
            data[row1] = data[row2];
            data[row2] = temp;
        }
    }
   
    public void fillRandom(double min, double max) {
        if(min > max) {
        	throw new IllegalArgumentException("Max must be >= min");
        }
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = min + Math.random() * (max - min);
            }
        }
    }
}