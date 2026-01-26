package Program3;

import java.util.Scanner;
import java.util.Arrays;
import java.util.Random;
import java.util.Date;

public class Matrix {

    public static void main(String[] args) {
        
        if (args.length < 2) {
            System.err.println("Usage: java Matrix <type> <k>");
            System.err.println("Where: ");
            System.err.println("  type - 'rows' to sort by column, 'cols' to sort by row");
            System.err.println("  k - column/row index for sorting (0-based)");
            System.exit(1);
        }
        
        String sortType = args[0].toLowerCase();
        int k = Integer.parseInt(args[1]);
        
        System.out.print("Enter n: ");
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        in.close();
        
        if (n <= 1) {
            System.err.println("Invalid n value, require n > 1");
            System.exit(1);
        }
        
        if (k < 0 || k >= n) {
            System.err.println("Invalid k value, require 0 <= k < n");
            System.exit(1);
        }
        
        Random rnd = new Random((new Date()).getTime());
        int[][] arr = new int[n][n];
        
        System.out.println("Source matrix:");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                arr[i][j] = rnd.nextInt(2 * n + 1) - n;
                System.out.print(arr[i][j] + " ");
            }
            System.out.println();
        }
        
        if ("rows".equals(sortType)) {
        	int[][] sortedMatrix = new int[n][n];
        	for (int i = 0; i < n; i++) {
        	    sortedMatrix[i] = arr[i].clone();
        	}
            
            Arrays.sort(sortedMatrix, (row1, row2) -> Integer.compare(row1[k], row2[k]));
            
            System.out.println("\nMatrix with rows sorted by column " + k + " (ascending):");
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    System.out.print(sortedMatrix[i][j] + " ");
                }
                System.out.println();
            }
            
        } else if ("cols".equals(sortType)) {
        	int[][] sortedMatrix = new int[arr.length][];
        	for (int i = 0; i < arr.length; i++) {
        	    sortedMatrix[i] = arr[i].clone();
        	}
            
            Integer[] columnIndices = new Integer[n];
            for (int i = 0; i < n; i++) {
                columnIndices[i] = i;
            }
            
            Arrays.sort(columnIndices, (col1, col2) -> 
                Integer.compare(sortedMatrix[k][col1], sortedMatrix[k][col2]));
            
            int[][] result = new int[n][n];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    result[i][j] = sortedMatrix[i][columnIndices[j]];
                }
            }
            
            System.out.println("\nMatrix with columns sorted by row " + k + " (ascending):");
            for (int i = 0; i < result.length; i++) {
                for (int j = 0; j < result[i].length; j++) {
                    System.out.print(result[i][j] + " ");
                }
                System.out.println();
            }
            
        } else {
            System.err.println("Invalid sort type. Use 'rows' or 'cols'");
            System.exit(1);
        }
    }
}